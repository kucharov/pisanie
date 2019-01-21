//L8_z2
//while((smietnik=getchar())!='\n');
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
	int i=0, j=0, len;
	double DANE[N][N]={0.0};
	
	generuj_dane(DANE);

	printf("\npodaj nazwe pliku do ktorego zapisac w formie tekstowej: \n");
	fgets(nazwa,10,stdin);
	
	len=strlen(nazwa); 
	if(nazwa[len-1]=='\n') nazwa[len-1]='\0';
	strcat (nazwa, ".txt");
	
	zapisz_do_pliku_text(nazwa,DANE);
	printf("\npodaj nazwe pliku do ktorego zapisac w formie binarnej: \n");	
	fgets(nazwa2,10,stdin);	
	
	len=strlen(nazwa2); 
	if(nazwa2[len-1]=='\n') nazwa2[len-1]='\0';
	strcat (nazwa2, ".txt");
	
	zapisz_do_pliku_bin(nazwa2,DANE);	
	printf("tekstowy %s\n ",nazwa);
	wyswietl(nazwa,tekstowy);
	printf("\nbinarny %s\n",nazwa2);
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
		fp=fopen(plik,"w+b");
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
	
	
	
	
	
	
	
