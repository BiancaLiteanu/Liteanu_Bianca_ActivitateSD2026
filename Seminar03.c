#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct StructuraMasina {
	int id;
	int nrUsi;
	float pret;
	char* model;
	char* numeSofer;
	unsigned char serie;
};
typedef struct StructuraMasina Masina;

typedef struct Nod Nod;
struct Nod {
	Masina info;
	Nod* next;
};

Masina citireMasinaDinFisier(FILE* file) {
	char buffer[100];
	char sep[3] = ",\n";
	if (fgets(buffer, 100, file) == NULL) {
		Masina m = { 0 }; return m;
	}
	char* aux;
	Masina m1;
	aux = strtok(buffer, sep);
	m1.id = atoi(aux);
	m1.nrUsi = atoi(strtok(NULL, sep));
	m1.pret = (float)atof(strtok(NULL, sep));

	aux = strtok(NULL, sep);
	m1.model = (char*)malloc(strlen(aux) + 1);
	strcpy(m1.model, aux);

	aux = strtok(NULL, sep);
	m1.numeSofer = (char*)malloc(strlen(aux) + 1);
	strcpy(m1.numeSofer, aux);

	m1.serie = *strtok(NULL, sep);
	return m1;
}

void afisareMasina(Masina masina) {
	printf("Id: %d\n", masina.id);
	printf("Nr. usi : %d\n", masina.nrUsi);
	printf("Pret: %.2f\n", masina.pret);
	printf("Model: %s\n", masina.model);
	printf("Nume sofer: %s\n", masina.numeSofer);
	printf("Serie: %c\n\n", masina.serie);
}

void afisareListaMasini(Nod* cap) {
	while (cap != NULL) {
		afisareMasina(cap->info);
		cap = cap->next;
	}
}

void adaugaLaInceputInLista(Nod** cap, Masina masinaNoua) {
	Nod* nodNou = (Nod*)malloc(sizeof(Nod));
	nodNou->info = masinaNoua;
	nodNou->next = *cap; 
	*cap = nodNou;       
}

void adaugaMasinaInLista(Nod** cap, Masina masinaNoua) {
	Nod* nodNou = (Nod*)malloc(sizeof(Nod));
	nodNou->info = masinaNoua;
	nodNou->next = NULL;
	if ((*cap) == NULL) {
		(*cap) = nodNou;
	}
	else {
		Nod* aux = *cap;
		while (aux->next != NULL) {
			aux = aux->next;
		}
		aux->next = nodNou;
	}
}

void* citireListaMasiniDinFisier(const char* numeFisier) {
	FILE* file = fopen(numeFisier, "r");
	if (file) {
		Nod* cap = NULL;
		while (!feof(file)) {
			long pos = ftell(file);
			char test;
			if (fscanf(file, " %c", &test) == EOF) break;
			fseek(file, pos, SEEK_SET);

			adaugaMasinaInLista(&cap, citireMasinaDinFisier(file));
		}
		fclose(file);
		return cap;
	}
	return NULL;
}

void dezalocareListaMasini(Nod** cap) {
	while (*cap) {
		Nod* p = *cap;
		(*cap) = p->next;
		if (p->info.model) free(p->info.model);
		if (p->info.numeSofer) free(p->info.numeSofer);
		free(p);
	}
}

float calculeazaPretMediu(Nod* cap) {
	float suma = 0;
	int nr = 0;
	while (cap) {
		suma += cap->info.pret;
		nr++;
		cap = cap->next;
	}
	return (nr > 0) ? (suma / nr) : 0;
}
float calculeazaPretulMasinilorUnuiSofer(Nod* cap, const char* numeSofer) {
	float suma = 0;
	while (cap) {
		if (strcmp(cap->info.numeSofer, numeSofer) == 0) {
			suma += cap->info.pret;
		}
		cap = cap->next;
	}
	return suma;
}

void stergeMasiniDinSeria(Nod** cap, char serieCautata) {
	
	while ((*cap) && (*cap)->info.serie == serieCautata) {
		Nod* temp = *cap;
		(*cap) = temp->next;
		if (temp->info.numeSofer) free(temp->info.numeSofer);
		if (temp->info.model) free(temp->info.model);
		free(temp);
	}

	Nod* p = *cap;
	while (p && p->next) {
		if (p->next->info.serie == serieCautata) {
			Nod* temp = p->next;
			p->next = temp->next;
			if (temp->info.model) free(temp->info.model);
			if (temp->info.numeSofer) free(temp->info.numeSofer); 
			free(temp);
		}
		else {
			p = p->next;
		}
	}
}

int main() {
	Nod* cap = NULL;
	cap = (Nod*)citireListaMasiniDinFisier("masini.txt");
	printf("Lista initiala\n");
	afisareListaMasini(cap);
	printf("Pret mediu: %.2f\n", calculeazaPretMediu(cap));
	const char* soferCautat = "Popescu";
	printf("Pret total masini %s: %.2f\n", soferCautat, calculeazaPretulMasinilorUnuiSofer(cap, soferCautat));
	printf("\nDupa stergerea seriei A\n");
	stergeMasiniDinSeria(&cap, 'A');
	afisareListaMasini(cap);
	dezalocareListaMasini(&cap);

	return 0;
}