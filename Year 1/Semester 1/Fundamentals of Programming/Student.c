#include<stdio.h>
#include<stdlib.h>
#include<crtdbg.h>
#include<string.h>

struct student {

	char* nume;
	char* facultate;
	char* sectie;
	int restante;
};

void citire(int n, struct student* studenti) {

	getchar();

	for (int i = 0; i < n; i++) {
		printf("\n\nStudentul cu numarul: %d\n", i+1);

		(*(studenti + i)).nume = (char*)malloc(50 * sizeof(char));
		(*(studenti + i)).facultate = (char*)malloc(50 * sizeof(char));
		(*(studenti + i)).sectie = (char*)malloc(50 * sizeof(char));

		printf("\nNume: ");
		fgets((*(studenti + i)).nume, 50, stdin);
		(*(studenti + i)).nume[strcspn((*(studenti + i)).nume, "\n")] = 0;

		printf("\nFacultate: ");
		fgets((*(studenti + i)).facultate, 50, stdin);
		(*(studenti + i)).facultate[strcspn((*(studenti + i)).facultate, "\n")] = 0;

		printf("\nSectie: ");
		fgets((*(studenti + i)).sectie, 50, stdin);
		(*(studenti + i)).sectie[strcspn((*(studenti + i)).sectie, "\n")] = 0;

		printf("\nNumar restante: ");
		scanf("%d", &(*(studenti + i)).restante);

		getchar();
	}
}

void afisare(int n, struct student* studenti) {
	for (int i = 0; i < n; i++) {
		printf("\nStudentul cu numarul: %d are: numele: %s , facultatea: %s , secita %s , restante: %d \n\n",
			i+1, (*(studenti + i)).nume, (*(studenti + i)).facultate, (*(studenti + i)).sectie, (*(studenti + i)).restante);
	}
}

void student_nume(int n, struct student* studenti) {
	char* student_cautat = (char*)malloc(50 * sizeof(char));
	printf("\n\nIntroduceti numele studentului: ");
	fgets(student_cautat, 50, stdin);
	student_cautat[strcspn(student_cautat, "\n")] = 0;

	int gasit = 0;
	for (int i = 0; i < n; i++) {
		if (strcmp((*(studenti + i)).nume, student_cautat) == 0) {
			printf("Facultate: %s ; sectie: %s ; restante: %d\n\n", (*(studenti + i)).facultate, (*(studenti + i)).sectie, (*(studenti + i)).restante);
			gasit = 1;
		}
	}

	if (!gasit) {
		printf("Nu exista acest student in bazele de date.\n");
	}
	free(student_cautat);
}

void restante(int n, struct student* studenti) {

	int x;
	printf("\n\nIntroduceti numarul de restane dorit pentru comparare: \n");
	scanf("%d", &x);

	for (int i = 0; i < n; i++) {
		if ((*(studenti + i)).restante >= x)
			printf("\nNr: %d , Nume: %s, Facultate: %s, Sectie: %s, Restante: %d ", i+1, (*(studenti + i)).nume, (*(studenti + i)).facultate, (*(studenti + i)).sectie, (*(studenti + i)).restante);
	}
}

void integralisti(int n, struct student* studenti) {

	char* fac = (char*)malloc(50 * sizeof(char));
	printf("\n\nIntroduceti facultatea de la care vreti sa vedeti toti studentii integralisti: ");
	getchar();
	fgets(fac,50,stdin);
	fac[strcspn(fac, "\n")] = 0;

	int gasit =0;
	for (int i = 0; i < n; i++) {
		if (strcmp((*(studenti + i)).facultate, fac) == 0 && (*(studenti + i )).restante == 0) {
			gasit = 1;
			printf("\nNr: % d, Nume : % s, Facultate : % s, Sectie : % s, Restante : % d ", i+1, (*(studenti + i)).nume, (*(studenti + i)).facultate, (*(studenti + i)).sectie, (*(studenti + i)).restante);
		}
	}
	if (gasit == 0) {
		printf("Nu exista studenti integralisti\n\n");
	}
	else
		printf("\n\n");
	free(fac);
}

int main() {

	int n;
	printf("introduceti numarul de studenti: ");
	scanf("%d", &n);

	struct student* studenti = (struct student*)malloc(n * sizeof(struct student));

	citire(n, studenti);
	afisare(n, studenti);

	student_nume(n, studenti);
	restante(n, studenti);
	integralisti(n, studenti);

	for (int i = 0; i < n; i++) {

		free((*(studenti + i)).nume);
		free((*(studenti + i)).facultate);
		free((*(studenti + i)).sectie);
	}
	free(studenti);

	_CrtDumpMemoryLeaks();

	return 0;
}
