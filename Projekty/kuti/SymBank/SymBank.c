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
 * zrobione menu. generator randow musi poczekac. 
 * PAMIETAJ O FLAGACH DLA MENU
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
 


void menu(int);
double gauss(double, double); //funkcja generujaca losowe liczby o rozkladzie normalnym o podanej wartosci oczekiwanej (sredniej) i odchyleniu standardowym.
void plikwzorcowy(void);


int main(void)
{
//deklaracje

menu(0);


//Pobranie danych z pliku	
	
	
	
	
	
	
}








double gauss(double srednia, double odchylenie)
{
	srand(time(NULL));
	double losowa1 = -1 + (rand()/RAND_MAX) * 2;
	double losowa2 = -1 + (rand()/RAND_MAX) * 2; 							// https://stackoverflow.com/questions/2325472/generate-random-numbers-following-a-normal-distribution-in-c-c
	do { double s = pow(losowa1, 2) + pow(losowa2, 2);}
		while (s >= 1 || s == 0)
	return srednia + odchylenie * losowa1 * sqrt(-2*log(s) / s);// gowno, nie dziala
	
}

void menu(int flaga)
{
	int odp,kontrolawejscia, testwejscia, choragiewka = 0;
	char smietnik;
	
	
	
	for(;;)
	{
		if (choragiewka == 0) {printf("\n\n\t\t\t***SymBank - symulator kolejki w banku***\n\n\t\t\tMENU\t\t\t");
								printf("\n1 - symulacja\t\t2 - informacje o formacie pliku wejsciowego\n3 - wyjscie\n:  ");}
	
		
		
		do 
			{
				testwejscia = 0;
				kontrolawejscia = scanf("%d", &odp);
				if ((smietnik=getchar())!='\n' || kontrolawejscia != 1) {testwejscia = 1; printf("\nNiepoprawna odpowiedz, wpisz 1, 2 lub 3. \n:   "); while((smietnik=getchar())!='\n');}
				
			}while (kontrolawejscia !=1 || testwejscia == 1 );
		
		switch (odp)
			{	
				case 1: choragiewka = 2; break;
				case 2: 
						printf("\nW katalogu roboczym utworzylem plik z ktorego dowiesz sie wiele o formacie pliku wejsciowego do SymBanku! \nWracam do menu glownego...");
						break;
				case 3:	printf("\nDo zobaczenia!\n\n"); exit(0);
				default: printf("\nNieznana odpowiedz, wcisnij 1, 2 lub 3. \n:  "); choragiewka = 1;  	
			}
			if (choragiewka == 2) break;
		}
	}

void plikwzorcowy(void);
{
	
}





