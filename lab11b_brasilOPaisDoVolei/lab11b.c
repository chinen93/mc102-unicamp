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


int acharTime(char *nome, time_t *time, int *timesCriados);
time_t criarTime(char *nome, int indice);

void printTime(time_t *time){
    printf("%s ", time->nome);
    printf("%2d ", time->pontosGanhos);
    printf("%2d\n", time->vitorias);
    
}

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
    char teste;
    int  acabouSets;
    int  timesCriados=0;
    int  sets1, sets2, ind1, ind2, pontos1, pontos2;
    int  i, j;

    /*le 15 linhas e para a execucao*/
    for(i=0; i<15; i++){
        sets1=0;
        sets2=0;

        /*------------------Achar Times no Vetor-----------------------------*/
        scanf("%s", time1);
        ind1=acharTime(time1, timesChave, &timesCriados);
        
        scanf("%s", time2);
        ind2=acharTime(time2, timesChave, &timesCriados);

        /*----------------------Verificar quem ganhou------------------------*/
        acabouSets=FALSE;
        sets1=0;
        sets2=0;
        for(j=0; j<5 && !acabouSets; j++){
            scanf("%d-%d%c", &pontos1, &pontos2, &teste);
            if(pontos1 > pontos2){
                /* time 1 ganhou, 2 perdeu SET*/
                atualizaSetsPontos(&timesChave[ind1], 1, 0, 
                                   pontos1, pontos2);
                atualizaSetsPontos(&timesChave[ind2], 0, 1, 
                                   pontos2, pontos1);
                sets1++;
            }else{
                /* time 2 ganhou, 1 perdeu SET*/
                atualizaSetsPontos(&timesChave[ind1], 0, 1, 
                                   pontos1, pontos2);
                atualizaSetsPontos(&timesChave[ind2], 1, 0, 
                                   pontos2, pontos1);
                sets2++;
            }
            
            /* verifica se eh para sair dos resultados dos jogos  */
            if(teste == '\n')
                acabouSets=TRUE;
        }

        /* quem ganhou a partida e por quantos sets  */
        if(sets1 > sets2){
            /* time 1 ganhou, 2 perdeu PARTIDA*/
            atualizaPartida(&timesChave[ind1], &timesChave[ind2], 
                          sets1-sets2, confrontoDireto);
        }else{
            /* time 2 ganhou, 1 perdeu PARTIDA*/
            atualizaPartida(&timesChave[ind2], &timesChave[ind1], 
                          sets2-sets1, confrontoDireto);
        }
    }
}


int acharTime(char *nome, time_t *time, int *timesCriados){
    int existeTime=FALSE;
    int i, indice;

    /* verifica se o time esta no vetor de times  */
    for(i=0; i<(*timesCriados); i++){
        if(strcmp(time[i].nome, nome)==0){
            return i;
        }
    }

    /* se nao estiver cria o time  */
    if(!existeTime){
        indice=(*timesCriados);
        time[(*timesCriados)]=criarTime(nome, indice);
        (*timesCriados)++;
    }

    return indice;
}

time_t criarTime(char *nome, int indice){
    time_t retorno;
    
    strcpy(retorno.nome, nome);
    retorno.indice=indice;
    retorno.pontos=0;
    retorno.vitorias=0;
    retorno.pontosGanhos=0;
    retorno.pontosPerdidos=0;
    retorno.setsGanhos=0;
    retorno.setsPerdidos=0;

    return retorno;
}

/* Ordena o vetor de times */
void ordenaTimes(time_t times[], int n, int confrontoDireto[][6]) {
    int i, j, indMelhor;
    for(i=0; i<n; i++){
        indMelhor=i;
        for(j=i+1; j<n; j++){
            /* verifica casos de ranking  */
            /* Pontos,  numVitorias, razaoSets, razaoPontos, confrontoDireto */
        }
        
        if(indMelhor != i){
            /* troca */
        }
    }
    

}
