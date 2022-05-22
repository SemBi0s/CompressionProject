#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "list.h"

void Push(node** headRef, char *value, int id){
  element d;
  d.id = id + 1;
  d.value = value;
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
    PushEnd(&(((*headRef)->next)),value, (*headRef)->data.id);
}

void PrintList(node *head, FILE *fp){
    if(head->data.id == 0){
        head = head->next;
    }

    while(head != NULL){
        fprintf(fp, "%d:%s ", (head->data.id) , (head->data.value));
        head = head->next;
    }
    fprintf(fp,"\n");
}

void DeleteList(node ** head){
	node *temp;
	while (*head){
		temp = *head;
		(*head) = (*head)->next;
		free(temp);
	}
}