#include <math.h>

int sprawdzenie_danych(FILE *plik)
{
	int flaga, a, b;
	char probkatekstu[50] = '\n';
	double suma;
	
// bede sciagac po kolei wiersze pliku z danymi i kontrolowac zgodnosc z formatem.

	if (fscanf(plik, "%s", probkatekstu) == 3);
	else return 1;
	if(probkatekstu != "tab" & probkatekstu != "par") return 1;
	
	
	
	
	if (probkatekstu[0] == 't') 
	{
		klienci rozklad[25];
		
		for(a=0;a<50;a++) probkatekstu[a]='\n';
		
		a=0;
		while (fscanf(plik, "%lf %lf", &(rozklad[a]->liczba), &(rozklad[a]->szansa)) == 2) 
		{
			if (floor(rozklad[a]->liczba) != rozklad[a]->liczba) return 1;
			a++;
		}
		for(b=0;b<=a;b++) suma+=rozklad[a]->szansa;
		if (suma != 1) return 1;}
		
	
	
	else {
		for(a=0;a<50;a++) probkatekstu[a]='\n';
		fscanf(plik, "%s", probkatekstu);
		if(probkatekstu!= "rownomierny" && probkatekstu!= "normalny") return 1;
		
		if (probkatekstu == "rownomierny")
			{
				if (fscanf(plik, "%lf", 
			}  
		
		if (probkatekstu == "normalny")
			{
				
			}
		
		
	
	
	
	
	
	
	
	
	
	
	
	
	
}

typedef struct 
{	double liczba;
	double szansa;}
	klienci;
	
	for(a=0;a<100;a++) probkatekstu[a]='\n';
	
