#include <iostream>
#include <fstream>
#include <string>
#include "headers/Gerenciador.h"
using namespace std;
int main(){
    int tamanho_pagina, paginas_primaria, paginas_secundaria,tipo;
    char operador, opcao;
    string PID, endereco;
    ifstream file("entrada.txt");
    if(file.is_open()){
        file.ignore(256,'\n');
        cin.rdbuf(file.rdbuf());
    }
    cout << "Digite o tamanho da página (KB) : ";
    cin >> tamanho_pagina;
    cout << endl << "Digite a quantidade de páginas na memória primária: ";
    cin >> paginas_primaria;
    cout << endl << "Digite a quantidade de páginas na memória secundária: ";
    cin >> paginas_secundaria;
    cout << endl << "Escolha o algoritmo de substitução(0 - relógio, 1 - LRU): ";
    cin >> tipo;
    system("clear");
    Gerenciador *gerenciador = new Gerenciador(tamanho_pagina*paginas_primaria, tamanho_pagina*paginas_secundaria, tamanho_pagina, tipo);
    while(true){
        cout << endl << "Comando (H - help): ";
        cin >> operador;
        if(operador == 'E')
            return 0;
        switch(operador){
            case 'C':
                cin >> PID;
                cin >> endereco;
                gerenciador->criar_processo(stoi(PID),stoi(endereco));
            break;
            case 'R':
                cin >> PID;
                cin >> endereco;
                gerenciador->ler_processo(stoi(PID),stoi(endereco));
            break;
            case 'W':
                cin >> PID;
                cin >> endereco;
                gerenciador->escrever_processo(stoi(PID),stoi(endereco));
            break;
            case 'P':
            cin >> opcao;
            if(opcao == '1')
                gerenciador->print_memoria_primaria();
            if(opcao == '2')
                gerenciador->print_memoria_secundaria();
            break;
            case 'I':
            // I/O process
            break;
            case 'K':
                cin >> PID;
                gerenciador->kill_processo(stoi(PID));
            case 'H':
                system("clear");
                cout << "\tC pid size(KB)     - cria um processo (Ex: C 1 7)" << endl;
                cout << "\tR pid adress       - leitura em memória de um processo (Ex: R 3 7)" << endl;
                cout << "\tW pid adress       - escrita em memória de um processo (Ex: W 4 5)" << endl;
                cout << "\tI pid device       - realiza uma operação I/O de um processo (Ex: I 3 2)" << endl;
                cout << "\tU pid instruction  - executa instrução de um processo na CPU (Ex: U 3 8)" << endl;
                cout << "\tP 1                - printa na tela a memória primária" << endl;
                cout << "\tP 2                - printa na tela a memória secundária" << endl;
                cout << "\tH                  - Menu de ajuda" << endl;
                cout << "\tE                  - Fecha o simulador" << endl;
                break;
            case 'E':
            // END
                return 0;
            break;
            
        }
        
    }
    file.close();
    return 0;
}