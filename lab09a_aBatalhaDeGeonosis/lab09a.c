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

int main(){
    int linhas, colunas;
    int **campo;
    int horizontal, vertical, diagonal13, diagonal24;
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

    /* Fazer as contas antes de posicionar o AT-TE */
    
    
    /* Posicionar o AT-TE  */
    for(i=0; i<linhas; i++)
        for(j=0; j<colunas; j++){
            if(!campo[i][j]){
                droids=0;
                disparos=0;
                /* Calcula a quantidade de droids em cada sentido  */
                horizontal=dispHorizontal(campo, i, colunas);
                vertical=dispVertical(campo, j, linhas);
                diagonal13=dispDiagonal13(campo, i, j, linhas, colunas);
                diagonal24=dispDiagonal24(campo, i, j, linhas, colunas);
                if(horizontal){
                    disparos++;
                    droids+=horizontal;
                }

                if(vertical){
                    disparos++;
                    droids+=vertical;
                }

                if(diagonal13){
                    disparos++;
                    droids+=diagonal13;
                }

                if(diagonal24){
                    disparos++;
                    droids+=diagonal24;
                }

                /* Verifica se a posicao atual eh a melhor entre todas
                   as posicoes */
                if(droids > melhor[2]){
                    melhor[0] = i;
                    melhor[1] = j;
                    melhor[2] = droids;
                    melhor[3] = disparos;
                }
                else if(melhor[2] == droids){
                    if(disparos < melhor[3]){
                        melhor[0] = i;
                        melhor[1] = j;
                        melhor[3] = disparos;
                    }
                    else if(disparos == melhor[3]){
                        if(i < melhor[0]){
                            melhor[0] = i;
                            melhor[1] = j;
                        }
                        else if(i == melhor[0] && j < melhor[1]){
                            melhor[1] = j;
                        }
                    }
                }
            }/*if(!campo[i][j])*/
        }/*for(j=0; j<colunas; j++)*/

    printf("Posicao = (%d,%d)\n", melhor[0], melhor[1]);
    printf("Droids = %d\n",melhor[2]);
    printf("Disparos = %d\n", melhor[3]);
    
    /* Desalocar Memoria */    
    for(i=0; i<linhas; i++)
        free(campo[i]);
    free(campo);
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
    for(k=i, l=j; k>=0 && l<colunas; k--, l++)
        droids+=campo[k][l];
    for(k=i, l=j; k<linhas && l>=0; k++, l--)
        droids+=campo[k][l];
    return droids;
}
int dispDiagonal24(int *campo[MAX],
                   int i, int j, int linhas, int colunas){
    int k, l, droids=0;
    for(k=i, l=j; k<linhas && l<colunas; k++, l++)
        droids+=campo[k][l];
    for(k=i, l=j; k>=0 && l>=0; k--, l--)
        droids+=campo[k][l];
    return droids;
}
