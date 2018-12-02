#include <stdio.h>
#include <string.h>
#define N 5
#define M 80
#define L 600
void wyswietl(char (*)[M], int ); //////// [M] to DRUGI parametr. pierwszy jest pominiety (dowolny)
int wczytaj(char (*), char (*)[M]);


int main()
	{
		int x;
		char nazwa[M];
		printf("START\n\nPodaj nazwe pliku ktory chcesz otworzyc:");
		char tab1[N][M];
		fgets(nazwa, 10, stdin);
		x=wczytaj(nazwa, tab1);
		if (x!=-1) wyswietl(tab1, N);
		printf("\n");
		
		return 0;
	}

int wczytaj(char *plik1, char (*tablica)[M])
	{
		int i=0, j=0, ret;
		char strzpliku[L];
		FILE *fp;
		fp=fopen(plik1,"r");
		if (fp==NULL) ret=-1;
		else
			{	
					for(i=0; i<=100000000; i++) 
						{
							strzpliku[i] = fgetc(fp);
							if( feof(fp) ) break;
						  
						}
					
					for(i=0; i<=strlen(strzpliku); i++)
						{
							int j=0;
							if (*(strzpliku+i)!='\n') *(*(tablica+j)+i)=*(strzpliku+i);
							else if (*(strzpliku+i)=='\n') 
								{
									*(*(tablica+j)+i)=*(strzpliku+i);
									j++;
								}
						}
					ret=0;
			}
		printf("%d",ret);
		fclose(fp);
		return ret;
	}
	
void wyswietl(char (*tablica)[M], int n)
	{
		int i, j;
		for (j=0;j<=n;j++) for(i=0;i<=M;i++)
			{
				if( (*(tablica+j))[i]=='\0' ) break;
				printf("%c",(*(tablica+j))[i]);
			}
	}


