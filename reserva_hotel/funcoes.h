#ifndef FUNCOES_H_INCLUDED
#define FUNCOES_H_INCLUDED

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
int valida_cpf (int cpf, int cpf_dig) {
    printf("\n---Funcao valida_cpf---");
    int somatorio, dig1, dig2, r, dig;
    printf("\nCPF_dig: %d", cpf_dig);
    printf("\nCPF: %d", cpf);
    somatorio = soma_cpf(cpf, -1); printf("\nsomatorio: %d", somatorio);
    dig1 = 11 - (somatorio % 11); printf("\ndig1: %d", dig1);
    if (dig1 > 9) {
        dig1 = 0; printf("\ndig1: %d", dig1);
    }
    somatorio = soma_cpf(cpf , dig1); printf("\nsomatorio: %d", somatorio);
    dig2 = 11 - (somatorio % 11); printf("\ndig2: %d", dig2);
    if (dig2 > 9) {
        dig2 = 0; printf("\ndig2: %d", dig2);
    }
    dig = (dig1*10) + dig2; printf("\ndig: %d", dig);
    if (cpf_dig == dig) {
        r = 1;
    }
    else {
        r = 0;
    }
    printf("\ncpf_dig: %d, dig: %d", cpf_dig, dig);
    return r;
}

/*juliana_to_gregoriana ()*/
/*converte data juliana em gregoriana*/
long int juliana_to_gregoriana (int juliana) {
	int b, n, k, j, dia, mes, ano;
	long int data;
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
	data = (ano * 10000) + (mes * 100) + dia;
	return data;
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

#endif // FUNCOES_H_INCLUDED
