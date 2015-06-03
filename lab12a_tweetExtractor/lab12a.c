/* Laboratorio 12a - Tweet Extractor
   Autor: Pedro Hideaki Uiechi Chinen
   Email: ph.u.chinen@gmail.com
   RA   : 175829
*/

#include <stdio.h>
#include <string.h>

#define MAX_FILENAME 25
#define MAX_ENTITY 10

#define TRUE 1
#define FALSE 0

/* Funcao que converte uma entidade no caractere correspondente,
   supondo que o caractere '&' foi previamente lido no arquivo de
   entrada (arqin). Se a entidade eh diferente de aspas simples ou
   aspas dupla, a funcao simplesmente o ignora, caso contrario ela
   imprime o caractere correspondente no arquivo de saida (arqout). */
void converte_entidade(FILE *arqin, FILE *arqout) {
    char c, entidade[MAX_ENTITY];
    int i = 0;
    
    /* armazena o codigo da entidade ate encontrar o caractere ';' */
    c = fgetc(arqin);
    while (c != ';') {
        entidade[i++] = c;
        c = fgetc(arqin);
    }
    entidade[i] = '\0';
    
    /* se a entidade corresponde ao caractere aspas simples ou aspas duplas,
       imprime o caractere no arquivo de saida */
    if (!strcmp(entidade, "#39"))
        fprintf(arqout, "\'");
    else if(!strcmp(entidade, "quot"))
        fprintf(arqout, "\"");
}

void extrai_tweets(char nomearqin[], char nomearqout[]) {
    FILE *arqIn, *arqOut;
    char texto[] = "      <p class=\"ProfileTweet-text js-tweet-text u-dir\"\n";
    char lido[60], cAtual, cAnte = 'a';
    int cont=2050;
    int noTweet=FALSE;
    cAnte++;
    arqIn=fopen(nomearqin, "r");
    arqOut=fopen(nomearqout, "w+");

    /* Se os arquivos foram abertos corretamente */
    if(arqIn != NULL && arqOut != NULL){ 
        printf("%s\n", texto);
        
        printf("achou os arquivos\n");
        while(fgets(lido, 60, arqIn) != NULL){
            /* ler 29 caracteres do comeco da linha ate que o arquivo acabe */
            if(cont>0){
                printf("%s\n", lido);
                cont--;
            }
            /* verificar se sao os 29 caracteres que quero */
            if(strcmp(lido, texto) != 0){
                /* se nao for, ler a linha ate o '\n' */
                cAtual=fgetc(arqIn);
                while(cAtual != '\n')
                    cAtual=fgetc(arqIn);
            }else{
                /* se for, ler os proximos caracteres um a um ate achar <\p> */
                noTweet=TRUE;
                printf("achou o tweet\n");
                while(noTweet){
                    if(cAtual=='p' && cAnte=='/'){
                        printf("sair do tweet");
                    }
                    noTweet=FALSE;
                }
                break;
            }
        }
        fclose(arqIn);
        fclose(arqOut);
    }else{
        printf("Arquivos nao encontrados\n");
    }
}


int main(int argc, char *argv[]) {  
    char nomearqin[MAX_FILENAME], nomearqout[MAX_FILENAME];
    
    /* Copia os nomes do arquivo de entrada e de saida nas variaveis */
    strcpy(nomearqin, argv[1]);
    strcpy(nomearqout, argv[2]);
 
    extrai_tweets(nomearqin, nomearqout);

    return 0;
}
