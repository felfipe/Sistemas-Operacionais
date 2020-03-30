#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define TAM 500  // DEFINE O TAMANHO DA MATRIX QUADRADA
#define FAIXA 100  // DEFINE A FAIXA DE VALORES DOS ELEMENTOS
/*
CRIA UMA MATRIZ ALEATÓRIA DE TAM ELEMENTOS.
*/
double** create_rand_matrix(int tam){
  double **x = (double**)calloc(tam, sizeof(double));
  for(int i = 0; i < tam; i++)
    x[i] = (double*)calloc(tam, sizeof(double));
  for(int i = 0; i < tam; i++)
    for(int j = 0; j < tam; j++)
      x[i][j] = rand()%FAIXA;
  return x;
}


/*
  LIBERA A MATRIZ
*/
void free_matrix(double** matrix, int tam){
  for(int i = 0; i < tam; i++)
    free(matrix[i]);
}


/*
  Multiplica duas matrizes quadradas, gerando uma terceira
*/
double** multiplica_matriz(double** matrix1, double** matrix2){
  double** matrix3 = create_rand_matrix(TAM);
  for(int i = 0; i < TAM; i++){
    for(int j = 0; j < TAM; j++){
      double soma = 0;
      for(int k = 0; k < TAM; k++){
        soma+= matrix1[i][k]*matrix2[k][j];
        
      }
      matrix3[i][j] = soma;
    }
  }
  return matrix3;
}
/*
 Este programa gera 2 matrizes aleatórias de ordem TAM e faz a multiplicação delas criando uma terceira matriz.
 Tudo isso envolve muita conta para a cpu e nenhuma interação de E/S. Logo, podemos considerar este programa como sendo CPU-BOUND.
*/
int main(){
  srand(time(NULL));
  double** matriz1 = create_rand_matrix(TAM);
  double** matriz2 = create_rand_matrix(TAM);
  double** resultado = multiplica_matriz(matriz1,matriz2);
  free_matrix(matriz1, TAM);
  free_matrix(matriz2, TAM);
  free_matrix(resultado, TAM);
  return 0;
}