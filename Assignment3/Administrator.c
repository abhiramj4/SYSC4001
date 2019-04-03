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
#include <sys/ipc.h>
#include <sys/msg.h>

#define MAX_TEXT 12

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
    //7 for end
};




int main () {
    
    int running = 1;
    
    int msgidAdmintoRecord;
    int msgidRecordtodAdmin;
    
    struct message_st messageAdmintoRecord;
    struct message_st messageRecordtoAdmin;
    
    char userinputString[MAX_TEXT];
    int userinputNumber;
    long int msg_to_receive = 0;
    
    msgidAdmintoRecord = msgget((key_t)1235, 0666 | IPC_CREAT);
    
    msgidRecordtodAdmin = msgget((key_t)1236, 0666 | IPC_CREAT);
    
    
    
    
    if (msgidAdmintoRecord == -1) {
        fprintf(stderr, "msgget failed with error: %d\n", errno);
        exit(EXIT_FAILURE);
    }
    
    if (msgidRecordtodAdmin == -1) {
        fprintf(stderr, "msgget failed with error: %d\n", errno);
        exit(EXIT_FAILURE);
    }
    
    
    
    while (running){
        
        
        //ask for what command the user wants
        printf("Enter a command: ");
        scanf("%s", &userinputString);
        printf("\n");
        messageAdmintoRecord.message_type = 1;
        //printf("%s", userinput);
        
        if(strcmp(userinputString,"input") == 0){
            
            printf("Enter a name:");
            scanf("%s", &userinputString);
            strcpy(messageAdmintoRecord.name, userinputString);
            printf("\n");
            //printf("\n");
            
            printf("Enter a department name:");
            scanf("%s", &userinputString);
            strcpy(messageAdmintoRecord.departmentName, userinputString);
            printf("\n");
            //printf("\n");
            
            printf("Enter a employee number:");
            scanf("%i", &userinputNumber);
            messageAdmintoRecord.employeeNum = userinputNumber;
            printf("\n");
            //printf("\n");
            
            printf("Enter a salary:");
            scanf("%i", &userinputNumber);
            messageAdmintoRecord.salary = userinputNumber;
            printf("\n");
            //printf("\n");
            
            messageAdmintoRecord.type = 0;
            
            
        }
        
        else if(strcmp(userinputString,"check_name") == 0){
            
            printf("Enter a employee number:");
            scanf("%i", &userinputNumber);
            messageAdmintoRecord.employeeNum = userinputNumber;
            printf("\n");
            
            messageAdmintoRecord.type = 1;
            
        }
        
        else if(strcmp(userinputString,"check_department") == 0){
            
            printf("Enter a employee number:");
            scanf("%i", &userinputNumber);
            messageAdmintoRecord.employeeNum = userinputNumber;
            printf("\n");
            
            messageAdmintoRecord.type = 2;
            
        }
        
        else if(strcmp(userinputString,"check_salary") == 0){
            
            printf("Enter a employee number:");
            scanf("%i", &userinputNumber);
            messageAdmintoRecord.employeeNum = userinputNumber;
            printf("\n");
            
            messageAdmintoRecord.type = 3;
            
        }
        
        else if(strcmp(userinputString,"check_employee_number") == 0){
            
            printf("Enter a employee name:");
            scanf("%s", &userinputString);
            strcpy(messageAdmintoRecord.name, userinputString);
            printf("\n");
            
            messageAdmintoRecord.type = 4;
            
        }
        
        else if(strcmp(userinputString,"check") == 0){
            
            printf("Enter a department name:");
            scanf("%s", &userinputString);
            strcpy(messageAdmintoRecord.departmentName, userinputString);
            printf("\n");
            
            messageAdmintoRecord.type = 5;
            
        }
        
        else if(strcmp(userinputString,"delete") == 0){
            
            printf("Enter a employee number:");
            scanf("%i", &userinputNumber);
            messageAdmintoRecord.employeeNum = userinputNumber;
            printf("\n");
            
            messageAdmintoRecord.type = 6;
            
        } else if(strcmp(userinputString,"end") == 0){
            printf("Messages ended");
            messageAdmintoRecord.type = 7;
            printf("\n");
        }
        
        
        else {
            printf("Error! Not a correct command");
        }
        
        
        if (msgsnd(msgidAdmintoRecord,(void *)&messageAdmintoRecord, sizeof(messageAdmintoRecord), 0) == -1) {
            fprintf(stderr, "msgsnd failed\n");
            exit(EXIT_FAILURE);
        }
        
        
        if(msgrcv(msgidRecordtodAdmin, (void *)&messageRecordtoAdmin, sizeof(messageRecordtoAdmin), msg_to_receive,0) == -1) {
            fprintf(stderr, "msgrcv failed with error: %d\n", errno);
            exit(EXIT_FAILURE);
        }
        
        if(messageRecordtoAdmin.type == 1){
            //check name
            printf("%s \n",messageRecordtoAdmin.name);
        }
        
        if(messageRecordtoAdmin.type == 2){
            //check name
            printf("%s \n",messageRecordtoAdmin.departmentName);
        }
        
        if(messageRecordtoAdmin.type == 3){
            //check name
            printf("%i \n",messageRecordtoAdmin.salary);
        }
        
        if(messageRecordtoAdmin.type == 4){
            //check name
            printf("%i \n",messageRecordtoAdmin.employeeNum);
        }
        
        if(messageRecordtoAdmin.type == 5){
            //check name
            printf("%this command is check! \n");
        }
        
        if(messageRecordtoAdmin.type == 6){
            //check name
            printf("0 \n");
        }
        
        if(messageRecordtoAdmin.type == 8){
            //check name
            printf("1 \n");
        }
        
        
        if (strncmp(userinputString, "end", 3) == 0) {
            running = 0;
        }
        
        
        
        
        
        
    }
    
    if (msgctl(msgidAdmintoRecord, IPC_RMID, 0) == -1) {
        fprintf(stderr, "msgctl(IPC_RMID) failed\n");
        exit(EXIT_FAILURE);
    }
    
    if (msgctl(msgidRecordtodAdmin, IPC_RMID, 0) == -1) {
        fprintf(stderr, "msgctl(IPC_RMID) failed\n");
        exit(EXIT_FAILURE);
    }
    
    exit(EXIT_SUCCESS);
    
}
