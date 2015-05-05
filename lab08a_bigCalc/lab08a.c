/* Laboratorio 08a - BigCalc
 * Nome: Pedro Hideaki Uiechi Chinen 
 * RA:   175828
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define TRUE 1
#define FALSE 0

void printVetor(int *vetor, int tam){
  int i;
  printf("[");
  for(i=0; i<tam; i++){
    printf("%d", *(vetor+i));
  }
  printf("]\n");
}

void printResultado(int *vetor, int tam){
  int i, escreveu=FALSE;
  
  for(i=0; i<tam; i++){
    /* nao escreve os 0 a esquerda  */
    if (!(*(vetor+i) == 0 && !escreveu)){
      printf("%d", *(vetor+i));
      escreveu=TRUE;
    }
  }
  
  if(!escreveu)
    printf("0");
  
  printf("\n");
}

/* realiza a adicao n1+n2, armazendo o resultado em result */
void add(int *n1, int tam_n1, int *n2, int tam_n2, int *result) {
  int i, j;
  int pos1, pos2, posR, aux;
  printVetor(n1, tam_n1);
  printVetor(n2, tam_n2);
  for(i=0; i<tam_n2; i++){
    pos1 = tam_n1-i-1;
    pos2 = tam_n2-i-1;
    posR = tam_n1-i;

    /*somar as duas parcelas*/
    aux = *(n1+pos1) + *(n2+pos2);
    if(aux >= 10){
      *(result+posR) += aux%10;
      *(result+posR-1) += 1;
    }else
      *(result+posR) += aux;
  }/*for(i=0; i<tam_n2; i++)*/
  for(i=0; i<tam_n1-tam_n2; i++){
    pos1 = tam_n1-i-2;
    *(result+posR) =  *(n1+pos1);
  }
  printVetor(result, tam_n1+1);
}

/* realiza a subtracao n1-n2, com n1>=n2, armazenando o resultado em result */
void substract(int *n1, int tam_n1, int *n2, int tam_n2, int *result) {
  int i, j;
  int pos1, pos2;
  for(i=0; i<tam_n2; i++){
    /* Subitrai unidade/unidade dezena/dezena e assim por diante */
    pos1 = tam_n1-i-1;
    pos2 = tam_n2-i-1;
    /* Subtrai normalmente caso o valor de n2 seja menor que n1  */
    if(*(n1+pos1) < *(n2+pos2)){
      /* Caso contrario, subtrair 1 no valor da esquerda de n1 
         caso o valor seja 0, substitui-lo por 9 e ir mais a esquerda*/
      for(j=1; j<=pos1; j++){
	if(*(n1+pos1-j) == 0)
	  *(n1+pos1-j)=9;
	else	  
	  *(n1+pos1-j) -= 1;
      }
      *(n1+pos1) = *(n1+pos1)+pow(10, i+1);
    }
    /* efetua a subtracao */
    *(result+pos1) =  *(n1+pos1) - *(n2+pos2);
  }/*for(i=0; i<tam_n2; i++)*/
  /* Coloca as posicoes de n1, caso nao exista correspondente em n2  */
  for(i=0;i<tam_n1-tam_n2;i++){
    pos1 = tam_n1-i-2;
    *(result+pos1) =  *(n1+pos1);
  }
}

/* realiza a multiplicacao n1*n2, armazendo o resultado em result */
void multiply(int *n1, int tam_n1, int *n2, int tam_n2, int *result) {
  printVetor(n1, tam_n1);
  printVetor(n2, tam_n2);
}

int main() {
  int *x, *y, *resultado;
  int tamX, tamY;
  char comando;
  int i;
  char aux;

  
  scanf("%d %d %c", &tamX, &tamY, &comando);
  x=malloc(tamX * sizeof(int));
  for(i=0; i<tamX; i++){
    scanf(" %c", &aux);
    *(x+i)= aux-'0';
  }
  y=malloc(tamY * sizeof(int));
  for(i=0; i<tamY; i++){
    scanf(" %c", &aux);
    *(y+i)= aux-'0';
  }
  
  switch(comando){
  case 'A':
    resultado=malloc((tamX+1) * sizeof(int));
    for(i=0; i<tamX+1; i++){
      *(resultado+i) = 0;
    }
    add(x, tamX, y, tamY, resultado);
    printResultado(resultado, tamX+1);
    break;
  case 'S':
    resultado=malloc(tamX * sizeof(int));
    for(i=0; i<tamX; i++){
      *(resultado+i) = 0;
    }
    substract(x, tamX, y, tamY, resultado);
    printResultado(resultado, tamX);
    break;
  case 'M':
    resultado=malloc(tamX * sizeof(int));
    for(i=0; i<tamX; i++){
      *(resultado+i) = 0;
    }
    multiply(x, tamX, y, tamY, resultado);
    printResultado(resultado, tamX);
    break;
  }
  
  free(x);
  free(y);
  free(resultado);
  return 0;
}
