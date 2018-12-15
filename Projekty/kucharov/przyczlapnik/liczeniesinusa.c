/* 
Autor: Konrad Kucharczyk 1E05

Program liczący przybliżenie funkcji sinus.
Instrukcje:
* Należy kompilować z przełącznikiem -lm

*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#define PI 3.141592653589793238
#define N 10000
#define M 30
#define EPS 0.00000001

///Prototypy funkcji sprawdzających poprawność wpisanych danych
double sprd(char [], int*);
long int spri(char [], int*);

int main(void)
	{
		
		///Definicja zmiennych

		long double wartosc_przyblizenia=0.0, wartosc_licznika=0.0, wartosc_mianownika=0.0; 
		long double dokladnosc=0.0, dokladnosc_finalna=0.0;
		double xp=0.0, xk=0.0, x_chwilowe=0.0, krok=0.0;
		int powtorz_input=1, mnoznik=0, licznik_zer=0;
		long int n=0, licznik=0;
		char input[M], *reszta_ze_str={"\0"}, str_dokladnosc[N];
		

		////Pobieranie danych
		printf("_________________________\n\n");
		printf("Witaj w programie liczacym przyblizenie funkcji ");
		printf("trygonometrycznej sinus z rozwiniecia w szereg potegowy\n");
		printf("_________________________\n");
		printf("\nAby rozpoczac wpisz dane\n");
		do
			{	
				
				printf("Xp:");
				fgets(input, 15, stdin);
				if (input[0]=='0' && (input[2]=='0' || input[2]=='\0'))
					{
						xp= strtod(input, &reszta_ze_str);;
						powtorz_input=0;
					}
				else 
					{
						xp=sprd(input, &powtorz_input);
					}
								
			}
		while(powtorz_input!=0);
		
		do
			{	
				
				printf("Xk:");
				fgets(input, 15, stdin);
				xk=sprd(input, &powtorz_input);
				if (xk<=xp)
					{
						printf("Xk musi byc wieksze od Xp!\n");
						powtorz_input=1;
					}
				
			}
		while(powtorz_input!=0);
		
		do
			{	
				
				printf("n:");
				fgets(input, 15, stdin);
				n=spri(input, &powtorz_input);
				
			}
		while(powtorz_input!=0);
		
		do
			{	
				
				printf("krok:");
				fgets(input, 15, stdin);
				if (input[0]=='0' && (input[2]=='0' || input[2]=='\0') && (input[3]=='0') && (input[4]=='0' ) && (input[5]=='0'))
					{
						printf("Krok nie moze byc rowny 0!\n");
						powtorz_input=1;
					}
				else 
					{
						krok=sprd(input, &powtorz_input);
						if (fabs(krok)<EPS) 
							{
								printf("Krok nie moze byc rowny 0!\n");
								powtorz_input=1;
							}
					
					}
				
			}  
		while(powtorz_input!=0);
	  
		///Filtracja
			
			mnoznik=(int) (xp/PI);
			if (mnoznik>=2 && mnoznik%2==0)
				{
					xp=(xp-(mnoznik*PI));
					xk=(xk-(mnoznik*PI));
				}
			
			else if (mnoznik>=2 && mnoznik%2==1)
				{
					xp=(xp-((mnoznik-1)*PI));
					xk=(xk-((mnoznik-1)*PI));
				}
			
		
		 
		//Liczenie przyblizenia
		printf("Wartosc x\t Wartosc sinx\n");

		for (x_chwilowe=xp; x_chwilowe<xk || fabs(x_chwilowe-xk)<EPS; x_chwilowe+=krok)
			{			
				for (licznik=0; licznik<=n; licznik++)
					{
						wartosc_licznika=pow(x_chwilowe,((2*licznik)+1));			
						wartosc_mianownika=wartosc_mianownika*2*licznik*((2*licznik)+1);
						
						
						if (licznik==0) 
							{
								wartosc_mianownika=1; 
								wartosc_przyblizenia=wartosc_licznika/wartosc_mianownika;
							}
						else if (licznik%2==0 && licznik!=0) 
							{
								wartosc_przyblizenia+=wartosc_licznika/wartosc_mianownika;
							}  
							
						else if (licznik%2==1 && licznik!=0) 
							{
								wartosc_przyblizenia-=wartosc_licznika/wartosc_mianownika;
							} 
							
					}
		
		
				if (mnoznik>=2 && mnoznik%2==0)
					{
						x_chwilowe+=(mnoznik*PI);
						printf("%f\t %3.40Lf\n",x_chwilowe, wartosc_przyblizenia);
						x_chwilowe-=(mnoznik*PI);
					}
			
				else if (mnoznik>=2 && mnoznik%2==1)
					{
						x_chwilowe+=((mnoznik-1)*PI);
						printf("%f\t %3.40Lf\n",x_chwilowe, wartosc_przyblizenia);
						x_chwilowe-=((mnoznik-1)*PI);
					}
				else 
					{
						printf("%f\t %3.40Lf\n",x_chwilowe, wartosc_przyblizenia);
					}
			}

	/// Dokladnosc przyblizenia

		dokladnosc=(wartosc_licznika/wartosc_mianownika);
		sprintf(str_dokladnosc,"%.10000Lf", dokladnosc);
		licznik_zer=0;
		for (licznik=0; licznik<=100000000; licznik++)
			{
				if (str_dokladnosc[licznik+2]=='0')
					{
						licznik_zer++;
						
					}
				else if (str_dokladnosc[licznik]!='0')
					{
						licznik=100000000;
						
					}
			}
		dokladnosc_finalna=pow(10, -licznik_zer);
		printf("Przy %ld skladnikach szeregu, sinus jest przyblizony z dokladnoscia %0.0Le\n",n, dokladnosc_finalna);
		



			return 0;

	}

/*
 Funkcja sprawdzająca poprawność wpisanej wartości double.
 Pobiera lancuch z inputem uzytkownika i adres do zmiennej decydujacej o powtarzaniu wczytania danych
*/

double sprd(char str[], int* powtorz_input)
	{
		char *reszta_ze_str, odp1[15], smietnik;
		double wartosc_wlasciwa;
		wartosc_wlasciwa = strtod(str, &reszta_ze_str);
		*str=wartosc_wlasciwa;
	
				if (strlen(reszta_ze_str)>1)
					{
						while(odp1[0]!='t')
							{
								printf("Czy chciales podac wartosc %lf? (wpisz tak/nie)\n", wartosc_wlasciwa);
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
						printf("Podaj prosze wartosc float!\n");
						
					}
				else 
					{
						*powtorz_input=0;
						
					}
		return (wartosc_wlasciwa);
	}

/*
 Funkcja sprawdzająca poprawność wpisanej wartości int.
 Pobiera lancuch z inputem uzytkownika i adres do zmiennej decydujacej o powtarzaniu wczytania danych
*/
long int spri(char str[], int* powtorz_input)
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
						printf("Podaj prosze wartosc int >0!\n");
						
					}
				else 
					{
						*powtorz_input=0;
						
					}
		return (wartosc_wlasciwa);
	}
