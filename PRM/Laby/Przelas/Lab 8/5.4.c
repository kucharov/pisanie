#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define M 10
#define N 16

void imnozenie_macierzy(int [N][M],int, int, int [N][M], int, int, int[M][N], int, int);
void wmnozenie_macierzy(int (*)[M],int, int, int (*)[M],int, int, int (*)[N], int, int);
void wyswietlenie(int[][], int, int);

int main(void)
{
int ma[N][M], mb[M][N], mc[N][M];
imnozenie_macierzy(mc, N, M, ma, N, M,mb, M, N);
wmnozenie_macierzy(mc, N, M, ma, N, M, mb, M, N);
vmnozenie_macierzy();
wyswietlenie(mc, N, M);
return 0;
}


void imnozenie_macierzy(int tabc[N][M],int wierszec, int kolumnyc, int taba[N][M],
int wierszea, int kolumnya, int tabb[M][N], int wierszeb, int kolumnyb)
{
	
	
	


