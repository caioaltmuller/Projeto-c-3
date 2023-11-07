#include <stdio.h>
#include "biblioteca.h"

int cadastrarTarefa(ListaDeTarefas *lt){ //função que é usada para cadastrar uma nova tarefa para o usuario
    printf("Digite a prioridade da tarefa (0 a 10): "); // define a prioridade da tarefa
    scanf("%d", &lt->tarefas[lt->qtd].prioridade); // define a entrada de dados da prioridade da tarefa e salva na struct
    getchar(); // Limpa o buffer de entrada
    printf("Descreva a tarefa: \n"); // define o que seria a tarefa
    fgets(lt->tarefas[lt->qtd].descricao, 300, stdin);
    lt->tarefas[lt->qtd].descricao[strcspn(lt->tarefas[lt->qtd].descricao, "\n")] = '\0'; // Remove a quebra de linha do final
    printf("Categorize a tarefa (menos importante a muito importante): "); // define o grau de importância da tarefa
    fgets(lt->tarefas[lt->qtd].categoria, 100, stdin);
    lt->tarefas[lt->qtd].categoria[strcspn(lt->tarefas[lt->qtd].categoria, "\n")] = '\0'; // Remove a quebra de linha do final
    lt->qtd++;
    printf("\n");
    return 0;
}

int deletarTarefa(ListaDeTarefas *lt){
    if (lt->qtd == 0) { // se o número de tarefas for zero
        printf("Nenhuma tarefa cadastrada.\n"); // aparece a mensagem de nenhuma tarefa cadastrada
        return 0;
    }

    printf("Escolha o numero da tarefa que deseja deletar (1 a %d): ", lt->qtd); //puxa as tarefas salvas em na struct
    int numeroTarefa;                                                                  // contabiliza o numero de tarefas
    scanf("%d", &numeroTarefa);                                                 // e da a opcao para o usuario de qual tarefa apagar

    if (numeroTarefa < 1 || numeroTarefa > lt->qtd) { // se o usuario digitar um número menor do que 1
        printf("Numero de tarefa invalido.\n");// retorna o print de numero invalido
        return 0;
    }

    // Remove a tarefa escolhida movendo as tarefas restantes uma posição para frente
    for (int i = numeroTarefa - 1; i < lt->qtd - 1; i++) {
        lt->tarefas[i] = lt->tarefas[i + 1];
    }

    lt->qtd--;
    printf("Tarefa deletada com sucesso.\n");

    return 0;
}

int listarTarefas(ListaDeTarefas lt){ // lsita o número de tarefas feitas pelo usuario
    if (lt.qtd == 0) {                // se o numero de tarefas for 0 retorna o print
        printf("Nenhum tarefa cadastrada\n");
        return 0;
    }

    for (int  i = 0; i < lt.qtd; i++) { // Pega a posição das tarefas e lista elas como "tarefa1", "tarefa2"...
        printf("Tarefa %d: \n", i+1);
        printf("Prioridade: %d\n", lt.tarefas[i].prioridade);
        printf("Descricao: %s\n", lt.tarefas[i].descricao);
        printf("Categoria: %s\n", lt.tarefas[i].categoria);
    }
    return 0;
}