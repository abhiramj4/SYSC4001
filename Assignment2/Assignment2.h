//
//  Assignment2.h
//  
//
//  Created by Abhiram Santhosh and Gabriele Sarwar.
//

#ifndef Assignment2_h
#define Assignment2_h

#include <stdio.h>

#endif /* Assignment2_h */

struct shared_use {
    int B[5]; //array of numbers to be shared
};
union semun {
    int val;
    struct semid_ds *buf;
    unsigned short *array;
};
