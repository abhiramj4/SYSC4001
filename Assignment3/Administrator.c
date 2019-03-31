//
//  Administrator.c
//  
//
//  Created by Abhiram Santhosh on 3/30/19.
//

#include "Administrator.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

#include <sys/msg.h>

#define MAX_TEXT 512

struct message_st {
    
    long int message_type;
    char name[MAX_TEXT];
    char departmentName[MAX_TEXT];
    int employeeNum;
    int salary;
    int type; //type of message sent
    //0 for input
    //1 for check name
    //2 for check dept
    //3 for check salary
    //4 for check employee number
    //5 for check (dept name)
    //6 for delete
    int end;
};


int main () {
    
    int running = 1;
    int msgid;
    struct message_st myMessage;
    char userinputString[MAX_TEXT];
    int userinputNumber;
    
    msgid = msgget((key_t)1234, 0666 | IPC_CREAT);
    
    
    printf("here");
    
    
    
    if (msgid == -1) {
        fprintf(stderr, "msgget failed with error: %d\n", errno);
        exit(EXIT_FAILURE);
    }
    
    
    
    while (running){
        
        
        //ask for what command the user wants
        printf("Enter a command: ");
        scanf("%s", &userinputString);
        printf("\n");
        
        //printf("%s", userinput);
        
        if(strcmp(userinputString,"input") == 0){
            
            printf("Enter a name:");
            scanf("%s", &userinputString);
            strcpy(myMessage.name, userinputString);
            printf("\n");
            //printf("\n");
            
            printf("Enter a department name:");
            scanf("%s", &userinputString);
            strcpy(myMessage.departmentName, userinputString);
            printf("\n");
            //printf("\n");
            
            printf("Enter a employee number:");
            scanf("%i", &userinputNumber);
            myMessage.employeeNum = userinputNumber;
            printf("\n");
            //printf("\n");
            
            printf("Enter a salary:");
            scanf("%i", &userinputNumber);
            myMessage.salary = userinputNumber;
            printf("\n");
            //printf("\n");
            
            myMessage.type = 0;
            
            
        }
        
        if(strcmp(userinputString,"check_name") == 0){
            
            printf("Enter a employee number:");
            scanf("%i", &userinputNumber);
            myMessage.employeeNum = userinputNumber;
            printf("\n");
            
            myMessage.type = 1;
            
        }
        
        if(strcmp(userinputString,"check_department") == 0){
            
            printf("Enter a employee number:");
            scanf("%i", &userinputNumber);
            myMessage.employeeNum = userinputNumber;
            printf("\n");
            
            myMessage.type = 2;
            
        }
        
        if(strcmp(userinputString,"check_salary") == 0){
            
            printf("Enter a employee number:");
            scanf("%i", &userinputNumber);
            myMessage.employeeNum = userinputNumber;
            printf("\n");
            
            myMessage.type = 3;
            
        }
        
        if(strcmp(userinputString,"check_employee_number") == 0){
            
            printf("Enter a employee name:");
            scanf("%s", &userinputString);
            strcpy(myMessage.name, userinputString);
            printf("\n");
            
            myMessage.type = 4;
            
        }
        
        if(strcmp(userinputString,"check") == 0){
            
            printf("Enter a department name:");
            scanf("%s", &userinputString);
            strcpy(myMessage.departmentName, userinputString);
            printf("\n");
            
            myMessage.type = 5;
            
        }
        
        if(strcmp(userinputString,"delete") == 0){
            
            printf("Enter a employee number:");
            scanf("%i", &userinputNumber);
            myMessage.employeeNum = userinputNumber;
            printf("\n");
            
            myMessage.type = 6;
            
        }
        
        if (strncmp(userinputString, "end", 3) == 0) {
            myMessage.type = 7;
            
            if (msgsnd(msgid, (void *)&myMessage, MAX_TEXT, 0) == -1) {
                fprintf(stderr, "msgsnd failed\n");
                exit(EXIT_FAILURE);
            }
            
            running = 0;
        }
        
        
        if (msgsnd(msgid, (void *)&myMessage, MAX_TEXT, 0) == -1) {
            fprintf(stderr, "msgsnd failed\n");
            exit(EXIT_FAILURE);
        }
        
        if (msgrcv(msgid, (void *)&myMessage, BUFSIZ,
                   msg_to_receive, 0) == -1) {
            fprintf(stderr, "msgrcv failed with error: %d\n", errno);
            exit(EXIT_FAILURE);
        }
        
        
        
        
        
    }
    
    
    
    if (msgctl(msgid, IPC_RMID, 0) == -1) {
        fprintf(stderr, "msgctl(IPC_RMID) failed\n");
        exit(EXIT_FAILURE);
    }
    
    exit(EXIT_SUCCESS);
    
}
