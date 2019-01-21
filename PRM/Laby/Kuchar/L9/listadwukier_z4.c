

/* lista.c - M. Niewinski for PRM 2018L */
/* kod kompilowany i dzialajacy na systemie Linux*/
#include <stdio.h>
#include <stdlib.h>

#define ROZMIAR 80

struct ElementListy
   {
   int przykladowePoleElementu;
   struct ElementListy *nastepnyElementListy;
   struct ElementListy *poprzedniElementListy;
   };

typedef struct ElementListy * WskaznikNaElementListy;
typedef enum {FALSZ, PRAWDA} Bool;

/*funkcja dodaje nowy element na poczatek listy i jako wynik zwraca wskaznik do niego*/
WskaznikNaElementListy dodanieNowegoElementuListy_na_poczatku(WskaznikNaElementListy pierwszyElementListy, int wartoscPola);
/*funkcja dodaje nowy element na koniec listy i jako wynik zwraca wskaznik do niego*/
WskaznikNaElementListy dodanieNowegoElementuListy_na_koncu(WskaznikNaElementListy ostatniElementListy, WskaznikNaElementListy pierwszyElementListy, int wartoscPola);
/*funcja usuwa pierwszy element dla ktorego przykladowePoleElementu==wartoscPola*/
WskaznikNaElementListy usuniecieElementuListy(WskaznikNaElementListy pierwszyElementListy, int wartoscPola);
WskaznikNaElementListy zwolnieniePamieciListy(WskaznikNaElementListy pierwszyElementListy);
void wyswietlenieElementowListy(WskaznikNaElementListy pierwszyElementListy);
Bool czyListaJestPusta(WskaznikNaElementListy pierwszyElementListy);
void wyswietlenieMenuUzytkownika(WskaznikNaElementListy pierwszyElementListy);
char odczytWyboruMenuUzytkownika(void);
Bool odczytDanychOdUzytkownika(char * tekstKomunikatu, int * wskaznikDoDanych);

int main(void)
	{
	WskaznikNaElementListy pierwszyElementListy = NULL, ostatniElementListy = NULL;
	char wybranaOpcjaMenu;
	int tymczasowaWartosc;
	for(;;)
		{
		wyswietlenieMenuUzytkownika(pierwszyElementListy);
		wybranaOpcjaMenu=odczytWyboruMenuUzytkownika();
		switch(wybranaOpcjaMenu)
			 {
			 case 'd': /*dodawanie elementu*/
				if (odczytDanychOdUzytkownika("\nPodaj wartosc pola dana - typu int:", &tymczasowaWartosc ))
					 pierwszyElementListy=dodanieNowegoElementuListy_na_poczatku(pierwszyElementListy,tymczasowaWartosc );
			    break;
			 case 'k': /*dodawanie elementu na koniec*/
				if (odczytDanychOdUzytkownika("\nPodaj wartosc pola dana - typu int:", &tymczasowaWartosc ))
					 ostatniElementListy=dodanieNowegoElementuListy_na_koncu(ostatniElementListy, pierwszyElementListy, tymczasowaWartosc );
			    break; 
			 case 'w': /*wyswietlanie elementow*/
			    wyswietlenieElementowListy(pierwszyElementListy);
			    break;
			 case 'u': /*usuwanie elementu o zadanej wartosci pola: przykladowePoleElementu*/
				if (odczytDanychOdUzytkownika("\nWprowadz wartosc pola elementu do usuniecia - typu int: ", &tymczasowaWartosc ))
					 pierwszyElementListy=usuniecieElementuListy(pierwszyElementListy,tymczasowaWartosc);
				break;
			 case 'q':
				pierwszyElementListy=zwolnieniePamieciListy(pierwszyElementListy);
			    exit(0);
			    break;
			 default:
			    puts("\nBledny wybor opcji menu!");
			 }
		}
	return 0;
	}

WskaznikNaElementListy dodanieNowegoElementuListy_na_poczatku(WskaznikNaElementListy pierwszyElementListy, int wartoscPola)
   {
   WskaznikNaElementListy nowyElementListy= (WskaznikNaElementListy)malloc( sizeof(struct ElementListy) );
   if(nowyElementListy==NULL)
      {
      fputs("Blad alokacji pamieci",stderr);
      exit(1);
      }
   nowyElementListy->przykladowePoleElementu=wartoscPola;
   if (pierwszyElementListy!= NULL) pierwszyElementListy->poprzedniElementListy=nowyElementListy;
   nowyElementListy->nastepnyElementListy = pierwszyElementListy;
   
   return nowyElementListy;
   }

WskaznikNaElementListy dodanieNowegoElementuListy_na_koncu(WskaznikNaElementListy ostatniElementListy,WskaznikNaElementListy pierwszyElementListy, int wartoscPola)
   {
   WskaznikNaElementListy biezacyElementListy=pierwszyElementListy;
   WskaznikNaElementListy nowyElementListy= (WskaznikNaElementListy)malloc( sizeof(struct ElementListy) );
   if(nowyElementListy==NULL)
      {
      fputs("Blad alokacji pamieci",stderr);
      exit(1);
      }
   
   nowyElementListy->przykladowePoleElementu=wartoscPola;
   
   if (ostatniElementListy == NULL)
	{
		if (pierwszyElementListy != NULL)
			{
				while(biezacyElementListy->nastepnyElementListy != NULL)
					{
						biezacyElementListy = biezacyElementListy->nastepnyElementListy;
					}
				biezacyElementListy->nastepnyElementListy = nowyElementListy;	
				nowyElementListy->poprzedniElementListy = biezacyElementListy;
			}
		
	}
   
   
   else if (ostatniElementListy!= NULL) 
	{
		ostatniElementListy->nastepnyElementListy=nowyElementListy;
		nowyElementListy->poprzedniElementListy = ostatniElementListy;
	}
	
   return nowyElementListy;
   }

void wyswietlenieElementowListy(WskaznikNaElementListy pierwszyElementListy)
   {
	WskaznikNaElementListy biezacyElementListy=pierwszyElementListy;
	unsigned licznikElementow=1;
	while(biezacyElementListy != NULL)
    	{
		printf("Element %d Dane: %d\n",licznikElementow++, biezacyElementListy->przykladowePoleElementu );
		biezacyElementListy = biezacyElementListy->nastepnyElementListy;
    	}
   }

WskaznikNaElementListy usuniecieElementuListy(WskaznikNaElementListy pierwszyElementListy, int wartoscPola)
   {
	WskaznikNaElementListy biezacyElementListy=pierwszyElementListy, poprzedniElementListy=NULL;
	do
		{
        if( biezacyElementListy->przykladowePoleElementu==wartoscPola)
        	{
        	if(biezacyElementListy==pierwszyElementListy) pierwszyElementListy = biezacyElementListy->nastepnyElementListy;
        	else poprzedniElementListy->nastepnyElementListy = biezacyElementListy->nastepnyElementListy;
        	free(biezacyElementListy);
        	return pierwszyElementListy;
        	}
        poprzedniElementListy = biezacyElementListy;
        biezacyElementListy = biezacyElementListy->nastepnyElementListy;
		} while(biezacyElementListy != NULL);
	printf("Elementu z polem o zadanej wartosci nie ma na liscie\n");
	printf("Dostępne elementy to:\n");
	wyswietlenieElementowListy(pierwszyElementListy);
	return pierwszyElementListy;
   }

WskaznikNaElementListy zwolnieniePamieciListy(WskaznikNaElementListy pierwszyElementListy)
   {
   WskaznikNaElementListy biezacyElementListy=pierwszyElementListy, tymczasowyWskaznik;
   while(biezacyElementListy != NULL)
      {
      tymczasowyWskaznik = biezacyElementListy;
      biezacyElementListy = biezacyElementListy->nastepnyElementListy;
      free(tymczasowyWskaznik);
      }
   return NULL;
   }

Bool czyListaJestPusta(WskaznikNaElementListy pierwszyElementListy)
	{
	if (pierwszyElementListy == NULL) return PRAWDA;
	else return FALSZ;
	}

void wyswietlenieMenuUzytkownika(WskaznikNaElementListy pierwszyElementListy)
	{
	 printf("Prosze wybrać opcje:\n");
	 printf("\n\t'd'- dodanie nowego elementu na poczatku listy");
	 printf("\n\t'k'- dodanie nowego elementu na koncu listy");
	 if (!czyListaJestPusta(pierwszyElementListy))
	 	 {
		 printf("\n\t'w'- wyswietlenie wszystkich elementow listy");
		 printf("\n\t'u'- usuniecie elementu z listy,");
		 }
     printf("\n\t'q'- wyjscie z programu");
     printf("\n\t >");
	}

char odczytWyboruMenuUzytkownika(void)
	{
	char znak, wybranaOpcja[2];
	fgets(wybranaOpcja,2,stdin);
	while((znak=getchar())!='\n');
	return wybranaOpcja[0];
	}

Bool odczytDanychOdUzytkownika(char * tekstKomunikatu, int * wskaznikDoDanych)
	{
	char buforDlaDanych[ROZMIAR];
	int wynikKonwersji;
	printf("%s",tekstKomunikatu);
	fgets(buforDlaDanych,ROZMIAR,stdin);
	wynikKonwersji=sscanf(buforDlaDanych,"%d",wskaznikDoDanych);
	if (wynikKonwersji==EOF) return FALSZ;
	else return PRAWDA;
	}

