// SymBank - - symulator Banku 
// rozp. 15.12.2018
// tu musi byc wiele funkcji, budowa modularna to same plusy: D
/*0. Format pliku wejściowego
 *1. zapytanie o nazwe pliku
 * 2. pobranie danych + kontrola
 * 3. Utworzenie okienek  - list
 * 4. Wpuszczenie klientów
 * 
 * 
 * zrobione menu. generator tez, format jest
 * czas na rozwiazanie problemu pobrania danych z pliku
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 */
 
 #include <stdio.h>
 #include <stdlib.h>
 #include <string.h>
 #include <math.h>
 #include <time.h>
 


void menu(void);
double gauss(double, double); //funkcja generujaca losowe liczby o rozkladzie normalnym o podanej wartosci oczekiwanej (sredniej) i odchyleniu standardowym.
void plikwzorcowy(void);


int main(void)
{
	
//deklaracje
FILE *plik_wejsciowy;
char *nazwa_wejscia; 

//  kontakt z uzytkownikiem
do{
		menu();
		printf("\nPodaj nazwe pliku z danymi wejsciowymi(powinien znajdowac sie w katalogu roboczym)\n:   ");
		nazwa_wejscia = (char*)malloc(35 * sizeof(char));
		scanf("%s", nazwa_wejscia);
		if ((plik_wejsciowy = fopen(nazwa_wejscia, "r")) == NULL) printf("\nAlarm. Nie udalo sie odczytac pliku o podanej nazwie. Moze sie pomyliles albo jest on w innym katalogu niz program?\n)";
		free(nazwa_wejscia); // oszczedzam pamiec
	}while(wlik_wejsciowy == NULL);
	

	
	
	

//  Pobranie danych z pliku	





	
	
	
	
	
	
}








double gauss(double srednia, double odchylenie)
{
	double s, losowa1, losowa2;
	do{ 
		losowa1 = -1 + ((double)rand()/RAND_MAX) * 2;
		losowa2 = -1 + ((double)rand()/RAND_MAX) * 2; 							// https://stackoverflow.com/questions/2325472/generate-random-numbers-following-a-normal-distribution-in-c-c
		s = (losowa1 * losowa1) + (losowa2 * losowa2);}
	while (s >= 1 || s == 0);
	return srednia + (odchylenie * losowa1 * sqrt((-2*log(s)) / s));  // działa!!. 
}
	

void menu(void)
{
	int odp,kontrolawejscia, testwejscia, choragiewka = 0;
	char smietnik;
	
	
	
	for(;;)
	{
		if (choragiewka == 0) {printf("\n\n\t\t\t***SymBank - symulator kolejki w banku***\n\n\t\t\tMENU\t\t\t");
								printf("\n1 - symulacja\t\t2 - informacje o formacie pliku wejsciowego\n3 - wyjscie\n:  ");}
	
		do {
				testwejscia = 0;
				kontrolawejscia = scanf("%d", &odp);
				if ((smietnik=getchar())!='\n' || kontrolawejscia != 1) {testwejscia = 1; printf("\nNiepoprawna odpowiedz, wpisz 1, 2 lub 3. \n:   "); while((smietnik=getchar())!='\n');}
				
			}while (kontrolawejscia !=1 || testwejscia == 1 );
		
		switch (odp)
			{	
				case 1: choragiewka = 2; break;
				case 2: 
						choragiewka = 0; if (plik_wzorcowy() == 0) printf("\nW katalogu roboczym utworzylem plik z ktorego dowiesz sie wiele o formacie pliku wejsciowego do SymBanku! \nWracam do menu glownego...");
						break;
				case 3:	printf("\nDo zobaczenia!\n\n"); exit(0);
				default: printf("\nNieznana odpowiedz, wcisnij 1, 2 lub 3. \n:  "); choragiewka = 1;  	
			}
			if (choragiewka == 2) break;
		}
	}
	
	
	
	
	
	
	

int plik_wzorcowy(void)
{
	FILE *wzorzec;
	
	if ((wzorzec = fopen("SymBank_format_pliku.txt", "w")) == NULL) {printf("\nBlad tworzenia pliku wzorcowego, sprobuj jeszcze raz w innej lokalizacji.\n"); return 1;}
	
	fprintf(wzorzec, "tab          // w pierwszej linijce wpisz sposob opisywania prawdopodobienstwa liczby przychodzacych klientow: tab (tabelarycznie) lub par (parametrycznie)");
	fprintf(wzorzec, "\n0 0.1     //w przypadku tabeli: w kolejnych linijkach wypisz pary: ilosc przychodzacych klientow/minute[spacja]prawdopodobienstwo(w ulamku dziesietnym)\
			\n1 0.2\n2 0.3\n3 0.25\n4 0.15\n.      // koniec dzialu dotyczacego klientow, oddzielamy go od reszty kropka.\n");
	fprintf(wzorzec, "okienka=3         //liczba okienek w symulowanym banku, nalezy zwrocic uwage na brak spacji!");
	fprintf(wzorzec, "\n.\ntab\n2.5 0.5   //podajemy czas obslugi w kazdym okienku wraz z jego prawdopodobienstwem");
	fprintf(wzorzec, "\n3 0.5    // w przypadku formy tabelarycznej, podaj pary: czas obslugi(w minutach)[spacja]prawdopodobienstwo(w ulamku dziesietnym)");
	fprintf(wzorzec, "\n.    //kolejne okienka oddzielamy kropka \npar\nnormalny\n0     // mozemy podac parametrycznie rozklad normalny. Wtedy pierwsza podana liczba niech bedzie ");
	fprintf(wzorzec, "wartosc oczekiwana(srednia wartosc)\n20     //a druga niech bedzie odchylenie standardowe losowanych wartosci.");
	fprintf(wzorzec, "\n.\npar\nrownomierny\n0      //w przypadku rozkladu rownomiernego pierwsza liczba niech bedzie dolna granica przedzialu w ktorym losujemy czas(w minutach).\
			\n5      // druga liczba to gorna granica przedzialu.\n.");
	fclose(wzorzec);
	return 0;
	
}







