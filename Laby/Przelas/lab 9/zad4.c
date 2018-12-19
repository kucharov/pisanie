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









