//
//  LinkedList.h
//  
//
//  Created by Abhiram Santhosh on 3/31/19.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

struct node {
    int employeeNum;
    char name[12];
    char departmentName[12];
    int key;
    int salary;
    struct node *next;
};

struct node *head = NULL;
struct node *current = NULL;

//display the list
void printList() {
    struct node *ptr = head;
    printf("\n[ ");
    
    //start from the beginning
    while(ptr != NULL) {
        printf("(%d: %d %s %s %d) ",ptr->key,ptr->employeeNum, ptr->name, ptr->departmentName, ptr->salary);
        ptr = ptr->next;
    }
    
    printf(" ]");
}

//insert link at the first location
void insertFirst(int key, char name[12], char departmentName[12], int employeeNum, int salary) {
    //create a link
    struct node *link = (struct node*) malloc(sizeof(struct node));
    
    link->key = key;
    strcpy(link->name, name);
    strcpy(link->departmentName, departmentName);
    link->employeeNum = employeeNum;
    link->salary = salary;
    
    //point it to old first node
    link->next = head;
    
    //point first to new first node
    head = link;
}

//delete first item
struct node* deleteFirst() {
    
    //save reference to first link
    struct node *tempLink = head;
    
    //mark next to first link as first
    head = head->next;
    
    //return the deleted link
    return tempLink;
}

//is list empty
bool isEmpty() {
    return head == NULL;
}

int length() {
    int length = 0;
    struct node *current;
    
    for(current = head; current != NULL; current = current->next) {
        length++;
    }
    
    return length;
}

//find a link with given key
struct node* find(int key) {
    
    //start from the first link
    struct node* current = head;
    
    //if list is empty
    if(head == NULL) {
        return NULL;
    }
    
    //navigate through list
    while(current->key != key) {
        
        //if it is last node
        if(current->next == NULL) {
            return NULL;
        } else {
            //go to next link
            current = current->next;
        }
    }
    
    //if data found, return the current Link
    return current;
}

//find a link with a given employee number
struct node* findLink(int employeeNum) {
    
    struct node* current = head; //start with first link
    
    if(head == NULL){
        return NULL;
    }
    
    //traverse the whole linked list
    while(current->employeeNum != employeeNum){
        if(current->next == NULL){
            return NULL;
        } else {
            current = current->next;
        }
    }
    
    return current;
    
}


//delete a link with given key
struct node* delete(int key) {
    
    //start from the first link
    struct node* current = head;
    struct node* previous = NULL;
    
    //if list is empty
    if(head == NULL) {
        return NULL;
    }
    
    //navigate through list
    while(current->key != key) {
        
        //if it is last node
        if(current->next == NULL) {
            return NULL;
        } else {
            //store reference to current link
            previous = current;
            //move to next link
            current = current->next;
        }
    }
    
    //found a match, update the link
    if(current == head) {
        //change first to point to next link
        head = head->next;
    } else {
        //bypass the current link
        previous->next = current->next;
    }
    
    return current;
}
