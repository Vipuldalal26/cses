📘 Complete Curriculum: _Processes vs Threads (and surrounding concepts) for a Software Engineer_
-------------------------------------------------------------------------------------------------

I’ll teach you each topic like a teacher would, one at a time — with diagrams and examples that match your work.

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