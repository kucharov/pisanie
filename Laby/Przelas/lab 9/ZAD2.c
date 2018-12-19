// ZAD2.c

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

struct student
{
	int semestr;
	char *motto;
};

int main(void)
{
	int rozmiar, i, b;
	struct student **dupa;
	
	
	
	printf("\nJaki rozmiar tablicy?:   ");
	scanf("%d", &rozmiar);
	
	
	 dupa = (struct student **)malloc((rozmiar)*sizeof(struct student *));
	
	
for(i=0;i<rozmiar;i++)

{
	dupa[i] = (struct student *)malloc(sizeof(struct student));
	dupa[i]->motto = (char *)malloc(25*sizeof(char)); 
	
	char belkot[10];
	for(int a=0;a<10;a++) belkot[a] = (50 + rand()%100);
	
	dupa[i]->semestr = (rand()%15);
	*(dupa[i]->motto) = "dupsko";
<<<<<<< HEAD
=======
	//strncpy(dupa[i]->motto,belkot,sizeof(belkot));
	
>>>>>>> cac5ee0ff59e56792943c0da28041f614dcd5b4f
	
}


for( b=0;b<rozmiar;b++)
{
	if(b==0)printf("\n\t\t\tTABLICA STRUKTUR\n");
	printf("\ntab[%d]\t\t%d\t\t%s", b, dupa[b]->semestr, dupa[b]->motto); 


}
	
for( b=0;b<rozmiar;b++)
{
	
	free(dupa[b]->motto);
	free(dupa[b]);
	
}	
	free(dupa);
	return 0;
	
	}
