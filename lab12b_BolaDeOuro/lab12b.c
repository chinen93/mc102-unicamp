/* Laboratorio 12b - Bola de Ouro
   Autor: Pedro Hideaki Uiechi Chinen 175828
   Email: ph.u.chinen@gmail.com
*/

#include <stdio.h>
#include <string.h>

/* Tamanho maximo do nome do jogador */
#define MAXNOME 26
/* Tamanho maximo do nome dos arquivos de entrada/saida */
#define MAXNOMEARQ 101
/* Numero maximo de jogadores */
#define MAXJOGADORES 40

/* Jogador:
 * nome = nome do jogador
 * C1 = numero de gols
 * C2 = numero de assistencias
 * C3 = numero de dribles feitos
 * C4 = numero de gols contra
 * C5 = numero de cartoes vermelhos
 * C6 = numero de cartoes amarelos
 */
struct Jogador {
    char nome[MAXNOME];
    int C1;
    int C2;
    int C3;
    int C4;
    int C5;
    int C6;
};
typedef struct Jogador Jogador;

void printJog(Jogador jog){
    printf("[%s - %d %d %d %d %d %d]\n",
           jog.nome, jog.C1, jog.C2, 
           jog.C3, jog.C4, jog.C5, jog.C6);
}

void printJogadores(Jogador *jog, int tam){
    int i;
    for(i=0; i<tam; i++){
        printJog(jog[i]);
    }
}

int pontosJog(Jogador jog, int *pontos){
    return  jog.C1 * pontos[0]+
        jog.C2 * pontos[1]+
        jog.C3 * pontos[2]-
        jog.C4 * pontos[3]-
        jog.C5 * pontos[4]-
        jog.C6 * pontos[5];
}

void selectionSort(Jogador *jogadores, int tam, int *pontos){
    int i, j, iMax;
    int pi, pj;
    Jogador aux;
    for (j=0; j<tam-1; j++) {
        iMax=j;
        pj=pontosJog(jogadores[j], pontos);
        for (i=j+1; i<tam; i++) {
            pi=pontosJog(jogadores[i], pontos);
            if(pj < pi){
                iMax=i;
                pj=pi;
            }else if(pj==pi && strcmp(jogadores[j].nome, jogadores[i].nome) < 1){
                iMax=i;
            }
        }
 
        if(iMax!=j) {
            aux=jogadores[j]; 
            jogadores[j]=jogadores[iMax]; 
            jogadores[iMax]=aux;
        }
    }
}

void atualizarJog(Jogador jog, Jogador *jogadores, int tam){
    int i;
    for(i=0; i<tam; i++){
        if(strcmp(jog.nome, jogadores[i].nome)==0){
            jogadores[i].C1+=jog.C1;
            jogadores[i].C2+=jog.C2;
            jogadores[i].C3+=jog.C3;
            jogadores[i].C4+=jog.C4;
            jogadores[i].C5+=jog.C5;
            jogadores[i].C6+=jog.C6;           
        }
    }
}

int main(int argc, char **argv) {
    FILE *arqIn, *arqOut;
    int i, j;
    int numRodadas, numJogArquivo, numJogPadrao;
    Jogador jogadores[MAXJOGADORES], jog, jogadoresAux[MAXJOGADORES];
    int pontos[6];
    /*
    char nomeJog[MAXNOME];
    int C1, C2, C3, C4, C5, C6;
    */
     
    /* Nome do arquivo binario com as estatisticas */
    char nomeArqEstat[MAXNOMEARQ];
    /* Nome do arquivo binario de saida */
    char nomeArqSaida[MAXNOMEARQ];

    /* Lendo os nomes dos arquivos binarios */
    strcpy(nomeArqEstat, argv[1]);
    strcpy(nomeArqSaida, argv[2]);   

    /* Ler o Arquivo binario e criar o vetor de jogadores */
    arqIn=fopen(nomeArqEstat, "rb");
    if(arqIn != NULL){
        fread(&numJogArquivo, sizeof(int), 1, arqIn);
        for(i=0; i<numJogArquivo; i++)
            fread(&jogadores[i], sizeof(Jogador), 1, arqIn);
        fclose(arqIn);
    }else{
        printf("Erro ao ler arquivo de entrada");
        return 1;
    }

    /* Ler os dados da entrada padrao sobre a rodada atual */
    scanf("%d %d %d %d %d %d",
          &pontos[0], &pontos[1], &pontos[2], 
          &pontos[3], &pontos[4], &pontos[5]);
    scanf("%d", &numRodadas);
    for(i=0; i<numRodadas; i++){
        scanf("%d", &numJogPadrao);
        for(j=0; j<numJogPadrao; j++){
            scanf("%s %d %d %d %d %d %d", 
                  jog.nome, &jog.C1, &jog.C2, &jog.C3, 
                  &jog.C4, &jog.C5, &jog.C6);
            atualizarJog(jog, jogadores, numJogArquivo);
        }
    }
    /* Copiar o vetor em outro 
       Ordenar a copia por pontos e lexicografica
       Escrever os 3 melhores colocados da copia */
    for(i=0; i<numJogArquivo; i++)
        jogadoresAux[i]=jogadores[i];

    selectionSort(jogadoresAux, numJogArquivo, pontos);
    printf("%s\n", jogadoresAux[0].nome);
    printf("%s\n", jogadoresAux[1].nome);
    printf("%s\n", jogadoresAux[2].nome);
    
    /*Escrever um arquivo binario com o vetor original */
    arqOut=fopen(nomeArqSaida, "wb");
    fwrite(&numJogArquivo, sizeof(int), 1, arqOut);
    for(i=0; i<numJogArquivo; i++){
        fwrite(&jogadores[i], sizeof(Jogador), 1, arqOut);
    }
    fclose(arqOut);
    
    return 0;
}
