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
    int qtd_alfabeto;

    char estados[MAX_ESTADOS][TAM_ESTADOS];
    int qtd_estados;

    char estado_inicial[TAM_ESTADOS]; // Apenas 1 estado inicial

    char estados_finais[MAX_ESTADOS][TAM_ESTADOS];
    int qtd_finais;

    char transicoes[MAX_TRANSICOES][TAM_TRANSICOES];
    int qtd_transicoes;

    char palavras[MAX_PALAVRAS][TAM_PALAVRAS];
    int qtd_palavras;
}AFD;

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

void processararAFD(ListaDeLinhas *lista, AFD *afd){
    // Inicializa os contadores
    afd->qtd_alfabeto = 0;
    afd->qtd_estados = 0;
    afd->qtd_finais = 0;
    afd->qtd_transicoes = 0;
    afd->qtd_palavras = 0;
    char buffer[TAM_LINHAS];
    
    for(int i=0; i<lista->qtd; i++){
        strcpy(buffer, lista->texto[i]);
        
        // Delimitadores: espaço, quebra de linha e tabulação
        char *token = strtok(buffer, " \r\n"); 
        
        if(token == NULL) continue;

        if(strcmp(token, "A") == 0) { // [cite: 22]
            token = strtok(NULL, " \r\n"); 
            while(token != NULL) {
                strcpy(afd->alfabeto[afd->qtd_alfabeto], token);
                afd->qtd_alfabeto++;
                token = strtok(NULL, " \r\n"); // Correção: continua buscando por espaço
            }
        } 
        else if(strcmp(token, "Q") == 0) { // [cite: 23]
            token = strtok(NULL, " \r\n"); 
            while(token != NULL) {
                strcpy(afd->estados[afd->qtd_estados], token);
                afd->qtd_estados++;
                token = strtok(NULL, " \r\n");
            }
        }
        else if(strcmp(token, "q") == 0) { // [cite: 24]
            token = strtok(NULL, " \r\n");
            if(token != NULL) {
                strcpy(afd->estado_inicial, token);
            }
        }
        else if(strcmp(token, "F") == 0) { // [cite: 25]
            token = strtok(NULL, " \r\n"); 
            while(token != NULL) {
                strcpy(afd->estados_finais[afd->qtd_finais], token);
                afd->qtd_finais++;
                token = strtok(NULL, " \r\n");
            }
        }
        else if(strcmp(token, "T") == 0) { // 
            // Para transições, vamos guardar os tokens seguintes como uma string única ou processar
            // Vamos assumir formato: T Origem Simbolo Destino
            char t_origem[50], t_simb[50], t_dest[50];
            
            char *p1 = strtok(NULL, " \r\n");
            char *p2 = strtok(NULL, " \r\n");
            char *p3 = strtok(NULL, " \r\n");

            if (p1 && p2 && p3) {
                // Formata padronizado na struct: "Origem Simbolo Destino"
                sprintf(afd->transicoes[afd->qtd_transicoes], "%s %s %s", p1, p2, p3);
                afd->qtd_transicoes++;
            }
        }
        else if(strcmp(token, "P") == 0) { // [cite: 27]
            token = strtok(NULL, " \r\n");
            while(token != NULL) {
                strcpy(afd->palavras[afd->qtd_palavras], token);
                afd->qtd_palavras++;
                token = strtok(NULL, " \r\n");
            }
        }
    }
}

void imprimeAFD(AFD *afd){
    printf("Alfabeto (%d): ", afd->qtd_alfabeto);
    for(int i=0; i<afd->qtd_alfabeto; i++) printf("%s, ", afd->alfabeto[i]);
    printf("\n");

    printf("Estados (%d): ", afd->qtd_estados);
    for(int i=0; i<afd->qtd_estados; i++) printf("%s, ", afd->estados[i]);
    printf("\n");

    printf("Estado Inicial: [%s]\n", afd->estado_inicial);

    printf("Estados Finais (%d): ", afd->qtd_finais);
    for(int i=0; i<afd->qtd_finais; i++) printf("%s, ", afd->estados_finais[i]);
    printf("\n");
    
    printf("Transicoes (%d): ", afd->qtd_transicoes);
    for(int i=0; i<afd->qtd_transicoes; i++) printf("%s, ", afd->transicoes[i]);
    printf("\n");

    printf("Palavras (%d): ", afd->qtd_palavras);
    for(int i=0; i<afd->qtd_palavras; i++) printf("%s, ", afd->palavras[i]);
    printf("\n");
}

void processarPalavras(AFD *afd){
    for(int i=0; i < afd->qtd_palavras; i++) {
        char estadoAtual[TAM_ESTADOS];
        strcpy(estadoAtual, afd->estado_inicial); // Começa no estado inicial [cite: 9]
        int rejeitada = 0;
        char *palavra = afd->palavras[i];
        // Loop letra por letra da palavra
        for(int j=0; j < strlen(palavra); j++) {
            char proximoEstado[TAM_ESTADOS];
            if(obterProximoEstado(afd, estadoAtual, palavra[j], proximoEstado)) {
                strcpy(estadoAtual, proximoEstado); // Avança
            } else {
                rejeitada = 1; // Não há transição definida para este símbolo
                break;
            }
        }
        // Ao final da palavra, verifica se parou em um estado final
        if(!rejeitada && ehEstadoFinal(afd, estadoAtual)) {
            // Formato de saída exigido no PDF 
            printf("M aceita a palavra <%s>\n", palavra);
        } else {
            printf("M rejeita a palavra <%s>\n", palavra);
        }
    }
}

void processarTransicoes(AFD *afd, char *estadoAtual, char simbolo, char *estadoDestino){
    char s_simbolo[2] = {simbolo, '\0'}; // Converte char para string para comparar
    
    for(int i=0; i < afd->qtd_transicoes; i++) {
        char copia[TAM_TRANSICOES];
        strcpy(copia, afd->transicoes[i]);
        
        char *origem = strtok(copia, " ");
        char *lido = strtok(NULL, " ");
        char *destino = strtok(NULL, " ");
        
        // Verifica se a transição serve para o estado atual e o símbolo lido
        if(strcmp(origem, estadoAtual) == 0 && strcmp(lido, s_simbolo) == 0) {
            strcpy(estadoDestino, destino);
            return 1; // Sucesso
        }
    }
    return 0;}

int main(){
    ListaDeLinhas entrada;
    AFD afd;
    carregarArquivo("entradaAFD.txt", &entrada);
    //imprimeLinhas(&entrada);
    processararAFD(&entrada, &afd);
    imprimeAFD(&afd);
    return 0;
}