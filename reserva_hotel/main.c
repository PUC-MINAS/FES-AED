#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <conio.h>
#define ESC 27

int main()
{
    setlocale(LC_ALL,"portuguese");

    char op=0;
    int msg = 0, num_quarto, dia, mes, ano, periodo;
    long reserva[42][181];
    short quartos [42][2];
    float preco_diaria[3];

    //inicializa_dados (reserva, quartos, preco_diaria);

    while (op != ESC) {
        system("cls");
        printf("---Reserva de Hotel---\n");
        printf("\nSelecione uma das opções abaixo.\n");
        printf("1 - Fazer reserva\n");
        printf("2 - Cancelar reserva\n");
        printf("3 - Consultar reservas\n");
        printf("ESC para sair do programa\n");
        op = getch();

        switch (op){
            case 49:
                system("cls");
                printf("---Incluir Reserva---\n");
                //msg = incluir_reserva (reserva, quartos, preco_diaria);

                switch (msg) {
                    case 0:
                        printf("Quarto não existe.\n");
                        break;
                    case 1:
                        printf("Período inválido.\n");
                        break;
                    case 2:
                        printf("Quarto não disponível no período selecionado.\n");
                        break;
                    case 3:
                        printf("Cliente já possui reserva no mesmo período.\n");
                        break;
                    case 4:
                        printf("Reserva realizada com sucesso.\n");
                }

                system("pause");
                break;
            case 50:
                system("cls");
                printf("---Cancelar Reserva---\n");
                printf("Informe o número do quarto: ");
                scanf("%d", &num_quarto);
                printf("Data reservada do checking: ");
                scanf("%d-%d-%d", &dia, &mes, &ano);
                printf("Quantidade de dias reservados: ");
                scanf("%d", &periodo);
                //msg = excluir_reserva(reserva, num_quarto, dia, mes, ano, periodo );

                switch (msg) {
                    case 0:
                        printf("Quarto não existe.\n");
                        break;
                    case 1:
                        printf("Período inválido.\n");
                        break;
                    case 2:
                        printf("Não existe reserva para este período.\n");
                        break;
                    case 3:
                        printf("Reserva cancelada com sucesso.\n");
                        break;
                }

                system("pause");
                break;
            case 51:
                system("cls");
                printf("---Consultar Reservas---\n");
                printf("1 - Consultar dados de um quarto\n");
                printf("2 - Consultar todas as ocupações\n");
                printf("3 - Consultar dados de todos os quartos\n");
                printf("ESC para cancelar\n");
                op = getch();

                switch (op) {
                    case 49:
                        system("cls");
                        printf("---Consultar dados de um quarto---\n");
                        printf("Número do quarto: ");
                        scanf("%d", &num_quarto);
                        //msg = imprimir_reserva(reserva, quartos, preco_diaria, op, num_quarto );
                        break;
                    case 50:
                        system("cls");
                        printf("---Consultar todas as ocupações---\n");
                        //msg = imprimir_reserva(reserva, quartos, preco_diaria, op);
                        break;
                    case 51:
                        system("cls");
                        printf("---Consultar dados de todos os quartos---\n");
                        //msg = imprimir_reserva(reserva, quartos, preco_diaria, op);
                        break;
                    case ESC:
                        system("cls");
                        op=0;
                        break;

                }

                switch (msg) {
                    case 0:
                        printf("Não existe quarto com esse número.\n");
                        break;
                    case 1:
                        printf("Dados impressos.\n");
                        break;
                }


                system("pause");
                break;
            case ESC:
                system("cls");
                printf("Fechando programa");
                exit(1);
                break;
        }
    }
    return 0;
}
