#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>

int main(void)
{
    pid_t pid;
    clock_t t_fork;
    clock_t t_gp;
    clock_t t_wait;
    
    t_fork=clock();
    pid=fork();
    t_fork=clock()-t_fork;
    if(pid<0){ //se o fork retornar negativo, houve um erro
        perror("fork");
        exit(1);
    }
    else if(pid==0){ //se o fork retornar 0, significa que essa parte do código será executado no processo do filho
        t_gp=clock();
        printf("pid do filho:%d e pid do pai:%d\n",getpid(),getppid()); //é possível pegar o pid do pai e do filho no processo do filho
        t_gp=clock()-t_gp;
    }
    else{ //O código neste trecho será executado no processo pai
        printf("pid do pai:%d e pid do filho:%d\n",getpid(),pid); //é possível pegar o pid do pai e do filho no processo do pai
    }
    t_wait=clock();
    wait(NULL); //garante que o pai não dê exit antes de saber o valor de retorno do filho
    t_wait=clock()-t_wait();
    if(pid==0){
        printf("Tempo de execucao do fork:%lf\n",((double)t_fork)/(CLOCKS_PER_SEC / 1000));
           }
    if(pid>0){
        printf("Tempo de execucao do getpid e getppid:%lf\nTempo de execucao do wait:%lf\n",((double)t_gp)/(CLOCKS_PER_SEC / 1000),((double)t_wait)/(CLOCKS_PER_SEC / 1000));
    }
    exit(1);
}
