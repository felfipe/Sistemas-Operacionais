#include<stdio.h>
#include<stdlib.h>



int main(){
    FILE *arquivo1 = fopen("foto.jpg","r");
    if(!arquivo1)
        printf("ERRO NA LEITURA");
    FILE *arquivo2 = fopen("copia.jpg","w");
    if(!arquivo2)
        printf("ERRO NA LEITURA");    
    char byte;
    while(fread(&byte,sizeof(char),1,arquivo1))
        fwrite(&byte,sizeof(char),1,arquivo2);
    fclose(arquivo1);
    fclose(arquivo2);
    return 0;
}