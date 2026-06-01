#include<stdio.h>
#include<string.h>
#include<crtdbg.h>
#include<stdlib.h>

struct carte {

	char *titlu;
	char *autor;
	float pret;
	int nr_pag;

};


void citire(int n, struct carte *carti) {
	
	getchar();	

	for (int i = 0; i < n; i++) {
		printf("\nCartea cu numarul %d: \n", i+1);
		printf("\ntitlu: ");
	
		(*(carti + i)).titlu = (char*)malloc(50 * sizeof(char));
		(*(carti + i)).autor = (char*)malloc(50 * sizeof(char));
		
		fgets((*(carti+i)).titlu, 50, stdin);
		(*(carti + i)).titlu[strcspn((*(carti + i)).titlu, "\n")] = 0;

		printf("\nautor: ");
		fgets((*(carti+i)).autor, 50, stdin);
		(*(carti + i)).autor[strcspn((*(carti + i)).autor, "\n")] = 0;

		printf("\npret: ");
		scanf("%f", &(*(carti + i)).pret);

		printf("\nnr_pag: ");
		scanf("%d", &(*(carti+i)).nr_pag);
		getchar();
	}
}

void afisare(int n, struct carte *carti) {
	
	for (int i = 0; i < n; i++) {
		printf("\nCartea cu numarul %d: titlu: %s ; autor: %s ; pret: %.2f ; numar de pagini: %d\n\n", i+1, (*(carti+i)).titlu, (*(carti+i)).autor, (*(carti+i)).pret, (*(carti+i)).nr_pag);
	}
}

struct carte* calcul(int n, struct carte *carti) {

	int index = -1;
	float pret_max = -1.0;

	for (int i = 0; i < n; i++) {
		if ((*(carti+i)).pret > pret_max)
			pret_max = (*(carti+i)).pret, index = i;
	}
	return (carti+index);
}


void carti_dupa_autor(int n, struct carte *carti) {
	char *autor_cautat = (char*)malloc(50 * sizeof(char));
	printf("\n\nIntroduceti numele autorului: ");
	fgets(autor_cautat, 50, stdin);
	autor_cautat[strcspn(autor_cautat, "\n")] = 0;

	int gasit = 0;
	printf("\nCartile scrise de autorul %s \n", autor_cautat);

	for (int i = 0; i < n; i++) {
		if (strcmp((*(carti+i)).autor, autor_cautat) == 0) {
			printf("titlu: %s ; pret: %.2f ; numar de pagini: %d\n\n", (*(carti+i)).titlu, (*(carti+i)).pret, (*(carti+i)).nr_pag);
			gasit = 1;
		}
	}

	if (!gasit) {
		printf("Nu exista carti scrise de acest autor.\n");
	}
	free(autor_cautat);
}


int main() {

	int n;
	printf("Introduceti numarul de carti: ");
	scanf("%d", &n);

	struct carte *carti = (struct carte*) malloc (n * sizeof(struct carte));

	citire(n, carti);
	afisare(n, carti);
	
	struct carte *pret_max = calcul(n, carti);
	printf("Cartea cu pretul cel mai mare este: ");
	printf("titlu: %s ; autor: %s ; pret: %.2f ; numar de pagini: %d", (*pret_max).titlu, (*pret_max).autor, (*pret_max).pret, (*pret_max).nr_pag);

	carti_dupa_autor(n, carti);

	for (int i = 0; i < n; i++) {
		free((*(carti + i)).titlu);
		free((*(carti + i)).autor);
	}
	free(carti);


	_CrtDumpMemoryLeaks();

	return 0;
}
