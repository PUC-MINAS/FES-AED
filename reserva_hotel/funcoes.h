#ifndef FUNCOES_H_INCLUDED
#define FUNCOES_H_INCLUDED

/*estrutura de data - usado para conversão de data juliana para gregoriana*/
struct date
{
    int dia;
    int mes;
};
typedef struct date data;

/*Função que converte index para data*/
void indexToData (int index, int *dia, int *mes)
{
    data juliana_to_gregoriana (int juliana);
    int datainicial = gregoriana_to_juliana(1,1,2018);
    int juli = datainicial + index;
    data dt;
    dt =  juliana_to_gregoriana(juli);
    *dia = dt.dia;
    *mes = dt.mes;
}

/*função que converte data para index*/
int dataToIndex (int dia, int mes)
{
    int juli = gregoriana_to_juliana(dia, mes, 2018);
    return juli - (gregoriana_to_juliana(1,1,2018));
}

/*função que retorna periodo de dias*/
int tempo_reserva (int dia_in,int mes_in,int dia_out,int mes_out)
{
    int juli = gregoriana_to_juliana(dia_in, mes_in, 2018);
    return juli - (gregoriana_to_juliana(dia_out,mes_out,2018));
}

float calcReserva (short quartos[42][2], float preco_diaria[3], int periodo, int num_quarto) {
    int camas, i;
    float preco;
    for (i=0; i<42; i++) {
        if (num_quarto == quartos[i][0]) {
            camas = quartos[i][1];
            break;
        }
    }
    preco = preco_diaria[camas-1];

    return preco * ((float)periodo);
}





/*Função que lê dia e mês digitado pelo usuário e faz validação*/
void readData (int *dia, int *mes)
{
    scanf("%d/%d", dia, mes);
    while (!validaData(*dia, *mes, 2018) || *mes >6)
    {
        printf("\n###Data inválida!###\n\n");
        printf("Data de entrada (dia/mes): ");
        scanf("%d/%d", dia, mes);
    }
}

/*funcao que ler número de quartos digitado pelo usuário*/
int readNumQuarto (short quartos [42][2])
{
    int num_quarto;
    printf("Digite o número do quarto: ");
    scanf("%d", &num_quarto);
    while (!validaNumQuarto(num_quarto, quartos))
    {
        printf("\n###Número de quarto inválido!###\n\n");
        printf("Digite o número do quarto: ");
        scanf("%d", &num_quarto);
    }
    return num_quarto;
}

/*funcao que ler número de camas digitado pelo usuário*/
int readNumCamas (void)
{
    int camas;
    printf("Número de camas desejado? ");
    scanf("%d", &camas);
    while ( camas < 1 || camas > 3 )
    {
        printf("\n###Número de camas inválido!###\n\n");
        printf("Número de camas desejado? ");
        scanf("%d", &camas);
    }
    return camas;
}

/*Função que valida número do quarto*/
int validaNumQuarto (int num, short quartos[42][2])
{
    int i;

    for (i = 0; i < 42; i++)
    {
        if (num == quartos[i][0])
        {
            return 1;
        }
    }
    return 0;
}

/*Função para validação de data*/
int validaData(int dia, int mes, int ano)
{
    if ((dia >= 1 && dia <= 31) && (mes >= 1 && mes <= 12) && (ano >= 1900 && ano <= 2100)) //verifica se os numeros sao validos
    {
        if ((dia == 29 && mes == 2) && ((ano % 4) == 0)) //verifica se o ano e bissexto
        {
            return 1;
        }
        if (dia <= 28 && mes == 2) //verifica o mes de feveireiro
        {
            return 1;
        }
        if ((dia <= 30) && (mes == 4 || mes == 6 || mes == 9 || mes == 11)) //verifica os meses de 30 dias
        {
            return 1;
        }
        if ((dia <=31) && (mes == 1 || mes == 3 || mes == 5 || mes == 7 || mes ==8 || mes == 10 || mes == 12)) //verifica os meses de 31 dias
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
    else
    {
        return 0;
    }
}




/*juliana_to_gregoriana ()*/
/*converte data juliana em gregoriana*/
data juliana_to_gregoriana (int juliana)
{
    int b, n, k, j, dia, mes, ano;
    long int data1;
    data dt;
    b= juliana+68569 ;
    n= ( 4*b )/146097;
    b = b-((146097 * n + 3)/4) ;
    k = 4000 * (b + 1)/1461001;
    b = b - (1461 * k)/4 + 31;
    j = ( 80 * b)/2447;
    dia = b - (2447 * j)/80;
    b = (j/11);
    mes = j + 2 - (12*b);
    ano = 100 * (n-49) + k + b;
    //printf ("\nTeste resultado d = %d, m = %d, a = %d\n", dia, mes, ano);
    data1 = (ano * 10000) + (mes * 100) + dia;
    dt.dia = (int)data1%100;
    data1 = (int)data1/100;
    dt.mes = (int)data1%100;
    return dt;
}

/*gregoriana_to-juliana ()*/
/*converte data gregoriana para juliana*/
int gregoriana_to_juliana (int dia, int mes, int ano)
{
    int juliana;
    juliana = (1461*(ano + 4800 + (mes -14)/12))/4 +
              (367*(mes - 2 - 12 *((mes -14)/12)))/12 -
              ( 3 * ((ano+ 4900 + (mes -14)/12)/100))/4 +
              dia - 32075 ;

    return juliana ;
}

//reseta o programa
void inicializa_dados (short reserva[42][181],short quartos [42][2],float preco_diaria[3], int MAX, double cpfs[MAX])
{
    int a,q,d, i;
    int aux,ex;
    double newcpf;

    //definindo o valor de quarto para quantidade de camas-+
    for(a=0; a<3; a++)
    {
        printf("Defina o valor do quarto para %d cama(s): ",a+1);
        scanf("%f", &preco_diaria[a]);
    }
    //reseta todas as reservas
    for(a=0; a<42; a++)
    {
        for(q=0; q<181; q++)
        {
            quartos[a][q]=-1;
        }
    }

    //definindo numero de camas pra cada quarto
    printf("Definindo número de camas pra cada quarto\n");
    quartos[0][1]   =1;//[numero do quarto][numero de camas]
    quartos[1][1]   =2;
    quartos[2][1]   =3;
    quartos[3][1]   =3;
    quartos[4][1]   =1;
    quartos[5][1]   =2;
    quartos[6][1]   =3;
    quartos[7][1]   =2;
    quartos[8][1]   =3;
    quartos[9][1]   =1;
    quartos[10][1]  =1;
    quartos[11][1]  =2;
    quartos[12][1]  =3;
    quartos[13][1]  =1;
    quartos[14][1]  =3;
    quartos[15][1]  =1;
    quartos[16][1]  =2;
    quartos[17][1]  =2;
    quartos[18][1]  =1;
    quartos[19][1]  =2;
    quartos[20][1]  =3;
    quartos[21][1]  =2;
    quartos[22][1]  =3;
    quartos[23][1]  =1;
    quartos[24][1]  =1;
    quartos[25][1]  =2;
    quartos[26][1]  =3;
    quartos[27][1]  =1;
    quartos[28][1]  =3;
    quartos[29][1]  =1;
    quartos[30][1]  =2;
    quartos[31][1]  =2;
    quartos[32][1]  =1;
    quartos[33][1]  =2;
    quartos[34][1]  =3;
    quartos[35][1]  =1;
    quartos[36][1]  =2;
    quartos[37][1]  =3;
    quartos[38][1]  =3;
    quartos[39][1]  =1;
    quartos[40][1]  =2;
    quartos[41][1]  =3;

    //definindo o numero dos quartos
    printf("Definindo o número de quartos\n");
    int apt=8;
    for(a=0; a<42; a++)
    {
        if (a%7==0)
        {
            apt=(apt+93);
        }
        quartos[a][0]=a+apt;
    }

    //Gerando 1000 reservas
    printf("Gerando 1000 reservas\n");
    a=0;
   /* while (a<1000)
    {
        for(q=0; q<42; q++)
        {
            for(d=0; d<181; d++)
            {
                if (reserva[q][d]==-1)
                {
                    aux=rand()%3;
                    if(aux==0)
                    {
                        newcpf=cpf_generator();
                        printf("Erro aqui?\n");

                        aux=rand()%8;
                        if(aux<3){aux=3;}
                        int l = d + aux;
                        for(d; d<l; d++)
                        {
                            reserva[q][d]=newcpf;
                            printf("Erro aqui? a = %d, d= %d\n", a, d);
                        }
                        a = a+1;
                        printf("E aqui? \n");
                    }

                }
            }
        }
    }*/
    int periodo = 0;
    while (a <1000) {
        //do {
            q = rand()%42;
            d = rand()%100;
            periodo = rand()%8;
            if (periodo < 3) {
                periodo = 3;
            }
            /*for (i = 0; i < periodo; i++) {
                if (reserva[q][d+i] != -1) {

                }
            }


        }while ();*/


        newcpf = cpf_generator();
        printf("A = %d - Quarto = %3d, dia= %3d, periodo= %d, cpf= %11.0lf\n", a, q, d, periodo, newcpf);
        a++;

    }
    system("pause");

}


int incluir_reserva (short reserva[42][181], short quartos [42][2], float preco_diaria[3],int num_quarto,double bcpf,int dia_in,int mes_in,int dia_out,int mes_out)
{

}


int ImprimirReserva (int numquarto, short reserva[42][181], short quartos[42][2], float precodiaria[3], double *cpfs)
    {
        int numcamas;
        int numandar = (int)(numquarto/100);
        int i;
        for (i=0; i<42; i++)
        {
            if (numquarto == quartos[i][0])
            {
                numcamas = quartos[i][1];
                break;
            }
        }
        printf("%d° andar, quarto %d (%d camas)", numandar, numquarto, numcamas);
    }



























#endif // FUNCOES_H_INCLUDED
