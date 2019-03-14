#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <time.h>
#include <sys/time.h>
#include "data2.h"

#define MICRO_SEC_IN_SEC 1000000

//global variable for the shared memory as it is used in multiple functions
void *shared_mem = (void *)0;
struct Matrix *SharedMatrix;

void WorkMyChildren(int child, int rows){
    //detemines the start and end row this child is in charge of
    int startRow = child * rows;
    int endRow = startRow + rows -1;
    //prints the rows in charge of, +1 to startRow and endRow since child start at 0
    printf("child process #%d, working with row(s): %d to %d\n", child +1, startRow+1, endRow+1);
    int value = 0; //keeping track of the summation
    
    //i tracks all the rows this incharge of, k tracks column and j is used for the calculations
    for(int i = startRow; i<=endRow ; i ++){
        for(int k = 0; k<MATRIX_SIZE; k++){
            for(int j = 0; j<MATRIX_SIZE; j++){
                value += SharedMatrix->M[i][j]*SharedMatrix->N[j][k];
            }
            SharedMatrix->Q[i][k]=value; // stored the calculated value in the correct location in matrix Q
            value = 0;
        }
        
    }
    gettimeofday(&SharedMatrix->end[child],NULL); //stored the time at the end of this proess
}
//Hardcoding in the matric i can also do SharedMatrix->M = {{},{},{},{}} but I did this because i found it easier to change values for testing
void CreateMatrix(){
    SharedMatrix->M[0][0] = 1;
    SharedMatrix->M[0][1] = 2;
    SharedMatrix->M[0][2] = 3;
    SharedMatrix->M[0][3] = 4;
    SharedMatrix->M[1][0] = 5;
    SharedMatrix->M[1][1] = 6;
    SharedMatrix->M[1][2] = 7;
    SharedMatrix->M[1][3] = 8;
    SharedMatrix->M[2][0] = 4;
    SharedMatrix->M[2][1] = 3;
    SharedMatrix->M[2][2] = 2;
    SharedMatrix->M[2][3] = 1;
    SharedMatrix->M[3][0] = 8;
    SharedMatrix->M[3][1] = 7;
    SharedMatrix->M[3][2] = 6;
    SharedMatrix->M[3][3] = 5;
    
    SharedMatrix->N[0][0] = 1;
    SharedMatrix->N[0][1] = 3;
    SharedMatrix->N[0][2] = 5;
    SharedMatrix->N[0][3] = 7;
    SharedMatrix->N[1][0] = 2;
    SharedMatrix->N[1][1] = 4;
    SharedMatrix->N[1][2] = 6;
    SharedMatrix->N[1][3] = 8;
    SharedMatrix->N[2][0] = 7;
    SharedMatrix->N[2][1] = 3;
    SharedMatrix->N[2][2] = 5;
    SharedMatrix->N[2][3] = 7;
    SharedMatrix->N[3][0] = 8;
    SharedMatrix->N[3][1] = 6;
    SharedMatrix->N[3][2] = 4;
    SharedMatrix->N[3][3] = 2;
    
}
//Function to print out the matrix, Param is int matrix[4][4] because that is how a matrix is defiled in data.h
void PrintMatrix(int matrix[4][4]){
    //iterates through all elements in the 2d array, and prints them out accodingly. Each column is seperated by a space and each row is seperated by \n
    for(int i = 0; i<4;i++){
        for(int k = 0; k<4;k++){
            printf("%d ",matrix[i][k]);
        }
        printf("\n");
    }
    printf("\n");
    
}



int main(int argc, char const *argv[])
{
    int n = atoi(argv[1]); //converts the input argument in the shell into an integer that is used to keep track of how many child processes need to be created
    int numOfWorkingRows = 4 / n; //number of rows managed by each child
    int shmid;
    shmid = shmget((key_t)1274, sizeof(struct Matrix), 0666| IPC_CREAT); //creating an id
    if (shmid == -1){
        fprintf(stderr, "smhget failed\n");
        exit(EXIT_FAILURE);
    }
    
    shared_mem = shmat(shmid, (void *) 0, 0); //attaing the malloc address space
    
    if(shared_mem == (void *) -1){
        fprintf(stderr, "shmat failed\n");
        exit(EXIT_FAILURE);
    }
    
    SharedMatrix = (struct Matrix *)shared_mem;
    CreateMatrix();
    
    gettimeofday(&SharedMatrix->start, NULL); //stores the time before the forking process starts
    
    pid_t pid[n];
    for(int i =0; i<n ; i++){
        if((pid[i] = fork())<0){ //if parent, fork. How it works: comes in the first time, in parent pid[i] > 0 so it continues to fork more children, in the child, since pid[1] < 0 false, check else if and in the child pid[1] = 0, so that block is executed
            fprintf(stderr, "fork failed\n");
            exit(EXIT_FAILURE);
        }else if(pid[i]==0){ //if in the child process, call WorkMyChildern and then exit. Need to exit so that the child doesnt call WorkMyChildren more than once
            WorkMyChildren(i,numOfWorkingRows);
            exit(0);
        }
    }
    
    
    
    //waits for all the child processes to compele and exit
    int status;
    int b = n;
    while (b > 0) {
        wait(&status);
        --b;
    }
    //prints out all the matrix
    printf("Matrix M:\n");
    PrintMatrix(SharedMatrix->M);
    printf("Matrix N:\n");
    PrintMatrix(SharedMatrix->N);
    printf("Matrix Q:\n");
    PrintMatrix(SharedMatrix->Q);
    
    //prints out how long it took each child to complete and the over duration of the matrix multiplication
    for(int i = 0; i<n ; i++){
        double elapsed = (SharedMatrix->end[i].tv_sec*MICRO_SEC_IN_SEC + SharedMatrix->end[i].tv_usec)-(SharedMatrix->start.tv_sec*MICRO_SEC_IN_SEC + SharedMatrix->start.tv_usec);
        printf("Child %d finished in %f micro seconds\n",i+1, elapsed);
        if(i == n-1){
            printf("Number of child proceses used is: %d.Total completion time is %f micro seconds\n", n, elapsed );
        }
    }
    
    if (shmdt(shared_mem)==-1){
        fprintf(stderr, "shmdt failed\n");
        exit(EXIT_FAILURE);
    }
    if(shmctl(shmid, IPC_RMID, 0)==-1){
        fprintf(stderr, "shmctl failed\n");
        exit(EXIT_FAILURE);
    }
    exit(EXIT_SUCCESS);
    
    return 0;
}
