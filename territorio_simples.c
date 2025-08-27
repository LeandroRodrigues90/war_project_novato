#include <stdio.h>
#include <string.h>

// Inclusão das bibliotecas padrão necessárias para entrada/saída, alocação de memória, manipulação de strings e tempo.
#define MAX_TROPAS 5
#define TAM_STRING_NOME 30
#define TAM_STRING_COR 10
// --- Constantes Globais ---
// Definem valores fixos para o número de territórios, missões e tamanho máximo de strings, facilitando a manutenção.
struct Territorio
{
    char nome[TAM_STRING_NOME];
    char cor[TAM_STRING_COR];
    int tropas;
};

// --- Estrutura de Dados ---
// Define a estrutura para um território, contendo seu nome, a cor do exército que o domina e o número de tropas.

// --- Protótipos das Funções ---
void limparBufferEntrada(){
    int c;
    while ((c=getchar()) !='\n' && c !=EOF);
    
}

// Declarações antecipadas de todas as funções que serão usadas no programa, organizadas por categoria.
// Funções de setup e gerenciamento de memória:
// Funções de interface com o usuário:
// Funções de lógica principal do jogo:
// Função utilitária:

// --- Função Principal (main) ---
// Função principal que orquestra o fluxo do jogo, chamando as outras funções em ordem.
int main() {

    struct Territorio combat[MAX_TROPAS];
    

    printf("Vamos cadastrar 5 territorios iniciais do nosso mundo.\n\n");

    for (int i=0;i<MAX_TROPAS;i++){

            printf("---Cadastrando Territorio %d---\n",i+1);

            printf("Nome do Territorio: ");
            fgets(combat[i].nome,TAM_STRING_NOME,stdin);

            printf("Cor do Territorio:(Azul,Verde...) ");
            fgets(combat[i].cor,TAM_STRING_COR,stdin);

            combat[i].nome[strcspn(combat[i].nome,"\n")]=0;
            combat[i].cor[strcspn(combat[i].cor,"\n")]=0;

            printf("Numero de tropas: ");
            scanf("%d",&combat[i].tropas);

            limparBufferEntrada();
            printf("\n");
           
        }
        printf("Relatório de Territorios cadastrados\n");
        printf("--------------------------------\n");
        for (int i=0;i<MAX_TROPAS;i++){

            printf("\n");
            printf("Territorio -%d\n",i+1);
            printf("Nome do Territorio: %s\n",combat[i].nome);
            printf("Cor do Territorio: %s\n",combat[i].cor);
            printf("Tropas: %d\n",combat[i].tropas);
            printf("\n");
            printf("---------------------------------\n\n");
        }

        return 0;
    }