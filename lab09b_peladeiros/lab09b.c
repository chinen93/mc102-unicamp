/* Nome: Pedro Hideaki Uiechi Chinen
   RA  : 175828
   Lab 09b - Peladeiros */
#include <stdio.h>
#include <stdlib.h>

#define DELTA -0.0001

int acharIndiceMaior(float *vetor, int tam);
void zerarColuna(float **tabela, int jogador, int jogadores);

int main(){
    int jogadores, capitoes;
    float **tabela, *medias;
    float mediaAux;
    int **times;
    int i, j, indice;

    /* Ler dados e alocar memoria  */
    scanf("%d %d", &jogadores, &capitoes);
    tabela=(float **)malloc(jogadores * sizeof(float *));
    for(i=0; i<jogadores; i++)
        tabela[i]=(float *)malloc(jogadores * sizeof(float));
    medias=(float *)malloc(jogadores * sizeof(float));
    times=(int **)malloc(capitoes * sizeof(int *));
    for(i=0; i<capitoes; i++)
        times[i]=(int *)malloc((jogadores/capitoes)
                                  * sizeof(int));
    
    for(i=0; i<jogadores; i++)
        for(j=0; j<jogadores; j++)
            scanf("%f", &tabela[i][j]);

    /* Calcular medias dos jogadores */
    for(j=0; j<jogadores; j++){
        mediaAux=0;
        for(i=0; i<jogadores; i++)
            mediaAux+=tabela[i][j];
        medias[j]=mediaAux/jogadores;
    }
    
    /* Escolher os capitoes
       Achar o indice e zerar a posicao onde ele estava
       Para nao ser escolhido novamente*/
    for(i=0; i<capitoes; i++){
        indice=acharIndiceMaior(medias, jogadores);
        times[i][0]=indice;
        zerarColuna(tabela, indice, jogadores);
        medias[indice]=-1.0;
    }

    /* Escolher o resto do time */
    for(i=1; i<jogadores/capitoes; i++){
        for(j=0; j<capitoes; j++){
            indice=acharIndiceMaior(tabela[times[j][0]], jogadores);
            times[j][i]=indice;
            zerarColuna(tabela, indice, jogadores);
        }
    }
    

    /* Exibir dados e desalocar memoria  */

    for(i=0; i<capitoes; i++){
        printf("Time %d: ",i+1);
        for(j=0; j<jogadores/capitoes-1; j++){
            printf("%d ", times[i][j]+1);
        }
        printf("%d", times[i][jogadores/capitoes-1]+1);
        printf("\n");
    }

    for(i=0; i<capitoes; i++)
        free(times[i]);
    free(times);
    free(medias);
    for(i=0; i<jogadores; i++)
        free(tabela[i]);
    free(tabela);
    return 0;
}

int acharIndiceMaior(float *vetor, int tam){
    int i, indice=0;
    for(i=0; i<tam; i++)
        if(vetor[indice]-vetor[i] < DELTA)
            indice=i;
    
    return indice;
}

void zerarColuna(float **tabela, int jogador, int jogadores){
    int i;
    for(i=0; i<jogadores; i++)
        tabela[i][jogador]=-1.0;
    
}
