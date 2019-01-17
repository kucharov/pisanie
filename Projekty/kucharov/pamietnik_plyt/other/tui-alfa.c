/*
 * untitled.c
 * 
 * Copyright 2018 Konrad Kucharczyk <kucharov@kucharov>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 * 
 * 
 */
// najstarszy element ma najmniejsze ID
// 
// do listy dopisuje z przodu |--------------321

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define K 10000
#define ROZMIAR 20
//popr wyswietlanie
struct Element
   {
   int id;
   char *tytul;
   char *artysta;
   char *gatunek;
   int rok;
   int l_utworow;
   struct Element *nastepny_album;
   };

typedef struct Element * WskaznikNaElement;
typedef enum {FALSZ, PRAWDA} Bool;

/*funkcja dodaje nowy element na poczatek  i jako wynik zwraca wskaznik do niego*/
WskaznikNaElement dodanieNowegoElementu(WskaznikNaElement pierwszy_album, char *, char *, char * , int , int);
/*funcja usuwa pierwszy element dla ktorego przykladowePoleElementu==wartoscPola*/
WskaznikNaElement usuniecieElementu(WskaznikNaElement pierwszy_album, char *);
WskaznikNaElement zwolnieniePamieci(WskaznikNaElement pierwszy_album);
void wyswietlenieElementow(WskaznikNaElement pierwszy_album);
Bool czyListaJestPusta(WskaznikNaElement pierwszy_album);
void wyswietlenieMenuUzytkownika_1(WskaznikNaElement pierwszy_album);
void wyswietlenieMenuUzytkownika_2(void);
void wyswietlenieMenuUzytkownika_3(void);
void wyswietlenieMenuUzytkownika_4(void);
char odczytWyboruMenuUzytkownika(void);
void odczyt_lancucha(char * , char *);
void odczyt_inta(char * , int *);
long int spri(char *, int *);
void edycjaDanych(WskaznikNaElement pierwszy_album, char *, int );
WskaznikNaElement wyszukanieElementu_edycja(WskaznikNaElement pierwszy_album, char *, int );
WskaznikNaElement wyszukanieElementu(WskaznikNaElement pierwszy_album, char *, char *, char *, int , int , int );

int main(void)
	{
	WskaznikNaElement pierwszy_album = NULL;;
	char wybranaOpcjaMenu;
	char temp_tytul[ROZMIAR], temp_artysta[ROZMIAR], temp_gatunek[ROZMIAR], tytul_do_usuniecia[ROZMIAR], zapychacz[ROZMIAR]="stolzpowylamywanymi";
	int temp_rok, temp_l_utworow, szukane_id;
	
	for(;;)
		{
		wyswietlenieMenuUzytkownika_1(pierwszy_album);
		wybranaOpcjaMenu=odczytWyboruMenuUzytkownika();
		switch(wybranaOpcjaMenu)
			 {
				 case 'd': /*dodawanie elementu*/
					odczyt_lancucha("Nazwa albumu: ",temp_tytul);
					odczyt_lancucha("\nArtysta: ",temp_artysta);
					odczyt_lancucha("\nGatunek: ",temp_gatunek);
					odczyt_inta("\nRok wydania albumu: ",&temp_rok);
					odczyt_inta("\nIlosc utworow na plycie: ",&temp_l_utworow);
				   ///developer option 
					pierwszy_album=dodanieNowegoElementu(pierwszy_album, temp_tytul, temp_artysta, temp_gatunek, temp_rok, temp_l_utworow);
					
					break;
				 case 'e': /*edycja elementu*/
					wyswietlenieMenuUzytkownika_2();
					wybranaOpcjaMenu=odczytWyboruMenuUzytkownika();
					switch(wybranaOpcjaMenu)
						{
							case 'i': /*szukanie po id*/
							odczyt_inta("\nPodaj ID plyty do edycji: ",&szukane_id);
							edycjaDanych(pierwszy_album, zapychacz, szukane_id);
							break;
							case 't': /*szukanie po tytule*/
							odczyt_lancucha("\nPodaj tytul plyty do edycji: ",temp_tytul);
							edycjaDanych(pierwszy_album, temp_tytul, K);
							break;
							case 'b': /*szukanie po tytule*/
							break;
						}														
				 case 'w': /*wyswietlanie wszystkich elementow*/
					wyswietlenieElementow(pierwszy_album);
					break;
				 case 's': /* wyszukanie elementu/elementow po polu*/
					wyswietlenieMenuUzytkownika_4();
					wybranaOpcjaMenu=odczytWyboruMenuUzytkownika();
					switch(wybranaOpcjaMenu)
						{
							
							case 't': /*szukanie po tytule*/
							odczyt_lancucha("\nPodaj tytul plyty do wszukania: ",temp_tytul);
							printf("\nOto plyta o tytule \"%s\"\n", temp_tytul);
							wyszukanieElementu(pierwszy_album, temp_tytul, zapychacz, zapychacz, K, K, K);
							break;
							case 'a': /*szukanie po artyscie*/
							odczyt_lancucha("\nPodaj artyste, ktorego plyte/plyty chcesz wyszukac: ",temp_artysta);
							printf("\nOto wszystkie plyty artysty \"%s\"\n", temp_artysta);
							wyszukanieElementu(pierwszy_album, zapychacz, temp_artysta, zapychacz, K, K, K);
							break;
							case 'g': /*szukanie po gatunku*/
							odczyt_lancucha("\nPodaj gatunek wedlug ktorego chcesz wyszukac plyte/plyty: ",temp_gatunek);
							printf("\nOto wszystkie plyty z gatunku \"%s\"\n", temp_artysta);
							wyszukanieElementu(pierwszy_album, zapychacz, zapychacz, temp_gatunek, K, K, K);
							break;
							case 'r': /*szukanie po roku*/
							odczyt_inta("\nPodaj rok wydania wedlug ktorego chcesz wyszukac plyte/plyty: ",&temp_rok);
							printf("\nOto wszystkie plyty wydane w roku \"%d\"\n", temp_rok);
							wyszukanieElementu(pierwszy_album, zapychacz, zapychacz, zapychacz, temp_rok, K, K);
							break;
							case 'l': /*szukanie po l_utworow*/
							odczyt_inta("\nPodaj liczbe utworow wedlug ktorej chcesz wyszukac plyte/plyty: ",&temp_l_utworow);
							printf("\nOto wszystkie plyty artysty: \"%d\"\n", temp_l_utworow);
							wyszukanieElementu(pierwszy_album, zapychacz, zapychacz, zapychacz, K, temp_l_utworow, K);
							break;
							case 'i': /*szukanie po id*/
							odczyt_inta("\nPodaj id plyty ktora chcesz wyswietlic: ",&szukane_id);
							printf("\nOto plyta o ID nr \"%d\"\n", szukane_id);
							wyszukanieElementu(pierwszy_album, zapychacz, zapychacz, zapychacz, K, K, szukane_id);
							break;
							case 'b': /*meniu*/
							
							break;
							default:
							puts("\nBledny wybor opcji menu!");
						}	
					break;
				 case 'u': /*usuwanie elementu o zadanej wartosci pola: przykladowePoleElementu*/
					odczyt_lancucha("\nWprowadz tytul albumu, ktory chcesz usunac z listy: ",tytul_do_usuniecia);
					pierwszy_album=usuniecieElementu(pierwszy_album,tytul_do_usuniecia);
					break;
				 case 'q':
					if (pierwszy_album!=NULL) pierwszy_album=zwolnieniePamieci(pierwszy_album);
					exit(0);
					break;
				 default:
					puts("\nBledny wybor opcji menu!");
			 }
			 
		}
	return 0;
	}
	
WskaznikNaElement dodanieNowegoElementu(WskaznikNaElement pierwszy_album, char *t, char *a, char *g, int r, int l)
   {
    WskaznikNaElement nowyElement= (WskaznikNaElement)malloc( sizeof(struct Element) );
    static int licznik_id=0;
    if(nowyElement==NULL)
       {
       fputs("Blad alokacji pamieci",stderr);
       exit(1);
       }
    nowyElement->id=1+licznik_id++;
    nowyElement->tytul=(char *)malloc( ROZMIAR*sizeof(char) );
    nowyElement->artysta=(char *)malloc( ROZMIAR*sizeof(char) );
    nowyElement->gatunek=(char *)malloc( ROZMIAR*sizeof(char) );
    strncpy(nowyElement->tytul,t,ROZMIAR*sizeof(*t));
    strncpy(nowyElement->artysta,a,ROZMIAR*sizeof(*a));
    strncpy(nowyElement->gatunek,g,ROZMIAR*sizeof(*g));
    nowyElement->rok=r;
    nowyElement->l_utworow=l;
    nowyElement->nastepny_album = pierwszy_album;
    return nowyElement;
   }

void wyswietlenieElementow(WskaznikNaElement pierwszy_album)
   {
	WskaznikNaElement biezacy_album=pierwszy_album;
	unsigned licznikElementow=1;
	while(biezacy_album != NULL)
    	{
		printf("%d.\nTytul: %s\n",licznikElementow++, biezacy_album->tytul );
		printf("Artysta: %s\n", biezacy_album->artysta );
		printf("Gatunek: %s\n", biezacy_album->gatunek );
		printf("Rok wydania: %d\n",biezacy_album->rok );
		printf("Liczba utworow na plycie: %d\n\n", biezacy_album->l_utworow );
		printf("ID: %d\n\n",biezacy_album->id);
		biezacy_album = biezacy_album->nastepny_album;
    	}
   }

WskaznikNaElement usuniecieElementu(WskaznikNaElement pierwszy_album, char *tytul_do_usuniecia)
   {
	WskaznikNaElement biezacy_album=pierwszy_album, poprzedniElement=NULL;
	char tymczasowy_artysta[ROZMIAR];
	do
		{
		
        if( !strcmp(biezacy_album->tytul,tytul_do_usuniecia))
        	{
        	if(biezacy_album==pierwszy_album) pierwszy_album = biezacy_album->nastepny_album;
        	else poprzedniElement->nastepny_album = biezacy_album->nastepny_album;
        	strncpy(tymczasowy_artysta,biezacy_album->artysta,sizeof(*biezacy_album->artysta));
        	free(biezacy_album->artysta);
        	free(biezacy_album->gatunek);
        	free(biezacy_album->tytul);
        	free(biezacy_album);
        	return pierwszy_album;
        	}
        poprzedniElement = biezacy_album;
        biezacy_album = biezacy_album->nastepny_album;
		} while(biezacy_album != NULL);
	printf("Usunięto album %s artysty %s\n", tytul_do_usuniecia, tymczasowy_artysta  );
	
	return pierwszy_album;
   }

WskaznikNaElement zwolnieniePamieci(WskaznikNaElement pierwszy_album)
   {
   WskaznikNaElement biezacy_album=pierwszy_album, tymczasowyWskaznik;
   do
      {
      tymczasowyWskaznik = biezacy_album;
      biezacy_album = biezacy_album->nastepny_album;
      free(tymczasowyWskaznik->artysta);
      free(tymczasowyWskaznik->gatunek);
      free(tymczasowyWskaznik->tytul);
      free(tymczasowyWskaznik);
      }
   while(biezacy_album != NULL);
   return NULL;
   }

Bool czyListaJestPusta(WskaznikNaElement pierwszy_album)
	{
	if (pierwszy_album == NULL) return PRAWDA;
	else return FALSZ;
	}

void wyswietlenieMenuUzytkownika_1(WskaznikNaElement pierwszy_album)
	{
	 printf("\nProsze wybrać opcje:");
	 printf("\n\t'd'- dodanie nowej plyty ");
	 if (!czyListaJestPusta(pierwszy_album))
	 	 {
		 printf("\n\t'e'- edycja plyt ");
		 printf("\n\t'w'- wyswietlenie wszystkich plyt ");
		 printf("\n\t's'- szukanie plyty ");
		 printf("\n\t'u'- usuniecie plyty ,");
		 }
     printf("\n\t'q'- wyjscie z programu");
     printf("\n\t >");
	}
void wyswietlenieMenuUzytkownika_2(void)
	{
	 printf("\nWyszukiwanie płyty:");
	 
	 printf("\n\t't'- znajdz plyte wpisujac jej tytul ");
     printf("\n\t'i'- znajdz plyte wpisujac jej ID ");
     printf("\n\t'b'- powrot do menu glownego");
     printf("\n\t >");
	}
void wyswietlenieMenuUzytkownika_3(void)
	{
	 printf("\nWybierz co zamierzasz edytowac:");
	 printf("\n\t't'- edycja tytulu");
	 printf("\n\t'a'- edycja artysty");
     printf("\n\t'g'- edycja gatunku");
     printf("\n\t'r'- edycja roku wydania");
     printf("\n\t'l'- edycja liczby utworow");
     printf("\n\t'b'- powrot do menu glownego");
     printf("\n\t >");
	}

void wyswietlenieMenuUzytkownika_4(void)
	{
	 printf("\nWybierz według jakiego pola chcialbys wyszukac plyte/plyty:");
	 printf("\n\t't'- wedlug tytulu");
	 printf("\n\t'a'- wedlug artysty");
     printf("\n\t'g'- wedlug gatunku");
     printf("\n\t'r'- wedlug roku wydania");
     printf("\n\t'l'- wedlug liczby utworow");
     printf("\n\t'b'- powrot do menu glownego");
     printf("\n\t >");
	}
char odczytWyboruMenuUzytkownika(void)
	{
	char znak, wybranaOpcja[2];
	fgets(wybranaOpcja,2,stdin);
	while((znak=getchar())!='\n');
	return wybranaOpcja[0];
	}



void odczyt_lancucha(char * tekstKomunikatu, char * lancuch)
	{
	char buforDlaDanych[ROZMIAR];
	int n=0;
	printf("%s",tekstKomunikatu);
	fgets(buforDlaDanych,ROZMIAR,stdin);
	n=strlen(buforDlaDanych);
	buforDlaDanych[n-1]='\0';
	strncpy(lancuch,buforDlaDanych,sizeof(buforDlaDanych));	
	}
	

void odczyt_inta(char * tekstKomunikatu, int * adres_inta)
	{
	int powtorz_input=1;
	char input[ROZMIAR];
		do
			{	
				
				printf("%s",tekstKomunikatu);
				fgets(input, 15, stdin);
				*adres_inta=spri(input, &powtorz_input);
				
			}
		while(powtorz_input!=0);
	
	}
	
long int spri(char *str, int* powtorz_input)
	{
		char *reszta_ze_str={"\0"}, odp1[15], smietnik;
		int wartosc_wlasciwa;
		wartosc_wlasciwa = strtol(str, &reszta_ze_str, 10);
		*str=wartosc_wlasciwa;
				if (strlen(reszta_ze_str)>1)
					{
						while(odp1[0]!='t')
							{
								printf("Czy chciales podac wartosc %d? (wpisz tak/nie)\n", wartosc_wlasciwa);
								fgets(odp1, 4, stdin);
								
								if (odp1[0]=='t' && odp1[1]=='a')
									{
										*powtorz_input=0;
										while((smietnik=getchar())!='\n');
										
									}
								else if (odp1[0]=='n' && odp1[1]=='i' ) 
									{
										odp1[0]='t';
										*powtorz_input=1;
										while((smietnik=getchar())!='\n');
										
									}	
							}
					}
				else if (wartosc_wlasciwa==0)
					{
						
						*powtorz_input=1;
						
						
					}
				else 
					{
						*powtorz_input=0;
						
					}
		return (wartosc_wlasciwa);
	}
	
void edycjaDanych(WskaznikNaElement pierwszy_album, char *tytul_do_wyszukania, int id_do_wyszukania)
	{
		WskaznikNaElement plyta_edytowana=NULL;
		int nowa_dana_int;
		char wybranaOpcjaMenu;
		
		if	(wyszukanieElementu_edycja(pierwszy_album, tytul_do_wyszukania, id_do_wyszukania)!=NULL)
			{	
				
			plyta_edytowana=wyszukanieElementu_edycja(pierwszy_album, tytul_do_wyszukania, id_do_wyszukania);
			wyswietlenieMenuUzytkownika_3();
			wybranaOpcjaMenu=odczytWyboruMenuUzytkownika();
			switch(wybranaOpcjaMenu)
						 {
						 case 't': /*edycja tytulu*/
							odczyt_lancucha("Podaj nowy tytul: ", tytul_do_wyszukania );
							strncpy(plyta_edytowana->tytul,tytul_do_wyszukania,ROZMIAR*sizeof(*tytul_do_wyszukania));
    
							break;
						 case 'a': /*edycja artysty*/
							odczyt_lancucha("Podaj nowego artyste: ",tytul_do_wyszukania);
							strncpy(plyta_edytowana->artysta,tytul_do_wyszukania,ROZMIAR*sizeof(*tytul_do_wyszukania));
   
							break;
						 case 'g': /*edycja gatunku*/
							odczyt_lancucha("Podaj nowy gatunek: ", tytul_do_wyszukania);
							 strncpy(plyta_edytowana->gatunek,tytul_do_wyszukania,ROZMIAR*sizeof(*tytul_do_wyszukania));
    
							break;
						 case 'r': /*edycja roku wydania*/
							odczyt_inta("Podaj nowy rok wydania plyty: ", &nowa_dana_int);
							plyta_edytowana->rok=nowa_dana_int;
    
							break;
						 case 'l': /*edycja liczby utworow*/
							odczyt_inta("Podaj nowa liczbe utworow na plycie", &nowa_dana_int);
							plyta_edytowana->l_utworow=nowa_dana_int;
							break;
						 case 'b': /*powrot do menu glownego*/	
							break;
						 default:
							puts("\nBledny wybor opcji menu!");
						 }
					 
			}
		else printf("\nNie ma takiego albumu!\n\n");
	}
	
WskaznikNaElement wyszukanieElementu_edycja(WskaznikNaElement pierwszy_album, char *tytul_do_wyszukania, int id_do_wyszukania)				 
	{
		WskaznikNaElement biezacy_album=pierwszy_album, poprzedniElement=NULL;
		
		do
			{
			
			if( !strcmp(biezacy_album->tytul,tytul_do_wyszukania)) ////WYSZUKANIE PO TYTULE
				{
				
				return biezacy_album;
				}
			else if (biezacy_album->id==id_do_wyszukania) ////WYSZUKANIE PO ID
				{
				
				return biezacy_album;
				}
			poprzedniElement = biezacy_album;
			biezacy_album = biezacy_album->nastepny_album;
			} while(biezacy_album != NULL);
		return NULL;
	}

WskaznikNaElement wyszukanieElementu(WskaznikNaElement pierwszy_album, char *tytul_do_wyszukania, char *artysta_do_wyszukania, char *gatunek_do_wyszukania, int rok_do_wyszukania, int l_utworow_do_wyszukania, int id_do_wyszukania)				 
	{
		WskaznikNaElement biezacy_album=pierwszy_album, poprzedniElement=NULL;
		
		do
			{
			
			if( !strcmp(biezacy_album->tytul,tytul_do_wyszukania)) ////WYSZUKANIE PO TYTULE
				{
				
				
				printf("\nTytul: %s\n", biezacy_album->tytul );
				printf("Artysta: %s\n", biezacy_album->artysta );
				printf("Gatunek: %s\n", biezacy_album->gatunek );
				printf("Rok wydania: %d\n",biezacy_album->rok );
				printf("Liczba utworow na plycie: %d\n\n", biezacy_album->l_utworow );
				printf("ID: %d\n\n",biezacy_album->id);
				
    	
				
				}
			else if ( !strcmp(biezacy_album->artysta,artysta_do_wyszukania)) ////WYSZUKANIE PO ARTYSCIE
				{
				printf("\nTytul: %s\n", biezacy_album->tytul );
				printf("Artysta: %s\n", biezacy_album->artysta );
				printf("Gatunek: %s\n", biezacy_album->gatunek );
				printf("Rok wydania: %d\n",biezacy_album->rok );
				printf("Liczba utworow na plycie: %d\n\n", biezacy_album->l_utworow );
				printf("ID: %d\n\n",biezacy_album->id);
				
				}
			else if ( !strcmp(biezacy_album->gatunek,gatunek_do_wyszukania)) ////WYSZUKANIE PO GATUNKU
				{
				printf("\nTytul: %s\n", biezacy_album->tytul );
				printf("Artysta: %s\n", biezacy_album->artysta );
				printf("Gatunek: %s\n", biezacy_album->gatunek );
				printf("Rok wydania: %d\n",biezacy_album->rok );
				printf("Liczba utworow na plycie: %d\n\n", biezacy_album->l_utworow );
				printf("ID: %d\n\n",biezacy_album->id);
				
				}
			else if (biezacy_album->rok==rok_do_wyszukania) ////WYSZUKANIE PO ROKU WYDANIA
				{
				printf("\nTytul: %s\n", biezacy_album->tytul );
				printf("Artysta: %s\n", biezacy_album->artysta );
				printf("Gatunek: %s\n", biezacy_album->gatunek );
				printf("Rok wydania: %d\n",biezacy_album->rok );
				printf("Liczba utworow na plycie: %d\n\n", biezacy_album->l_utworow );
				printf("ID: %d\n\n",biezacy_album->id);
				
				}
			else if (biezacy_album->l_utworow==l_utworow_do_wyszukania) ////WYSZUKANIE PO L_UTWOROW
				{
				printf("\nTytul: %s\n", biezacy_album->tytul );
				printf("Artysta: %s\n", biezacy_album->artysta );
				printf("Gatunek: %s\n", biezacy_album->gatunek );
				printf("Rok wydania: %d\n",biezacy_album->rok );
				printf("Liczba utworow na plycie: %d\n\n", biezacy_album->l_utworow );
				printf("ID: %d\n\n",biezacy_album->id);
				
				}
			else if (biezacy_album->id==id_do_wyszukania) ////WYSZUKANIE PO ID
				{
				printf("\nTytul: %s\n", biezacy_album->tytul );
				printf("Artysta: %s\n", biezacy_album->artysta );
				printf("Gatunek: %s\n", biezacy_album->gatunek );
				printf("Rok wydania: %d\n",biezacy_album->rok );
				printf("Liczba utworow na plycie: %d\n\n", biezacy_album->l_utworow );
				printf("ID: %d\n\n",biezacy_album->id);
				
				}
			poprzedniElement = biezacy_album;
			biezacy_album = biezacy_album->nastepny_album;
			} while(biezacy_album != NULL);
		return NULL;
	}
