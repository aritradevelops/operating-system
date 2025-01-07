# Processes: Definition, Process Relationship, Different states of a Process, Process State transitions, Process Control Block (PCB), Context switching Thread: Definition, Various states, Benefits of threads, Types of threads, Concept of multithreads, Process Scheduling: Foundation and Scheduling objectives, Types of Schedulers, Scheduling criteria: CPU utilization, Throughput, Turnaround Time, Waiting Time, Response Time; Scheduling algorithms: Pre-emptive and Non pre-emptive, FCFS, SJF, RR; Multiprocessor scheduling: Real Time scheduling: RM and EDF. 

### **Processes in Operating Systems**

A **process** is a program in execution. It includes the program code, current activity, and the resources needed to execute it. In the context of an operating system, processes are fundamental units of execution that are managed and scheduled by the OS.

---

### **Process Relationships**
In modern operating systems, processes can have relationships with each other. The most common process relationships are:

1. **Parent and Child Processes:**
   - A **parent process** can create one or more **child processes**. This relationship is typically established via a system call like `fork()` in UNIX-like systems.
   - **Parent-Child Relationship**: The parent process controls and manages the child process. The child inherits most of its resources from the parent.

2. **Siblings:**
   - Processes that share the same parent are called **siblings**.

3. **Process Tree:**
   - A **process tree** is a hierarchical structure of processes, where each process can spawn multiple child processes, creating a tree structure. 
   - The root of the tree is usually the **init process** (in UNIX-based systems).

4. **Orphan Processes:**
   - A **child process** becomes an orphan when its parent terminates before it.
   - The **init process** typically adopts orphan processes.

5. **Zombie Processes:**
   - When a child process terminates, its exit status is stored by the OS until the parent reads it. Until this is done, the process remains in the system as a **zombie**.

---

### **Different States of a Process**
A process can exist in different states during its life cycle. These states are represented as follows:

1. **New**:
   - The process is being created but is not yet scheduled for execution.
   - In this state, the OS is allocating resources and initializing process control blocks.

2. **Ready**:
   - The process is ready to run, but the CPU is not currently allocated to it.
   - It waits in the **ready queue** until the scheduler assigns it CPU time.

3. **Running**:
   - The process is currently being executed by the CPU.
   - It has control over the CPU and is actively performing its task.

4. **Waiting (Blocked)**:
   - The process is waiting for some event to occur, such as waiting for I/O completion, synchronization, or a resource to become available.
   - It cannot continue execution until the event it is waiting for happens.

5. **Terminated (Exit)**:
   - The process has finished execution, either successfully or due to an error.
   - The process control block is deallocated, and the process is removed from the system.

---

### **Process State Transitions**
The process moves between various states based on the scheduling decisions made by the OS. Here's a general overview of the transitions between these states:

1. **New → Ready**:
   - The process is created and moved to the ready state when it is prepared to be executed.

2. **Ready → Running**:
   - The process is scheduled to run by the CPU scheduler, and it is moved to the running state.

3. **Running → Waiting**:
   - A process moves to the waiting state when it cannot continue due to an I/O operation or other blocking condition.

4. **Running → Ready**:
   - A running process may be preempted (due to a higher-priority process or time slice expiration) and moved back to the ready state.

5. **Waiting → Ready**:
   - Once the event or condition the process was waiting for is fulfilled (e.g., I/O completes), it moves back to the ready state.

6. **Running → Terminated**:
   - The process completes its task and terminates, either successfully or because of an error.

---

### **Process Control Block (PCB)**
The **Process Control Block (PCB)** is a data structure maintained by the OS to store information about each process. It holds critical information required to manage and track the execution of processes.

#### **Components of a PCB:**
1. **Process ID (PID)**:
   - A unique identifier assigned to the process.

2. **Process State**:
   - The current state of the process (New, Ready, Running, Waiting, Terminated).

3. **Program Counter (PC)**:
   - The address of the next instruction to be executed in the process.

4. **CPU Registers**:
   - Values stored in CPU registers, including general-purpose registers, stack pointers, and status registers.

5. **Memory Management Information**:
   - Information related to the process’s memory allocation, such as base and limit registers, page tables, etc.

6. **Scheduling Information**:
   - Information used by the scheduler, such as priority, scheduling queue pointers, and CPU burst time.

7. **I/O Status Information**:
   - Information about I/O devices assigned to the process and their status.

8. **Accounting Information**:
   - Data related to the process’s resource usage, such as CPU time used, process execution time, etc.

9. **Pointer to Parent and Child Processes**:
   - Links to the parent and child processes in case of hierarchical relationships.

---

### **Context Switching**
**Context switching** is the process of saving the state of the currently running process and restoring the state of the next process to be executed. This is necessary for multitasking operating systems, where multiple processes share CPU time.

#### **Steps Involved in Context Switching:**
1. **Save the State of the Current Process**:
   - The OS saves the values of the CPU registers, program counter, and other context information in the current process’s PCB.

2. **Select the Next Process to Run**:
   - The scheduler picks the next process to execute from the ready queue.

3. **Restore the State of the Next Process**:
   - The OS loads the saved state (program counter, registers, etc.) from the next process’s PCB.

4. **Switch the CPU to the New Process**:
   - The CPU begins executing the next process based on the restored state.

#### **Importance of Context Switching:**
- **Multitasking**: Allows the OS to switch between processes quickly, providing the illusion of concurrent execution.
- **Fairness**: Ensures that all processes get a fair share of CPU time.
- **Overhead**: Context switching comes with some overhead in terms of time and resources.

---

### **Summary of Process Lifecycle**
1. **Creation (New State):** Process is created.
2. **Execution (Ready and Running States):** Process waits for CPU or runs when scheduled.
3. **Waiting for Resources (Blocked State):** Process waits for I/O or other resources.
4. **Termination (Exit State):** Process finishes execution or is terminated by the OS.

---

This is a comprehensive explanation of **process management** in an operating system, covering key aspects like states, PCB, context switching, and process relationships.

### **Thread: Definition**

A **thread** is the smallest unit of execution within a process. A process can have multiple threads, and each thread shares the process's resources, including memory and open files, but has its own execution stack and program counter. Threads enable **concurrent execution** within a single process, allowing multiple operations to happen at the same time.

Threads are sometimes referred to as "lightweight processes" because they are more efficient than traditional processes in terms of resource usage. In multi-core systems, multiple threads can run in parallel, improving performance.

---

### **Various States of a Thread**

Threads, like processes, go through different states during their lifecycle. The typical states of a thread are:

1. **New (Born)**:
   - The thread has been created but has not yet started execution.
   - It is in the initial state, waiting for the scheduler to start it.

2. **Runnable**:
   - The thread is ready to run and is in the queue, waiting for the CPU to be assigned to it.
   - A thread can move to this state from the **new** state or after being in the **blocked** state once the blocking condition is resolved.

3. **Running**:
   - The thread is currently being executed by the CPU.
   - The thread moves to this state when it gets CPU time.

4. **Blocked (Waiting)**:
   - The thread cannot proceed because it is waiting for some resource or event (e.g., waiting for I/O, data, or synchronization with another thread).
   - A thread may move to this state if it calls a blocking system call or waits for another thread.

5. **Terminated (Dead)**:
   - The thread has finished its execution and is no longer in the system.
   - This happens after the thread completes its task or is terminated by the OS due to some error or external event.

---

### **Benefits of Threads**

1. **Improved Performance through Parallelism**:
   - With threads, multiple tasks within a process can run simultaneously, especially on multi-core processors, improving the overall performance of the application.

2. **Efficient Resource Sharing**:
   - Threads within the same process share the same memory and resources, making communication between them faster and more efficient compared to inter-process communication (IPC).

3. **Better Responsiveness**:
   - Threads enable applications to remain responsive by performing background tasks (like file I/O or network communication) while the main thread continues processing user inputs.

4. **Lower Overhead**:
   - Creating and managing threads is generally less resource-intensive than creating new processes because threads share resources and memory within the same process.

5. **Scalability**:
   - Threads allow an application to scale efficiently on multi-core processors by enabling concurrent execution of different threads.

---

### **Types of Threads**

1. **User Threads**:
   - **User-level threads** are managed entirely by the user-level thread library (e.g., `pthread` in POSIX systems). The operating system is unaware of user threads, and all scheduling and management are done by the thread library.
   - Advantages: Lower overhead, faster thread creation and management, but the OS cannot optimize CPU usage across multiple threads since it sees only one process.

2. **Kernel Threads**:
   - **Kernel-level threads** are managed by the operating system kernel. The kernel schedules these threads and handles all aspects of their execution and management.
   - Advantages: The OS can schedule threads across multiple processors, improving performance. However, kernel threads incur higher overhead due to the involvement of the kernel in their management.

3. **Hybrid Threads**:
   - **Hybrid threads** combine the advantages of both user and kernel threads. They allow user threads to be mapped to kernel threads in a way that the OS schedules them, but the management of threads is done partly by the kernel and partly by the user-level thread library.

---

### **Concept of Multithreading**

**Multithreading** is the ability of a CPU (or a single core in a multi-core processor) to provide multiple threads of execution within a single process. It is a way to achieve concurrent execution of tasks within a program.

Multithreading is important for applications that need to perform many tasks simultaneously, such as web servers, video games, database servers, and applications involving I/O-bound tasks.

#### **Key Concepts of Multithreading**:
1. **Thread Pooling**:
   - A pool of worker threads is created to handle tasks. When a new task arrives, a thread from the pool is used to handle it. Once the task is finished, the thread is returned to the pool.
   - This reduces the overhead of creating and destroying threads for each task.

2. **Concurrency**:
   - Multithreading allows multiple threads to be executed in an interleaved manner, improving application performance by allowing tasks to run concurrently.

3. **Parallelism**:
   - With multi-core processors, multithreading allows true parallel execution, where different threads can run simultaneously on different cores, further boosting performance.

4. **Synchronization**:
   - When multiple threads are accessing shared resources, synchronization mechanisms like **mutexes**, **semaphores**, and **locks** are used to avoid race conditions and ensure data integrity.

5. **Thread Synchronization**:
   - Proper synchronization mechanisms are essential to avoid conflicts, such as deadlocks or race conditions, that arise when threads interact with shared resources.
   - Thread synchronization ensures that only one thread can access a critical section of code at a time.

---

### **Thread Scheduling and Context Switching in Multithreading**
- **Thread Scheduling**:
  - Just like processes, threads need to be scheduled for execution. This is typically done by a **thread scheduler**, which decides which thread to execute next based on factors like priority, CPU time, and fairness.
  
- **Context Switching**:
  - The operating system performs a context switch to save the state of one thread and load the state of another. This is necessary when switching from one thread to another, either within the same process or across different processes.

---

### **Multithreading Models**
There are several models of how threads are mapped to processes and cores:

1. **Many-to-One Model**:
   - Multiple user threads are mapped to a single kernel thread. This model is simple but inefficient because the kernel cannot schedule multiple threads to run in parallel.

2. **One-to-One Model**:
   - Each user thread is mapped to a kernel thread. This model allows better parallelism but incurs higher overhead due to the kernel managing a large number of threads.

3. **Many-to-Many Model**:
   - Many user threads are mapped to many kernel threads, allowing better scalability and parallelism while minimizing the overhead.

4. **Two-Level Model**:
   - A hybrid of the many-to-many and one-to-one models. It allows user-level threads to be mapped to kernel threads in a flexible manner, optimizing for both parallelism and overhead.

---

### **Summary**
- **Threads** are the smallest units of execution in an operating system, and they enable **concurrent execution** within a single process.
- **States of a thread** include new, runnable, running, blocked, and terminated.
- The **benefits of threads** include efficient resource sharing, parallelism, better responsiveness, and lower overhead.
- **Types of threads** include user threads, kernel threads, and hybrid threads.
- **Multithreading** enhances performance by allowing multiple threads to execute concurrently or in parallel, especially on multi-core systems. It is essential for modern applications that require concurrent execution.

### **Process Scheduling**

**Process scheduling** is the method by which an operating system determines which process should be executed by the CPU at any given time. It plays a crucial role in managing processes and ensuring efficient CPU utilization.

The goal of process scheduling is to ensure that the system is efficient, responsive, and fair to all processes. The scheduler must balance competing processes that require CPU time in a manner that maximizes performance and minimizes wait times.

---

### **Foundations of Scheduling**

Process scheduling relies on the following basic principles:

1. **Context Switching**:
   - The CPU switches from one process to another. During this switch, the state of the current process is saved and the state of the next process is loaded.
   
2. **Dispatcher**:
   - The dispatcher is the component responsible for assigning the CPU to a process selected by the scheduler. The dispatcher performs the context switch and hands control over to the chosen process.

3. **Queuing**:
   - Processes in the system are usually placed in different queues depending on their state. For example:
     - **Ready Queue**: Processes that are ready to execute but waiting for CPU time.
     - **Waiting/Blocked Queue**: Processes that are waiting for some event or I/O operation.
     - **New Queue**: Processes that are in the creation stage.
   
4. **Preemption vs. Non-preemption**:
   - **Preemptive Scheduling**: The operating system can interrupt a running process to assign CPU time to another process (usually in a time-sharing system).
   - **Non-preemptive Scheduling**: Once a process starts executing, it runs to completion unless it voluntarily releases the CPU.

---

### **Scheduling Objectives**

The primary objectives of process scheduling are:

1. **Maximize CPU Utilization**:
   - Ensuring that the CPU is in use as much as possible and not idle.
   
2. **Fairness**:
   - Ensuring that no single process monopolizes the CPU for too long, and that each process gets a fair share of the CPU time.
   
3. **Minimize Response Time**:
   - Ensuring that interactive applications respond to the user’s input as quickly as possible.

4. **Maximize Throughput**:
   - Ensuring that the system executes the maximum number of processes in a given period of time.

5. **Minimize Waiting Time and Turnaround Time**:
   - Ensuring that processes spend minimal time waiting for resources and complete execution quickly.

---

### **Types of Schedulers**

Schedulers are responsible for managing process execution and are classified into the following types:

1. **Long-Term Scheduler (Job Scheduler)**:
   - Decides which processes should be moved into the ready queue. It controls the degree of multiprogramming (the number of processes in memory).
   - In some systems, it is inactive when the number of processes in memory is sufficient.

2. **Short-Term Scheduler (CPU Scheduler)**:
   - Decides which of the ready processes should be allocated CPU time next.
   - This scheduler is very active, running frequently to ensure fair allocation of CPU time to processes.

3. **Medium-Term Scheduler**:
   - It handles swapping processes in and out of memory. For systems that use **virtual memory**, the medium-term scheduler decides when to swap processes between main memory and secondary storage (disk).
   - This scheduler helps in controlling the number of processes in memory.


![alt text](../assets/image%20copy%206.png)
---

### **Scheduling Criteria**

The operating system uses several metrics to evaluate the performance of scheduling algorithms:

1. **CPU Utilization**:
   - The goal is to maximize CPU usage. In an ideal scenario, CPU utilization should be kept close to 100%. However, in practice, the goal is to avoid both high CPU idle times and high overload conditions.
   
2. **Throughput**:
   - The number of processes completed within a certain time period. Higher throughput indicates that more processes are being executed, leading to better system performance.

3. **Turnaround Time**:
   - **Turnaround Time** is the total time a process takes from the submission to its completion. It includes:
     - **Waiting Time**: Time spent waiting in the ready queue.
     - **Execution Time**: Time spent actively running on the CPU.
     - **I/O Time**: Time spent waiting for I/O operations.
   
   **Formula**: 
   \[
   \text{Turnaround Time} = \text{Completion Time} - \text{Arrival Time}
   \]

4. **Waiting Time**:
   - **Waiting Time** is the total time a process spends in the ready queue waiting for CPU time. It is a key factor in determining how efficient the scheduling algorithm is.
   
   **Formula**: 
   \[
   \text{Waiting Time} = \text{Turnaround Time} - \text{Burst Time}
   \]
   where **Burst Time** is the time required by the process for execution.

5. **Response Time**:
   - **Response Time** is the time from when a request is made (e.g., user input in an interactive application) to when the first response is produced. It is crucial for interactive systems, as users expect quick feedback.
   
   **Formula**: 
   \[
   \text{Response Time} = \text{First Response Time} - \text{Arrival Time}
   \]

---

### **Process Scheduling Algorithms**

The efficiency of a scheduling algorithm can be judged based on how well it minimizes these criteria. Below are common scheduling algorithms:

1. **First-Come, First-Served (FCFS)**:
   - Processes are executed in the order they arrive in the ready queue.
   - It is simple but can lead to high average waiting time, especially if long processes arrive first (convoy effect).

2. **Shortest Job First (SJF)**:
   - The process with the shortest burst time (execution time) is executed first.
   - SJF minimizes average waiting time but requires knowing the burst time in advance, which is often not possible.

3. **Round Robin (RR)**:
   - Each process gets a fixed time slice (quantum). When a process's time slice expires, it is moved to the end of the ready queue.
   - This is fair and provides better response time but can increase turnaround time if the time quantum is too large or too small.

4. **Priority Scheduling**:
   - Each process is assigned a priority, and the process with the highest priority is executed first.
   - This can lead to starvation (low-priority processes may never get CPU time) unless aging is implemented.

5. **Multilevel Queue Scheduling**:
   - Processes are divided into different queues based on priorities or characteristics (e.g., interactive vs. batch processes). Each queue has its own scheduling algorithm, and processes can be moved between queues based on their behavior.

6. **Multilevel Feedback Queue Scheduling**:
   - This is an enhancement to the multilevel queue, where processes can move between queues based on their behavior (e.g., if a process uses too much CPU, it moves to a lower-priority queue).

---

### **Summary**

Process scheduling is an essential part of the operating system's task management system. It involves deciding which process to execute next, based on various scheduling objectives such as CPU utilization, throughput, waiting time, response time, and turnaround time. The system uses various scheduling algorithms to achieve these goals, with different trade-offs in fairness, performance, and efficiency. Proper scheduling helps ensure that all processes get a fair share of CPU time, leading to efficient system operation.

### **Scheduling Algorithms**

Scheduling algorithms are crucial in determining the order in which processes get executed by the CPU. These algorithms are generally divided into two categories based on whether they allow preemption or not.

---

### **1. Pre-emptive vs. Non-Pre-emptive Scheduling**

- **Pre-emptive Scheduling**:
  - In pre-emptive scheduling, a running process can be interrupted by the operating system in order to give CPU time to another process. The current process can be paused and resumed later. This type of scheduling allows better responsiveness to high-priority processes.
  - Preemption happens based on time slicing (e.g., Round Robin) or priority levels.
  
- **Non-Pre-emptive Scheduling**:
  - In non-pre-emptive scheduling, once a process starts its execution, it runs to completion without being interrupted. The operating system only gets control when the process voluntarily releases the CPU (e.g., after completing its execution or waiting for I/O).
  - Non-preemptive scheduling can lead to longer waiting times if a long-running process is ahead in the queue.

---

### **2. FCFS (First-Come, First-Served)**

- **Type**: Non-Pre-emptive
- **Description**: 
  - FCFS is one of the simplest scheduling algorithms. In this approach, the process that arrives first is executed first. It is a FIFO (First-In-First-Out) scheduling method.
  
- **Advantages**:
  - Simple and easy to implement.
  - Fair for all processes as they are executed in the order they arrive.
  
- **Disadvantages**:
  - Can cause the **convoy effect**: Long processes can delay short processes, leading to poor performance, especially if there is a mix of long and short processes.
  - High **average waiting time** if long processes are ahead of short ones.

- **Example**:
  - If Process A arrives at time 0 and runs for 5 units, and Process B arrives at time 2 and runs for 3 units, Process A will complete first, leading to a delay for Process B.

- **Waiting Time**: \( W(T) = \text{Turnaround Time} - \text{Burst Time} \)

---

### **3. SJF (Shortest Job First)**

- **Type**: Non-Pre-emptive
- **Description**:
  - The process with the shortest burst time (execution time) is given priority and executed first. It minimizes the average waiting time, but it requires knowledge of the burst time of each process, which is often not available in real-time.
  
- **Advantages**:
  - Minimizes **average waiting time**.
  - Efficient when there is a mix of long and short processes.
  
- **Disadvantages**:
  - **Starvation**: Long processes can suffer if short processes keep arriving.
  - **Burst time estimation**: The system needs to predict the burst time, which is challenging.

- **Example**:
  - Consider processes with burst times of 5, 2, and 8 units. The process with a burst time of 2 will be executed first, followed by the one with 5, and lastly the one with 8.

- **Waiting Time**: \( W(T) = \text{Turnaround Time} - \text{Burst Time} \)

---

### **4. Round Robin (RR)**

- **Type**: Pre-emptive
- **Description**:
  - Round Robin is one of the most widely used preemptive scheduling algorithms. In RR, each process gets a small unit of time (time quantum) to execute. Once a process’s time quantum expires, the next process in the queue is given the CPU, and the previous one is placed at the end of the ready queue.
  - This approach is fair and ensures that every process gets an equal share of the CPU time.

- **Advantages**:
  - Fair for all processes and ensures responsiveness.
  - Reduces waiting time for interactive processes.
  
- **Disadvantages**:
  - The performance heavily depends on the time quantum. If it's too long, RR behaves like FCFS; if too short, overheads increase due to frequent context switching.
  - **High turnaround time** for processes that need less than the time quantum.

- **Example**:
  - For 3 processes with burst times of 10, 5, and 8 units, and a time quantum of 4 units, the processes will get executed in a round-robin fashion until all processes are complete.

- **Waiting Time**: \( W(T) = \text{Turnaround Time} - \text{Burst Time} \)

---

### **Multiprocessor Scheduling**

In a multiprocessor system, there are multiple CPUs, and processes can be executed concurrently on different processors. The challenge is to efficiently distribute processes among the available CPUs.

#### **Types of Multiprocessor Scheduling**:

1. **Asymmetric Multiprocessing**:
   - Only one CPU (the master processor) controls the system and the other CPUs (slave processors) handle specific tasks as assigned by the master processor.
   - The master processor schedules and manages all processes, while the slave processors handle the execution.

2. **Symmetric Multiprocessing (SMP)**:
   - All CPUs are equal and can execute processes independently. The operating system’s scheduler distributes processes across CPUs to balance load.
   - SMP allows better scalability and performance but requires careful load balancing.

---

### **Real-Time Scheduling**

Real-time systems require that processes complete their execution within a specific time frame. The operating system must ensure that high-priority tasks are executed on time, often with strict deadlines. Real-time scheduling is crucial in systems like embedded systems, robotics, and multimedia applications.

---

### **1. Rate Monotonic Scheduling (RM)**

- **Type**: Pre-emptive
- **Description**:
  - Rate Monotonic Scheduling (RM) assigns priorities to tasks based on their periodicity. The task with the shortest period (highest frequency) gets the highest priority.
  - RM is optimal for fixed-priority scheduling when the tasks are periodic and independent.

- **Advantages**:
  - Simple and works well for periodic tasks.
  - Easy to implement and widely used for real-time systems.
  
- **Disadvantages**:
  - Not suitable for tasks with varying periods or irregular execution times.

- **Example**:
  - If Task A has a period of 5ms, Task B has a period of 10ms, and Task C has a period of 15ms, Task A will have the highest priority, followed by Task B, and then Task C.

- **Schedulability Condition**:
  - \( \sum \left(\frac{C_i}{T_i}\right) \leq n(2^{1/n} - 1) \), where \(C_i\) is the execution time of task \(i\), and \(T_i\) is the period.

---

### **2. Earliest Deadline First (EDF)**

- **Type**: Pre-emptive
- **Description**:
  - EDF assigns priorities based on the absolute deadline of each task. The task with the closest deadline has the highest priority. EDF is optimal for dynamic priority scheduling, where tasks may have different deadlines at different points in time.
  - Unlike RM, EDF works well with a mix of periodic and aperiodic tasks.

- **Advantages**:
  - EDF can schedule a broader variety of tasks, including both periodic and aperiodic ones.
  - Provides higher utilization of CPU resources compared to RM.

- **Disadvantages**:
  - EDF requires more complex management and calculation than RM.
  - The system may become overloaded if tasks are not schedulable.

- **Example**:
  - If Task A has a deadline of 8ms, Task B has a deadline of 12ms, and Task C has a deadline of 10ms, Task A would have the highest priority, then Task C, and Task B.

- **Schedulability Condition**:
  - The system is schedulable if the total CPU utilization is less than or equal to 1: 
  \[
  \sum \left(\frac{C_i}{T_i}\right) \leq 1
  \]
  where \(C_i\) is the execution time of task \(i\), and \(T_i\) is the period.

---

### **Summary**

- **Pre-emptive Scheduling** allows interruptions to processes, ensuring responsiveness and fairness but introducing context-switching overhead.
- **Non-Pre-emptive Scheduling** guarantees processes run to completion without interruption, but may cause delays for other processes.
- **FCFS** and **SJF** are simple but suffer from long waiting times and potential starvation. **Round Robin** ensures fairness with time slices, balancing system responsiveness.
- **Multiprocessor Scheduling** optimizes how tasks are distributed across multiple CPUs, aiming to balance loads.
- **Real-time Scheduling** is crucial for tasks with deadlines, with algorithms like **Rate Monotonic** and **Earliest Deadline First** ensuring tasks are completed on time.

These algorithms aim to optimize system performance while managing multiple processes effectively in diverse computing environments.