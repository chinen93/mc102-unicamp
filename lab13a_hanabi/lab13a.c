/* Nome: Pedro Hideaki Uiechi Chinen
   Ra  : 175828
   Laboratorio 13a - Hanabi
 */

#include <stdio.h>

int altura();

int main(){
    printf("%d\n", altura());
    return 0;    
}

int altura(){
    int num, hmax=0;
    int i, hfilho;
    /* ler numero */
    scanf("%d", &num);
    /* caso base */
    if(num==0){
        return 1;
    }else{
        for(i=0; i<num; i++){
            /* percorrer filhos  */
            hfilho=altura();
            if(hfilho > hmax){
                hmax=hfilho;
            }
        }
    }
    /* somar altura propria com a dos filhos  */
    return 1+hmax;
}

