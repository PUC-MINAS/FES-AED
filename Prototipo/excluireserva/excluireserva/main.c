#include <stdio.h>
#include <stdlib.h>

/*Nesta opção o programa principal deverá chamar uma função passando, além das
estruturas de dados necessárias, o número do quarto, o período de permanência e
o CPF do passageiro.
A função deverá retornar um código que:
1 - indica período inválido;

Caso seja feita a exclusão,
deverá atualizar o número de vagas no hotel ao longo de todo o período,
excluindo o número do CPF do cliente nos dias referentes ao
período naquele quarto.*/


struct hotel
{
    int quarto[6][7], preco[4], dia[31][6];
    long cpf[31][6];
    short camas[6][7];
};
typedef struct hotel htl;

void excluir_reserva(int h.quarto[6][7], int h.dia[31][6], int periodo, int h.cpf[6][7]){
    int a,q,d,m,cpf,cont,andar,quarto,vagas;
    vagas=0;
    printf("Digite o periodo da estadia: ");
    scanf("%d",&periodo);
    printf("Digite o CPF que deseja excluir: ");
    scanf("%d",&cpf);
    cont=0;

//0 - indica que o quarto não existe;
    printf("Digite andar do quarto: ");
    scanf("%d",&andar);

    printf("Digite numero do quarto: ");
    scanf("%d",&quarto);

    if(andar>6 or andar<1 or quarto>7 or quarto<1)
    {
        printf("0 - Quarto não existe! ");
    }

    for (a=0; a<6; a++)
    {
        for(q=0; q<7; q++)
        {

            if(cpf==h.cpf[a][q])
            {
                cont=1;
                h.cpf=0;
                else
                    cont=0;
            }

        }
    }
                  if(cont==1)
                {
                    //3 - indica exclusão realizada com sucesso;
                    printf("3 - Exclusão realizada com sucesso!");
                    else
                    //2 - indica reserva inexistente no período;
                        printf("2 - Reserva inexistente. ");
                }
            }

//atualizar o número de vagas no hotel;
    for (a=0; a<6; a++){
        for(q=0; q<7; q++){
            for (m=0; m<6; m++){
                for(d=0; d<31; d++){
                   if(cpf[d][m]==0){
                    vagas++;
                   }
                }
            }
        }
    }



int main()
{
    int cpf[11],periodo;
    htl h;
    int a,q,apt;

    apt=101;
    h.preco[1]=117;
    h.preco[2]=150;
    h.preco[3]=180;

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
            printf("Quarto: %d  Camas: %d    Preco: %0.2d   \n",h.quarto[a][q], h.camas[a][q], h.preco[h.camas[a][q]]);
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
    excluir_reserva(reserva,num_quarto, dia, mes, ano, periodo );

    return 0;
}
