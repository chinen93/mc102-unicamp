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
    printf("%d;", *(vetor+i));
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
}

/* realiza a subtracao n1-n2, com n1>=n2, armazenando o resultado em result */
void substract(int *n1, int tam_n1, int *n2, int tam_n2, int *result) {
  int i, j;
  int pos1, pos2, posR;

  printVetor(n1, tam_n1);
  printVetor(n2, tam_n2);  
  pos1=tam_n1-1;
  pos2=tam_n2-1;
  posR=tam_n1-1;
  
  /* subtrair as casas correspondentes */
  for(i=0; i<tam_n2; i++){
    /* se a posicao de n1 for menor que n2
       pegar emprestado da posicao a esquerda de n1
       se a posicao for 0 tranformar em 9
       e continuar procurando um valor diferente de 0
    */
    if(*(n1+pos1) < *(n2+pos2)){
      printf("{%d %d}\n", pos1, tam_n1-i-1);
      /*TODO a segunda vez não funciona*/
      for(j=i+1; j<tam_n1-i-1; j++){
	if(*(n1+pos1-j) == 0)
	  *(n1+pos1-j) = 9;
	else{
	  *(n1+pos1-j) =  *(n1+pos1-j)-1;
	  break;
	}
      }

      *(n1+pos1) += 10;
      printVetor(n2, tam_n2);
      printVetor(n1, tam_n1);
    }/*if(*(n1+pos1) < *(n2+pos2))*/

    /* efetua a subtracao */
    *(result+posR) = *(n1+pos1) - *(n2+pos2); 

    pos1--;
    pos2--;
    posR--;
  }/*for(i=0; i<tam_n2; i++)*/

  
  /* colocar as outras casa de n1 no resultado */
  for(i=0; i<tam_n1-tam_n2-1; i++){
    *(result+posR) = *(n1+pos1);
    pos1--;
    posR--;
  }

  printVetor(result, tam_n1);
}

/* realiza a multiplicacao n1*n2, armazendo o resultado em result */
void multiply(int *n1, int tam_n1, int *n2, int tam_n2, int *result) {
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
  printf("--%c--\n\n",comando);
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
      /* *(resultado+i) = 0; */
    }
    substract(x, tamX, y, tamY, resultado);
    printResultado(resultado, tamX);
    break;
  case 'M':
    resultado=malloc((tamX+tamY) * sizeof(int));
    for(i=0; i<(tamX+tamY); i++){
      *(resultado+i) = 0;
    }
    multiply(x, tamX, y, tamY, resultado);
    printResultado(resultado, tamX+tamY);
    break;
  }
  
  free(x);
  free(y);
  free(resultado);
  return 0;
}
