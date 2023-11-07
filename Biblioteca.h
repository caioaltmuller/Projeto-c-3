
//
// Created by Caio on 07/11/2023. 
//

#ifndef UNTITLED1_BIBLIOTECA_H
#define UNTITLED1_BIBLIOTECA_H

typedef struct { // Struct onde as tarefas estão armazenadas
    int prioridade;
    char categoria[100];
    char descricao[300];
} Tarefa;

typedef struct { // Struct que armazena a quantidade de tarefas
    Tarefa tarefas[100];
    int qtd;
} ListaDeTarefas; // O máximo de tarefas possíveis é 100

// Funções para o código de tarefas
int cadastrarTarefa(ListaDeTarefas *lt);
int deletarTarefa(ListaDeTarefas *lt);
int listarTarefas(ListaDeTarefas lt);
void alterarTarefa(ListaDeTarefas *lt);
void filtrarPorPrioridade(ListaDeTarefas lt);
void filtrarPorCategoria(ListaDeTarefas lt);
void filtrarPorCategoriaComPrioridade(ListaDeTarefas lt);
void filtrarPorPrioridadeECategoria(ListaDeTarefas lt);
void exportarPorPrioridade(ListaDeTarefas lt, char *arquivo);
void exportarPorCategoria(ListaDeTarefas lt, char *arquivo);
void exportarPorPrioridadeECategoria(ListaDeTarefas lt, char *arquivo);
void printMenu();
int salvarTarefas(ListaDeTarefas *lt, char *arquivo);
int carregarTarefas(ListaDeTarefas *lt, char *arquivo);

#endif //UNTITLED1_BIBLIOTECA_H