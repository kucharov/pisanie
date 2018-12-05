//zadanie 2 

#include <stdlib.h>
#include <stdio.h>
#define A 10
#define B 10

void generuj_dane(double [A][B], int, int);
void zapisz_do_pliku_text(char *, double[A][B], int, int);
void zapisz_do_pliku_bin(char *, double [A][B], int, int);
void wyswietl(double [A][B], int, int);

int main(void)
{
	double DANE [A][B] = {'\n'};
	char nazwat[20];
	char nazwab[20];
	printf("nazwa pliku tekstowego??\n");
	gets(nazwat);
	printf("\nnazwa pliku binarnego??\n");
	gets(nazwab);
	generuj_dane(DANE, A, B);
	zapisz_do_pliku_text(nazwat, DANE, A, B);
	zapisz_do_pliku_bin(nazwab, DANE, A, B);
	wyswietl(DANE, A, B);
	return 0;
}

void generuj_dane(double tab[A][B], int wiersze, int kolumny)
{
	int a, b;
	double c = 1;
	for (a=0;a<wiersze;a++) for (b=0;b<kolumny;b++, c++) tab[a][b] = c;
}

void zapisz_do_pliku_text(char *nazwapliku, double tab[A][B], int wiersze, int kolumny)
{
	FILE *plik;
	int a,b;
	plik = fopen(nazwapliku, "w");
	for (a=0;a<wiersze;a++) for (b=0;b<kolumny;b++) 
	{
		fprintf(plik, "%lf\t", tab[a][b]);
		if (b==kolumny-1) fprintf(plik, "\n");
	}
	fclose(plik);
}

void zapisz_do_pliku_bin(char *nazwapliku, double tab[A][B], int wiersze, int kolumny)
{
	FILE *plik;
	int a,b;
	plik = fopen(nazwapliku, "wb");
	for (a=0;a<wiersze;a++) for (b=0;b<kolumny;b++) 
	{
		fprintf(plik, "%lf\t", tab[a][b]);
		if (b==kolumny-1) fprintf(plik, "\n");
	}
	fclose(plik); 
}

void wyswietl(double tab[A][B], int wiersze, int kolumny)
{
	int a,b;
	for (a=0;a<wiersze;a++) for (b=0;b<kolumny;b++)
	{
		printf("%lf\t", tab[a][b]);
		if (b==kolumny-1) printf("\n");
	}
}


	 
		
	
	

	
	

 
