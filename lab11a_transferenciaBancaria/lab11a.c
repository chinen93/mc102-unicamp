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

#define DELTA -0.0000001

typedef struct{
    char conta[TAMCONTA];
    char nome[TAMNOME];
    char sobrenome[TAMNOME];
    double saldo;
} Conta;

Conta lerConta();
void tranferencia(Conta *banco, int numContas);
void printConta(Conta conta);

int main(){
    int numContas, numTransf;
    Conta *banco;
    int i;

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
    scanf("%lf", &retorno.saldo);
    return retorno;
}
void tranferencia(Conta *banco, int numContas){
    int  tranferiu=FALSE;
    char lixo[3];
    char origem[TAMCONTA], destino[TAMCONTA];
    double quanto;
    int i, j;

    scanf("%s", origem);
    scanf("%s", lixo);
    scanf("%lf", &quanto);
    scanf("%s", lixo);
    scanf("%s", destino);
    
    for(i=0; i<numContas && !tranferiu; i++){
        /* percorre as conta bancarias para ver se o endereco de origem existe
           e tem saldo maior que a quantidade tranferida*/
        if(strcmp(banco[i].conta, origem) == 0){
            if(banco[i].saldo-quanto >= DELTA){
                /* verifica se a conta de destino existe */
                for(j=0; j<numContas && !tranferiu; j++){
                    if(strcmp(banco[j].conta, destino) == 0){
                        tranferiu=TRUE;
                        banco[j].saldo+=quanto;
                        banco[i].saldo-=quanto;
                    }
                }
            }else{
                /* tranferencia nao ocorrera pois a 
                   origem nao tem o dinheiro  */
                tranferiu=TRUE;
            }
        }
    }
}
void printConta(Conta conta){
    printf("%s ",conta.conta);
    printf("%s ",conta.nome);
    printf("%s ",conta.sobrenome);
    printf("%.2lf\n",conta.saldo);
}
