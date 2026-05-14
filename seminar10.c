// graful este o multime de noduri si de muchii care vor lega resp. noduri

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//trebuie sa folositi fisierul masini.txt
//sau va creati un alt fisier cu alte date

struct StructuraMasina {
	int id;
	int nrUsi;
	float pret;
	char* model;
	char* numeSofer;
	unsigned char serie;
};
typedef struct StructuraMasina Masina;

Masina citireMasinaDinFisier(FILE* file) {
	char buffer[100];
	char sep[3] = ",\n";
	fgets(buffer, 100, file);
	char* aux;
	Masina m1;
	aux = strtok(buffer, sep);
	m1.id = atoi(aux);
	m1.nrUsi = atoi(strtok(NULL, sep));
	m1.pret = atof(strtok(NULL, sep));
	aux = strtok(NULL, sep);
	m1.model = malloc(strlen(aux) + 1);
	strcpy_s(m1.model, strlen(aux) + 1, aux);

	aux = strtok(NULL, sep);
	m1.numeSofer = malloc(strlen(aux) + 1);
	strcpy_s(m1.numeSofer, strlen(aux) + 1, aux);

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

//1. 
// structuri necesare
//dorim stocarea unui graf intr-o lista de liste
//astfel avem nod ListaPrincipala si NodListaSecundara

typedef struct NodPrincipal NodPrincipal;
typedef struct NodSecundar NodSecundar;

struct NodPrincipal {
	Masina info;
	NodPrincipal* next;
	NodSecundar* vecini;

};

struct NodSecundar {
	NodSecundar* next;
	NodPrincipal* info;
};



//2.
//functii de inserare in liste
//si in principala si in secundara

void inserareListaP(NodPrincipal** graf, Masina masina) {
	NodPrincipal* nou = (NodPrincipal*)malloc(sizeof(NodPrincipal));
	nou->info = masina;
	nou->next = NULL;
	nou->vecini = NULL;
	if (*graf) {
		NodPrincipal* aux = *graf;
		while (aux->next) {
			aux = aux->next;
		}
		aux->next = nou;
	}
	else {
		*graf = nou;
	}

}

void inserareListaS(NodSecundar** listaS, NodPrincipal* masina) {
	NodSecundar* nou = (NodSecundar*)malloc(sizeof(NodSecundar));
	nou->info = masina;
	nou->next = NULL;
	if (*listaS) {
		NodSecundar* aux = *listaS;
		while (aux->next) {
			aux = aux->next;
		}
		aux->next = nou;
	}
	else {
		*listaS = nou;
	}


}




//3.
//functie de cautarea in lista principala dupa ID
NodPrincipal* cautaNodDupaID(NodPrincipal* listaPrincipala, int id) {
	while ((listaPrincipala) && listaPrincipala->info.id != id) {
		listaPrincipala = listaPrincipala->next;
	}
	return listaPrincipala;

}

//4.
//inserare muchie
void inserareMuchie(NodPrincipal* listaPrincipala, int idStart, int idStop) {
	if (listaPrincipala) {
		NodPrincipal* nodStart = cautaNodDupaID(listaPrincipala, idStart);
		NodPrincipal* nodStop = cautaNodDupaID(listaPrincipala, idStop);
		if (nodStart && nodStop) {
			inserareListaS(&(nodStart->vecini), nodStop); // amandoua pt ca avem graf neorientat 
			inserareListaS(&(nodStop->vecini), nodStart);
		}
	}
}


NodPrincipal* citireNoduriMasiniDinFisier(const char* numeFisier) {

	FILE* f = fopen(numeFisier, "r");
	NodPrincipal* graf = NULL;

	while (!feof(f)) {
		inserareListaP(&graf, citireMasinaDinFisier(f));
	}
	fclose(f);
	return graf;
}

void citireMuchiiDinFisier(NodPrincipal* graf, const char* numeFisier) {

	FILE* f = fopen(numeFisier, "r");

	while (!feof(f)) {
		int idStart;
		int idStop;
		fscanf(f, "%d %d", &idStart, &idStop); //fscanf vrea sa modifice, deci dam adresa 
		inserareMuchie(graf, idStart, idStop);

	}
	fclose(f);




}

void afisareLista(NodPrincipal* graf, int id) {
	NodPrincipal* nod = cautaNodDupaID(graf, id);
	NodSecundar* cap = nod->vecini;
	while(cap) {
		afisareMasina(cap->info->info);
		cap = cap->next;
	}
}

void dezalocareNoduriGraf(void* listaPrincipala) {
	//sunt dezalocate toate masinile din graf 
	//si toate nodurile celor doua liste
}

int main() {

	NodPrincipal* nodPrincipal = NULL;
	nodPrincipal = citireNoduriMasiniDinFisier("masini.txt");
	citireMuchiiDinFisier(nodPrincipal, "muchii.txt");
	afisareLista(nodPrincipal, 1);

	return 0;
}