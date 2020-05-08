#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h>
#define TAM_BUFFER 10 // tamanho que o buffer terá

pthread_t produtor_id;
pthread_t consumidor_id;
pthread_mutex_t semaforo_buffer;  // serve para controlar acesso ao buffer
pthread_cond_t status_produtor;   // serve para acordar/dormir produtor
pthread_cond_t status_consumidor; // serve para acordar/dormir consumidor
int* buffer = NULL;
int qtd_itens_buffer = 0;
int i = 0; // aponta para a próxima posição a ser inserida no buffer
int j = 0; // aponta para a próxima posição a ser consumida no buffer



/*
função produtora de informação executada em uma thread que acessa um buffer compartilhado 
*/
void * produtor(void *arg){
    while(1){
        pthread_mutex_lock(&semaforo_buffer); // Início da região crítica
        int item = rand()%10 + 1;
        if(qtd_itens_buffer >= TAM_BUFFER){ // Se não houver mais espaços para inserir, dorme e acorda consumidor.
            printf("[produtor] : buffer cheio, indo dormir. \n");
            pthread_cond_signal(&status_consumidor);
            pthread_cond_wait(&status_produtor,&semaforo_buffer);
            printf("[produtor] : acordei! Trabalho para fazer. \n");
        }
        qtd_itens_buffer++;
        buffer[i] = item;
        printf("[produtor] : item %d inserido na posição %d\n",item,i);
        i = (i + 1)%(TAM_BUFFER);    
        pthread_cond_signal(&status_consumidor);
        pthread_mutex_unlock(&semaforo_buffer); // Fim da região crítica
    }
    pthread_exit(NULL);
}

/*
função consumidora de informação de um buffer compartilhado
*/
void * consumidor(void *arg){
    while(1){
        pthread_mutex_lock(&semaforo_buffer); // Início da região crítica
        int item;
        if(qtd_itens_buffer <= 0){ // Se não houver itens para consumir, dorme e acorda produtor
            printf("[consumidor] : buffer vazio, indo dormir. \n");
            pthread_cond_signal(&status_produtor);
            pthread_cond_wait(&status_consumidor,&semaforo_buffer);
            printf("[consumidor] : acordei! Trabalho para fazer. \n");
        }
        qtd_itens_buffer--;
        item = buffer[j];
        buffer[j] = 0;
        printf("[consumidor] : item %d consumido da posicao %d.\n",item,j);
        j = (j + 1)%(TAM_BUFFER);
        pthread_cond_signal(&status_produtor);
        pthread_mutex_unlock(&semaforo_buffer); // Fim da região crítica
    }
    pthread_exit(NULL);
}


int main(){
    srand(time(NULL));
    buffer = (int*)calloc(TAM_BUFFER,sizeof(int));
    pthread_mutex_init(&semaforo_buffer, NULL);
    
    
    if(pthread_create(&produtor_id, NULL, produtor, NULL)){
        printf("Erro ao criar Produtor");
        exit(0);
    }
    if(pthread_create(&consumidor_id, NULL, consumidor, NULL)){
        printf("Erro ao criar Consumidor");
        exit(0);
    }
    pthread_join(produtor_id,NULL);
    pthread_join(consumidor_id,NULL);
}