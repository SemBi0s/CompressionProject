#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

int isInList(char *value, node *head){
	while(head != NULL){
		if (!strcmp(value, head->data.value))
			return 1;
		head = head->next;
	}
	return 0;
}

int printId(char *value, node *head, FILE *fp){
	while(head != NULL){
		if (!strcmp(value, head->data.value)){
			fprintf(fp, "%d", head->data.id);
			return 1;
		}
		head = head->next;
	}
	return 0;
}

int compress(const char input[]){
	
	FILE *lzw = fopen(input, "r");
	FILE *new = fopen("compress.txt", "w");
	int id = 0;
	char *value;
	char c;
	fpos_t pos;
	node **head = (node**) malloc(sizeof(node*)); 
	
	element d;
	d.id = 0;
  	d.value = " ";
	
	node *newNode = (node*) malloc(sizeof(node));
	(newNode->data) = d;
	newNode->next = NULL;
	*head = newNode;
	
	
	if(lzw!=NULL){
		while(fscanf(lzw, "%ms", &value) == 1){
			if(!isInList(value,*head))
				PushEnd(head, value, 0);
		}

		PrintList(*head, new);
		
		rewind(lzw);
		while(fscanf(lzw, "%ms", &value) == 1){
			printId(value, *head, new);
			if(fgetpos(lzw, &pos))printf("error while getting pos in file");
			
			while((c = fgetc(lzw)) == ' ' || c == '\n')
				fprintf(new, "%c",c);
			fsetpos(lzw, &pos);
		}
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