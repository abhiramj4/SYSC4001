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
    int msgid;
    struct message_st myMessage;
    long int msg_to_receive = 0;
    int linkedListKey = 0;
    
    msgid = msgget((key_t)1235, 0666 | IPC_CREAT);
    
    if (msgid == -1) {
        fprintf(stderr, "msgget failed with error: %d\n", errno);
        exit(EXIT_FAILURE);
    }
    
    while (running){
        
        if (msgrcv(msgid, (void *)&myMessage, BUFSIZ,
                   msg_to_receive, 0) == -1) {
            fprintf(stderr, "msgrcv failed with error: %d\n", errno);
            exit(EXIT_FAILURE);
        }
        
        printf("The type of message was: %i \n", myMessage.type);
        
        if(myMessage.type == 0){
            //insert command
            insertFirst(linkedListKey, )
        }
        
        if(myMessage.type == 7){
            running = 0;
        }
    
}
}