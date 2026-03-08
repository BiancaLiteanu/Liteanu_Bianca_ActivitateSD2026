#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct StructuraJocVideo {
	int id;
	int oreJucate;
	float pret;
	char* titlu;
	char* dezvoltator;
	unsigned char rating;
};
typedef struct StructuraJocVideo JocVideo;

void adaugaJocInVector(JocVideo** jocuri, int* nrJocuri, JocVideo jocNou) {
	JocVideo* temp = (JocVideo*)malloc(sizeof(JocVideo) * ((*nrJocuri) + 1));
	for (int i = 0; i < *nrJocuri; i++) {
		temp[i] = (*jocuri)[i];
	}
	temp[*nrJocuri] = jocNou;
	if (*jocuri) free(*jocuri);
	(*jocuri) = temp;
	(*nrJocuri)++;
}

JocVideo citireJocFisier(FILE* file) {
	JocVideo j;
	char buffer[100];
	char sep[3] = ",\n";
	if (fgets(buffer, 100, file)) {
		j.id = atoi(strtok(buffer, sep));
		j.oreJucate = atoi(strtok(NULL, sep));
		j.pret = (float)atof(strtok(NULL, sep));
		char* aux = strtok(NULL, sep);
		j.titlu = (char*)malloc(strlen(aux) + 1);
		strcpy(j.titlu, aux);
		aux = strtok(NULL, sep);
		j.dezvoltator = (char*)malloc(strlen(aux) + 1);
		strcpy(j.dezvoltator, aux);
		j.rating = strtok(NULL, sep)[0];
	}
	return j;
}


JocVideo* getJocuriPremium(JocVideo* jocuri, int nrJocuri, float pragPret, int* nrJocuriRezultat) {
	JocVideo* rezultat = NULL;
	*nrJocuriRezultat = 0;
	for (int i = 0; i < nrJocuri; i++) {
		if (jocuri[i].pret > pragPret) {
			JocVideo copie;
			copie.id = jocuri[i].id;
			copie.oreJucate = jocuri[i].oreJucate;
			copie.pret = jocuri[i].pret;
			copie.rating = jocuri[i].rating;
			copie.titlu = (char*)malloc(strlen(jocuri[i].titlu) + 1);
			strcpy(copie.titlu, jocuri[i].titlu);
			copie.dezvoltator = (char*)malloc(strlen(jocuri[i].dezvoltator) + 1);
			strcpy(copie.dezvoltator, jocuri[i].dezvoltator);
			adaugaJocInVector(&rezultat, nrJocuriRezultat, copie);
		}
	}
	return rezultat;
}


int cautaJocDupaDezvoltator(JocVideo* jocuri, int nrJocuri, const char* numeCautat) {
	for (int i = 0; i < nrJocuri; i++) {
		if (strcmp(jocuri[i].dezvoltator, numeCautat) == 0) {
			return i;
		}
	}
	return -1; 
}


float calculMediaOre(JocVideo* jocuri, int nrJocuri) {
	if (nrJocuri == 0) return 0;
	float suma = 0;
	for (int i = 0; i < nrJocuri; i++) {
		suma += (float)jocuri[i].oreJucate;
	}
	return suma / nrJocuri;
}

void dezalocareVectorJocuri(JocVideo** vector, int* nrMasini) {
	if (*vector == NULL) return;
	for (int i = 0; i < (*nrMasini); i++) {
		free((*vector)[i].titlu);
		free((*vector)[i].dezvoltator);
	}
	free(*vector);
	*vector = NULL;
	*nrMasini = 0;
}

int main() {
	int nrJocuri = 0;
	JocVideo* catalog = NULL;

	FILE* f = fopen("jocuri.txt", "r");
	if (f) {
		while (!feof(f)) {
			adaugaJocInVector(&catalog, &nrJocuri, citireJocFisier(f));
		}
		fclose(f);
	}

	printf("Media orelor jucate: %.2f\n", calculMediaOre(catalog, nrJocuri));
	int pozitie = cautaJocDupaDezvoltator(catalog, nrJocuri, "Nintendo");
	if (pozitie != -1) {
		printf("Jocul gasit: %s\n", catalog[pozitie].titlu);
	}
	int nrJocuriPremium = 0;
	JocVideo* premium = getJocuriPremium(catalog, nrJocuri, 100.0f, &nrJocuriPremium);

	printf("\nJocuri Premium");
	for (int i = 0; i < nrJocuriPremium; i++) printf("%s (%.2f )\n", premium[i].titlu, premium[i].pret);

	
	dezalocareVectorJocuri(&catalog, &nrJocuri);
	dezalocareVectorJocuri(&premium, &nrJocuriPremium);

	return 0;
}