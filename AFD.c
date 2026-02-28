// Bibliotecas
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definindo limites
#define MAX_LINHAS 100
#define TAM_LINHAS 256
#define MAX_ALFABETO 50
#define TAM_ALFABETO 50 
#define MAX_ESTADOS 50
#define TAM_ESTADOS 50
#define TAM_ESTADO_INICIAL 50
#define TAM_ESTADOS_FINAIS 50
#define MAX_ESTADOS_FINAIS 50   
#define MAX_TRANSICOES 100
#define TAM_TRANSICOES 100
#define MAX_PALAVRAS 100
#define TAM_PALAVRAS 100

//Para armazenar as linhas
typedef struct{
    char texto[MAX_LINHAS][TAM_LINHAS]; //matriz
    int qtd; //qtd de linhas
}ListaDeLinhas;

typedef struct{
    char alfabeto[MAX_ALFABETO][TAM_ALFABETO];
    char estados[MAX_ESTADOS][TAM_ESTADOS];
    char estado_inicial[TAM_ESTADO_INICIAL];
    char estados_finais[MAX_ESTADOS_FINAIS][TAM_ESTADOS_FINAIS];
    char transicoes  [MAX_TRANSICOES][TAM_TRANSICOES];
    char palavras[MAX_PALAVRAS][TAM_PALAVRAS];
}AFD

//Função que lê o arquivo, ignora as linhas com '#' e armazena as outras no struct
void carregarArquivo(const char *Nomearquivo, ListaDeLinhas *lista){
    FILE *arquivo = fopen(Nomearquivo, "r");
    lista->qtd =0;
    if(arquivo==NULL){
        printf("Erro: Não foi possível abrir o arquivo!");
        return;
    }
    char linha[TAM_LINHAS];
    while(fgets(linha, TAM_LINHAS, arquivo) != NULL){
        if(linha[0]=='#'){
            continue; //força o loop a continuar, ignorando essa linha
        }
        if(lista->qtd >= MAX_LINHAS){ // Se a lista encher, para de ler
            printf("Limite de linhas atingido!");
            break;
        }
        // Copia a linha para a lista de listas, onde armazenaremos as linhas para usá-las depois
        strcpy(lista->texto[lista->qtd], linha);//destino -> origem, ou seja, veio do buffer "linha" e vai para a lista de lista
        lista->qtd++;
    }
    fclose(arquivo);
}

void imprimeLinhas(ListaDeLinhas *lista){
    for(int i=0; i<lista->qtd; i++){
        printf("%s", lista->texto[i]);
    }
}

processararAFD(ListaDeLinhas *lista){
    // Aqui você pode implementar a lógica para processar as linhas do AFD
    // Por exemplo, você pode criar uma estrutura para representar o AFD e preencher essa estrutura com base nas linhas lidas
}

int main(){
    ListaDeLinhas entrada;
    carregarArquivo("entradaAFD.txt", &entrada);
    imprimeLinhas(&entrada);
    return 0;
}