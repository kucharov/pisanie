#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cdk.h>
#include <form.h>
#include <unistd.h>
#define N 6
#define B 100
#define C 1000
#define K 10000
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



int forma_dodawanie_elementu(char *, char *, char *, int *, int *);
int forma_edycja_elementu(char *, char *, char *, int *, int *);
void menu(CDKSCREEN *,WINDOW *, int *);
WskaznikNaElement dodanie_nowego_elementu(WskaznikNaElement pierwszy_album, char *, char *, char * , int  , int );
WskaznikNaElement usuniecie_elementu(WskaznikNaElement pierwszy_album, char *);
WskaznikNaElement zwolnienie_pamieci(WskaznikNaElement pierwszy_album);
int wyswietlenie_calosci(CDKSCREEN *, WskaznikNaElement pierwszy_album);
int wyswietlenie_wyszukania(CDKSCREEN *,WskaznikNaElement pierwszy_album,int);
void edycja_danych(WskaznikNaElement pierwszy_album, char *, int );
WskaznikNaElement wyszukanie_elementu_edycja(WskaznikNaElement pierwszy_album, char *, int );
WskaznikNaElement wyszukanie_elementu(WskaznikNaElement pierwszy_album, char *, char *, char *, int , int , int, WINDOW * );
char *pobor_danych (CDKSCREEN *,const char *,char *temp);
int dialog_1 (CDKSCREEN *,int , char **, int *);
int dialog_2 (CDKSCREEN *,int , char **, int *);
int dialog_3 (CDKSCREEN *,int , char **, int *);
int dialog_4 (CDKSCREEN *,int , char **, int *);
char *trim(char *);
char *wybor_pliku (CDKSCREEN *ekran,char *);
WskaznikNaElement wczytanie_do_struktury(WskaznikNaElement ,char *);
int zapis_do_pliku(WskaznikNaElement );
int sortowanie(CDKSCREEN *,WskaznikNaElement, int, int);
int Msortuj_rok(const void * a, const void * b);
int Msortuj_l_utworow(const void * a, const void * b);
int Msortuj_tytul(const void * a, const void * b);
int Msortuj_artysta(const void * a, const void * b);
int Msortuj_gatunek(const void * a, const void * b);
int Rsortuj_rok(const void * a, const void * b);
int Rsortuj_l_utworow(const void * a, const void * b);
int Rsortuj_tytul(const void * a, const void * b);
int Rsortuj_artysta(const void * a, const void * b);
int Rsortuj_gatunek(const void * a, const void * b);
