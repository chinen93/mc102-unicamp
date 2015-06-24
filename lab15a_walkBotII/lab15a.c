/* Nome: Pedro Hideaki Uichi Chinen
   RA  : 175828
   Laboratorio 15a - WalkBot II
*/

#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

typedef struct {
    int x,y;
} Pos;

int **global_jogo;
Pos global_direcao[4]={{0, +1}, {+1, 0}, {0, -1}, {-1, 0}};

int achouCaminho(Pos atual, int vidas, int linhas,
                 int colunas, Pos *jaPassou, int tam);

int main(){
    int i,j;
    int linhas, colunas, vidas;
    Pos inicial, anterior;
    Pos *jaPassou;

    scanf("%d %d %d", &linhas, &colunas, &vidas);
    
    /*Alocar memoria*/
    global_jogo=malloc(linhas*sizeof(int *));
    for(i=0; i<linhas; i++)
        global_jogo[i]=malloc(colunas*sizeof(int));
    jaPassou=malloc(vidas*sizeof(Pos));

    /*preencher vetores*/
    for(i=0; i<vidas; i++){
        jaPassou[i].x=-1;
        jaPassou[i].y=-1;
    }
    for(i=0; i<linhas; i++)
        for(j=0; j<colunas; j++)
            scanf("%d", &global_jogo[i][j]);
    
    /*executar funcao para cada posicao inicial*/
    inicial.y=0;
    for(i=0; i<linhas; i++){
        inicial.x=i;
        if(achouCaminho(inicial, vidas, linhas,
                        colunas, jaPassou, vidas))
            printf("Sim\n");
        else
            printf("Nao\n");
            
    }

    /*liberar memoria*/
    free(jaPassou);
    for(i=0; i<linhas; i++)
        free(global_jogo[i]);
    free(global_jogo);
    return 0;
}

int achouCaminho(Pos atual, int vidas, int linhas,
                 int colunas, Pos *jaPassou, int tam){
    int i, j, quantosGuardados=0;
    Pos aux;
    int dir[4]={0,0,0,0};
    if(vidas==0)
        return FALSE;

    switch(global_jogo[atual.x][atual.y]){
    case 0:
        return FALSE;
        break;
    case 1:
        dir[2]=1;
        break;
    case 2:
        dir[1]=1;
        break;
    case 3:
        dir[1]=1;
        dir[2]=1;
        break;
    case 4:
        dir[0]=1;
        break;
    case 5:
        dir[0]=1;
        dir[2]=1;
        break;
    case 6:
        dir[0]=1;
        dir[1]=1;
        break;
    case 7:
        dir[0]=1;
        dir[1]=1;
        dir[2]=1;
        break;
    case 8:
        dir[3]=1;
        break;
    case 9:
        dir[2]=1;
        dir[3]=1;
        break;
    case 10:
        dir[1]=1;
        dir[3]=1;
        break;
    case 11:
        dir[1]=1;
        dir[2]=1;
        dir[3]=1;
        break;
    case 12:
        dir[0]=1;
        dir[3]=1;
        break;
    case 13:
        dir[0]=1;
        dir[2]=1;
        dir[3]=1;
        break;
    case 14:
        dir[0]=1;
        dir[1]=1;
        dir[3]=1;
        break;
    case 15:
        dir[0]=1;
        dir[1]=1;
        dir[2]=1;        
        dir[3]=1;
        break;
    }
    /*
    for(i=0; i<vidas; i++)
        printf("*");
    printf("(%d %d (%d))", atual.x, atual.y, vidas);
    printf("[%d %d %d %d]\n", dir[0], dir[1],dir[2],dir[3]);
    */

    /* tentativa de salvar os lugares nos quais o bot passou  */
    for(i=0; i<tam; i++){
        if(jaPassou[i].x=-1)
            break;
        quantosGuardados++;
    }
    jaPassou[quantosGuardados].x=atual.x;
    jaPassou[quantosGuardados].y=atual.y;
    quantosGuardados++;
    
    for(i=0; i<4; i++){
        if(dir[i]!=0){
            aux.x=atual.x+global_direcao[i].x;
            aux.y=atual.y+global_direcao[i].y;

            /* Guardar locais passados para que não demore tanto a recurcao   */
            for(j=0; j<quantosGuardados; i++)
                if(jaPassou[j].x==aux.x && jaPassou[j].y==aux.y)
                    return FALSE;
            
                
            if(aux.y==colunas)
                return TRUE;
            if(aux.x>=0 && aux.y>=0 && aux.y<=colunas)
                if(achouCaminho(aux, vidas-1, linhas,
                                colunas, jaPassou, tam))
                    return TRUE;
        }
    }

    return FALSE;
}
