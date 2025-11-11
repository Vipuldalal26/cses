# JVM, Spring Boot Startup, Tomcat, and Kubernetes Routing — Practical Notes
**Date:** 2025-11-11

These notes summarize everything covered: JVM basics, Spring Boot startup lifecycle, JIT warm‑up, JVM memory regions, Tomcat/web‑server fundamentals, request parsing, worker threads, signals (SIGTERM), Kubernetes primitives (Namespace, Service, Ingress), ports, and the full end‑to‑end request flow. Examples and commands included.

---


## 1) Java Execution Pipeline: Source → Bytecode → JVM
**Goal:** understand what actually runs when you execute a Java/Spring Boot app.

1. **Compile**
   - `javac` compiles `*.java` → `*.class` (bytecode; platform‑independent).
2. **Run**
   - `java` starts the **JVM** (Java Virtual Machine).
   - JVM loads classes, verifies bytecode, and executes it via **interpreter + JIT**.
3. **Why Java is portable**
   - The same `.class` (bytecode) runs on Windows, Linux, macOS because **JVM** is the native translator per OS/CPU.

**Tiny example**
```java
class Hello { public static void main(String[] a){ System.out.println("Hello"); } }
```
Run: `javac Hello.java` → `Hello.class` → `java Hello`

---

## 2) What happens when a Spring Boot service starts in a container (Kubernetes)
**Observed log:** `Tomcat started on port(s): 8080 (http)` and `Started Application in X.Ys (JVM running for Z.ZZ)`.

**Sequence**
```
Container starts → java -jar app.jar
   → JVM boots (sets up Heap/Stack/Metaspace, class loaders, JIT)
   → Spring Boot auto-configuration
   → Embedded Tomcat/Netty/Undertow starts
   → Tomcat binds to internal port (default 8080)
   → “Started Application in … (JVM running for …)”
   → Pod becomes ready to receive traffic
```

**Meaning of the line**
- `Started Application in 7.123s` → time for Spring context + server startup.
- `(JVM running for 7.456)` → total uptime since `java` process began.

---

## 3) JIT (Just‑In‑Time Compiler) and warm‑up
**Problem:** Interpreting bytecode line‑by‑line is slow.
**Solution:** **JIT** compiles “hot” methods (frequently executed) into native machine code during runtime.

**Effect in services**
- First few requests: slower (interpreter + caches cold).
- After warm‑up: hot paths JIT‑compiled → near native speed.

**Example (hot loop)**
```java
for (int i = 0; i < 1_000_000; i++) { Math.sqrt(i); } 
```
Initially interpreted; once JVM detects it’s hot, it JIT‑compiles that path.

**Operational tip:** send “warming calls” after deployment to prime caches/JIT before live traffic.

---

## 4) JVM Memory Regions: Heap, Stack, Metaspace
**Purpose:** separation of concerns, performance, and GC management.

| Region      | What it stores                                   | Scope                  | Example (HTTP request path)                                  |
|-------------|---------------------------------------------------|------------------------|---------------------------------------------------------------|
| **Heap**    | Objects created with `new`                        | Shared across threads  | DTOs, Entities, `List<Order>`, Spring beans, JSON trees       |
| **Stack**   | Call frames + local variables per thread          | Per‑thread, LIFO       | Controller method params, local variables during execution    |
| **Metaspace** | Class metadata (method/field tables, bytecode) | Shared, mostly static  | Definition of `UserService`, `OrderController`, etc.          |

**Concrete request example**
```java
@GetMapping("/users/{id}")
UserDto get(@PathVariable long id) {
    var user = userService.find(id);     // user (Heap), local var ref (Stack)
    return mapper.toDto(user);           // dto (Heap), locals (Stack)
}
```
- **Stack (worker thread):** `id`, reference to `user`, reference to `dto`.
- **Heap:** the `user` entity, the `dto`, any intermediate objects.
- **Metaspace:** the class layouts (`User`, `UserService`, `UserDto`, etc.).

**GC (Garbage Collector):** reclaims Heap objects no longer referenced.

---

## 5) Tomcat = Embedded Web Server (default in Spring Boot)
**What is a web server?** Software that listens on a TCP port, speaks **HTTP**, parses requests, and writes HTTP responses.

**Why you need it:** Without a web server, your Java program wouldn’t accept network HTTP requests. Tomcat provides:
- TCP acceptor
- HTTP parser (headers, method, path, body)
- Servlet API bridge → Spring MVC controllers
- Thread pool (worker threads) to serve many requests concurrently

**Default port 8080**
- 80 is the standard HTTP port but usually requires elevated privileges.
- Spring Boot defaults to **8080** (change via `server.port=9090`).

**“I never hit 8080” (in Kubernetes)**
- You usually hit a public URL (port 80/443 on an Ingress/Gateway).
- Inside the cluster, traffic is forwarded to the **container’s 8080** where Tomcat listens.

**What will I see at http://localhost:8080/**
- If no `/` mapping → Spring “Whitelabel Error Page” or 404.
- With a controller mapping at root → your JSON/HTML response.

**HTTP parsing example**
Raw:
```
POST /login HTTP/1.1
Host: api.example.com
Content-Type: application/json
Content-Length: 34

{"user":"vipul","pass":"1234"}
```
Becomes (Servlet API):
```java
req.getMethod()      // "POST"
req.getRequestURI()  // "/login"
req.getHeader("Content-Type") // "application/json"
req.getInputStream() // body stream → parsed JSON
```

---

## 6) Tomcat worker threads; Process vs Thread
- **Process:** an OS‑level running program with its own memory space. → your **JVM**.
- **Thread:** a lightweight execution unit within a process, sharing its memory. → **Tomcat worker threads**.

**Flow**
```
JVM process (1) → Tomcat thread pool (many)
Each HTTP request → assigned to a free worker thread → calls your controller → returns response.
```
**Key property**
```properties
server.tomcat.threads.max=200   # max concurrent request threads
```

---

## 7) Signals: SIGTERM (graceful) vs SIGKILL (force)
- **SIGTERM:** polite stop signal. Spring Boot shutdown hooks run: stop Tomcat, close DB pools, finish in‑flight work.
- **SIGKILL:** forced termination (no cleanup). Sent if the app ignores SIGTERM within the grace period.

**Kubernetes lifecycle**
```
kubectl delete pod X → K8s sends SIGTERM → waits (terminationGracePeriodSeconds) → if still running, sends SIGKILL
```

---

## 8) Kubernetes: Namespace, Service, Ingress — beginner view
**Namespace** = logical folder/isolation boundary in a cluster. Different teams/apps keep resources separate.

### Service
Stable virtual IP (ClusterIP) that load‑balances to your pods.
- Type **ClusterIP**: internal‑only (most common for microservices)
- Other types: **NodePort**, **LoadBalancer**, **ExternalName**

Example (your output):
```
NAME                                    TYPE       CLUSTER-IP     PORT(S)
esp-carrierintegration-service-primary  ClusterIP  10.50.170.121  8080/TCP
```
Pods can call: `http://esp-carrierintegration-service-primary.esp-stg-01-cissvc.svc.cluster.local:8080`

### Ingress (entry gate)
HTTP(S) router at the cluster boundary. Listens on 80/443 and forwards based on host/path to **Services** (not pods). Often centralized in a different namespace.

**“Ingress endpoint” (informal term):** the public DNS/IP of the Ingress Controller/load balancer (e.g., `a1b2c3d4e5.elb.amazonaws.com`).

**Typical external flow**
```
Client → Ingress (443) → Service (ClusterIP) → Pod (container:8080) → JVM → Tomcat → Controller
```

---

## 9) Ports: valid range
- Port numbers are **16‑bit unsigned** → **0–65535**.
- 0–1023: well‑known (22 SSH, 80 HTTP).
- 1024–49151: registered.
- 49152–65535: ephemeral/dynamic.

**Invalid:** 909090 (out of range).

---

## 10) End‑to‑end request flow (ASCII diagrams)

### A. Network path (external to container)
```
🌍 Client (HTTPS) 
   │
   ▼
🚦 Ingress Controller (Nginx/ALB/Traefik) :443
   │  routes by Host/Path
   ▼
🔁 Service (ClusterIP) :80 → targetPort 8080
   │  balances across pods
   ▼
🧱 Pod → Container (your image)
   │
   ▼
☕ JVM process: java -jar app.jar
   │
   ▼
🧩 Embedded Tomcat :8080  (HTTP server)
   │  parses request, selects a worker thread
   ▼
⚙️ Worker thread executes controller/service/DAO
   │
   ▼
✅ Response → Tomcat → Service → Ingress → Client
```

### B. Inside the JVM: memory & execution
```
Request hits Tomcat
   ├─ Select/dispatch worker thread
   ├─ Controller method invoked
   │    ├─ Locals on Stack (params, temp vars)
   │    ├─ Objects on Heap (DTOs, Entities, maps)
   │    └─ Class metadata in Metaspace
   ├─ JIT may optimize hot paths on the fly
   └─ GC reclaims unused Heap objects over time
```

---

## 11) Practical kubectl commands you used

```bash
# List namespaces
kubectl get ns

# List ingresses in current namespace
kubectl get ingress

# List ingresses across all namespaces
kubectl get ingress -A

# List pods in a namespace
kubectl get pods -n esp-stg-01-cissvc

# List services in a namespace
kubectl get svc -n esp-stg-01-cissvc

# Describe a specific service (see selectors, endpoints)
kubectl describe svc esp-carrierintegration-service-primary -n esp-stg-01-cissvc
```

---

## 12) Quick Q&A Recap

- **Why first requests are slower?** JIT warm‑up + caches cold. After a few hits, hot methods are native‑compiled.
- **Why Tomcat on 8080?** Unprivileged default. In k8s you hit 80/443 at ingress; internally it maps to 8080.
- **What is parsing HTTP?** Converting raw bytes into structured request objects (method, headers, body).
- **Process vs Thread here?** One JVM process; many Tomcat worker threads per request.
- **What is SIGTERM?** Graceful stop signal; Spring Boot shuts down cleanly. SIGKILL is the hard stop fallback.
- **What is Ingress?** Public HTTP(S) gateway routing to Services inside cluster. “Ingress endpoint” = its public DNS/IP.
- **What is a Namespace?** Logical isolation boundary (like folders). Different teams/services live in different namespaces.
- **Port range?** 0–65535 only.

---

## 13) Minimal config/code references

**Change server port**
```properties
server.port=9090
```

**Tune Tomcat threads**
```properties
server.tomcat.threads.max=200
```

**Simple controller to test stack/heap mapping**
```java
@RestController
class UserController {
  @GetMapping("/users/{id}")
  UserDto get(@PathVariable long id) {
    User u = userService.find(id);   // Heap
    UserDto dto = mapper.toDto(u);   // Heap
    return dto;                      // Heap; locals on Stack
  }
}
```

---

## 14) Mental model: single sentence
**Ingress routes** external HTTP to a **Service**, which load‑balances to a **Pod** running your **JVM**; **Tomcat** parses the request and dispatches a **worker thread**; locals live on the **Stack**, objects on the **Heap**, metadata in **Metaspace**; **JIT** speeds hot paths; **SIGTERM** shuts it all down cleanly.
