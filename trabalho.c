#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#define L 48

// Alunos:
// Caio Carneiro Fernandes Fereira
// Gabriel Reis do Valle Silvestre
// Robert Cardoso Cantares Martins
// Wendel Marcio de Oliveira Filho

typedef struct {
  int   cod;
  char  nome_passageiro[40];
  char  tel[15];
  char  data_nasc[11];
  char  tipo;
  char  status;
  float valor;
} Passageiro;

typedef struct {
  Passageiro cadeira[L];
  int        cadeiras_ocupadas;
  int        passagens;
  int        passagens_inteiras;
  int        passagens_meias;
  char       origem[20];
  char       destino[20];
  char       data[15];
  char       horario_partida[7];
  char       horario_chegada[7];
  float      valor_arrecadado;
} ONIBUS;

void inicializar_sala(ONIBUS *s) {
  int i, j;
  for(i=0; i<L; i++)
    s -> cadeira[i].status='V';
  s -> valor_arrecadado = 0.0;
  s -> cadeiras_ocupadas = 0;
  s -> passagens = 0;
  s -> passagens = 0;
  s -> passagens_inteiras = 0;
  s -> passagens_meias = 0;
  strcpy(s -> origem, "GOIANIA");
  strcpy(s -> destino, "BRASILIA");
  strcpy(s -> data, "10/11/2021");
  strcpy(s -> horario_partida, "15:30");
  strcpy(s -> horario_chegada, "18:30");
}

void Menu() {
  printf("  M E N U   O N I B U S\n");
  printf("1 - Adicionar passageiro\n");
  printf("2 - visualizar passageiro\n");
  printf("3 - Consultar uma determinada poltrona do onibus\n");
  printf("4 - Exibir passageiros cadastrados\n");
  printf("5 - Exibir dados de controle\n");
  printf("6 - Reemitir ticket\n");
  printf("7 - Sair do aplicativo\n");
  printf("Opcao: ");
}

void ler_passageiro(Passageiro *p, ONIBUS S) {
  int i, c=1, cont;
  for(i=0; i<L; i++)
    if(S.cadeira[i].status != 'V')
      c++;
  (p -> cod) = c;
  getchar();

  printf("Entre com o Nome do Passageiro: \n");
  fgets(p->nome_passageiro,40,stdin);
  printf("\n");

  printf("Entre com o Telefone do Passageiro: \n");
  fgets(p->tel,15,stdin);
  printf("\n");

  printf("Entre com a Data de Nascimento do Passageiro: \n");
  fgets(p->data_nasc,11,stdin);
  printf("\n");
}

void exibir_sala(ONIBUS s) {
  int i, j;
  printf("EXIBICAO DO ONIBUS\n");
  printf("++++++++ ++ ++++++\n\n");
  for(i=0; i<L; i = i+4) {
    printf("%2d  %2d        %2d  %2d\n",i+1,i+2,i+4,i+3);
		printf("%2c  %2c        %2c  %2c\n",s.cadeira[i].status, s.cadeira[i+1].status, s.cadeira[i+3].status, s.cadeira[i+2].status);
  }
}

void cadastrar_passageiro(ONIBUS *s, Passageiro p, int l, int cont) {
  s -> cadeira[l-1] = p;
  s -> valor_arrecadado += p.valor;
  s -> cadeiras_ocupadas++;
  s -> passagens++;
  if(cont == 1) {
      s -> passagens_inteiras++;
  }
    else if(cont == 2) {
        s -> passagens_meias++;
    }
}

void exibir_passageiro(Passageiro a) {
  printf(" \n========= Ticket %6d =========\n", a.cod);
  printf(" Nome do passageiro: %s\n", a.nome_passageiro);
  printf(" Telefone do passageiro: %s\n", a.tel);
  printf(" Valor da passagem: R$ %.2f\n", a.valor);
  printf(" Tipo da passagem: R$ %c\n", a.tipo);
  printf("=================================\n");
}

void controle_onibus(ONIBUS s) {
  printf("=========================================\n");
	printf(" Valor arrecadado: %0.2f\n", s.valor_arrecadado);
	printf(" Poltronas ocupadas: %d\n",s.cadeiras_ocupadas);
	printf(" Passagens inteiras: %d\n",s.passagens_inteiras);
	printf(" Passagens meias: %d\n",s.passagens_meias);
	printf("=========================================\n");
}

void exibir_ticket(Passageiro a) {
  printf("==========================================\n");
  printf("   TICKET N. %d\n", a.cod);
  printf("+++++++ ++ ++++ ++ ++++++\n");
  printf("O NUMERO DO ONIBUS E 215\n");
  printf("O HORARIO DE EMBARQUE E 15:30\n");
  printf("O HORARIO DE CHEGADA E 18:30\n");
  printf("A CIDADE DE SAIDA DO ONIBUS E GOIANIA\n");
  printf("A CIDADE DE CHEGADA DO ONIBUS E BRASILIA\n");
  printf("O NUMERO DA POLTRONA E ");
}

void Carregar_onibus(ONIBUS *o) {
  FILE *fp;
  fp = fopen("Onibus.dat", "rb");
  if(fp == NULL) {
      inicializar_sala(&(*o));
  }
    else {
        fread(&(*o), sizeof(ONIBUS), 1, fp);
          fclose(fp);
    }
}

void Gravar_onibus(ONIBUS o) {
  FILE *fp;
  fp = fopen("Onibus.dat", "wb");
  if(fp == NULL) {
      printf("Erro ao abrir arquivo.\n");
      return;
  }
    else {
        printf("Arquivo binario criado com sucesso.\n");
        fwrite(&o, sizeof(ONIBUS), 1, fp);
    }
  fclose(fp);
}

int main() {
  Passageiro A;
  ONIBUS S;
  int l, c, i;
  int op, cont;
  Carregar_onibus(&S);
  do {
    Menu();
    scanf("%d", &op);
    switch(op) {
      case 1: ler_passageiro(&A, S);
              printf("Escolha uma poltrona do onibus que nao esteja ocupada\n");
              exibir_sala(S);
              printf("Entre com a posicao da cadeira:\n");
              scanf("%d",&l);
              A.status = 'O';
              printf("\n");
              printf("Entre com o tipo do seu ingresso...\n");
              printf("\n");
              printf("Digite '1' para passagem inteira e '2' para meia:\n");
              scanf("%d", &cont);
              printf("\n");
              switch(cont) {
                case 1: A.tipo = 'I';
                        A.valor = 50;
                        cadastrar_passageiro(&S, A, l, cont);
                        exibir_ticket(A);
                        printf("%d\n", l);
                        break;

                case 2: A.tipo = 'M';
                        A.valor = 25;
                        cadastrar_passageiro(&S, A, l, cont);
                        exibir_ticket(A);
                        printf("%d\n", l);
                        break;

                default:printf("Entre com uma opcao valida...\n");
                        break;
              }
              break;

      case 2: exibir_sala(S);
              break;

      case 3: exibir_sala(S);
              printf("Entre com o numero da poltrona\n");
              scanf("%d", &l);
              if(S.cadeira[l-1].status == 'V')
                  printf("A poltrona %d esta vaga\n", l);
                else {
                    printf("A poltrona %d esta ocupada por:\n", l);
                    exibir_passageiro(S.cadeira[l-1]);
                }
              break;

      case 4: printf("Exibicao dos passageiros cadastrados\n");
              for(i=0; i<L; i++)
                if(S.cadeira[i].status != 'V')
                  exibir_passageiro(S.cadeira[i]);
              break;

      case 5: controle_onibus(S);
              break;

      case 6: exibir_sala(S);
              printf("Entre com a poltrona do onibus\n");
              scanf("%d", &l);
              exibir_ticket(A);
              printf("%d\n", l);
              break;

      case 7: printf("OBRIGADO POR USAR NOSSO APLICATIVO - VOLTE SEMPRE\n");
              Gravar_onibus(S);
              break;

      default:printf("Entre com a opcao correta de 1 a 6\n");
              break;
    }
  } while(op != 7);
  return 0;
}
