#include <stdio.h>
#include <stdlib.h>
#include "funcoes.h"

int main()
{





    int cama,dia,mes,val,dgf,cpf;
    //dgf usada como auxiliador do digito verificador do cpf
    // val variavel que recebe 0 ou 1 sendo 0 falso e 1 para verdadeiro na validacao de data



    do
    {
        printf("\n informe o numero de camas: ") ;
        scanf("%d",&cama);

        if(cama<1||cama>3)
        {
            printf("Numero de camas invalido digite novamente ..");

        }

    }while(cama<1||cama>3);


    do
    {
        printf("informe o dia :");
        scanf("%d",&dia);
        system("cls");
        do
        {
            printf("informe o mes da reserva:");
            scanf("%d",&mes);
            val=1;

            if(mes<1||mes>12)
            {
                printf("mes invalido digite novamente ");
            }

            }while(mes<1||mes>12);

            if(mes%2==0||dia==31)
            {
                printf("data invalida ");
                val=0;
            }
            else if(mes==2||dia>28)
            {
                printf("data invalida ");
                val=0;
            }



        }
        while(val==0);

        printf("informe o cpf para a reservar");
        scanf("%d-%d",&cpf,&dgf);







        return 0;





    }
