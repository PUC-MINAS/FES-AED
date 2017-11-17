#ifndef FUNCOES_H_INCLUDED
#define FUNCOES_H_INCLUDED

/*estrutura de data - usado para conversão de data juliana para gregoriana*/
struct date {
   int dia;
   int mes;
};
typedef struct date data;

void indexToData (int index, int *dia, int *mes) {
    data juliana_to_gregoriana (int juliana);
    int datainicial = gregoriana_to_juliana(1,1,2018);
    int juli = datainicial + index;
    data dt;
    //dt =  juliana_to_gregoriana(juli);
    *dia = dt.dia;
    *mes = dt.mes;
}


int dataToIndex (int dia, int mes) {
    int juli = gregoriana_to_juliana(dia, mes, 2018);
    return juli - (gregoriana_to_juliana(1,1,2018));
}
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

/*int incluir_reserva (short reserva[42][181], short quartos [42][2], float preco_diaria[3], num_quarto, bcpf,dia_in,mes_in,dia_out,mes_out);
{
int  ini_vet=dataToIndex(dia_in,mes_in);
int tam_vet=tempo_reserva(dia_in,mes_in,dia_out,mes_out);
int i;

    for(i=0;i<100;i++)
    {



    }





    }*/

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
