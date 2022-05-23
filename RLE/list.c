#include "list.h"
#include<stdlib.h>
#include<stdio.h>


void Push(node** headRef, element d ){
  node* newNode=(node*) malloc(sizeof(node));
  newNode->data=d;
  newNode->next=*headRef;
  *headRef=newNode;
}


void PushEnd(node** headRef, element data){
    if((*headRef)==NULL){
        Push(headRef,data);
        return;
    }
    PushEnd(&(((*headRef)->next)),data);
}

void PrintList(node *head)
{
    while(head != NULL)
    {
        printf("%d ", head->data.vertex);
        head = head->next;
    }
}

void DeleteList(node ** head){
	node *temp;
	while (*head){
		temp = *head;
		(*head) = (*head)->next;
		free(temp);
	}
}