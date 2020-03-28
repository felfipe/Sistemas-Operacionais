#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void)
{
    pid_t pid;
    pid=fork();
    if(pid<0){ //se o fork retornar negativo, houve um erro
        perror("fork");
        exit(EXIT_FAILURE);
    }
    else if(pid==0){ //se o fork retornar 0, significa que essa parte do código será executado no processo do filho
        printf("pid do filho:%d e pid do pai:%d\n",getpid(),getppid()); //é possível pegar o pid do pai e do filho no processo do filho
    }
    else{ //O código neste trecho será executado no processo pai
        printf("pid do pai:%d e pid do filho:%d\n",getpid(),pid); //é possível pegar o pid do pai e do filho no processo do pai
    }

    int status = -1;
    waitpid(pid, &status, WEXITED); //garante que o pai não dê exit antes de saber o valor de retorno do filho

    printf("O filho retornou o codigo %d\n", status);
    exit(EXIT_SUCCESS);
}
