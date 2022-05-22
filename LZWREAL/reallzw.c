/*
*
*	LZW by Alexandre Daumard and Iwen Zanou
*
*/

// We include all libraries we need and our header file
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

// This Function is used to verify if a string is in the dictionnary
int isInList(char *value, node *head){
	// While the element of the linked list is not Null we check if the element is in the dictionnary
	while(head != NULL){
		if (!strcmp(value, head->data.value))
			// If the element is in, we return 1
			return 1;
		head = head->next;
	}
	//If not, we return 0
	return 0;
}


// This is our encoding function
int compress(const char input[]){
	// We open the file we want to encode
	FILE *lzw = fopen(input, "r");
	// We open the file that will be our output
	FILE *new = fopen("compress.txt", "w");


	// We initialize our buffer and our result which is buffer+readByte to 256 bits
	char *buffer =(char *) malloc(sizeof(char) * 256);
	char *result = (char *) malloc(sizeof(char) * 256);
	//We initialize our char c as a string of to element, the character and the EOF char
	char c[2];

	//We initialize our dictionnary 
	node **head = (node**) malloc(sizeof(node*)); 
	
	element d;
  	d.value = " ";
	
	node *newNode = (node*) malloc(sizeof(node));
	(newNode->data) = d;
	newNode->next = NULL;
	*head = newNode;
	
	
	if(lzw!=NULL){
		c[0] = fgetc(lzw);
		strcpy(buffer, "")
		strcpy(result,"");
		
		strcpy(buffer, c);
		PushEnd(head, buffer);
		

		while(c[0] != EOF){

			c[0] = fgetc(lzw);
			//printf("%s",c);		
			strcpy(result, "\0");

			strcpy(result,buffer);
			strcat(result,c);

			//PrintList(*head);

			if (isInList(result, *head)){
				strcpy(buffer, result);
			}else{

				fprintf(new,"%s", buffer);
				PushEnd(head, result);
				strcpy(buffer, c);
			}
			
		}
		fprintf(new,"%s",buffer);
		fclose(lzw);
	}
	else
		return 0;
	
	fclose(new);
	//calcul_ratio( input, "compress.txt");
	return 1;
}

int decompress(const char input[]){
	
	return 1;
}


int main(int argc, char const *argv[]){

	if (argv[1] != NULL && argv[1][1] == 'c' ){
		if(argv[2] != NULL && !compress(argv[2]))
			printf("\ncompression failed check filename\n");
		else
			printf("\ncompression successfull\n");
	}

	else if(argv[1] != NULL && argv[1][1] == 'd'){
		if(argv[2] != NULL &&!decompress(argv[2]))
			printf("\ndecompression failed check filename\n");
		else
			printf("\ndecompression successfull\n");
	}
	else 		
		printf("\nwrong arguments\n");
	
	return 0;
}