#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

int main()
{
    int fp;
    struct stat mystat;
    void *pmap;

    fp = open("teste.txt", O_RDWR);

    if(fp == -1){
        exit(1);
    }

    if(fstat(fp, &mystat) <0){
        close(fp);
        exit(1);
    }

    clock_t inicio,fim;                 //Utilizado para a medição de tempo da mmap
    inicio = clock();
    /* FUNÇÃO MMAP:
        -argumento 1: Endereço preferencial para alocar a memória (não necessariamente será alocada nele)
        -argumento 2: Quantidade de bytes a serem alocados
        -argumento 3: Descreve a proteção de memória desejada. No caso permite leitura e escrita
        -argumento 4: Offset do inicio do mapa em um arquivo

     */

    pmap = mmap(0, mystat.st_size, PROT_READ | PROT_WRITE, MAP_SHARED, fp, 0);

    fim = clock();
    double tempo = (fim - inicio)*1000.0/CLOCKS_PER_SEC;        //Calculo do tempo gasto em MMAP
    printf("Tempo gasto no MMAP: %g ms\n", tempo);

    /*
        Verifica se o ponteiro retornado por mmap() é válido, caso contrário sai do programa
        A constante MAP_FAILED é igual a ((void *) -1) e foi definida em mman.h
     */

    if(pmap == MAP_FAILED){
        close(fp);
        exit(1);

    }
    /*
        Palavra "Esse" ser copiada para a região da memória reservada, substituindo assim a palavra
        "isso" no arquivo de texto

    */
    strncpy(pmap, "Esse", 4);

    inicio = clock();

    /*
        Função MUNMAP devolve o espaço de memória reservado por MMAP. Basta informar o ponteiro da regio da memória
        e também o tamanho.
    */

    munmap(pmap, mystat.st_size);

    fim = clock();
    tempo = (fim - inicio)*1000.0/CLOCKS_PER_SEC;           //Calculo do tempo percorrido em MUNMAP
    printf("Tempo gasto no MUNMAP: %g ms\n", tempo);

    close(fp);

    return 0;
}
