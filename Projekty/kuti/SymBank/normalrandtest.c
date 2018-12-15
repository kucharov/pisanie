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
		s = pow(losowa1, 2) + pow(losowa2, 2);}
	while (s >= 1 || s == 0);
	return srednia + odchylenie * losowa1 * sqrt((-2*log(s)) / s);  // 
}
	
	
	
int main(void)
{
FILE *histogram, *meta;
int proby = 3;
int razy = 0;
double odchylenie, srednia;


printf("\nSrednia?:  ");
scanf("%lf", &srednia);
printf("\nodchylenie?:  ");
scanf("%lf", &odchylenie);

int hist[101] = {0};
printf("cipa");
do
{
		int los = nearbyint(gauss(srednia, odchylenie));
		printf("%d", los);
		hist[los+51] = hist[los+51] + 1;
		razy++;
	
} while (razy<proby);
printf("guwno");

histogram = fopen("histogram.txt", "w");

for(int a=0;a<101;a++) fprintf(histogram, "%d %d\n", a-51, hist[a]);

fclose(histogram);

meta = fopen("meta.txt", "w");
fprintf(meta, "set title 'HISTOGRAM FUNKCJI GAUSS() NA PRZEDZIALE [srednia 0 odchyl 1]'; set xlabel 'liczba'; set ylabel 'czestosc';plot './histogram.txt");
fclose(meta);
system("gnuplot -plot 'meta.txt'");
return 0;
}
