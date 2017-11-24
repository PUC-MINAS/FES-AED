#ifndef INICIALIZA_H_INCLUDED
#define INICIALIZA_H_INCLUDED



//reseta o programa
void inicializa_dados (short reserva[42][181],short quartos [42][2],float preco_diaria[3], double cpfs[MAX], int *nvagas)
{
    resetacamas(quartos);
    definepreco(preco_diaria);
    resetreservas(reserva, cpfs, nvagas);
    nomeiaquartos(quartos);
    //gerar1000reservas(reserva, nvagas, cpfs, MAX);
    gerar1000reservas2(reserva, nvagas, cpfs);
}

//gerando  1000 reservas
void gerar1000reservas(short reserva[42][181], int *nvagas, double cpfs[MAX])
{
    int x=0;
    int i=0;
    int a=0;
    int q,d,aux;

    double cpfnovo;
    int l;

    while (a<1000)
    {
        q = rand()%42;
        d = rand()%174;
        if (reserva[q][d]==-1)
        {
            aux=rand()%3;
            if(aux==0)
            {
                //printf("%4d",a);
                //sorteia periodo da reserva
                aux=rand()%8;
                if(aux<3){aux=3;}
                l=d+aux;
                //conferindo se os dias a diante estão vagos
                for(d;d<l;d++)
                {
                    if(reserva[q][d]==-1)
                    {
                        x++;
                    }
                }
                //se dias a diante livres salva cpf
                if (x==aux)
                {
                    for(i;i<MAX;i++)
                    {
                        if(cpfs[i]==-1)
                        {
                            cpfnovo=gera_cpf3();
                            cpfs[i]=cpfnovo;
                            a++;
                            break;
                        }
                    }
                    for(d;d<l;d++)
                    {
                        reserva[q][d]=criar_id(cpfnovo,cpfs);
                    }
                }

            }

        }
    }
}

//Correção gerar1000reservas
void gerar1000reservas2(short reserva[42][181], int *nvagas, double cpfs[MAX]){

    int a,q,d,i;
    int periodo = 0;
    int tst = 1, id_cpf;
    double newcpf;

    while (a <1000) {

        do {
            tst =1 ;
            q = rand()%42;
            d = rand()%170;
            periodo = rand()%8;
            if (periodo < 3) {periodo = 3;}

            for (i = 0; i < periodo; i++){
                if (reserva[q][d+i] != -1){
                    tst = 0;  // tst = 0, periodo com ocupação
                    break;
                }
            }
        }while (tst == 0);

        newcpf = gera_cpf3();
        id_cpf = criar_id(newcpf, cpfs);
        cpfs[id_cpf] = newcpf;
        for (i = 0; i < periodo; i++) {
            reserva[q][d+i] = id_cpf;
        }

        //Descomente o printf abaixo para fazer teste
        //printf("A = %d - Quarto = %3d, dia= %3d, periodo= %d, cpf= %11.0lf\n", a, q, d, periodo, newcpf);
        a++;
    }
    system("pause");
}

//definindo o numero dos quartos
void nomeiaquartos(short quartos[42][2])
    {
    int a,apt=8;
    for(a=0; a<42; a++)
    {
        if (a%7==0)
        {
            apt=(apt+93);
        }
        quartos[a][0]=a+apt;
    }
    }

//retorna as camas para o padrao
void resetacamas(short quartos[42][2])
{
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

}

//definindo o valor de quarto para quantidade de camas
void definepreco (float preco_diaria[3])
{
    int a;
    for(a=0; a<3; a++)
    {
        printf("Defina o valor do quarto para %d cama(s): ",a+1);
        scanf("%f", &preco_diaria[a]);
    }
    printf("\n");
}

//reseta todas as reservas
void resetreservas(short reserva[42][181], double cpfs[MAX], int *nvagas)
    {
        int a,q;
        nvagas=0;

        for(a=0; a<42; a++)
        {
            for(q=0; q<181; q++)
            {
                reserva[a][q]=-1;
                nvagas++;
            }
        }
        for(a=0;a<MAX;a++)
        {
            cpfs[a]=-1;
        }
    }



#endif // INICIALIZA_H_INCLUDED
