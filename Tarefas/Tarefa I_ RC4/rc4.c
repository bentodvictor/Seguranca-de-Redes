#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//==================================================
unsigned char chave[256];
unsigned char entrada[256];
unsigned char *resultado;
unsigned char s[256];
unsigned int i, j, tamanho_chave, tamanho_entrada;
//==================================================
void troca()
{
unsigned char aux;
aux=s[i];
s[i]=s[j];
s[j]=aux;
}

//====================================================

void ksa ()
{
 for (i = 0; i < 256; i++)
{
     s[i]=i;
} 
  j=0;
 for (i = 0; i < 256; i++)
   {
   j = (j + s[i] + chave[i % tamanho_chave]) % 256;
   troca(s, i, j);
   }
 i=0;
 j=0;
}

//====================================================

void prga ()
{ 
unsigned int aux;
unsigned char result[tamanho_entrada-1];
for (aux=0; aux < tamanho_entrada; aux++)
  {
   i = (i + 1) % 256;
   j = (j + s[i]) % 256;
   troca(s,i,j);
 result[aux]=(s[(s[i] + s[j]) % 256])^entrada[aux];
  }
resultado=(unsigned char*)malloc((tamanho_entrada-1)*(sizeof(unsigned char)));
strcpy(resultado, result);
}

//====================================================

int main ()
{
unsigned char confirma[256];
int confirm;
printf ("Escreva a Frase a ser Criptografada:");
scanf ("%s", entrada);
tamanho_entrada=strlen(entrada);
printf ("\nChave:");
scanf ("%s", chave);
tamanho_chave=strlen(chave);
ksa ();
prga ();
printf ("\nResultado Gerado: %s\n", resultado);
printf ("\n\nPara Desfazer, confirme a chave: ");
TENTA: scanf ("%s", confirma);
confirm=strcmp(confirma, chave); 
if (confirm==0)
 { 
 printf ("\nDesfazendo....\n");
 strcpy(entrada, resultado);
 ksa();
 prga ();
 printf ("\nFrase Original: %s\n", resultado);
 }
else
  {
  printf ("Chave nao confere, por favor insira a chave correta:\n");
  goto TENTA;
  }
return 0;
}
