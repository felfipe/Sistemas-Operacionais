#include "headers/Gerenciador.h"

Gerenciador::Gerenciador(int tamanho_primaria, int tamanho_secundaria, int tamanho_pagina){
    this->tamanho_primaria = tamanho_primaria;
    this->tamanho_secundaria = tamanho_secundaria;
    this->tamanho_pagina = tamanho_pagina;
    this->espaco_ocupado = 0;
    memoria_primaria = new Memoria(calcula_paginas(tamanho_primaria));
    memoria_secundaria = new Memoria(calcula_paginas(tamanho_secundaria));
};

int Gerenciador::criar_processo(int pid, int tamanho){
    if(tamanho_primaria + tamanho_secundaria - espaco_ocupado < tamanho){
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
    }
    return 0;
        
};

int Gerenciador::ler_processo(int pid, int endereco){
    if(find_process(pid) == NULL){
        std::cout << "[INFO] Erro. Processo " << pid << "não existe." << std::endl;
        return -1;
    }
    if(endereco )
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
void Gerenciador::swap_out(){
    Pagina* p = memoria_primaria->paginas.back();
    memoria_primaria->paginas.pop_back();
    memoria_primaria->espaco_ocupado--;
    int pid = p->get_pid();
    Processo* processo = find_process(pid);
    for(int i = 0; i < processo->get_tamanho(); i++)
        if(processo->tabela[i].endereco == p->get_endereco()){
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