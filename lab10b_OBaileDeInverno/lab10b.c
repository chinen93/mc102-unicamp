/* Nome: Pedro Hideaki Uiechi Chinen
   Ra  : 175828
   Laboratorio 10b - O Baile de Inverno
  */

#include <stdio.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0

void printVetor(int *vetor, int tam){
    int i;
    for(i=0; i<tam; i++)
        printf("[%d]", vetor[i]);
    printf("\n");
}


void insertionSort(int *A, int tam) { 
   int i, j, eleito;
   for (i=1; i<tam; i++) {
       eleito=A[i];
       j=i;
       while ((j > 0) && (A[j-1] > eleito)) {
           A[j]=A[j-1];
           j=j-1;
       }
       A[j]=eleito;
   }
}

int main(){
    int numH, numM, diffMax, diff;
    int *homens, *mulheres; 
    int i, j, cont=0;
    int achouPar;
    
    /* Ler dados e alocar memoria  */
    scanf("%d %d %d", &numH, &numM, &diffMax);

    homens=(int *)malloc(numH * sizeof(int));
    mulheres=(int *)malloc(numM * sizeof(int));
    
    for(i=0; i<numH; i++){
        scanf("%d",&homens[i]);
    }
    
    for(i=0; i<numM; i++){
        scanf("%d",&mulheres[i]);
    }

    /* Ordenar vetores e trabalhar com eles  */
    insertionSort(homens, numH);
    insertionSort(mulheres, numM);

    for(i=0; i<numH; i++){
        achouPar=FALSE;
        for(j=0; j<numM && !achouPar; j++){
            if(mulheres[j]!=-1){
                diff=homens[i]-mulheres[j];
                if(diff < 0)
                    diff = diff * -1;
                if(diff <= diffMax){
                    mulheres[j]=-1;
                    cont++;
                    achouPar=TRUE;
                }
            }
        }
    }
    
    /* Escrever resultado */
    printf("Numero maximo de duplas equilibradas = %d\n",cont);
    return 0;
}
