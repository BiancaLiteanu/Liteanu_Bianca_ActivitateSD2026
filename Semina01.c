//#include<stdio.h>
//#include<malloc.h>
//
//
//struct Biblioteca {
//	int id;
//	int nrCarti;
//	char* nume;
//	float suprafata;
//	char sector;
//};
//
//struct Biblioteca initializare(int id, int nrCarti, char* nume, float suprafata, char sector) {
//	struct Biblioteca s;
//	s.id = id;
//	s.nrCarti = nrCarti;
//	s.nume = (char*)malloc(sizeof(char) * (strlen(nume) + 1));
//	strcpy(s.nume, nume);
//	s.suprafata = suprafata;
//	s.sector = sector;
//	return s;
//}
//
//struct Biblioteca copiazaBiblioteca(struct Biblioteca sursa){
//
//	return initializare(sursa.id, sursa.nrCarti, sursa.nume, sursa.suprafata, sursa.sector);
//}
//
//void afisare(struct Biblioteca s) {
//	printf("%d, %d, %s, %.2f, %d \n", s.id, s.nrCarti, s.nume, s.suprafata, (int)s.sector);
//}
//
//void afisareVector(struct Biblioteca* vector, int nrElemente) {
//	for (int i = 0; i < nrElemente; i++) {
//		afisare(vector[i]);
//	}
//}
//
//struct Biblioteca* copiazaPrimeleNElemente(struct Biblioteca* vector, int nrElemente, int nrElementeCopiate) {
//	struct Biblioteca* vectorNou = NULL;
//	if (nrElementeCopiate > nrElemente) {
//		nrElementeCopiate = nrElemente;
//	}
//	vectorNou = (struct Biblioteca*)malloc(sizeof(struct Biblioteca) * nrElementeCopiate);
//	for (int i = 0; i < nrElementeCopiate; i++) {
//		vectorNou[i] = copiazaBiblioteca(vector[i]);
//	}
//	return vectorNou;
//}
//
//void dezalocare(struct Biblioteca** vector, int* nrElemente) {
//	
//	for (int i = 0; i < *nrElemente; i++) {
//		free((*vector)[i].nume); //deref+deplasare+deref+deref+accesare * ; [] ; .
//	}
//	free((*vector));
//	*vector = NULL;
//	*nrElemente = 0;
//}
//
//void copiazaBibliotecileCuSuprafataMare(struct Biblioteca* vector, int nrElemente, float suprafataMinima, struct Biblioteca** vectorNou, int* dimensiune) {
//	*dimensiune = 0;
//	for (int i = 0; i < nrElemente; i++) {
//		if (vector[i].suprafata > suprafataMinima)
//			(*dimensiune)++;
//	}
//	*vectorNou = (struct Biblioteca*)malloc(sizeof(struct Biblioteca) * (*dimensiune));
//	int contor = 0;
//	for (int i = 0; i < nrElemente; i++) {
//		if (vector[i].suprafata > suprafataMinima) {
//			(*vectorNou)[contor++] = copiazaBiblioteca(vector[i]);
//		}
//	}
//}
//
//struct Biblioteca getPrimulElementConditionat(struct Biblioteca* vector, int nrElemente, const char* conditie) {
//	
//	struct Biblioteca s;
//	s.id = -1; 
//	s.nume = NULL;
//
//	for (int i = 0; i < nrElemente; i++) {
//		if (strcmp(vector[i].nume, conditie) == 0) {
//			return copiazaBiblioteca(vector[i]);
//		}
//	}
//	return s;
//}
//
//int main() {
//	struct Biblioteca b;
//	b = initializare(1, 400, "Biblioteca", 300.5, 4);
//	printf("Elementul b: \n");
//	afisare(b);
//	printf("\n");
//	int nrBiblioteci = 5;
//	struct Biblioteca* vectorB = (struct Biblioteca*)malloc(sizeof(struct Biblioteca) * nrBiblioteci);
//
//	//vectorB[0] = b; shallow copy
//	vectorB[0] = copiazaBiblioteca(b);
//	vectorB[1] = initializare(2, 400, "Biblioteca2", 200, 3);
//	vectorB[2] = initializare(3, 300, "Biblioteca3", 200, 6);
//	vectorB[3] = initializare(4, 400, "Biblioteca4", 400, 1);
//	vectorB[4] = initializare(5, 500, "Biblioteca5", 500, 2);
//
//	printf("Elementele vectorului: \n");
//	afisareVector(vectorB, 5);
//	printf("\n");
//
//	int nrElementeCopiate = 3;
//	struct Biblioteca* copie = copiazaPrimeleNElemente(vectorB, nrBiblioteci, nrElementeCopiate);
//	printf("Primele %d elemente copiate: \n", nrElementeCopiate);
//	afisareVector(copie, nrElementeCopiate);
//	printf("\n");
//
//	dezalocare(&copie, &nrElementeCopiate);
//	printf("Dupa dezalocare copie: \n");
//	afisareVector(copie, nrElementeCopiate);
//	printf("\n");
//
//	struct Biblioteca* biblioteciSuprafataMare = NULL;
//	int numarBiblioteciSuprafataMare = 0;
//	copiazaBibliotecileCuSuprafataMare(vectorB, nrBiblioteci, 250.0f, &biblioteciSuprafataMare, &numarBiblioteciSuprafataMare);
//	printf("Bibliotecile cu suprafata mare: \n");
//	afisareVector(biblioteciSuprafataMare, numarBiblioteciSuprafataMare);
//	printf("\n");
//
//	printf("Rezultat cautare: \n");
//	afisare(getPrimulElementConditionat(vectorB, nrBiblioteci, "Biblioteca4"));
//	
//	dezalocare(&biblioteciSuprafataMare, &numarBiblioteciSuprafataMare);
//	dezalocare(&vectorB, &nrBiblioteci);
//	free(b.nume); 
//
//	
//
//	return 0;
//}
//
//
