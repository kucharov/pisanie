//CALKONATOR ~~~projekt programistyczny przelasa~~~
// autor : MATEUSZ PRZELASKOWSKI 1E5 
//zadanie 9. : Napisac program wyznaczajacy wartosc calki oznaczonej wielomianow stopnia N<100 - metoda Monte Carlo - odmiana zwana podstawowa.
//prosze kompilowac z flaga -lm


/*

* 
* 
* TEST  ----->  printf( "gorna %Lf, dolna %Lf, los %Lf, PROBA NUMER %lld, WYNIK = %Lf", gorna, dolna, los, z, wynik); return 0;
		


*/
nie wiem jak odnalezc sile by przezwyciezyc zgnilizne codziennej szarosci
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>
#include <float.h>
#define EPS  10e-10

int main(void)
{
//     			 DEKLARACJE


double wsp[100] = {0}; // tabela dla wspolczynnikow przy potegach wielomianu 0 - 99 
int st = 0; // stopien wpisywanego wielomianu W(x) 
long long int podloga;
float test_wejscia;
int inspekcja_wejscia;
int kontrola_wejscia;          // samo za siebie
long double sprawdzenie_wejscia = 0;
long  double dolna, gorna, zmieniacz; // przedzial calkowania , zmieniacz dla ewentualnej zamiany w razie odwrotnej kolejnosci podania granic
int y=0; 
long long int z = 0;  //liczniki
long long int proby; //liczba prob losowych
char odpowiedz;
char smietnik = '\n'; // zmienna specjalnie na czyszczenie bufora
long double suma = 0, sumakw = 0, calka = 0, blad = 0, wynik = 0,los = 0;
FILE *plik; // plik ze sformatowanymi wynikami
FILE *instrukcje; //plik z instrukcjami dla gnuplota


 
//				INSTALACJA DLA NIEPRZYGOTOWANYCH 


do {printf("\n\nCzy masz zainstalowany program gnuplot? [t/n]:   "); odpowiedz = getchar(); while((smietnik=getchar())!='\n');} while (odpowiedz != 't' && odpowiedz != 'n'); 
if (odpowiedz == 'n')  system("sudo apt install gnuplot-x11"); // wyreczamy uzytkownika w instalacji



//			 		STOPIEN WIELOMIANU
	


printf("\n\n\t\t~*~*~*~*~*~*~*Witaj w  C A L K O N A T O R Z E!!!!*~*~*~*~*~*~*~\n aby obliczyc calke oznaczona z wielomianu na danym przedziale,\nnajpierw podaj stopien wielomianu ktory chcesz scalkowac:  ");
do {
		inspekcja_wejscia=0;
		kontrola_wejscia = scanf("%f", &test_wejscia);
		podloga = floorf(test_wejscia);
		if ((smietnik=getchar())!='\n' || kontrola_wejscia != 1) {inspekcja_wejscia = 1; printf("\nZle wpisales dane!!\nPodaj stopien wielomianu: "); while((smietnik=getchar())!='\n');} 
		if ((test_wejscia - podloga)>EPS &&  kontrola_wejscia == 1) printf("Podaj liczbe calkowita!!\nPodaj stopien wielomianu: ");// jesli liczba nie rowna sie czesci calkowitej 
		if (test_wejscia>99) printf("\nMaksymalny mozliwy stopien wielomianu wynosi 99 !!\n\nPodaj stopien wielomianu:   ");		// z siebie, to znaczy ze nie jest calkowita...
		st = test_wejscia;
 	} while (inspekcja_wejscia!=0 || kontrola_wejscia != 1 || test_wejscia - podloga > EPS || st>99 ); 
 	


//				WSPOLCZYNNIKI
	

for(y=0; y<=st; y++) //petla wpisywania wspolczynnikow calkowanego wielomianu
	{
		do
			 {
				inspekcja_wejscia = 0;
				printf("\nWprowadz wspolczynnik wielomianu przy potedze %d:  ", y);
				if (y==0) printf("\b\b\b (wyraz wolny):  ");
				kontrola_wejscia = scanf("%lf", &wsp[y]);
				if ((smietnik = getchar()) != '\n' || kontrola_wejscia != 1) {printf("\nWprowadz poprawne dane!!!"); inspekcja_wejscia = 1; while((smietnik=getchar())!='\n');} //test niepoprawnych znakow  
				// typu litery w ogóle, ale tez litery na koncu np  "43gd". wiekszosc programow konkurencji takich bledow nie wylapuje
				
			} while (inspekcja_wejscia !=0 || kontrola_wejscia != 1);	
			
		
	}
	
		
//  				 GRANICE

do {

	printf("\nPodaj granice przedzialu calkowania [a;b]:  \n");
	
	do	{
			inspekcja_wejscia = 0;
			printf("a: ");
			kontrola_wejscia = scanf("%Lf", &dolna);
			if ((smietnik = getchar()) != '\n' || kontrola_wejscia != 1) { printf("Wpisz dane poprawnie!!!\n"); inspekcja_wejscia = 1; while((smietnik=getchar())!='\n');}
		} while (kontrola_wejscia !=1 || inspekcja_wejscia != 0);
	
	do {
			inspekcja_wejscia = 0;
			printf("\nb: ");
			kontrola_wejscia = scanf("%Lf", &gorna);
			if ((smietnik = getchar()) != '\n' || kontrola_wejscia != 1) {printf("Wpisz dane poprawnie!!!\n"); inspekcja_wejscia = 1; while((smietnik=getchar())!='\n');}
		} while (kontrola_wejscia != 1 ||inspekcja_wejscia !=0);
		
		if (dolna>gorna) { zmieniacz = dolna; dolna = gorna; gorna = zmieniacz; }// jesli uzytkownik poda dolna granice zamiast gornej i odwrotnie, 
																				// to inteligentny program nie zglupieje tylko zamieni sobie te granice i bedzie wszystko ok
	if (gorna-dolna<EPS) printf("\nPrzedzial nie moze byc pusty ....Podaj rozne granice!!");	
		
	} while (gorna-dolna<EPS);	




//  			 PROBY


do {	
		inspekcja_wejscia = 0;
		printf("\nPodaj liczbe prob losowych podejmowanych do dokladnego obliczenia wartosci calki:    "); 
		kontrola_wejscia = scanf("%Lf", &sprawdzenie_wejscia); 
		podloga = floorl(sprawdzenie_wejscia);
		if ( kontrola_wejscia != 1 || sprawdzenie_wejscia <= 0 || sprawdzenie_wejscia > LLONG_MAX) printf("\nWpisales zle dane. Podaj naturalna liczbe wieksza od zera.\
		\nByc moze przekroczyles mozliwy zakres ( 0 - %lld )?", LLONG_MAX); else proby = sprawdzenie_wejscia;
		if (sprawdzenie_wejscia - (long double)podloga > EPS && kontrola_wejscia == 1) printf("\nPodaj liczbe calkowita!!!");
		if ((smietnik = getchar())!= '\n') {printf("\nWpisz dane poprawnie..."); inspekcja_wejscia = 1; while((smietnik=getchar())!='\n');}
    }	 while (inspekcja_wejscia!=0 ||kontrola_wejscia != 1 || sprawdzenie_wejscia <= 0 || podloga > LLONG_MAX || (sprawdzenie_wejscia - (long double)podloga) > EPS);	
	 
	 
	 


	//			LICZENIE : D

plik = fopen("calkonator_wyniki.txt", "w");
if (plik == NULL) {printf("\n\nNie mozna utworzyc lub otworzyc pliku z wynikami. Napraw problem i uruchom CALKONATOR jeszcze raz."); return 0;} 
fprintf(plik, "# Wyniki obliczenia calki z wielomianu ");										
for (y = st; y >= 0; y--) { if (y==st) fprintf(plik, "% lf x^%d ", wsp[y], y); else if (y>0) fprintf(plik, "%+lf x^%d ", wsp[y], y); else fprintf(plik, "%+lf ", wsp[y]);} //duzo warunkow dla prawidlowego wyswietlenia wielomianu 
fprintf(plik, "\n# W granicach [%Lf ; %Lf] \n\n\n # Proby			Wartosc\n", dolna, gorna); 	 //Przygotowanie wstepne pliku, informacje o wielomianie itp



for(z = 0; z< proby; )
		{
			wynik = 0;
			los = dolna + (((long double)rand()/(long double)RAND_MAX) * (gorna-dolna)) ; 
			for(y=0; y <= st; y++) wynik += (powl(los, (long double)y) * (long double)wsp[y]);
			if ((suma + wynik) > LDBL_MAX || (sumakw + wynik * wynik) > LDBL_MAX || sumakw < 0) {printf("\n\nPrzekroczono mozliwy zakres rozmiaru danych . Sprobuj z mniejsza liczba prob !"); return 0;}
			
			
			suma += wynik;
			sumakw += (wynik * wynik);
				
			z++;
			
	
		///warunki na wgrywanie do pliku
		if (proby <= 100) fprintf(plik,"%lld			%Lf\n", z, (suma/(long double)z) * fabsl(gorna - dolna) );  
		if (proby > 100 && (z % (proby/100)) == 0) fprintf(plik, "%lld			%Lf\n", z, (suma/(long double)z) * fabsl(gorna - dolna)); 
		if (z == proby) fprintf(plik, "%lld			%Lf\n", z, (suma/(long double)z) * fabsl(gorna - dolna)); 
	
		}
		
fclose(plik);
		
calka = (suma/(long double)proby) * fabsl(gorna - dolna);
blad =  2 * sqrtl(((1/((long double)proby-1))*(sumakw/(long double)proby - ((suma/(long double)proby)*(suma/(long double)proby))))/proby);
printf("\n\nEstymowana wartosc calki wynosi %Lf . \n\nNiepewnosc metody jest rowna %Lf przy liczbie prob %lld .\n\n Poszukaj pliku z wynikami w katalogu roboczym!\n\n", calka, blad, proby); 
	

	
	/// uruchomienie gnuplot
	

instrukcje = fopen("gnuplot_info.txt", "w");
fprintf(instrukcje,"set title 'Wartosci obliczonej calki w zaleznosci od liczby prob losowych'; set xlabel 'Liczba prob losowych'; set ylabel 'Wartosc calki';plot './calkonator_wyniki.txt");
fclose(instrukcje);
system("gnuplot -plot 'gnuplot_info.txt'");
	
	

	
 
return 0;
}









