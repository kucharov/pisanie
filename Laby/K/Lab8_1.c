#include <stdio.h>
#include <string.h>
#define N 5
#define M 80
#define L 600
void wyswietl(char (*)[M], int ); //////// [M] to DRUGI parametr. pierwszy jest pominiety (dowolny)
int wczytaj(char (*), char (*)[M]);


int main()
	{
		char nazwa[]="plik1";
		printf("START\n\n");
		char tab1[N][M];
		wczytaj(nazwa, tab1);
		wyswietl(tab1, N);
		printf("\n\nSTOP\n\n");
		//printf("\n\n%d\n\n",wczytaj(nazwa, tab1));
		
		return 0;
	}

int wczytaj(char *plik1, char (*tablica)[M])
	{
		int i=0, j=0, ret;
		char strzpliku[L];
		FILE *fp;
		fp=fopen("plik1.txt","r");
		for(i=0; i<=100000000; i++) 
			{
				strzpliku[i] = fgetc(fp);
				if( feof(fp) ) break;
			  
			}
		/////fscanf(fp, "%c", strzpliku);
		//printf("\n%s\n\n",strzpliku);
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
		
		if (fp==NULL) ret=-1;
		else ret=0;
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


