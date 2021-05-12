
// Full name: Ariel Gutierrez
// Student ID: 2318163
// Chapman email: arigutierrez@chapman.edu
// Course number and section: CPSC 380-01
// Assignment number: Project 4

// Rate Monotonic Scheduler (RMS): Build a Rate Monotonic Scheduler using four
// threads, each representing a rate or 1/period.

#include <iostream>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h> // usleep
using namespace std;

// global variables
sem_t sem1, sem2, sem3, sem4, semSched;
pthread_mutex_t mutex1, mutex2, mutex3, mutex4;
unsigned int t1Count = 0, t2Count = 0, t3Count = 0, t4Count = 0, t4Count1=0; // times each thread ran
unsigned int t1overrun = 0, t2overrun = 0, t3overrun = 0, t4overrun = 0; // times overrun occured
int THREAD2ITER = 200;
bool t1done = false, t2done = false, t3done = false, t4done = false; // tells if thread is done


void doWork(){
  //In doWork function declare you matrix to a 10x10 double
  double** myMatrix;
  myMatrix = new double*[10];
  for(int i = 0; i < 10; ++i){
    myMatrix[i] = new double[10];
  }

  //Multiply the content of each cell with itself :p
  int columnNum[10] = {0, 5, 1, 6, 2, 7, 3, 8, 4, 9};
  for(int i = 0; i < 10; ++i){
    for(int j = 0; j < 10; ++j){
      myMatrix[j][columnNum[i]] =
        myMatrix[j][columnNum[i]]*myMatrix[j][columnNum[i]];
    }
  }
  for(int i = 0; i < 1; ++i){
    delete [] myMatrix[i];
  }
  delete [] myMatrix;
}

// Given the thread, priority, and number of core, function sets the attributes
// and processor affinity for a thread and then creates the thread
pthread_attr_t createThread(pthread_t thread, int priority, int coreID){
  pthread_attr_t attr;
  pthread_attr_init(&attr);

  // get existing scheduling paramater and set scheduling policy
  sched_param param;
  pthread_attr_getschedparam(&attr, &param);
  pthread_attr_setschedpolicy(&attr, SCHED_FIFO);
  // set the priority
  param.sched_priority = priority;

  // set the new scheduling parameter
  int s = pthread_attr_setschedparam(&attr, &param);
  if(s == EINVAL)
    cout << "Error setting priority" << endl;

  // Set CPU affinity mask to only include coreID
  cpu_set_t cpuset;
  CPU_ZERO(&cpuset);
  CPU_SET(coreID, &cpuset);

  s = pthread_attr_setaffinity_np(&attr, sizeof(cpu_set_t), &cpuset);
  if(s != 0)
    cout << "Error setting processor affinity" << endl;

  return attr;
}

// timer that doesn't really work
void timer(unsigned int ms){
  usleep(ms*1000);
  sem_post(&semSched);
}

void* thread1(void* arg){
  for(int j = 0; j < 160; ++j){
    sem_wait(&sem1);
    pthread_mutex_lock(&mutex1);
    t1done = false;
    pthread_mutex_unlock(&mutex1);
    for(int i = 0; i < 100; ++i){
      doWork();
    }
    pthread_mutex_lock(&mutex1);
    t1done = true;
    pthread_mutex_unlock(&mutex1);
  }
  pthread_exit(NULL);
}

void* thread2(void* arg){
  for(int j = 0; j < 80; ++j){
    sem_wait(&sem2);
    pthread_mutex_lock(&mutex2);
    t2done = false;
    pthread_mutex_unlock(&mutex2);
    for(int i = 0; i < THREAD2ITER; ++i){
      doWork();
    }
    pthread_mutex_lock(&mutex2);
    t2done = true;
    pthread_mutex_unlock(&mutex2);
  }
  pthread_exit(NULL);
}

void* thread3(void* arg){
  for(int j = 0; j < 40; ++j){
    sem_wait(&sem3);
    pthread_mutex_lock(&mutex3);
    t3done = false;
    pthread_mutex_unlock(&mutex3);
    for(int i = 0; i < 400; ++i){
      doWork();
    }
    pthread_mutex_lock(&mutex3);
    t3done = true;
    pthread_mutex_unlock(&mutex3);
  }
  pthread_exit(NULL);
}

void* thread4(void* arg){
  for(int j = 0; j < 10; ++j){
    sem_wait(&sem4);
    pthread_mutex_lock(&mutex4);
    t4done = false;
    pthread_mutex_unlock(&mutex4);
    for(int i = 0; i < 1600; ++i){
      doWork();
    }
    ++t4Count1;
    pthread_mutex_lock(&mutex4);
    t4done = true;
    pthread_mutex_unlock(&mutex4);
  }
  pthread_exit(NULL);
}

// scheduler thread that schedules the 4 threads
void* scheduler(void* arg){

  for(int i = 0; i < 160; i++){
    sem_wait(&semSched);

    if(i % 1 == 0){
      pthread_mutex_lock(&mutex1);
      if(!t1done && i!=0){
        ++t1overrun;
      }
      pthread_mutex_unlock(&mutex1);
      sem_post(&sem1);
      ++t1Count;
    }

    if(i % 2 == 0){
      pthread_mutex_lock(&mutex2);
      if(!t2done && i!=0){
        ++t2overrun;
      }
      pthread_mutex_unlock(&mutex2);
      sem_post(&sem2);
      ++t2Count;
    }

    if(i % 4 == 0){
      pthread_mutex_lock(&mutex3);
      if(!t3done && i!=0){
        ++t3overrun;
      }
      pthread_mutex_unlock(&mutex3);
      sem_post(&sem3);
      ++t3Count;
    }

    if(i % 16 == 0){
      pthread_mutex_lock(&mutex4);
      if(!t4done && i!=0){
        ++t4overrun;
      }
      pthread_mutex_unlock(&mutex4);
      sem_post(&sem4);
      ++t4Count;
    }
    timer(10);
  }

  pthread_exit(NULL);
}

void printOutput(){
  cout << " Thread | # of runs | # of overruns" << endl;
  cout << "------------------------------------" << endl;
  cout << "   T1   |   " << t1Count << "     |      " << t1overrun << endl;
  cout << "   T2   |    " << t2Count << "     |      " << t2overrun << endl;
  cout << "   T3   |    " << t3Count << "     |      " << t3overrun << endl;
  cout << "   T4   |    " << t4Count1 << "     |      " << t4overrun << endl;
}

int main(int argc, char** argv){
  // if there is a command line argument use it, else use default of 200
  if(argc == 2){
    THREAD2ITER = stoi(argv[1]);
  }

  // initialize the semaphores
  sem_init(&sem1, 0, 0);
  sem_init(&sem2, 0, 0);
  sem_init(&sem3, 0, 0);
  sem_init(&sem4, 0, 0);
  sem_init(&semSched, 0, 1);

  // create and initialize threads with attributes
  pthread_t t1, t2, t3, t4, sched;
  pthread_attr_t attr1 = createThread(t1, 80, 0);
  pthread_attr_t attr2 = createThread(t2, 70, 0);
  pthread_attr_t attr3 = createThread(t3, 20, 0);
  pthread_attr_t attr4 = createThread(t4, 1, 0);
  pthread_attr_t attrS = createThread(sched, 90, 0);

  pthread_create(&t1, &attr1, thread1, NULL);
  pthread_create(&t2, &attr2, thread2, NULL);
  pthread_create(&t3, &attr3, thread3, NULL);
  pthread_create(&t4, &attr4, thread4, NULL);
  pthread_create(&sched, &attrS, scheduler, NULL);

  //main thread waits for child threads
  pthread_join(sched, NULL);
  pthread_join(t1, NULL);
  pthread_join(t2, NULL);
  pthread_join(t3, NULL);
  pthread_join(t4, NULL);

  // done simulating so destroy the semaphores
  sem_destroy(&sem1);
  sem_destroy(&sem2);
  sem_destroy(&sem3);
  sem_destroy(&sem4);
  sem_destroy(&semSched);

  // destroy attributes
  pthread_attr_destroy(&attrS);
  pthread_attr_destroy(&attr1);
  pthread_attr_destroy(&attr2);
  pthread_attr_destroy(&attr3);
  pthread_attr_destroy(&attr4);

  printOutput();
  return 0;
}
