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

// Constantes Globais
#define MAX_TROPAS 5
#define SIZE_STRING 30

// Definição da Struct
struct Territorio {
  char nome[SIZE_STRING];
  char cor[SIZE_STRING];
  int tropas;
};

// Função para limpar o buffer de entrada
void limparBufferEntrada() {
  int c;
  while ((c = getchar()) != '\n' && c != EOF);
}

// Função principal
int main() {
  struct Territorio territorios[MAX_TROPAS];

  // Laço principal - mensagem inicial do sistema
    printf("================================================\n");
    printf("Vamos cadastrar os 5 territorios iniciais do nosso mundo.\n");
    
    for (int totalTropas = 0; totalTropas < 5; totalTropas++) {
      printf("--- Cadastrando território %d ---\n", totalTropas + 1);
      printf("Nome do territorio: ");
      fgets(territorios[totalTropas].nome, SIZE_STRING, stdin);

      printf("Cor do exercito (ex: Azul, Verde): ");
      fgets(territorios[totalTropas].cor, SIZE_STRING, stdin);

      printf("Numero de tropas: ");
      scanf("%d", &territorios[totalTropas].tropas);
      limparBufferEntrada();
      printf("\n");
    };

    printf("Cadastro inicial concluido com sucesso!\n");
    printf("============================================\n");
    printf("               MAPA DO MUNDO\n");
    printf("============================================\n");

    for (int totalTropas = 0; totalTropas < 5; totalTropas++) {
      printf("TERRITORIO %d:\n", totalTropas + 1);
      printf("  - Nome: %s", territorios[totalTropas].nome);
      printf("  - Dominado por: Exercito %s", territorios[totalTropas].cor);
      printf("  - Tropas: %d\n", territorios[totalTropas].tropas);
    };
};