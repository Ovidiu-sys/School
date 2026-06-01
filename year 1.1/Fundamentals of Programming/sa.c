#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<crtdbg.h>

void citire(int** a, int n, int m) {
	for (int i = 0; i < n; i++) 
		for (int j = 0; j < m; j++) {
			printf("%d %d: ", i, j);
			scanf("%d", (*(a+i)+j));
		}
}

void afisare(int **a, int n, int m) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			printf("%d ", *(*(a+i)+j));
		}
		printf("\n");
	}
}

int nr_sa(int **a, int n, int m ) {
	
	int cnt = 0;
	
	for (int i = 0; i < n; i++) {

		int min_linie = INT_MAX, max_linie = INT_MIN;

		for (int j = 0; j < m; j++) {
			if (*(*(a + i) +j ) < min_linie)
				min_linie = *(*(a + i) +j );
			if (*(*(a + i)+j) > max_linie)
				max_linie = *(*(a + i) +j );
		}
		for (int j = 0; j < m; j++) {
			if (*(*(a + i) + j) == min_linie) {
				bool ok_min = true;
				for (int i_min = 0; i_min < n; i_min++)
					if (*(*(a + i) + j) < *(*(a + i_min) + j)) {
						ok_min = false;
						break;
					}
				if (ok_min == true)
					cnt++;
			}
			else
				if (*(*(a + i) + j) == max_linie) {
					bool ok_max = true;
					for (int i_max = 0; i_max < n; i_max++)
						if (*(*(a + i) + j) > *(*(a + i_max) + j)) {
							ok_max = false;
							break;
						}
					if (ok_max == true)
						cnt++;
				}
		}
	}
	return cnt;
}


int main() {

	int n, m;
	printf("n: ");
	scanf("%d", &n);
	printf("m: ");
	scanf("%d", &m);

	int **a = (int**)malloc(n * sizeof(int*));
	if (a == NULL) {
		printf("eroare alocare");
		return 1;
	}
	for (int i = 0; i < n; i++) {
		*(a + i) = (int*)malloc(m * sizeof(int));
		if (*(a + i) == NULL) {
			printf("eroare alocare");
			return 1;
		}
	}
	citire(a, n, m);
	afisare(a, n, m);

	int res = nr_sa(a, n, m);
	printf("\n%d\n", res);

	for (int i = 0; i < n; i++) {
		free(*(a + i));
		*(a + i) = NULL;
	}
	free(a);
	a = NULL;

	_CrtDumpMemoryLeaks();

	return 0;
}
