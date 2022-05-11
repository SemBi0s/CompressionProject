#include <stdio.h>
#include <stdlib.h>



int compress(const char input[]){
	FILE *rle = fopen(input, "r");
	FILE *new = fopen("compress.txt", "w");
	char c, temp = '\0';
	int count = 1;
	int cbis = 1;
	int t =1;
	if(rle!=NULL){
		while(t){
			c = fgetc(rle);
			if(!(temp == EOF)){
				if(c == temp){
					count++;
					cbis++;
					cbis = cbis %3;
				}else{
					if(count > 3 ){
						fprintf(new, "%c$%d",temp,count);
					}else if(temp != '\0'){
						for (int i = 0; i <= cbis; ++i){
							fprintf(new,"%c", temp);
						}
					}
					count = 1;
					cbis = 0;
					temp = c;
				}
			}else
				t = 0;
		}
	}
	else
		return 0;

	fclose(rle);
	fclose(new);

	return 1;
}

int decompress(const char input[]){
	FILE *rle = fopen(input, "r");
	FILE *decomp = fopen("decompress.txt", "w");
	char c, temp = '\0';
	int count = 0;
	char a,b;
	int co;
	if((rle)!=NULL){
		while((c = fgetc(rle) )!= EOF && temp != EOF){
			if (c == '$'){
				fscanf(rle ,"%d", &co);
				for (int i = 0; i < co; ++i){
					fprintf(decomp, "%c",temp);
				}
			}else if (temp != '\0' && temp != '$'){
				fprintf(decomp,"%c",temp);
			}
			temp = c;
		}
		
	}
	else
		return 0;

	fclose(rle);
	fclose(decomp);

	return 1;
}



int main(int argc, char const *argv[]){
	
	if (argv[1][1] == 'c'){
		if(!compress(argv[2]))
			printf("\ncompression failed check filename\n");
		else
			printf("\ncompression successfull\n");
	}

	else if(argv[1][1] == 'd'){
		if(!decompress(argv[2]))
			printf("\ndecompression failed check filename\n");
		else
			printf("\ndecompression successfull\n");
	}
	else 		
		printf("\nwrong arguments\n");
	
	return 0;
}