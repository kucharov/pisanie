//zadanie 1, tym razem samodzielnie, umiem to zrobić sam !
#include <stdlib.h>
#include <stdio.h>

struct osoba 
{
	char *imie;
	char *nazwisko;
};

int main(void)
{
struct osoba *ws_osoba;
ws_osoba = (struct osoba *)malloc(sizeof(struct osoba));
ws_osoba->imie = (char *)malloc(25*sizeof(char));
ws_osoba->nazwisko = (char *)malloc(30*sizeof(char));

printf("\nImie?:  ");
scanf("%s", ws_osoba->imie);
while(getchar() != '\n');
printf("\nDzieki, a nazwisko?:   ");
scanf("%s", ws_osoba->nazwisko);

printf("\nAdresy: \nws_osoba\t%p\nws_osoba->imie\t%p\nws_osoba->nazwisko\t%p\nZawartosc:\nws_osoba->imie\t%s\nws_osoba->nazwisko\t%s", &ws_osoba, &ws_osoba->imie, &ws_osoba->nazwisko, ws_osoba->imie, ws_osoba->nazwisko);

free(ws_osoba);
return 0;

	
	
	
	}
