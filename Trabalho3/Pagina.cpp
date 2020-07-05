#include "headers/Pagina.h"
Pagina::Pagina(int endereco, int pid){
    this->endereco = endereco;
    this->pid = pid;
    this->R = 1;
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
void Pagina::setR(bool R){
    this->R = R;
    return;
}
bool Pagina::getR(){
    return this->R;
}