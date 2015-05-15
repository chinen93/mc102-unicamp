/* Nome: Pedro Hideaki Uiechi Chinen
   RA  : 175828
   Lab 09b - Peladeiros */

#define DELTA 0.001

/*dado um grupo de n jogadores confirmados, os t capitães são definidos com base nas t maiores notas médias atribuídas para cada jogador. 
Definidos os capitães, inicia-se o processo de escolha alternada entre eles, de tal modo que o primeiro capitão a escolher é o que possui maior nota média, o segundo é o que possui a segunda maior nota média e assim sucessivamente. 
Tal como dito anteriormente, cada capitão sempre escolhe um jogador, dentre os jogadores ainda não escolhidos, que ele acredita ser o melhor.
Nesse caso, um capitão C considera um jogador A melhor que um jogador B se a nota atribuída pelo capitão C ao jogador A é maior do que a nota atribuída pelo capitão C ao jogador B.
Casos de empate, tanto na definição dos capitães quanto na escolha dos jogadores pelos capitães, devem ser resolvidos em favor do jogador com o menor número identificador, isto é, caso os jogadores A e B tenham notas iguais, considera-se que jogador A é melhor que o jogador B se A < B. 


*/
int acharIndiceMaior(float *vetor);
void zerarColuna(float **tabela, int jogador, int jogadores);

int main(){
    int jogadores, capitoes;
    float **tabela, *medias;
    float mediaAux;
    int **times;
    int i, j, indice;

    /* Ler dados e alocar memoria  */
    scanf("%d %d", &jogadores, &capitoes);
    tabela=(float **)malloc(jogadores * sizeof(float *));
    for(i=0; i<jogadores; i++)
        tabela[i]=(float *)malloc(jogadores * sizeof(float));
    media=(float *)malloc(jogadores * sizeof(float));
    times=(int **)malloc((jogadores/capitoes) * sizeof(int *));
    for(i=0; i<(jogadores/capitoes); i++)
        times[i]=(float *)malloc((jogadores/capitoes)
                                  * sizeof(int));  

    for(i=0; i<jogadores; i++)
        for(j=0; j<jogadores; j++)
            scanf("%f", &tabela[i][j]);
    
    /* Calcular medias dos jogadores */
    for(j=0; j<jogadores; j++){
        mediaAux=0;
        for(i=0; i<jogadores; i++)
            mediaAux+=tabela[i][j];
        medias[j]=mediaAux/jogadores;
    }
    
    /* Escolher os capitoes  */
    for(i=0; i<capitoes; i++){
        indice=acheIndiceMaior(medias, jogadores);
        times[i][0]=indice;
        zerarTabela(tabela, jogador, jogadores);
    }

    /* Escolher o resto to time */
    
    
    
    /* Exibir dados e desalocar memoria  */
    for(i=0; i<(jogadores/capitoes); i++)
        free(times[i]);
    free(times);
    free(media);
    for(i=0; i<jogadores; i++)
        free(tabela[i]);
    free(tabela);
    return 0;
}

int acharIndiceMaior(float *vetor, int tam){
    int i, indice=0;
    for(i=0; i<tam; i++)
        if(vetor[indice]-vetor[i] < DELTA)
            indice=i;
    
    return indice
}

void zerarColuna(float **tabela, int jogador, int jogadores){
    int i, j;
    for(i=0; i<jogadores; i++)
        tabela[i][jogador]=0.0;
    
}
