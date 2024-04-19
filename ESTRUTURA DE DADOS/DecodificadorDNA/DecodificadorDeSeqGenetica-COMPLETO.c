#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Sequência para validação = (seq para teste = ATTTACCGTAACTGCGA || TTTATGTGTACGTGTGTGCTTATGCTAACGTGTGTGTGCTTACGTACGT)

//-----------------------------------------------Estrutura da Pilha
typedef struct Pilha{
    char *itens;
    int topo;
    int capacidade;
} Pilha;

//funções da pilha
Pilha *criarPilha(int capacidade){
    Pilha *pilha = malloc(sizeof(Pilha));
    pilha->capacidade = capacidade;
    pilha->topo = -1;
    pilha->itens = malloc(capacidade * sizeof(char));
    return pilha;
} 

void push(Pilha *pilha, char item){
    pilha->itens[++(pilha->topo)] = item;
}


//-----------------------------------------------Estrutura da Fila
typedef struct Fila{
    int* itens;
    int frente;
    int tras;
    int capacidade;
}Fila;

//funções da Fila
Fila *criarFila(int capacidade){
    Fila *fila = malloc(sizeof(Fila));
    fila->capacidade = capacidade;
    fila->frente = 0;
    fila->tras = -1;
    fila->itens = malloc(capacidade * sizeof(int));
    return fila;
}


//-----------------------------------------------Estrutura da Lista
typedef struct No{
    int posicaoInicial;
    char *doenca;
    struct No* proximo;
} No;

typedef struct Lista{
    No *inicio;
    No *fim;
} Lista;

//funções da Lista
Lista *criarLista(){
    Lista *lista = malloc(sizeof(Lista));
    lista->inicio = NULL;
    lista->fim = NULL;
    return lista;
}

void inserir(Lista *lista, char *doenca, int posicaoInicial){
    No *novoNo = malloc(sizeof(No));
    novoNo->posicaoInicial = posicaoInicial;
    novoNo->doenca = doenca;
    novoNo->proximo = NULL;
    if(lista->inicio == NULL){
        lista->inicio = novoNo;
        lista->fim = novoNo;
    }else{
        lista->fim->proximo = novoNo;
        lista->fim = novoNo;
    }

}

//função para verificar se uma subsequência é um motivo genético e retornar sua posição inicial e a doença correspondente
int ehMotivoGenetico(char *subseq, int tamanhoMinimo, char **doenca, int *posicaoInicial){
    if(strcmp(subseq, "TTT") == 0 || strcmp(subseq, "TTC") == 0){
        *posicaoInicial = 0;
        *doenca = "Fenilanina";
        return 1;
    }else if(strcmp(subseq, "TAT") == 0 || strcmp(subseq, "TAC") == 0){
        *posicaoInicial = 1;
        *doenca = "Tirosina  ";
        return 1;
    }else if(strcmp(subseq, "TGT") == 0 || strcmp(subseq, "TGC") == 0){
        *posicaoInicial = 2;
        *doenca = "Cisteina  ";
        return 1;
    }
    return 0;
}
//-----------------------------------------------Main
int main(){
    char dna[100]; //Sequência de DNA
    printf("Digite a sequencia de DNA: ");
    scanf("%s", &dna);

    int tamSequencia = strlen(dna);

    Pilha *pilha = criarPilha(tamSequencia);
    Lista *listaMotivos = criarLista();

    int i, j;

    printf("\nForam encotrados motivos geneticos...\n\n");
    //percorre a seq de DNA;
    for(i=0; i<tamSequencia;i++){
        //limpa pilha anter de procurar a nova
        pilha->topo = -1;
        //empilha suseq começando a partir do indice i
        for(j=i; j<i+3;j++){
            push(pilha, dna[j]);
        }

        //converter pilha para strinh
        char subseq[4]; //3 char da seq de DNA + 1 para o caracter nulo
        for(j=0; j < 3; j++){
            subseq[j] = pilha->itens[j];
        }
        subseq[j] = '\0';

        int posicaoInicial;
        char *doenca;
        //verifica se a subseq é um motivo gen
        if(ehMotivoGenetico(subseq, 3, &doenca, &posicaoInicial)){
            //se sim armazena sua posiçao inicial e a doença na lista
            inserir(listaMotivos, doenca, i);
            printf("> Motivo Genetico: %s = %s | Posicao: %d\n", subseq, doenca, i+1);
        }
    }

    //libera a memória alocada para pilha e listavv
    free(pilha->itens);
    free(pilha);

    No *atual = listaMotivos->inicio;
    No *proximo;
    while(atual != NULL){
        proximo = atual->proximo;
        free(atual);
        atual = proximo;
    }
    free(listaMotivos);

    return 0;
}
