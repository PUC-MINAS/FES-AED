#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <conio.h>
#include "funcoes.h"
#include "cpfb.h"
#define ESC 27
#define MAX 5000



int main()
{
    setlocale(LC_ALL,"portuguese"); //seta caracteres portugueses
    char op=0;
    const int ano = 2018;
    const int DATAINICIAL = gregoriana_to_juliana(1,1,2018);
    int num_quarto, dia, mes, periodo;
    short reserva[42][181];  //reseva[id do quarto][dia] = id_cpfs
    short quartos [42][2]; //quartos[numero do quarto][quantidade de camas]
    float preco_diaria[3]; // preco_diaria[quant_camas-1] = preco
    double cpfs[MAX];
    int juliana;
    data dt;
    int cpf, dig;
    double bcpf;
    float preco;



    //teste indexToDate
    /*int index = 5;
    indexToData(index, &dia, &mes);
    printf("index = %d, dia= %d, mes= %d", index, dia, mes);
    system("pause");*/

    inicializa_dados(reserva, quartos, preco_diaria, MAX, cpfs);

    //teste calcReserva
    quartos[0][0] = 100;
    quartos[0][1] = 2;
    preco = calcReserva (quartos, preco_diaria, 5, 100);
    printf("Preco reserva %.2f\n", preco);
    system("pause");

    //teste de referenciar matriz reserva por data juliana
    /*int dia1 = 2, mes1= 1;
    int dia2 = 10, mes2= 1;
    int conv_juli1 = gregoriana_to_juliana(dia1, mes1, 2018);
    int conv_juli2 = gregoriana_to_juliana(dia2, mes2, 2018);
    printf("Juli1 = %d\n", conv_juli1);
    printf("Juli2 = %d\n", conv_juli2);
    printf("Juli1 - Juli2 = %d\n", conv_juli2 - conv_juli1);
    printf("Posic�o= %d\n", dataToIndex(30,6));
    system("pause");*/


    /*Teste de convers�o de CPF entre double e int
    printf("Tamanho vetor cpfs: %d\n", sizeof(cpfs));
    printf("Tamanho matriz reserva: %d\n", sizeof(reserva));
    printf("Tamanho matriz quartos: %d\n", sizeof(quartos));
    cpfs[0] = 99999999999;
    cpf = (int)(cpfs[0]/100);
    dig = cpfs[0] - (double)cpf*100;
    cpfDoubleToInt(&cpfs[0], &cpf, &dig);
    printf("CPFS[0] = %f\n", cpfs[0]);
    printf("Convertido CPFS[0] = %d-%d\n", cpf, dig );
    //cpfs[1] = (double)cpf*100 + dig;
    cpfIntToDouble(&cpfs[1], &cpf, &dig);
    printf("CPFS[1] = %f\n", cpfs[1]);
    system("pause");*/

    //teste de data juliana
    /*printf("testando data juliana\n");
    juliana = gregoriana_to_juliana(25,03,2018);
    printf("Juliana = %d\n", juliana);
    dt = juliana_to_gregoriana(juliana);
    printf("Gregoriana %d - %d\n\n", dt.dia, dt.mes);
    system("pause");*/

    //teste cpf
    /*printf("Informe o CPF: ");
    scanf("%lf", &bcpf );
    printf("%f", bcpf);

    if ( valida_cpf(bcpf)){
        printf("\nCPF ok\n");
    }
    else {
        printf("\ninvalido\n");
    }
    system("pause");*/

    while (op != ESC) {
        system("cls"); //limpa tela
        printf("---Reserva de Hotel---\n");
        printf("\nSelecione uma das op��es abaixo.\n");
        printf("1 - Fazer reserva\n");
        printf("2 - Cancelar reserva\n");
        printf("3 - Consultar reservas\n");
        printf("ESC para sair do programa\n");
        op = getch();

        switch (op){
            case '1':  //op=1

                system("cls");
                int camas, dia_in, dia_out, mes_in, mes_out, check=1, msg= 0;

                printf("---Incluir Reserva---\n");

                camas = readNumCamas();

                printf("Data de entrada (dia/mes): ");
                readData(&dia_in, &mes_in);

                printf("Data de sa�da (dia/mes): ");
                readData(&dia_out, &mes_out);
                while (gregoriana_to_juliana(dia_out, mes_out, 2018) < gregoriana_to_juliana(dia_in, mes_in, 2018) )
                    {
                        printf("###Data de sa�da n�o pode menor do que a data de entrada!###\n\n");
                        printf("Data de sa�da (dia/mes): ");
                        readData(&dia_out, &mes_out);
                    }

                //check = print informacoes dos quartos dispon�veis segundo o numero de camas solicitado. retornar true se tiver quartos que atendem a condi��o e false se n�o tiver

                if (check){

                    num_quarto = readNumQuarto(quartos);

                    bcpf = readCpf();

                    //msg = incluir_reserva (reserva, quartos, preco_diaria, num_quarto, bcpf);
                }
                else {
                    printf("N�o temos quartos dispon�veis com %d cama(s) para este per�odo\n", camas);
                    if (camas < 3) {
                        printf("Temos estes quartos dispon�veis:\n");
                        //check = print informa��es de quartos dispon�veis. retornar true se tiver quartos que atendem a condi��o e false se n�o tiver
                        check = 1;
                        if (check) {
                            printf("Deseja continuar com a reserva?(s/n)");
                            op = getch();
                            if (op == 's' || op == 'S') {

                                num_quarto = readNumQuarto(quartos);

                                bcpf = readCpf();
                                //msg = incluir_reserva (reserva, quartos, preco_diaria, num_quarto, bcpf);
                            }
                            else {
                                msg = -1;
                            }
                        }
                    }
                }


                switch (msg) {
                    case 0:
                        printf("Quarto n�o existe.\n");
                        break;
                    case 1:
                        printf("Per�odo inv�lido.\n");
                        break;
                    case 2:
                        printf("Quarto n�o dispon�vel no per�odo selecionado.\n");
                        break;
                    case 3:
                        printf("Cliente j� possui reserva no mesmo per�odo.\n");
                        break;
                    case 4:
                        printf("Reserva realizada com sucesso.\n");
                        break;
                    case -1:
                        printf("\n\nOpera��o cancelada!");
                }

                system("pause");
                break;

            case '2':  //op=2
                system("cls");
                printf("---Cancelar Reserva---\n");

                num_quarto = readNumQuarto(quartos);

                printf("Data do check in (dia/mes): ");
                readData(&dia_in, &mes_in);

                printf("Data do check out (dia/mes): ");
                scanf("%d", &dia_out, &mes_out);

                bcpf = readCpf();

                //msg = excluir_reserva(reserva, num_quarto, dia, mes, periodo, bcpf, cpfs );

                switch (msg) {
                    case 0:
                        printf("Quarto n�o existe.\n");
                        break;
                    case 1:
                        printf("Per�odo inv�lido.\n");
                        break;
                    case 2:
                        printf("N�o existe reserva para este per�odo.\n");
                        break;
                    case 3:
                        printf("Reserva cancelada com sucesso.\n");
                        break;
                    case 4:
                        printf("CPF n�o corresponde � reserva.\n");
                        break;
                }

                system("pause");
                break;

            case 51:  //op=3
                system("cls");
                printf("---Consultar Reservas---\n");
                printf("1 - Consultar dados de um quarto\n");
                printf("2 - Consultar todas as ocupa��es\n");
                printf("3 - Consultar dados de todos os quartos\n");
                printf("ESC para cancelar\n");
                op = getch();

                switch (op) {
                    case 49:
                        system("cls");
                        printf("---Consultar dados de um quarto---\n");

                        //num_quarto = readNumQuarto(quartos);

                        //ImprimirReserva(num_quarto, reserva, quartos, preco_diaria, cpfs);

                        //msg = imprimir_reserva(reserva, quartos, preco_diaria, op, num_quarto );

                        break;
                    case 50:
                        system("cls");
                        printf("---Consultar todas as ocupa��es---\n");
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
                   printf("N�o existe quarto com esse n�mero.\n");
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
