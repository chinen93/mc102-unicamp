/* Nome: Pedro Hideaki Uichi Chinen
   RA  : 175828
   Laboratorio 13 b - QuadTree
 */

#include <stdio.h>
#include <stdlib.h>

/* matriz global para nao precisar passar na recursao */
int **global_matriz;

int homogeneo(int linha, int coluna, int tam);

int main(){
    int tam;
    int i, j;

    scanf("%d", &tam);

    /* Alocar memoria  */
    global_matriz=malloc(tam * sizeof(int*));
    for(i=0; i<tam; i++)
        global_matriz[i]=malloc(tam * sizeof(int));
    
    /* Popular a matriz  */
    for(i=0; i<tam; i++)
        for(j=0; j<tam; j++)
            scanf("%d", &global_matriz[i][j]);
    
    printf("Numero de regioes = %d\n", homogeneo(0,0,tam));

    /* liberar memoria alocada  */ 
    for(i=0; i<tam; i++)
        free(global_matriz[i]);
    free(global_matriz);
    
    
    return 0;
}

int homogeneo(int linha, int coluna, int tam){
    int i, j;
   
    /* caso alguma posicao seja diferente da 
       primeira posicao da submatriz  
       dividir a submatriz na metade e verificar se essas novas
       partes sao homogeneas
    */
    for(i=linha; i<linha+tam; i++)
        for(j=coluna; j<coluna+tam; j++)
            if(global_matriz[i][j] != global_matriz[linha][coluna])
                return homogeneo(linha, coluna, tam/2) +
                    homogeneo(linha+tam/2, coluna, tam/2) +
                    homogeneo(linha, coluna+tam/2, tam/2) +
                    homogeneo(linha+tam/2, coluna+tam/2, tam/2);

    return 1;       
}
