#ifndef CPFB_H_INCLUDED
#define CPFB_H_INCLUDED

/*Funcao que lê um cpf e valida*/
double readCpf ()
{
    double cpf;
    printf("Digite o seu cpf: ");
    scanf("%lf", &cpf);
    while (!valida_cpf(cpf))
    {
        printf("\n###CPF inválido!###\n\n");
        printf("Digite o seu cpf: ");
        scanf("%lf", &cpf);
    }
    return cpf;
}


void cpfDoubleToInt (double *pcpfs, int *pcpf, int *pdig)
{
    double cpfs = *pcpfs;
    int cpf = *pcpf;
    int dig = *pdig;
    cpf = (int)(cpfs/100);//  printf("---TesteFuncao---\n");  printf("CPFS = %f\n", cpfs); printf("CPF = %d\n", cpf); printf("CPFS - CPF = %d\n", (int)(cpfs - (double)cpf*100) );
    dig = (int)(cpfs - (double)cpf*100);// printf("Dig = %d\n", dig );
    *pcpf = cpf;
    *pdig = dig;
}

void cpfIntToDouble (double *cpfs, int *cpf, int *dig)
{
    //cpfs[1] = (double)cpf*100 + dig;
    *cpfs = (double)*cpf*100 + *dig;
}


/*Funcao que trabalha junto com a valida_CPF*/
int soma_cpf (int cpf, int dig)
{
    int c, peso, soma, i;
    i = 1;
    peso = 2;
    soma = 0;
    if (dig < 0)
    {
        while ( i <= 9)
        {
            c = cpf % 10;
            soma = soma + c*peso;
            cpf = (int)(cpf/10);
            i++;
            peso++;
        }
    }
    else
    {
        cpf = cpf*10 + dig;
        while ( i <= 10)
        {
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
int valida_cpf (double cpfs)
{
    //printf("\n---Funcao valida_cpf---");
    int cpf, cpf_dig;
    cpfDoubleToInt(&cpfs, &cpf, &cpf_dig);
    int somatorio, dig1, dig2, r, dig;
    //printf("\nCPF_dig: %d", cpf_dig);
    //printf("\nCPF: %d", cpf);
    somatorio = soma_cpf(cpf, -1); //printf("\nsomatorio: %d", somatorio);
    dig1 = 11 - (somatorio % 11); //printf("\ndig1: %d", dig1);
    if (dig1 > 9)
    {
        dig1 = 0; //printf("\ndig1: %d", dig1);
    }
    somatorio = soma_cpf(cpf, dig1);  //printf("\nsomatorio: %d", somatorio);
    dig2 = 11 - (somatorio % 11); //printf("\ndig2: %d", dig2);
    if (dig2 > 9)
    {
        dig2 = 0; //printf("\ndig2: %d", dig2);
    }
    dig = (dig1*10) + dig2; //printf("\ndig: %d", dig);
    if (cpf_dig == dig)
    {
        r = 1;
    }
    else
    {
        r = 0;
    }
    //printf("\ncpf_dig: %d, dig: %d", cpf_dig, dig);
    return r;
}


int geracpf1()
{
        int numero[9],soma1,soma2,i,erro,cpf,quant;
        int parte1,parte2,parte3,dig1;
        int parte5,parte6,parte7,dig2;
        //*==========================================*
        //|        Geração dos numeros do CPF        |
        //*==========================================*
            for(i=1;i<= 9;i++)
            {
               erro=1;
               do
               {
                  if(erro>1)
                  {
                     printf("Numero invalido.\n");
                     erro=1;
                  }
                  numero[i]=rand()%9;
                  erro++;
               }while(numero[i]>9 || numero[i]<0);
            }
            //*==========================================*
            //|       Primeiro digito veridicador        |
            //*==========================================*
            soma1=((numero[1]*10)+
                  (numero[2]*9)+
                  (numero[3]*8)+
                  (numero[4]*7)+
                  (numero[5]*6)+
                  (numero[6]*5)+
                  (numero[7]*4)+
                  (numero[8]*3)+
                  (numero[9]*2));
            parte1=(soma1 / 11);
            parte2=(parte1 * 11);
            parte3=(soma1 - parte2);
            dig1=(11 - parte3);
            if(dig1>9)dig1=0;
            //*==========================================*
            //|        Segundo digito veridicador        |
            //*==========================================*
            soma2=((numero[1]*11)+
                  (numero[2]*10)+
                  (numero[3]*9)+
                  (numero[4]*8)+
                  (numero[5]*7)+
                  (numero[6]*6)+
                  (numero[7]*5)+
                  (numero[8]*4)+
                  (numero[9]*3)+
                  (dig1*2));
            parte5=(soma2 / 11);
            parte6=(parte5 * 11);
            parte7=(soma2 - parte6);
            dig2=(11 - parte7);
            if(dig2>9)dig2=0;
            //*==========================================*
            //|       Impressao do numero completo       |
            //*==========================================*
            double cpfnovo;
            for(i=1;i<=9;i++)
            {
               printf("%d",numero[i]);
               cpfnovo=cpfnovo*10+numero[i];
               printf("%11.0lf\n",cpfnovo);
            }
            printf("%d%d\n",dig1,dig2); //dois últimos digitos
            cpfnovo=cpfnovo*10+dig1;
            cpfnovo=cpfnovo*10+dig2;
            //printf("%.0lf",cpfnovo);
            return cpfnovo;
}


/*
int digito1(int vetor[9])
{
    int soma,dig1,i,a,aux,resto;
    a=10;
    soma=0;
    for (i = 0; i < 9; i++);
    {
        aux=vetor[i]*a;
        soma=soma+aux;
        a--;
    }
    resto=soma%11;
    if (resto<2)
    {
        dig1=0;
    }
    else
    {
        dig1=11-resto;
    }
    return dig1;

}

int digito2(int vetor[9],int digit1)
{
    int soma,dig2,i,a,aux,resto;
    a=11;
    soma=digit1*2;
    for (i = 0; i < 9; i++);
    {
        aux=vetor[i]*a;
        soma=soma+aux;
        a--;
    }
    resto=soma%11;
    if(resto<2)
    {
        dig2=0;

    }
    else
    {
        dig2=11-resto;
    }
    return dig2;

}

//gerador cpf:lebana
int geradorcpf()
{
    int i,vetor[9],digit1,digit2;
    for (i=0; i<9; i++)
    {
        //scanf("%d",&vetor[i]);
        vetor[i]=rand()%10;
    }
    digit1=digito1(vetor);
    digit2=digito2(vetor,digit1);
    unsigned long int newcpf;
    newcpf=0;
    //transforma vetor em variavel simples
    for (i=0; i<9;  i++)
    {
        newcpf=(newcpf*10)+vetor[i];
    }
    printf("%11d nodig\n",newcpf);
    newcpf=(newcpf*10)+digit1;
    printf("%11d 1dig\n",newcpf);
    newcpf=(newcpf*10)+digit2;
    printf("%11d 2dig\n",newcpf);

    system("pause");
    return newcpf;

}


// Função Geradora de CPF
int cpf_generator()
{
    int *cpf, pesos[11], vetSoma[11], soma, resto, digito,  i;

    // Aloca memória para o cpf
    cpf = (int *) malloc(sizeof(int) * 11);

    // Gera 9 números aleatórios
    for(i = 0; i < 9; i++)
    {
        cpf[i] = rand() % 10;
    }

    // Cálculo do primeiro dígito verificador

    // Gera os 9 pesos
    for(i = 0; i < 9; i++)
    {
        pesos[i] = 10 - i;
    }

    // Multiplica os valores de cada coluna
    for(i = 0; i < 9; i++)
    {
        vetSoma[i] = cpf[i] * pesos[i];
    }

    // Calcula o somatório dos resultados
    soma = 0;
    for(i = 0; i < 9; i++)
    {
        soma += vetSoma[i];
    }

    // Realiza-se a divisão inteira do resultado por 11
    resto = soma % 11;

    // Verifica o resto da divisão
    if(resto < 2)
    {
        digito = 0;
    }
    else
    {
        digito = 11 - resto;
    }

    // Adiciona o 1º dígito verificador ao cpf
    cpf[9] = digito;

    // Cálculo do segundo dígito verificador

    // Gera os 10 pesos
    for(i = 0; i < 10; i++)
    {
        pesos[i] = 11 - i;
    }

    // Multiplica os valores de cada coluna
    for(i = 0; i < 10; i++)
    {
        vetSoma[i] = cpf[i] * pesos[i];
    }

    // Calcula o somatório dos resultados
    soma = 0;
    for(i = 0; i < 10; i++)
    {
        soma += vetSoma[i];
    }

    // Realiza-se a divisão inteira do resultado por 11
    resto = soma % 11;

    // Verifica o resto da divisão
    if(resto < 2)
    {
        digito = 0;
    }
    else
    {
        digito = 11 - resto;
    }

    // Adiciona o 2º dígito verificador ao cpf
    cpf[10] = digito;

    return cpf;
}


// Função main
// Main geradora de cpf
int geracpf(int argc, char** argv)
{
    int *cpf, i, aux;
    double newcpf;
// Inicia o gerador de números aleatórios
    srand(time(NULL));

// Gera um cpf aleatório
    cpf = cpf_generator();
    newcpf=cpf[0];
    aux=10;

// Imprime o cpf gerado na tela
    for(i = 0; i < 11; i++)
    {
        newcpf=(newcpf*aux)+cpf[i];
    }

// Libera a memória usada para o cpf
    free(cpf);
    return newcpf;
}
*/

double gera_cpf3(){

    int i ;
    double newcpf = 0.00;
    int cpf=0, cpf_dig, somatorio, dig1, dig2;
    //randomisa 9 digitos
    for (i= 0; i<9; i++) {
        cpf = (cpf*10) + (rand() % 10);
    }

    somatorio = soma_cpf(cpf, -1);
    dig1 = 11 - (somatorio % 11); //printf("\ndig1: %d", dig1);
    if (dig1 > 9)
    {
        dig1 = 0; //printf("\ndig1: %d", dig1);
    }

    somatorio = soma_cpf(cpf, dig1);  //printf("\nsomatorio: %d", somatorio);
    dig2 = 11 - (somatorio % 11); //printf("\ndig2: %d", dig2);

    if (dig2 > 9)
    {
        dig2 = 0; //printf("\ndig2: %d", dig2);
    }

    cpf_dig = (dig1*10) + dig2;
    cpfIntToDouble(&newcpf, &cpf, &cpf_dig);

    if (valida_cpf(newcpf)) {
        return newcpf;
    }
    else {return -1;}
}






/*
int cpf_generator(char cpf[11])
{
    int i, j, dig = 0;
    srand(time(NULL));
    for(i = 0; i <= 9; i++){
        cpf[i] = (rand() % 10) + 48;}
    for(i = 0, j = 10; i <= strlen(cpf)-2; i++, j--){
        dig += (cpf[i]-48) * j;}
    dig %= 11;
    if(dig < 2){
        cpf[9] = 48;}
    else{
        cpf[9] = (11-dig)+48;}
    dig = 0;
    for(i = 0, j = 11; i <= strlen(cpf)-1; i++, j--)
    {
        dig += (cpf[i]-48) * j;
    }
    dig %= 11;
    if(dig < 2){
        cpf[10] = 48;}
    else{
        cpf[10] = (11-dig)+48;}
}

int gerandocpf()
{
    char cpf[11];
    int i;
    unsigned long int newcpf;
    cpf_generator(cpf);
    printf("\n");
    for(i = 0; i < 11; i++)
    {
        printf("%c", cpf[i]);
    }
    //transforma vetor em variavel simples
    for (i=0; i<11;  i++)
    {
        newcpf=(newcpf*10)+cpf[i];
    }
    printf("\n");
    system("pause");
    return newcpf;
}
*/

#endif // CPFB_H_INCLUDED
