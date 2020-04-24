///HIAGO MURILO LIMA INDALECIO

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include<locale.h>
#include <conio.h>
#include <ctype.h>

#define MAXEST 4000
#define MAXFOR 200

struct estoque
{
    char descricao[40], tipoPeca[15];
    int cod, quantidade, qtdMinima;
};
typedef struct estoque Estoque;

struct fornecedor
{
    char cnpj[20], tipoPeca[15], razaoSocial[40], endereco[60], telefone[14];
    float preco;
};
typedef struct fornecedor Fornecedor;

struct entrega
{
    char cnpj[20];
    int codPeca, quant;
    float preco;
};
typedef struct entrega EntregaRealizada;

///protótipos de funções
void ExibirMenu();
char digitaOpcao();
Estoque digitaPeca();
int existePeca(Estoque umaPeca, Estoque pecas[], int quantasPecas);
int inserirNovaPeca(Estoque pecas[], int *quantasPecas);
Fornecedor digitaFornecedor();
int existeFornecedor(Fornecedor umFornecedor, Fornecedor fornecedores[], int quantosFornecedores);
int inserirNovoFornecedor(Fornecedor fornecedores[], int *quantosFornecedores);
Estoque digitaPecaRemover();
int RemoverPeca(Estoque pecas[], int quantasPecas, Fornecedor fornecedores[], int quantosFornecedores, EntregaRealizada entregasRealizadas[], int *quantasEntregas);
int encontrarIndice(Estoque umaPeca, Estoque pecas[], int quantasPecas);
int ComprarPeca(Estoque pecas[], int quantos, Fornecedor fornecedores[], int quantosFornecedores, int indicePeca, EntregaRealizada entregasRealizadas[], int *quantasEntregas);
Estoque digitarCompra();
int ConsultarFornecedores(Fornecedor fornecedores[], int quantosFornecedores, int indicePeca, Estoque pecas[]);
void ImprimirEntregas(EntregaRealizada entregasRealizadas[], int quantasEntregas);
void ImprimirEstoqueBaixo(Estoque pecas[], int quantasPecas, Fornecedor fornecedores[], int quantosFornecedores, EntregaRealizada entregasRealizadas[], int *quantasEntregas);
void ImprimirEstoque(Estoque pecas[], int quantas);
void ordenarPecas(Estoque pecas[], int quantas);
void ImprimirFornecedores(Fornecedor fornecedores[], int quantos);
void ordenarFornecedores(Fornecedor fornecedores[], int quantos);

///funções
/* 1. Objetivo da função: Exibir o menu principal.
   2. Resumo de seu funcionamento: Imprime na tela as opções de menu.
   3. Descrição dos parâmetros de entrada: .
   4. Descrição dos parâmetros de saída e/ou valores retornados: Texto de tópicos de menu.
   5. Observações: */
void ExibirMenu()
{
    printf("\n\tMenu de Opcoes\n\n1. Inserir nova peça\n2. Inserir novo fornecedor\n3. Retirar peça\n4. Relatório de estoque abaixo do permitido\n5. Relatório de peça\n6. Relatório de fornecedores\n7. Relatório de entrega de peças\n8. Comprar estoque\nS. Sair");
}

/* 1. Objetivo da função: Exibir mensagem de escolha de opção.
   2. Resumo de seu funcionamento: Coleta uma opção de menu.
   3. Descrição dos parâmetros de entrada: .
   4. Descrição dos parâmetros de saída e/ou valores retornados: Variável tipo 'char'.
   5. Observações: */
char digitaOpcao()
{
  char opcao;
  fflush(stdin);
  printf("\nDigite sua opcao: ");
  opcao = toupper(getchar());
  return(opcao);
}

///funções para manipulação de peças
/* 1. Objetivo da função: Digitar as características de uma peça.
   2. Resumo de seu funcionamento: Pega as informações do tipo Estoque.
   3. Descrição dos parâmetros de entrada: .
   4. Descrição dos parâmetros de saída e/ou valores retornados: Peça preenchida.
   5. Observações: texto. */
Estoque digitaPeca()
{
  Estoque nova;
  fflush(stdin);
  printf("\nDigite a descrição da peça: ");
  gets(nova.descricao);
  fflush(stdin);
  printf("\nDigite o tipo da peça: ");
  gets(nova.tipoPeca);
  fflush(stdin);
  printf("\nDigite o código da peça: ");
  scanf("%i", &nova.cod);
  fflush(stdin);
  printf("\nDigite a quantidade mínima que a peça terá em estoque: ");
  scanf("%i", &nova.qtdMinima);
  fflush(stdin);
  do{
  printf("\nDigite a quantidade que deseja adicionar ao estoque: ");
  scanf("%i", &nova.quantidade);
    if(nova.quantidade < nova.qtdMinima * 2)
    {
        fflush(stdin);
        puts("\nO estoque deve ter no mínimo duas vezes o estoque mínimo!\n");
        system("pause");
    }
  }while(nova.quantidade < nova.qtdMinima * 2);
  return(nova);
}

/* 1. Objetivo da função: Analizar a existência de uma peça no array de peças cadastradas.
   2. Resumo de seu funcionamento: Uma estrutura de repetição caminha pelo array procurando igualidade entre as informações.
   3. Descrição dos parâmetros de entrada: Variável do tipo Estoque, array do tipo Estoque, um inteiro.
   4. Descrição dos parâmetros de saída e/ou valores retornados: Valor booleando indicando a existência da peça no array.
   5. Observações: */
int existePeca(Estoque umaPeca, Estoque pecas[], int quantasPecas)
{
  int i, achou = 0;
  for(i = 0; i < quantasPecas && !achou; i++)
  {
    if(umaPeca.cod == pecas[i].cod)
    {
      achou = 1;
    }
  }
  return(achou);
}

/* 1. Objetivo da função: Fazer a inserção de uma nova peça no sistema.
   2. Resumo de seu funcionamento: É analisado se existe espaço para uma nova peça e se ja existe uma peça igual, em seguida se esta passar por estes dois testes ela é inserida no array de peças cadastradas.
   3. Descrição dos parâmetros de entrada: Array do tipo Estoque e inteiro indicando a quantidade de peças cadastradas.
   4. Descrição dos parâmetros de saída e/ou valores retornados: Valor booleando validando a inserção de uma nova peça.
   5. Observações: */
int inserirNovaPeca(Estoque pecas[], int *quantasPecas)
{
  Estoque novaPeca;
  int oQueRetorna = 1; ///deu certo inserir nova peça
  if(*quantasPecas == MAXEST)
  {
    oQueRetorna = 0; /// NÃO deu certo inserir nova peça
  }
  else
  {
    do
    {
      novaPeca = digitaPeca();
      if(existePeca(novaPeca, pecas, *quantasPecas))
      {
        fflush(stdin);
        puts("\nERRO.\nO código da peça já está cadastrado.\nPor favor digite um novo código.");
        system("pause");
      }
    }
    while(existePeca(novaPeca, pecas, *quantasPecas));
    pecas[(*quantasPecas)++] = novaPeca;
  }
  return(oQueRetorna);
}

/* 1. Objetivo da função: Recolher informações do tipo Estoque.
   2. Resumo de seu funcionamento: Coleta informações do tipo Estoque.
   3. Descrição dos parâmetros de entrada: .
   4. Descrição dos parâmetros de saída e/ou valores retornados: Variável do tipo peça com dois campos preenchidos.
   5. Observações: */
Estoque digitaPecaRemover()
{
    Estoque umaPeca;
    printf("\nDigite o código da peça: ");
    scanf("%i", &umaPeca.cod);
    fflush(stdin);
    printf("\nDigite a quantidade a ser removida: ");
    scanf("%i", &umaPeca.quantidade);
    return(umaPeca);
}

/* 1. Objetivo da função: Remover peças do estoque.
   2. Resumo de seu funcionamento: Encontra uma peça que o usuário fornece no arrayu de peças cadastradas, em seguida verifica se tem peças o suficiente no sistema para a remoção
   e em seguida remove as peças; caso a quantidade de peças passe a ser menor do que o permitido é sugerida uma reposição.
   3. Descrição dos parâmetros de entrada: Array de peças cadastradas do tipo Estoque, inteiro de quantas peças cadastradas, arrai=y de fornecedores do tipo Fornecedor, inteiro de
   quantos fornecedores cadastrados, array de entregas realizadas do tipo EntregaRealizada e inteiro de quantas entregas realizadas.
   4. Descrição dos parâmetros de saída e/ou valores retornados: Valor booleando validando a remoção de peças.
   5. Observações: */
int RemoverPeca(Estoque pecas[], int quantasPecas, Fornecedor fornecedores[], int quantosFornecedores, EntregaRealizada entregasRealizadas[], int *quantasEntregas)
{
    Estoque umaPeca;
    int indice;
    int oQueRetorna = 1;///Deu certo remover peça
    do
    {
      umaPeca = digitaPecaRemover();
      if(encontrarIndice(umaPeca, pecas, quantasPecas) == -1)
      {
        fflush(stdin);
        puts("\nERRO. O código da peça não está cadastrado.");
        system("pause");
        oQueRetorna = 0;
      }
    }
    while(encontrarIndice(umaPeca, pecas, quantasPecas) == -1);
    indice = encontrarIndice(umaPeca, pecas, quantasPecas);
    if(pecas[indice].quantidade < umaPeca.quantidade)
    {
        oQueRetorna = 0;
    }
    else
    {
        pecas[indice].quantidade -= umaPeca.quantidade;
        if(pecas[indice].quantidade < pecas[indice].qtdMinima)
        {
            fflush(stdin);
            puts("\nA peça está com o estoque a baixo do nível mínimo!\nSerá necessária uma nova compra para que o estoque seja o dobro da quantidade mínima.\n");
            system("pause");
            int quantos = (pecas[indice].qtdMinima - pecas[indice].quantidade) + pecas[indice].qtdMinima;
            if(ComprarPeca(pecas, quantos, fornecedores, quantosFornecedores, indice, entregasRealizadas, quantasEntregas))
            {
                fflush(stdin);
                puts("\nPeças compradas com sucesso!");
                system("pause");
            }
            else
            {
                fflush(stdin);
                puts("\nNão foi possível comprar as peças.");
                system("pause");
            }
        }
        oQueRetorna = 1;
    }
    return(oQueRetorna);
}

/* 1. Objetivo da função: Realizar a compra de uma determinada quantidade de uma determinada peça, registrando a entrega da mesma.
   2. Resumo de seu funcionamento: Encontra a peça indicada pelo usuário e em seguida pesquisa preços em fornecedores por fim realizando a compra.
   3. Descrição dos parâmetros de entrada: Array de peças do tipo Estoque, inteiro de quantas peças comprar, array de fornecedores do tipo Fornecedor, inteiro de quantos fornecedores cadastrados, inteiro de índice da peça para realizar a compra,
   array de entregas realizadas do tipo EntregaRealizada e inteiro de qauntas entregas realizadas.
   4. Descrição dos parâmetros de saída e/ou valores retornados: Booleando validando a compra da peça.
   5. Observações: */
int ComprarPeca(Estoque pecas[], int quantos, Fornecedor fornecedores[], int quantosFornecedores, int indicePeca, EntregaRealizada entregasRealizadas[], int *quantasEntregas)
{
    int oQueRetorna = 0, indiceFornecedor;
    char opcao;
    if(indicePeca < 0)
    {
        puts("\nO índice não existe!");
        system("pause");
    }
    else
    {
        if(ConsultarFornecedores(fornecedores, quantosFornecedores, indicePeca, pecas) >= 0)
        {
            indiceFornecedor = ConsultarFornecedores(fornecedores, quantosFornecedores, indicePeca, pecas);
            printf("\n%s. O fornecedor com o menor preço para este tipo de peça é o %s, o total da compra será R$%.2f\nDigite 'S' para comprar ou 'N' para cancelar a compra: ", pecas[indicePeca].descricao, fornecedores[indiceFornecedor].razaoSocial, fornecedores[indiceFornecedor].preco * quantos);
            fflush(stdin);
            opcao = toupper(getchar());
            if(opcao == 'S')
            {
                pecas[indicePeca].quantidade += quantos;
                strcpy(entregasRealizadas[*quantasEntregas].cnpj, fornecedores[indiceFornecedor].cnpj);
                entregasRealizadas[*quantasEntregas].codPeca = pecas[indicePeca].cod;
                entregasRealizadas[*quantasEntregas].preco = fornecedores[indiceFornecedor].preco * quantos;
                entregasRealizadas[(*quantasEntregas)++].quant = quantos;
                oQueRetorna = 1;
            }
            else
            {
                puts("\nCompra cancelada!");
                system("pause");
            }
        }
    }
    return(oQueRetorna);
}

/* 1. Objetivo da função: Digitar as características de uma peça para compra.
   2. Resumo de seu funcionamento: Pega as informações do tipo Estoque.
   3. Descrição dos parâmetros de entrada: .
   4. Descrição dos parâmetros de saída e/ou valores retornados: Peça preenchida.
   5. Observações: texto. */
Estoque digitarCompra()
{
    Estoque umaPeca;
    printf("\nDigite o código da peça: ");
    scanf("%i", &umaPeca.cod);
    return(umaPeca);
}

/* 1. Objetivo da função: Consultar o array de fornecedores procurando o mais barato.
   2. Resumo de seu funcionamento: Uma estrutura de repetição percorrei o array do tipo Fornecedor procurando o que tem o preço mais barato.
   3. Descrição dos parâmetros de entrada: Array de fornecedores do tipo Fornecedor, inteiro de quantos fornecedores cadastrados, inteiro de indice da peça e array de peças do tipo Estoque.
   4. Descrição dos parâmetros de saída e/ou valores retornados: Índice de fornecedor mais barato.
   5. Observações: */
int ConsultarFornecedores(Fornecedor fornecedores[], int quantosFornecedores, int indicePeca, Estoque pecas[])
{
    float menorPreco = fornecedores[0].preco;
    int i, indice = 0;
    for(i = 0; i < quantosFornecedores && !indice; i++)
    {
        if(fornecedores[i].preco < menorPreco && (strcmp(fornecedores[i].tipoPeca, pecas[indicePeca].tipoPeca) == 0))
        {
            menorPreco = fornecedores[i].preco;
            indice = i;
        }
    }
    return(indice);
}

/* 1. Objetivo da função: Encontrar o índice de uma peça no array de acordo com seu código.
   2. Resumo de seu funcionamento: Uma estrutura de repetição percorre o array de peças procurando o código correspondente.
   3. Descrição dos parâmetros de entrada: Uma peça do tipo Estoque, array de peças do tipo Estoque e inteiro de quantas peças cadastradas.
   4. Descrição dos parâmetros de saída e/ou valores retornados: Índice da peça desejada.
   5. Observações: */
int encontrarIndice(Estoque umaPeca, Estoque pecas[], int quantasPecas)
{
  int i, indice = -1;
  for(i = 0; i < quantasPecas; i++)
  {
    if(umaPeca.cod == pecas[i].cod)
    {
      indice = i;
    }
  }
  return(indice);
}

/* 1. Objetivo da função: Imprimir ao usuário uma lista de peças que estão com o estoque a baixo do valor mínimo permitido e repor as mesmas.
   2. Resumo de seu funcionamento: Uma estrutura de repetição percorre o array de peças imprimindo na tela as que estão como o estoque a baixo do mínimo,
   em seguida propõe uma reposição.
   3. Descrição dos parâmetros de entrada: Array de peças cadastradas do tipo Estoque, inteiro de quantidade de peças cadastradas, array de fornecedores cadastrados do tipo fornecedor, quantidade de
   fornecedores cadastrados do tipo interio, array de entregas recebidas do tipo EntregaRealizada e quantidade de entregas recebidas do tipo inteiro.
   4. Descrição dos parâmetros de saída e/ou valores retornados: .
   5. Observações: */
void ImprimirEstoqueBaixo(Estoque pecas[], int quantasPecas, Fornecedor fornecedores[], int quantosFornecedores, EntregaRealizada entregasRealizadas[], int *quantasEntregas)
{
    int i, quantas = 0, quais[MAXEST];
    printf("\n\tEstoque Abaixo do Permitido:\n\n");
    for(i = 0; i < quantasPecas; i++)
    {
        if(pecas[i].quantidade < pecas[i].qtdMinima)
        {
            printf("Peça: %s | Cód.: %i | Quantidade: %i | Quantidade Mínima: %i\n", pecas[i].descricao, pecas[i].cod, pecas[i].quantidade, pecas[i].qtdMinima);
            quais[quantas] = i;
            quantas++;
        }
    }
    puts("\nDeseja comprar as peças para reposção?(S/N)");
    fflush(stdin);
    char resp = toupper(getchar());
    if(resp == 'S')
    {
        for(i = 0; i < quantas; i++)
        {
            ComprarPeca(pecas, (pecas[quais[i]].qtdMinima - pecas[quais[i]].quantidade) + pecas[quais[i]].qtdMinima, fornecedores, quantosFornecedores, quais[i], entregasRealizadas, quantasEntregas);
        }
    }
    system("pause");
}

/* 1. Objetivo da função: Ordenar as peças em ordem alfabética de acordo com a descrição.
   2. Resumo de seu funcionamento: Duas estruturas de repetição em conjunto ordenam as palavras de acordo com a letra que elas se iniciam.
   3. Descrição dos parâmetros de entrada: Array de peças cadastradas do tipo Estoque e quantidade de peças cadastradas do tipo inteiro.
   4. Descrição dos parâmetros de saída e/ou valores retornados: Array de peças cadastradas e ordenadas alfabeticamente.
   5. Observações: */
void ordenarPecas(Estoque pecas[], int quantas) ///bubblesort
{
  int i, j;
  Estoque aux;
  for(i = 0; i < quantas; i++)
  {
    for(j = 0; j < quantas-1; j++)
    {
      if(strcmp(pecas[j].descricao, pecas[j+1].descricao) > 0)
      {
        aux = pecas[j];
        pecas[j] = pecas[j+1];
        pecas[j+1] = aux;
      }
    }
  }
}

/* 1. Objetivo da função: Imprimir na tela um relatório de peças cadastradas.
   2. Resumo de seu funcionamento: É executada uma função de ordenação em ordem alfabética, logo em seguida um estrutura de repetição imprime todos os índices do array de peças cadastradas.
   3. Descrição dos parâmetros de entrada: Array de peças cadastradas do tipo Estoque e quantidade de peças cadastradas do tipo inteiro.
   4. Descrição dos parâmetros de saída e/ou valores retornados: Sequência de peças cadastradas ordenadas em ordem alfabética.
   5. Observações: */
void ImprimirEstoque(Estoque pecas[], int quantas)
{
    ordenarPecas(pecas, quantas);
    int i;
    printf("\n\tPeças\n\n");
    for(i = 0; i < quantas; i++)
    {
        printf("%s | Tipo: %s | Cód.: %i | Quantidade: %i | Quantidade Mínima: %i\n", pecas[i].descricao, pecas[i].tipoPeca, pecas[i].cod, pecas[i].quantidade, pecas[i].qtdMinima);
    }
    system("pause");
}

///funções para manipulção de fornecedor
/* 1. Objetivo da função: Retornar os dados do tipo Fornecedor.
   2. Resumo de seu funcionamento: Pede ao usuário cada campo do tipo Fornecedor e armazena em uma variável do mesmo tipo, retornando a mesma.
   3. Descrição dos parâmetros de entrada: .
   4. Descrição dos parâmetros de saída e/ou valores retornados: Uma variável do tipo Fornecedor preenchida.
   5. Observações: */
Fornecedor digitaFornecedor()
{
  Fornecedor novo;
  fflush(stdin);
  printf("\nDigite o CNPJ do fornecedor: ");
  gets(novo.cnpj);
  fflush(stdin);
  printf("\nDigite a razão social do fornecedor: ");
  gets(novo.razaoSocial);
  fflush(stdin);
  printf("\nDigite o endereço do forecedor: ");
  gets(novo.endereco);
  fflush(stdin);
  printf("\nDigite o telefone do fornecedor: ");
  gets(novo.telefone);
  fflush(stdin);
  printf("\nDigite o tipo de peça do fornecedor:");
  gets(novo.tipoPeca);
  printf("\nDigite o quanto o preço por unidade que este fornecedor cobra: R$");
  scanf("%f", &novo.preco);
  return(novo);
}

/* 1. Objetivo da função: Verificar a existencia de um fornecedor.
   2. Resumo de seu funcionamento: Uma estrutura de repetição percorre o array de fornecedores comparando-o a um fornecedor.
   3. Descrição dos parâmetros de entrada: Um fornecedor do tipo Fornecedor, o array de fornecedores cadastrados do tipo Fornecedor e a quantidade de fornecedores cadastrados do tipo inteiro.
   4. Descrição dos parâmetros de saída e/ou valores retornados: Um valor booleando validando a existência do fornecedor no array de fornecedores.
   5. Observações: */
int existeFornecedor(Fornecedor umFornecedor, Fornecedor fornecedores[], int quantosFornecedores)
{
  int i, achou = 0;
  for(i = 0; i < quantosFornecedores && !achou; i++)
  {
    if(strcmp(umFornecedor.cnpj, fornecedores[i].cnpj) == 0)
    {
      achou = 1;
    }
  }
  return(achou);
}

/* 1. Objetivo da função: Fazer a inserção de um novo fornecedor no array de fornecedores.
   2. Resumo de seu funcionamento: Verifica se existe espaço no array, se ele já existe e por fim insere o mesmo no array.
   3. Descrição dos parâmetros de entrada: Array de fornecedores do tipo Fornecedor e quantidade de fornecedores cadastrados do tipo inteiro.
   4. Descrição dos parâmetros de saída e/ou valores retornados: Valor booleando validando a inserção do novo fornecedor.
   5. Observações: A digitação do novo fornecedor e a verificação da existencia são implementadas através de outras funções*/
int inserirNovoFornecedor(Fornecedor fornecedores[], int *quantosFornecedores)
{
  Fornecedor novoFornecedor;
  int oQueRetorna = 1; ///deu certo inserir novo fornecedor
  if(*quantosFornecedores == MAXFOR)
  {
    oQueRetorna = 0; /// NÃO deu certo inserir novo fornecedor
  }
  else
  {
    do
    {
      novoFornecedor = digitaFornecedor();
      if(existeFornecedor(novoFornecedor, fornecedores, *quantosFornecedores))
      {
        fflush(stdin);
        puts("\nERRO. O CNPJ do fornecedor já está cadastrado.");
        system("pause");
      }
    }
    while(existeFornecedor(novoFornecedor, fornecedores, *quantosFornecedores));
    fornecedores[(*quantosFornecedores)++] = novoFornecedor;
  }
  return(oQueRetorna);
}

/* 1. Objetivo da função: Ordenar os fornecedores em ordem alfabética de acordo com o tipo de peça.
   2. Resumo de seu funcionamento: Duas estruturas de repetição em conjunto ordenam as palavras de acordo com a letra que elas se iniciam.
   3. Descrição dos parâmetros de entrada: Array de fornecedores cadastrados do tipo Fornecedor e quantidade de fornecedores cadastrados do tipo inteiro.
   4. Descrição dos parâmetros de saída e/ou valores retornados: Array de fornecedores cadastrados e ordenados alfabeticamente.
   5. Observações: */
void ordenarFornecedores(Fornecedor fornecedores[], int quantos) ///bubblesort
{
  int i, j;
  Fornecedor aux;
  for(i = 0; i < quantos; i++)
  {
    for(j = 0; j < quantos-1; j++)
    {
      if(strcmp(fornecedores[j].tipoPeca, fornecedores[j+1].tipoPeca) > 0)
      {
        aux = fornecedores[j];
        fornecedores[j] = fornecedores[j+1];
        fornecedores[j+1] = aux;
      }
    }
  }
}

/* 1. Objetivo da função: Imprimir na tela um relatório de fornecedores cadastrados.
   2. Resumo de seu funcionamento: É executada uma função de ordenação em ordem alfabética, logo em seguida um estrutura de repetição imprime todos os índices do array de fornecedores cadastrados.
   3. Descrição dos parâmetros de entrada: Array de fornecedores cadastrados do tipo Fornecedor e quantidade de fornecedores cadastrados do tipo inteiro.
   4. Descrição dos parâmetros de saída e/ou valores retornados: Sequência de fornecedores cadastrados ordenados em ordem alfabética.
   5. Observações: */
void ImprimirFornecedores(Fornecedor fornecedores[], int quantos)
{
    ordenarFornecedores(fornecedores, quantos);
    int i;
    printf("\n\tFornecedores\n\n");
    for(i = 0; i < quantos; i++)
    {
        printf("Tipo de Peça: %s | Razão Social: %s | CNPJ: %s | Endereço: %s | Telefone: %s | Preço:R$%.2f\n", fornecedores[i].tipoPeca, fornecedores[i].razaoSocial, fornecedores[i].cnpj, fornecedores[i].endereco, fornecedores[i].telefone, fornecedores[i].preco);
    }
    system("pause");
}


///função para impressão de entregas
/* 1. Objetivo da função: Imprimir entregas de peças recebidas.
   2. Resumo de seu funcionamento: Uma estrutura de repetição percorre e imprime os dados de um array que armazena as entregas.
   3. Descrição dos parâmetros de entrada: Array de entregas realizadas do tipo EntregaRealizada e quantidade de entregas do tipo inteiro.
   4. Descrição dos parâmetros de saída e/ou valores retornados: Lista de entregas.
   5. Observações: */
void ImprimirEntregas(EntregaRealizada entregasRealizadas[], int quantasEntregas)
{
    int i;
    printf("\n\tEntregas\n\n");
    if(quantasEntregas == 0)
    {
        printf("Vazio.\n");
    }
    else
    {
        for(i = 0; i < quantasEntregas; i++)
        {
            printf("Entrega %i: CNPJ %s | cód. Peça: %i | Preço: %.2f | Quantidade: %i\n", i + 1, entregasRealizadas[i].cnpj, entregasRealizadas[i].codPeca, entregasRealizadas[i].preco, entregasRealizadas[i].quant);
        }
    }
    system("pause");
}

int main()
{
    setlocale(LC_ALL, "Portuguese");
    Estoque pecas[MAXEST] = {"Vela", "Elétrica", 1111, 100, 50,
                             "Junta de motor", "Mecânica", 2222, 100, 50,
                             "Lanterna frontal Celta", "Iluminação", 3333, 100, 50,
                             "Estofado Celta", "Forração", 4444, 30, 60,
                             "Parafuso de Eixo", "Fixação", 5555, 20, 50};
    Fornecedor fornecedores[MAXFOR] = {"89.587.365/4785-98", "Mecânica", "Peças LTDA", "Rua dos Bobos, n°0", "(19)98796-0593", 5.90,
                                       "90.435.642/4527-74", "Mecânica", "Jurema LTDA", "Rua XV, n°1", "(11)97648-9276", 8.25,
                                       "96.872.365/7895-75", "Elétrica", "Jair Bolsonaro LTDA", "Rua Um, n°1", "(11)98878-6878", 5.20,
                                       "89.785.487/1479-47", "Iluminação", "Pezão Luz LTDA", "Rua Dois, n°2", "(14)3466-7666", 7.75,
                                       "79.874.686/0453-67", "Elétrica", "Luz LTDA", "Rua 5, n°8", "(19)98876-5431", 5.50,
                                       "89.596.485/3540-00", "Iluminação", "Luz 2 LTDA", "Rua Cinco, n°9", "(11)94587-8735", 4.20,
                                       "98.976.857/4598-98", "Forração", "Estofados do Pinga LTDA", "Rua Cachaça, n°1000", "(19)97784-9876", 9.50,
                                       "76.573.568/8956-90", "Fixação", "Muller Peças", "Av. XV de Março, n°250", "(11)98765-7890", 8.20};
    EntregaRealizada entregasRealizadas[4000];
    int quantasPecas = 5, quantosFornecedores = 8, quantasEntregas = 0;
    char opcao;
    do
    {
        system("cls");
        ExibirMenu();
        opcao = digitaOpcao();
        system("cls");
        switch(opcao)
        {
        case '1':///Inserir nova peça
            {
                if(inserirNovaPeca(pecas, &quantasPecas))
                {
                  fflush(stdin);
                  puts("\nNova peça inserida com sucesso.");
                  system("pause");
                }
                else
                {
                  fflush(stdin);
                  puts("\nERRO ao inserir nova peça.");
                  system("pause");
                }
                break;
            }
        case '2':///Inserir novo fornecedor
            {
                if(inserirNovoFornecedor(fornecedores, &quantosFornecedores))
                {
                    fflush(stdin);
                    puts("\nNova peça inserida com sucesso.");
                    system("pause");
                }
                else
                {
                    fflush(stdin);
                    puts("\nERRO ao inserir nova peça.");
                    system("pause");
                }
                break;
            }
        case '3':///Retirar peça
            {
                if(RemoverPeca(pecas, quantasPecas, fornecedores, quantosFornecedores, entregasRealizadas, &quantasEntregas))
                {
                    fflush(stdin);
                    puts("\nPeças removidas com sucesso.");
                    system("pause");
                }
                else
                {
                    fflush(stdin);
                    puts("\nERRO ao remover peça, a mesma não possui quantidade suficiente no estoque.");
                    system("pause");
                }
                break;
            }
        case '4':///Relatório de estoque abaixo do permitido
            {
                ImprimirEstoqueBaixo(pecas, quantasPecas, fornecedores, quantosFornecedores, entregasRealizadas, &quantasEntregas);
                break;
            }
        case '5':///Relatório de peças
            {
                ImprimirEstoque(pecas, quantasPecas);
                break;
            }
        case '6':///Relatório de fornecedores
            {
                ImprimirFornecedores(fornecedores, quantosFornecedores);
                break;
            }
        case '7':///Relatório de entrega de peças
            {
                ImprimirEntregas(entregasRealizadas, quantasEntregas);
                break;
            }
        case '8':///Comprar estoque
            {
                printf("\nDigite quantos produtos deseja comprar: ");
                int quantos;
                fflush(stdin);
                scanf("%i", &quantos);
                if(ComprarPeca(pecas, quantos, fornecedores, quantosFornecedores, encontrarIndice(digitarCompra(), pecas, quantasPecas), entregasRealizadas, &quantasEntregas))
                {
                    puts("\nEstoque comprado com sucesso!");
                    system("pause");
                }
                else
                {
                    puts("\nErro ao comprar estoque!");
                    system("pause");
                }
                break;
            }
        case 'S':///Sair
            {
                printf("\nSaindo...");
                break;
            }
        default:
            puts("\nOpção inválida!");
        }
    }while(toupper(opcao) != 'S');
}
