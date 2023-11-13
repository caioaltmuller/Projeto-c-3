#include <stdio.h>
#include "Biblioteca.h"

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
            cadastrarNovaTarefa(&lt); // Chama a função de cadastrar a tarefa localizada nas bibliotecas .c e .h
        } else if (opcao == 2) {
            listarTarefas(lt); // Chama a função de listar as tarefas que já foram salvas
        } else if (opcao == 3) {
            deletarTarefa(&lt); // Deleta a tarefa selecionada pelo usuário
        } else if (opcao == 4) {
            salvarTarefas(&lt, "tarefas.txt"); // salva as tarefas em um arquivo.txt
        } else if (opcao == 5) {
            carregarTarefas(&lt, "tarefas.txt"); // carrega as taref as de um arquivo.txt
        } else if (opcao == 6) {
            alterarTarefa(&lt); // Altera uma tarefa selecionada pelo usuário
        } else if (opcao == 7) {
            filtrarPorPrioridade(lt); // Filtra tarefas por prioridade
        } else if (opcao == 8) {
            filtrarPorCategoria(lt); // Filtra tarefas por categoria
        } else if (opcao == 9) {
            filtrarPorCategoriaComPrioridade(lt); // Filtra tarefas por categoria e prioridade
        } else if (opcao == 10) {
            filtrarPorPrioridadeECategoria(lt); // Filtra tarefas por prioridade e categoria
        } else if (opcao == 11) {
            exportarPorPrioridade(lt, "export_prioridade.txt"); // Exporta tarefas por prioridade
        } else if (opcao == 12) {
            exportarPorCategoria(lt, "export_categoria.txt"); // Exporta tarefas por categoria
        } else if (opcao == 13) {
            exportarPorPrioridadeECategoria(lt, "export_prioridade_categoria.txt"); // Exporta tarefas por prioridade e categoria
        } else {
            printf("Opcao nao disponivel.\n"); // Mostra ao usuário que não existe a opção além de 1 a 13, e retorna as opções de entrada
        }
    }

    return 0;
}
