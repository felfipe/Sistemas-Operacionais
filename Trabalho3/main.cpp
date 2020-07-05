#include <iostream>
#include <fstream>
#include <string>
#include "headers/Gerenciador.h"
using namespace std;
int main(){
    char operador;
    string PID, endereco;
    ifstream file("entrad1a.txt");
    if(file.is_open()){
        file.ignore(256,'\n');
        cin.rdbuf(file.rdbuf());
    }
    Gerenciador *gerenciador = new Gerenciador(16, 16, 4);
    while(true){
        cin >> operador;
        if(operador == 'E')
            return 0;
        cin >> PID;
        cin >> endereco;
        switch(operador){
            case 'C':
                gerenciador->criar_processo(stoi(PID),stoi(endereco));
            break;
            case 'R':
                gerenciador->ler_processo(stoi(PID),stoi(endereco));
            break;
            case 'W':
                gerenciador->escrever_processo(stoi(PID),stoi(endereco));
            break;
            case 'P':
            // CPU-func
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