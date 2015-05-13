/* Nome: Pedro Hideaki Uiechi Chinen
   RA  : 175828
   Laboratorio 09a - A Batalha de Geonosis
  */

#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define MAX 50

int dispHorizontal(int *campo[MAX],
                   int i, int colunas);
int dispVertical(int *campo[MAX],
                 int j, int linhas);
int dispDiagonal13(int *campo[MAX],
                    int i, int j, int linhas, int colunas);
int dispDiagonal24(int *campo[MAX],
                    int i, int j, int linhas, int colunas);


void printVetor(int *vetor, int tam){
    int i;
    for(i=0; i<tam; i++)
        printf("[%d]", vetor[i]);
    printf("\n");
}
void printMatriz(int *matriz[MAX], int linhas, int colunas){
    int i, j;
    for(i=0; i<linhas; i++){
        for(j=0; j<colunas; j++)
            printf("{%d}",matriz[i][j]);
        printf("\n");
    }
    printf("\n");
}

int main(){
    int linhas, colunas;
    int **campo;
    int *horizontal, *vertical, *diagonal13, *diagonal24;
    int i, j;
    int disparos, droids;
    /* i, j, droids, disparos */
    int melhor[4] = {0, 0, 0, 0};
    
    /* Ler dados e Alocar memoria*/
    scanf("%d %d", &linhas, &colunas);
    campo=(int **)malloc(linhas * sizeof(int *));
    for(i=0; i<linhas; i++)
        campo[i] = (int *)malloc(colunas * sizeof(int));
    for(i=0; i<linhas; i++)
        for(j=0; j<colunas; j++)
            scanf(" %d", &campo[i][j]);

    horizontal=(int *)malloc(colunas * sizeof(int));
    vertical=(int *)malloc(linhas * sizeof(int));
    diagonal13=(int *)malloc((linhas + colunas-1) * sizeof(int));
    diagonal24=(int *)malloc((linhas + colunas-1) * sizeof(int));

    /* Fazer as contas antes de posicionar o AT-TE */
    for(i=0; i<linhas; i++)
        horizontal[i] = dispHorizontal(campo,
                                       i, colunas);    
    for(i=0; i<colunas; i++)
        vertical[i] = dispVertical(campo,
                                   i, linhas);
  
    for(j=0; j<colunas; j++)
        diagonal13[j] = dispDiagonal13(campo,
                                       0, j, linhas, colunas);
    for(i=1; i<linhas; i++)
        diagonal13[colunas-1+i] = dispDiagonal13(campo,
                                       i, colunas-1, linhas, colunas);
    
    for(i=0; i<linhas; i++)
        diagonal24[i] = dispDiagonal24(campo,
                                       i, colunas-1, linhas, colunas);
    for(j=1; j<colunas; j++)
        diagonal24[linhas-1+j] = dispDiagonal24(campo,
                                              linhas-1, colunas-1-j,
                                              linhas, colunas);

    printf("\n");
    printVetor(diagonal13, linhas+colunas-1);
    printVetor(diagonal24, linhas+colunas-1);
    printf("\n");
    printMatriz(campo, linhas, colunas);
    
    
    /* Posicionar o AT-TE  */
    for(i=0; i<linhas; i++)
        for(j=0; j<colunas; j++){
            if(!campo[i][j]){
                droids=0;
                disparos=0;
                if(horizontal[i]){
                    printf("hor = %d\n",i);
                    disparos++;
                    droids+=horizontal[i];
                }

                if(vertical[j]){
                    printf("ver = %d\n",j);
                    disparos++;
                    droids+=vertical[j];
                }

                if(diagonal13[i+j]){
                    printf("d13 = %d\n",i+j);
                    disparos++;
                    droids+=diagonal13[i+j];
                }

                if(diagonal24[i-j+colunas-1]){
                    printf("d24 = %d\n",i-j+colunas-1);
                    disparos++;
                    droids+=diagonal24[i-j+colunas-1];
                }

                if(droids > melhor[2]){
                    melhor[0] = i;
                    melhor[1] = j;
                    melhor[2] = droids;
                    melhor[3] = disparos;
                }
                else if(melhor[2] == droids){
                    if(i <melhor[0]){
                        melhor[0] = i;
                        melhor[1] = j;
                        melhor[2] = droids;
                        melhor[3] = disparos;
                    }
                    else if(i == melhor[0] && j < melhor[1]){
                        melhor[1] = j;
                        melhor[2] = droids;
                        melhor[3] = disparos;
                    }
                }
                printVetor(melhor, 4);
            }/*if(!campo[i][j])*/
        }/*for(j=0; j<colunas; j++)*/


    printf("Posicao = (%d,%d)\n", melhor[0], melhor[1]);
    printf("Droids = %d\n",melhor[2]);
    printf("Disparos = %d\n", melhor[3]);
    
    /* Desalocar Memoria */    
    for(i=0; i<linhas; i++)
        free(campo[i]);
    free(campo);
    free(horizontal);
    free(vertical);
    free(diagonal13);
    free(diagonal24);
    return 0;
}


int dispHorizontal(int *campo[MAX],
                   int i, int colunas){
    int k, droids=0;
    for(k=0; k<colunas; k++)
        droids+=campo[i][k];
    return droids;
}
int dispVertical(int *campo[MAX],
                 int j, int linhas){
    int k, droids=0;
    for(k=0; k<linhas; k++)
        droids+=campo[k][j];
    return droids;
}
int dispDiagonal13(int *campo[MAX],
                   int i, int j, int linhas, int colunas){
    int k, l, droids=0;
    k=i+j;
    l=0;
    if(k>linhas-1){
        k=linhas-1;
        l=i+j-linhas;
    }
    while(k>=0 && l<colunas){
        droids+=campo[k][l];
        k--;
        l++;
    }
    return droids;
}
int dispDiagonal24(int *campo[MAX],
                   int i, int j, int linhas, int colunas){
    int k, l, droids=0;
    k=0;
    l=-(i-j);
    if(l<0){
        k=i-j;
        l=0;
    }
    while(k<linhas && l<colunas){
        droids+=campo[k][l];
        k++;
        l++;
    }
    return droids;
}
