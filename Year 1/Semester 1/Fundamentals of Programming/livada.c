#include<stdio.h>
#include<stdlib.h>
#include<crtdbg.h>
#include<string.h>
#include<stdbool.h>

struct pom {

	char* specie;
	int varsta;
	int rodeste;

};

struct livada {

	int n;
	struct pom* pomi;

};

void citire(struct livada* liv) {
    printf("Introduceti numarul de pomi: ");
    scanf("%d", &(*liv).n);
    getchar(); 

    (*liv).pomi = (struct pom*)malloc((*liv).n * sizeof(struct pom));

    for (int i = 0; i < (*liv).n; i++) {
        printf("\nPomul %d\n", i + 1);

        (*((*liv).pomi + i)).specie = (char*)malloc(50);
        printf("Specie: ");
        fgets((*((*liv).pomi + i)).specie, 50, stdin);
        (*((*liv).pomi + i)).specie[strcspn((*((*liv).pomi + i)).specie, "\n")] = 0;

        printf("Varsta: ");
        scanf("%d", &(*((*liv).pomi + i)).varsta);

        printf("Rodeste? (1-DA / 0-NU): ");
        scanf("%d", &(*((*liv).pomi + i)).rodeste);
        getchar(); 
    }
}

void afisare(struct livada liv) {
    for (int i = 0; i < liv.n; i++) {
        printf("\nPom %d: %s, varsta %d, rodeste: %s", i + 1,
            (*(liv.pomi + i)).specie, (*(liv.pomi + i)).varsta,
            (*(liv.pomi + i)).rodeste ? "DA" : "NU");
    }
}


struct pom* varsta(struct livada liv) {

    struct pom* min = NULL;

    for (int i = 0; i < liv.n; i++) {

        if ((*(liv.pomi + i)).rodeste == 1) {
            if (min == NULL || (*(liv.pomi + i)).varsta < (*min).varsta) {
                min = (liv.pomi + i);
            }
        }
    }
    return min;
}

void cauta_specie(struct livada liv) {
    char *cautat = (char*)malloc(50 * sizeof(char));
    printf("\n\nIntroduceti specia cautata: ");
    fgets(cautat, 50, stdin);
    cautat[strcspn(cautat, "\n")] = 0;

    printf("Rezultate pentru %s:", cautat);
    for (int i = 0; i < liv.n; i++) {
        if (strcmp((*(liv.pomi + i)).specie, cautat) == 0) {
            printf("\nPom varsta %d, rodeste: %s", (*(liv.pomi + i)).varsta, (*(liv.pomi + i)).rodeste ? "DA" : "NU");
        }
    }
    printf("\n\n");
    free(cautat);
}

int main() {

	struct livada liv;

    citire(&liv);
    afisare(liv);

    struct pom* p_min = varsta(liv);
    if (p_min) {
        printf("\n\nCel mai tanar pom fructifer: %s cu varsta de %d ani", (*p_min).specie, (*p_min).varsta);
    }

    cauta_specie(liv);

    for (int i = 0; i < liv.n; i++) {
        free((*(liv.pomi + i)).specie);
    }
    free(liv.pomi);

	return 0;
}
