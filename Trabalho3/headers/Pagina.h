#ifndef _PAGINA
#define _PAGINA
#endif

class Pagina{
    private:
        int pid;
        int endereco;
        bool R; // indica se a pagina foi referenciada (clock)
    public:
        Pagina(int endereco, int pid);
        int get_endereco();
        void set_endereco(int endereco);
        int get_pid();
        int set_pid(int pid);
};