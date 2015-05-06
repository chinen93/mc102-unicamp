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

int vetorNulo(int *vetor, int tam){
  int i;
  for(i=0; i<tam; i++)
    if(*(vetor+i) != 0)
      return FALSE;

  return TRUE;
}

void printResultado(int *vetor, int tam){
  int i, escreveu=FALSE;
  if(vetorNulo(vetor, tam))
    printf("0");

  else
    for(i=0; i<tam; i++)
      /* nao escreve os 0 a esquerda  */
      if (!(*(vetor+i) == 0 && !escreveu)){
        printf("%d", *(vetor+i));
        escreveu=TRUE;
      }
  
  
  
  printf("\n");
}

/* realiza a adicao n1+n2, armazendo o resultado em result */
void add(int *n1, int tam_n1, int *n2, int tam_n2, int *result) {
  int i;
  int pos1, pos2, posR;
  pos1=tam_n1-1;
  pos2=tam_n2-1;
  posR=tam_n1;

  /* somar as casas correspondentes */
  for(i=0; i<tam_n2; i++){
    /* se a soma for maior que 1 digito
       colocar o ultimo digito na posicao atual
       e incrementar a posicao a esquerda do resultado
    */
    if(*(n1+pos1) + *(n2+pos2) > 9){
      *(result+posR) += (*(n1+pos1) + *(n2+pos2))%10;
      *(result+posR-1) += 1;
    }else{
       *(result+posR) += *(n1+pos1) + *(n2+pos2);
    }

    pos1--;
    pos2--;
    posR--;
  }/*for(i=0; i<tam_n2; i++)*/
  for(i=0; i<tam_n1-tam_n2; i++){
    *(result+posR) += *(n1+pos1);
    pos1--;
    posR--;
  }
}

/* realiza a subtracao n1-n2, com n1>=n2, armazenando o resultado em result */
void substract(int *n1, int tam_n1, int *n2, int tam_n2, int *result) {
  int i, j;
  int pos1, pos2, posR;
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
      *(n1+pos1) += 10;
      for(j=1; j<tam_n1-i; j++){
        if(*(n1+pos1-j) == 0)
          *(n1+pos1-j) = 9;
        else{
          *(n1+pos1-j) =  *(n1+pos1-j)-1;
          break;
        }
      }
    }/*if(*(n1+pos1) < *(n2+pos2))*/

    /* efetua a subtracao */
    *(result+posR) = *(n1+pos1) - *(n2+pos2); 
    pos1--;
    pos2--;
    posR--;
  }/*for(i=0; i<tam_n2; i++)*/

  /* colocar as outras casa de n1 no resultado */
  for(i=0; i<tam_n1-tam_n2; i++){
    *(result+posR) = *(n1+pos1);
    pos1--;
    posR--;
  }
}

/* realiza a multiplicacao n1*n2, armazendo o resultado em result */
void multiply(int *n1, int tam_n1, int *n2, int tam_n2, int *result) {
    /*
      int i, j;
      int pos1, pos2, posR;
      int aux[1] = {1};

      pos2=tam_n2-1;
      posR=tam_n1+tam_n2-1;

      while(!vetorNulo(n2, tam_n2)){ 
      add(result, tam_n1+tam_n2-1, n1, tam_n1, result);
      substract(n2, tam_n2, aux, 1, n2);
      }
    */
    int i, j;
    int pos1, pos2, posR;

    pos2=tam_n2-1;
 
    for(i=0; i<tam_n2; i++){
	pos1=tam_n1-1;
	posR=tam_n1+tam_n2-1-i;
	for(j=0; j<tam_n2; j++){
	    if(*(n1+pos1) * *(n2+pos2) > 9){
		*(result+posR) += (*(n1+pos1) * *(n2+pos2))%10;
		*(result+posR-1) += (*(n1+pos1) * *(n2+pos2))/10;
	    }else
		*(result+posR) += *(n1+pos1) * *(n2+pos2);
	    pos1--;
	    posR--;
	}
	pos2--;
    }/*for(i=0; i<tam_n2; i++)*/
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
