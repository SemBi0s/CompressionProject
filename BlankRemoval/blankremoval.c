#include <stdio.h>

int Compress(){
    FILE *fr = fopen("white.txt", "r");
    if(fr == NULL) {
        perror("Error opening the file to compress");
        return(-1);
    }
    FILE *fp = fopen("compressed.txt", "w");
    if(fp == NULL) {
        perror("Error opening the output file");
        return(-1);
    }

    //l is the freshly taken character from the file
    //i is the temporary variable that counts blank spaces in a row.
    char l;
    int i;
    //x is the tally of the char type characters except the blanks
    //n is the total number of blanks in the original file
    //c is the total number of characters corresponding to the simplifications of the blanks in the compressed file
    //r is the compressin ratio
    int end;
    float n, c, x, r;

    while (end==0){
        i=0;
        l = fgetc(fr);
        x++;
        while (l == ' '){
            i++;
            n++;
            l = fgetc(fr);
        }
        if (i==1){
            fprintf(fp, " ");
            c++;
        }
        else if (i==2){
            fprintf(fp, "  ");
            c=c+2;
        }
        else if (i>2){
            fprintf(fp, "$%d", i);
            c=c+2;
            if (i>=10)
                c=c+3;
            if (i>=100)
                c=c+4;
            //c, the number of characters added to the compressed file;
        }
        if (l!= ' ')
             fprintf(fp, "%c", l);
        if (feof(fr))
            end=1;
    }
    c=c+x;  //c is now the total number of characters in the compressed file
    n=n+x;  //n is now the total number of characters in the original file
    r=100-((c/n)*100);
    printf("\tStats :\n");
    printf("Num. of Characters in the oiginal file : %.0f\nNum. of characters in the compressed file : %.0f\n", n, c);
    printf("Compression Eatio: %.2f", r);
    
    fclose(fr);
    fclose(fp);
}

int DeCompress(){
    //open the files and make sure the file to compress exists
    FILE *fp = fopen("compressed.txt", "r");
    if(fp == NULL) {
        perror("Error opening the compressed file for decompression");
        return(-1);
    }
    FILE *fc = fopen("decompressed.txt", "w");
    if(fc == NULL) {
        perror("Error opening the 'decompressed file' file");
        return(-1);
    }
    char l;
    int i, a, end=0;
    while (end==0){
        l = fgetc(fp);
        a=0;
        if (l == '$'){
            fscanf(fp, "%d", &i);
            for(a=0;a<=i;a++)
                fprintf(fc, " ");
        }
        else
            fprintf(fc, "%c", l);
        if (feof(fp))
            end=1;
    }
    fclose(fp);
    fclose(fc);
}

int main(){
    Compress();
    DeCompress();
}