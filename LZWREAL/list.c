#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "list.h"

void Push(node** headRef, char *value){
  element d;
  d.value = value;
  node* newNode=(node*) malloc(sizeof(node));
  newNode->data=d;
  newNode->next=*headRef;
  *headRef=newNode;
}


void PushEnd(node** headRef, char *value){
    if((*headRef)==NULL){
        Push(headRef,value);
        return;
    }
    PushEnd(&(((*headRef)->next)),value);
}

void PrintList(node *head){
   int i =0;
    while(head != NULL){
        printf( "%s %d ;" , (head->data.value),i);
        head = head->next;
        i++;
    }
    printf("\n");
}

void DeleteList(node ** head){
	node *temp;
	while (*head){
		temp = *head;
		(*head) = (*head)->next;
		free(temp);
	}
}