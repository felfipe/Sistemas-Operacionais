#include <iostream>
#include <fstream>
#include <string>
#include "headers/Gerenciador.h"
using namespace std;
int main(){
    char operador, opcao;
    string PID, endereco;
    ifstream file("entrada.txt");
    if(file.is_open()){
        file.ignore(256,'\n');
        cin.rdbuf(file.rdbuf());
    }
    Gerenciador *gerenciador = new Gerenciador(16, 16, 4);
    while(true){
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
            case 'E':
            // END
            return 0;
            break;
            
        }
        
    }
    file.close();
    return 0;
}