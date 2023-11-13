#include <stdio.h>
#include "Biblioteca.h" 

int cadastrarNovaTarefa(ListaDeTarefas *lt){ //função que é usada para cadastrar uma nova tarefa para o usuario
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

void printMenu(){ // função usada para listar as opções do nosso código para o usuario
    printf("/// Bem vindo ao nosso codigo de listar tarefas, olhe as opcoes /// \n");
    printf("Opcao 1: Cadastrar nova tarefa\n"); // se opcao for 1,  cadastra uma nova tarefa
    printf("Opcao 2: Listar tarefa\n"); // se opcao for 2, lista as tarefas
    printf("Opcao 3: Deletar tarefa\n"); // se opcao for 3, deleta a tarefa selecionada pelo usuario
    printf("Opcao 4: Salvar tarefas\n"); // se opcao for 4, salva as tarefas em um arquivo txt
    printf("Opcao 5: Carregar tarefa\n"); // se opcao for 5, carrega as tarefas em um arquivo txt
    printf("Qual opcao voce deseja: "); // input do usuario de qual opcao ele deseja
}

int salvarTarefas(ListaDeTarefas *lt, char *arquivo) {
    FILE *arquivoTarefas = fopen(arquivo, "w");

    if (arquivoTarefas == NULL) {
        printf("Erro ao salvar tarefa.\n");
        return 1;
    }

    // Adicione um cabeçalho ao arquivo para armazenar o estado da lista
    fprintf(arquivoTarefas, "%d\n", lt->qtd); // Salve a quantidade de tarefas no arquivo

    for (int i = 0; i < lt->qtd; i++) {
        fprintf(arquivoTarefas, "%d\n", lt->tarefas[i].prioridade);
        fprintf(arquivoTarefas, "%s\n", lt->tarefas[i].descricao);
        fprintf(arquivoTarefas, "%s\n", lt->tarefas[i].categoria);
    }

    fclose(arquivoTarefas);
    printf("As tarefas foram salvas.\n");

    return 0;
}

int carregarTarefas(ListaDeTarefas *lt, char *arquivo) {
    FILE *arquivoTarefas = fopen(arquivo, "r");

    if (arquivoTarefas == NULL) {
        printf("Erro ao carregar arquivo.\n");
        return 1;
    }

    // Leitura do cabeçalho para obter a quantidade de tarefas
    if (fscanf(arquivoTarefas, "%d", &lt->qtd) != 1) {
        printf("Erro ao ler a quantidade de tarefas no arquivo.\n");
        fclose(arquivoTarefas);
        return 1;
    }
    fgetc(arquivoTarefas); // Consuma o caractere de nova linha após a quantidade

    // Carregue as tarefas com base na quantidade lida
    for (int i = 0; i < lt->qtd; i++) {
        fscanf(arquivoTarefas, "%d", &lt->tarefas[i].prioridade);
        fgetc(arquivoTarefas); // Consuma o caractere de nova linha após a prioridade
        fgets(lt->tarefas[i].descricao, 300, arquivoTarefas);
        lt->tarefas[i].descricao[strcspn(lt->tarefas[i].descricao, "\n")] = '\0';
        fgets(lt->tarefas[i].categoria, 100, arquivoTarefas);
        lt->tarefas[i].categoria[strcspn(lt->tarefas[i].categoria, "\n")] = '\0';
    }

    fclose(arquivoTarefas);
    printf("Tarefas carregadas com sucesso.\n");

    return 0;
}

void alterarTarefa(ListaDeTarefas *lt) {
    if (lt->qtd == 0) {
        printf("Nenhuma tarefa cadastrada.\n");
        return;
    }

    printf("Escolha o numero da tarefa que deseja alterar (1 a %d): ", lt->qtd);
    int numeroTarefa;
    scanf("%d", &numeroTarefa);

    if (numeroTarefa < 1 || numeroTarefa > lt->qtd) {
        printf("Numero de tarefa invalido.\n");
        return;
    }

    printf("Escolha o campo que deseja alterar:\n");
    printf("1. Prioridade\n");
    printf("2. Descrição\n");
    printf("3. Categoria\n");
    int escolhaCampo;
    scanf("%d", &escolhaCampo);

    if (escolhaCampo < 1 || escolhaCampo > 3) {
        printf("Escolha de campo invalida.\n");
        return;
    }

    printf("Digite o novo valor: ");
    getchar(); // Limpa o buffer de entrada
    char novoValor[300];
    fgets(novoValor, 300, stdin);
    novoValor[strcspn(novoValor, "\n")] = '\0'; // Remove a quebra de linha do final

    // Atualize o campo escolhido com o novo valor
    switch (escolhaCampo) {
        case 1:
            printf("Antiga Prioridade: %d\n", lt->tarefas[numeroTarefa - 1].prioridade);
            lt->tarefas[numeroTarefa - 1].prioridade = atoi(novoValor);
            printf("Nova Prioridade: %d\n", lt->tarefas[numeroTarefa - 1].prioridade);
            break;
        case 2:
            printf("Antiga Descrição: %s\n", lt->tarefas[numeroTarefa - 1].descricao);
            strncpy(lt->tarefas[numeroTarefa - 1].descricao, novoValor, sizeof(lt->tarefas[numeroTarefa - 1].descricao));
            break;
        case 3:
            printf("Antiga Categoria: %s\n", lt->tarefas[numeroTarefa - 1].categoria);
            strncpy(lt->tarefas[numeroTarefa - 1].categoria, novoValor, sizeof(lt->tarefas[numeroTarefa - 1].categoria));
            break;
    }
    printf("Tarefa alterada com sucesso.\n");
}

void filtrarPorPrioridade(ListaDeTarefas lt) {
    if (lt.qtd == 0) {
        printf("Nenhuma tarefa cadastrada.\n");
        return;
    }

    int prioridadeFiltrar;
    printf("Digite a prioridade para filtrar: ");
    scanf("%d", &prioridadeFiltrar);

    printf("Tarefas com prioridade %d:\n", prioridadeFiltrar);

    for (int i = 0; i < lt.qtd; i++) {
        if (lt.tarefas[i].prioridade == prioridadeFiltrar) {
            printf("Tarefa %d: %s\n", i + 1, lt.tarefas[i].descricao);
        }
    }
}

void filtrarPorCategoria(ListaDeTarefas lt) {
    if (lt.qtd == 0) {
        printf("Nenhuma tarefa cadastrada.\n");
        return;
    }

    char categoriaFiltrar[100];
    printf("Digite a categoria para filtrar: ");
    getchar(); // Limpa o buffer de entrada
    fgets(categoriaFiltrar, 100, stdin);
    categoriaFiltrar[strcspn(categoriaFiltrar, "\n")] = '\0'; // Remove a quebra de linha do final

    printf("Tarefas com categoria %s:\n", categoriaFiltrar);

    for (int i = 0; i < lt.qtd; i++) {
        if (strcmp(lt.tarefas[i].categoria, categoriaFiltrar) == 0) {
            printf("Tarefa %d: %s\n", i + 1, lt.tarefas[i].descricao);
        }
    }
}

void filtrarPorCategoriaComPrioridade(ListaDeTarefas lt) {
    if (lt.qtd == 0) {
        printf("Nenhuma tarefa cadastrada.\n");
        return;
    }

    char categoriaFiltrar[100];
    printf("Digite a categoria para filtrar: ");
    getchar(); // Limpa o buffer de entrada
    fgets(categoriaFiltrar, 100, stdin);
    categoriaFiltrar[strcspn(categoriaFiltrar, "\n")] = '\0'; // Remove a quebra de linha do final

    int prioridadeFiltrar;
    printf("Digite a prioridade para ordenar: ");
    scanf("%d", &prioridadeFiltrar);

    printf("Tarefas com categoria %s e prioridade >= %d:\n", categoriaFiltrar, prioridadeFiltrar);

    // Crie um vetor temporário para armazenar índices das tarefas que atendem aos critérios
    int tarefasFiltradas[lt.qtd];
    int qtdFiltradas = 0;

    for (int i = 0; i < lt.qtd; i++) {
        if (strcmp(lt.tarefas[i].categoria, categoriaFiltrar) == 0 && lt.tarefas[i].prioridade >= prioridadeFiltrar) {
            tarefasFiltradas[qtdFiltradas] = i;
            qtdFiltradas++;
        }
    }

    // Ordene o vetor de índices com base na prioridade
    for (int i = 0; i < qtdFiltradas - 1; i++) {
        for (int j = i + 1; j < qtdFiltradas; j++) {
            if (lt.tarefas[tarefasFiltradas[i]].prioridade < lt.tarefas[tarefasFiltradas[j]].prioridade) {
                int temp = tarefasFiltradas[i];
                tarefasFiltradas[i] = tarefasFiltradas[j];
                tarefasFiltradas[j] = temp;
            }
        }
    }

    for (int i = 0; i < qtdFiltradas; i++) {
        int index = tarefasFiltradas[i];
        printf("Tarefa %d (Prioridade: %d): %s\n", index + 1, lt.tarefas[index].prioridade, lt.tarefas[index].descricao);
    }
}

void filtrarPorPrioridadeECategoria(ListaDeTarefas lt) {
    if (lt.qtd == 0) {
        printf("Nenhuma tarefa cadastrada.\n");
        return;
    }

    char categoriaFiltrar[100];
    printf("Digite a categoria para filtrar: ");
    getchar(); // Limpa o buffer de entrada
    fgets(categoriaFiltrar, 100, stdin);
    categoriaFiltrar[strcspn(categoriaFiltrar, "\n")] = '\0'; // Remove a quebra de linha do final

    int prioridadeFiltrar;
    printf("Digite a prioridade para filtrar: ");
    scanf("%d", &prioridadeFiltrar);

    printf("Tarefas com categoria %s e prioridade %d:\n", categoriaFiltrar, prioridadeFiltrar);

    for (int i = 0; i < lt.qtd; i++) {
        if (strcmp(lt.tarefas[i].categoria, categoriaFiltrar) == 0 && lt.tarefas[i].prioridade == prioridadeFiltrar) {
            printf("Tarefa %d: %s\n", i + 1, lt.tarefas[i].descricao);
        }
    }
}

void exportarPorPrioridade(ListaDeTarefas lt, char *arquivo) {
    if (lt.qtd == 0) {
        printf("Nenhuma tarefa cadastrada.\n");
        return;
    }

    int prioridadeExportar;
    printf("Digite a prioridade para exportar: ");
    scanf("%d", &prioridadeExportar);

    FILE *arquivoTarefas = fopen(arquivo, "w");

    if (arquivoTarefas == NULL) {
        printf("Erro ao exportar tarefas.\n");
        return;
    }

    for (int i = 0; i < lt.qtd; i++) {
        if (lt.tarefas[i].prioridade == prioridadeExportar) {
            fprintf(arquivoTarefas, "%d\n", lt.tarefas[i].prioridade);
            fprintf(arquivoTarefas, "%s\n", lt.tarefas[i].categoria);
            fprintf(arquivoTarefas, "%s\n", lt.tarefas[i].descricao);
        }
    }

    fclose(arquivoTarefas);
    printf("Tarefas exportadas com sucesso.\n"); 
}

void exportarPorCategoria(ListaDeTarefas lt, char *arquivo) {
    if (lt.qtd == 0) {
        printf("Nenhuma tarefa cadastrada.\n");
        return;
    }

    char categoriaExportar[100];
    printf("Digite a categoria para exportar: ");
    getchar(); // Limpa o buffer de entrada
    fgets(categoriaExportar, 100, stdin);
    categoriaExportar[strcspn(categoriaExportar, "\n")] = '\0'; // Remove a quebra de linha do final

    FILE *arquivoTarefas = fopen(arquivo, "w");

    if (arquivoTarefas == NULL) {
        printf("Erro ao exportar tarefas.\n");
        return;
    }

    // Crie um vetor temporário para armazenar índices das tarefas que atendem aos critérios
    int tarefasFiltradas[lt.qtd];
    int qtdFiltradas = 0;

    for (int i = 0; i < lt.qtd; i++) {
        if (strcmp(lt.tarefas[i].categoria, categoriaExportar) == 0) {
            tarefasFiltradas[qtdFiltradas] = i;
            qtdFiltradas++;
        }
    }

    // Ordene o vetor de índices com base na prioridade
    for (int i = 0; i < qtdFiltradas - 1; i++) {
        for (int j = i + 1; j < qtdFiltradas; j++) {
            if (lt.tarefas[tarefasFiltradas[i]].prioridade < lt.tarefas[tarefasFiltradas[j]].prioridade) {
                int temp = tarefasFiltradas[i];
                tarefasFiltradas[i] = tarefasFiltradas[j];
                tarefasFiltradas[j] = temp;
            }
        }
    }

    for (int i = 0; i < qtdFiltradas; i++) {
        int index = tarefasFiltradas[i];
        fprintf(arquivoTarefas, "%d\n", lt.tarefas[index].prioridade);
        fprintf(arquivoTarefas, "%s\n", lt.tarefas[index].categoria);
        fprintf(arquivoTarefas, "%s\n", lt.tarefas[index].descricao);
    }

    fclose(arquivoTarefas);
    printf("Tarefas exportadas com sucesso.\n");
}

void exportarPorPrioridadeECategoria(ListaDeTarefas lt, char *arquivo) {
    if (lt.qtd == 0) {
        printf("Nenhuma tarefa cadastrada.\n");
        return;
    }

    char categoriaExportar[100];
    printf("Digite a categoria para exportar: ");
    getchar(); // Limpa o buffer de entrada
    fgets(categoriaExportar, 100, stdin);
    categoriaExportar[strcspn(categoriaExportar, "\n")] = '\0'; // Remove a quebra de linha do final

    int prioridadeExportar;
    printf("Digite a prioridade para exportar: ");
    scanf("%d", &prioridadeExportar);

    FILE *arquivoTarefas = fopen(arquivo, "w");

    if (arquivoTarefas == NULL) {
        printf("Erro ao exportar tarefas.\n");
        return;
    }

    for (int i = 0; i < lt.qtd; i++) {
        if (strcmp(lt.tarefas[i].categoria, categoriaExportar) == 0 && lt.tarefas[i].prioridade == prioridadeExportar) {
            fprintf(arquivoTarefas, "%d\n", lt.tarefas[i].prioridade);
            fprintf(arquivoTarefas, "%s\n", lt.tarefas[i].categoria);
            fprintf(arquivoTarefas, "%s\n", lt.tarefas[i].descricao);
        }
    }

    fclose(arquivoTarefas);
    printf("Tarefas exportadas com sucesso.\n");
}
