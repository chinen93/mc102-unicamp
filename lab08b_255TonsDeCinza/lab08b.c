/* Laboratorio 08b - Cinquenta Tons de Cinza
 * Nome: Pedro Hideaki Uiechi Chinen
 * RA:   175828
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

/* Definindo tamanho maximo das imagens */
#define MAX_TAM 400

/* Le uma imagem em formato PGM a partir da entrada padrao.
 * Retorna 1 se a leitura for realmente de um arquivo PGM
 * e 0 caso contrario */
int ler_pgm(int img[][MAX_TAM], int *W, int *H, int *MaxV,
            int *F, double *C, double *Gama) {
    char nome_formato[3];
    int i,j;

    /* Le o formato da imagem. P2 indica o formato PGM */
    scanf("%s ", nome_formato);
    if (strcmp(nome_formato, "P2") != 0)
        return 0;

    /* Le o '#', que indica um comentario, e os numeros indicando
       o filtro e os parametros, se houver */
    scanf("# %d", F);

    if (*F == 1) {
        scanf("%lf %lf", C, Gama);
    }

    /* Le dimensoes e intensidade maxima da imagem */
    scanf("%d", W);
    scanf("%d", H);
    scanf("%d", MaxV);

    /* Le o valor de cada ponto da imagem */
    for (i = 0; i < (*H); i++) {
        for (j = 0; j < (*W); j++) {
            scanf("%d", &img[i][j]);
        }
    }

    return 1;
}

/* Escreve a imagem em formato PGM na saida padrao */
void escrever_pgm(int img[][MAX_TAM], int W, int H, int MaxV) {
    int i, j;

    /* Escreve os atributos da imagem */
    /* Tipo da imagem: P2 significa pgm*/
    printf("P2\n");

    /* Dimensoes e intensidade maxima da imagem */
    printf("%d %d %d\n", W, H, MaxV);

    /* Escreve os pontos da imagem */
    for (i = 0; i < H; i++) {
        printf("%d", img[i][0]);
        for (j = 1; j < W; j++) {
            printf(" %d", img[i][j]);
        }
        printf("\n");
    }
}

/* Transformacao de Potencia (gama) */
void potencia(int img[][MAX_TAM], int W, int H, int MaxV, 
              double c, double gama) {
    int x, y;
    int aux;
    for(y=0; y<H; y++){
	for(x=0; x<W; x++){
	    /* Percorre a imagem aplicando a funcao*/
	    aux = (int) floor(c*pow(img[y][x], gama));
	    if(aux > MaxV)
		aux = MaxV;
	    img[y][x] = aux;
	}
    }
    
}

/* Espelhamento */
void espelhamento(int img[][MAX_TAM], int W, int H) {
    int x, y;
    for(y=0; y<H; y++){
	for(x=0; x<W/2; x++){
	    img[y][x] = img[y][(W-1)-x];
	}
    }
}

/* Reducao de Ruidos com Filtro Gaussiano */
void reducaoRuido(int img[][MAX_TAM], int W, int H, int MaxV) {
    int x, y;
    int **aux;
    int soma;

    /* Alocar memoria */
    aux =(int **)malloc(H * sizeof(int*));
    for(y=0; y<H; y++)
	aux[y] =(int *)malloc(W * sizeof(int));
    
    /* Andar pela matriz principal */
    for(y=1; y<H-1; y++){
	for(x=1; x<W-1; x++){
	    /* Andar pelo filtro Gaussiano */
	    soma = (1*img[y-1][x-1]+ 2*img[y-1][x]+ 1*img[y-1][x+1]+
		    2*img[y][x-1]  + 4*img[y][x]  + 2*img[y][x+1]+
		    1*img[y+1][x-1]+ 2*img[y+1][x]+ 1*img[y+1][x+1]
		    )/16;
	    if(soma > MaxV)
		soma = MaxV;
	    else
		soma = floor(soma);
	    aux[y][x]=soma;
	}
    }
    /* Colocar as alteracoes na imagem */
    for(y=1; y<H-1; y++){
	for(x=1; x<W-1; x++){
	    img[y][x]=aux[y][x];
	}
    }

    /* Liberar memoria  */
    for(y=0; y<H; y++){
	free((int *)aux[y]);
    }
    free((int **)aux);
}

/* Rotacao 90 graus */
void rotacao(int img[][MAX_TAM], int W, int H) {
    int y, x;
    int **aux;

    /* Imagem original HxW 
       Imagem auxiliar WxH
     */
    
    /* Alocar Memoria */
    aux=(int **)malloc(W * sizeof(int *));
    for(y=0; y<W; y++)
	aux[y]=(int *)malloc(H * sizeof(int));

    /* Rotacionar para a aux */
    /* aux[variavel][const] = img [const][variavel] */
    for(y=0; y<H; y++){
	for(x=0; x<W; x++){
	    aux[(W-1)-x][y] = img[y][x];
	}
    }
    /* Passar para a normal */
    for(y=0; y<W; y++){
	for(x=0; x<H; x++){
	    img[y][x] = aux[y][x];
	}
    }
    
    /* Desalocar Memoria  */
    for(y=0; y<W; y++)
	free((int *)aux[y]);
    free((int **)aux);

}

int main() {
    /* Matriz que armazena os pixels da imagem */
    int img[MAX_TAM][MAX_TAM];
    /* Atributos da imagem */
    int W, H, MaxV, aux;
    /* Identificador do filtro a ser utilizado */
    int F;
    /* Parametros a serem passados para a potencia */
    double C, Gama;

    /* Le a imagem */
    if (ler_pgm(img, &W, &H, &MaxV, &F, &C, &Gama) != 1) {
        printf("Error: nao foi possivel ler a imagem\n");
        return 0;
    }

    /* Seleciona o filtro */
    switch (F) {
    case 1:
	potencia(img, W, H, MaxV, C, Gama);
	break;
    case 2:
	espelhamento(img, W, H);
	break;
    case 3:
	reducaoRuido(img, W, H, MaxV);
	break;
    case 4:
	rotacao(img, W, H);
	aux = W;
	W = H;
	H = aux;
	break;
    }

    /* Escreve a imagem */
    escrever_pgm(img, W, H, MaxV);

    return 0;
}
