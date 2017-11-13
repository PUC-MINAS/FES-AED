#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <conio.h>
#include "funcoes.h"
#define ESC 27



int main()
{
    setlocale(LC_ALL,"portuguese"); //seta caracteres portugueses
    char op=0;
    const int ano = 2018;
    const int DATAINICIAL = gregoriana_to_juliana(1,1,2018);
    int msg = 0, num_quarto, dia, mes, periodo;
    long reserva[42][181];  //resera[id do quarto][dia] = cpf
    short quartos [42][2]; //quartos[n][0] = numero do quarto; quartos[42][1] = quantidade de camas
    float preco_diaria[3]; // preco_diaria[quant_camas-1] = preco
    int juliana;
    data dt;
    int cpf, dig;

    //inicializa_dados (reserva, quartos, preco_diaria);

    //teste de data juliana
    /*printf("testando data juliana\n");
    juliana = gregoriana_to_juliana(25,03,2018);
    printf("Juliana = %d\n", juliana);
    dt = juliana_to_gregoriana(juliana);
    printf("Gregoriana %d - %d\n\n", dt.dia, dt.mes);
    system("pause");*/

    //teste cpf
    /*printf("Informe o CPF: ");
    scanf("%d-%d", &cpf, &dig );
    if ( valida_cpf(cpf, dig)){
        printf("\nCPF ok\n");
    }
    else {
        printf("\ninvalido\n");
    }
    system("pause");*/

    while (op != ESC) {
        system("cls"); //limpa tela
        printf("---Reserva de Hotel---\n");
        printf("\nSelecione uma das opções abaixo.\n");
        printf("1 - Fazer reserva\n");
        printf("2 - Cancelar reserva\n");
        printf("3 - Consultar reservas\n");
        printf("ESC para sair do programa\n");
        op = getch();

        switch (op){
            case 49:  //op=1
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

            case 50:  //op=2
                system("cls");
                printf("---Cancelar Reserva---\n");
                printf("Informe o número do quarto: ");
                scanf("%d", &num_quarto);
                printf("Data reservada do checking: dia/mes");
                scanf("%d/%d", &dia, &mes);
                printf("Quantidade de dias reservados: ");
                scanf("%d", &periodo);
                //msg = excluir_reserva(reserva, num_quarto, dia, mes, periodo );

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
            case 51:  //op=3
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

                if (msg==0){
                   printf("Não existe quarto com esse número.\n");
                }
                system("pause");
                break;

            case ESC: //op=ESC
                system("cls");
                printf("Fechando programa");
                exit(1);
                break;
        }
    }
    return 0;
}
