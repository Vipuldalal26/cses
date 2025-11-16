Below are clean, ready-to-convert notes for:

-   **Topic 2 -- Processes vs Threads (Core Concept)**

-   **Topic 3 -- CPU Scheduling & Context Switching**

I'll structure them with headings, lists, tables, code blocks, and small diagrams.

* * * * *

Topic 2 -- Processes vs Threads (Core Concept)
=============================================

1\. Background and Context
--------------------------

Early computers ran **one program at a time**. There was no concept of "multiple apps open." Over time, users wanted to:

-   Run **multiple programs simultaneously** (browser + IDE + music player).

-   Make a single program do **multiple things at once** (server handling many requests).

Operating systems introduced:

-   **Processes** → to run multiple programs at the same time.

-   **Threads** → to let a single process handle multiple tasks concurrently.

For you as a backend/Spring Boot/Kubernetes engineer:

-   Each **microservice** runs as a **process** (your JVM inside a container).

-   Inside each process, you have many **threads** (Tomcat workers, DB pool threads, GC, etc.).

-   Understanding this lets you reason about **performance, crashes, and concurrency**.

* * * * *

2\. Definitions and Key Concepts
--------------------------------

### 2.1 Process

A **process** is a running program with its **own isolated memory space** and resources.

Key properties:

-   Has a unique **PID** (Process ID).

-   Has its own:

    -   **Code** (instructions)

    -   **Data** (global/static variables)

    -   **Heap** (dynamic memory, e.g., Java objects)

    -   **Stacks** (one per thread)

    -   Open files, network sockets

-   Managed by the **operating system kernel**.

You can see processes with:

```
ps -ef

```

* * * * *

### 2.2 Thread

A **thread** is the smallest unit of execution **inside a process**.

Key properties:

-   Shares the process's:

    -   Code

    -   Data

    -   Heap

    -   File descriptors (e.g., sockets)

-   Has its own:

    -   Stack (local variables, function call frames)

    -   CPU register state (what it's currently executing)

You see threads per process with:

```
ps -eLf | grep <PID>
top -H -p <PID>

```

* * * * *

### 2.3 Process vs Thread -- Comparison

| Aspect | Process | Thread |
| --- | --- | --- |
| Definition | A running program with its own memory | Execution unit inside a process |
| Memory space | Separate, isolated | Shared (uses the same process memory) |
| Creation cost | High (new memory mappings, resources) | Low (reuses existing memory) |
| Communication | Via IPC (sockets, pipes, shared memory) | Via shared variables in same heap |
| Failure impact | Process crash does **not** kill others | Thread crash can bring down the **process** |
| Isolation | Strong | Weak (same address space) |
| Scheduling unit | Indirectly (through its threads) | Directly scheduled onto CPU cores |

* * * * *

3\. Why Threads Exist
---------------------

### 3.1 Problem Without Threads

If we used only processes:

-   Each concurrent task = separate process.

-   Each process needs its own memory space and OS bookkeeping.

-   Communication between them is slower (IPC).

-   Process creation is relatively expensive.

For a server handling 1000 concurrent clients, 1 process/client would be heavy.

### 3.2 What Threads Solve

Threads allow:

-   **Concurrency inside a single process**.

-   Fast communication via shared heap.

-   Lower overhead than creating multiple processes.

Example (Spring Boot):

-   One **JVM process** runs your service.

-   It creates:

    -   Many **Tomcat worker threads** for HTTP requests.

    -   **HikariCP** threads for DB connections.

    -   **Kafka consumer** threads.

    -   **GC** and other internal JVM threads.

All share the **same Java heap**, making it easy to share state (services, caches, configs) between requests.

* * * * *

4\. What Happens When a Process Dies
------------------------------------

When a process:

-   exits normally (`System.exit`, main method returns), or

-   crashes (e.g., fatal error, OOM, segmentation fault),

-   or is killed (`kill`, `SIGKILL`, container stop),

the OS will:

1.  Remove it from the **process table**.

2.  Free its **memory** (code, data, heap, stacks).

3.  Close its **open files and sockets**.

4.  Mark any child processes as **orphaned** (they're reparented to `init`/PID 1).

**Important point:**

-   All **threads** inside the process die instantly with it.

-   You cannot have a "thread surviving" if the process is gone.

In Kubernetes:

-   Your **container main process** (often the JVM) dies.

-   The pod's container is marked not ready.

-   Kubernetes restarts the container (new process, fresh heap, new threads).

* * * * *

5\. Shared Memory and Isolation
-------------------------------

### 5.1 Memory Inside a Single Process

Within a process:

-   All threads share:

    -   Same **code section**.

    -   Same **global/static data**.

    -   Same **heap** (all Java objects).

    -   Same **file descriptors** (sockets, files).

-   Each thread has:

    -   Its own **stack**.

This is powerful but dangerous:

-   Two threads can read/write the same object at the same time.

-   Without synchronization, this causes **race conditions**, **data corruption**, and **weird bugs**.

In Java:

-   You synchronize shared access using:

    -   `synchronized`

    -   `ReentrantLock`

    -   `AtomicInteger`

    -   Concurrent collections like `ConcurrentHashMap`

* * * * *

### 5.2 Memory Between Different Processes

Different processes:

-   Have **separate address spaces**.

-   Cannot see each other's heap or stack directly.

-   Must use **Inter-Process Communication (IPC)** to talk:

    -   Sockets (TCP/UDP)

    -   Pipes

    -   Shared memory regions

    -   Files

This makes processes **safer** (one cannot corrupt another's memory) but **slower to talk** compared to threads.

* * * * *

6\. Use Cases and Applications
------------------------------

### 6.1 Where Processes Are Used

-   Running separate applications:

    -   Browser, IDE, Terminal, DB server.

-   Microservices on a node:

    -   `esp-bpo-service` JVM process.

    -   `esp-carrierintegration-service` JVM process.

    -   Envoy/Istio, sidecar containers.

Each microservice = **separate process** (running in its own container).

* * * * *

### 6.2 Where Threads Are Used

Inside your Spring Boot service (one JVM process):

-   **Tomcat (Servlet) model**:

    -   One thread per concurrent HTTP request (up to max threads).

-   **HikariCP**:

    -   Threads managing DB connections.

-   **Kafka consumers**:

    -   One thread per consumer.

-   **Async tasks**:

    -   `@Async`, `CompletableFuture`, scheduled executors.

-   **JVM internal threads**:

    -   GC threads.

    -   JIT compiler threads.

All live in the same process and share memory.

* * * * *

7\. Why This Matters
--------------------

If you ignore process/thread concepts:

-   You cannot understand:

    -   Why one service crash kills all current requests.

    -   Why too many threads hurt performance (context switching).

    -   Why race conditions and deadlocks happen.

-   You misconfigure:

    -   Thread pools (Tomcat, Hikari)

    -   CPU/memory limits per pod

    -   Number of pods vs. threads

Understanding processes vs threads allows you to:

-   Design **scalable**, **stable** services.

-   Debug **high CPU**, **hangs**, **deadlocks**, **OOMs**.

-   Tune **thread pools** and **replica counts** correctly.

* * * * *

8\. Visual / Mental Model
-------------------------

Process and threads:

```
Operating System
 ├─ Process A (PID 101): JVM for esp-bpo-service
 │   ├─ Thread 1: main
 │   ├─ Thread 2: GC
 │   ├─ Thread 3: Tomcat worker #1
 │   ├─ Thread 4: Tomcat worker #2
 │   └─ Thread 5: HikariCP pool thread
 └─ Process B (PID 202): JVM for esp-carrierintegration-service
     ├─ Thread 1: main
     └─ ...

```

-   Each **process** is a separate box with its own memory.

-   Threads are "workers" inside that box.

If **Process A** dies, all its threads are gone, but **Process B** keeps running.

* * * * *

Topic 3 -- CPU Scheduling & Context Switching
============================================

1\. Background and Context
--------------------------

Modern systems run:

-   Hundreds of processes.

-   Thousands of threads.

But you only have a **limited number of CPU cores** (e.g., 4, 8, 16).

The OS must **decide**:

-   Which thread runs now.

-   Which one waits.

-   For how long.

This decision-making is **CPU scheduling**, and the act of switching between threads is **context switching**.

In your world:

-   You may have 300 threads in a Spring Boot app.

-   Only a handful can run at the same time.

-   Scheduling behavior directly impacts latency and throughput.

* * * * *

2\. Definitions and Key Concepts
--------------------------------

### 2.1 CPU Core

-   A **core** executes instructions.

-   A CPU with 8 cores can run **8 threads simultaneously** (one per core).

### 2.2 Time-Sharing

-   The OS rapidly switches between runnable threads on each core.

-   Gives the illusion that many things run "at the same time", even if cores are fewer.

### 2.3 Thread States (Simplified)

Common thread states:

-   **Running** -- currently executing on a core.

-   **Runnable/Ready** -- ready to run, waiting in the run queue.

-   **Blocked/Sleeping** -- waiting on I/O, lock, `sleep`, etc.

-   **Terminated** -- finished execution.

The scheduler only chooses from **runnable** threads.

* * * * *

3\. Context Switching
---------------------

A **context switch** happens when the CPU stops running one thread and starts running another.

Steps (simplified):

1.  Save current thread's state:

    -   CPU registers

    -   Program counter (where it left off)

    -   Stack pointer

2.  Load the next thread's saved state.

3.  Jump to the next thread's program counter and resume.

Context switches are:

-   Necessary for multitasking.

-   Cheap but **not free**. Too many switches → CPU time wasted on overhead instead of real work.

* * * * *

4\. CPU Scheduling -- How the OS Chooses the Next Thread
-------------------------------------------------------

### 4.1 Basic Idea

The scheduler's goals:

-   Share CPU fairly among threads.

-   Keep the system responsive.

-   Prioritize some threads if needed (via priorities).

### 4.2 Time Slice (Quantum)

-   Each runnable thread gets a small **time slice** (e.g., a few ms).

-   When the slice expires:

    -   If the thread is still running, it may be preempted (forced off).

    -   Another runnable thread gets the CPU.

This is called **preemptive multitasking**.

* * * * *

### 4.3 Linux CFS (Completely Fair Scheduler) -- Simplified

Linux uses **CFS** for normal threads:

-   Keeps a tree of runnable threads.

-   Tracks how much CPU time each has used.

-   Gives CPU time to threads that have used **less** so far.

-   Priority (nice value) influences how much CPU share a thread gets.

Result:

-   CPU-bound threads don't starve others.

-   I/O-bound threads (that often block quickly) get CPU when they need it.

* * * * *

5\. Runnable vs Blocked Threads
-------------------------------

### 5.1 Runnable

-   Ready to run and waiting in the run queue.

-   Compete for CPU time.

-   Cause **CPU usage**.

### 5.2 Blocked

-   Waiting on:

    -   Disk I/O

    -   Network I/O

    -   Sleep timers

    -   Locks / synchronization

-   Do **not** consume CPU while blocked.

-   Scheduler skips them until they become runnable again.

In a typical Spring Boot app:

-   Many threads are usually blocked (waiting on DB or HTTP responses).

-   Only a few are **actually running** at any given time.

* * * * *

6\. Multi-Core and Load
-----------------------

On a multi-core system:

-   Each core has its own queue of runnable threads.

-   Load balancer (inside OS) may rebalance threads between cores.

Example:

-   8 cores, 100 runnable threads:

    -   At most 8 threads run concurrently.

    -   92 are waiting in ready queues.

-   Load average roughly indicates how many threads are runnable/blocked-on-IO over time.

* * * * *

7\. Containers, cgroups, and CPU Limits
---------------------------------------

In Kubernetes, containers are controlled by **cgroups**.

### 7.1 CPU Requests and Limits

```
resources:
  requests:
    cpu: "500m"   # 0.5 core guaranteed (scheduling hint)
  limits:
    cpu: "2000m"  # 2 cores max

```

-   **Request** → what the scheduler uses to pack pods on nodes.

-   **Limit** → actual upper cap on CPU usage enforced by the kernel.

### 7.2 CPU Throttling

If your container hits its CPU limit:

-   The kernel **throttles** its threads:

    -   They are temporarily prevented from running even if the node has spare CPU.

-   You'll see:

    -   Higher latencies.

    -   p95/p99 spikes.

    -   Throttling counters increasing.

Inside the container (cgroup v2 example):

```
cat /sys/fs/cgroup/cpu.stat
# Look at "nr_throttled" and "throttled_usec"

```

* * * * *

8\. Observing Scheduling and Threads in Practice
------------------------------------------------

Useful commands inside a pod:

```
# 1. Find the JVM process
ps -eo pid,cmd | grep java

# 2. Show per-thread CPU usage
top -H -p <PID>

# 3. Show scheduling stats for a process
cat /proc/<PID>/sched

```

You can see:

-   Which threads use the most CPU.

-   How many context switches they have.

-   Whether your application is CPU-bound or mostly waiting on I/O.

* * * * *

9\. Use Cases and Applications
------------------------------

### 9.1 Thread Pool Tuning

Knowing that CPU cores are limited:

-   For **CPU-bound tasks** (heavy computation), you want:

    -   Thread count ≈ number of cores (or slightly above).

-   For **I/O-bound tasks** (DB, HTTP calls), you can:

    -   Use more threads than cores because many threads are blocked.

If you overshoot:

-   Too many runnable threads → context-switching overhead → worse performance.

* * * * *

### 9.2 Capacity Planning

Using scheduling knowledge:

-   Decide **how many cores per pod** you need.

-   Decide **how many pods** for your expected QPS.

-   Avoid CPU throttling by setting reasonable `limits`.

* * * * *

### 9.3 Debugging High CPU

When CPU is high:

-   Use `top -H -p <PID>` to see which threads are hot.

-   Combine with Java tools (`jstack`, `jcmd`) to see what those threads are doing.

-   Check if:

    -   GC is running too often.

    -   A particular endpoint/loop is burning CPU.

    -   Too many threads are competing at once.

* * * * *

10\. Why Scheduling & Context Switching Matter
----------------------------------------------

If you don't understand these concepts:

-   You might:

    -   Randomly set thread pools (e.g., 500 threads on 1 core).

    -   Set CPU limits too low and blame "network" for latency.

    -   Fail to link high CPU metrics with real code paths.

-   Systems may:

    -   Thrash due to too many runnable threads.

    -   Show spiky latency under load.

    -   Waste resources.

If you do understand:

-   You can:

    -   Size CPU cores per pod rationally.

    -   Tune thread pools based on cores and workload type.

    -   Interpret CPU and context-switch metrics correctly.

    -   Explain **why** a system misbehaves under load -- not guess.

* * * * *

11\. Visual / Mental Model
--------------------------

### 11.1 One Core, Many Threads

```
Time →
+---------+---------+---------+---------+
| ThreadA | ThreadB | ThreadC | ThreadA |
+---------+---------+---------+---------+

```

-   OS runs `ThreadA` for a slice, then `ThreadB`, then `ThreadC`, etc.

-   Each switch requires saving/loading context.

### 11.2 Multi-Core and Runnable Threads

```
Core 1: [Thread A] [Thread D] [Thread B] ...
Core 2: [Thread C] [Thread E] [Thread F] ...
Core 3: [Idle]     [Thread G] [Idle] ...
Core 4: [Thread H] [Thread I] [Thread J] ...

```

-   Only as many threads run as there are cores.

-   Others wait in queues.

* * * * *

These notes should be directly usable as a `.md` file with minimal change.\
Next step (whenever you want): we can go deeper into **how an HTTP request flows through threads in Spring Boot (Tomcat vs Netty) and how that interacts with scheduling and processes**.