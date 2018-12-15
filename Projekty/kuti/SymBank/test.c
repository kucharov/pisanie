#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>



double gauss(double srednia, double odchylenie)
{

	double s, losowa1, losowa2;
	
		do { 
			 
			 losowa1 = -1 + ((double)rand()/RAND_MAX) * 2;
			 printf("dupa");
			losowa2 = -1 + ((double)rand()/RAND_MAX) * 2; s = pow(losowa1, 2) + pow(losowa2, 2);	} while (s >= 1 || s == 0);
	return (srednia + odchylenie * losowa1 * sqrt(-2*log(s) / s));  // random na przedziale [0;1]
}

int main(void)
{
	double los = gauss(0.5, 0.1);
	printf("%lf", los);
	return 0;


}
