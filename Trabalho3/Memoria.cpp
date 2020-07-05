#include "headers/Memoria.h"

Memoria::Memoria(int tamanho){
    this->tamanho = tamanho;
    this->espaco_ocupado = 0;
}
/*
bool Memoria::get_pagina(int pagina){
    for(auto it : this->paginas)
        if(it->get_endereco() == pagina)
            return 1;
    std::cout << "[INFO] Erro, página não existe na memória" << std::endl;
    return 0;
}
void Memoria::insert_pagina(int pagina, int pid){
    if(espaco_ocupado == tamanho){
        std::cout << "[INFO] Erro, espaço insuficiente" << std::endl;
        return;
    }
    if(!(pagina >= 0 && pagina < tamanho)){
        std::cout << "[INFO] Erro, página não existe na memória" << std::endl;
        return;
    }
    Pagina *p = new Pagina(pagina);
    this->paginas.push_front(p);
    espaco_ocupado++;
    return;
}

void Memoria::unset_pagina(int pagina){
    if(!(pagina >= 0 && pagina < tamanho))
        std::cout << "[INFO] Erro, página não existe na memória" << std::endl;
    for(auto it : this->paginas){
        if(it->get_endereco() == pagina){
            paginas.remove(it);
            espaco_ocupado--;
            return;
        }
    }
    std::cout << "[INFO] Erro, página não encontrada." << std::endl;
    return;
}
*/
int Memoria::get_espaco_ocupado(){
    return this->espaco_ocupado;
}
int Memoria::get_tamanho(){
    return this->tamanho;
}
int Memoria::get_endereco_livre(){
    for(int i = 0; i < tamanho; i++)
        if(encontra_endereco(i) == 0)
            return i;
    return -1;
}
bool Memoria::encontra_endereco(int endereco){
    for(auto i : paginas)
        if(i->get_endereco() == endereco)
            return 1;
    return 0;
}