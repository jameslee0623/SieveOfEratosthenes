//
//  main.c
//  SieveOfEratosthenes
//
//  Created by James Li on 2/8/14.
//

#include <stdio.h> 
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <stdbool.h>

int main(int argc, char **argv) {
    unsigned long int top_value = 1000000000; // N, the value you want to find primes up to. change me.
    
    unsigned long int count     = top_value - 1; // pi(N), number of primes up to N.
    unsigned long int i, prime, multiple;
    unsigned long int AddCount= 0; // A(N)
    unsigned long int MulCount= 0; // M(N)
    bool              *array    = calloc(top_value + 1, sizeof(bool));
    clock_t           t;
    
    // mark each bool as potentially prime
    for (i=2; i <= top_value; ++i)
        array[i] = 1;
    t = clock(); // strat timeing
    // for each starting prime, mark its every multiple as non-prime
    for (prime = 2; prime <= sqrt(top_value); prime++){
        AddCount++;
        if (array[prime]){
            MulCount++;
            for (multiple = prime*prime; multiple <= top_value; multiple += prime){
                AddCount++;
                if (array[multiple]) {
                    array[multiple] = 0;
                    --count;
                }
            }
            AddCount--; // the first time is multiplicative.
        }
    }
    AddCount--; // the first time is assing 2.
    t=clock()-t; //end of timeing
    // Now that we have marked all multiples of primes as non-prime, print
    //the remaining numbers that fell through the sieve, and are thus prime
    /*
    for (i=2; i <= top_value; ++i)
    {
        if (array[i])
            printf("%d ", i);
    }*/
    printf("\n\n%lu primes up to %lu found.\n", count, top_value);
    printf("Beta: %f \n", log(top_value)*count/top_value);
    printf("The number of addition operations: %lu \n", AddCount);
    printf("The number of multiplication operations: %lu \n", MulCount);
    printf ("It took me %d clicks (%f seconds).\n", (int)t, ((float)t)/CLOCKS_PER_SEC);
    exit(0);
}

