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

///prot�tipos de fun��es
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

///fun��es
/* 1. Objetivo da fun��o: Exibir o menu principal.
   2. Resumo de seu funcionamento: Imprime na tela as op��es de menu.
   3. Descri��o dos par�metros de entrada: .
   4. Descri��o dos par�metros de sa�da e/ou valores retornados: Texto de t�picos de menu.
   5. Observa��es: */
void ExibirMenu()
{
    printf("\n\tMenu de Opcoes\n\n1. Inserir nova pe�a\n2. Inserir novo fornecedor\n3. Retirar pe�a\n4. Relat�rio de estoque abaixo do permitido\n5. Relat�rio de pe�a\n6. Relat�rio de fornecedores\n7. Relat�rio de entrega de pe�as\n8. Comprar estoque\nS. Sair");
}

/* 1. Objetivo da fun��o: Exibir mensagem de escolha de op��o.
   2. Resumo de seu funcionamento: Coleta uma op��o de menu.
   3. Descri��o dos par�metros de entrada: .
   4. Descri��o dos par�metros de sa�da e/ou valores retornados: Vari�vel tipo 'char'.
   5. Observa��es: */
char digitaOpcao()
{
  char opcao;
  fflush(stdin);
  printf("\nDigite sua opcao: ");
  opcao = toupper(getchar());
  return(opcao);
}

///fun��es para manipula��o de pe�as
/* 1. Objetivo da fun��o: Digitar as caracter�sticas de uma pe�a.
   2. Resumo de seu funcionamento: Pega as informa��es do tipo Estoque.
   3. Descri��o dos par�metros de entrada: .
   4. Descri��o dos par�metros de sa�da e/ou valores retornados: Pe�a preenchida.
   5. Observa��es: texto. */
Estoque digitaPeca()
{
  Estoque nova;
  fflush(stdin);
  printf("\nDigite a descri��o da pe�a: ");
  gets(nova.descricao);
  fflush(stdin);
  printf("\nDigite o tipo da pe�a: ");
  gets(nova.tipoPeca);
  fflush(stdin);
  printf("\nDigite o c�digo da pe�a: ");
  scanf("%i", &nova.cod);
  fflush(stdin);
  printf("\nDigite a quantidade m�nima que a pe�a ter� em estoque: ");
  scanf("%i", &nova.qtdMinima);
  fflush(stdin);
  do{
  printf("\nDigite a quantidade que deseja adicionar ao estoque: ");
  scanf("%i", &nova.quantidade);
    if(nova.quantidade < nova.qtdMinima * 2)
    {
        fflush(stdin);
        puts("\nO estoque deve ter no m�nimo duas vezes o estoque m�nimo!\n");
        system("pause");
    }
  }while(nova.quantidade < nova.qtdMinima * 2);
  return(nova);
}

/* 1. Objetivo da fun��o: Analizar a exist�ncia de uma pe�a no array de pe�as cadastradas.
   2. Resumo de seu funcionamento: Uma estrutura de repeti��o caminha pelo array procurando igualidade entre as informa��es.
   3. Descri��o dos par�metros de entrada: Vari�vel do tipo Estoque, array do tipo Estoque, um inteiro.
   4. Descri��o dos par�metros de sa�da e/ou valores retornados: Valor booleando indicando a exist�ncia da pe�a no array.
   5. Observa��es: */
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

/* 1. Objetivo da fun��o: Fazer a inser��o de uma nova pe�a no sistema.
   2. Resumo de seu funcionamento: � analisado se existe espa�o para uma nova pe�a e se ja existe uma pe�a igual, em seguida se esta passar por estes dois testes ela � inserida no array de pe�as cadastradas.
   3. Descri��o dos par�metros de entrada: Array do tipo Estoque e inteiro indicando a quantidade de pe�as cadastradas.
   4. Descri��o dos par�metros de sa�da e/ou valores retornados: Valor booleando validando a inser��o de uma nova pe�a.
   5. Observa��es: */
int inserirNovaPeca(Estoque pecas[], int *quantasPecas)
{
  Estoque novaPeca;
  int oQueRetorna = 1; ///deu certo inserir nova pe�a
  if(*quantasPecas == MAXEST)
  {
    oQueRetorna = 0; /// N�O deu certo inserir nova pe�a
  }
  else
  {
    do
    {
      novaPeca = digitaPeca();
      if(existePeca(novaPeca, pecas, *quantasPecas))
      {
        fflush(stdin);
        puts("\nERRO.\nO c�digo da pe�a j� est� cadastrado.\nPor favor digite um novo c�digo.");
        system("pause");
      }
    }
    while(existePeca(novaPeca, pecas, *quantasPecas));
    pecas[(*quantasPecas)++] = novaPeca;
  }
  return(oQueRetorna);
}

/* 1. Objetivo da fun��o: Recolher informa��es do tipo Estoque.
   2. Resumo de seu funcionamento: Coleta informa��es do tipo Estoque.
   3. Descri��o dos par�metros de entrada: .
   4. Descri��o dos par�metros de sa�da e/ou valores retornados: Vari�vel do tipo pe�a com dois campos preenchidos.
   5. Observa��es: */
Estoque digitaPecaRemover()
{
    Estoque umaPeca;
    printf("\nDigite o c�digo da pe�a: ");
    scanf("%i", &umaPeca.cod);
    fflush(stdin);
    printf("\nDigite a quantidade a ser removida: ");
    scanf("%i", &umaPeca.quantidade);
    return(umaPeca);
}

/* 1. Objetivo da fun��o: Remover pe�as do estoque.
   2. Resumo de seu funcionamento: Encontra uma pe�a que o usu�rio fornece no arrayu de pe�as cadastradas, em seguida verifica se tem pe�as o suficiente no sistema para a remo��o
   e em seguida remove as pe�as; caso a quantidade de pe�as passe a ser menor do que o permitido � sugerida uma reposi��o.
   3. Descri��o dos par�metros de entrada: Array de pe�as cadastradas do tipo Estoque, inteiro de quantas pe�as cadastradas, arrai=y de fornecedores do tipo Fornecedor, inteiro de
   quantos fornecedores cadastrados, array de entregas realizadas do tipo EntregaRealizada e inteiro de quantas entregas realizadas.
   4. Descri��o dos par�metros de sa�da e/ou valores retornados: Valor booleando validando a remo��o de pe�as.
   5. Observa��es: */
int RemoverPeca(Estoque pecas[], int quantasPecas, Fornecedor fornecedores[], int quantosFornecedores, EntregaRealizada entregasRealizadas[], int *quantasEntregas)
{
    Estoque umaPeca;
    int indice;
    int oQueRetorna = 1;///Deu certo remover pe�a
    do
    {
      umaPeca = digitaPecaRemover();
      if(encontrarIndice(umaPeca, pecas, quantasPecas) == -1)
      {
        fflush(stdin);
        puts("\nERRO. O c�digo da pe�a n�o est� cadastrado.");
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
            puts("\nA pe�a est� com o estoque a baixo do n�vel m�nimo!\nSer� necess�ria uma nova compra para que o estoque seja o dobro da quantidade m�nima.\n");
            system("pause");
            int quantos = (pecas[indice].qtdMinima - pecas[indice].quantidade) + pecas[indice].qtdMinima;
            if(ComprarPeca(pecas, quantos, fornecedores, quantosFornecedores, indice, entregasRealizadas, quantasEntregas))
            {
                fflush(stdin);
                puts("\nPe�as compradas com sucesso!");
                system("pause");
            }
            else
            {
                fflush(stdin);
                puts("\nN�o foi poss�vel comprar as pe�as.");
                system("pause");
            }
        }
        oQueRetorna = 1;
    }
    return(oQueRetorna);
}

/* 1. Objetivo da fun��o: Realizar a compra de uma determinada quantidade de uma determinada pe�a, registrando a entrega da mesma.
   2. Resumo de seu funcionamento: Encontra a pe�a indicada pelo usu�rio e em seguida pesquisa pre�os em fornecedores por fim realizando a compra.
   3. Descri��o dos par�metros de entrada: Array de pe�as do tipo Estoque, inteiro de quantas pe�as comprar, array de fornecedores do tipo Fornecedor, inteiro de quantos fornecedores cadastrados, inteiro de �ndice da pe�a para realizar a compra,
   array de entregas realizadas do tipo EntregaRealizada e inteiro de qauntas entregas realizadas.
   4. Descri��o dos par�metros de sa�da e/ou valores retornados: Booleando validando a compra da pe�a.
   5. Observa��es: */
int ComprarPeca(Estoque pecas[], int quantos, Fornecedor fornecedores[], int quantosFornecedores, int indicePeca, EntregaRealizada entregasRealizadas[], int *quantasEntregas)
{
    int oQueRetorna = 0, indiceFornecedor;
    char opcao;
    if(indicePeca < 0)
    {
        puts("\nO �ndice n�o existe!");
        system("pause");
    }
    else
    {
        if(ConsultarFornecedores(fornecedores, quantosFornecedores, indicePeca, pecas) >= 0)
        {
            indiceFornecedor = ConsultarFornecedores(fornecedores, quantosFornecedores, indicePeca, pecas);
            printf("\n%s. O fornecedor com o menor pre�o para este tipo de pe�a � o %s, o total da compra ser� R$%.2f\nDigite 'S' para comprar ou 'N' para cancelar a compra: ", pecas[indicePeca].descricao, fornecedores[indiceFornecedor].razaoSocial, fornecedores[indiceFornecedor].preco * quantos);
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

/* 1. Objetivo da fun��o: Digitar as caracter�sticas de uma pe�a para compra.
   2. Resumo de seu funcionamento: Pega as informa��es do tipo Estoque.
   3. Descri��o dos par�metros de entrada: .
   4. Descri��o dos par�metros de sa�da e/ou valores retornados: Pe�a preenchida.
   5. Observa��es: texto. */
Estoque digitarCompra()
{
    Estoque umaPeca;
    printf("\nDigite o c�digo da pe�a: ");
    scanf("%i", &umaPeca.cod);
    return(umaPeca);
}

/* 1. Objetivo da fun��o: Consultar o array de fornecedores procurando o mais barato.
   2. Resumo de seu funcionamento: Uma estrutura de repeti��o percorrei o array do tipo Fornecedor procurando o que tem o pre�o mais barato.
   3. Descri��o dos par�metros de entrada: Array de fornecedores do tipo Fornecedor, inteiro de quantos fornecedores cadastrados, inteiro de indice da pe�a e array de pe�as do tipo Estoque.
   4. Descri��o dos par�metros de sa�da e/ou valores retornados: �ndice de fornecedor mais barato.
   5. Observa��es: */
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

/* 1. Objetivo da fun��o: Encontrar o �ndice de uma pe�a no array de acordo com seu c�digo.
   2. Resumo de seu funcionamento: Uma estrutura de repeti��o percorre o array de pe�as procurando o c�digo correspondente.
   3. Descri��o dos par�metros de entrada: Uma pe�a do tipo Estoque, array de pe�as do tipo Estoque e inteiro de quantas pe�as cadastradas.
   4. Descri��o dos par�metros de sa�da e/ou valores retornados: �ndice da pe�a desejada.
   5. Observa��es: */
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

/* 1. Objetivo da fun��o: Imprimir ao usu�rio uma lista de pe�as que est�o com o estoque a baixo do valor m�nimo permitido e repor as mesmas.
   2. Resumo de seu funcionamento: Uma estrutura de repeti��o percorre o array de pe�as imprimindo na tela as que est�o como o estoque a baixo do m�nimo,
   em seguida prop�e uma reposi��o.
   3. Descri��o dos par�metros de entrada: Array de pe�as cadastradas do tipo Estoque, inteiro de quantidade de pe�as cadastradas, array de fornecedores cadastrados do tipo fornecedor, quantidade de
   fornecedores cadastrados do tipo interio, array de entregas recebidas do tipo EntregaRealizada e quantidade de entregas recebidas do tipo inteiro.
   4. Descri��o dos par�metros de sa�da e/ou valores retornados: .
   5. Observa��es: */
void ImprimirEstoqueBaixo(Estoque pecas[], int quantasPecas, Fornecedor fornecedores[], int quantosFornecedores, EntregaRealizada entregasRealizadas[], int *quantasEntregas)
{
    int i, quantas = 0, quais[MAXEST];
    printf("\n\tEstoque Abaixo do Permitido:\n\n");
    for(i = 0; i < quantasPecas; i++)
    {
        if(pecas[i].quantidade < pecas[i].qtdMinima)
        {
            printf("Pe�a: %s | C�d.: %i | Quantidade: %i | Quantidade M�nima: %i\n", pecas[i].descricao, pecas[i].cod, pecas[i].quantidade, pecas[i].qtdMinima);
            quais[quantas] = i;
            quantas++;
        }
    }
    puts("\nDeseja comprar as pe�as para repos��o?(S/N)");
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

/* 1. Objetivo da fun��o: Ordenar as pe�as em ordem alfab�tica de acordo com a descri��o.
   2. Resumo de seu funcionamento: Duas estruturas de repeti��o em conjunto ordenam as palavras de acordo com a letra que elas se iniciam.
   3. Descri��o dos par�metros de entrada: Array de pe�as cadastradas do tipo Estoque e quantidade de pe�as cadastradas do tipo inteiro.
   4. Descri��o dos par�metros de sa�da e/ou valores retornados: Array de pe�as cadastradas e ordenadas alfabeticamente.
   5. Observa��es: */
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

/* 1. Objetivo da fun��o: Imprimir na tela um relat�rio de pe�as cadastradas.
   2. Resumo de seu funcionamento: � executada uma fun��o de ordena��o em ordem alfab�tica, logo em seguida um estrutura de repeti��o imprime todos os �ndices do array de pe�as cadastradas.
   3. Descri��o dos par�metros de entrada: Array de pe�as cadastradas do tipo Estoque e quantidade de pe�as cadastradas do tipo inteiro.
   4. Descri��o dos par�metros de sa�da e/ou valores retornados: Sequ�ncia de pe�as cadastradas ordenadas em ordem alfab�tica.
   5. Observa��es: */
void ImprimirEstoque(Estoque pecas[], int quantas)
{
    ordenarPecas(pecas, quantas);
    int i;
    printf("\n\tPe�as\n\n");
    for(i = 0; i < quantas; i++)
    {
        printf("%s | Tipo: %s | C�d.: %i | Quantidade: %i | Quantidade M�nima: %i\n", pecas[i].descricao, pecas[i].tipoPeca, pecas[i].cod, pecas[i].quantidade, pecas[i].qtdMinima);
    }
    system("pause");
}

///fun��es para manipul��o de fornecedor
/* 1. Objetivo da fun��o: Retornar os dados do tipo Fornecedor.
   2. Resumo de seu funcionamento: Pede ao usu�rio cada campo do tipo Fornecedor e armazena em uma vari�vel do mesmo tipo, retornando a mesma.
   3. Descri��o dos par�metros de entrada: .
   4. Descri��o dos par�metros de sa�da e/ou valores retornados: Uma vari�vel do tipo Fornecedor preenchida.
   5. Observa��es: */
Fornecedor digitaFornecedor()
{
  Fornecedor novo;
  fflush(stdin);
  printf("\nDigite o CNPJ do fornecedor: ");
  gets(novo.cnpj);
  fflush(stdin);
  printf("\nDigite a raz�o social do fornecedor: ");
  gets(novo.razaoSocial);
  fflush(stdin);
  printf("\nDigite o endere�o do forecedor: ");
  gets(novo.endereco);
  fflush(stdin);
  printf("\nDigite o telefone do fornecedor: ");
  gets(novo.telefone);
  fflush(stdin);
  printf("\nDigite o tipo de pe�a do fornecedor:");
  gets(novo.tipoPeca);
  printf("\nDigite o quanto o pre�o por unidade que este fornecedor cobra: R$");
  scanf("%f", &novo.preco);
  return(novo);
}

/* 1. Objetivo da fun��o: Verificar a existencia de um fornecedor.
   2. Resumo de seu funcionamento: Uma estrutura de repeti��o percorre o array de fornecedores comparando-o a um fornecedor.
   3. Descri��o dos par�metros de entrada: Um fornecedor do tipo Fornecedor, o array de fornecedores cadastrados do tipo Fornecedor e a quantidade de fornecedores cadastrados do tipo inteiro.
   4. Descri��o dos par�metros de sa�da e/ou valores retornados: Um valor booleando validando a exist�ncia do fornecedor no array de fornecedores.
   5. Observa��es: */
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

/* 1. Objetivo da fun��o: Fazer a inser��o de um novo fornecedor no array de fornecedores.
   2. Resumo de seu funcionamento: Verifica se existe espa�o no array, se ele j� existe e por fim insere o mesmo no array.
   3. Descri��o dos par�metros de entrada: Array de fornecedores do tipo Fornecedor e quantidade de fornecedores cadastrados do tipo inteiro.
   4. Descri��o dos par�metros de sa�da e/ou valores retornados: Valor booleando validando a inser��o do novo fornecedor.
   5. Observa��es: A digita��o do novo fornecedor e a verifica��o da existencia s�o implementadas atrav�s de outras fun��es*/
int inserirNovoFornecedor(Fornecedor fornecedores[], int *quantosFornecedores)
{
  Fornecedor novoFornecedor;
  int oQueRetorna = 1; ///deu certo inserir novo fornecedor
  if(*quantosFornecedores == MAXFOR)
  {
    oQueRetorna = 0; /// N�O deu certo inserir novo fornecedor
  }
  else
  {
    do
    {
      novoFornecedor = digitaFornecedor();
      if(existeFornecedor(novoFornecedor, fornecedores, *quantosFornecedores))
      {
        fflush(stdin);
        puts("\nERRO. O CNPJ do fornecedor j� est� cadastrado.");
        system("pause");
      }
    }
    while(existeFornecedor(novoFornecedor, fornecedores, *quantosFornecedores));
    fornecedores[(*quantosFornecedores)++] = novoFornecedor;
  }
  return(oQueRetorna);
}

/* 1. Objetivo da fun��o: Ordenar os fornecedores em ordem alfab�tica de acordo com o tipo de pe�a.
   2. Resumo de seu funcionamento: Duas estruturas de repeti��o em conjunto ordenam as palavras de acordo com a letra que elas se iniciam.
   3. Descri��o dos par�metros de entrada: Array de fornecedores cadastrados do tipo Fornecedor e quantidade de fornecedores cadastrados do tipo inteiro.
   4. Descri��o dos par�metros de sa�da e/ou valores retornados: Array de fornecedores cadastrados e ordenados alfabeticamente.
   5. Observa��es: */
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

/* 1. Objetivo da fun��o: Imprimir na tela um relat�rio de fornecedores cadastrados.
   2. Resumo de seu funcionamento: � executada uma fun��o de ordena��o em ordem alfab�tica, logo em seguida um estrutura de repeti��o imprime todos os �ndices do array de fornecedores cadastrados.
   3. Descri��o dos par�metros de entrada: Array de fornecedores cadastrados do tipo Fornecedor e quantidade de fornecedores cadastrados do tipo inteiro.
   4. Descri��o dos par�metros de sa�da e/ou valores retornados: Sequ�ncia de fornecedores cadastrados ordenados em ordem alfab�tica.
   5. Observa��es: */
void ImprimirFornecedores(Fornecedor fornecedores[], int quantos)
{
    ordenarFornecedores(fornecedores, quantos);
    int i;
    printf("\n\tFornecedores\n\n");
    for(i = 0; i < quantos; i++)
    {
        printf("Tipo de Pe�a: %s | Raz�o Social: %s | CNPJ: %s | Endere�o: %s | Telefone: %s | Pre�o:R$%.2f\n", fornecedores[i].tipoPeca, fornecedores[i].razaoSocial, fornecedores[i].cnpj, fornecedores[i].endereco, fornecedores[i].telefone, fornecedores[i].preco);
    }
    system("pause");
}


///fun��o para impress�o de entregas
/* 1. Objetivo da fun��o: Imprimir entregas de pe�as recebidas.
   2. Resumo de seu funcionamento: Uma estrutura de repeti��o percorre e imprime os dados de um array que armazena as entregas.
   3. Descri��o dos par�metros de entrada: Array de entregas realizadas do tipo EntregaRealizada e quantidade de entregas do tipo inteiro.
   4. Descri��o dos par�metros de sa�da e/ou valores retornados: Lista de entregas.
   5. Observa��es: */
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
            printf("Entrega %i: CNPJ %s | c�d. Pe�a: %i | Pre�o: %.2f | Quantidade: %i\n", i + 1, entregasRealizadas[i].cnpj, entregasRealizadas[i].codPeca, entregasRealizadas[i].preco, entregasRealizadas[i].quant);
        }
    }
    system("pause");
}

int main()
{
    setlocale(LC_ALL, "Portuguese");
    Estoque pecas[MAXEST] = {"Vela", "El�trica", 1111, 100, 50,
                             "Junta de motor", "Mec�nica", 2222, 100, 50,
                             "Lanterna frontal Celta", "Ilumina��o", 3333, 100, 50,
                             "Estofado Celta", "Forra��o", 4444, 30, 60,
                             "Parafuso de Eixo", "Fixa��o", 5555, 20, 50};
    Fornecedor fornecedores[MAXFOR] = {"89.587.365/4785-98", "Mec�nica", "Pe�as LTDA", "Rua dos Bobos, n�0", "(19)98796-0593", 5.90,
                                       "90.435.642/4527-74", "Mec�nica", "Jurema LTDA", "Rua XV, n�1", "(11)97648-9276", 8.25,
                                       "96.872.365/7895-75", "El�trica", "Jair Bolsonaro LTDA", "Rua Um, n�1", "(11)98878-6878", 5.20,
                                       "89.785.487/1479-47", "Ilumina��o", "Pez�o Luz LTDA", "Rua Dois, n�2", "(14)3466-7666", 7.75,
                                       "79.874.686/0453-67", "El�trica", "Luz LTDA", "Rua 5, n�8", "(19)98876-5431", 5.50,
                                       "89.596.485/3540-00", "Ilumina��o", "Luz 2 LTDA", "Rua Cinco, n�9", "(11)94587-8735", 4.20,
                                       "98.976.857/4598-98", "Forra��o", "Estofados do Pinga LTDA", "Rua Cacha�a, n�1000", "(19)97784-9876", 9.50,
                                       "76.573.568/8956-90", "Fixa��o", "Muller Pe�as", "Av. XV de Mar�o, n�250", "(11)98765-7890", 8.20};
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
        case '1':///Inserir nova pe�a
            {
                if(inserirNovaPeca(pecas, &quantasPecas))
                {
                  fflush(stdin);
                  puts("\nNova pe�a inserida com sucesso.");
                  system("pause");
                }
                else
                {
                  fflush(stdin);
                  puts("\nERRO ao inserir nova pe�a.");
                  system("pause");
                }
                break;
            }
        case '2':///Inserir novo fornecedor
            {
                if(inserirNovoFornecedor(fornecedores, &quantosFornecedores))
                {
                    fflush(stdin);
                    puts("\nNova pe�a inserida com sucesso.");
                    system("pause");
                }
                else
                {
                    fflush(stdin);
                    puts("\nERRO ao inserir nova pe�a.");
                    system("pause");
                }
                break;
            }
        case '3':///Retirar pe�a
            {
                if(RemoverPeca(pecas, quantasPecas, fornecedores, quantosFornecedores, entregasRealizadas, &quantasEntregas))
                {
                    fflush(stdin);
                    puts("\nPe�as removidas com sucesso.");
                    system("pause");
                }
                else
                {
                    fflush(stdin);
                    puts("\nERRO ao remover pe�a, a mesma n�o possui quantidade suficiente no estoque.");
                    system("pause");
                }
                break;
            }
        case '4':///Relat�rio de estoque abaixo do permitido
            {
                ImprimirEstoqueBaixo(pecas, quantasPecas, fornecedores, quantosFornecedores, entregasRealizadas, &quantasEntregas);
                break;
            }
        case '5':///Relat�rio de pe�as
            {
                ImprimirEstoque(pecas, quantasPecas);
                break;
            }
        case '6':///Relat�rio de fornecedores
            {
                ImprimirFornecedores(fornecedores, quantosFornecedores);
                break;
            }
        case '7':///Relat�rio de entrega de pe�as
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
            puts("\nOp��o inv�lida!");
        }
    }while(toupper(opcao) != 'S');
}
