
#include <stdio.h>
#include <string.h>
#define M 20

void wczytaj();
void zapisz(char *, char *);

int main(int argc, char **argv)
{
	wczytaj();
	if (argc!=3) 
		{	
			printf("Nieodpowiednia liczba argumentow!\n");
			return 0;
		}
	printf("Tekstowo zapisano do pliku: %s, a binarnie do: %s\n",*(argv+1),*(argv+2));
	zapisz(*(argv+1),*(argv+2));
	
	return 0;
}


void wczytaj()
	{
		char linijka[500], szukane[]="processor";
		FILE *fp;
		
        
        fp=fopen("/proc/cpuinfo","r");
		while(1)
			{
			
				if ((fgets(linijka,500,fp))!=NULL) 
					{
						if (strstr(linijka, szukane)!=NULL) 
							{
								printf("%s\n", linijka);
								
							}
					}
				else break;
			
					
					
			}
			
		fclose(fp);
        
        
	}

void zapisz(char *tekstowo, char *binarnie)
	{
		FILE *liczenie_procesorow;
		FILE *zapistekstowy;
		FILE *zapisbinarny;
		char linijka[500], szukane[]="processor", licznik_lancuch[10];
		
		int licznik=0, n=0;
		///LICZENIE	
		liczenie_procesorow=fopen("/proc/cpuinfo","r");
		while(1)
			{
				if ((fgets(linijka,500,liczenie_procesorow))!=NULL) 
					{
						if (strstr(linijka, szukane)!=NULL) 
							{					
								licznik++;
							}
					}
				else break;												
			}
		fclose(liczenie_procesorow);
		
		///ZAPISY
		zapistekstowy=fopen(tekstowo,"w");
		zapisbinarny=fopen(binarnie,"wb");
		fprintf(zapistekstowy, "Liczba procesorow: %d",licznik);
		sprintf(licznik_lancuch, "%d", licznik);
		
		n=fwrite(licznik_lancuch, 1, sizeof(licznik_lancuch), zapisbinarny);
		fclose(zapistekstowy);
		fclose(zapisbinarny);
	
	}
