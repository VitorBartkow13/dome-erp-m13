#include <stdio.h>

// Estrutura utilizada para armazenar os dados de cada escala de trabalho
typedef struct {
    char nicho[10];
    int voluntarios;
    float horas;
    char supervisor[50];
} EscalaTrabalho;


// Exibe o menu principal do sistema
void exibirMenu() {

    printf("========================================================\n");
    printf("       DOME-ERP M13 - COZINHA E DIETA COMUNITARIA\n");
    printf("========================================================\n");
    printf("\n");

    printf("[1] Selecao do Arquivo de Entrada\n");
    printf("[2] Processamento do Arquivo de Entrada\n");
    printf("[3] Ajuste de Dados do Arquivo\n");
    printf("[4] Geracao do Arquivo de Saida\n");
    printf("[5] Dashboard e Estatisticas\n");
    printf("[0] Sair\n");
}


// Verifica se o arquivo informado pelo usuario existe e pode ser aberto
int selecionarArquivo(char nomeArquivo[]) {

    FILE *arquivo;

    printf("\n--- SELECAO DO ARQUIVO DE ENTRADA ---\n");

    printf("Digite o nome do arquivo: ");
    scanf("%99s", nomeArquivo);

    arquivo = fopen(nomeArquivo, "r");

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return 0;
    }
    else {
        printf("Arquivo encontrado com sucesso!\n");
        printf("Arquivo selecionado: %s\n", nomeArquivo);

        fclose(arquivo);

        return 1;
    }
}


// Le o arquivo de entrada e armazena os registros no vetor de estruturas
void processarArquivo(char nomeArquivo[],
                      int arquivoSelecionado,
                      EscalaTrabalho escala[],
                      int *quantidadeEscalas) {

    FILE *arquivo;
    char linha[100];
    int i = 0;

    printf("\n--- PROCESSAMENTO DO ARQUIVO DE ENTRADA ---\n");

    if (arquivoSelecionado == 0) {
        printf("Nenhum arquivo valido foi selecionado!\n");
        return;
    }

    printf("Processando o arquivo: %s\n", nomeArquivo);

    arquivo = fopen(nomeArquivo, "r");

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }

    // Le uma linha por vez, limitando o vetor a 15 registros
    while (fgets(linha, 100, arquivo) != NULL && i < 15) {

        // Separa os campos da linha utilizando ';' como delimitador
        sscanf(linha,
               "%9[^;];%d;%f;%49[^\n]",
               escala[i].nicho,
               &escala[i].voluntarios,
               &escala[i].horas,
               escala[i].supervisor);

        printf("%s | %d | %.1f | %s\n",
               escala[i].nicho,
               escala[i].voluntarios,
               escala[i].horas,
               escala[i].supervisor);

        i++;
    }

    // Atualiza a quantidade de registros carregados no programa principal
    *quantidadeEscalas = i;

    printf("\nTotal de escalas carregadas: %d\n",
           *quantidadeEscalas);

    fclose(arquivo);
}


// Calcula a carga total de atividade de cada nicho
void calcularHorasAtividade(EscalaTrabalho escala[],
                            int quantidadeEscalas) {

    int i;
    float horasAtividade;

    printf("\n--- HORAS DE ATIVIDADE ---\n");

    for (i = 0; i < quantidadeEscalas; i++) {

        horasAtividade =
            escala[i].voluntarios * escala[i].horas;

        printf("%s | Horas de atividade: %.1f\n",
               escala[i].nicho,
               horasAtividade);
    }
}


// Permite alterar a quantidade de voluntarios de um registro
void ajustarDados(EscalaTrabalho escala[],
                  int quantidadeEscalas) {

    int posicao;
    int i;
    int novaQuantidade;

    printf("\n--- AJUSTE DE DADOS ---\n");

    if (quantidadeEscalas == 0) {
        printf("Nenhum dado foi processado!\n");
        return;
    }

    printf("\nDados disponiveis:\n");

    for (i = 0; i < quantidadeEscalas; i++) {

        printf("[%d] %s | Voluntarios: %d | Horas: %.1f\n",
               i + 1,
               escala[i].nicho,
               escala[i].voluntarios,
               escala[i].horas);
    }

    // Repete enquanto o usuario escolher uma posicao inexistente
    do {

        printf("\nEscolha um registro entre 1 e %d: ",
               quantidadeEscalas);

        scanf("%d", &posicao);

        if (posicao < 1 || posicao > quantidadeEscalas) {
            printf("Posicao invalida! Tente novamente.\n");
        }

    } while (posicao < 1 || posicao > quantidadeEscalas);


    printf("\nRegistro selecionado: %s\n",
           escala[posicao - 1].nicho);


    // Nao permite quantidade de voluntarios igual ou menor que zero
    do {

        printf("Digite a nova quantidade de voluntarios: ");
        scanf("%d", &novaQuantidade);

        if (novaQuantidade <= 0) {
            printf("Quantidade invalida! Digite um valor maior que 0.\n");
        }

    } while (novaQuantidade <= 0);


    // O vetor inicia em 0, por isso utilizamos posicao - 1
    escala[posicao - 1].voluntarios = novaQuantidade;

    printf("Dados atualizados com sucesso!\n");

    printf("%s | Voluntarios: %d | Horas: %.1f\n",
           escala[posicao - 1].nicho,
           escala[posicao - 1].voluntarios,
           escala[posicao - 1].horas);
}


// Gera um novo arquivo contendo os dados atuais do vetor
void gerarArquivoSaida(EscalaTrabalho escala[],
                       int quantidadeEscalas) {

    FILE *arquivo;
    int i;

    printf("\n--- GERACAO DO ARQUIVO DE SAIDA ---\n");

    if (quantidadeEscalas == 0) {
        printf("Nenhum dado foi processado!\n");
        return;
    }

    // Modo "w" cria ou sobrescreve o arquivo de saida
    arquivo = fopen("dados_ajustados.txt", "w");

    if (arquivo == NULL) {
        printf("Erro ao criar arquivo de saida!\n");
        return;
    }

    for (i = 0; i < quantidadeEscalas; i++) {

        fprintf(arquivo,
                "%s;%d;%.1f;%s\n",
                escala[i].nicho,
                escala[i].voluntarios,
                escala[i].horas,
                escala[i].supervisor);
    }

    fclose(arquivo);

    printf("Arquivo dados_ajustados.txt gerado com sucesso!\n");
}


// Calcula e apresenta as principais estatisticas dos registros
void exibirDashboard(EscalaTrabalho escala[],
                     int quantidadeEscalas) {

    int i;
    int totalVoluntarios = 0;

    float totalHorasAtividade = 0;
    float horasAtividade;
    float maiorHoras;
    float menorHoras;

    printf("\n--- DASHBOARD E ESTATISTICAS ---\n");

    if (quantidadeEscalas == 0) {
        printf("Nenhum dado foi processado!\n");
        return;
    }

    // O primeiro registro e usado como referencia inicial
    maiorHoras =
        escala[0].voluntarios * escala[0].horas;

    menorHoras =
        escala[0].voluntarios * escala[0].horas;


    for (i = 0; i < quantidadeEscalas; i++) {

        totalVoluntarios =
            totalVoluntarios + escala[i].voluntarios;

        horasAtividade =
            escala[i].voluntarios * escala[i].horas;

        totalHorasAtividade =
            totalHorasAtividade + horasAtividade;


        if (horasAtividade > maiorHoras) {
            maiorHoras = horasAtividade;
        }

        if (horasAtividade < menorHoras) {
            menorHoras = horasAtividade;
        }
    }


    printf("Total de registros: %d\n",
           quantidadeEscalas);

    printf("Total de voluntarios: %d\n",
           totalVoluntarios);

    printf("Total de horas de atividade: %.1f\n",
           totalHorasAtividade);

    printf("Maior carga de atividade: %.1f\n",
           maiorHoras);

    printf("Menor carga de atividade: %.1f\n",
           menorHoras);
}


int main() {

    int opcao;
    int arquivoSelecionado = 0;

    char nomeArquivo[100];

    EscalaTrabalho escala[15];

    int quantidadeEscalas = 0;


    // Mantem o sistema em execucao ate o usuario escolher a opcao 0
    do {

        exibirMenu();

        printf("\nEscolha uma opcao: ");

        // Verifica se a entrada realmente e um numero
        if (scanf("%d", &opcao) != 1) {

            printf("\nEntrada invalida! Digite apenas numeros.\n");

            // Limpa caracteres invalidos que ficaram no buffer de entrada
            while (getchar() != '\n');

            opcao = -1;
        }


        // Direciona o programa para a funcao correspondente a opcao escolhida
        switch (opcao) {

            case 1:

                arquivoSelecionado =
                    selecionarArquivo(nomeArquivo);

                break;


            case 2:

                processarArquivo(nomeArquivo,
                                 arquivoSelecionado,
                                 escala,
                                 &quantidadeEscalas);

                if (quantidadeEscalas > 0) {

                    calcularHorasAtividade(
                        escala,
                        quantidadeEscalas);
                }

                break;


            case 3:

                ajustarDados(
                    escala,
                    quantidadeEscalas);

                break;


            case 4:

                gerarArquivoSaida(
                    escala,
                    quantidadeEscalas);

                break;


            case 5:

                exibirDashboard(
                    escala,
                    quantidadeEscalas);

                break;


            case 0:

                printf("\nSaindo do sistema...\n");

                break;


            default:

                printf("\nOpcao invalida!\n");
        }


    } while (opcao != 0);


    return 0;
}
