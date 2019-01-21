#include <stdlib.h>
#include <stdio.h>
#define A 10
#define B 10

void wczytaj_z_pliku_bin(char *, double[A][B], int, int);
void wczytaj_z_pliku_text(char *, double[A][B], int, int);
void wyswietl(double[A][B], int, int);

int main(void)
{
char nazwat[20], nazwab[20];
double DANE[A][B];
printf("nazwa pliku tekstowego?");
gets(nazwat);
printf("nazwa pliku binarnego?");
gets(nazwab);
wczytaj_z_pliku_bin(nazwab, DANE, A, B);
wyswietl(DANE, A, B);
wczytaj_z_pliku_text(nazwat, DANE, A, B);
wyswietl(DANE, A, B);
return 0;
}

void wczytaj_z_pliku_bin(char *nazwapliku, double tab[A][B], int wiersze, int kolumny)
{
	FILE *plik;
	plik = fopen(nazwapliku, "rb");
	int a,b;
	for(a=0;a<wiersze;a++) for(b=0;b<kolumny;b++)
	{
		fscanf(plik, "%lf", &tab[a][b]);
		
		
	}
	fclose(plik);
}

void wczytaj_z_pliku_text(char *nazwapliku, double tab[A][B], int wiersze, int kolumny)
{
	FILE *plik;
	plik = fopen(nazwapliku, "r");
	int a,b;
	for(a=0;a<wiersze;a++) for(b=0;b<kolumny;b++)
	{
		fscanf(plik, "%lf", &tab[a][b]);
			
	}
	fclose(plik);
}

void wyswietl(double tab[A][B], int wiersze, int kolumny)
{
	int a,b;
	for(a=0;a<wiersze;a++) for(b=0;b<kolumny;b++)
	{
		printf("%lf\t", tab[a][b]);
		if (b==kolumny-1) printf("\n");
	}
}
	
	
	

