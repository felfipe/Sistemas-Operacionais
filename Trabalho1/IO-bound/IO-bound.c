#include<stdio.h>
#include<stdlib.h>


/*
Este código basicamente cria 10 vezes uma cópia de um arquivo, forçando assim a ter vários acessos a disco e consequentemente um uso forçado
das E/S do sistema. 
*/
int main(){
    for(int i = 0; i < 10; i++){
        FILE *arquivo1 = fopen("foto.jpg","r"); // abre arquivo principal
        if(!arquivo1)
            printf("ERRO NA LEITURA");
        FILE *arquivo2 = fopen("copia.jpg","w"); // cria um arquivo copia
        if(!arquivo2)
            printf("ERRO NA LEITURA");    
        char byte;
        while(fread(&byte,sizeof(char),1,arquivo1)) // faz a cópia byte por byte
            fwrite(&byte,sizeof(char),1,arquivo2);
        fclose(arquivo1);
        fclose(arquivo2);
    }
    return 0;
}