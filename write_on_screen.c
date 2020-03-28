#include <unistd.h>  // unistd.h é uma biblioteca que fornece API wrapper para chamadas de sistema do SO, usando o padrão POSIX (IEEE).
#include <stdio.h>
#include <time.h>

int main(){
    char frase[50] = "This is a different Hello World.\n";
    clock_t inicio,fim;
    inicio = clock();
    write(0, &frase, 50); // essa função utiliza a syscall write. O primeiro argumento é o descritor do arquivo ( 0 para out, 1 para input, 2 para stderr).
    fim = clock();
    double tempo = (fim - inicio)*1000.0/CLOCKS_PER_SEC;
    printf("Tempo gasto: %g mS\n", tempo);
    return 0;
}