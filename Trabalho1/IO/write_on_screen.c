#include <unistd.h>  // unistd.h é uma biblioteca que fornece API wrapper para chamadas de sistema do SO, usando o padrão POSIX (IEEE).
#include <fcntl.h>
#include <stdio.h>
#include <time.h>

void limpa_string(char* string, int tam){
    for(int i = 0; i < tam; i++)
        string[i] = '\0';
    return;
}
int main(){
    clock_t inicio,fim; // DECLARAÇÕES
    int file_descriptor;
    char frase[50];
    limpa_string(frase, 50);
    double tempo;
    
    inicio = clock();   // ABRIR ARQUIVO
    file_descriptor = open("file.txt", O_RDONLY); // Syscall para abrir um arquivo e gerar um file_descriptor.
    fim = clock();
    tempo = (fim - inicio)*1000.0/CLOCKS_PER_SEC;
    printf("Tempo para abrir o arquivo: %g mS\n", tempo);

    inicio = clock(); // LER ARQUIVO
    read(file_descriptor, frase, 50);
    fim = clock();
    tempo = (fim - inicio)*1000.0/CLOCKS_PER_SEC;
    printf("Tempo para ler do arquivo: %g mS\n", tempo);

    inicio = clock(); // ESCREVER NA TELA
    write(0, &frase, 50); // essa função utiliza a syscall write. O primeiro argumento é o descritor do arquivo ( 0 para out, 1 para input, 2 para stderr).
    fim = clock();
    tempo = (fim - inicio)*1000.0/CLOCKS_PER_SEC;
    printf("Tempo gasto na escrita: %g mS\n", tempo);


    return 0;
}