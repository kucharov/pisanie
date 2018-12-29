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

struct dane_plyty_dodawanej{
	
	char *tytul;
	char *artysta;
	char *gatunek;
	int  rok;
	int l_utworow;
};

typedef struct Element * WskaznikNaElement;
typedef enum {FALSZ, PRAWDA} Bool;

int forma_dodawanie_elementu(char *, char *, char *, int *, int *);
int forma_edycja_elementu(char *, char *, char *, int *, int *);
void menu(int *);
/*funkcja dodaje nowy element na poczatek  i jako wynik zwraca wskaznik do niego*/
WskaznikNaElement dodanieNowegoElementu(WskaznikNaElement pierwszy_album, char *, char *, char * , int  , int );
/*funcja usuwa pierwszy element dla ktorego przykladowePoleElementu==wartoscPola*/

WskaznikNaElement usuniecieElementu(WskaznikNaElement pierwszy_album, char *);
WskaznikNaElement zwolnieniePamieci(WskaznikNaElement pierwszy_album);
int wyswietlenie_calosci(WskaznikNaElement pierwszy_album);
int wyswietlenie_wyszukania(WskaznikNaElement pierwszy_album,int);
void edycjaDanych(WskaznikNaElement pierwszy_album, char *, int );
WskaznikNaElement wyszukanieElementu_edycja(WskaznikNaElement pierwszy_album, char *, int );
WskaznikNaElement wyszukanieElementu(WskaznikNaElement pierwszy_album, char *, char *, char *, int , int , int, WINDOW * );
char *pobor_danych (const char *,char *temp);
int dialog_1 (int , char **, int *);
int dialog_2 (int , char **, int *);
char *trim(char *);
char *wybor_pliku (char *);
WskaznikNaElement wczytanie_do_struktury(WskaznikNaElement ,char *);
int zapis_do_pliku(WskaznikNaElement );




/*zmienne STATYCZNE ncurses*/
static int funcja_zwrotna(EObjectType, void *,void *,chtype);
static const char *elementy_menu[MAX_MENU_ITEMS][MAX_SUB_ITEMS];
static const char *menuInfo[3][6] =
{
   {
      "",
      "Wyswietlenie calego spisu plyt muzycznych",
      "Wyszukiwanie plyt wedlug konkretnego pola",     
      "Wyjscie z programu",
      ""
      ""
   },
   {
      "",
      "Dodawanie plyty do spisu",
      "Edycja danych na temat wybranej plyty",
      "Usuniecie wybranej plyty ze spisu",
      "Wczytanie listy plyt z pliku na dysku",
      "Zapis aktualnego spisu do pliku na dysku"
   },
   {
      "",
      "Help for editing",
      "Help for file management",
      "Info about the program",
      "",
      ""}
};

/// MAIN
int main (int argc, char **argv)
	{
		struct dane_plyty_dodawanej dane_zczytane;
		int wybrany; 
		WskaznikNaElement pierwszy_album = NULL;
		char wybranaOpcjaMenu, nazwa_pliku[C]={"\0"};
		char temp_tytul[ROZMIAR], temp_artysta[ROZMIAR], temp_gatunek[ROZMIAR], tytul_do_usuniecia[ROZMIAR], zapychacz[ROZMIAR]="stolzpowylamywanymi";
		int temp_rok, temp_l_utworow, szukane_id, wybor;
		for(;;)
			{
				menu(&wybrany);
				//wyswietl spis
				if((wybrany / 100)==0 && (wybrany % 100)==0)
					{
						if(pierwszy_album!=NULL) wyswietlenie_calosci(pierwszy_album);
								
					}
				//wyszukaj utwor
				else if((wybrany / 100)==0 && (wybrany % 100)==1)
					{
						dialog_2(argc, NULL, &wybor);
						wyswietlenie_wyszukania(pierwszy_album,wybor);
							
					}
				
				//dodanie elementu
				else if((wybrany / 100)==1 && (wybrany % 100)==0)
					{
						forma_dodawanie_elementu(temp_tytul, temp_artysta, temp_gatunek, &temp_rok, &temp_l_utworow);
						
						pierwszy_album=dodanieNowegoElementu(pierwszy_album, temp_tytul, temp_artysta, temp_gatunek, temp_rok, temp_l_utworow);	
					}
				//edycja elementu
				else if((wybrany / 100)==1 && (wybrany % 100)==1)
					{
						dialog_1(argc, NULL, &wybor);
						if (wybor==0) 
							{

								edycjaDanych(pierwszy_album, pobor_danych("Wpisz tytul plyty do wyszukania",temp_tytul), K);
							}
						else if (wybor==1) 
							{
								
								szukane_id=atoi(pobor_danych("Wpisz ID plyty do wyszukania",temp_tytul));
								
								edycjaDanych(pierwszy_album, zapychacz, szukane_id);
							}
						
						
								
					}
				//usuwanie plyty
				else if((wybrany / 100)==1 && (wybrany % 100)==2)
					{
						
						usuniecieElementu(pierwszy_album,pobor_danych("Wpisz tytul plyty do usuniecia",temp_tytul));
								
					}
				//wczytanie z pliku
				else if((wybrany / 100)==1 && (wybrany % 100)==3)
					{
					pierwszy_album=wczytanie_do_struktury(pierwszy_album,wybor_pliku(nazwa_pliku));
					
					}
				//zapis do pliku
				else if((wybrany / 100)==1 && (wybrany % 100)==4)
					{
					zapis_do_pliku(pierwszy_album);
					
					}
				//wyjscie
				else if((wybrany / 100)==0 && (wybrany % 100)==2)
					{
						return 0;
							
					}
			}
		return 0;
		
		
	}
///  FUNKCJE	
void menu(int *wybrany)
{
   CDKSCREEN *ekran;
   CDKLABEL *info;
   CDKMENU *menu;
   WINDOW *okno;
   int rozmiar_submenu[3]={4,6,4}, pozycja_submenu[3]={LEFT,LEFT,RIGHT};
   const char *tekst[2]={"                                                    ",
						"                                                    "};
   char temp[256];
	start_color();
	okno = initscr ();
	ekran = initCDKScreen (okno);
	noecho();
	curs_set(0);

    /* Set up the menu. */
	elementy_menu[0][0] = "</B>Baza danych<!B>";
	elementy_menu[0][1] = "</B>Wyswietl spis<!B>";
	elementy_menu[0][2] = "</B>Wyszukaj plyte<!B>";
	elementy_menu[0][3] = "</B>Wyjscie<!B>";

	elementy_menu[1][0] = "</B>Edycja<!B>";
	elementy_menu[1][1] = "</B>Dodaj<!B> ";
	elementy_menu[1][2] = "</B>Edytuj<!B>";
	elementy_menu[1][3] = "</B>Usun<!B>";
	elementy_menu[1][4] = "</B>Wczytaj<!B>";
	elementy_menu[1][5] = "</B>Zapisz<!B>";
   
	elementy_menu[2][0] = "</B>Pomoc<!B>";
	elementy_menu[2][1] = "</B>On Edit <!B>";
	elementy_menu[2][2] = "</B>On File <!B>";
	elementy_menu[2][3] = "</B>About...<!B>";

	

   info = newCDKLabel (ekran, CENTER, BOTTOM, (CDK_CSTRING2) tekst, 2, TRUE, FALSE);
   menu = newCDKMenu (ekran, elementy_menu, 3, rozmiar_submenu, pozycja_submenu,
		      TOP, A_UNDERLINE, A_REVERSE);
   setCDKMenuPostProcess (menu, funcja_zwrotna, info);
   refreshCDKScreen (ekran);
   *wybrany = activateCDKMenu (menu, 0);
   
   destroyCDKMenu (menu);
   destroyCDKLabel (info);
   destroyCDKScreen (ekran);
   endCDK ();
   
}

static int funcja_zwrotna (EObjectType cdktype GCC_UNUSED, void *object,
			    void *clientData,
			    chtype input GCC_UNUSED)

{
   CDKMENU *menu        = (CDKMENU *)object;
   CDKLABEL *info    = (CDKLABEL *)clientData;
   char *tekst[2];
   char temp[256];
   sprintf (temp, "%.*s",(int)(sizeof (temp) - 20), elementy_menu[menu->currentTitle][0]);
   tekst[0] = strdup (temp);
   sprintf (temp, "Funkcja: %.*s", (int)(sizeof (temp) - 20), menuInfo[menu->currentTitle][menu->currentSubtitle + 1]);
   tekst[1] = strdup (temp);
  
   setCDKLabel (info, (CDK_CSTRING2)tekst, 2, TRUE);
   drawCDKLabel (info, TRUE);
   freeCharList (tekst, 2);
   return 0;
}
char *trim(char *str)
{
    size_t len = 0;
    char *frontp = str;
    char *endp = NULL;

    if( str == NULL ) { return NULL; }
    if( str[0] == '\0' ) { return str; }

    len = strlen(str);
    endp = str + len;

    /* Move the front and back pointers to address the first non-whitespace
     * characters from each end.
     */
    while( isspace((unsigned char) *frontp) ) { ++frontp; }
    if( endp != frontp )
    {
        while( isspace((unsigned char) *(--endp)) && endp != frontp ) {}
    }

    if( str + len - 1 != endp )
            *(endp + 1) = '\0';
    else if( frontp != str &&  endp == frontp )
            *str = '\0';

    /* Shift the string so that it starts at str so that if it's dynamically
     * allocated, we can still free it on the returned pointer.  Note the reuse
     * of endp to mean the front of the string buffer now.
     */
    endp = str;
    if( frontp != str )
    {
            while( *frontp ) { *endp++ = *frontp++; }
            *endp = '\0';
    }


    return str;
}
int forma_dodawanie_elementu(char *temp_tytul, char *temp_artysta, char *temp_gatunek, int *temp_rok, int *temp_l_utworow)
	{	FIELD *pola[N];
		FORM  *formularz;
		char *etykieta[N-1]={"Nazwa albumu:","Artysta:","Gatunek:","Rok wydania:","Ilosc utworow:"}, *ptr;
		
		int ch,wiersz=4,wiersze,kolumny;
		long int konwersja_input_int;
		initscr();
		getmaxyx(stdscr,wiersze,kolumny);
		cbreak();
		start_color();
		noecho();
		curs_set(1);
		keypad(stdscr, TRUE);

		/* Definiowanie pol */
		for (int i=0, wiersz=4;i<N-1;i++)
			{
			pola[i] = new_field(1, 20, wiersz, 18, 0, 0);
			wiersz=wiersz+2;
			}
			pola[N-1] = NULL;

		/* Ustawienie parametrow pol */
		for (int j=0;j<N-1;j++)
			{
				set_field_back(pola[j], A_UNDERLINE);
				
				set_field_opts(pola[j], O_VISIBLE | O_PUBLIC | O_EDIT | O_ACTIVE);
			}
		set_field_type(pola[3],TYPE_INTEGER,0,1,2030);
		set_field_type(pola[4],TYPE_INTEGER,0,1,100);
		
		/* Utworzenie formularza */
		formularz = new_form(pola);
		post_form(formularz);
		refresh();
		/*wyswietlenie etykiet*/
		for (int k=0, wiersz=4;k<N-1;k++)
			{
				mvprintw(wiersz, 4, etykieta[k]);
				wiersz=wiersz+2;
			}
		
		
		
		mvprintw(18, 80, "F5 - zamknij");
		move(4,18);
		refresh();

		/* Petla obslugujaca input */
		while((ch = getch()) != KEY_F(1))
		{	switch(ch)
			{	case KEY_DOWN:
					/* przejscie do nastepnego pola */
					form_driver(formularz, REQ_NEXT_FIELD);
					form_driver(formularz, REQ_END_LINE);
					
				case KEY_LEFT:
					form_driver(formularz, REQ_PREV_CHAR);
					break;
					// usuwanie znaku przed kursorem
					case KEY_BACKSPACE:
					case 127:
						form_driver(formularz, REQ_DEL_PREV);
						break;
				case KEY_RIGHT:
					form_driver(formularz, REQ_NEXT_CHAR);
					break;
					/* Go to next pola */
					form_driver(formularz, REQ_NEXT_FIELD);
					/* Go to the end of the present buffer */
					/* Leaves nicely at the last character */
					form_driver(formularz, REQ_END_LINE);
					break;
				case KEY_UP:
					/* przejscie do nastepnego pola */
					form_driver(formularz, REQ_PREV_FIELD);
					form_driver(formularz, REQ_END_LINE);
					break;
				case KEY_F(4):
					form_driver(formularz, REQ_NEXT_FIELD);
					form_driver(formularz, REQ_PREV_FIELD);
					move(wiersze-1, 1);
					printw("%s",field_buffer(pola[4], 0));
						refresh();
					break;
				case KEY_F(5):
				
					refresh();
					strncpy(temp_tytul,trim(field_buffer(pola[0], 0)),strnlen(field_buffer(pola[0], 0),20));
					strncpy(temp_artysta,trim(field_buffer(pola[1], 0)),strnlen(field_buffer(pola[1], 0),20));
					strncpy(temp_gatunek,trim(field_buffer(pola[2], 0)),strnlen(field_buffer(pola[2], 0),20));
					
					*temp_rok=atoi(trim(field_buffer(pola[3], 0)));
					*temp_l_utworow=atoi(trim(field_buffer(pola[4], 0)));
					
					unpost_form(formularz);
					free_form(formularz);
					free_field(pola[0]);
					free_field(pola[1]);
					free_field(pola[2]);
					free_field(pola[3]);
					free_field(pola[4]);
					
					endwin();
					
					return 0;
				default:
					/* Gdy zwykly znak, pobranie */
					form_driver(formularz, ch);
					break;
			}
		}
	return 0;	
	}
	
int forma_edycja_elementu(char *temp_tytul, char *temp_artysta, char *temp_gatunek, int *temp_rok, int *temp_l_utworow)
	{	FIELD *pola[N];
		FORM  *formularz;
		char *etykieta[N-1]={"Nazwa albumu:","Artysta:","Gatunek:","Rok wydania:","Ilosc utworow:"}, *ptr;
		char rok_lancuch[ROZMIAR], liczba_lancuch[ROZMIAR];
		int ch,wiersz=4,wiersze,kolumny;
		long int konwersja_input_int;
		initscr();
		getmaxyx(stdscr,wiersze,kolumny);
		cbreak();
		start_color();
		noecho();
		curs_set(1);
		keypad(stdscr, TRUE);

		/* Definiowanie pol */
		for (int i=0, wiersz=4;i<N-1;i++)
			{
			pola[i] = new_field(1, 20, wiersz, 18, 0, 0);
			wiersz=wiersz+2;
			}
			pola[N-1] = NULL;

		/* Ustawienie parametrow pol */
		for (int j=0;j<N-1;j++)
			{
				set_field_back(pola[j], A_UNDERLINE);
				set_field_opts(pola[j], O_VISIBLE | O_PUBLIC | O_EDIT | O_ACTIVE);
			}
		set_field_type(pola[3],TYPE_INTEGER,0,1,2030);
		set_field_type(pola[4],TYPE_INTEGER,0,1,100);
		
		/* Utworzenie formularza */
		formularz = new_form(pola);
		post_form(formularz);
		refresh();
		/*wyswietlenie etykiet*/
		for (int k=0, wiersz=4;k<N-1;k++)
			{
				mvprintw(wiersz, 4, etykieta[k]);
				wiersz=wiersz+2;
			}
		/* wczytanie danych o plycie*/
		
		
		
		sprintf(rok_lancuch,"%d",*temp_rok);
		sprintf(liczba_lancuch,"%d",*temp_l_utworow);			
		
		set_field_buffer(pola[0], 0, temp_tytul);
		set_field_buffer(pola[1], 0, temp_artysta);
		set_field_buffer(pola[2], 0, temp_gatunek);
		set_field_buffer(pola[3], 0, rok_lancuch);
		set_field_buffer(pola[4], 0, liczba_lancuch);
	
	
		
		
		
		
		
		
		
		mvprintw(18, 80, "F5 - zamknij");
		move(4,18);
		refresh();

		/* Petla obslugujaca input */
		while((ch = getch()) != KEY_F(1))
		{	switch(ch)
			{	case KEY_DOWN:
					/* przejscie do nastepnego pola */
					form_driver(formularz, REQ_NEXT_FIELD);
					form_driver(formularz, REQ_END_LINE);
					
				case KEY_LEFT:
					form_driver(formularz, REQ_PREV_CHAR);
					break;
					// usuwanie znaku przed kursorem
					case KEY_BACKSPACE:
					case 127:
						form_driver(formularz, REQ_DEL_PREV);
						break;
				case KEY_RIGHT:
					form_driver(formularz, REQ_NEXT_CHAR);
					break;
					/* Go to next pola */
					form_driver(formularz, REQ_NEXT_FIELD);
					/* Go to the end of the present buffer */
					/* Leaves nicely at the last character */
					form_driver(formularz, REQ_END_LINE);
					break;
				case KEY_UP:
					/* przejscie do nastepnego pola */
					form_driver(formularz, REQ_PREV_FIELD);
					form_driver(formularz, REQ_END_LINE);
					break;
				case KEY_F(4):
					form_driver(formularz, REQ_NEXT_FIELD);
					form_driver(formularz, REQ_PREV_FIELD);
					move(wiersze-1, 1);
					printw("%s",field_buffer(pola[4], 0));
						refresh();
					break;
				case KEY_F(5):
					refresh();
					strncpy(temp_tytul,trim(field_buffer(pola[0], 0)),strnlen(field_buffer(pola[0], 0),20));
					strncpy(temp_artysta,trim(field_buffer(pola[1], 0)),strnlen(field_buffer(pola[1], 0),20));
					strncpy(temp_gatunek,trim(field_buffer(pola[2], 0)),strnlen(field_buffer(pola[2], 0),20));
					
					*temp_rok=atoi(trim(field_buffer(pola[3], 0)));
					*temp_l_utworow=atoi(trim(field_buffer(pola[4], 0)));
					
					unpost_form(formularz);
					free_form(formularz);
					free_field(pola[0]);
					free_field(pola[1]);
					free_field(pola[2]);
					free_field(pola[3]);
					free_field(pola[4]);
					
					endwin();
					
					return 0;
				default:
					/* Gdy zwykly znak, pobranie */
					form_driver(formularz, ch);
					break;
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
    //Alokacja
    nowyElement->tytul=(char *)malloc( ROZMIAR*sizeof(char) );
    nowyElement->artysta=(char *)malloc( ROZMIAR*sizeof(char) );
    nowyElement->gatunek=(char *)malloc( ROZMIAR*sizeof(char) );
    //Kopiowanie danych
    strncpy(nowyElement->tytul,t,ROZMIAR*sizeof(*t));
    strncpy(nowyElement->artysta,a,ROZMIAR*sizeof(*a));
    strncpy(nowyElement->gatunek,g,ROZMIAR*sizeof(*g));
    nowyElement->rok=r;
    nowyElement->l_utworow=l;
    nowyElement->nastepny_album = pierwszy_album;
    
    return nowyElement;
   }

int wyswietlenie_calosci(WskaznikNaElement pierwszy_album)
   {
	WskaznikNaElement biezacy_album=pierwszy_album;
	const char *tekst[3]={"strzalka w dol - przewijanie listy w dol                                 ",
						"strzalka w gore - przewijanie listy w gore                                ",
						"F5 - wyjscie do menu glownego                                            "};
	int mypadpos = 0, ch;
	char smietnik;
	int mrow, mcol=70, rowcount =100;
	WINDOW *pad;
	CDKLABEL *info;
	CDKSCREEN *ekran;
	
	initscr();
	keypad(stdscr, TRUE);
	start_color();
	getmaxyx(stdscr, mrow, mcol);
	curs_set(0);
	
	pad = newpad (rowcount + 1, mcol);
	
	fprintf(stdin, "\n");
	//INFO
	ekran = initCDKScreen (pad);
	info = newCDKLabel (ekran, CENTER, TOP, (CDK_CSTRING2) tekst, 3, TRUE, FALSE);
	
	
	
	while(biezacy_album != NULL)
    	{
		wprintw(pad,"ID: %d\n\n",biezacy_album->id);  
        wprintw(pad,"Tytul: %s\n", biezacy_album->tytul );
		wprintw(pad,"Artysta: %s\n", biezacy_album->artysta );
		wprintw(pad,"Gatunek: %s\n", biezacy_album->gatunek );
		wprintw(pad,"Rok wydania: %d\n",biezacy_album->rok );
		wprintw(pad,"Liczba utworow na plycie: %d\n\n", biezacy_album->l_utworow );
		biezacy_album = biezacy_album->nastepny_album;
    	}
    	
	  prefresh(pad, mypadpos, 0, 0, 0, 50, mcol);
	 
	
	
	  // menu
	  fprintf(stdin, "\n");
	  while((ch = getch()) != KEY_F(5))
	  {
		fprintf(stdin, "\n");
		switch (ch)
		{
			case KEY_UP:
			
			if (mypadpos >= 0)
					{
						mypadpos-=8;
					}
			prefresh(pad, mypadpos, 0, 0, 0, 50, mcol);
			refreshCDKScreen (ekran);
			
			break;
			
			
			case KEY_DOWN:
			
			
			if (mypadpos <= rowcount+1)
					{
						mypadpos+=8;
					}
			prefresh(pad, mypadpos, 0, 0, 0, 50, mcol);
			refreshCDKScreen (ekran);
			break;
			
			default:
			prefresh(pad, mypadpos, 0, 0, 0, 50, mcol);
			refreshCDKScreen (ekran);
				/* Gdy zwykly znak, pobranie */
			//return(0);
			break;
		 }
	  }
    
    delwin(pad);
    destroyCDKLabel (info);
    destroyCDKScreen (ekran);
	clear();
    endwin();
    endCDK ();
    return 0;
   }
int wyswietlenie_wyszukania(WskaznikNaElement pierwszy_album, int wybor)
   {
	
	
	int mypadpos = 0, ch, szukana_dana;
	char smietnik, temp_tytul[ROZMIAR], zapychacz[ROZMIAR]="stolzpowylamywanymi";
	const char *tekst[3]={"strzalka w dol - przewijanie listy w dol                                 ",
						"strzalka w gore - przewijanie listy w gore                                ",
						"F5 - wyjscie do menu glownego                                            "};
	int mrow, mcol=70, rowcount =100;
	int argc=4;
	if (wybor==0) 
		{
			 strcpy(temp_tytul,pobor_danych("Wpisz tytul plyty do wyszukania",temp_tytul));
		}
	else if (wybor==1) 
		{
			strcpy(temp_tytul,pobor_danych("Wpisz artyste, ktorego plyty szukasz",temp_tytul));
		}
	else if (wybor==2) 
		{
			strcpy(temp_tytul,pobor_danych("Wpisz gatunek plyt, ktorych szukasz",temp_tytul));
		}
	else if (wybor==3) 
		{
			szukana_dana=atoi(pobor_danych("Wpisz rok wydania plyt, ktorych szukasz",temp_tytul));		 
		}	
	else if (wybor==4) 
		{
			szukana_dana=atoi(pobor_danych("Wpisz liczbe utworow na plytach, ktorych szukasz",temp_tytul));		 
		}
	else if (wybor==5) 
		{
			szukana_dana=atoi(pobor_danych("Wpisz ID plyty ktorej szukasz",temp_tytul));		 
		}
	
	
	
	WINDOW *pad;
	CDKLABEL *info;
	CDKSCREEN *ekran;
	
	initscr();
	keypad(stdscr, TRUE);
	start_color();
	getmaxyx(stdscr, mrow, mcol);
	curs_set(0);
	
	pad = newpad (rowcount + 1, mcol);
	
	fprintf(stdin, "\n");
	//INFO
	ekran = initCDKScreen (pad);
	info = newCDKLabel (ekran, CENTER, TOP, (CDK_CSTRING2) tekst, 3, TRUE, FALSE);
	
	
	
	
	
	///DANE
	if (wybor==0) 
		{
			wyszukanieElementu( pierwszy_album, temp_tytul, zapychacz, zapychacz, K, K, K,pad);		 
		}
	else if (wybor==1) 
		{
			wyszukanieElementu( pierwszy_album, zapychacz,temp_tytul, zapychacz, K, K, K,pad);		 
		}
	else if (wybor==2) 
		{
			wyszukanieElementu( pierwszy_album, zapychacz, zapychacz, temp_tytul, K, K, K,pad);		 
		}
	else if (wybor==3) 
		{
			wyszukanieElementu( pierwszy_album, zapychacz, zapychacz, zapychacz,szukana_dana, K, K,pad);		 
		}	
	else if (wybor==4) 
		{
			wyszukanieElementu( pierwszy_album, zapychacz, zapychacz, zapychacz, K,szukana_dana , K,pad);		 
		}
	else if (wybor==5) 
		{
			wyszukanieElementu( pierwszy_album, zapychacz, zapychacz, zapychacz, K, K, szukana_dana,pad);		 
		}
    	
	
    
	 
	  // menu
	  
	  while((ch = getch()) != KEY_F(5))
	  {
		switch (ch)
		{
			case KEY_UP:
			
			if (mypadpos >= 0)
					{
						mypadpos-=8;
					}
			prefresh(pad, mypadpos, 0, 0, 0, 50, mcol);
			refreshCDKScreen (ekran);
			break;
			
			
			case KEY_DOWN:
			
		
			if (mypadpos <= rowcount+1)
					{
						mypadpos+=8;
					}
			prefresh(pad, mypadpos, 0, 0, 0, 50, mcol);
			refreshCDKScreen (ekran);
			break;
			
			default:
			prefresh(pad, mypadpos, 0, 0, 0, 50, mcol);
			refreshCDKScreen (ekran);
			break;
		 }
	  }
    
    delwin(pad);
    destroyCDKLabel (info);
    destroyCDKScreen (ekran);
	clear();
    endwin();
    endCDK ();
    return 0;
   }


int dialog_1 (int argc, char **argv, int *wybor)
{
   /* *INDENT-EQLS* */
   CDKSCREEN *cdkscreen = 0;
   CDKDIALOG *question  = 0;
   const char *buttons[] =
   {"</B16>Tytul", "</B16>ID"};
   const char *message[10];
   const char *mesg[3];
   char temp[100];
   
   CDK_PARAMS params;

   CDKparseParams (argc, argv, &params, CDK_MIN_PARAMS);

   cdkscreen = initCDKScreen (NULL);

   /* Start color. */
   initCDKColor ();
	curs_set(0);
   /* Create the message within the dialog box. */
   message[0] = "<C></B>Edycja plyty";
   message[1] = " ";
   message[2] = " ";
   message[3] = "<C>Aby edytowac plyte, musisz wyszukac ja w bazie danych.";
   message[4] = "<C>Wybierz czy chcesz wyszukac wpisujac tytul plyty, czy jej ID";
	message[5] = " ";
	message[6] = " ";
   /* Create the dialog box. */
   question = newCDKDialog (cdkscreen,
			    CDKparamValue (&params, 'X', CENTER),
			    CDKparamValue (&params, 'Y', CENTER),
			    (CDK_CSTRING2) message, 7,
			    (CDK_CSTRING2) buttons, 2,
			    COLOR_PAIR (2) | A_REVERSE,
			    TRUE,
			    CDKparamValue (&params, 'N', TRUE),
			    CDKparamValue (&params, 'S', FALSE));

   /* Check if we got a null value back. */
   if (question == 0)
   {
      /* Shut down Cdk. */
      destroyCDKScreen (cdkscreen);
      endCDK ();

      printf ("Za male okno terminala\n");
      return 0;
   }

   /* Activate the dialog box. */
   *wybor = activateCDKDialog (question, 0);

   /* Tell them what was selected. */
   

   /* Clean up. */
   destroyCDKDialog (question);
   destroyCDKScreen (cdkscreen);
   endCDK ();
   return 0;
   
}

int dialog_2 (int argc, char **argv, int *wybor)
{
   /* *INDENT-EQLS* */
   CDKSCREEN *cdkscreen = 0;
   CDKDIALOG *question  = 0;
   const char *buttons[] =
   {"</B16>Tytul","</B16>Artysta","</B16>Gatunek","</B16>Rok wydania","</B16>Liczba utworow", "</B16>ID"};
   const char *message[10];
   const char *mesg[3];
   char temp[100];
   
   CDK_PARAMS params;

   CDKparseParams (argc, argv, &params, CDK_MIN_PARAMS);

   cdkscreen = initCDKScreen (NULL);

   /* Start color. */
   initCDKColor ();
	curs_set(0);
   /* Create the message within the dialog box. */
   message[0] = "<C></B>Wyszukiwanie plyty";
   message[1] = " ";
   message[2] = " ";
   message[3] = "<C>Aby wyszukac plyte w bazie danych, musisz wybrac pole ";
   message[4] = "<C>wedlug ktorego chcesz przeprowadzic wyszukiwanie";
	message[5] = " ";
	message[6] = " ";
   /* Create the dialog box. */
   question = newCDKDialog (cdkscreen,
			    CDKparamValue (&params, 'X', CENTER),
			    CDKparamValue (&params, 'Y', CENTER),
			    (CDK_CSTRING2) message, 7,
			    (CDK_CSTRING2) buttons, 6,
			    COLOR_PAIR (2) | A_REVERSE,
			    TRUE,
			    CDKparamValue (&params, 'N', TRUE),
			    CDKparamValue (&params, 'S', FALSE));

   /* Check if we got a null value back. */
   if (question == 0)
   {
      /* Shut down Cdk. */
      destroyCDKScreen (cdkscreen);
      endCDK ();

      printf ("Za male okno terminala\n");
      return 0;
   }

   /* Activate the dialog box. */
   *wybor = activateCDKDialog (question, 0);

   /* Tell them what was selected. */
   

   /* Clean up. */
   destroyCDKDialog (question);
   destroyCDKScreen (cdkscreen);
   endCDK ();
   return 0;
   
}
char *pobor_danych (const char *title, char *info)
{
     /* *INDENT-EQLS* */
   CDKSCREEN *cdkscreen = 0;
   CDKMENTRY *widget    = 0;
   const char *label    = "</R>:";
   

  

   cdkscreen = initCDKScreen (NULL);

   /* Start CDK Colors. */
   initCDKColor ();

   /* Set up the multi-line entry field. */
   widget = newCDKMentry (cdkscreen,
			  CENTER,
			  CENTER,
			  title, label, A_BOLD, '_', vMIXED,
			  30,
			  1,
			  30,
			  0,
			  TRUE,
			  FALSE);

   /* Is the object null? */
   if (widget == 0)
   {
      /* Shut down CDK. */
      destroyCDKScreen (cdkscreen);
      endCDK ();

      printf ("Za male okno terminala\n");
      
   }

   /* Draw the CDK screen. */
   refreshCDKScreen (cdkscreen);

   /* Set what ever was given from the command line. */
   //setCDKMentry (widget, argv[optind], 0, TRUE);

   /* Activate this thing. */
   activateCDKMentry (widget, 0);
   info = strdup (widget->info);

   /* Clean up. */
   destroyCDKMentry (widget);
   destroyCDKScreen (cdkscreen);
   endCDK ();

   printf ("\n\n\n");
   printf ("Your message was : <%s>\n", info);
  
  
   return info;
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







void edycjaDanych(WskaznikNaElement pierwszy_album, char *tytul_do_wyszukania, int id_do_wyszukania)
	{
		
		WskaznikNaElement plyta_edytowana=NULL;
		char temp_tytul[ROZMIAR], temp_artysta[ROZMIAR], temp_gatunek[ROZMIAR];
		int temp_rok, temp_l_utworow;
		if	(wyszukanieElementu_edycja(pierwszy_album, tytul_do_wyszukania, id_do_wyszukania)!=NULL)
					{	
					
					plyta_edytowana=wyszukanieElementu_edycja(pierwszy_album, tytul_do_wyszukania, id_do_wyszukania);
					//wyciagniecie danych ze struktury
					strncpy(temp_tytul,plyta_edytowana->tytul,ROZMIAR);
					strncpy(temp_artysta,plyta_edytowana->artysta,ROZMIAR);
					strncpy(temp_gatunek,plyta_edytowana->gatunek,ROZMIAR);
					temp_rok=plyta_edytowana->rok;
					temp_l_utworow=plyta_edytowana->l_utworow;
					
					forma_edycja_elementu(temp_tytul, temp_artysta, temp_gatunek, &temp_rok, &temp_l_utworow);	
					/*nadpisanie danych*/
					strncpy(plyta_edytowana->tytul,temp_tytul,ROZMIAR);
					strncpy(plyta_edytowana->artysta,temp_artysta,ROZMIAR);
					strncpy(plyta_edytowana->gatunek,temp_gatunek,ROZMIAR);
					plyta_edytowana->rok=temp_rok;
					plyta_edytowana->l_utworow=temp_l_utworow;
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

WskaznikNaElement wyszukanieElementu(WskaznikNaElement pierwszy_album, char *tytul_do_wyszukania, char *artysta_do_wyszukania, char *gatunek_do_wyszukania, int rok_do_wyszukania, int l_utworow_do_wyszukania, int id_do_wyszukania, WINDOW *pad)				 
	{
		WskaznikNaElement biezacy_album=pierwszy_album, poprzedniElement=NULL;
		
		do
			{
			
			if( !strcmp(biezacy_album->tytul,tytul_do_wyszukania)) ////WYSZUKANIE PO TYTULE
				{
				
				wprintw(pad,"ID: %d\n\n",biezacy_album->id);
				wprintw(pad,"\nTytul: %s\n", biezacy_album->tytul );
				wprintw(pad,"Artysta: %s\n", biezacy_album->artysta );
				wprintw(pad,"Gatunek: %s\n", biezacy_album->gatunek );
				wprintw(pad,"Rok wydania: %d\n",biezacy_album->rok );
				wprintw(pad,"Liczba utworow na plycie: %d\n\n", biezacy_album->l_utworow );
				
				}
			else if ( !strcmp(biezacy_album->artysta,artysta_do_wyszukania)) ////WYSZUKANIE PO ARTYSCIE
				{
				wprintw(pad,"ID: %d\n\n",biezacy_album->id);
				wprintw(pad,"\nTytul: %s\n", biezacy_album->tytul );
				wprintw(pad,"Artysta: %s\n", biezacy_album->artysta );
				wprintw(pad,"Gatunek: %s\n", biezacy_album->gatunek );
				wprintw(pad,"Rok wydania: %d\n",biezacy_album->rok );
				wprintw(pad,"Liczba utworow na plycie: %d\n\n", biezacy_album->l_utworow );
				
				}
			else if ( !strcmp(biezacy_album->gatunek,gatunek_do_wyszukania)) ////WYSZUKANIE PO GATUNKU
				{
				wprintw(pad,"ID: %d\n\n",biezacy_album->id);
				wprintw(pad,"\nTytul: %s\n", biezacy_album->tytul );
				wprintw(pad,"Artysta: %s\n", biezacy_album->artysta );
				wprintw(pad,"Gatunek: %s\n", biezacy_album->gatunek );
				wprintw(pad,"Rok wydania: %d\n",biezacy_album->rok );
				wprintw(pad,"Liczba utworow na plycie: %d\n\n", biezacy_album->l_utworow );
				}
			else if (biezacy_album->rok==rok_do_wyszukania) ////WYSZUKANIE PO ROKU WYDANIA
				{
				wprintw(pad,"ID: %d\n\n",biezacy_album->id);
				wprintw(pad,"\nTytul: %s\n", biezacy_album->tytul );
				wprintw(pad,"Artysta: %s\n", biezacy_album->artysta );
				wprintw(pad,"Gatunek: %s\n", biezacy_album->gatunek );
				wprintw(pad,"Rok wydania: %d\n",biezacy_album->rok );
				wprintw(pad,"Liczba utworow na plycie: %d\n\n", biezacy_album->l_utworow );
				}
			else if (biezacy_album->l_utworow==l_utworow_do_wyszukania) ////WYSZUKANIE PO L_UTWOROW
				{
				wprintw(pad,"ID: %d\n\n",biezacy_album->id);
				wprintw(pad,"\nTytul: %s\n", biezacy_album->tytul );
				wprintw(pad,"Artysta: %s\n", biezacy_album->artysta );
				wprintw(pad,"Gatunek: %s\n", biezacy_album->gatunek );
				wprintw(pad,"Rok wydania: %d\n",biezacy_album->rok );
				wprintw(pad,"Liczba utworow na plycie: %d\n\n", biezacy_album->l_utworow );
				}
			else if (biezacy_album->id==id_do_wyszukania) ////WYSZUKANIE PO ID
				{
				wprintw(pad,"ID: %d\n\n",biezacy_album->id);
				wprintw(pad,"\nTytul: %s\n", biezacy_album->tytul );
				wprintw(pad,"Artysta: %s\n", biezacy_album->artysta );
				wprintw(pad,"Gatunek: %s\n", biezacy_album->gatunek );
				wprintw(pad,"Rok wydania: %d\n",biezacy_album->rok );
				wprintw(pad,"Liczba utworow na plycie: %d\n\n", biezacy_album->l_utworow );
				}
			poprzedniElement = biezacy_album;
			biezacy_album = biezacy_album->nastepny_album;
			} while(biezacy_album != NULL);
		return NULL;
	}










//#define CB_PARAMS EObjectType cdktype GCC_UNUSED, void* object GCC_UNUSED, void* clientdata GCC_UNUSED, chtype key GCC_UNUSED











char *wybor_pliku (char *nazwa_pliku)
{
	CDKSCREEN *cdkscreen = 0;
	
    CDKVIEWER *example   = 0;
    CDKFSELECT *fSelect  = 0;
	const char *title    = "<C>Pick\n<C>A\n<C>File";
	const char *label    = "File: ";
	char **info          = 0;
	const char *button[5];
	
	char *filename;
	char vTitle[256];
	
	int selected, lines;

   
 
   button[0] = "</5><OK><!5>";
   button[1] = "</5><Wyjdz><!5>";

   cdkscreen = initCDKScreen (NULL);

   
   initCDKColor ();

   /* Zlapanie nazwy pliku */
   fSelect = newCDKFselect (cdkscreen,
			    CENTER,
			    CENTER,
			    20,
			    65,
			    title, label, A_NORMAL, '_', A_REVERSE,
			    "</5>", "</48>", "</N>", "</N>",
			    TRUE,
			    FALSE);

   if (fSelect == 0)
   {
      destroyCDKScreen (cdkscreen);
      endCDK ();

      fprintf (stderr, "Nie udalo sie stworzyc funkcji\n");
      return NULL;
   }

   

 

   
   filename = activateCDKFselect (fSelect, 0);

   
   if (fSelect->exitType == vESCAPE_HIT)
   {
     
    
      destroyCDKFselect (fSelect);
      destroyCDKScreen (cdkscreen);
      endCDK ();

      return NULL;
   }

   /* stworzenie widgetu podgladu */
   example = newCDKViewer (cdkscreen, CENTER, CENTER, 20, -2,
			   (CDK_CSTRING2)button, 2, A_REVERSE, TRUE, FALSE);

   /* sprawdzenie */
   if (example == 0)
   {
      /* wyjscie */
      destroyCDKFselect (fSelect);
      destroyCDKScreen (cdkscreen);
      endCDK ();

      printf ("Za male okno?\n");
      return NULL;
   }

   /* otwarcie pliku i wysw zawartosci */
   lines = CDKreadFile (filename, &info);
   if (lines == -1)
   {
      filename = copyChar (filename);

      destroyCDKFselect (fSelect);
      destroyCDKScreen (cdkscreen);
      endCDK ();

      printf ("Nie udalo sie otworzyc \"%s\"\n", filename);

	return NULL;
   }

   /* nadanie tytulu i zawartosci*/
   sprintf (vTitle, "<C></B/21>Plik:<!21></22>%20s<!22!B>", filename);
   setCDKViewer (example, vTitle,
		 (CDK_CSTRING2)info, lines,
		 A_REVERSE, TRUE, TRUE, TRUE);
	
	
	

  

   /* aktywacja */
   selected = activateCDKViewer (example, 0);
	
	if (selected!=1) strncpy(nazwa_pliku,filename,strlen(filename));
	
   CDKfreeStrings (info);
	
    /* niszczenie widgetu selekcji */
   destroyCDKFselect (fSelect);
   
   
   /* Czyszczenie */
   destroyCDKViewer (example);
   destroyCDKScreen (cdkscreen);
   endCDK ();
   
   return nazwa_pliku;
}



WskaznikNaElement wczytanie_do_struktury(WskaznikNaElement pierwszy_album,char *nazwa_pliku)
{
	char* token;
	char line[B], temp_tytul[ROZMIAR],temp_artysta[ROZMIAR],temp_gatunek[ROZMIAR],temp_r_lancuch[ROZMIAR],temp_l_lancuch[ROZMIAR];
	int temp_rok_wydania=0, temp_l_utworow=0;
	FILE *wybrany_plik;
	
	///Wlasciwe odszukanie pliku
		wybrany_plik=fopen(nazwa_pliku,"r+");
		if (wybrany_plik==NULL)
			{
				printf ("Nie udalo sie otworzyc \"%s\"\n", nazwa_pliku);
				return NULL;
			}
	
	
///dodawanie struktur	
  
  while (fgets(line, sizeof(line), wybrany_plik) != NULL)
  {
     token = strtok(line, "/");
     while (token != NULL)
     {
        
        strncpy(temp_tytul, token, 20);
        temp_tytul[19] = '\0'; 
        token = strtok(NULL, "/");
        
        strncpy(temp_artysta, token, 20);
        temp_tytul[19] = '\0'; 
        token = strtok(NULL, "/");
        
        strncpy(temp_gatunek, token, 20);
        temp_tytul[19] = '\0'; 
        token = strtok(NULL, "/");
        
        strncpy(temp_r_lancuch, token, 20);
        temp_tytul[19] = '\0'; 
        temp_rok_wydania=atoi(temp_r_lancuch);
        token = strtok(NULL, "/");
        
					
        strncpy(temp_l_lancuch, token, 20);
        temp_tytul[19] = '\0'; 
        temp_l_utworow=atoi(temp_l_lancuch);
        token = strtok(NULL, "/");
        
     }
     pierwszy_album=dodanieNowegoElementu(pierwszy_album,temp_tytul,temp_artysta,temp_gatunek,temp_rok_wydania,temp_l_utworow);
  }
  
  fclose(wybrany_plik);
  return pierwszy_album;
}



int zapis_do_pliku(WskaznikNaElement pierwszy_album)
	{
		FILE *fp;
		char temp_l_utworow[ROZMIAR], temp_rok_lancuch[ROZMIAR];
		WskaznikNaElement biezacy_album=pierwszy_album;
		fp=fopen("baza.txt","w");
		if (fp==NULL)
			{
				printf ("Nie udalo sie otworzyc pliku...\n");
				return 0;
			}
		while(biezacy_album != NULL)
    	{
		
		fputs("/",fp);
		fputs(biezacy_album->tytul,fp);
		fputs("/",fp);
		fputs(biezacy_album->artysta,fp);
		fputs("/",fp);
		fputs(biezacy_album->gatunek,fp);
		fputs("/",fp);
		sprintf(temp_rok_lancuch,"%d",biezacy_album->rok);
		fputs(temp_rok_lancuch,fp);
		fputs("/",fp);
		sprintf(temp_l_utworow,"%d",biezacy_album->l_utworow);
		fputs(temp_l_utworow,fp);
		fputs("\n",fp);
		biezacy_album = biezacy_album->nastepny_album;
    	}
    	fclose(fp);
    	return 0;
    	
   }
		



