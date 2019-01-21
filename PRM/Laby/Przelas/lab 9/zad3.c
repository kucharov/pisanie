//zad3.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
int wiersze, kolumny, a, b, **tabelka, **nowatabelka;


printf("\nWiersze?:  ");
scanf("%d", &wiersze);
while (getchar()!='\n')
;
printf("\nKolumny?:  ");
scanf("%d", &kolumny);

//alokacja i wypelnienie tabeli

tabelka = calloc(wiersze, sizeof(int *));

for(a=0;a<wiersze;a++)
{
	tabelka[a] = calloc(kolumny, sizeof(int));
	for(b=0;b<kolumny;b++) *(*(tabelka+a)+b) = rand()%101;
}

//wyswietlenie

for(a=0;a<wiersze;a++){ if (a==0)printf("\t\t\t    TABELA:\n"); for(b=0;b<kolumny;b++)
{
	if (b==0) printf("\n");
	printf("%d\t", *(*(tabelka+a)+b));
}}

printf("\n\n");

//realokacja


nowatabelka = realloc(tabelka, ((wiersze+2)*sizeof(int *)));

for(a=0;a<wiersze;a++) nowatabelka[a] = realloc(nowatabelka[a], ((kolumny + 3)*sizeof(int)));
for(a=wiersze;a<(wiersze+2);a++) nowatabelka[a] = calloc((kolumny + 3),sizeof(int));
for(a=0;a<wiersze;a++) for(b=kolumny;b<(kolumny+3);b++) *(*(nowatabelka + a)+b) = rand()%101;
for(a=wiersze;a<(wiersze+2);a++) for(b=0;b<(kolumny+3);b++) *(*(nowatabelka + a)+b) = rand()%101;


//nowa tabelka

for(a=0;a<(wiersze+2);a++){ if (a==0)printf("\t\t\t   NOWA TABELA:\n"); for(b=0;b<(kolumny+3);b++)
{
	if (b==0) printf("\n");
	printf("%d\t", *(*(nowatabelka+a)+b));
}}

return 0;
}
