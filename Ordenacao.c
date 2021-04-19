#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void main(){
    int* getvet(int* vet,int* size); //para vetores pequenos e pré-determinados
    void insercao(int* vet,int* size); //Algoritmo de ordenação por inserção
    void selecao(int* vet,int* size); //Algoritmo de ordenação por seleção
    int* size=(int*)malloc(sizeof(int)); //Ponteiro que armazena o tamanho do vetor
    int* randomgen(int* vet,int* size); //Gera vetores aleatorios para testes

    int* vetor=NULL; //Vetor principal a ser organizado
    int* newvet=NULL; //Vetor organizado
    // int i; Para visualizar o vetor

    //vetor = getvet(vetor,size); Para vetores pequenos e pré-determinados
    vetor = randomgen(vetor,size);
    if (vetor==NULL) {
        printf("Vetor nulo");
        exit(1);
    }
    newvet = (int*)malloc((*size)*sizeof(int));
    memcpy(newvet,vetor,(*size)*sizeof(int)); //Copia um vetor com tamanho dinâmico
    /*Imprimir vetor
    for(i=0;i<*size;i++){
        printf("\n%d -> %d",i+1,vetor[i]);
    }*/

    clock_t begin = clock();
    insercao(vetor,size);
    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("\nTempo consumido em insercao: %f",time_spent);
    /*Imprimir vetor
    for(i=0;i<*size;i++){
        printf("\n%d -> %d",i+1,vetor[i]);
    }*/
    free(vetor);

    begin = clock();
    selecao(newvet,size);
    end = clock();
    time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("\nVetor ordenado em selecao: %f", time_spent);
    /* Imprimir vetor
    for(i=0;i<*size;i++){
        printf("\n%d -> %d",i+1,newvet[i]);
    } */
    free(newvet);

    exit(0);
}

int* getvet(int* vet,int* size){
    *size=0;
    char aux[150];
    char* numbs=NULL;
    printf("Digite um numero ou sequencia de numeros para o vetor\nPara sequencias, separe com virgulas\nPara parar digite -\n\n");
    do{
    printf("\nInput: ");
    fgets(aux,150,stdin);
    if (aux[0]=='-'&&aux[1]=='\n') break;

        do{
            if (numbs==NULL){
                    numbs=strtok(aux,",");
            }else{
                numbs=strtok(NULL,",");
            }
            if (numbs==NULL||numbs=='-') break;
            if (vet==NULL) {
                vet=(int*)malloc(sizeof(int));
            } else vet=(int*)realloc(vet,(*size)*sizeof(int));
            vet[*size]=atoi(numbs);
            *size=*size+1;
        }while(1);
    }while(1);
    return vet;
}

void insercao(int* vet,int* size){
    //Percorre o vetor em pequenos passos, conferindo o valor anterior e o atual
    //Caso o valor anterior seja maior, substitui com o próximo
    int aux;
    int i,j;

    for(i=1;i<*size;i++){
        aux=vet[i];
        for (j=i-1;j>=0 && aux<vet[j];j--){
        if (vet[j]>vet[j+1]){
            vet[j+1]=vet[j];
            vet[j]=aux;
            }
        }
    }
}

void selecao(int* vet,int* size){
    //Percorre o vetor, selecionando o valor mais baixo
    //Quando chega no ultimo valor,
    //o algoritmo substitui o valor mais baixo com o de comparação
    int aux;
    int i,j,k;

    for(i=0;i<*size;i++){
        aux = vet[i];
        k=i;
        for(j=i+1;j<*size;j++){
            if (vet[j]<aux) {
                aux=vet[j];
                k=j;
            }
        }
        vet[k]=vet[i];
        vet[i]=aux;
    }
}

int* randomgen(int* vet,int* size){
    int i;
    printf("\nDigite a quantidade de valores: ");
    scanf("%d",size);
    srand(time(NULL));
    for(i=0;i<*size;i++){
        if (vet==NULL) vet=(int*)malloc(sizeof(int));
        else vet=(int*)realloc(vet,(i+1)*sizeof(int));
        vet[i]=rand();
    }
    return vet;
}
