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
    int end;
};




int main () {
    
    int running = 1;
    int msgidAdminRecord; //messages recieved from the admin
    int msgidRecordAdmin; //messages to be sent to the admin
    struct message_st myMessage;
    long int msg_to_receive = 0;
    int linkedListKey = 0;
    
    //need to use two message queues
    msgidAdminRecord = msgget((key_t)1235, 0666 | IPC_CREAT); //this sends messages from the admin to here (the record)
    
    msgidRecordAdmin = msgget((key_t)1236, 0666 | IPC_CREAT); //this sends messages from here to the admin
    
    
    
    
    if (msgidAdminRecord == -1) {
        fprintf(stderr, "msgget failed with error: %d\n", errno);
        exit(EXIT_FAILURE);
    }
    
    if (msgidRecordAdmin == -1) {
        fprintf(stderr, "msgget failed with error: %d\n", errno);
        exit(EXIT_FAILURE);
    }
    
    while (running){
        
        if (msgrcv(msgidAdminRecord, (void *)&myMessage, BUFSIZ,
                   msg_to_receive, 0) == -1) {
            fprintf(stderr, "msgrcv failed with error: %d\n", errno);
            exit(EXIT_FAILURE);
        }
        
        printf("The type of message was: %i \n", myMessage.type);
        
        if(myMessage.type == 0){
            
            //insert command
            printf("message type was input!");
            insertFirst(linkedListKey, myMessage.name, myMessage.departmentName, myMessage.employeeNum, myMessage.salary);
        }
        
        else if(myMessage.type == 1){
            
            //check name command
            printf("message type was check name! \n");
            struct node *result = NULL;
            result = findLink(myMessage.employeeNum);
            printf("The employee name is: %s", result->name);
            strcpy(myMessage.name, result->name);
        }
        
        else if(myMessage.type == 2){
            
            //check department
            printf("message type was check department! \n");
            struct node *result = NULL;
            result = findLink(myMessage.employeeNum);
            printf("The employee deptartment is: %s", result->departmentName);
            strcpy(myMessage.departmentName, result->departmentName);
            
        } else if (myMessage.type == 3) {
            
            //check salary
            printf("message type was check salary! \n");
            struct node *result = NULL;
            result = findLink(myMessage.employeeNum);
            printf("The employee salary is: %i", result->salary);
            myMessage.salary = result->salary;
            
        } else if (myMessage.type == 4) {
            
            //check employee number
            printf("message type was check employee number! \n");
            //struct node *result = NULL;
            //result = findLinkName(myMessage.name);
            //printf("The employee name is: %s", result->name);
            //strcpy(myMessage.name, result->name);
            
        } else if (myMessage.type == 5){
            
            //check employee number
            printf("message type was check employee number! \n");
        } else if (myMessage.type == 6) {
            
            //delete employee
            printf("The message type was delete \n");
            struct node *result = NULL;
            result = delete(myMessage.employeeNum);
            printf("0");
        } else {
            printf("error \n");
        }
        
        //send message
        
        /*
        if (msgsnd(msgidAdminRecord,(void *)&myMessage, sizeof(myMessage), 0) == -1) {
            fprintf(stderr, "msgsnd failed\n");
            exit(EXIT_FAILURE);
        }
        */
        
        //strcpy(myMessage.name, result->name);
        
        //printList();
        
        if(myMessage.type == 7){
            running = 0;
        }
    
    }
}
