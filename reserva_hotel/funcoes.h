#ifndef FUNCOES_H_INCLUDED
#define FUNCOES_H_INCLUDED

/*estrutura de data - usado para conversão de data juliana para gregoriana*/
struct date {
   int dia;
   int mes;
};
typedef struct date data;

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

int incluir_cadastro()
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

        do{
        printf("informe o cpf para a reservar");
        scanf("%d-%d",&cpf,&dgf);

        }while(valida_cpf(cpf));









        return 0;





    }



























#endif // FUNCOES_H_INCLUDED
