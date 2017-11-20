#include <stdio.h>
#include <stdlib.h>

/*função que retorna periodo de dias*/
tempo_reserva (int dia_in,int mes_in,int dia_out,int mes_out)
/*converte data juliana em gregoriana*/
data juliana_to_gregoriana (int juliana)
/*converte data gregoriana para juliana*/
int gregoriana_to_juliana (int dia, int mes, int ano)


struct hotel
{
    int quarto[6][7], preco[3], dia[31][6];
    long cpf[31][6];
    short camas[6][7];
};
typedef struct hotel htl;

int main()
{
    htl h;
    int a,q,apt;

    apt=101;
    h.preco[0]=117;
    h.preco[1]=150;
    h.preco[2]=180;
    for(a=0; a<6; a++)
    {
        for(q=0; q<7; q++)
        {
            h.quarto[a][q]=q+apt;
            h.camas[a][q]= rand()%4;
            if (h.camas[a][q]==0)
            {
                h.camas[a][q]=1;
            }
            printf("Quarto: %d  Camas: %d    Preco: %0.2d   \n",h.quarto[a][q], h.camas[a][q], h.preco[h.camas[a][q]-1]);
        }
        apt=apt+100;
        printf("\n");
    }
    int dia,mes;
    for(a=0; a<6; a++)
    {
        mes=a+1;
        for(q=0; q<31; q++)
        {
            dia=q+1;

            printf("Dia: %2d Mes: %2d CPF: %11d\n",dia,mes,h.cpf[a][q]);
        }
        printf("\n");
    }

    return 0;
}
