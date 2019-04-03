//
//  RecordKeeper.c
//
//
//  Created by Abhiram Santhosh on 3/30/19.
//

#include "RecordKeeper.h"
#include "LinkedList.h" //use it to store the employees
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/msg.h>

struct message_st {
    
    long int message_type;
    char name[12];
    char departmentName[12]; //max of 12 DON'T CHANGE
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
    
    long int msg_to_receive = 0;
    int linkedListKey = 0;
    
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
        
        if (msgrcv(msgidAdmintoRecord, (void *)&messageAdmintoRecord, BUFSIZ,
                   msg_to_receive, 0) == -1) {
            fprintf(stderr, "msgrcv failed with error: %d\n", errno);
            exit(EXIT_FAILURE);
        }
        
        printf("The type of message was: %i \n", messageAdmintoRecord.type);
        
        if(messageAdmintoRecord.type == 0){
            //insert command
            printf("message type was input!");
            insertFirst(linkedListKey, messageAdmintoRecord.name, messageAdmintoRecord.departmentName, messageAdmintoRecord.employeeNum, messageAdmintoRecord.salary);
        }
        
        if(messageAdmintoRecord.type == 1){
            //check name command
            printf("message type was check name! \n");
            struct node *result = NULL;
            result = findLink(messageAdmintoRecord.employeeNum);
            printf("The employee name is: %s", result->name);
            strcpy(messageRecordtoAdmin.name, result->name);
            messageRecordtoAdmin.type = 1;
        }
        
        if(messageAdmintoRecord.type == 2){
            //check department command
            printf("message type was check department! \n");
            struct node *result = NULL;
            result = findLink(messageAdmintoRecord.employeeNum);
            printf("The employee department is: %s", result->departmentName);
            strcpy(messageRecordtoAdmin.departmentName, result->departmentName);
            messageRecordtoAdmin.type = 2;
        }
        
        if(messageAdmintoRecord.type == 3){
            //check department command
            printf("message type was check salary! \n");
            struct node *result = NULL;
            result = findLink(messageAdmintoRecord.employeeNum);
            printf("The employee salary is: %i", result->salary);
            messageRecordtoAdmin.salary = result->salary;
            messageRecordtoAdmin.type = 3;
        }
        
        if(messageAdmintoRecord.type == 4){
            //check department command
            printf("message type was check employee number! \n");
            struct node *result = NULL;
            result = findLinkName(messageRecordtoAdmin.name);
            printf("The employees number is: %i", result->employeeNum);
            messageRecordtoAdmin.employeeNum = result->employeeNum;
            messageRecordtoAdmin.type = 4;
        }
        
        if(messageAdmintoRecord.type == 5){
            //check department command
            printf("message type was check ! \n");
            messageRecordtoAdmin.type = 5;
            
        }
        
        if(messageAdmintoRecord.type == 6){
            //check department command
            printf("message type was delete employee! \n");
            struct node *result = NULL;
            result = deleteSpecific(messageRecordtoAdmin.employeeNum);
            
            
            if(result == NULL){
                messageRecordtoAdmin.type = 6;
            } else {
                messageRecordtoAdmin.type = 8;
            }
        }
        
        
        if (msgsnd(msgidRecordtodAdmin, (void *)&messageRecordtoAdmin, sizeof(messageRecordtoAdmin), 0) == -1){
            fprintf(stderr, "msgsnd failed\n");
            exit(EXIT_FAILURE);
        }
        
        if(messageAdmintoRecord.type == 7){
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
