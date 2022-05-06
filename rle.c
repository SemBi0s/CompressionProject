#include <stdio.h>
#include <stdlib.h>


int main(int argc, char const *argv[]){

	FILE *rle = fopen("rle.txt", "r");
	char c, temp = "";
	int count;
	if(rle!=NULL)
		while((c = fgetc(rle)) != EOF){
			if(c == temp)
				count++;
			else{
				if(count > 0)
					for (int i = 0; i < count; ++i){
						
					}



				count = 0;
				c = temp;
			}
		}


	return 0;
}