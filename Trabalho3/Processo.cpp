#ifndef _PROCESSO
#define _PROCESSO
#include "headers/Processo.h"
Processo::Processo(int pid, int tamanho){
    this->pid = pid;
    this->tamanho = tamanho;
    tabela = new Elemento[tamanho];
}
int Processo::get_pid(){
    return this->pid;
}
int Processo::get_tamanho(){
    return this->tamanho;
}
void Processo::set_pid(int pid){
    this->pid = pid;
}
void Processo::set_tamanho(int tamanho){
    this->tamanho = tamanho;
}

#endif