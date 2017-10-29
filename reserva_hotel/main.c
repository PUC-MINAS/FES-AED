#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <conio.h>
#define ESC 27

int main()
{
    char op=0;
    setlocale(LC_ALL,"portuguese");
    while (op != ESC) {
        system("cls");
        printf("---Reserva de Hotel---\n");
        printf("\nSelecione uma das opções abaixo.\n");
        printf("1 - Fazer reserva\n");
        printf("2 - Cancelar reserva\n");
        printf("3 - Consultar reserva\n");
        printf("ESC para sair do programa\n");
        op = getch();

        switch (op){
            case 49:
                system("cls");
                printf("Opção 1\n");
                system("pause");

                //chama função incluir reserva
                break;
            case 50:
                system("cls");
                printf("Opção 2\n");
                system("pause");

                //chama função excluir reserva
                break;
            case 51:
                system("cls");
                printf("Opção 3\n");
                system("pause");

                //imprimir reserva
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
