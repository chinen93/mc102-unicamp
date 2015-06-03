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

#define TAM 56

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

void printString(char *lido){
    int i;
    printf("[");
    for(i=0; i<TAM; i++){
        if(lido[i]=='\n'){
            printf("{N}");
        }else if(lido[i]=='\0'){
            printf("{0}");
        }else{
            printf("%c", lido[i]);
        }
    }
    printf("]\n");
}

void limparString(char *lido){
    int i;
    for(i=0; i<TAM; i++)
        lido[i]=' ';
}

void extrai_tweets(char nomearqin[], char nomearqout[]) {
    FILE *arqIn, *arqOut;
    char texto[] = "      <p class=\"ProfileTweet-text js-tweet-text u-dir\"\n";
    char lido[TAM], cAtual, cAnte;
    int noTweet, temBarraN;
    
    arqIn=fopen(nomearqin, "r");
    arqOut=fopen(nomearqout, "w+");
    
    /* Se os arquivos foram abertos corretamente */
    if(arqIn != NULL && arqOut != NULL){ 
        printf("%s\n", texto);
        
        printf("achou os arquivos\n");
        limparString(lido);


        /*         
                   LENDO ECA PORRA ERRADO
         */

        
        while(fgets(lido, TAM, arqIn) != NULL){
            /* ler caracteres do comeco da linha ate que o arquivo acabe */
            /* verificar se sao os caracteres que quero */
            
            printString(lido);
            
            if(strcmp(lido, texto) != 0){
                /* se nao for, ler a linha ate o '\n' */
                temBarraN=FALSE;
                if(lido[TAM-1] == '\n')
                    temBarraN=TRUE;
                
                if(!temBarraN){ 
                    cAtual=fgetc(arqIn);
                    while(cAtual != '\n'){
                        if(cAtual==EOF)
                            break;
                        cAtual=fgetc(arqIn);
                    }
                    
                }
            }else{
                /* se for, ler os proximos caracteres um a um ate achar <\p> */
                noTweet=TRUE;
                printf("achou o tweet - ");
                
                /* Achar o comeco do Tweet */
                while(cAtual != '>'){
                    cAtual=fgetc(arqIn);
                }
                
                while(noTweet){
                    cAtual=fgetc(arqIn);
                    /* verificar se caracter eh '<'
                       se for, procurar pelo '>' nao imprimir nada ate la e verificar se saiu do tweet 
                       pegar o proximo caracter nao deixando com o '>'*/
                    if(cAtual == '<'){
                        while(cAtual != '>'){
                            cAnte=cAtual;
                            cAtual=fgetc(arqIn);
                            if(cAtual=='p' && cAnte=='/'){
                                printf(" - sair do tweet\n");
                                noTweet=FALSE;
                                fprintf(arqOut, "\n");
                            }
                        }
                    }
                    
                    /* verificar se eh & 
                        se for, aplicar a funcao especial 
                        se nao for, imprimir normal  */
                    /*if(cAtual=='&'){
                        converte_entidade(arqIn, arqOut);
                    }else{
                    }*/
                    if(cAtual!='\n' && cAtual!='>'){
                        fprintf(arqOut, "%c", cAtual);
                        printf("%c", cAtual);
                    }
                }
            }
            
            limparString(lido);        
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
