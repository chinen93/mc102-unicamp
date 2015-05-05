/*Nome: Pedro Hideaki Uiechi Chinen
  RA  : 175828
  Laboratorio 07a - Cargo Bot : Part II
*/

#include <stdio.h>

#define TRUE 1
#define FALSE 0
#define MAX_MATRIZ 10
#define MAX_PROGRAMAS 9
#define MAX_COMANDOS 60
int main(){
  char jogo[MAX_MATRIZ][MAX_MATRIZ];
  char programas[MAX_PROGRAMAS+1][MAX_COMANDOS+1];
  char execucoes[MAX_COMANDOS];
  char garra;
  int posGarra, ondeTopo;
  int colunas, linhas;
  int nProg, nComand;
  int nExec, progExec;
  int acidente=FALSE, execProx;
  int i, j;

  /*inicializa variaveis*/
  garra='.';
  posGarra=0;
  execProx=TRUE;
  
  /*Ler dados*/
  scanf("%d %d %d %d %d", &colunas, &linhas,
	&nProg, &nComand, &nExec);  
  for(i=0; i<linhas; i++){
    for(j=0; j<colunas; j++){
      scanf(" %c", &jogo[i][j]);
    }
  }
  for(i=0; i<nExec; i++){
    scanf(" %c",&execucoes[i]);
  }
  for(i=0; i<nProg; i++){
    scanf("%s",programas[i]);
  }

  /*Trabalhar com os dados*/
  for(i=0; i<nExec && !acidente; i++){
    /*Transformar character '0' em numero 0*/
    progExec=execucoes[i]-48;
    /*o programa 1 esta na posicao 0 do vetor de programas*/
    progExec--;
    for(j=0; programas[progExec][j]!='*' && !acidente; j++){
      switch(programas[progExec][j]){
	/* Com BGYAN verifica se executara o proximo comando*/
      case 'B':
	if(garra != 'B')
	  execProx=FALSE;
	break;
      case 'G':
	if(garra != 'G')
	  execProx=FALSE;
	break;
      case 'Y':
	if(garra != 'Y')
	  execProx=FALSE;
	break;
      case 'A':
	if(garra == '.')
	  execProx=FALSE;
	break;
      case 'N':
	if(garra != '.')
	  execProx=FALSE;
	break;
	/* Comandos que de fato mudam o jogo*/
      case 'L':
	/*Esquerda, ve se houve acidente para a esquerda*/
	if(execProx && posGarra>0){
	  posGarra--;
	  if(jogo[0][posGarra] != '.' && garra != '.'){
	    acidente=TRUE;
	  }
	}
	execProx=TRUE;
	break;
      case 'R':
	/*Direita, ve se houve acidente para a direita*/
	if(execProx && posGarra<colunas-1){
	  posGarra++;
	  if(jogo[0][posGarra] != '.' && garra != '.'){
	    acidente=TRUE;
	  }
	}
	execProx=TRUE;
	break;
      case 'D':
	if(execProx){
	  ondeTopo=0;
	  if(garra == '.'){
	    /* Pegar */
	    while(jogo[ondeTopo][posGarra] == '.' && ondeTopo<linhas)
	      ondeTopo++;

	    /*Caso nao tenha batido no chao, pegar uma caixa*/
	    if(ondeTopo<linhas){
	      garra=jogo[ondeTopo][posGarra];
	      jogo[ondeTopo][posGarra]='.';
	    }
	  }else{
	    /* Deixar */
	    while(jogo[ondeTopo][posGarra] == '.' && ondeTopo<linhas)
	      ondeTopo++;
	    /* voltar uma posicao pois na atual tem uma caixa ou o chao*/
	    ondeTopo--;
	    jogo[ondeTopo][posGarra]=garra;
	    garra='.';
	  }
	}
	execProx=TRUE;
	break;
      }/*switch(programas[progExec][j])*/
    }/*for(j=0; programas[progExec][j]!='*' && !acidente; j++)*/
  }/* for(i=0; i<nExec && !acidente; i++)*/
  
  /*Imprimir mensagem*/
  if(acidente)
    printf("Um acidente ocorreu\n");
  else{
    for(i=0; i<linhas; i++){
      for(j=0; j<colunas; j++)
	printf("%c", jogo[i][j]);
      printf("\n");
    }
  }
  return 0;
}
