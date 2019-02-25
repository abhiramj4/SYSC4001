//
//  Assignment1Part2.c
//  
//
//  Created by Abhiram Santhosh on 2/24/19.
//

#include "Assignment1Part2.h"

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/shm.h>
#include <sys/types.h>



int main (){
    
    struct shared_matrix {
        
        int M[4][4]; //first matrix
        int N[4][4]; //second matrix
        int Q[4][4]; //result matrix
        
        
        int written; //a flag - if 0 means not written, else it has been written on
        
    };
    
    
    //part 1
    /**
     * Create a structure that saves the index I, J and K
     * when multiplying M[i,j] and N[j,k]
     *
     * Going to do it one row at a time, then pass on the shared structure
     * which will hold the i, j and k needed to access the next row from
     * each respective matrix
     **/
    
    int running = 1;
    void *shared_memory = (void *)0;
    struct shared_matrix *shared_stuff;
    int shmid;
    //pid_t pid;
    
    
    srand((unsigned int)getpid());
    
    shmid = shmget((key_t)1233, sizeof(struct shared_matrix), 0666 | IPC_CREAT);
    
    if (shmid == -1){
        fprintf(stderr, "shmget failed \n");
        exit(EXIT_FAILURE);
    }
    
    
    shared_memory = shmat(shmid, (void *)0, 0);
    
    if (shared_memory == (void *)-1){
        fprintf(stderr, "shmat failed \n");
        exit(EXIT_FAILURE);
    }
    
    printf("memory attached at %X\n",(int)shared_memory);
    
    //Solving FIRST ROW
    
    printf("Fork starting \n");
    
    
    //pid = fork();
    
    shared_stuff = (struct shared_matrix *)shared_memory;
    //switch
    
    
    
    //Init M
    shared_stuff->M[0][0] = 1;
    shared_stuff->M[1][0] = 5;
    shared_stuff->M[2][0] = 4;
    shared_stuff->M[3][0] = 8;
    shared_stuff->M[0][1] = 2;
    shared_stuff->M[1][1] = 6;
    shared_stuff->M[2][1] = 3;
    shared_stuff->M[3][1] = 7;
    shared_stuff->M[0][2] = 3;
    shared_stuff->M[1][2] = 7;
    shared_stuff->M[2][2] = 2;
    shared_stuff->M[3][2] = 6;
    shared_stuff->M[0][3] = 4;
    shared_stuff->M[1][3] = 8;
    shared_stuff->M[2][3] = 1;
    shared_stuff->M[3][3] = 5;
    
    //Init N
    shared_stuff->N[0][0] = 1;
    shared_stuff->N[1][0] = 2;
    shared_stuff->N[2][0] = 7;
    shared_stuff->N[3][0] = 8;
    shared_stuff->N[0][1] = 3;
    shared_stuff->N[1][1] = 4;
    shared_stuff->N[2][1] = 3;
    shared_stuff->N[3][1] = 6;
    shared_stuff->N[0][2] = 5;
    shared_stuff->N[1][2] = 6;
    shared_stuff->N[2][2] = 5;
    shared_stuff->N[3][2] = 4;
    shared_stuff->N[0][3] = 7;
    shared_stuff->N[1][3] = 8;
    shared_stuff->N[2][3] = 7;
    shared_stuff->N[3][3] = 2;
    
    printf("%d %d %d %d \n", shared_stuff->M[0][0], shared_stuff->M[1][0], shared_stuff->M[2][0], shared_stuff->M[3][0]);
    printf("%d %d %d %d \n", shared_stuff->M[0][1], shared_stuff->M[1][1], shared_stuff->M[2][1], shared_stuff->M[3][1]);
    printf("%d %d %d %d \n", shared_stuff->M[0][2], shared_stuff->M[1][2], shared_stuff->M[2][2], shared_stuff->M[3][2]);
    printf("%d %d %d %d \n", shared_stuff->M[0][3], shared_stuff->M[1][3], shared_stuff->M[2][3], shared_stuff->M[3][3]);
    
    printf("\n");
    
    printf("%d %d %d %d \n", shared_stuff->N[0][0], shared_stuff->N[1][0], shared_stuff->N[2][0], shared_stuff->N[3][0]);
    printf("%d %d %d %d \n", shared_stuff->N[0][1], shared_stuff->N[1][1], shared_stuff->N[2][1], shared_stuff->N[3][1]);
    printf("%d %d %d %d \n", shared_stuff->N[0][2], shared_stuff->N[1][2], shared_stuff->N[2][2], shared_stuff->N[3][2]);
    printf("%d %d %d %d \n", shared_stuff->N[0][3], shared_stuff->N[1][3], shared_stuff->N[2][3], shared_stuff->N[3][3]);
    
    int currentRow = 0;
    //loop and create 4
    for(int i = 0; i < 4; i++){
        
        pid_t pid = fork();
        
        switch(pid) {
                
            case -1:
                
                perror("Fork failed \n");
                exit(1);
            case 0:
                
                //child process
                //printf("%d \n", shared_stuff->M[1][1]);
                
                
                
                
                for (int k = 0; k < 4; k++){
                    shared_stuff->Q[currentRow][k] = 0;
                    
                    for(int j = 0;j < 4;j++){
                        shared_stuff->Q[currentRow][k] += shared_stuff->M[currentRow][j] * shared_stuff->N[j][k];
                    }
                }
                
                
                shared_stuff->written = 1;
                
                printf("%d %d %d %d \n", shared_stuff->Q[0][0], shared_stuff->Q[0][1], shared_stuff->Q[0][2], shared_stuff->Q[0][3]);
                
                break;
                
            default:
                
                printf("Reached Parent \n");
                
                while(running) {
                    
                    if(shared_stuff->written) {
                        //flag is raised, done this row
                        printf("Done row 1! \n");
                        
                        shared_stuff->written = 0; //close flag
                        
                        //                    printf("%d %d %d %d \n", shared_stuff->Q[0][0], shared_stuff->Q[1][0], shared_stuff->Q[2][0], shared_stuff->Q[3][0]);
                        
                        
                        running = 0;
                    }
                    
                    
                    
                }  //going to add this part after - will cause a crash rn
                
                _Exit(EXIT_SUCCESS);
                break;
                
        }
        
        
    }
    
    
   
    
    
    
    return 0;
    
    
    
    
    if (shmdt(shared_memory) == -1){
        fprintf(stderr, "shmdt failed \n");
        exit(EXIT_FAILURE);
    }
    
    if (shmctl(shmid, IPC_RMID, 0) == -1){
        fprintf(stderr, "shmctl failed \n");
        exit(EXIT_FAILURE);
    }
    
    
    
    _Exit(EXIT_SUCCESS);
    
    
    
}

