#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// zadanie 1 
#define A 5
#define B 80



int wczytaj(char *nazwa_pliku,char [][B], int Ra, int Rb);

void wyswietl(char [][B], int Ra, int Rb);

int main(void)
{
char imiepliku [15];
scanf("%s", imiepliku);
	char TEKST [A][B] = {'\n'};
	wczytaj(imiepliku, TEKST, A, B);
	wyswietl(TEKST, A, B);
	return 0;
}

int wczytaj(char *nazwa_pliku, char t[][B], int Ra, int Rb)
{
FILE *plik;
if (plik == NULL) return -1;
plik = fopen(nazwa_pliku, "r");
int i,j;
char znak;
int wiersz = 0;

for(i=0;i<Ra; i++)
for (j = 0 ; j<Rb; j++)
 {znak = getc(plik); if (znak == '\n') wiersz ++; else t[i][j] = znak; 
	 if (wiersz==5) break;
 }
 fclose(plik);
 return 0;
}
 
void wyswietl(char t[][B], int Ra, int Rb)
{
int i,j;
for(i=0;i<Ra;i++) for (j=0;j<Rb;j++)
{printf("%c\t", t[i][j]); if (j==Rb-1) printf("\n");}
}
	
	
	
	









