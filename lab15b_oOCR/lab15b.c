/* Nome: Pedro Hideaki Uiechi Chinen
   RA  : 175828
   email: chinen93@gmail.com
   Laboratorio 15 b - O o CR 
*/

#include <stdio.h>
#include <stdlib.h>

int troca(int *a, int *b);
void ordenar(int *vet, int inicio, int fim);

printVetor(int *vet, int inicio, int fim){
    int i;
    for(i<inicio; i<fim; i++)
        printf("{%d}", vet[i]);

    printf("\n");
}

int main(){
    int numBlocos;
    int *permutacao;
    int i, cont=0;
    
    scanf("%d", &numBlocos);
    permutacao=malloc(numBlocos * sizeof(int));
    for(i=0; i<numBlocos; i++)
        scanf("%d", &permutacao[i]);
    printVetor(permutacao, 0, numBlocos);

    printVetor(permutacao, 0, numBlocos);
    printf("%d\n", cont);
    free(permutacao);
    return 0;
}

int troca(int *a, int *b){
    int aux=*a;
    *a=*b;
    *b=aux;
    return 1;
}

void ordenar(int *vet, int inicio, int fim){
    int i, j;
    int menor=vet[inicio];
    if(fim-incio==2){
        for(i=inicio; i<=fim; i++)
            if(vet[i]<menor)
                menor=vet[i];
        
    }
            
        
    
}
