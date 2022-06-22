# Rate Monotonic Scheduler (RMS)
C++ program that builds a Rate Monotonic Scheduler using four threads, each representing a rate or 1/period.


## Identifying Information
* Name: Ariel Gutierrez
* Student ID: 2318163
* Email: arigutierrez@chapman.edu
* Course: CPSC 380-01
* Assignment: Project 4

## Source Files
* main.cpp

## Known Errors
* Nothing happens to T3 and T4 when T2 overruns.
* Sometimes T1 will overrun when it should not.
* The Mutex Locks are not working as they should.

## References
* Passing a string as a parameter in pthreads - https://stackoverflow.com/questions/52833368/passing-a-string-to-pthread-function
* Multithreading in C++ - https://www.tutorialspoint.com/cplusplus/cpp_multithreading.html
* pthread libraries - https://www.cs.cmu.edu/afs/cs/academic/class/15492-f07/www/pthreads.html#BASICS
* C++ Tutorial: Multi-Threaded Programming - https://www.bogotobogo.com/cplusplus/multithreading_pthread.php
* sem_wait operation - https://pubs.opengroup.org/onlinepubs/7908799/xsh/sem_wait.html
* pthread_attr_setaffinity_np() - https://man7.org/linux/man-pages/man3/pthread_attr_setaffinity_np.3.html
* Create a thread with priority - https://docs.oracle.com/cd/E19455-01/806-5257/attrib-16/index.html
* Mutex locks - https://www.geeksforgeeks.org/mutex-lock-for-linux-thread-synchronization/

## Instructions
* Clone repository to computer
* Start and attach compsci docker container
* Go to the directory/repository you cloned on computer
* Compile program: make all
* Run program: ./proj4.out [number of doWork T2 iterations]
* Clear .out files when done: make realclean
