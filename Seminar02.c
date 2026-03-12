//#define _CRT_SECURE_NO_WARNINGS
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//
////trebuie sa folositi fisierul masini.txt
////sau va creati un alt fisier cu alte date
//
//struct StructuraMasina {
//	int id;
//	int nrUsi;
//	float pret;
//	char* model;
//	char* numeSofer;
//	unsigned char serie;
//};
//typedef struct StructuraMasina Masina;
//
//void afisareMasina(Masina masina) {
//	printf("id: %d ", masina.id);
//	printf("Nr usi: %d" , masina.nrUsi);
//	printf("Pret: %.2f" ,masina.pret);
//	printf("Model: %s",masina.model);
//	printf("Nume sofer: %s" ,masina.numeSofer);
//	printf("Serie: %c" ,masina.serie);
//	printf("\n\n");
//}
//
//void afisareVectorMasini(Masina* masini, int nrMasini) {
//	for (int i = 0; i < nrMasini; i++) {
//		afisareMasina(masini[i]);
//	}
//
//
//}
//
//void adaugaMasinaInVector(Masina** masini, int* nrMasini, Masina masinaNoua) {
//	
//	Masina* temp = (Masina*)malloc(sizeof(Masina) * ((*nrMasini) + 1));
//	for (int i = 0; i < *nrMasini; i++) {
//		temp[i] = (*masini)[i];
//	}
//	temp[*nrMasini] = masinaNoua;
//	free(*masini);
//	(*masini) = temp;
//	(*nrMasini)++;
//
//
//}
//
//Masina citireMasinaFisier(FILE* file) {
//
//	Masina m;
//	char buffer[50];
//	char sep[3] = ",\n";
//	fgets(buffer, 50, file);
//	m.id = atoi(strtok(buffer, sep));
//	m.nrUsi = atoi(strtok(NULL, sep));
//	m.pret = atof(strtok(NULL, sep));
//
//	char* aux;
//	aux = strtok(NULL, sep);
//	m.model = (char*)malloc(sizeof(char) * strlen(aux) + 1);
//	strcpy(m.model, aux);
//
//	aux = strtok(NULL, sep);
//	m.numeSofer = (char*)malloc(sizeof(char) * (strlen(aux) + 1));
//	strcpy(m.numeSofer, aux);
//
//	m.serie = strtok(NULL, sep)[0];
//	return m;
//
//}
//
//Masina* citireVectorMasiniFisier(const char* numeFisier, int* nrMasiniCitite) {
//
//	FILE* file;
//	file = fopen(numeFisier, "r");
//	Masina* masini = NULL;
//	*nrMasiniCitite = NULL;
//
//	while (!feof(file)) {
//
//		adaugaMasinaInVector(&masini, nrMasiniCitite, citireMasinaFisier(file));
//	}
//	fclose(file);
//
//	return masini;
//}
//
//void dezalocareVectorMasini(Masina** vector, int* nrMasini) {
//	for (int i = 0; i < (*nrMasini); i++) {
//		free((*vector)[i].model);
//		free((*vector)[i].numeSofer);  //deref, deplasare, deref ,accesare
//	}
//
//	free(*vector);
//	*vector = NULL;
//	*nrMasini = NULL;
//
//
//
//}
//
//int main() {
//
//	Masina* masini = NULL;
//	int nrMasini = 0;
//
//	masini = citireVectorMasiniFisier("masini.txt", &nrMasini);
//	afisareVectorMasini(masini, nrMasini);
//
//
//	return 0;
//}