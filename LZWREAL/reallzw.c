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

int returnCode(char *value, node *head){
	while(head != NULL){
		if (!strcmp(value, head->data.value))
			// If the element is in, we return 1
			return head->data.id;
		head = head->next;
	}
}

int calcul_ratio(const char input[], const char compressed[]){
	FILE *base = fopen(input,"r");
	FILE *compress = fopen(compressed,"r");
	
	if (base == NULL || compress == NULL){
		return 0; 	
	} 
	char c;
	float c1 = 0;
	float c2 = 0;

	while( (c = fgetc(base)) != EOF){
			c1++;
		}

	while( (c = fgetc(compress)) != EOF){
			c2++;
		}

	printf("compression ratio = %.2f \n", (100 - ((c2/c1))*100));

	fclose(base);
	fclose(compress);
	return 1;
}

// This is our encoding function
int compress(const char input[]){
	// We open the file we want to encode
	FILE *lzw = fopen(input, "r");
	// We open the file that will be our output
	FILE *new = fopen("compress.txt", "w");


	int id = 256;
	// We initialize our buffer and our result which is buffer+readByte to 256 bits
	char buffer[256] = "\0";
	char result[256] = "\0";
	//We initialize our char c as a string of to element, the character and the EOF char
	char c[2] = "\0";


	node *head = (node*) malloc(sizeof(node)); 
	
	element d;
  	d.value = " ";
	d.id = id;

	node *newNode = (node*) malloc(sizeof(node));
	(newNode->data) = d;
	newNode->next = NULL;
	head = newNode;
	
	if(lzw!=NULL){
		
		c[0] = fgetc(lzw);
		strcpy(buffer, "");
		strcpy(result,"");
		
		strcpy(buffer, c);
		

		while(c[0] != EOF){
			c[0] = fgetc(lzw);
			//printf("%s",c);		
			
			strcpy(result, "");
			strcpy(result,buffer);
			strcat(result,c);
			//printf("%s\n",result);

			printf("%d %s\n", isInList(result,head), result);
			//PrintList(*head);

			if (isInList(result, head)){
				strcpy(buffer, result);
			}else{
				id++;
				fprintf(new,"%d", id);
				strcpy(buffer, "");
				PushEnd(&head, result, id);
				strcpy(buffer, c);
				//printf("%s \n", buffer);
			}
			
		}
		fprintf(new,"%s",buffer);
		fclose(lzw);
	}
	else
		return 0;
	
	fclose(new);
	calcul_ratio( input, "compress.txt");
	return 1;
}

int decompress(const char input[]){
	
	FILE *comp = fopen(input, "r");
	// We open the file that will be our output
	FILE *new = fopen("decompress.txt", "w");


	int id = 256;
	// We initialize our buffer and our result which is buffer+readByte to 256 bits
	char buffer[256] = "\0";
	char result[256] = "\0";
	char tempString[256] = "\0";
	//We initialize our char c as a string of to element, the character and the EOF char
	char c[2] = "\0";


	node *head = (node*) malloc(sizeof(node)); 
	
	element d;
  	d.value = " ";
	d.id = id;

	node *newNode = (node*) malloc(sizeof(node));
	(newNode->data) = d;
	newNode->next = NULL;
	head = newNode;

	if(comp!=NULL){
			
		c[0] = fgetc(comp);
		fprintf(new,"%c",id);	

		while((c[0] = fgetc(comp))!= EOF){
			strcpy(buffer, c);
			if (!isInList(c, head)){
				strcat(buffer, c);
				PushEnd(&head, buffer, id++);
			}

			*tempString = (char ) returnCode(buffer, head);
			strcat(buffer, &tempString[0]);

			if (!isInList(buffer, head))			{
				PushEnd(&head, result, id);
			}
			strcat(result, tempString);
			fprintf(new, "%s", result);
			id++;
			
		}
		fprintf(new,"%s",buffer);
		fclose(comp);
	}
	else
		return 0;
	
	fclose(new);

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