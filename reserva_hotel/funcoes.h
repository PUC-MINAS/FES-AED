<<<<<<< HEAD
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
void inicializa_dados (short reserva[42][181],short quartos [42][2],float preco_diaria[3], int MAX, double cpfs[MAX], int *nvagas)
{
    int a,q,d;
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
    a=0;
    while (a<1000)
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

                        aux=rand()%8;
                        if(aux<3){aux=3;}
                        for(d=d; d<d+aux; d++)
                        {
                            reserva[q][d]=newcpf;
                        }
                        a++;
                    }
                }
            }
        }
    }
    for(a=0;a<42;a++)
    {
        for(q=0;q<181;q++)
        {
            if (reserva[a][q]==-1){nvagas++;}
        }
    }
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
=======
#ifndef FUNCOES_H_INCLUDED
#define FUNCOES_H_INCLUDED

/*estrutura de data - usado para conversÃƒÂ£o de data juliana para gregoriana*/
struct date
{
    int dia;
    int mes;
};
typedef struct date data;

/*FunÃ§Ã£o que converte index para data*/
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

/*funÃ§Ã£o que converte data para index*/
int dataToIndex (int dia, int mes)
{
    int juli = gregoriana_to_juliana(dia, mes, 2018);
    return juli - (gregoriana_to_juliana(1,1,2018));
}

/*funÃ§Ã£o que retorna periodo de dias*/
int tempo_reserva (int dia_in,int mes_in,int dia_out,int mes_out)
{
    int juli = gregoriana_to_juliana(dia_in, mes_in, 2018);
    return juli - (gregoriana_to_juliana(dia_out,mes_out,2018));
}





/*FunÃ§Ã£o que lÃª dia e mÃªs digitado pelo usuÃ¡rio e faz validaÃ§Ã£o*/

void readData (int *dia, int *mes)
{
    scanf("%d/%d", dia, mes);
    while (!validaData(*dia, *mes, 2018) || *mes >6)
    {
        printf("\n###Data invÃƒÂ¡lida!###\n\n");
        printf("Data de entrada (dia/mes): ");
        scanf("%d/%d", dia, mes);
    }
}


/*funcao que ler nÃºmero de quartos digitado pelo usuÃ¡rio*/

int readNumQuarto (short quartos [42][2])
{
    int num_quarto;
    printf("Digite o nÃƒÂºmero do quarto: ");
    scanf("%d", &num_quarto);
    while (!validaNumQuarto(num_quarto, quartos))
    {
        printf("\n###NÃƒÂºmero de quarto invÃƒÂ¡lido!###\n\n");
        printf("Digite o nÃƒÂºmero do quarto: ");
        scanf("%d", &num_quarto);
    }
    return num_quarto;
}


/*funcao que ler nÃºmero de camas digitado pelo usuÃ¡rio*/
int readNumCamas (void)
{
    int camas;
    printf("NÃƒÂºmero de camas desejado? ");
    scanf("%d", &camas);
    while ( camas < 1 || camas > 3 )
    {
        printf("\n###NÃƒÂºmero de camas invÃƒÂ¡lido!###\n\n");
        printf("NÃƒÂºmero de camas desejado? ");
        scanf("%d", &camas);
    }
    return camas;
}

/*FunÃ§Ã£o que valida nÃºmero do quarto*/
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

/*FunÃ§Ã£o para validaÃ§Ã£o de data*/
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
/*void inicializa_dados (short reserva[42][181],short quartos [42][2],float preco_diaria[3], int MAX, double cpfs[MAX])
{

    int a,q,d,i;
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
    quartos[0][1]   =1;//[numero do quarto][numero de camas]
    quartos[1][1]   =2;
    quartos[2][1]   =3;    quartos[3][1]   =3;    quartos[4][1]   =1;    quartos[5][1]   =2;    quartos[6][1]   =3;    quartos[7][1]   =2;    quartos[8][1]   =3;    quartos[9][1]   =1;    quartos[10][1]  =1;    quartos[11][1]  =2;    quartos[12][1]  =3;    quartos[13][1]  =1;    quartos[14][1]  =3;    quartos[15][1]  =1;    quartos[16][1]  =2;    quartos[17][1]  =2;    quartos[18][1]  =1;    quartos[19][1]  =2;    quartos[20][1]  =3;    quartos[21][1]  =2;    quartos[22][1]  =3;    quartos[23][1]  =1;    quartos[24][1]  =1;    quartos[25][1]  =2;    quartos[26][1]  =3;    quartos[27][1]  =1;    quartos[28][1]  =3;    quartos[29][1]  =1;    quartos[30][1]  =2;    quartos[31][1]  =2;    quartos[32][1]  =1;    quartos[33][1]  =2;    quartos[34][1]  =3;    quartos[35][1]  =1;    quartos[36][1]  =2;    quartos[37][1]  =3;    quartos[38][1]  =3;    quartos[39][1]  =1;    quartos[40][1]  =2;    quartos[41][1]  =3;

    //definindo o numero dos quartos
    int apt=8;
    for(a=0; a<42; a++)
    {
        if (a%7==0)
        {
            apt=(apt+93);
        }
        quartos[a][0]=a+apt;
    }

   //gerando  1000 reservas
    a=0;
    while (a<1000)
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

                        newcpf=gera_cpf();
                        printf("%11.0d\n",newcpf);

                        aux=rand()%8;
                        if(aux<3){aux=3;}
                        //periodo
                        int l = d + aux;
                        for(d; d<l; d++)
                        {
                            reserva[q][d]=newcpf;
                            printf("a = %4d, d= %3d\n", a, d);
                        }
                        a++;
                        printf("    \n");

                    }

                }
            }
        }
    }

    int periodo = 0;
    while (a <1000) {
        //do {
            q = rand()%42;
            d = rand()%174;
            periodo = rand()%8;
            if (periodo < 3) {periodo = 3;}

            for (i = d; i < periodo; i++)
                {
                        if (reserva[q][d+i] != -1)
                            {

                            }

                 }

            }
       //
       //newcpf = gera_cpf();
        printf("A = %d - Quarto = %3d, dia= %3d, periodo= %d, cpf= %11.0lf\n", a, q, d, periodo, newcpf);
        a++;

    //}
    system("pause");

}*/





int incluir_reserva (short reserva[42][181], short quartos [42][2], float preco_diaria[3],int camas,double bcpf,double cpfs[5000],int dia_in,int mes_in,int dia_out,int mes_out)
{

    int ini_vetor=dataToIndex(dia_in,mes_in);
    int final_vetor=dataToIndex(dia_out,mes_out)+1;
    int tam_vetor=tempo_reserva(dia_in,mes_in,dia_out,mes_out);
    int i,id,i_vaga,aux,vaga,vaga_quartos[42],j;
    int quarto_aux[28];
    for(i=0; i<28; i++)
    {
        quarto_aux[i]=-1;
    };

    for(i=0; i<42; i++)
    {
        vaga_quartos[i]=-1;
    };







    for(i=0; i<42; i++)
    {
        if (reserva[i][j]==id)
        {
            vaga=0;
            return  3;
        };

        for(j=ini_vetor; j<final_vetor; j++)
        {
            if (reserva[i][j]==id)
            {
                vaga=0;
                continue;
            }

        }



    };


    if(localiza_quarto_vago(quarto_aux[28],camas,reserva[42][181],quartos [42][2],vaga_quartos[42],dia_in,mes_in,dia_out,mes_out)==1)
    {
        printf(" quartos disponiveis para reservar  com %d\n\n ",camas);
        for(i=0; i<28; i++)
        {
            if(vaga_quartos[i]!=-1)
            {
                printf("disponivel quarto nÃ‚Â° %d  preco %d \n",vaga_quartos[i],preco_diaria[camas-1]);
            }
            else{
                break;
                }

        }
    }
    else if(localiza_quarto_reserva(quarto_aux[28],camas,reserva[42][181],quartos[42][2],vaga_quartos[42],dia_in,mes_in,dia_out,mes_out)==1)
    {
        printf(" quartos disponiveis para reservar  com %d\n\n ",camas);
        for(i=0; i<28; i++)
        {
            if(vaga_quartos[i]!=-1)
            {
                printf("disponivel quarto nÃ‚Â° %d  preco %d \n",vaga_quartos[quarto_aux[i]],preco_diaria[quartos[quarto_aux[i]][1]-1]);
            }
            else
            {
                break;
            }

        }


    }
    else
    {
        return 2;

    }


return realizar_reserva( reserva[41][182],quartos[41][2] ,bcpf,cpfs[5000],vaga_quartos[42],dia_in, mes_in,dia_out,mes_out );
}


int realizar_reserva(short reserva[41][182],short quartos[41][2], double bcpf,double cpfs[5000],int vaga_quartos[42],int dia_in,int mes_in,int dia_out,int mes_out)
{
    int ini_vetor=dataToIndex(dia_in,mes_in);
    int final_vetor=dataToIndex(dia_out,mes_out)+1;
    int numquarto,val;
    int i,id,valido;
    char op;

  do{
        printf("gentileza informar o numero do quarto para reserva");
    scanf("%d",&numquarto);
    for(i=0; i<42; i++)
    {

        if(numquarto==quartos[i][0])
        {
            numquarto=i;
            break;
        }
    }

    for(i=0; i<28; i++)
    {
        if(vaga_quartos[i]==numquarto)
        {
            valido=1 ;
            break;

        }else
        valido=0;

    }

  }while(valido=0);

  do{
        printf("confirma a reserva  para o quarto %d no periodo  %d/%d ate %d/%d \n\n ",quartos[numquarto][0],dia_in,mes_in,dia_out,mes_out);
         op = getch();
        if(op=='s'||'S')
        {

            //id=criar_id(bcpf,cpfs[5000]);
            for(i=ini_vetor;i<final_vetor;i++)
            {

                reserva[numquarto][i]=id;
                val=1;
                return 4;
            }
        }else
		{
        printf("opcao invalida... [S]im ou [N]ÃƒÂ£o ");
		val=0;
		}


  }while(val=0);



}










void imprimir_reserva (short reserva[42][181], short quartos[42][2], float preco_diaria[3], double *cpfs, char op)
{
    int id_quarto, id_cpf, checkin, checkout, i, andar, dia_in, mes_in, dia_out, mes_out, num_quarto, d, q;
    switch (op)
    {
        case '1':
            num_quarto = readNumQuarto(quartos);
            for (i=0; i<42; i++)
            {
                if (num_quarto == quartos[i][0])
                {
                    id_quarto = i;
                }
            }
            andar = (int)(num_quarto/100);
            printf("Quarto: %d\n", num_quarto);
            printf("Andar: %dÃ‚Âº\n", andar);
            printf("Quantidade de camas: %d\n", quartos[id_quarto][1]);
            for (i=0; i<181; i++)
            {
                if (reserva[id_quarto][i] != -1)
                {
                    id_cpf = reserva[id_quarto][i];
                    checkin = i;

                    while (reserva[id_quarto][i] == id_cpf)
                    {
                        i++;
                    }

                    checkout = i;
                    indexToData(checkin, &dia_in, &mes_in);
                    indexToData(checkout, &dia_out, &mes_out);
                    printf("CPF: %.0lf\n", cpfs[id_cpf]);
                    printf("Data de entrada: %d/%d\n", dia_in, mes_in);
                    printf("Data de saÃƒÂ­da: %d/%d\n", dia_out, mes_out);
                }

            }
        break;
        case '2':
            printf("---JANEIRO---\n");
            for (q=0; q<42; q++)
            {
                for (d=0; d<31; d++)
                {
                    num_quarto = quartos[q][0];
                    if (reserva[q][d] != -1)
                    {
                        id_cpf = reserva[q][d];
                        checkin = d;
                        while (reserva[q][d] == id_cpf)
                        {
                            d++;
                        }
                        checkout = d;
                        indexToData(checkin, &dia_in, &mes_in);
                        indexToData(checkout, &dia_out, &mes_out);
                        printf("Quarto %d\n", num_quarto);
                        printf("CPF: %.0lf (%d/%d - %d/%d)\n", cpfs[id_cpf], dia_in, mes_in, dia_out, mes_out);
                    }

                }
            }
    }
}
























#endif // FUNCOES_H_INCLUDED
>>>>>>> master
