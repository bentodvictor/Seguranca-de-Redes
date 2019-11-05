//=============================================================================
//======================	Victor Dallagnol Bento	===========================
//======================	Segurança de Rede		===========================
//======================	Decifra					===========================
//=============================================================================



#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//===============================	Globais		===================================
unsigned char key[4];			// Chave
unsigned char input[256];		// Entrada
unsigned char *result_;			// Resultado
unsigned char s[256];			
unsigned char t[256];			
unsigned int i, j, len_input;
unsigned int len_key = 4;
FILE *fp;				// Criação de um arquivo para armazenar resultados

//===============================	Troca		===================================
//	Troca os valores entre s[i] e Ss[j]
void swap()
{
	unsigned char aux;
	aux = s[i];
	s[i] = s[j];
	s[j] = aux;
}


//===============================	Permuta		===================================
//	Permuta o valor de S apontado por i com j e armazena o resultado em j
void permut()
{
	j = 0;
	for (i = 0; i < 256; ++i)
	{
		j = (j + s[i] + t[i]) % 256;
		swap();
	}
	i = 0;
	j = 0;
}


//===============================	Inicia		===================================
//	A função init incrementa em 1 a variável i e o valor de t(chave) apontado por i 
void init()
{
	for (i = 0; i < 256; ++i)
	{	
		s[i] = i;
		t[i] = key[i % len_key];
	}
	permut();
}


//===============================	Stream		===================================
//	A saída é então calculada fazendo-se a operação XOR entre o valor de s apontado por s[i] + s[j] e 
//	a mensagem original apontado por aux
void stream()
{
	unsigned int aux;
	unsigned char result[len_input - 1]; 	// Resultado do mesmo tamanho da mensagem
	for (aux = 0; aux < len_input; ++aux)
	{
		i = (i+1) % 256;
   		j = (j + s[i]) % 256;
   		swap(); 
   		result[aux]=(s[(s[i] + s[j]) % 256]) ^ input[aux];	// Operação de XOR
  }
	result_= (unsigned char*) malloc((len_input - 1)*(sizeof(unsigned char)));
	strcpy(result_, result);
	
	//	Busca strings que tenham ponto final como ultimo caractere e letras como caracteres que compoem a string, 
	// 	as letras podem ser maiusculas ou minusculas
	//	salva posteriormente no arquivo Results
	if (result[len_input - 1] == '.')
	{	
		if ((result[0] >= 65 && result[0] <= 90) || result[0] >= 97 && result[0] <= 122)		//	primeiro caractere
			if ((result[1] >= 65 && result[1] <= 90) || result[1] >= 97 && result[1] <= 122)	// 	segundo caractere
				if ((result[len_input-2] >= 65 && result[len_input-2] <= 90) || result[len_input-2] >= 97 && result[len_input-2] <= 122)	//	penúltimo caractere
					if ((result[len_input-3] >= 65 && result[len_input-3] <= 90) || result[len_input-3] >= 97 && result[len_input-3] <= 122)	//	antepenúltimo caractere
						fprintf(fp, "->\t%s\tChave: %s\n", result, key);
	}
}


//===============================	find_Key		===================================
void find_key()
{
	for (int a = 65; a <= 90; ++a)
	{
		key[0] = (char)a;
		for (int b = 65; b <= 90; ++b)
		{
			key[1] = (char)b;
			for (int c = 65; c <= 90; ++c)
			{
				key[2] = (char)c;
				for (int d = 65; d <= 90; ++d)
				{
					key[3] = (char)d;
					init();
					stream();
				}
			}
		}
	}
}





//===============================	Principal		===================================
void main(int argc, char const *argv[])
{
	// para loop "for"
    int i;

    // entrada em hexa
    char hex[] = "A3B1E7428957C942EC959C4F5DE56A7947F6CE18";
    int sizeHex = strlen(hex);

    // variaveis de conveniencia
    char ch, high, low;

    // trata todos os caracteres da entrada
    // Conversão de HEXA para STRING através da tabela ASCII
    for (i = 0; i < sizeHex; i += 2)
    {
       high = hex[i];
       high -= 0x30;
       if (high > 9) high -= 7;
       high <<= 4;

       low = hex[i+1];
       low -= 0x30;
       if (low > 9) low -= 7;

       ch = high | low;

       // transfere para saida            
       input[i/2] = ch;
    }
    printf("<!> input in hexa: %s\n", hex);
	printf("<!> hexa to string: %s\n", input);
	len_input = strlen(input);	// Salva tamanho da mensagem

    fp = fopen ("Results.txt", "w");
	find_key();
	fclose(fp);

}
