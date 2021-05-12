## Identifying Information:
1. Name: Ariel Gutierrez
2. Student ID: 2318163
3. Email: arigutierrez@chapman.edu
4. Class: CPSC 380-01
5. Assignment: Project 4

## Application Purpose
Rate Monotonic Scheduler (RMS): Build a Rate Monotonic Scheduler using four threads, each representing a rate or 1/period


## Source Files
1. main.cpp

## Known Errors
1. Nothing happens to T3 and T4 when T2 overruns.
2. Sometimes T1 will overrun when it should not.

## References
1. Passing a string as a parameter in pthreads - https://stackoverflow.com/questions/52833368/passing-a-string-to-pthread-function
2. Multithreading in C++ - https://www.tutorialspoint.com/cplusplus/cpp_multithreading.html
3. pthread libraries - https://www.cs.cmu.edu/afs/cs/academic/class/15492-f07/www/pthreads.html#BASICS
4. C++ Tutorial: Multi-Threaded Programming - https://www.bogotobogo.com/cplusplus/multithreading_pthread.php
5. sem_wait operation - https://pubs.opengroup.org/onlinepubs/7908799/xsh/sem_wait.html
6. pthread_attr_setaffinity_np() - https://man7.org/linux/man-pages/man3/pthread_attr_setaffinity_np.3.html
7. Create a thread with priority - https://docs.oracle.com/cd/E19455-01/806-5257/attrib-16/index.html
8. Mutex locks - https://www.geeksforgeeks.org/mutex-lock-for-linux-thread-synchronization/

## Instructions
1. Clone repository to computer
2. Start and attach compsci docker container
3. Go to the directory/repository you cloned on computer
4. Compile program: make all
5. Run program: ./proj4.out [number of doWork T2 iterations]
6. Clear .out files when done: make realclean
