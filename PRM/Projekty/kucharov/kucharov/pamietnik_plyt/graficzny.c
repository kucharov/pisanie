
/*!
* \file graficzny.c
* \brief     Plik z glownymi funkcjami programu PP
* \author    Konrad Kucharczyk
* \version   0.1
* \date      16.01.2019
* \copyright Praca i wlasnosc Konrada Kucharczyka
*/

#include "graficzny.h"

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




/*!
* \fn int main (int argc, char **argv)
* \brief Funkcja main - jadro programu
* \details Funkcja spaja wszystkie funkcje programu. Zawiera petle z funkcja menu i instrukcje sterujace.
* \param argc - liczba pobranych argumentow(opcje uruchamiania, nazwa pliku) przy wlaczaniu programu
* \param argv - tablica lancuchow z wartosciami opcji uruchamiania i nazwa pliku
* \param wybrany - wybor opcji menu
* \return liczba 0 w razie poprawnego wywolania
*/
int main (int argc, char **argv)
	{
		int wybrany; 
		WskaznikNaElement pierwszy_album = NULL;
		char nazwa_pliku[C]={"\0"};
		char temp_tytul[ROZMIAR], temp_artysta[ROZMIAR], temp_gatunek[ROZMIAR], zapychacz[ROZMIAR]="stolzpowylamywanymi";
		int temp_rok, temp_l_utworow, szukane_id, wybor, wybor1=0, wybor2=0;
		CDKSCREEN *ekran;
		WINDOW *okno;
		okno = initscr ();
		ekran = initCDKScreen (okno);
		for(;;)
			{
				menu(ekran, okno,&wybrany);
				//wyswietl spis
				if((wybrany / 100)==0 && (wybrany % 100)==0)
					{
						
						if(pierwszy_album!=NULL) wyswietlenie_calosci(ekran,pierwszy_album);
						
						ekran = initCDKScreen (okno);
					}
				//wyszukaj utwor
				else if((wybrany / 100)==0 && (wybrany % 100)==1)
					{
						dialog_2(ekran,argc, NULL, &wybor);
						wyswietlenie_wyszukania(ekran,pierwszy_album,wybor);
						ekran = initCDKScreen (okno);
					}
				//sortowanie plyty
				else if((wybrany / 100)==0 && (wybrany % 100)==2)
					{
						dialog_3(ekran,argc, NULL, &wybor1);
						dialog_4(ekran,argc, NULL, &wybor2);
						sortowanie(ekran,pierwszy_album,wybor1,wybor2);
						ekran = initCDKScreen (okno);
					}
				//dodanie elementu
				else if((wybrany / 100)==1 && (wybrany % 100)==0)
					{
						forma_dodawanie_elementu(temp_tytul, temp_artysta, temp_gatunek, &temp_rok, &temp_l_utworow);
						
						pierwszy_album=dodanie_nowego_elementu(pierwszy_album, temp_tytul, temp_artysta, temp_gatunek, temp_rok, temp_l_utworow);	
					}
				//edycja elementu
				else if((wybrany / 100)==1 && (wybrany % 100)==1)
					{
						dialog_1(ekran,argc, NULL, &wybor);
						if (wybor==0) 
							{

								edycja_danych(pierwszy_album, pobor_danych(ekran,"Wpisz tytul plyty do wyszukania",temp_tytul), K);
							}
						else if (wybor==1) 
							{
								
								szukane_id=atoi(pobor_danych(ekran,"Wpisz ID plyty do wyszukania",temp_tytul));
								
								edycja_danych(pierwszy_album, zapychacz, szukane_id);
							}
									
					}
				//usuwanie plyty
				else if((wybrany / 100)==1 && (wybrany % 100)==2)
					{
						
						pierwszy_album=usuniecie_elementu(pierwszy_album,pobor_danych(ekran,"Wpisz tytul plyty do usuniecia",temp_tytul));
								
					}
				//wczytanie z pliku
				else if((wybrany / 100)==1 && (wybrany % 100)==3)
					{
					pierwszy_album=wczytanie_do_struktury(pierwszy_album,wybor_pliku(ekran,nazwa_pliku));
					
					}
				//zapis do pliku
				else if((wybrany / 100)==1 && (wybrany % 100)==4)
					{
					zapis_do_pliku(pierwszy_album);
					
					}
				//wyjscie
				else if((wybrany / 100)==0 && (wybrany % 100)==3)
					{
						zwolnienie_pamieci(pierwszy_album);
						destroyCDKScreen (ekran);
						endCDK ();
						endwin();
						return 0;
							
					}
			}
		destroyCDKScreen (ekran);
		endCDK ();
		endwin();
		return 0;
		
		
	}
	

/*!
* \fn void menu(CDKSCREEN *ekran,WINDOW *okno, int *wybrany)
* \brief Funkcja odpowiadajaca za graficzne menu uzytkownika
* \param ekran - ekran do pracy dla CDK
* \param okno - okno do pracy dla CDK
* \param wybrany - wybor opcji menu
* \return void
*/
void menu(CDKSCREEN *ekran,WINDOW *okno, int *wybrany)
{ 
	CDKLABEL *info;
	CDKMENU *menu;
	int rozmiar_submenu[3]={5,6,4}, pozycja_submenu[3]={LEFT,LEFT,RIGHT};
	const char *tekst[2]={"                                                    ",
						"                                                    "};

	//CURSES setup
	start_color();
	noecho();
	curs_set(0);

    //TEKST
	elementy_menu[0][0] = "</B>Baza danych<!B>";
	elementy_menu[0][1] = "</B>Wyswietl spis<!B>";
	elementy_menu[0][2] = "</B>Wyszukaj plyte<!B>";
	elementy_menu[0][3] = "</B>Sortuj i wyswietl<!B>";
	elementy_menu[0][4] = "</B>Wyjscie<!B>";

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
	endwin();
	eraseCDKScreen(ekran);
   
}

/*!
* \fn funcja_zwrotna (EObjectType cdktype GCC_UNUSED, void *object,
			    void *clientData,
			    chtype input GCC_UNUSED)
* \brief Funkcja niezbedna do funkcjonowania menu - wywolywana po kazdym ruchu uzytkownika w menu
* \return 0 przy poprawnym wywolaniu
*/
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

/*!
* \fn *trim(char *str)
* \brief Funkcja "przycina" spacje ktorymi uzupelniane sa lancuchy danych. 
* Potrzebna by poprawnie procesowac dane wprowadzane w formy przy dodawaniu i edycji plyt.
* \param str - konkretny lancuch, z ktorego chcemy usunac puste spacje na jego koncu, badz poczatku.
* \return "przyciety" lancuch
*/
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

/*!
* \fn forma_dodawanie_elementu(char *temp_tytul, char *temp_artysta, char *temp_gatunek, int *temp_rok, int *temp_l_utworow)
* \brief Funkcja pobierajaca dane o nowej plycie od uzytkownika w celu dodania jej do listy (bazy danych)
* \param temp_tytul - lancuch z tytulem plyty/plyt 
* \param temp_artysta - lancuch z artysta plyty/plyt 
* \param temp_gatunek - lancuch z gatunkiem plyty/plyt 
* \param temp_rok - rok wydania
* \param temp_l_utworow - liczba utworow 
* \return liczba 0 w razie poprawnego wywolania
*/
int forma_dodawanie_elementu(char *temp_tytul, char *temp_artysta, char *temp_gatunek, int *temp_rok, int *temp_l_utworow)
	{	FIELD *pola[N];
		FORM  *formularz;
		char *etykieta[N-1]={"Nazwa albumu:","Artysta:","Gatunek:","Rok wydania:","Ilosc utworow:"};
		int ch,wiersze,kolumny;
		
		//CURSES setup
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
/*!
* \fn forma_edycja_elementu(char *temp_tytul, char *temp_artysta, char *temp_gatunek, int *temp_rok, int *temp_l_utworow)
* \brief Funkcja wyswietlajaca dane edytowanej plyty i pobierajaca nowe dane
* \param temp_tytul - lancuch z tytulem plyty/plyt 
* \param temp_artysta - lancuch z artysta plyty/plyt 
* \param temp_gatunek - lancuch z gatunkiem plyty/plyt 
* \param temp_rok - rok wydania
* \param temp_l_utworow - liczba utworow 
* \return liczba 0 w razie poprawnego wywolania
*/	
int forma_edycja_elementu(char *temp_tytul, char *temp_artysta, char *temp_gatunek, int *temp_rok, int *temp_l_utworow)
	{	
		FIELD *pola[N];
		FORM  *formularz;
		char *etykieta[N-1]={"Nazwa albumu:","Artysta:","Gatunek:","Rok wydania:","Ilosc utworow:"};
		char rok_lancuch[ROZMIAR], liczba_lancuch[ROZMIAR];
		int ch,wiersze,kolumny;
		
		//CURSES setup
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
		{	
			switch(ch)
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
/*!
* \fn dodanie_nowego_elementu(WskaznikNaElement pierwszy_album, char *t, char *a, char *g, int r, int l)
* \brief Funkcja dodajaca element do bazy danych (dodawanie elementu do listy jednokierunkowej)
* \param pierwszy_album - wskaznik pierwszy element listy jednokierunkowej
* \param t - lancuch z tytulem plyty ktora uzytkownik chce dodac
* \param a - lancuch z artysta plyty ktora uzytkownik chce dodac
* \param g - lancuch z gatunkiem plyty ktora uzytkownik chce dodac
* \param r - lancuch z rokiem wydania plyty ktora uzytkownik chce dodac
* \param l - lancuch z liczba utworow na plycie ktora uzytkownik chce dodac
* \return pierwszy_album - wskaznik pierwszy element listy jednokierunkowej
*/
	
WskaznikNaElement dodanie_nowego_elementu(WskaznikNaElement pierwszy_album, char *t, char *a, char *g, int r, int l)
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
	
/*!
* \fn wyswietlenie_calosci(CDKSCREEN *ekran, WskaznikNaElement pierwszy_album)
* \brief Funkcja wyswietla baze danych
* \details Tworzy pad o wiekszych rozmiarach niz ekran urzadzenia, 
* wyswietla dane i umozliwia scorllowanie/ poruszanie sie strzalkami w celu ogladania danych
* \param ekran - ekran do pracy dla CDK
* \param pierwszy_album - wskaznik pierwszy element listy jednokierunkowej
* \return liczba 0 w razie poprawnego wywolania
*/

int wyswietlenie_calosci(CDKSCREEN *ekran, WskaznikNaElement pierwszy_album)
	{
		WskaznikNaElement biezacy_album=pierwszy_album;
		const char *tekst[3]={"strzalka w dol - przewijanie listy w dol                                 ",
							"strzalka w gore - przewijanie listy w gore                                ",
							"F5 - wyjscie do menu glownego                                            "};
		int mypadpos = 0, ch;
		int mrow, mcol=70, rowcount =100;
		WINDOW *pad;
		CDKLABEL *info;
	
		//CURSES setup
		keypad(stdscr, TRUE);
		start_color();
		getmaxyx(stdscr, mrow, mcol);
		curs_set(0);
		pad = newpad (rowcount + 1, mcol);
		ekran = initCDKScreen (pad);
		info = newCDKLabel (ekran, RIGHT, TOP, (CDK_CSTRING2) tekst, 3, TRUE, FALSE);
	
	
		//DANE
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
		refreshCDKScreen (ekran);
			
		// MENU  
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
		return 0;
	}
/*!
* \fn wyswietlenie_wyszukania(CDKSCREEN *ekran,WskaznikNaElement pierwszy_album, int wybor)
* \brief Funkcja wyswietlajaca wynik wyszukania plyty/plyt przez uzytkownika
* \details Tworzy pad o wiekszych rozmiarach niz ekran urzadzenia, 
* wyswietla dane i umozliwia scorllowanie/ poruszanie sie strzalkami w celu ogladania danych
* \param ekran - ekran do pracy dla CDK
* \param pierwszy_album - wskaznik pierwszy element listy jednokierunkowej
* \param wybor - wartosc zwracana przez funkcje dialog_2 potrzebna do instrukcji sterujacej wywolaniem funkcji wyszukanie_elementu.
* \return liczba 0 w razie poprawnego wywolania
*/	
int wyswietlenie_wyszukania(CDKSCREEN *ekran,WskaznikNaElement pierwszy_album, int wybor)
   {
	
		WINDOW *pad;
		CDKLABEL *info;
		int mypadpos = 0, ch, szukana_dana;
		char temp_tytul[ROZMIAR], zapychacz[ROZMIAR]="stolzpowylamywanymi";
		const char *tekst[3]={"strzalka w dol - przewijanie listy w dol                                 ",
							"strzalka w gore - przewijanie listy w gore                                ",
							"F5 - wyjscie do menu glownego                                            "};
		int mrow, mcol=70, rowcount =100;
		
		if (wybor==0) 
			{
				 strcpy(temp_tytul,pobor_danych(ekran,"Wpisz tytul plyty do wyszukania",temp_tytul));
			}
		else if (wybor==1) 
			{
				strcpy(temp_tytul,pobor_danych(ekran,"Wpisz artyste, ktorego plyty szukasz",temp_tytul));
			}
		else if (wybor==2) 
			{
				strcpy(temp_tytul,pobor_danych(ekran,"Wpisz gatunek plyt, ktorych szukasz",temp_tytul));
			}
		else if (wybor==3) 
			{
				szukana_dana=atoi(pobor_danych(ekran,"Wpisz rok wydania plyt, ktorych szukasz",temp_tytul));		 
			}	
		else if (wybor==4) 
			{
				szukana_dana=atoi(pobor_danych(ekran,"Wpisz liczbe utworow na plytach, ktorych szukasz",temp_tytul));		 
			}
		else if (wybor==5) 
			{
				szukana_dana=atoi(pobor_danych(ekran,"Wpisz ID plyty ktorej szukasz",temp_tytul));		 
			}
		
		
		//CURSES setup
		keypad(stdscr, TRUE);
		start_color();
		getmaxyx(stdscr, mrow, mcol);
		curs_set(0);
		pad = newpad (rowcount + 1, mcol);
		ekran = initCDKScreen (pad);
		info = newCDKLabel (ekran, RIGHT, TOP, (CDK_CSTRING2) tekst, 3, TRUE, FALSE);
		
		///DANE
		if (wybor==0) 
			{
				wyszukanie_elementu( pierwszy_album, temp_tytul, zapychacz, zapychacz, K, K, K,pad);		 
			}
		else if (wybor==1) 
			{
				wyszukanie_elementu( pierwszy_album, zapychacz,temp_tytul, zapychacz, K, K, K,pad);		 
			}
		else if (wybor==2) 
			{
				wyszukanie_elementu( pierwszy_album, zapychacz, zapychacz, temp_tytul, K, K, K,pad);		 
			}
		else if (wybor==3) 
			{
				wyszukanie_elementu( pierwszy_album, zapychacz, zapychacz, zapychacz,szukana_dana, K, K,pad);		 
			}	
		else if (wybor==4) 
			{
				wyszukanie_elementu( pierwszy_album, zapychacz, zapychacz, zapychacz, K,szukana_dana , K,pad);		 
			}
		else if (wybor==5) 
			{
				wyszukanie_elementu( pierwszy_album, zapychacz, zapychacz, zapychacz, K, K, szukana_dana,pad);		 
			}


		prefresh(pad, mypadpos, 0, 0, 0, 50, mcol);
		refreshCDKScreen (ekran);
	
    
		// MENU  
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
		return 0;
	}

/*!
* \fn dialog_1 (CDKSCREEN *ekran, int argc, char **argv, int *wybor)
* \brief Funkcja dialog_1 to okno dialogowe - skladowa funkcjonalnosci EDYCJI danych plyty
* \details Wyswietla menu i pozwala uzytkownikowi wybrac sposob w jaki ten chce znalezc plyte do edycji
* \param ekran - ekran do pracy dla CDK
* \param argc - liczba pobranych argumentow(opcje uruchamiania, nazwa pliku) przy wlaczaniu programu
* \param argv - tablica lancuchow z wartosciami opcji uruchamiania i nazwa pliku
* \param wybor - wartosc int mowiaca o wyborze uzytkownika
* \return liczba 0 w razie poprawnego wywolania
*/
int dialog_1 (CDKSCREEN *ekran, int argc, char **argv, int *wybor)
	{
	   
		CDKSCREEN *cdkscreen = 0;
		CDKDIALOG *question  = 0;
		const char *buttons[] =
		{"</B16>Tytul", "</B16>ID"};
		const char *message[10];
	 
		//CURSES setup
		CDK_PARAMS params;
		CDKparseParams (argc, argv, &params, CDK_MIN_PARAMS);
		cdkscreen = ekran;
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
			endwin();
			eraseCDKScreen(ekran);
			printf ("Za male okno terminala\n");
			return 0;
		}

		//Odpowiedz
		*wybor = activateCDKDialog (question, 0);

	 
		destroyCDKDialog (question);
		endwin();
		eraseCDKScreen(ekran);
		return 0;
	   
	}
/*!
* \fn dialog_2 (CDKSCREEN *ekran, int argc, char **argv, int *wybor)
* \brief Funkcja dialog_2 to okno dialogowe - skladowa funkcjonalnosci WYSZUKIWANIA konkretnej plyty\plyt
* \details Wyswietla menu i pozwala uzytkownikowi wybrac sposob w jaki ten chce wyszukiwac plyte/plyty
* \param ekran - ekran do pracy dla CDK
* \param argc - liczba pobranych argumentow(opcje uruchamiania, nazwa pliku) przy wlaczaniu programu
* \param argv - tablica lancuchow z wartosciami opcji uruchamiania i nazwa pliku
* \param wybor - wartosc int mowiaca o wyborze uzytkownika
* \return liczba 0 w razie poprawnego wywolania
*/
int dialog_2 (CDKSCREEN *ekran,int argc, char **argv, int *wybor)	
	{
	   
		CDKSCREEN *cdkscreen = 0;
		CDKDIALOG *question  = 0;
		const char *buttons[] =
		{"</B16>Tytul","</B16>Artysta","</B16>Gatunek","</B16>Rok wydania","</B16>Liczba utworow", "</B16>ID"};
		const char *message[10];
	 
		//CURSES setup
		CDK_PARAMS params;
		CDKparseParams (argc, argv, &params, CDK_MIN_PARAMS);
		cdkscreen = ekran;
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
			endwin();
			eraseCDKScreen(ekran);
			printf ("Za male okno terminala\n");
			return 0;
		}

		//Odpowiedz
		*wybor = activateCDKDialog (question, 0);

	 
		destroyCDKDialog (question);
		endwin();
		eraseCDKScreen(ekran);
		return 0;
	   
	}
/*!
* \fn dialog_3 (CDKSCREEN *ekran, int argc, char **argv, int *wybor)
* \brief Funkcja dialog_3 to okno dialogowe - skladowa funkcjonalnosci SORTOWANIA bazy danych
* \details Wyswietla menu i pozwala uzytkownikowi wybrac dane plyty po ktorej ten chce sortowac baze danych
* \param ekran - ekran do pracy dla CDK
* \param argc - liczba pobranych argumentow(opcje uruchamiania, nazwa pliku) przy wlaczaniu programu
* \param argv - tablica lancuchow z wartosciami opcji uruchamiania i nazwa pliku
* \param wybor - wartosc int mowiaca o wyborze uzytkownika
* \return liczba 0 w razie poprawnego wywolania
*/
int dialog_3 (CDKSCREEN *ekran,int argc, char **argv, int *wybor)	
	{
	   
		CDKSCREEN *cdkscreen = 0;
		CDKDIALOG *question  = 0;
		const char *buttons[] =
		{"</B16>Tytul","</B16>Artysta","</B16>Gatunek","</B16>Rok wydania","</B16>Liczba utworow"};
		const char *message[10];
	 
		//CURSES setup
		CDK_PARAMS params;
		CDKparseParams (argc, argv, &params, CDK_MIN_PARAMS);
		cdkscreen = ekran;
		curs_set(0);
		/* Create the message within the dialog box. */
		message[0] = "<C></B>Sortowanie bazy danych";
		message[1] = " ";
		message[2] = " ";
		message[3] = "<C>Aby posortowac plyty wybierz pole, ";
		message[4] = "<C>wedlug ktorego chcesz przeprowadzic sortowanie";
		message[5] = " ";
		message[6] = " ";
		/* Create the dialog box. */
		question = newCDKDialog (cdkscreen,
					CDKparamValue (&params, 'X', CENTER),
					CDKparamValue (&params, 'Y', CENTER),
					(CDK_CSTRING2) message, 7,
					(CDK_CSTRING2) buttons, 5,
					COLOR_PAIR (2) | A_REVERSE,
					TRUE,
					CDKparamValue (&params, 'N', TRUE),
					CDKparamValue (&params, 'S', FALSE));

		/* Check if we got a null value back. */
		if (question == 0)
		{
			/* Shut down Cdk. */
			endwin();
			eraseCDKScreen(ekran);
			printf ("Za male okno terminala\n");
			return 0;
		}

		//Odpowiedz
		*wybor = activateCDKDialog (question, 0);

	 
		destroyCDKDialog (question);
		endwin();
		eraseCDKScreen(ekran);
		return 0;
	   
	}

/*!
* \fn dialog_4 (CDKSCREEN *ekran, int argc, char **argv, int *wybor)
* \brief Funkcja dialog_4 to okno dialogowe - skladowa funkcjonalnosci SORTOWANIA bazy danych
* \details Wyswietla menu i pozwala uzytkownikowi wybrac sposob w jaki ten chce sortowac baze danych - malejaco, lub rosnaco
* \param ekran - ekran do pracy dla CDK
* \param argc - liczba pobranych argumentow(opcje uruchamiania, nazwa pliku) przy wlaczaniu programu
* \param argv - tablica lancuchow z wartosciami opcji uruchamiania i nazwa pliku
* \param wybor - wartosc int mowiaca o wyborze uzytkownika
* \return liczba 0 w razie poprawnego wywolania
*/
int dialog_4 (CDKSCREEN *ekran,int argc, char **argv, int *wybor)
	{
	   
		CDKSCREEN *cdkscreen = 0;
		CDKDIALOG *question  = 0;
		const char *buttons[] =
		{"</B16>Malejaco","</B16>Rosnaco"};
		const char *message[10];
	 
		//CURSES setup
		CDK_PARAMS params;
		CDKparseParams (argc, argv, &params, CDK_MIN_PARAMS);
		cdkscreen = ekran;
		curs_set(0);
		/* Create the message within the dialog box. */
		message[0] = "<C></B>Sortowanie bazy danych";
		message[1] = " ";
		message[2] = " ";
		message[3] = "<C>Wybierz w jaki sposob chcesz posortowac plyty";
		message[4] = "<C>";
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
			endwin();
			eraseCDKScreen(ekran);
			printf ("Za male okno terminala\n");
			return 0;
		}

		//Odpowiedz
		*wybor = activateCDKDialog (question, 0);

	 
		destroyCDKDialog (question);
		endwin();
		eraseCDKScreen(ekran);
		return 0;
	   
	}

/*!
* \fn pobor_danych (CDKSCREEN *ekran,const char *title, char *info)
* \brief Funkcja pobierajaca lancuch danych od uzytkownika
* \param ekran - ekran do pracy dla CDK
* \param title - lancuch informujacy uzytkownika o jakie dane ten jest proszony
* \param info - dane wprowadzone
* \return info - lancuch wprowadzonych danych
*/
char *pobor_danych (CDKSCREEN *ekran,const char *title, char *info)
	{
		CDKSCREEN *cdkscreen = 0;
		CDKMENTRY *widget    = 0;
		const char *label    = "</R>:";
 
		//CURSES SETUP
		cdkscreen = ekran;
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
	
		if (widget == 0)
			{
				endwin();
				eraseCDKScreen(ekran);
				printf ("Za male okno terminala\n");
			}

			refreshCDKScreen (cdkscreen);
			activateCDKMentry (widget, 0);
			info = strdup (widget->info);
			destroyCDKMentry (widget);
			endwin();
			eraseCDKScreen(ekran);

		return info;
	}



/*!
* \fn usuniecie_elementu(WskaznikNaElement pierwszy_album, char *tytul_do_usuniecia)
* \brief Funkcja usuwajaca element z bazy danych (usuniecie elementu listy jednokierunkowej)
* \param pierwszy_album - wskaznik pierwszy element listy jednokierunkowej
* \param tytul_do_usuniecia - lancuch z tytulem plyty ktora uzytkownik chce usunac
* \return pierwszy_album - wskaznik pierwszy element listy jednokierunkowej
*/

WskaznikNaElement usuniecie_elementu(WskaznikNaElement pierwszy_album, char *tytul_do_usuniecia)
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
		printf("Usunięto album %s artysty %s\n", tytul_do_usuniecia, tymczasowy_artysta);
		return pierwszy_album;
	}
/*!
* \fn zwolnienie_pamieci(WskaznikNaElement pierwszy_album)
* \brief Funkcja zwalniajaca uprzednio zaalokowana pamiec dla listy jednokierunkowej struktur (plyt)
* \param pierwszy_album - wskaznik pierwszy element listy jednokierunkowej
* \return pierwszy_album - wskaznik pierwszy element listy jednokierunkowej
*/
WskaznikNaElement zwolnienie_pamieci(WskaznikNaElement pierwszy_album)
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

/*!
* \fn edycja_danych(WskaznikNaElement pierwszy_album, char *tytul_do_wyszukania, int id_do_wyszukania)
* \brief Funkcja edytujaca dane wyszukanej struktury 
* \details Funkcja spajaja funkcje wyszukanie_elementu_do_edycji i forma_edycja_elementu oraz podmieniajaca dane w edytytowanej strukturze (plycie)
* \param tytul_do_wyszukania - lancuch z tytulem plyty/plyt ktora uzytkownik chce wyszukac
* \param id_do_wyszukania - wartosc id do wyszukania
* \return void
*/
void edycja_danych(WskaznikNaElement pierwszy_album, char *tytul_do_wyszukania, int id_do_wyszukania)
	{
		
		WskaznikNaElement plyta_edytowana=NULL;
		char temp_tytul[ROZMIAR], temp_artysta[ROZMIAR], temp_gatunek[ROZMIAR];
		int temp_rok, temp_l_utworow;
		if	(wyszukanie_elementu_edycja(pierwszy_album, tytul_do_wyszukania, id_do_wyszukania)!=NULL)
					{	
						plyta_edytowana=wyszukanie_elementu_edycja(pierwszy_album, tytul_do_wyszukania, id_do_wyszukania);
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
/*!
* \fn wyszukanie_elementu_edycja(WskaznikNaElement pierwszy_album, char *tytul_do_wyszukania, int id_do_wyszukania)	
* \brief Funkcja wyszukujaca element do edycji z listy struktur (plyt) po zadanym przez uzytkownika polu (tytule lub id)
* \param pierwszy_album - wskaznik pierwszy element listy jednokierunkowej
* \param tytul_do_wyszukania - lancuch z tytulem plyty/plyt ktora uzytkownik chce wyszukac
* \param id_do_wyszukania - wartosc id do wyszukania
* \return pierwszy_album - wskaznik pierwszy element listy jednokierunkowej
*/	
WskaznikNaElement wyszukanie_elementu_edycja(WskaznikNaElement pierwszy_album, char *tytul_do_wyszukania, int id_do_wyszukania)				 
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
/*!
* \fn wyszukanie_elementu(WskaznikNaElement pierwszy_album, char *tytul_do_wyszukania, char *artysta_do_wyszukania, char *gatunek_do_wyszukania, int rok_do_wyszukania, int l_utworow_do_wyszukania, int id_do_wyszukania, WINDOW *pad)				 
* \brief Funkcja wyszukujaca element z listy struktur (plyt) po zadanym przez uzytkownika polu
* \param pierwszy_album - wskaznik pierwszy element listy jednokierunkowej
* \param tytul_do_wyszukania - lancuch z tytulem plyty/plyt ktora uzytkownik chce wyszukac
* \param artysta_do_wyszukania - lancuch z artysta plyty/plyt ktora uzytkownik chce wyszukac
* \param gatunek_do_wyszukania - lancuch z gatunkiem plyty/plyt ktora uzytkownik chce wyszukac
* \param rok_do_wyszukania - rok po ktorym plyty maja byc wyszukane
* \param l_utworow_do_wyszukania - liczba utworow po ktorej plyty maja byc wyszukane
* \param id_do_wyszukania - wartosc id do wyszukania
* \param okno - okno do pracy dla CDK
* \return pierwszy_album - wskaznik pierwszy element listy jednokierunkowej
*/	
WskaznikNaElement wyszukanie_elementu(WskaznikNaElement pierwszy_album, char *tytul_do_wyszukania, char *artysta_do_wyszukania, char *gatunek_do_wyszukania, int rok_do_wyszukania, int l_utworow_do_wyszukania, int id_do_wyszukania, WINDOW *pad)				 
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

/*!
* \fn wybor_pliku (CDKSCREEN *ekran,char *nazwa_pliku)
* \brief Funkcja umozliwiajaca wybor pliku z dysku - skladowa funkcjonalnosci WCZYTYWANIA bazy danych
* \details Wyswietla viewer i pozwala wybrac dowolny plik z dysku
* \param ekran - ekran do pracy dla CDK
* \param nazwa_pliku - adres wybranego pliku na dysku
* \return nazwa_pliku - adres wybranego pliku na dysku
*/

char *wybor_pliku (CDKSCREEN *ekran,char *nazwa_pliku)
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
		cdkscreen = ekran;
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
				endwin();
				eraseCDKScreen(ekran);
				fprintf (stderr, "Nie udalo sie stworzyc funkcji\n");
				return NULL;
			}

		filename = activateCDKFselect (fSelect, 0);
		if (fSelect->exitType == vESCAPE_HIT)
			{
				destroyCDKFselect (fSelect);
				endwin();
				eraseCDKScreen(ekran);
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
		  endwin();
	   eraseCDKScreen(ekran);

		  printf ("Za male okno?\n");
		  return NULL;
	   }

	   /* otwarcie pliku i wysw zawartosci */
	   lines = CDKreadFile (filename, &info);
	   if (lines == -1)
	   {
		  filename = copyChar (filename);

		  destroyCDKFselect (fSelect);
		  endwin();
	   eraseCDKScreen(ekran);

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
	  endwin();
	   eraseCDKScreen(ekran);
	   
	   return nazwa_pliku;
	}


/*!
* \fn wczytanie_do_struktury(WskaznikNaElement pierwszy_album,char *nazwa_pliku)
* \brief Funkcja umozliwiajaca wczytanie bazy plyt z pliku
* \param pierwszy_album - wskaznik pierwszy element listy jednokierunkowej
* \param nazwa_pliku - adres wybranego pliku na dysku
* \return pierwszy_album - wskaznik pierwszy element listy jednokierunkowej
*/
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
		pierwszy_album=dodanie_nowego_elementu(pierwszy_album,temp_tytul,temp_artysta,temp_gatunek,temp_rok_wydania,temp_l_utworow);
		}  
		fclose(wybrany_plik);
		return pierwszy_album;
	}


/*!
* \fn zapis_do_pliku(WskaznikNaElement pierwszy_album)
* \brief Funkcja umozliwiajaca zapisanie bazy danych z programu do pliku na dysku (do katalogu zrodlowego programu)
* \param pierwszy_album - wskaznik pierwszy element listy jednokierunkowej
* \return liczba 0 w razie poprawnego wywolania
*/
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

