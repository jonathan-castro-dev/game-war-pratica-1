// =================================================================
// PRÁTICA: CRIAÇÃO DO JOGO WAR ESTRUTURADO - PARTE 1
//
// OBJETIVO:
// Criar o cadastro e listagem dos cinco exércitos usando array
//
// =================================================================

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Constantes Globais
#define MAX_TROPAS 5
#define SIZE_STRING 30
#define MAX_BATALHAS 80

// Definição das Structs
struct Territorio {
  char nome[SIZE_STRING];
  char cor[SIZE_STRING];
  int tropas;
};

struct Batalha {
  int territorio_atacante;
  int dado_atacante;
  int territorio_defensor;
  int dado_defensor;
};

// Função para limpar o buffer de entrada
void limparBufferEntrada() {
  int c;
  while ((c = getchar()) != '\n' && c != EOF);
};

void cadastroDeTerritorios(struct Territorio territorios[MAX_TROPAS]) {
  for (int totalTropas = 0; totalTropas < MAX_TROPAS; totalTropas++) {
    printf("--- Cadastrando territorio %d ---\n", totalTropas + 1);
    printf("Nome do territorio: ");
    scanf("%s", territorios[totalTropas].nome);

    printf("Cor do exercito (ex: Azul, Verde): ");
    scanf("%s", territorios[totalTropas].cor);

    printf("Numero de tropas: ");
    scanf("%d", &territorios[totalTropas].tropas);
    limparBufferEntrada();
    printf("\n");
  };

  printf("Cadastro inicial concluido com sucesso!\n");
}

void listagemDosTerritorios(struct Territorio territorios[MAX_TROPAS]) {
  printf("============================================\n");
  printf("               MAPA DO MUNDO\n");
  printf("============================================\n");

  for (int totalTropas = 0; totalTropas < MAX_TROPAS; totalTropas++) {
    printf("%d. %s ", totalTropas + 1, territorios[totalTropas].nome);
    printf("(Exercito %s, Tropas: %d)\n", territorios[totalTropas].cor, territorios[totalTropas].tropas);
  };
}

void ataque(struct Batalha *batalha, struct Territorio territorios[MAX_TROPAS]) {
    printf("\n\n--- FASE DE ATAQUE ---\n");
    printf("Escolha o territorio atacante (de 1 a 5, ou 0 para sair do jogo): ");
    scanf("%d", &batalha->territorio_atacante);
    limparBufferEntrada();
    
    if (batalha->territorio_atacante == 0) {
      printf("Jogo encerrado...");
      
    } else {
      printf("Escolha o territorio defensor (de 1 a 5): ");
      scanf("%d", &batalha->territorio_defensor);
      limparBufferEntrada();
      
      if (territorios[batalha->territorio_atacante - 1].cor == territorios[batalha->territorio_defensor - 1].cor) {
        printf("\nOs territorios escolhidos estao dominados pelo mesmo exercito!\n");
      } else {
          srand(time(0));
    
          batalha->dado_atacante = (rand() % 6) + 1;
          batalha->dado_defensor = (rand() % 6) + 1;
          
          printf("\n--- RESULTADO DA BATALHA ---\n");
          printf("O atacante %s jogou um dado e tirou: %d\n", territorios[batalha->territorio_atacante - 1].nome, batalha->dado_atacante);
          printf("O defensor %s jogou um dado e tirou: %d\n", territorios[batalha->territorio_defensor - 1].nome, batalha->dado_defensor);
          
          // Resultado da batalha
          if (batalha->dado_atacante > batalha->dado_defensor) {
            printf("VITORIA DO ATACANTE! O defensor perdeu 1 tropa.\n");
            
            if (territorios[batalha->territorio_defensor - 1].tropas == 1) {
              strcpy(territorios[batalha->territorio_defensor - 1].cor, territorios[batalha->territorio_atacante - 1].cor);
              printf("CONQUISTA! O territorio %s foi dominado pelo exercito %s!\n", territorios[batalha->territorio_defensor - 1].nome, territorios[batalha->territorio_atacante - 1].cor);
            } else {
              territorios[batalha->territorio_atacante - 1].tropas += 1;
              territorios[batalha->territorio_defensor - 1].tropas -= 1;
            }
          } else if (batalha->dado_atacante == batalha->dado_defensor) {
            printf("A BATALHA DEU EMPATE! Nenhum territorio perdeu tropa.\n");
          } else {
            printf("VITORIA DO DEFENSOR! O atacante perdeu 1 tropa.\n");
            
            if (territorios[batalha->territorio_atacante - 1].tropas == 1) {
              strcpy(territorios[batalha->territorio_atacante - 1].cor, territorios[batalha->territorio_defensor - 1].cor);
              printf("CONQUISTA! O territorio %s foi dominado pelo exercito %s!\n", territorios[batalha->territorio_atacante - 1].nome, territorios[batalha->territorio_defensor - 1].cor);
            } else {
              territorios[batalha->territorio_atacante - 1].tropas -= 1;
              territorios[batalha->territorio_defensor - 1].tropas += 1;
            };
          };
      };
    };
};

void liberarMemoriaDinamica(struct Batalha *batalha, struct Territorio territorios[MAX_TROPAS]) {
  free(batalha);
  free(territorios);
};

// Função principal
int main() {
  // Criação de ponteiros
  struct Territorio *territorios;
  void (*iniciar_ataque)(struct Batalha *batalha, struct Territorio *territorios) = ataque;
  
  // Alocação dinâmica de memória
  territorios = calloc(MAX_TROPAS, sizeof(struct Territorio));
  
  struct Batalha* batalha = (struct Batalha*) malloc(MAX_BATALHAS * sizeof(struct Batalha));
  
  // Verificação de alocação de memória
  if (territorios == NULL || batalha == NULL) {
    printf("Falha ao alocar memória!\n");
  };
  
  // Laço principal - mensagem inicial do sistema
  printf("================================================\n");
  printf("Vamos cadastrar os 5 territorios iniciais do nosso mundo.\n");
  
  // Cadastro dos territórios
  cadastroDeTerritorios(territorios);
    
  do {
    // Listagem dos territórios
    listagemDosTerritorios(territorios);
    
    // Fase de ataque
    iniciar_ataque(batalha, territorios);
    
    printf("\n");
  } while (batalha->territorio_atacante != 0);
  
  // Liberação de memória dinâmica
  liberarMemoriaDinamica(batalha, territorios);
};