#include <stdio.h>
#include <string.h>
#include <stdlib.h>
struct osoba{
	char *imie;
	char *nazwisko;
};


char  *stringi(char *p){
	int i;
	char c;
	p=NULL;
	for(i=0;(c=getchar())!='\n';i++){
	p=(char*)realloc(p,(1)*sizeof(char));
	*(p+i)=c;
	}
	*(p+i)='\0';
	return p;
}

int main()
{
	struct osoba *p;
	
	p=malloc(sizeof(struct osoba));
	
	(*p).imie=stringi((*p).imie);
	(*p).nazwisko=stringi((*p).nazwisko);
	printf("%s %s\n",(*p).imie, (*p).nazwisko);
	//printf("adresy:\nimie: %p\nnazwisko: %p\n",(p)->imie, (p)->nazwisko);
	printf("adresy:\nimie: %p\nnazwisko: %p\nstruktura: %p\n",(*p).imie, (*p).nazwisko, p);
	printf("rozmiar struktury: %lu ",sizeof(p));
	//printf("\nrozmiar struktury: %lu ",sizeof((*p).imie));
	//printf("\nrozmiar struktury: %lu ",sizeof((*p).nazwisko));
	free((*p).imie);
	free((*p).nazwisko);
	free(p);
	return 0;
}
