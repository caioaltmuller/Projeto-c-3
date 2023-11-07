#include <stdio.h>
#include "biblioteca.h"

int main() {
    ListaDeTarefas lt;
    lt.qtd = 0; // Inicializa a quantidade de tarefas como 0

    int opcao;  // Laço de repetição que dá as opções de escolha para o usuário
    while(1) { // Enquanto for verdadeiro, irá continuar o laço até o usuário digitar "0"
        printMenu();
        scanf("%d", &opcao);

        if (opcao == 0) { // se a opção digitada pelo usuário for "0", sai do laço de repetição e interrompe o código
            break; // Sai do loop
        } else if (opcao == 1) {
            cadastrarTarefa(&lt); // Chama a função de cadastrar a tarefa localizada nas bibliotecas .c e .h
        } else if (opcao == 2) {
            listarTarefas(lt); // Chama a função de listar as tarefas que já foram salvas
        } else if (opcao == 3) {
            deletarTarefa(&lt); // Deleta a tarefa selecionada pelo usuário
        }
    }

    return 0;
}
