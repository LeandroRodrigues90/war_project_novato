// Inclusão das bibliotecas padrão necessárias para entrada/saída, alocação de memória, manipulação de strings e tempo.
#include <stdio.h>
#include <string.h>



// --- Constantes Globais ---
// Definem valores fixos para o número de territórios, missões e tamanho máximo de strings, facilitando a manutenção.
#define MAX_TROPAS 5
#define TAM_STRING_NOME 30
#define TAM_STRING_COR 10

// --- Estrutura de Dados ---
// Define a estrutura para um território, contendo seu nome, a cor do exército que o domina e o número de tropas.
struct Territorio
{
    char nome[TAM_STRING_NOME];
    char cor[TAM_STRING_COR];
    int tropas;
};

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
    int opcaoAtaque;
    int opcaoDefesa;

    printf("Vamos cadastrar 5 territorios iniciais do nosso mundo.\n\n");

    for (int i=0;i<MAX_TROPAS;i++){

            printf("---Cadastrando Territorio %d---\n",i+1);

            printf("Nome do Territorio: ");
            fgets(combat[i].nome,TAM_STRING_NOME,stdin);

            printf("Cor do Territorio (Ex:Azul,Verde...): ");
            fgets(combat[i].cor,TAM_STRING_COR,stdin);

            combat[i].nome[strcspn(combat[i].nome,"\n")]=0;
            combat[i].cor[strcspn(combat[i].cor,"\n")]=0;

            printf("Numero de tropas: ");
            scanf("%d",&combat[i].tropas);

            limparBufferEntrada();
            printf("\n");
           
        }
        do
        {
            printf("====================================\n");
            printf("      Mapa do mundo-Estado atual    \n");
            printf("=====================================\n");
        for (int i=0;i<MAX_TROPAS;i++){

            printf("%d- %s (Exercito: %s, Tropas:%d)\n",i+1,combat[i].nome,combat[i].cor,combat[i].tropas);
            
        }
            printf("\n            Fase de Ataque           \n");
            printf("----------------------------------------\n");
            printf("Escolha o Territorio do Atacante (1 a 5 ou 0 para sair): ");
            scanf("%d",&opcaoAtaque);
            
            if(opcaoAtaque>=1 || opcaoAtaque<=5){
                printf("Escolha o Territorio para defender(1 a 5): ");
                scanf("%d",&opcaoDefesa);
            }else{
                break;
            }

        } while (opcaoAtaque != 0);
            printf("Finalizando jogo...");


        return 0;
    }