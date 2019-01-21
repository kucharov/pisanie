//zad 2 !


struct student
{
	int motywacja
	* char motto
	
};


int main(void)

{
	struct student **t;
	int rozmiar;
	printf("Ile struktur chcesz wygenerowac  w tablicy?");
	scanf("%d", &rozmiar);
	t = ( struct student **) malloc(rozmiar * sizeof(struct student *));
	for (int i=0;i<rozmiar;i++) *(t+i) = (struct student *)malloc(sizeof(struct student));
	for(int i=0;i<rozmiar;i++) {printf("\nmotywacja: %d, motto: %s ", (student+i)->motywacja, 
		(student+i)->motto);   
	
	
	
	

	
	
	
}
