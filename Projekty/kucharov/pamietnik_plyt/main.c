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
// najstarszy element jest ostatnim elementem na liscie.
// do listy dopisuje z przodu |--------------321
///PROBLEM PRZY QUIT GDY NIE MA PLYT
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ROZMIAR 20

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
WskaznikNaElement dodanieNowegoElementu(WskaznikNaElement pierwszy_album, char *, char *, char * , int , int , int * );
/*funcja usuwa pierwszy element dla ktorego przykladowePoleElementu==wartoscPola*/
WskaznikNaElement usuniecieElementu(WskaznikNaElement pierwszy_album, char *);
WskaznikNaElement zwolnieniePamieci(WskaznikNaElement pierwszy_album);
void wyswietlenieElementow(WskaznikNaElement pierwszy_album);
Bool czyListaJestPusta(WskaznikNaElement pierwszy_album);
void wyswietlenieMenuUzytkownika(WskaznikNaElement pierwszy_album);
char odczytWyboruMenuUzytkownika(void);
void odczyt_lancucha(char * tekstKomunikatu, char *);
void odczyt_inta(char * tekstKomunikatu, int *);
long int spri(char *, int *);
int main(void)
	{
	WskaznikNaElement pierwszy_album = NULL;
	char wybranaOpcjaMenu, temp_tytul[ROZMIAR], temp_artysta[ROZMIAR], temp_gatunek[ROZMIAR], tytul_do_usuniecia[ROZMIAR];
	int temp_rok, temp_l_utworow, licznik_id=1;
	for(;;)
		{
		wyswietlenieMenuUzytkownika(pierwszy_album);
		wybranaOpcjaMenu=odczytWyboruMenuUzytkownika();
		switch(wybranaOpcjaMenu)
			 {
			 case 'd': /*dodawanie elementu*/
				odczyt_lancucha("Nazwa albumu: ",temp_tytul);
				odczyt_lancucha("\nArtysta: ",temp_artysta);
				odczyt_lancucha("\nGatunek: ",temp_gatunek);
				odczyt_inta("\nRok wydania albumu: ",&temp_rok);
				odczyt_inta("\nIlosc utworow na plycie: ",&temp_l_utworow);
				//while((smietnik=getchar())!='\n');
				pierwszy_album=dodanieNowegoElementu(pierwszy_album, temp_tytul, temp_artysta, temp_gatunek, temp_rok, temp_l_utworow, &licznik_id);
				
			    break;
			 case 'w': /*wyswietlanie elementow*/
			    wyswietlenieElementow(pierwszy_album);
			    break;
			 case 'u': /*usuwanie elementu o zadanej wartosci pola: przykladowePoleElementu*/
				odczyt_lancucha("\nWprowadz tytul albumu, ktory chcesz usunac z listy: ",tytul_do_usuniecia);
				pierwszy_album=usuniecieElementu(pierwszy_album,tytul_do_usuniecia);
				break;
			 case 'q':
				pierwszy_album=zwolnieniePamieci(pierwszy_album);
			    exit(0);
			    break;
			 default:
			    puts("\nBledny wybor opcji menu!");
			 }
			 
		}
	return 0;
	}
	
WskaznikNaElement dodanieNowegoElementu(WskaznikNaElement pierwszy_album, char *t, char *a, char *g, int r, int l, int *licznik_id)
   {
    WskaznikNaElement nowyElement= (WskaznikNaElement)malloc( sizeof(struct Element) );
    if(nowyElement==NULL)
       {
       fputs("Blad alokacji pamieci",stderr);
       exit(1);
       }
    nowyElement->id=*licznik_id++;
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
		printf("%d.\nAlbum: %s\n",licznikElementow++, biezacy_album->tytul );
		printf("Artysta: %s\n", biezacy_album->artysta );
		printf("Gatunek: %s\n", biezacy_album->gatunek );
		printf("Rok wydania: %d\n",biezacy_album->rok );
		printf("Liczba utworow na plycie: %d\n", biezacy_album->l_utworow );
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

void wyswietlenieMenuUzytkownika(WskaznikNaElement pierwszy_album)
	{
	 printf("Prosze wybrać opcje:\n");
	 printf("\n\t'd'- dodanie nowej plyty ");
	 if (!czyListaJestPusta(pierwszy_album))
	 	 {
		 printf("\n\t'w'- wyswietlenie wszystkich plyt ");
		 printf("\n\t'u'- usuniecie plyty ,");
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



void odczyt_lancucha(char * tekstKomunikatu, char * lancuch)
	{
	char buforDlaDanych[ROZMIAR];
	int n=0;
	printf("%s\n",tekstKomunikatu);
	fgets(buforDlaDanych,ROZMIAR,stdin);
	n=strlen(buforDlaDanych);
	//printf("%d\n",n);
	buforDlaDanych[n-1]='\0';
	//printf("przed %s\n",buforDlaDanych);
	strncpy(lancuch,buforDlaDanych,sizeof(buforDlaDanych));
	//printf("po %s\n",lancuch);
	}
	
//test ten odczyt jak nie to funkcja z sinusa
void odczyt_inta(char * tekstKomunikatu, int * adres_inta)
	{
	int powtorz_input=1;
	char input[ROZMIAR];
/*	int n=0;
	printf("%s",tekstKomunikatu);
	while(n!=1) n=scanf("%d",adres_inta);
*/	do
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
