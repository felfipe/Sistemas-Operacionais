#ifndef _GERENCIADOR
#define _GERENCIADOR
#include "Memoria.h"
#include "Processo.h"
#include <iostream>
#include <list>
class Gerenciador{
    private:
        std::list<Processo*> Processos;
        int tamanho_primaria, tamanho_secundaria, tamanho_pagina, espaco_ocupado;
        Memoria* memoria_primaria;
        Memoria* memoria_secundaria;
        int calcula_paginas(int tamanho);
        Processo* find_process(int pid);
        void print_memoria(Memoria* memoria);

    public:
        Gerenciador(int tamanho_primaria, int tamanho_secundaria, int tamanho_pagina);
        int criar_processo(int pid, int tamanho);
        int excluir_processo(int pid);
        int ler_processo(int pid, int endereco);
        int escrever_processo(int pid, int endereco);
        int IO_func(int pid, int endereco);
        int CPU_func(int pid, int endereco);
        void swap_out();
        void swap_in(int pid);
        void print_memoria_primaria();
        void print_memoria_secundaria();
        void print_tabela_processo(int pid);
};
#endif