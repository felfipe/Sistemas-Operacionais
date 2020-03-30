#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/mman.h>
#include <time.h>

#define handle_error(msg) \
           do { perror(msg); exit(EXIT_FAILURE); } while (0)



int main(int argc, char *argv[])
{
    clock_t inicio,fim;
    char *buffer;
    char *p;
    int i = 0;
    int mp;
    int pagina_disco = 4096;

    buffer = memalign(pagina_disco, 4 * pagina_disco);

    /*
        Faz a chamada de mprotect e confere se deu erro
        Neste caso, das 4 paginas de disco alocadas, a segunda é impedida de leitura
    */

    inicio = clock();
    mp = mprotect(buffer + pagina_disco * 2, pagina_disco, PROT_READ);
    fim = clock();
    double tempo = (fim - inicio)*1000.0/CLOCKS_PER_SEC;        //Calculo do tempo gasto em MProtect

    if(mp == -1){
        exit(1);
    }


     /*
        Contagem de quantos bytes são lidos até que o programa caia em segmentation fault
        O último número exibido na tela representa essa quantidade de bytes, que deve ser de 8192 (duas paginas de disco)
     */

    for (p = buffer ; ; ){
        i++;
        *(p++) = 'a';
        printf("%d\n", i);
        printf("Tempo gasto no MProtect: %g ms\n", tempo);
    }

    printf("Loop completed\n");     /* Should never happen */
    exit(EXIT_SUCCESS);
}
