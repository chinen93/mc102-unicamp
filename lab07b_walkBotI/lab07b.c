/* Nome: Pedro Hideaki Uiechi Chinen
   RA  : 175828
   Laboratior 07b - WalkBot Part I
 */

#include <stdio.h>

#define TRUE 1
#define FALSE 0
#define MAX_MATRIZ 50

int ehLoop(int posX, int posY, int casasIdas[][2],
	   int passos, int *tam);

int main(){
  int linhas, colunas;
  char jogo[MAX_MATRIZ][MAX_MATRIZ];
  /* casasIdas[] = (linha, coluna) */
  int casasIdas[MAX_MATRIZ*MAX_MATRIZ][2];
  int i, j, linhaAtual, colunaAtual;
  int passos, tam;
  int loop, fim, armadilha;
  char comando;

  /*Ler dados de entrada e limpar vetores*/
  scanf("%d %d", &linhas, &colunas);
  for(i=0; i<linhas; i++)
    for(j=0; j<colunas; j++)
      scanf("%c",&jogo[i][j]);
  for(i=0; i<MAX_MATRIZ*2; i++){
    casasIdas[i][0]=0;
    casasIdas[i][1]=0;
  }
  
  /*Trabalhar com os dados*/
  for(i=0; i<linhas; i++){
    /*Inicializar variaveis para cada iteracao*/
    tam=0;
    passos=1;
    loop=FALSE;
    fim=FALSE;
    armadilha=FALSE;
    comando=jogo[i][0];
    casasIdas[0][0]=i;
    casasIdas[0][1]=0;
    while(!loop && !fim && !armadilha){
      linhaAtual=casasIdas[i][0];
      colunaAtual=casasIdas[i][1];
      switch(comando){
      case 'L':
	colunaAtual--;
	break;
      case 'R':
	if(colunaAtual<colunas){
	  colunaAtual++;
	}else
	  fim=TRUE;
	break;
      case 'D':
        linhaAtual++;
	break;
      case 'U':
	linhaAtual--;
	break;
      case 'X':
	armadilha=TRUE;
	break;
      }/*switch(comando)*/

      if(!armadilha){
	loop = ehLoop(linhaAtual, colunaAtual, casasIdas,
		      passos, &tam);
	if(!loop && !fim){
	  comando=jogo[linhaAtual][colunaAtual];
	  passos++;
	}
      }
    }/*while(!loop && !fim && !acidente)*/
    
    if(armadilha){
      printf("Armadilha em (%d,%d) apos %d passo(s)\n", linhaAtual,
	     colunaAtual, passos);
    }else if(loop){
      printf("Loop de tamanho %d\n", tam);
    }else{
      printf("Saiu em (%d,%d) apos %d passo(s)\n", linhaAtual,
	     colunaAtual, passos);
    }
       
    /*Limpar as casasIdas*/
    for(i=0; i<passos; i++){
      casasIdas[i][0]=0;
      casasIdas[i][1]=0;
    }
  }/*for(i=0; i<linhas; i++)*/
  
  return 0;
}


int ehLoop(int posX, int posY, int casasIdas[][2],
	   int passos, int *tam){
  int i;
  for(i=0; i<passos; i++){
    if(casasIdas[i][0]==posX && casasIdas[i][1]==posY){
      *tam=passos-i;
      return TRUE;
    }
  }

  return FALSE;
}
