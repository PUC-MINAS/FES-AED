#ifndef FUNCOES_H_INCLUDED
#define FUNCOES_H_INCLUDED

/*estrutura de data - usado para conversão de data juliana para gregoriana*/
struct date {
   int dia;
   int mes;
};
typedef struct date data;

/*Função que converte index para data*/
void indexToData (int index, int *dia, int *mes) {
    data juliana_to_gregoriana (int juliana);
    int datainicial = gregoriana_to_juliana(1,1,2018);
    int juli = datainicial + index;
    data dt;
    dt =  juliana_to_gregoriana(juli);
    *dia = dt.dia;
    *mes = dt.mes;
}

/*função que converte data para index*/
int dataToIndex (int dia, int mes) {
    int juli = gregoriana_to_juliana(dia, mes, 2018);
    return juli - (gregoriana_to_juliana(1,1,2018));
}

/*função que retorna periodo de dias*/
int tempo_reserva (int dia_in,int mes_in,int dia_out,int mes_out) {
    int juli = gregoriana_to_juliana(dia_in, mes_in, 2018);
    return juli - (gregoriana_to_juliana(dia_out,mes_out,2018));
}





/*Funcao que lê um cpf e valida*/
double readCpf () {
    double cpf;
    printf("Digite o seu cpf: ");
    scanf("%lf", &cpf);
    while (!valida_cpf(cpf)) {
        printf("\n###CPF inválido!###\n\n");
        printf("Digite o seu cpf: ");
        scanf("%lf", &cpf);
    }
    return cpf;
}

/*Função que lê dia e mês digitado pelo usuário e faz validação*/
void readData (int *dia, int *mes) {
    scanf("%d/%d", dia, mes);
    while (!validaData(*dia, *mes, 2018) || *mes >6) {
        printf("\n###Data inválida!###\n\n");
        printf("Data de entrada (dia/mes): ");
        scanf("%d/%d", dia, mes);
    }
}

/*funcao que ler número de quartos digitado pelo usuário*/
int readNumQuarto (short quartos [42][2]) {
    int num_quarto;
    printf("Digite o número do quarto: ");
    scanf("%d", &num_quarto);
    while (!validaNumQuarto(num_quarto, quartos)) {
        printf("\n###Número de quarto inválido!###\n\n");
        printf("Digite o número do quarto: ");
        scanf("%d", &num_quarto);
    }
    return num_quarto;
}

/*funcao que ler número de camas digitado pelo usuário*/
int readNumCamas (void){
    int camas;
    printf("Número de camas desejado? ");
    scanf("%d", &camas);
    while ( camas < 1 || camas > 3 ){
        printf("\n###Número de camas inválido!###\n\n");
        printf("Número de camas desejado? ");
        scanf("%d", &camas);
    }
    return camas;
}

/*Função que valida número do quarto*/
int validaNumQuarto (int num, short quartos[42][2]) {
    int i;

    for (i = 0; i < 42; i++) {
        if (num == quartos[i][0]) {
            return 1;
        }
    }
    return 0;
}

/*Função para validação de data*/
int validaData(int dia, int mes, int ano){
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

void cpfDoubleToInt (double *pcpfs, int *pcpf, int *pdig) {
    double cpfs = *pcpfs;
    int cpf = *pcpf;
    int dig = *pdig;
    cpf = (int)(cpfs/100);//  printf("---TesteFuncao---\n");  printf("CPFS = %f\n", cpfs); printf("CPF = %d\n", cpf); printf("CPFS - CPF = %d\n", (int)(cpfs - (double)cpf*100) );
    dig = (int)(cpfs - (double)cpf*100);// printf("Dig = %d\n", dig );
    *pcpf = cpf;
    *pdig = dig;
}

void cpfIntToDouble (double *cpfs, int *cpf, int *dig){
    //cpfs[1] = (double)cpf*100 + dig;
    *cpfs = (double)*cpf*100 + *dig;
}

/*Funcao que trabalha junto com a valida_CPF*/
int soma_cpf (int cpf, int dig) {
    int c, peso, soma, i;
    i = 1;
    peso = 2;
    soma = 0;
    if (dig < 0) {
        while ( i <= 9) {
            c = cpf % 10;
            soma = soma + c*peso;
            cpf = (int)(cpf/10);
            i++;
            peso++;
        }
    }
    else {
        cpf = cpf*10 + dig;
        while ( i <= 10) {
            c = cpf % 10;
            soma = soma + c*peso;
            cpf = (int)(cpf/10);
            i++;
            peso++;
        }
    }
    return soma;
}

/*Funcao para validar CPF*/
int valida_cpf (double cpfs) {
    //printf("\n---Funcao valida_cpf---");
    int cpf, cpf_dig;
    cpfDoubleToInt(&cpfs, &cpf, &cpf_dig);
    int somatorio, dig1, dig2, r, dig;
    //printf("\nCPF_dig: %d", cpf_dig);
    //printf("\nCPF: %d", cpf);
    somatorio = soma_cpf(cpf, -1); //printf("\nsomatorio: %d", somatorio);
    dig1 = 11 - (somatorio % 11); //printf("\ndig1: %d", dig1);
    if (dig1 > 9) {
        dig1 = 0; //printf("\ndig1: %d", dig1);
    }
    somatorio = soma_cpf(cpf , dig1); //printf("\nsomatorio: %d", somatorio);
    dig2 = 11 - (somatorio % 11); //printf("\ndig2: %d", dig2);
    if (dig2 > 9) {
        dig2 = 0; //printf("\ndig2: %d", dig2);
    }
    dig = (dig1*10) + dig2; //printf("\ndig: %d", dig);
    if (cpf_dig == dig) {
        r = 1;
    }
    else {
        r = 0;
    }
    //printf("\ncpf_dig: %d, dig: %d", cpf_dig, dig);
    return r;
}

/*juliana_to_gregoriana ()*/
/*converte data juliana em gregoriana*/
data juliana_to_gregoriana (int juliana) {
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
int gregoriana_to_juliana (int dia, int mes, int ano) {
	int juliana;
	juliana = (1461*(ano + 4800 + (mes -14)/12))/4 +
	          (367*(mes - 2 - 12 *((mes -14)/12)))/12 -
	          ( 3 * ((ano+ 4900 + (mes -14)/12)/100))/4 +
	          dia - 32075 ;

    return juliana ;
}

int inicializa_dados  (short reserva[42][181],short quartos [42][2],float preco_diaria[3])
{
    int a,q;
    for(a=0;a<3;a++)
    {
        printf("Defina os valores do quarto para %d cama(s): ",a+1);
        scanf("%f", &preco_diaria[a]);
    }

}
int criar_id(double bcpf, double cpfs[5000])
{
    int i;
    int id_cpf;

    if(localizar_id(bcpf,cpfs[5000])==-1)
    {
        for(i=0; i<5000; i++)
        {
            if(cpfs[i]==-1)
            {
                cpfs[i]=bcpf;
                id_cpf=i;
                break;
            }


        }


    }


return id_cpf;
}


int localizar_id( double bcpf,double cpfs[5000])
{
    int i=0;
    int id=-1;
    for(i=0; i<5000;i++)
    {
        if(cpfs[i]==-1)
        {
            break;

        }
        if(bcpf=cpfs[i])
        {
            id=i;
            break;
        }

    }
    return id;

}

int localiza_quarto_vago(int quarto_aux[14],int camas,short reserva[42][181],short quartos [42][2],int vaga_quartos[42],int dia_in,int mes_in,int dia_out,int mes_out)
{
    int vaga, ini_vetor=dataToIndex(dia_in,mes_in);
    int final_vetor=dataToIndex(dia_out,mes_out)+1;
    int tam_vet=tempo_reserva(dia_in,mes_in,dia_out,mes_out);
    int j,i,aux=0,i_vaga=0;
    for(i=0; i<28; i++)
    {
        quarto_aux[i]=-1;
    };


    for(i=0; i<42; i++)
    {

        if(quartos[i][1]== camas)
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

 int localiza_quarto_reserva(int quarto_aux[28],int camas,short reserva[42][181],short quartos [42][2],int vaga_quartos[42],int dia_in,int mes_in,int dia_out,int mes_out){
  int i,i_vaga,j,vaga,ini_vetor=dataToIndex(dia_in,mes_in);
    int final_vetor=dataToIndex(dia_out,mes_out)+1;
    int tam_vet=tempo_reserva(dia_in,mes_in,dia_out,mes_out);
 int aux=0;
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
                printf("disponivel quarto n° %d  preco %d \n",vaga_quartos[i],preco_diaria[camas-1]);
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
                printf("disponivel quarto n° %d  preco %d \n",vaga_quartos[quarto_aux[i]],preco_diaria[quartos[quarto_aux[i]][1]-1]);
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
        printf("opcao invalida... [S]im ou [N]ão ");
		val=0;
		}


  }while(val=0);



}












    int ImprimirReserva (int numquarto, short reserva[42][181], short quartos[42][2], float precodiaria[3], double *cpfs )
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
