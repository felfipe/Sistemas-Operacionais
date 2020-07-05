#ifndef _MEMORIA
#define _MEMORIA
#endif
#include <iostream>
#include <list>
#include "Pagina.h"
class Memoria{
    private:
        bool encontra_endereco(int endereco);
    public:
        Memoria(int tamanho);
        int tamanho;        // tamanho em paginas
        int espaco_ocupado; // espaco em paginas
        std::list<Pagina*> paginas;
        bool get_pagina(int pagina);
        void set_pagina(int pagina);
        void unset_pagina(int pagina);
        int get_tamanho();
        int get_espaco_ocupado();
        int get_endereco_livre();
        
};