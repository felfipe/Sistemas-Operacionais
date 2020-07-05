#include "headers/Gerenciador.h"

Gerenciador::Gerenciador(int tamanho_primaria, int tamanho_secundaria, int tamanho_pagina, bool tipo){
    this->tamanho_primaria = tamanho_primaria;
    this->tamanho_secundaria = tamanho_secundaria;
    this->tamanho_pagina = tamanho_pagina;
    this->espaco_ocupado = 0;
    this->tipo = tipo;
    this->memoria_primaria = new Memoria(calcula_paginas(tamanho_primaria));
    this->memoria_secundaria = new Memoria(calcula_paginas(tamanho_secundaria));
    this->clock_pointer = this->memoria_primaria->paginas.begin();
    std::cout << "[INFO] MMU instanciada." << std::endl;
    std::cout << "[INFO] Memória principal: " << tamanho_primaria << " KB" << std::endl;
    std::cout << "[INFO] Memória secundária: " << tamanho_secundaria << " KB" << std::endl;
    if(tipo == 1)
        std::cout << "[INFO] Algoritmo de substituição: LRU" << std::endl;
    else
        std::cout << "[INFO] Algoritmo de substituição: Relógio " << std::endl;
};

int Gerenciador::criar_processo(int pid, int tamanho){
    if(tamanho_primaria + tamanho_secundaria - (memoria_primaria->espaco_ocupado + memoria_secundaria->espaco_ocupado +1)*tamanho_pagina < tamanho){
        std::cout << "[INFO] Processo " << pid << " não criado. Espaço insuficiente" << std::endl;
        return -1;
    }
    if(find_process(pid) != NULL){
        std::cout << "[INFO] Erro. Processo " << pid << "Já existe." << std::endl;
        return -1;
    }
    int qtd_paginas = calcula_paginas(tamanho);
    Processo *p = new Processo(pid, qtd_paginas);
    Processos.push_front(p);
    int pagina = 0;
    while(pagina < qtd_paginas){
        if(memoria_primaria->espaco_ocupado == memoria_primaria->tamanho){
            swap_out();
            continue;
        }
        int endereco_livre = memoria_primaria->get_endereco_livre();
        Pagina *nova_pagina = new Pagina(endereco_livre,pid);
        memoria_primaria->paginas.push_front(nova_pagina);
        memoria_primaria->espaco_ocupado++;
        p->tabela[pagina].endereco = endereco_livre;
        p->tabela[pagina].local = 1;
        pagina++;
        if(clock_pointer == this->memoria_primaria->paginas.end())
            clock_pointer = this->memoria_primaria->paginas.begin();
    }
    return 0;
        
};

int Gerenciador::escrever_processo(int pid, int endereco){
    ler_processo(pid,endereco);
    return 0;
}

int Gerenciador::ler_processo(int pid, int endereco){
    int pagina_logica = calcula_paginas(endereco) -1;
    Processo* processo = find_process(pid);
    if(processo == NULL){
        std::cout << "[INFO] Erro. Processo " << pid << "não existe." << std::endl;
        return -1;
    }
    if(pagina_logica >= processo->get_tamanho()){
        std::cout << "[INFO] Erro, página não encontrada." << std::endl;
        return -1;
    }
    int pagina_fisica = processo->tabela[pagina_logica].endereco;
    if(processo->tabela[pagina_logica].endereco == -1){
        std::cout << "[INFO] página virtual " << pagina_logica << " não se encontra na memória primária." << std::endl;
        if(memoria_primaria->espaco_ocupado == memoria_primaria->tamanho) // memoria cheia?
            swap_out();
        swap_in(pid);
        return 0;
    
    }
    for(auto it : memoria_primaria->paginas)
        if(it->get_endereco() == pagina_fisica){
            if(tipo == 1){
                memoria_primaria->paginas.remove(it);       // LRU move página referenciada para o início
                memoria_primaria->paginas.push_front(it);
            }else{
                it->setR(true);
            }
        }
    return 0;
}


int Gerenciador::calcula_paginas(int tamanho){
    if(tamanho % this->tamanho_pagina != 0)
        return (int)tamanho/this->tamanho_pagina +1;
    else
        return (int)tamanho/this->tamanho_pagina;
};

Processo* Gerenciador::find_process(int pid){
    for (auto it: Processos)
        if(it->get_pid() == pid)
            return it;
    return NULL;
}
void Gerenciador::swap_in(int pid){
    for(auto i : this->memoria_secundaria->paginas)
        if(i->get_pid() == pid){
            Pagina* p = i;
            this->memoria_secundaria->paginas.remove(i);
            this->memoria_secundaria->espaco_ocupado--;
            p->set_endereco(memoria_primaria->get_endereco_livre());
            this->memoria_primaria->paginas.push_front(p);
            this->memoria_primaria->espaco_ocupado++;
            return;
        }
    std::cout << "[INFO] swap_in ERRO, página não encontrada no disco." << std::endl;
    return;
}
void Gerenciador::swap_out(){
    Pagina* p;
    Processo* processo;
    int pid;
    if(tipo == 1){
        p = memoria_primaria->paginas.back();
        memoria_primaria->paginas.pop_back();
        memoria_primaria->espaco_ocupado--;
        pid = p->get_pid();
    }else{
        if(clock_pointer == this->memoria_primaria->paginas.end())
            clock_pointer = this->memoria_primaria->paginas.begin();
        while((*clock_pointer)->getR() != 0){
            (*clock_pointer)->setR(0);
            clock_pointer++;
            if(clock_pointer == this->memoria_primaria->paginas.end())
                clock_pointer = this->memoria_primaria->paginas.begin();
                
        }
        p = *clock_pointer;
        clock_pointer++;
        if(clock_pointer == this->memoria_primaria->paginas.end())
            clock_pointer = this->memoria_primaria->paginas.begin();
        memoria_primaria->paginas.remove(p);
        memoria_primaria->espaco_ocupado--;
        pid = p->get_pid();
    }
    processo = find_process(pid);
    for(int i = 0; i < processo->get_tamanho(); i++)
        if(processo->tabela[i].endereco == p->get_endereco()){
            std::cout << "[INFO] swap da ram para o disco na página virtual " << i << " relativa ao processo P" << processo->get_pid() << std::endl; 
            processo->tabela[i].endereco = -1;
            processo->tabela[i].local = 0;
            break;
        }
    if(memoria_secundaria->espaco_ocupado == memoria_secundaria->tamanho){
        std::cout << "[INFO] Erro ao fazer swap. Memória cheia." << std::endl;
        return;
    }
    memoria_secundaria->paginas.push_front(p);
    memoria_secundaria->espaco_ocupado++;
}

void Gerenciador::print_memoria_primaria(){
    std::system("clear");
    std::cout << "Tamanho memória principal: " << this->memoria_primaria->get_tamanho()*tamanho_pagina << " KB" << std::endl;
    std::cout << "Espaço ocupado: " << this->memoria_primaria->get_espaco_ocupado()*tamanho_pagina << " KB" << std::endl << std::endl;
    for(int i = 0; i < this->memoria_primaria->tamanho; i++)
        std::cout << i*tamanho_pagina << " KB  ";
    std::cout << std::endl << std::endl;
    for(int i = 0; i < this->memoria_primaria->tamanho; i++){
        for(auto it : this->memoria_primaria->paginas)
            if(it->get_endereco() == i){
                std::cout << "P"<< it->get_pid() << "   ";
                break;
            }
        std::cout << " ";
    }
        std::cout << std::endl << std::endl << std::endl;
    return;
}

void Gerenciador::print_memoria_secundaria(){
    std::system("clear");
    std::cout << "Tamanho secundaria: " << this->memoria_secundaria->get_tamanho()*tamanho_pagina << " KB" << std::endl;
    std::cout << "Espaço ocupado: " << this->memoria_secundaria->get_espaco_ocupado()*tamanho_pagina << " KB" << std::endl << std::endl;
    for(int i = 0; i < this->memoria_secundaria->tamanho; i++)
        std::cout << i*tamanho_pagina << " KB  ";
    std::cout << std::endl << std::endl;
    for(auto it : this->memoria_secundaria->paginas)
            std::cout << "P"<< it->get_pid() << "   ";
    std::cout << std::endl << std::endl << std::endl;
    return;
}

int Gerenciador::kill_processo(int pid){
    Processo* p = find_process(pid);
    if(p == NULL)
        return -1;
    delete p;
    for(auto it : this->memoria_primaria->paginas)
        if(it->get_pid() == pid){
            Pagina* pagina = it;
            it++;
            this->memoria_primaria->paginas.remove(pagina);
            this->memoria_primaria->espaco_ocupado--;
            delete pagina;
        }
    for(auto it : this->memoria_secundaria->paginas)
        if(it->get_pid() == pid){
            this->memoria_secundaria->paginas.remove(it);
            this->memoria_secundaria->espaco_ocupado--;

        }
    return 0;
}

Gerenciador::~Gerenciador(){
    delete this->memoria_primaria;
    delete this->memoria_secundaria;
    for(auto it : this->Processos)
        delete it;
}