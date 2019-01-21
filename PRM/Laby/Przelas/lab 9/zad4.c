//zad 4
/*    Ja to nie wiem jak to zrobic wogole, kurwa ciagle chce mi sie spac i nie mam sily sie uczyc a musze uczyc sie do sesji ktora juz za niewiele poand miesiac. No ratunku, kurwa. 
 * 		Zycie mi ucieka a ja nie moge nigdzie uciec, bo zimno, bo biedno, bo nie ma z kim. Ponure to życie i w ogóle nie wiem o nim nic, gdzie ma mnie zawieść i w ogóle. 
 * 		Chce odnalezc powolanie, chce odnalezc prawdziwa pasje , cos co sprawi, ze idąc do pracy bede sie cieszyl, kazdy kolejny dzien witał z uśmiechem i poczuciem wyzwania. A teraz jest gówno, 
 * 		bo największe wyzwanie tygodnia to kurwa laboratorium z pomiarów, nudny syf potrzebny tylko po to, żeby zdać semestr na moich cudownych studiach . W ogóle co to za studia to ja nie wiem, ale odrzuca
 * 		mnie myśl o nich i teraz w ogóle mam ochotę tylko programować. Ratunku kurwa, bo ja nie chce spędzić całego życia w wątpliwościach i niepewności jutra.....
 * 
 */
 //dobra robota czeka
 
 #include <stdio.h>
 #include <string.h>
 #include <stdlib.h>
 
 struct fragment
 {
	 int wartosc;
	 struct fragment * nastepny;
	 struct fragment * poprzedni;
 };
 
 
 struct fragment *dodajnakoncu(struct fragment *ostatnipoprzedniak, int cyfra)
{
struct fragment *nowykoniec = malloc(sizeof(struct fragment));
if (nowykoniec==NULL) {printf("\n Blad alokacji przy dodawaniu elementu...\n"); exit(1);}

nowykoniec->nastepny = NULL;
nowykoniec->poprzedni = ostatnipoprzedniak;
nowykoniec->wartosc = cyfra;
if (ostatnipoprzedniak!=NULL) ostatnipoprzedniak->nastepny = nowykoniec;		 
	 
return nowykoniec;	 
	 
}

struct fragment *nowypoczatek(struct fragment *ostatninastepniak, int cyfra);
{
	struct fragment *nowypoczatek = malloc(sizeof(struct fragment));
	if(ostatninastepniak ==NULL) {nowypoczatek->wartosc = cyfra; return nowypoczatek;}
	if (nowypoczatek==0) {printf("\nZjebalo sie przy dodawaniu elementu"); exit(2);}
	
	nowypoczatek->poprzedni = NULL;
	nowypoczatek->nastepny = ostatninastepniak;
	nowypoczatek->wartosc = cyfra;
	if(ostatninastepniak!=NULL) ostatninastepniak->poprzedni = nowypoczatek;
	
	return nowypoczatek;
}

void wyswietlenie(struct fragment *czub);
{
// jesli jest w czubie to nie ma poprzedniaka.

struct fragment  *aktualniak;
int liczydlo = 1;

aktualniak = czub;


while(aktualniak!=NULL)
{
if (liczydlo==1) printf("\t\t\t\tLISTA DWUKIERUNKOWA");
printf("Fragment[%d]     =    %d\n", liczydlo, aktualniak->wartosc);
aktualniak=aktualniak->nastepny;
}
}

struct fragment *usuwanie(struct fragment *doskasowania);
{
struct fragment *poprzedniak=doskasowania->poprzedni, *nastepniak=doskasowania->nastepny;

if(poprzedniak==NULL && (nastepniak==NULL)) return NULL;

if(poprzedniak==NULL) {nastepniak->poprzedni = NULL; free(doskasowania); return nastepniak;} 

if(nastepniak==NULL) {struct fragment *aktualniak=doskasowania;
						while(aktualniak->poprzedniak!=NULL) aktualniak = aktualniak->poprzedni; poprzedniak->nastepny = NULL;
						  free(doskasowania); ; return aktualniak;}

struct fragment *aktualniak = doskasowania;
while(aktualniak!=NULL) aktualniak = aktualniak->poprzedniak;

nastepniak->poprzedni = poprzedniak; poprzedniak->nastepny = nastepniak;
free(doskasowania);


return aktualniak;
}


void zwolnienie(struct fragment *pierwszyelement)
{
	struct fragment *schowek;
	
while (pierwszyelement->nastepny != NULL)
{
	
	schowek = pierwszyelement->nastepny;
	free(schowek->poprzedni);
	pierwszyelement = schowek;
	
	if (pierwszyelement->nastepny == NULL) free(pierwszyelement);
}
	
	
}



int main(void)
{
		struct fragment *pierwszy;
		char odp;
																																												powrotpobledzie:
		printf ("Witaj w liscie dwukierunkowej, wcisnij:\n'a' - nowy fragment na poczatku\n'b' - nowy fragment na koncu\n'c' - wyswietl liste\n'd' - usun fragment\n'e' - usun cala liste\n :  ");
		scanf("%c", &odp);
		
		switch(odp)
			case 'a': pierwszy= nowypoczatek(
				
			
			
			case 'b': strasznie duzo pierdolenia z tym nie chce mi sie ide spac zZZzzZZZzZZ
			
			
			case 'c': cipa
			
			
			case 'd': dupa
			
			
			case 'e':
			
			
			default: printf("\n Blad wprowadzania, powracam do menu.\n\n\n\n"); goto powrotpobledzie;
		



	
}




	














