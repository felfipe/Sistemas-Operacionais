#include <unistd.h>



int main(){
    char frase[50] = "This is a different Hello World.";
    write(0, &frase, 50);
    return 0;
}