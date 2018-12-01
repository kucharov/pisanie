#include <stdio.h>
#include <stdlib.h>
void wyswietl(char tab[5][80]);
int wczytaj(char *nazwa_pliku, char tab[5][80]);

int main(void)
{
	char TEKST [5][80] = {'\n'};
	
	
	
	
	
	
	wczytaj(dupa.txt, TEKST);
	wyswietl(TEKST);
	return 0;
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
}

int wczytaj(char *nazwa_pliku, char tab[5][80])
{
FILE *plik;
plik = fopen("nazwa_pliku", "r");
if (plik == NULL) return -1;
int y;
char c;
for(y=0; (c = getc(plik)) != '\n' && y<6; y++) tab[y] = c;
return 0;
}

void wyswietl(char tab[5][80])
{
	int a, b;
	for (a=0; a<5; a++) {
		for(b=0; b<80; b++) {printf("%c\t", *tab[a][b]); if (b==4) printf("\n");}
		
}
		
	
	


	
	
	
	
	
	
	
} 
