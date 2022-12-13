#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


#define black "\033[0;30m"
#define red "\033[0;31m"
#define green "\033[0;32m"
#define yellow "\033[0;33m"
#define blue "\033[0;34m"
#define purple "\033[0;35m"
#define cyan "\033[0;36m"
#define white "\033[0;37m"


void teste(int *fila) {
  while ((*fila == 0) || (*fila < 0)) {
    system("clear");
    printf(red"Precisa ser um número inteiro positivo diferente de 0: \n" white);
    scanf("%d", &*fila);
  }
}

void teste2(float *preco) {
  while ((*preco == 0) || (*preco < 0)) {
    system("clear");
    printf(red"Precisa ser um número inteiro positivo diferente de 0: \n" white);
    scanf("%f", &*preco);
  }
}

void hora (time_t *valor_data, struct tm *data) { //função para controle de horário de brasília.
  if (data->tm_hour >= 3) {
    if (data->tm_min >=10) {
    printf("                    |Horário de Brasília: %d:%d\n", data->tm_hour-3, data->tm_min);
    } else {
      printf("                    |Horário de Brasília: %d:0%d\n", data->tm_hour-3, data->tm_min);
    }
  } else {
    if (data->tm_min >= 10) {
    printf("                    |Horário de Brasília: %d:%d\n", data->tm_hour+21, data->tm_min);
    } else {
      printf("                    |Horário de Brasília: %d:0%d\n", data->tm_hour+21, data->tm_min);
    }
  }
} 



void minimenu(float *comb_restante, int *qtd_carros, int *fila) {
  time_t valor_data; //variável que receberá o valor do horário
  valor_data = time(NULL);
  struct tm data = *localtime(&valor_data);
  time(&valor_data); //imprime o valor data
  hora(&valor_data, &data); //função para UTC 0 -> -3
  printf("                    |Quantidade de combustível restante: %.2f\n", *comb_restante);
  printf("                    |Quantidade de carros na fila: %d\n", *qtd_carros);
  printf("                    |Vagas sobrando na fila: %d\n", *fila);
  printf("\n\n");
}

void menu(int *opcao1) {
  printf(blue"Por favor, escolha uma das opções abaixo: \n\n" white);
  printf("[1] - Adicionar um carro na fila\n\n");
  printf("[2] - Abastecimento\n\n");
  printf("[3] - Exibir carros na fila de espera\n\n");
  printf("[4] - Relatório\n\n");
  printf("[5] - Encerrar\n\n");
  printf("[6] - Adicionar uma posição na fila\n\n");
  printf("[7] - Atualizar\n\n");
  printf("Opção: ");
  scanf("%d", &*opcao1);
}

void relatorio (int *opcao2) {
      printf(blue "\n\n---------RELATÓRIO---------\n" white);
      printf("Escolha a opção que deseja: \n\n");
      printf("1 - Quantidade de litros vendido.\n\n");
      printf("2 - Valor total arrecadado com as vendas. \n\n");
      printf("3 - Quantidade de carros atendidos. \n\n");
      printf("4 - Quantidade de combustível restante no tanque. \n\n");
      printf("5 - Gerar arquivo para impressão com todas as informações do relatório. \n\n");
      printf("6 - Voltar ao menu anterior. \n\n");
      printf("7 - Atualizar.");

      printf("\n\nEscolha uma opção: ");
      scanf("%d", &*opcao2);
}

/*
    int tm_sec;    Indica os segundos de 0 a 59
    int tm_min;    Indica os minutos de 0 a 59
    int tm_hour;   Indica as horas de 0 a 24
    int tm_mday:   Indica os dias do mês de 1 a 31
    int tm_mon;    Indica os meses do ano de 0 a 11
    int tm_year;   Indica o ano a partir de 1900
    int tm_wday;   Indica o dia da semana de 0 (domingo) até 6 (sábado)
    int tm_yday;   Indica o dia do ano de 1 a 365
    int tm_isdst;  Indica o horário de verão se for diferente de zero
*/

struct Tcarro {
  int ano;
  char placa[20];
  char cor[20];
  char marca[20];
  char modelo[20];
};

