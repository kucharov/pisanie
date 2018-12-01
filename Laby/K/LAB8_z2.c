//L8_z2

#include <stdio.h>
#include <string.h>
#define N 10
#define M 10000
void wyswietl(char *, char *);
void generuj_dane(double (*)[N]);
void zapisz_do_pliku_bin(char *, double (*)[N]);
void zapisz_do_pliku_text(char *, double (*)[N]);

int main(int argc, char **argv)
{
	char nazwa[N],nazwa2[N], tekstowy[]="r", binarny[]="rb", smietnik;
	int i=0, j=0;
	double DANE[N][N]={0.0};
	generuj_dane(DANE);
	for (j=0; j<=9;j++)	
		
		for (i=0; i<=9;i++)
			{
				printf("%lf ",*(*(DANE+j)+i));
			}
	printf("\npodaj nazwe pliku do ktorego zapisac w formie tekstowej: \n");
	fgets(nazwa,10,stdin);
	zapisz_do_pliku_text(nazwa,DANE);
	printf("\npodaj nazwe pliku do ktorego zapisac w formie binarnej: \n");
	//while((smietnik=getchar())!='\n');
	fgets(nazwa2,10,stdin);
	//while((smietnik=getchar())!='\n');
	zapisz_do_pliku_bin(nazwa2,DANE);
	
	printf("tekstowy \n");
	wyswietl(nazwa,tekstowy);
	printf("\nbinarny \n");
	wyswietl(nazwa2,binarny);
	
	return 0;
}


void generuj_dane(double (*t)[N])
	{
		int i, j, w=1;
		for (j=0; j<=9;j++)	
			for (i=0; i<=9;i++)
				{											
					*(*(t+j)+i)=w++;					
				}
	}
	
void zapisz_do_pliku_bin(char *plik, double (*t)[N])
	{
		int i, j;
		FILE *fp;
		fp=fopen(plik,"wb");
		if (fp==NULL) fprintf(stderr,"Blad otwarcia pliku\n");
		else 
			{
				for (j=0; j<=9;j++)			
					for (i=0; i<=9;i++)
						{
							fprintf(fp,"%lf ",*(*(t+j)+i));
						//	fputs(((char) *(*(t+j)+i)),fp);
						}
			}
		fclose(fp);
	}
		
		
void zapisz_do_pliku_text(char *plik, double (*t)[N])
	{
		int i, j;
		FILE *fp;
		fp=fopen(plik,"w+");
		if (fp==NULL) fprintf(stderr,"Blad otwarcia pliku\n");
		else 
			{
				for (j=0; j<=9;j++)			
					for (i=0; i<=9;i++)
						{
							fprintf(fp,"%lf ",*(*(t+j)+i));
						}
			}
		fclose(fp);
	}
	
	
void wyswietl(char *plik, char *tryb)
	{
		FILE *fp;
		char wynik[M];
		fp=fopen(plik,tryb);
		if (fp==NULL) fprintf(stderr,"Blad otwarcia pliku\n");
		else 
			{
				fgets(wynik,10000,fp);
				fputs(wynik,stdout);
			}
	}	
	
	
	
	
	
	
	
