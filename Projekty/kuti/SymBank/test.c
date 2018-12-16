
#include <stdio.h>


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



int main(void)
{
	plik_wzorcowy();
	return 0;
}
