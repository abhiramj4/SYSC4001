//
//  RecordKeeper.c
//  
//
//  Created by Abhiram Santhosh on 3/30/19.
//

#include "RecordKeeper.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/msg.h>

struct message_st {
    
    long int message_type;
    char name[500];
    char departmentName[500];
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
    
    msgid = msgget((key_t)1234, 0666 | IPC_CREAT);
    
    if (msgid == -1) {
        fprintf(stderr, "msgget failed with error: %d\n", errno);
        exit(EXIT_FAILURE);
    }
    
    while (running){
        
        if (msgrcv(msgid, (void *)&myMessage, sizeof(myMessage),
                   1, 0) == -1) {
            fprintf(stderr, "msgrcv failed with error: %d\n", errno);
            exit(EXIT_FAILURE);
        }
        
        printf("The type of message was: %i \n", myMessage.type);
        
        msgctl(msgid, IPC_RMID, NULL);
    
}
}
