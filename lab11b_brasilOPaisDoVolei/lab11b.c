/* Laboratorio 11b - Brasil, o Pais do Volei
 * Nome: Pedro Hideaki Uiechi Chinen
 * RA:   175828
 */

#include <stdio.h>
#include <string.h>

#define TRUE 1
#define FALSE 0

struct time {
   char nome[21];
   int indice, pontos, vitorias;
   int pontosGanhos, pontosPerdidos, setsGanhos, setsPerdidos; 
};
typedef struct time time_t;

void atualizaSetsPontos(time_t *time, int setsGanhos, int setsPerdidos, 
                        int pontosGanhos, int pontosPerdidos);
void atualizaPartida(time_t *timeGanhador, time_t *timePerdedor, 
                     int diferencaSets, int confrontoDireto[][6]);
void leResultadosChave(time_t timesChave[], int confrontoDireto[][6]);
void ordenaTimes(time_t times[], int n, int confrontoDireto[][6]);

int acharTime(char *nome, time_t *time);
void separaPontos(char *ponto1, char *pontos2, char *pontos);

int main() {
   /* variaveis de entrada */
   time_t timesChaveA[6], timesChaveB[6];
   /* variaveis auxiliares */
   /* confrontosChaves, tabela de jogos onde os indices sao os times jogando */
   int i, confrontosChaveA[6][6], confrontosChaveB[6][6];

   /* le entrada */
   leResultadosChave(timesChaveA, confrontosChaveA);
   leResultadosChave(timesChaveB, confrontosChaveB);
  
   /* ordena os vetores de times na ordem de classificacao */
   ordenaTimes(timesChaveA, 6, confrontosChaveA);
   ordenaTimes(timesChaveB, 6, confrontosChaveB);

   /* imprime a saida 
   for (i = 0; i < 4; i++) {
      printf("%s x %s\n", timesChaveA[i].nome, timesChaveB[3-i].nome);
   }
   */
   return 0;
}

/* Atualiza os atributos relativos aos sets e aos pontos */
void atualizaSetsPontos(time_t *time, int setsGanhos, int setsPerdidos, 
                        int pontosGanhos, int pontosPerdidos) {
   time->setsGanhos += setsGanhos;
   time->setsPerdidos += setsPerdidos;
   time->pontosGanhos += pontosGanhos;
   time->pontosPerdidos += pontosPerdidos;
}

/* Atualiza os atributos relativos as partidas */
void atualizaPartida(time_t *timeGanhador, time_t *timePerdedor, 
                     int diferencaSets, int confrontoDireto[][6]) {
   timeGanhador->vitorias++;

   if (diferencaSets > 1)
      timeGanhador->pontos += 3;
   else {
      timeGanhador->pontos += 2;
      timePerdedor->pontos += 1;
   }

   confrontoDireto[timeGanhador->indice][timePerdedor->indice] = 1;
   confrontoDireto[timePerdedor->indice][timeGanhador->indice] = -1;
}

/* Le os resultados das partidas entre todos os times de uma chave */
void leResultadosChave(time_t timesChave[], int confrontoDireto[][6]) {
    /* timesChave, contem os times naquela chave*/
    char time1[21], time2[21];
    char pontosAll[7], pontos1[7], pontos2[7];
    char teste;
    int  acabouRes, posicao;
    int  sets1, sets2, ind1, ind2;
    int  criarTime, timesCriados=0;
    int  i, j;

    /*le 15 linhas e para a execucao*/
    for(i=0; i<15; i++){
        sets1=0;
        sets2=0;

        /*------------------Achar Times no Vetor-----------------------------*/
        scanf("%s", time1);
        ind1=int acharTime(time1, timesChave);
        
        scanf("%s", time2);
        ind2=int acharTime(time2, timesChave);
        /*----------------------Verificar quem ganhou------------------------*/
        acabouRes=FALSE;
        for(j=0; j<5 && !acabouRes; j++){
            scanf("%s", pontosAll);

            printf("[%s] [%s]\n", pontos1, pontos2);
            
            /* verifica se eh para sair dos resultados dos jogos  */
            scanf("%c", &teste);
            if(teste == '\n')
                acabouRes=TRUE;
        }
        printf("-------------------\n");
        /*----------------------Atualizar Registro---------------------------*/
    }
}

void separaPontos(char *ponto1, char *pontos2, char *pontos){
    int i;
    if()
}

int acharTime(char *nome, time_t *time){
    int criarTime=TRUE;
    int i, indice;
    for(i=0; i<timesCriados; i++){
        if(strcmp(timesChave[i].nome, nome)==0){
            criarTime==FALSE;
            indice=i;
        }
    }
    if(criarTime){
        indice=timesCriados;
        strcpy(timesChave[timesCriados].nome, nome);
        timesCriados++;
    }

    return indice;
}

/* Ordena o vetor de times */
void ordenaTimes(time_t times[], int n, int confrontoDireto[][6]) {

}
