#include "funcao.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// trocar o nome das variaveis pelo snake case

int main() {
  int fila, opcao1, opcao2, qtdcarros, qtd_atendidos, cont, i, j, k, l;
  float valor, preco, comb, combrestante;
  struct Tcarro *TAMfila, *carroatendido;
  time_t valor_data;
  struct tm *p;
  FILE *pont_arquivo;
  i = 0;
  k = 1;
  l = 0;
  j = 0;
  cont = 0;
  fila = 0;
  preco = 0;
  comb = 0;
  qtdcarros = 0;
  qtd_atendidos = 0;
  combrestante = 200;

  printf(blue "Autor: Carlos Alexandre Oliveira Alves\n");
  printf(white "\nBem-vindo.\nEste programa tem como objetivo: "
               "melhorar o gerencioamento\nde informações de um posto.\n\n");

  printf("O usuário deverá ser capaz de:\n" green
         "- Determinar e poder mudar o tamanho da fila a qualquer\n"
         "momento que desejar.\n"
         "- Visualizar os carros que estão e já estiveram\n"
         "na fila de espera.\n"
         "- Imprimir o relatório com as principais informações.\n\n");

  valor_data = time(NULL);
  struct tm data = *localtime(&valor_data); // valor bruto em long long da data
  time(&valor_data);

  if (data.tm_hour < 3) { // exibir a data em dia, mês e ano.
    printf(white "Data: %d/%d/%d\n", data.tm_mday - 1, data.tm_mon + 1,
           data.tm_year + 1900);
  } else {
    printf(white "Data: %d/%d/%d\n", data.tm_mday, data.tm_mon + 1,
           data.tm_year + 1900);
  }
  printf("\n");

  printf(white "Informe o tamanho da fila.\n");
  scanf("%d", &fila);
  teste(&fila);
  cont = fila - 1;

  // Realiza uma subrotina para obsevar se o valor informado está dentro do
  // esperado.
  TAMfila = (struct Tcarro *)calloc(cont, sizeof(struct Tcarro));
  if (TAMfila == NULL) {
    printf("Erro.");
    exit(0); // inicializaçao do ponteiro que armazenará os dados da fila
  }

  carroatendido = (struct Tcarro *)calloc(0, sizeof(struct Tcarro));
  if (carroatendido == NULL) {
    printf("Erro!"); // inicialização do ponteiro para armazanar os carros
                     // atendidods
    exit(0);
  }

  cont = cont + 1;
  TAMfila =
      (struct Tcarro *)realloc(TAMfila, (cont + 1) * sizeof(struct Tcarro));
  // reallocando ponteiro para ocorrer uma atualização;

  pont_arquivo = NULL;
  pont_arquivo = fopen("arquivo txt", "w");
  if (pont_arquivo == NULL) {
    printf("Erro!");
    exit(0);
  }
  

  printf(white "\nInfome o preço do combustível\n");
  scanf("%f", &preco);
  teste2(&preco);
  // Realiza uma subrotina para obsevar se o valor informado está dentro do
  // esperado.

  system("clear");
  menu(&opcao1);
  system("clear");
  while (opcao1 != 5) {
    comb = 0;
    if ((opcao1 < 0) || (opcao1 == 0)) {
      system("clear");
      printf(red "Escolha números inteiros positivos!\n\n" white);
      opcao1 = 7;
    }

    if ((opcao1 > 6) && (opcao1 != 7)) {
      system("clear");
      printf(red "Escolha uma opção disponível!\n\n" white);
      opcao1 = 7;
    }

    if (opcao1 == 7) {
      minimenu(&combrestante, &qtdcarros, &fila);
      // Constrói o "mini-menu" no lado superior direito.
      menu(&opcao1);
      // Informa o menu no lado superior direito.
      system("clear");
    }

    switch (opcao1) {
    case 1: // Adiciona um carro na fila, fazendo o teste se o valor informado é
            // possível.
      if (combrestante == 0) {
        system("clear");
        printf(
            red
            "Bomba sem combustível! Não pode adicionar mais carros.\n" white);
        opcao1 = 7;
        break;

      } else {
        if (fila == 0) {
          system("clear");
          printf(red "Não pode adicionar mais carros!\n" white);
          printf("Escolha outra opção.\n\n");
          opcao1 = 7;
          break;
        } else {
          system("clear");
          printf("Informe o ano do carro: ");
          scanf("%d", &TAMfila[i].ano);

          getchar();
          printf("Informe a placa do carro: ");
          fgets(TAMfila[i].placa, 30, stdin);
          TAMfila[i].placa[strcspn(TAMfila[i].placa, "\n")] = 0;

          printf("Informe a cor do carro: ");
          fgets(TAMfila[i].cor, 30, stdin);
          TAMfila[i].cor[strcspn(TAMfila[i].cor, "\n")] = 0;

          printf("Informe a marca do carro: ");
          fgets(TAMfila[i].marca, 30, stdin);
          TAMfila[i].marca[strcspn(TAMfila[i].marca, "\n")] = 0;

          printf("Informe a modelo do carro: ");
          fgets(TAMfila[i].modelo, 30, stdin);
          TAMfila[i].modelo[strcspn(TAMfila[i].modelo, "\n")] = 0;

          system("clear");
          printf(green "+1 carro adicinado à fila\n\n" white);

          i = i + 1;
          fila = fila - 1;
          qtdcarros = qtdcarros + 1;
          opcao1 = 7;
          break;
        }

      case 2:
        if (qtdcarros == 0) {
          system("clear");
          printf(red "Sem carros na fila para abastecer!\n" white);
          opcao1 = 7;
          break;
        }
        if (combrestante == 0) {
          printf(red "Bomba sem combustível! Fila encerrada.\n" white);
          opcao1 = 7;
        } else {
          while ((comb <= 0) || (comb > combrestante)) {
            system("clear");
            printf(red "*Informe um número positivo;\n");
            printf("\n*Diferente de zero;\n");
            printf("\n*Menor que o combustível restante!\n\n" white);
            printf("Quantidade de combustível restante: %.2f\n", combrestante);
            printf("Quanto deseja abastecer? {em litros}\n");
            scanf("%f", &comb);
          }

          combrestante = combrestante - comb;
          system("clear");

          if (combrestante == 0) {
            printf(green "Carro abastecido com %.2f L de combustível.\n", comb);
            printf(red "AVISO: Bomba sem combustível! Fila encerrada.\n" white);

            l = l + 1; // variável de controle de carros atendidos
            carroatendido = realloc(carroatendido, 1 * sizeof(struct Tcarro));
            carroatendido[qtd_atendidos] = TAMfila[0];
            qtdcarros = 0;
            fila = 0;
            qtd_atendidos = qtd_atendidos + 1;
            opcao1 = 7;
            break;
          }

          else {
            printf(green "Carro abastecido com %.2f L de combustível\n", comb);
            printf(white);

            l = l + 1; // variável de controle de carros atendidos
            carroatendido = realloc(carroatendido, l * sizeof(struct Tcarro)); // preenchimento da fila de
            // "carros atendidos"
            carroatendido[qtd_atendidos] = TAMfila[0];

            while (j <= i) { // While para andar a fila de carros.
              TAMfila[j] = TAMfila[j + 1];
              j = j + 1;
            }

            i = i - 1;
            j = 0;
            fila = fila + 1;
            qtdcarros = qtdcarros - 1;
            qtd_atendidos = qtd_atendidos + 1;
            opcao1 = 7;
            break;
          }
        }
      case 3: // exibir carros que estão na fila

        system("clear");

        if (qtdcarros == 0) {
          printf(red "Sem carros na fila!\n\n" white);
          opcao1 = 7;
          break;
        } else {
          printf("Quantidade de carros na fila: %d\n", qtdcarros);

          while (j < i) {
            printf("\n[%dº] Carro", k);
            printf("\nPlaca: %s", TAMfila[j].placa);
            printf("\nModelo: %s", TAMfila[j].modelo);
            printf("\nMarca: %s", TAMfila[j].marca);
            printf("\nCor: %s", TAMfila[j].cor);
            printf("\nAno: %d", TAMfila[j].ano);
            printf("\n\n");
            j = j + 1;
            k = k + 1;
          }
          k = 1;
          j = 0;

          opcao1 = 7;
          break;
        }

      case 4:
        system("clear");
        relatorio(&opcao2); // subrotina para a exibição do relatório.
        system("clear");

        while (opcao2 != 6) {

          if ((opcao2 < 0) || (opcao2 == 0) || (opcao2 > 7)) {
            system("clear");
            printf(red "Escolha uma opção disponível!" white);
            relatorio(&opcao2); // subrotina para a exibição do relatório.
            system("clear");
          }

          if (opcao2 == 7) {
            relatorio(&opcao2); // subrotina para a exibição do relatório.
            system("clear");
          }

          switch (opcao2) {
          case 1:
            system("clear");
            printf("\nLitros vendidos: %.2f L\n", 200 - combrestante);
            opcao2 = 7;
            break;
          case 2:
            system("clear");
            printf("\nValor total arrecadado com as vendas: R$ %.2f\n",
                   (200 - combrestante) * preco);
            opcao2 = 7;
            break;
          case 3:
            system("clear");
            printf("\nQuantidade de carros atendidos: %d", qtd_atendidos);
            j = 0;
            printf("\n");
            while (j < l) { // exibição dos carros atendidos
              printf("\n[%dº] Carro do dia.", k);
              printf("\nPlaca: %s", carroatendido[j].placa);
              printf("\nModelo: %s", carroatendido[j].modelo);
              printf("\nMarca: %s", carroatendido[j].marca);
              printf("\nCor: %s", carroatendido[j].cor);
              printf("\nAno: %d", carroatendido[j].ano);
              printf("\n\n");
              j = j + 1;
              k = k + 1;
            }

            j = 0;
            k = 1;
            opcao2 = 7;
            break;
          case 4:
            system("clear");
            printf("\nQuantidade de combustível restante no tanque: %.2f\n",
                   combrestante);
            opcao2 = 7;
            break;
          case 5:
            pont_arquivo = NULL;
            pont_arquivo = fopen("arquivo txt", "w");
            if (pont_arquivo == NULL) {
              printf("Erro na impressão!");
              exit(0);
            }  // inicialização do ponteiro para armazenar o arquivo txt
            system("clear");
            printf("Arquivo impresso.");
            fprintf(pont_arquivo, "-------Arquivo de impressão-------");
            fprintf(pont_arquivo, "\nLitros vendidos: %.2f L\n", 200 - combrestante);
            fprintf(pont_arquivo, "\nValor total arrecadado com as vendas: R$ %.2f\n", (200 - combrestante) * preco);
            fprintf(pont_arquivo, "\nQuantidade de carros atendidos: %d\n", qtd_atendidos);
            fprintf(pont_arquivo, "\nQuantidade de combustível restante no tanque: %.2f\n", combrestante);
            
            fclose(pont_arquivo);
            printf(cyan "\n\n---Aperte enter para continuar---" white);

            getchar();
            getchar();
            system("clear");
            opcao2 = 7;
            break;
          case 6:
            system("clear");
            opcao2 = 6;
            system("clear");
            break;
          }
        }
        system("clear");
        printf(blue "\n--------------Menu incial--------------\n" white);
        opcao1 = 7;
        break;
      case 5:
        printf(red "\nPrograma encerrado." white);
        opcao1 = 5;
        break;
      case 6:
        if (combrestante == 0) {
          printf(red "Bomba sem combustível! Não poderá adicionar mais "
                     "posições!\n\n" white);
          opcao1 = 7;
          break;
        } else {
          cont++;
          printf(green "Adicionado mais uma posição na fila.\n\n" white);
          TAMfila = (struct Tcarro *)realloc(
              TAMfila, (cont + 1) * sizeof(struct Tcarro));
          fila = fila + 1;
          opcao1 = 7;
          break;
        }
      }
    }
  }
}
