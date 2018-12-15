#include <stdio.h>
#include <stdlib.h>

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
		
		int main()
		{menu(0);return 0;}
