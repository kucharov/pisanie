#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

double gauss(double srednia, double odchylenie)
{
	double s, losowa1, losowa2;
	do
	{ 
		losowa1 = -1 + ((double)rand()/RAND_MAX) * 2;
		losowa2 = -1 + ((double)rand()/RAND_MAX) * 2; 							// https://stackoverflow.com/questions/2325472/generate-random-numbers-following-a-normal-distribution-in-c-c
		s = (losowa1 * losowa1) + (losowa2 * losowa2);}
	while (s >= 1 || s == 0);
	return srednia + (odchylenie * losowa1 * sqrt((-2*log(s)) / s));  // 
}
	
	
	
int main(void)
{
FILE *histogram, *meta;
int proby = 300000;
int razy = 0;
double odchylenie, srednia;


printf("\nSrednia?:  ");
scanf("%lf", &srednia);
printf("\nodchylenie?:  ");
scanf("%lf", &odchylenie);

int hist[601] = {0};
dupa:
do
{
		int los = nearbyint(gauss(srednia, odchylenie));
		printf("%d", los);
		if (los>300 || los<-300) {printf("%d wyjebalo sie ", los); goto dupa;}
		hist[los+300] = hist[los+300] + 1;
		razy++;
	
} while (razy<proby);


histogram = fopen("histogram.txt", "w");

for(int a=0;a<601;a++) fprintf(histogram, "%d %d\n", a-300, hist[a]);

fclose(histogram);

meta = fopen("meta.txt", "w");
fprintf(meta, "set title 'HISTOGRAM FUNKCJI GAUSS() NA PRZEDZIALE [srednia 0 odchył 1]'; set xlabel 'liczba'; set ylabel 'czestosc';plot './histogram.txt");
fclose(meta);
system("gnuplot -plot 'meta.txt'");
return 0;
}
//działa!!!!!!!!!!!!!!!!!!!!!!!!!!!11
