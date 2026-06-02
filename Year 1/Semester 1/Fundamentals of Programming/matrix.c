#include<stdio.h>
#include<stdlib.h>
#include<crtdbg.h>

/// greatest element over the main diagonal/smalles element under the main diagonal using pointers
void citire(double **a, int n) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			printf("%d %d: ", i,j);
			scanf("%lf", (*(a + i) + j));
		}
	}
}

void afisare(double **a, int n) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			printf("%lf ", *(*(a + i) + j));
		}
		printf("\n");
	}
}


double deasupra(double** a, int n, int *linie, int *coloana) {

	double maxi = *(*a + 1);
	*linie = 0, * coloana = 1;
	for (int i = 0; i < n-1; i++)
		for (int j = i + 1; j < n; j++) 
			if (*(*(a + i) + j) > maxi)
				maxi = *(*(a + i) + j), *linie = i, *coloana = j;
	return maxi;
}

double sub(double** a, int n, int* linie, int* coloana) {

	double mini = *(*(a+1));
	*linie = 1, * coloana = 0;
	for (int i = 0; i < n-1; i++)
		for (int j = i+1; j < n; j++)
			if (*(*(a + j) + i) < mini)
				mini = *(*(a + j) + i), *linie = j, *coloana = i;
	return mini;

}

int main() {

	int n;
	printf("n: ");
	scanf("%d", &n);

	double **a = (double**)malloc(n * sizeof(double*));
	if (a == NULL) {
		printf("eroare alocare");
		return 1;
	}
	for (int i = 0; i < n; i++) {
		*(a + i) = (double*)malloc(n * sizeof(double));
		if (*(a + i) == NULL) {
			printf("eroare alocare");
			return 1;
		}
	}

	citire(a, n);
	afisare(a, n);
	
	int linie, coloana;
	double maxim, minim;
	
	if (n >= 2) {
		maxim = deasupra(a, n, &linie, &coloana);
		printf("element maxim:%lf situat pe linia: %d si coloana: %d", maxim, linie, coloana);

		minim = sub(a, n, &linie, &coloana);
		printf("\nelement minim:%lf situat pe linia: %d si coloana: %d", minim, linie, coloana);
	}
	else
		printf("matricea este de ordin prea mic");

	for (int i = 0; i < n; i++) {
		free(*(a + i));
		*(a + i) = NULL;
	}
	free(a);
	a = NULL;

	_CrtDumpMemoryLeaks();

	return 0;
}
