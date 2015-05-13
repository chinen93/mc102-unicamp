/* Nome: Pedro Hideaki Uiechi Chinen
   RA  : 175828
   Laboratorio 09a - A Batalha de Geonosis
  */

#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define MAX 50

int dispHorizontal(int campo[MAX][MAX],
                   int i, int colunas);
int dispVertical(int campo[MAX][MAX],
                 int j, int linhas);
int dispDiagonal13(int campo[MAX][MAX],
                    int i, int j, int linhas, int colunas);
int dispDiagonal24(int campo[MAX][MAX],
                    int i, int j, int linhas, int colunas);

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
        campo[i] = (int)malloc(colunas * sizeof(int));
    for(i=0; i<linhas; i++)
        for(j=0; j<colunas; j++)
            scanf(" %d", &campo[i][j]);

    horizontal=(int *)malloc(colunas * sizeof(int));
    vertical=(int *)malloc(linhas * sizeof(int));
    diagonal13=(int *)malloc((linhas + colunas-1) * sizeof(int));
    diagonal24=(int *)malloc((linhas + colunas-1) * sizeof(int));

    /* Fazer as contas antes de posicionar o AT-TE */
    for(i=0; i<linhas; i++)
        horizontal[i] = dispHorizontal(campo[MAX][MAX],
                                       i, linhas, colunas);    
    for(i=0; i<colunas; i++)
        vertical[i] = dispVertical(campo[MAX][MAX],
                                   i, linhas, colunas);
  
    for(j=0; j<colunas; j++)
        diagonal13[i] = dispDiagonal13(campo[MAX][MAX],
                                       0, i, linhas, colunas);
    for(i=1; i<linhas; i++)
        diagonal13[colunas+i] = dispDiagonal13(campo[MAX][MAX],
                                       i, colunas-1, linhas, colunas);
    
    for(i=0; i<linhas; i++)
        diagonal24[i] = dispDiagonal13(campo[MAX][MAX],
                                       i, colunas-1, linhas, colunas);
    for(j=1; j<colunas; j++)
        diagonal24[linhas+j] = dispDiagonal13(campo[MAX][MAX],
                                              linhas-1, colunas-1-j,
                                              linhas, colunas);
    /* Posicionar o AT-TE  */
    for(i=0; i<linhas; i++)
        for(j=0; j<colunas; j++){
            
        }

            
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


int dispHorizontal(int campo[MAX][MAX],
                   int i, int colunas){
    int k, droids=0;
    for(k=0; k<colunas; k++)
        droids+=campo[i][k];
    return droids;
}
int dispVertical(int campo[MAX][MAX],
                 int j, int linhas){
    int k, droids=0;
    for(k=0; k<linhas; k++)
        droids+=campo[k][j];
    return droids;
}
int dispDiagonal13(int campo[MAX][MAX],
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
int dispDiagonal24(int campo[MAX][MAX],
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
}
