// Bibliotecas
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definindo limites
#define MAX_LINHAS 100
#define TAM_LINHAS 256

//Para armazenar as linhas
typedef struct{
    char texto[MAX_LINHAS][TAM_LINHAS]; //matriz
    int qtd; //qtd de linhas
}ListaDeLinhas;

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

int main(){
    ListaDeLinhas entrada;
    carregarArquivo("entradaAFD.txt", &entrada);
    imprimeLinhas(&entrada);
    return 0;
}