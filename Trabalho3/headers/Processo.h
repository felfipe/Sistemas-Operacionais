#ifndef _PROCESSO
#define _PROCESSO
#endif

class Processo{
    public:
        struct elemento{
            bool     local; // bit que identifica se a página está na primária ou disco.
            int endereco;
        };
        typedef struct elemento Elemento;
        Elemento *tabela; 
        Processo(int pid, int tamanho);
        ~Processo();
        int  get_pid();
        int  get_tamanho();
        void set_pid(int pid);
        void set_tamanho(int tamanho);
        
    private:
        int pid;
        int tamanho;

};