// zadanie 1 z labek 9 !!

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct osoba 
	{
		char * imie;
		char * nazwisko;
	};
int main(void)

{	
struct osoba *ws_osoba;
ws_osoba = malloc(sizeof(struct osoba));
ws_osoba->imie = malloc(21*sizeof(char));
ws_osoba->nazwisko = malloc(26*sizeof(char));

printf("Podaj imie   ");
scanf("%s", ws_osoba -> imie);
printf("/nPodaj nazwisko:  ");
scanf("%s", ws_osoba->nazwisko);

printf("\n\n\t\t\tAdresy\tws_osoba: %p\nimie: %p\nnazwisko: %p\n\n\t\tZawartosc:\n\
		ws_osoba:\nimie: %s\nnazwisko: %s\n", &ws_osoba, &ws_osoba->imie, &ws_osoba->nazwisko, 
		ws_osoba->imie, ws_osoba->nazwisko);
		
free(ws_osoba);
free(ws_osoba->imie);
free(ws_osoba->nazwisko);

return 0;
}
		















