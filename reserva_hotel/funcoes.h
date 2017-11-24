#ifndef FUNCOES_H_INCLUDED
#define FUNCOES_H_INCLUDED

const int MAX = 5000;

/*estrutura de data - usado para conversÃ£o de data juliana para gregoriana*/
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
    return dataToIndex(dia_out, mes_out) - dataToIndex(dia_in, mes_in);
}

/*Função para calcular o preco total de uma reserva*/
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
        printf("\n###Data invÃ¡lida!###\n\n");
        printf("Data de entrada (dia/mes): ");
        scanf("%d/%d", dia, mes);
    }
}


/*funcao que ler número de quartos digitado pelo usuário*/
int readNumQuarto (short quartos [42][2])
{
    int num_quarto;
    printf("Digite o nÃºmero do quarto: ");
    scanf("%d", &num_quarto);
    while (!validaNumQuarto(num_quarto, quartos))
    {
        printf("\n###NÃºmero de quarto invÃ¡lido!###\n\n");
        printf("Digite o nÃºmero do quarto: ");
        scanf("%d", &num_quarto);
    }
    return num_quarto;
}


/*funcao que ler número de camas digitado pelo usuário*/
int readNumCamas (void)
{
    int camas;
    printf("NÃºmero de camas desejado? ");
    scanf("%d", &camas);
    while ( camas < 1 || camas > 3 )
    {
        printf("\n###NÃºmero de camas invÃ¡lido!###\n\n");
        printf("NÃºmero de camas desejado? ");
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
data juliana_to_gregoriana(int juliana)
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

/*Localiza index de posição do CPF no vetor cpfs
  Retorna index da posição se encontrar ou -1 se não encontrar*/
int localizar_id( double bcpf,double cpfs[MAX])
{
    int i=0;
    int id=-1;
    for(i=0; i<MAX;i++)
    {
        if(bcpf==cpfs[i])
        {
            return i;
        }
    }
    return id;
}

/*Cria um index para um cpf e armazenha o cpf no vetor cpfs
  Retorna posição do vetor*/
int criar_id(double bcpf, double cpfs[MAX])
{
    int i;
    int id_cpf = localizar_id(bcpf,cpfs);

    if(id_cpf==-1)
    {
        for(i=0; i<MAX; i++)
        {
            if(cpfs[i]==-1)
            {
                cpfs[i]=bcpf;
                id_cpf=i;
                return id_cpf;
            }
        }
    }

return id_cpf;
}


int localiza_quarto_vago(int quarto_aux[28],int camas,short reserva[42][181],short quartos [42][2],int vaga_quartos[42],int dia_in,int mes_in,int dia_out,int mes_out)
{

    int vaga= -1, ini_vetor=dataToIndex(dia_in,mes_in);
    int final_vetor=dataToIndex(dia_out,mes_out)+1;
    int tam_vet=tempo_reserva(dia_in,mes_in,dia_out,mes_out);
    int j,i,aux=0,i_vaga=0;
    int cont= 0;


    for(i=0; i<28; i++)
    {
        quarto_aux[i]=-1;
    }



    for(i=0; i<42; i++)
    {

        if(quartos[i][1]== camas)
        {
            quarto_aux[aux]=i;
            aux++;

        }

    }



    i_vaga=0;
    for(aux=0; aux<24; aux++)
    {
        if(quarto_aux[aux]==-1)
        {
            break;
        }

        for(j=ini_vetor; j<final_vetor; j++)
        {
            if (reserva[quarto_aux[aux]][j]!=-1)
            {
                vaga=0;
                //continue;

            }
            else
            {
                if(j==final_vetor-1)
                {
                    vaga_quartos[i_vaga]=quarto_aux[aux];
                    i_vaga++;
                    vaga=1;
                }


            }
        }
    }

    return vaga;

 }

 /* Localiza o na matriz de reservar o quarto que nao possuem ocupacao com mais camas */
 int localiza_quarto_reserva(int quarto_aux[28],int camas,short reserva[42][181],short quartos [42][2],int vaga_quartos[42],int dia_in,int mes_in,int dia_out,int mes_out){
  int i,i_vaga,j,vaga,ini_vetor=dataToIndex(dia_in,mes_in);
    int final_vetor=dataToIndex(dia_out,mes_out)+1;

  int aux=0;
 if( camas==3)
 {
     return 0;
 }


    for(i=0; i<28; i++)
    {
   quarto_aux[i]=-1;
    };

 for(i=0; i<42; i++)
    {

        if(quartos[i][1]> camas)
        {
            quarto_aux[aux]=i;
            aux++;

        }

    };


    i_vaga=0;
    for(aux=0; aux<24; aux++)
    {
        if(quarto_aux[aux]==-1)
        {
           break;
        }


        for(j=ini_vetor; j<final_vetor; j++)
        {
            if (reserva[quarto_aux[aux]][j]!=-1)
            {
                vaga=0;
                continue;

            }
            else
            {
              if(j==final_vetor-1)
                {
                   vaga_quartos[i_vaga]=quarto_aux[aux];
                   i_vaga++;
                   vaga=1;
                }

            }

        }
    }

 return vaga;

 }


int incluir_reserva (short reserva[42][181], short quartos [42][2], float preco_diaria[3],int camas,double bcpf,double cpfs[MAX],int dia_in,int mes_in,int dia_out,int mes_out)
{

    int ini_vetor=dataToIndex(dia_in,mes_in);
    int final_vetor=dataToIndex(dia_out,mes_out)+1;
    int tam_vetor=tempo_reserva(dia_in,mes_in,dia_out,mes_out);
    int i,id,i_vaga,aux,vaga,vaga_quartos[42],j;
    int quarto_aux[28];
    int cont = 0;

    id = criar_id(bcpf, cpfs);



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
        }

        for(j=ini_vetor; j<final_vetor; j++)
        {
            if (reserva[i][j]==id)
            {
                vaga=0;
                continue;
            }

        }
    }




    if(localiza_quarto_vago(quarto_aux,camas,reserva,quartos,vaga_quartos,dia_in,mes_in,dia_out,mes_out)==1)
    {

        printf("quartos disponiveis para reservar  com %d cama(s)\n\n ",camas);
        for(i=0; i<28; i++)
        {
            if(vaga_quartos[i]!=-1)
            {
                printf("disponivel quarto nº %d  preco %.2f \n",vaga_quartos[i],preco_diaria[camas-1]);
            }
            else{
                break;
                }

        }
    }
    else if(localiza_quarto_reserva(quarto_aux,camas,reserva,quartos,vaga_quartos,dia_in,mes_in,dia_out,mes_out)==1)
    {
        printf("quartos disponiveis para reservar  com %d cama(s)\n\n ",camas);
        for(i=0; i<28; i++)
        {
            if(vaga_quartos[i]!=-1)
            {
                printf("disponivel quarto nÂ° %d  preco %d \n",vaga_quartos[quarto_aux[i]],preco_diaria[quartos[quarto_aux[i]][1]-1]);
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



return realizar_reserva( reserva,quartos ,bcpf,cpfs,vaga_quartos,dia_in, mes_in,dia_out,mes_out );
}


int realizar_reserva(short reserva[41][182],short quartos[41][2], double bcpf,double cpfs[MAX],int vaga_quartos[42],int dia_in,int mes_in,int dia_out,int mes_out)
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
        printf("opcao invalida... [S]im ou [N]Ã£o ");
		val=0;
		}


  }while(val=0);



}

//Imprimir Reservas

void imprimir_mes (float preco_diaria[3], short reserva[42][181], short quartos[42][2], double *cpfs, int checkin, int dia_in, int mes_in, int checkout, int dia_out, int mes_out, int num_quarto, int id_cpf, int mes)
{
    int q, d, inicio, fim, periodo;
    float preco, cont=0;
    if (mes == 1) {
        inicio = 0;
        fim = 30;
    }
    else if (mes == 2) {
        inicio = 31;
        fim = 59;
    }
    else if (mes == 3) {
        inicio = 60;
        fim = 91;
    }
    else if (mes == 4) {
        inicio = 92;
        fim = 122;
    }
    else if (mes == 5) {
        inicio = 123;
        fim = 154;
    }
    else if (mes == 6) {
        inicio = 155;
        fim = 185;
    }
    for (q=0; q<42; q++)
    {
        for (d=inicio; d<fim; d++)
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
                periodo = checkout - checkin;
                preco = calcReserva(quartos, preco_diaria, periodo, num_quarto);
                indexToData(checkin, &dia_in, &mes_in);
                indexToData(checkout, &dia_out, &mes_out);
                printf("Quarto %d\n", num_quarto);
                printf("CPF: %.0lf\n", cpfs[id_cpf]);
                printf("Data de entrada: %d/%d\n", dia_in, mes_in);
                printf("Data de saída: %d/%d\n", dia_out, mes_out);
                printf("Valor pago: R$%.2lf\n\n", preco);
                cont++;
                if (cont>=9) {
                    cont = 0;
                    system("pause");
                }
            }

        }
    }
}



void imprimir_reserva (short reserva[42][181], short quartos[42][2], float preco_diaria[3], double *cpfs, char op)
{
    int id_quarto, id_cpf, checkin, checkout, i, andar, dia_in, mes_in, dia_out, mes_out, num_quarto, d, q, periodo;
    float preco;
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
            printf("\nQuarto: %d\n", num_quarto);
            printf("Andar: %dº\n", andar);
            printf("Quantidade de camas: %d\n\n", quartos[id_quarto][1]);
            printf("-------------------------\n\n");
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
                    periodo = checkout - checkin;
                    preco = calcReserva(quartos, preco_diaria, periodo, num_quarto);
                    printf("CPF: %.0lf\n", cpfs[id_cpf]);
                    printf("Data de entrada: %d/%d\n", dia_in, mes_in);
                    printf("Data de saída: %d/%d\n", dia_out, mes_out);
                    printf("Valor pago: R$%.2lf\n\n", preco);
                }

            }
        break;
        case '2':
            system("cls");
            printf("\n---JANEIRO---\n\n");
            int mes = 1;
            imprimir_mes(preco_diaria, reserva, quartos, cpfs, checkin, dia_in, mes_in, checkout, dia_out, mes_out, num_quarto, id_cpf, mes);
            system("pause");
            system("cls");
            printf("\n---FEVEREIRO---\n\n");
            mes = 2;
            imprimir_mes(preco_diaria, reserva, quartos, cpfs, checkin, dia_in, mes_in, checkout, dia_out, mes_out, num_quarto, id_cpf, mes);
            system("pause");
            system("cls");
            printf("\n---MARÇO---\n\n");
            mes = 3;
            imprimir_mes(preco_diaria, reserva, quartos, cpfs, checkin, dia_in, mes_in, checkout, dia_out, mes_out, num_quarto, id_cpf, mes);
            system("pause");
            system("cls");
            printf("\n---ABRIL---\n\n");
            mes = 4;
            imprimir_mes(preco_diaria, reserva, quartos, cpfs, checkin, dia_in, mes_in, checkout, dia_out, mes_out, num_quarto, id_cpf, mes);
            system("pause");
            system("cls");
            printf("\n---MAIO---\n\n");
            mes = 5;
            imprimir_mes(preco_diaria, reserva, quartos, cpfs, checkin, dia_in, mes_in, checkout, dia_out, mes_out, num_quarto, id_cpf, mes);
            system("pause");
            system("cls");
            printf("\n---JUNHO---\n\n");
            mes = 6;
            imprimir_mes(preco_diaria, reserva, quartos, cpfs, checkin, dia_in, mes_in, checkout, dia_out, mes_out, num_quarto, id_cpf, mes);
	case '3':
            for (i=0; i<42; i++)
            {
                num_quarto = quartos[i][0];
                andar = (int)(num_quarto/100);
                id_quarto = i;
                printf("\nQuarto: %d\n", num_quarto);
                printf("Andar: %dº\n", andar);
                printf("Quantidade de camas: %d\n\n", quartos[id_quarto][1]);
                somatorio = 0;
                for (d=0; d<181; d++)
                {
                    if (reserva[id_quarto][d] != -1)
                    {
                        id_cpf = reserva[id_quarto][d];
                        checkin = d;

                        while (reserva[id_quarto][d] == id_cpf)
                        {
                            d++;
                        }
                        checkout = d;
                        indexToData(checkin, &dia_in, &mes_in);
                        indexToData(checkout, &dia_out, &mes_out);
                        periodo = checkout - checkin;
                        preco = calcReserva(quartos, preco_diaria, periodo, num_quarto);
                        somatorio = somatorio + preco;
                        printf("CPF: %.0lf\n", cpfs[id_cpf]);
                        printf("Data de entrada: %d/%d\n", dia_in, mes_in);
                        printf("Data de saída: %d/%d\n", dia_out, mes_out);
                        printf("Valor pago: R$%.2lf\n\n", preco);
                    }
                }
                printf("Receita do quarto: R$%.2lf\n\n", somatorio);
                system("pause");
            }
    }
}


//printQuartos - Imprime quartos vagos pelo número de cama
int printQuartos (short reserva[42][181], short quartos[42][2], double cpfs[MAX], int camas, int dia_in, int mes_in, int dia_out, int mes_out) {
    int periodo = tempo_reserva(dia_in, mes_in, dia_out, mes_out);
    int q[42], i, d, contq=0, ocup= 0, error = 0 ;
    int id_checkin = dataToIndex(dia_in, mes_in);

    for (i = 0; i<42; i++) {
        q[i] = -1;
    }

    for (i = 0; i<42; i++) {
        if (quartos[i][1] == camas) {
            q[contq] = i;
            contq++;
        }
    }

    for (i =0; i <contq; i++) {
        ocup = 0;
        for (d=0; d<periodo; d++) {
            if (reserva[ q[i] ][id_checkin+d] != -1) {
                ocup = 1;
            }
        }
        if (!ocup) {
            printf("%d\n", quartos[ q[i] ][0]);
            error = 1;
        }
    }

    return error;

}

/*Função que converte número do quarto para seu index equivalente*/
int quartoToIndex (short quartos[42][2], int num_quarto) {
    int i;
    for (i = 0; i<42; i++) {
        if (quartos[i][0] == num_quarto) {
            return i;
        }
    }

    return -1;
}

/*Função que verifica se há ocupação no periodo desejado*/
int verificaOcupacao (short reserva[42][181], int id_quarto, int id_checkin, int periodo) {
    int d;
    for (d=0; d<periodo; d++ ) {
        if (reserva[id_quarto][id_checkin+d] != -1) {
            return 1;
        }
    }

    return 0;
}

/*Função que verifica se o cpf possui alguma reserva cadastrada em outro quarto no mesmo periodo*/
int verificaOcupacaoCpf(short reserva[42][181], int id_checkin, int periodo, int id_cpf) {
    int i,d;
    for (i=0; i<42; i++) {
        for (d=0; d<periodo; d++ ) {
            if (reserva[i][id_checkin+d] == id_cpf) {
                return 1;
            }
        }
    }

    return 0;
}

/*Função para incluir reserva*/
int incluirReserva2 (short reserva[42][181], short quartos[42][2], float preco_diaria[3], double cpfs[MAX], int num_quarto, double bcpf, int dia_in, int mes_in, int dia_out, int mes_out) {
    int i,d, ocup = 0, error;
    int id_quarto = quartoToIndex(quartos, num_quarto);;
    int id_checkin = dataToIndex(dia_in, mes_in);
    int periodo = tempo_reserva(dia_in, mes_in, dia_out, mes_out);
    int id_cpf = criar_id(bcpf, cpfs);


    /*for (i = 0; i<42; i++) {
        if (quartos[i][0] == num_quarto) {
            id_quarto = i;
            break;
        }
    }*/

    /*for (d=0; d<periodo; d++ ) {
        if (reserva[id_quarto][id_checkin+d] != -1) {
            ocup = 1;
            error =2;
            break;
        }
    }*/

    ocup = verificaOcupacao(reserva, id_quarto, id_checkin, periodo);
    if (ocup) {
            error = 2;
    }
    else {
        ocup = verificaOcupacaoCpf(reserva, id_checkin, periodo, id_cpf);
        if (ocup) {error = 3;}
    }


    /*for (i=0; i<42; i++) {
        for (d=0; d<periodo; d++ ) {
            if (reserva[id_quarto][id_checkin+d] == id_cpf) {
                ocup = 1;
                error =3;
                break;
            }
        }
    }*/

    if (!ocup) {
        cpfs[id_cpf] = bcpf;
        for (d=0; d<periodo; d++ ) {
            reserva[id_quarto][id_checkin+d] = id_cpf;
        }
        error = 4;
    }

    return error;
}





#endif // FUNCOES_H_INCLUDED

