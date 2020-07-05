#include "headers/Pagina.h"
Pagina::Pagina(int endereco, int pid){
    this->endereco = endereco;
    this->pid = pid;
}
int Pagina::get_endereco(){
    return this->endereco;
}
void Pagina::set_endereco(int endereco){
    this->endereco = endereco;
}
int Pagina::get_pid(){
    return this->pid;
}