# DOME-ERP M13 — Cozinha e Dieta Comunitária 🍽️

Projeto acadêmico desenvolvido em **C** durante o curso de Ciência da Computação.

O projeto faz parte do **DOME-ERP**, um sistema modular ambientado em uma comunidade Solarpunk. O módulo M13 é responsável pela área de **Cozinha e Dieta Comunitária**.

## 🚀 Sprint 1

A primeira Sprint teve como objetivo desenvolver a estrutura inicial e o fluxo de funcionamento do módulo.

O programa recebe dados de escalas de trabalho através de um arquivo `.txt`, processa essas informações e permite a interação através de um menu no terminal.

### Funcionalidades

- Menu interativo no terminal
- Seleção de arquivo de entrada
- Leitura e processamento de arquivos `.txt`
- Armazenamento dos registros utilizando `struct`
- Uso de vetor de estruturas
- Cálculo das horas de atividade
- Ajuste da quantidade de voluntários
- Validação de entradas
- Geração de arquivo de saída
- Dashboard com estatísticas
- Identificação da maior e menor carga de atividade

## 🧠 Conceitos utilizados

Durante o desenvolvimento foram aplicados conceitos fundamentais da linguagem C:

- Structs
- Vetores
- Ponteiros
- Funções
- Passagem de parâmetros
- `switch/case`
- `for`, `while` e `do-while`
- Manipulação de arquivos
- `fopen`, `fgets`, `sscanf`, `fprintf` e `fclose`
- Validação de entrada com `scanf`

## 📂 Arquivos

`main.c`  
Código-fonte principal do sistema.

`escala_trabalho.txt`  
Arquivo utilizado como entrada de dados.

`dados_ajustados.txt`  
Arquivo gerado pelo programa após o processamento e ajuste dos dados.

## ▶️ Como executar

Coloque `main.c` e `escala_trabalho.txt` na mesma pasta.

Compile e execute o programa.

No menu, selecione:

1. Seleção do Arquivo de Entrada
2. Processamento do Arquivo de Entrada
3. Ajuste de Dados
4. Geração do Arquivo de Saída
5. Dashboard e Estatísticas

Quando solicitado o arquivo de entrada, informe:

`escala_trabalho.txt`

## 📈 Próximos passos

A Sprint 2 dará continuidade ao projeto com foco em:

- Modelagem de novas structs
- Structs aninhadas
- Maior modularização do código
- Aprimoramento da manipulação de arquivos
- Integração da saída do módulo com a pipeline do DOME-ERP
- Melhorias na interface do terminal

## 📌 Status

✅ Sprint 1 — Concluída  
🚧 Sprint 2 — Em desenvolvimento
