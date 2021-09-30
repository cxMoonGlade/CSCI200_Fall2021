//import the mutilple thred library.
#include <pthread.h>
#include <stdio.h>

using namespace std;

//find the greatest prime number under half million numbers.
#define N 500000

// there are 128 threads for the maximum.
#define MAX_THREADS 128

// initlize the array to record it is a prime number or not.
int prime_arr[N]={0};

// find the prime numbers out
void * findPrime(void *pointer){
    //int core for core number, flag for mark it is a prime number or not.
    // using marks insead of the actual number to save memory
    int core, flag;
    // set an integer for the number we are going to check.
    int i = (int)(long long int) pointer;
    // make sure i is in the range.
    while (i < N){
        // flag set to 0 means it is a prime number, 1 means it is not.
        flag = 0;
        // core number increasing.
        for (core = 2; core <=i/2; core ++){
            // i is not a prime number if it cannot zheng chu a number
            if (i % core ==0){
                // set floag to 1.
                flag = 1;
                // end this loop, threads doesn't change.
                break;
            }
        }
        // i is a prime number
        if (flag == 0 && ( i > 1)){
            prime_arr [i] = 1;
        }
        i += MAX_THREADS;
    }
};

int main()
{
    //creating the thread pool.
    pthread_t tid[MAX_THREADS]={{0}};
    //set a int number using for counting threads and all the numbers.
    int count=0;
    
    // creating threads
    for(count=0;count<MAX_THREADS;count++)
    {
        printf("\r\n CREATING THREADS %d",count);
        pthread_create(&tid[count],NULL,findPrime,(void*)count);
    }
    //just skip a line for looking better.
    printf("\n");
    //
    // adding threads into the pool.
    for(count=0;count<MAX_THREADS;count++)
    {
        pthread_join(tid[count],NULL);
    }
    // set a number to save the greatest one.
    int greatest = 0;

    //print all the prime numbers
    for(count=0;count<N;count++){
        if(prime_arr[count]==1){
            printf("%d ",count);
            if (greatest < count){
                greatest = count;
            }
        }
    }

    //print the greast one.
    printf("\nThe greatest prime number is %d", greatest);

    // end the program.
    return 0;
 }