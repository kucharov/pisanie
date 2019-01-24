/*!
* \file sortowanie.c
* \brief     Plik z funkcjami sortujacymi programu PP
* \author    Konrad Kucharczyk
* \version   0.1
* \date      16.01.2019
* \copyright Praca i wlasnosc Konrada Kucharczyka
*/

#include "graficzny.h"

/*!
* \fn sortowanie(CDKSCREEN *ekran,WskaznikNaElement pierwszy_album, int wybor1, int wybor2)
* \brief Funkcja sortujaca i wyswietlajaca posortowane elementy listy (bazy danych)
* \param ekran - ekran do pracy dla CDK
* \param pierwszy_album - wskaznik pierwszy element listy jednokierunkowej
* \param wybor1 - wybor uzytkownika z okna dialog_3 - mowi o polu po ktorym sortowac
* \param wybor2 - wybor uzytkownika z okna dialog_4 - mowi o kolejnosci sortowania malejaco, rosnaco
* \return liczba 0 w razie poprawnego wywolania
*/
int sortowanie(CDKSCREEN *ekran,WskaznikNaElement pierwszy_album, int wybor1, int wybor2)
	{
		WINDOW *pad;
		CDKLABEL *info;
		int mypadpos = 0, ch;
		int l_elementow=pierwszy_album->id, i=0;
		int mrow, mcol=70, rowcount =100;
		WskaznikNaElement konwertowany=pierwszy_album;
		struct Element tablica_struktur[l_elementow];  //tablica VLA struktur
		const char *tekst[3]={"strzalka w dol - przewijanie listy w dol                                 ",
						"strzalka w gore - przewijanie listy w gore                                ",
						"F5 - wyjscie do menu glownego                                            "};
		
		//konwersja listy do tablicy
		for(i=0; i<l_elementow; i++)
			{
				tablica_struktur[i]=*konwertowany;
				pierwszy_album=pierwszy_album->nastepny_album;
				konwertowany=pierwszy_album;
			}
		
		if (wybor1==0) 
		{
			 if (wybor2==0) qsort(tablica_struktur,l_elementow, sizeof(struct Element),Rsortuj_tytul);
			 else if (wybor2==1) qsort(tablica_struktur,l_elementow, sizeof(struct Element),Msortuj_tytul);
		}
		else if (wybor1==1) 
		{
			if (wybor2==0) qsort(tablica_struktur,l_elementow, sizeof(struct Element),Rsortuj_artysta);
			else if (wybor2==1) qsort(tablica_struktur,l_elementow, sizeof(struct Element),Msortuj_artysta);
		}
		else if (wybor1==2) 
		{
			if (wybor2==0) qsort(tablica_struktur,l_elementow, sizeof(struct Element),Rsortuj_gatunek);
			else if (wybor2==1) qsort(tablica_struktur,l_elementow, sizeof(struct Element),Msortuj_gatunek);
		}
		else if (wybor1==3) 
		{
			if (wybor2==0) qsort(tablica_struktur,l_elementow, sizeof(struct Element),Rsortuj_rok);
			else if (wybor2==1) qsort(tablica_struktur,l_elementow, sizeof(struct Element),Msortuj_rok);		 
		}	
		else if (wybor1==4) 
		{
			if (wybor2==0) qsort(tablica_struktur,l_elementow, sizeof(struct Element),Rsortuj_l_utworow);
			else if (wybor2==1) qsort(tablica_struktur,l_elementow, sizeof(struct Element),Msortuj_l_utworow);		 
		}
		//CURSES setup
		keypad(stdscr, TRUE);
		start_color();
		getmaxyx(stdscr, mrow, mcol);
		curs_set(0);
		pad = newpad (rowcount + 1, mcol);
		ekran = initCDKScreen (pad);
		info = newCDKLabel (ekran, RIGHT, TOP, (CDK_CSTRING2) tekst, 3, TRUE, FALSE);
		//wyswietlanie posortowania
		for (i=0;i<l_elementow;i++)
			{
				wprintw(pad,"ID: %d\n\n",tablica_struktur[i].id);
				wprintw(pad,"\nTytul: %s\n", tablica_struktur[i].tytul );
				wprintw(pad,"Artysta: %s\n", tablica_struktur[i].artysta );
				wprintw(pad,"Gatunek: %s\n", tablica_struktur[i].gatunek );
				wprintw(pad,"Rok wydania: %d\n", tablica_struktur[i].rok );
				wprintw(pad,"Liczba utworow na plycie: %d\n\n", tablica_struktur[i].l_utworow );
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
* \fn Msortuj_rok(const void * a, const void * b)
* \brief Funkcja porownujaca dla funkcji qsort
* \details Porownuje pola "rok" listy i daje funkcji qsort
* taka informacje, zeby ten sortowal malejaco
* \param a - pierwszy porownywany element
* \param b - drugi porownywany element
* \return liczba 0 w razie rownosci elementow porownywanych
* liczba -1 gdy el1 jest mniejszy od el2
* liczba 1 gdy el1 jest wiekszy od el2 
*/
int Msortuj_rok(const void * a, const void * b)
	{
		const WskaznikNaElement el1=a;
		const WskaznikNaElement el2=b;
		
		if (el1->rok<el2->rok) return -1;
		else if (el1->rok==el2->rok)
		return 0;
		else
		return 1;
	}
/*!
* \fn Msortuj_l_utworow(const void * a, const void * b)
* \brief Funkcja porownujaca dla funkcji qsort
* \details Porownuje pola "l_utworow" listy i daje funkcji qsort
* taka informacje, zeby ten sortowal malejaco
* \param a - pierwszy porownywany element
* \param b - drugi porownywany element
* \return liczba 0 w razie rownosci elementow porownywanych
* liczba -1 gdy el1 jest mniejszy od el2
* liczba 1 gdy el1 jest wiekszy od el2 
*/
int Msortuj_l_utworow(const void * a, const void * b)
	{
		const WskaznikNaElement el1=a;
		const WskaznikNaElement el2=b;

		if (el1->l_utworow<el2->l_utworow) return -1;
		else if (el1->l_utworow==el2->l_utworow)
		return 0;
		else
		return 1;
	}
/*!
* \fn Msortuj_tytul (const void * a, const void * b)
* \brief Funkcja porownujaca dla funkcji qsort
* \details Porownuje pola "tytul" listy i daje funkcji qsort
* taka informacje, zeby ten sortowal malejaco
* \param a - pierwszy porownywany element
* \param b - drugi porownywany element
* \return liczba 0 w razie rownosci elementow porownywanych
* liczba -1 gdy el1 jest mniejszy od el2
* liczba 1 gdy el1 jest wiekszy od el2 
*/
int Msortuj_tytul (const void * a, const void * b)
	{
		const WskaznikNaElement el1=a;
		const WskaznikNaElement el2=b;
		return strcmp(el1->tytul,el2->tytul);
		return 0;
	}
/*!
* \fn Msortuj_artysta (const void * a, const void * b)
* \brief Funkcja porownujaca dla funkcji qsort
* \details Porownuje pola "artysta" listy i daje funkcji qsort
* taka informacje, zeby ten sortowal malejaco
* \param a - pierwszy porownywany element
* \param b - drugi porownywany element
* \return liczba 0 w razie rownosci elementow porownywanych
* liczba -1 gdy el1 jest mniejszy od el2
* liczba 1 gdy el1 jest wiekszy od el2 
*/
int Msortuj_artysta (const void * a, const void * b)
	{
		const WskaznikNaElement el1=a;
		const WskaznikNaElement el2=b;
		return strcmp(el1->artysta,el2->artysta);
		return 0;
	}
/*!
* \fn Msortuj_gatunek (const void * a, const void * b)
* \brief Funkcja porownujaca dla funkcji qsort
* \details Porownuje pola "gatunek" listy i daje funkcji qsort
* taka informacje, zeby ten sortowal malejaco
* \param a - pierwszy porownywany element
* \param b - drugi porownywany element
* \return liczba 0 w razie rownosci elementow porownywanych
* liczba -1 gdy el1 jest mniejszy od el2
* liczba 1 gdy el1 jest wiekszy od el2 
*/	
int Msortuj_gatunek (const void * a, const void * b)
	{
		const WskaznikNaElement el1=a;
		const WskaznikNaElement el2=b;
		return strcmp(el1->gatunek,el2->gatunek);
		return 0;
	}
	
/*!
* \fn Rsortuj_rok(const void * a, const void * b)
* \brief Funkcja porownujaca dla funkcji qsort
* \details Porownuje pola "rok" listy i daje funkcji qsort
* taka informacje zeby ten sortowal rosnaco
* \param a - pierwszy porownywany element
* \param b - drugi porownywany element
* \return liczba 0 w razie rownosci elementow porownywanych
* liczba 1 gdy el1 jest mniejszy od el2
* liczba -1 gdy el1 jest wiekszy od el2 
*/	
int Rsortuj_rok(const void * a, const void * b)
	{
		const WskaznikNaElement el1=a;
		const WskaznikNaElement el2=b;
		
		if (el1->rok<el2->rok) return 1;
		else if (el1->rok==el2->rok)
		return 0;
		else
		return -1;
	}
/*!
* \fn Rsortuj_l_utworow(const void * a, const void * b)
* \brief Funkcja porownujaca dla funkcji qsort
* \details Porownuje pola "l_utworow" listy i daje funkcji qsort
* taka informacje, zeby ten sortowal rosnaco
* \param a - pierwszy porownywany element
* \param b - drugi porownywany element
* \return liczba 0 w razie rownosci elementow porownywanych
* liczba 1 gdy el1 jest mniejszy od el2
* liczba -1 gdy el1 jest wiekszy od el2 
*/
int Rsortuj_l_utworow(const void * a, const void * b)
	{
		const WskaznikNaElement el1=a;
		const WskaznikNaElement el2=b;

		if (el1->l_utworow<el2->l_utworow) return 1;
		else if (el1->l_utworow==el2->l_utworow)
		return 0;
		else
		return -1;
	}
/*!
* \fn Rsortuj_tytul (const void * a, const void * b)
* \brief Funkcja porownujaca dla funkcji qsort
* \details Porownuje pola "tytul" listy i daje funkcji qsort
* taka informacje, zeby ten sortowal rosnaco
* \param a - pierwszy porownywany element
* \param b - drugi porownywany element
* \return liczba 0 w razie rownosci elementow porownywanych
* liczba 1 gdy el1 jest mniejszy od el2
* liczba -1 gdy el1 jest wiekszy od el2 
*/
int Rsortuj_tytul (const void * a, const void * b)
	{
		const WskaznikNaElement el1=a;
		const WskaznikNaElement el2=b;
		if (strcmp(el1->tytul,el2->tytul)!=0) return -strcmp(el1->tytul,el2->tytul);
		else return 0;
	}
/*!
* \fn Rsortuj_artysta (const void * a, const void * b)
* \brief Funkcja porownujaca dla funkcji qsort
* \details Porownuje pola "artysta" listy i daje funkcji qsort
* taka informacje, zeby ten sortowal rosnaco
* \param a - pierwszy porownywany element
* \param b - drugi porownywany element
* \return liczba 0 w razie rownosci elementow porownywanych
* liczba 1 gdy el1 jest mniejszy od el2
* liczba -1 gdy el1 jest wiekszy od el2 
*/
int Rsortuj_artysta (const void * a, const void * b)
	{
		const WskaznikNaElement el1=a;
		const WskaznikNaElement el2=b;
		if (strcmp(el1->artysta,el2->artysta)!=0) return -strcmp(el1->artysta,el2->artysta);
		else return 0;
	}
/*!
* \fn Rsortuj_gatunek (const void * a, const void * b)
* \brief Funkcja porownujaca dla funkcji qsort
* \details Porownuje pola "gatunek" listy i daje funkcji qsort
* taka informacje, zeby ten sortowal rosnaco
* \param a - pierwszy porownywany element
* \param b - drugi porownywany element
* \return liczba 0 w razie rownosci elementow porownywanych
* liczba 1 gdy el1 jest mniejszy od el2
* liczba -1 gdy el1 jest wiekszy od el2 
*/	
int Rsortuj_gatunek (const void * a, const void * b)
	{
		const WskaznikNaElement el1=a;
		const WskaznikNaElement el2=b;
		if (strcmp(el1->gatunek,el2->gatunek)!=0) return -strcmp(el1->gatunek,el2->gatunek);
		else return 0;
	}
