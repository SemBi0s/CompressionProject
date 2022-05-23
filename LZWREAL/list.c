#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "list.h"

void Push(node** headRef, char *value, int id){
  element d;
  d.value = malloc(sizeof(value));
  d.value = value;
  d.id = id + 1;
  node* newNode=(node*) malloc(sizeof(node));
  newNode->data=d;
  newNode->next=*headRef;
  *headRef=newNode;
}


void PushEnd(node** headRef, char *value, int id){
    if((*headRef)==NULL){
        Push(headRef,value, id);
        return;
    }
    PushEnd(&(((*headRef)->next)),value, (*headRef)->data.id );
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