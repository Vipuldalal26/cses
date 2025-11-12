📘 Complete Curriculum: _Processes vs Threads (and surrounding concepts) for a Software Engineer_
-------------------------------------------------------------------------------------------------


### **Module 1 — The Foundation**

1.  **What actually happens when you run a program**
    
    *   What is a program vs a process
        
    *   How the OS gives CPU + memory to it
        
    *   What is a thread, stack, heap
        
2.  **Processes vs Threads (core concept)**
    
    *   Why threads exist
        
    *   What happens when a process dies
        
    *   Shared memory and isolation
        
3.  **How multiple processes run “together”**
    
    *   Context switching
        
    *   CPU scheduling basics (fair share, time slice, blocking vs runnable)
        
4.  **How threads are used inside Java + Spring Boot**
    
    *   JVM process, Tomcat/Netty worker threads
        
    *   Example: one HTTP request → which threads handle it
        

### **Module 2 — Inside a Container / Kubernetes Pod**

1.  **What a container really is**
    
    *   Process isolation using namespaces and cgroups
        
    *   “One process per container” rule
        
2.  **What are tini, dumb-init, supervisord, s6, and runit**
    
    *   Why containers need an init process
        
    *   How these manage or forward signals to your app
        
3.  **Multi-process containers**
    
    *   When you run multiple processes inside
        
    *   Why it breaks restart/logging/health-check simplicity
        

### **Module 3 — Communication Between Processes**

1.  **Inter-Process Communication (IPC)**
    
    *   Simple definition: how two running programs talk
        
    *   Mechanisms: files, pipes, sockets, shared memory
        
    *   How your microservices actually use sockets (HTTP/Kafka)
        

### **Module 4 — Networking & Kernel Involvement**

1.  **What happens when a request hits your service**
    
    *   NIC, iptables, CNI — what these mean in Kubernetes
        
    *   Sidecars (Envoy/Istio/Nginx) and why they intercept traffic
        
2.  **Pod network flow visualization**
    
    *   Node → Pod → Container network stack → JVM process thread
        

### **Module 5 — Spring Boot Thread Architecture**

1.  **Servlets, Tomcat, and thread pools**
    
    *   What is a servlet
        
    *   How Tomcat creates and manages worker threads
        
    *   Role of HikariCP (DB connection pool)
        
2.  **Netty, WebFlux, and Reactive model**
    
    *   What Netty is
        
    *   How reactive programming avoids blocking threads
        
    *   Why event-loop threads are different
        

### **Module 6 — System Observation Tools**

1.  **Seeing processes and threads**
    
    *   ps, top, jcmd, jstack, perf, jattach explained clearly
        
2.  **Native memory and what jcmd VM.native\_memory summary shows**
    

### **Module 7 — Putting It All Together**

1.  **One complete journey**
    
    *   From request entering the pod
        
    *   Through container, process, thread, JVM, controller, DB
        
    *   Back to response


# 🧠 Topic 1 – What Happens When You Run a Program

## 1️⃣ Program vs Process
| Term | Meaning |
|------|----------|
| **Program** | A file on disk that contains machine instructions (code + data). It’s *inactive*. |
| **Process** | A running instance of that program created by the operating system. It’s *alive* and executing. |

---

## 2️⃣ Steps When You Run a Program

1. **You type:**
   ```bash
   java -jar esp-bpo-service.jar
   ```

2. **OS loads the program**
   - Copies machine instructions from disk → RAM.
   - Loads needed libraries (e.g., `libjvm.so`, `libc.so`).

3. **OS creates a process**
   - Gives it a **PID** (process ID).
   - Stores info: program path, user, state, open files, network ports, environment vars.
   - Adds entry to its **process table**.

4. **OS allocates memory regions**
   | Region | Purpose |
   |---------|----------|
   | **Code / Text** | The compiled instructions |
   | **Data** | Global/static variables |
   | **Heap** | Dynamically created objects (`new`) |
   | **Stack (per thread)** | Local variables + function calls |

5. **Creates main thread**
   - The first thread that starts running your code.
   - For Java: executes `main()` inside the JVM.

6. **CPU executes instructions**
   - The scheduler gives CPU time to this thread.
   - The process may later create more threads or child processes.

7. **Process terminates**
   - On normal exit or crash, OS cleans up memory and entries.
   - All threads in it die together.

---

## 3️⃣ Example in Your World (Spring Boot + Kubernetes)

| Layer | What Happens |
|--------|---------------|
| **Kubernetes Pod** | The container runtime (Docker/Containerd) tells Linux to start a new process inside an isolated namespace. |
| **That process** | It’s your JVM process. |
| **Inside JVM** | Spring Boot creates threads for Tomcat/Netty, HikariCP, GC, etc. |
| **Threads run** | Handle HTTP requests, DB I/O, background tasks. |

### Hierarchy

```
Pod (namespace)
 └── Container
      └── JVM Process (PID)
           ├── Main Thread
           ├── GC Thread
           ├── Tomcat Worker Threads
           └── HikariCP Threads
```

---

## 4️⃣ Visualization

```
+---------------------------------------------+
|           Operating System Kernel           |
|---------------------------------------------|
| Process Table                               |
|   ├─ PID 101 : java (JVM)                   |
|   |     ├─ Thread 1 : main                  |
|   |     ├─ Thread 2 : GC                    |
|   |     ├─ Thread 3 : Tomcat worker #1      |
|   |     └─ Thread 4 : DB connection pool    |
|   └─ PID 200 : nginx                        |
+---------------------------------------------+
```

---

## 5️⃣ Commands to View It

```bash
ps -ef                 # list processes
ps -eLf | grep java    # show threads inside a process
top -H -p <PID>        # per-thread CPU usage
```

---

## 6️⃣ Key Takeaways

- Every running app = a **process**.
- A process can have **many threads** (lightweight executors).
- OS manages their **memory, CPU, and scheduling**.
- In containers, usually **one main process per container**.
- Spring Boot → one JVM process + many threads.
- When that process ends, all threads inside die.

---

Once you grasp this, you have the foundation for everything else — threads, scheduling, containers, networking, and scaling all build on top of this model.
