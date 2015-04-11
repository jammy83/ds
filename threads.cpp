//
//  threads.cpp
//  
//
//  Created by Janani Natarajan on 4/11/15.
//
//

#include <stdio.h>



void perform(void* arg) {
    vector<int> jobs = (vector<int>)*arg;
    for (vector<int>::iterator itr = jobs.begin; itr != jobs.end(); itr++) {
        if (ping(*itr)) {
            cout << "Pinged " << *itr << "successfully" << endl;
        } else {
            cout << "Failed to ping " << *itr << endl;
        }
    }
    pthread_exit(NULL);
}

//@param arr - array of integers to be evaluated for reachability
//@param size - no. of elements in the array
#define NUM_THREADS 500 // to be sized based on OS and the job
void evaluateIPAddresses(int* arr, int size)
{
    vector<int>* jobs = new vector<int>[NUM_THREADS];
    if (jobs == NULL) { return; }
    for (int index = 0; index < size; index++) {
        jobs[index%NUM_THREADS].push_back(arr[index]);
    }
    
    for (int i = 0; i < NUM_THREADS; i++) {
        int ret = pthread_create(&threads[i], NULL, perform, (void*)&jobs[i]);
        if (ret) {
            cout << "pthread creation failed for thread id " << i << endl;
            return;
        }
    }
    
    for int i = 0; i < NUM_THREADS; i++) {
        int ret = pthread_join(&threads[i], NULL);
    }
}
