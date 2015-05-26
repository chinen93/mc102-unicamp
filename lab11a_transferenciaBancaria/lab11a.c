/* Nome: Pedro Hideaki Uiechi Chinen
   RA  : 175828
   Laboratorio 11a - Tranferencia Bancaria
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAMCONTA 13
#define TAMNOME 21

#define TRUE 1
#define FALSE 0

#define DELTA 0.001
typedef struct{
  char conta[TAMCONTA];
  char nome[TAMNOME];
  char sobrenome[TAMNOME];
  float saldo;
} Conta;

Conta lerConta();
void tranferencia(Conta *banco, int numContas);
void printConta(Conta conta);

int main(){
  int numContas, numTransf;
  Conta *banco;
  int i, j;

  /* Ler dados e alocar memoria*/
  scanf("%d %d", &numContas, &numTransf);
  banco=malloc(numContas * sizeof(Conta));
  for(i=0; i<numContas; i++){
    banco[i]=lerConta();
  }

  for(i=0; i<numTransf; i++){
    tranferencia(banco, numContas);
  }

  /* Escrever resultado  */
  for(i=0; i<numContas; i++){
    printConta(banco[i]);
  }
  
  free(banco);
  return 0;
}


Conta lerConta(){
  Conta retorno;
  
  scanf("%s", retorno.conta);
  scanf("%s", retorno.nome);
  scanf("%s", retorno.sobrenome);
  scanf("%f", &retorno.saldo);
  printConta(retorno);
  return retorno;
}
void tranferencia(Conta *banco, int numContas){
  int  tranferiu=FALSE;
  char lixo[3];
  char origem[TAMCONTA], destino[TAMCONTA];
  float quanto;
  int i, j;

  scanf("%s", origem);
  scanf("%s", lixo);
  scanf("%f", &quanto);
  scanf("%s", lixo);
  scanf("%s", destino);

  /*
    TESTE 8 - problema de precisao
< [53341@2864 ->  266.279999 ->  12866@8834]
< 53341@2864 Felipe Mendes 266.28
---
> 53341@2864 Felipe Mendes 0.00
   */

  printf("\n[%s ->  %f ->  %s]\n", origem, quanto, destino);
  for(i=0; i<numContas && !tranferiu; i++){
    if(strcmp(banco[i].conta, origem) == 0 && banco[i].saldo-quanto > DELTA)
      for(j=0; j<numContas && !tranferiu; j++){
        if(strcmp(banco[j].conta, destino) == 0){
          tranferiu=TRUE;
          banco[j].saldo+=quanto;
          banco[i].saldo-=quanto;
        }
      }
  }
}
void printConta(Conta conta){
  printf("%s ",conta.conta);
  printf("%s ",conta.nome);
  printf("%s ",conta.sobrenome);
  printf("%.2f\n",conta.saldo);
}
