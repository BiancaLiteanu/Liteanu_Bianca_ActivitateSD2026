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

//creare structura pentru un nod dintr-o lista simplu inlantuita
typedef struct Nod Nod;
struct Nod {
	Masina info;
	Nod* next;
};

//creare structura pentru tabela de dispersie
// aceasta este un vector de liste
struct HashTable {
	int dim;
	Nod** vector;
};
typedef struct HashTable HashTable;

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

void afisareListaMasini(Nod* cap) {
	if (cap == NULL) {
		printf("Lista este vida.\n");
		return;
	}

	Nod* temp = cap;
	// Parcurgem lista până la final
	while (temp != NULL) {
		// Apelăm funcția de afișare pentru structura Masina din interiorul nodului
		afisareMasina(temp->info);

		// Trecem la următorul nod
		temp = temp->next;
	}
}

void adaugaMasinaInLista(Nod** cap, Masina masinaNoua) {
	//adauga la final in lista primita o noua masina pe care o primim ca parametru
	Nod* nod = (Nod*)malloc(sizeof(Nod));
	nod->info = masinaNoua;
	nod->next = NULL;
	while (*cap) {
		*cap = (*cap)->next;
	}
	*cap = nod;

}


HashTable initializareHashTable(int dimensiune) {
	HashTable ht;
	//initializeaza vectorul de liste si seteaza fiecare lista ca fiind NULL;
	ht.dim = dimensiune;
	ht.vector = (Nod**)malloc(sizeof(Nod*) * dimensiune);
	for (int i = 0; i < dimensiune; i++) {
		ht.vector[i] = NULL;
	}
	return ht;
}

int calculeazaHash(int id, int dimensiune) {
	if (dimensiune <= 0) {
		return -1; // Protecție împotriva împărțirii la zero
	}
	// Folosim ID-ul mașinii ca atribut pentru clusterizare
	return id % dimensiune;
}

void inserareMasinaInTabela(HashTable hash, Masina galerie) {
	//este folosit mecanismul CHAINING
	//este determinata pozitia si se realizeaza inserarea pe pozitia respectiva
	// 1. Determinam pozitia in tabela folosind functia hash
	// Folosim ID-ul masinii ca atribut pentru clusterizare
	int pozitie = calculeazaHash(galerie.id, hash.dim);

	// 2. Cream un nou nod care va contine informatia masinii
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	if (nou == NULL) {
		printf("Eroare la alocarea memoriei pentru nod!\n");
		return;
	}

	nou->info = galerie; // Copiem structura masinii in nod

	// 3. Inseram nodul in lista de la pozitia determinata (Mecanism CHAINING)
	// Inserarea se face la inceputul listei pentru eficienta maxima
	nou->next = hash.vector[pozitie];
	hash.vector[pozitie] = nou;
}

HashTable citireMasiniDinFisier(const char* numeFisier) {
	//functia primeste numele fisierului, il deschide si citeste toate masinile din fisier
	//prin apelul repetat al functiei citireMasinaDinFisier()
	// aceste masini sunt inserate intr-o tabela de dispersie initializata aici
	//ATENTIE - la final inchidem fisierul/stream-ul
	FILE* f = fopen(numeFisier, "r");
	HashTable ht = initializareHashTable(10);
	if (f) {
		while (!feof(f)) {
			Masina m = citireMasinaDinFisier(f);
			if(m.model != NULL) {
				inserareMasinaInTabela(ht, m);
			}
			else {
				//daca modelul este NULL inseamna ca am ajuns la finalul fisierului
				break;
			}
		}
	}
}

void afisareTabelaDeMasini(HashTable ht) {
	//sunt afisate toate masinile cu evidentierea clusterelor realizate
	// Verificăm dacă tabela a fost inițializată
	if (ht.vector == NULL) {
		printf("Tabela de dispersie nu este initializata.\n");
		return;
	}

	printf("=== AFISARE TABELA HASH (DIMENSIUNE: %d) ===\n", ht.dim);

	for (int i = 0; i < ht.dim; i++) {
		// Afișăm indexul clusterului curent
		printf("Cluster [%d]: ", i);

		if (ht.vector[i] == NULL) {
			printf("Gol\n");
		}
		else {
			printf("\n");
			Nod* temp = ht.vector[i];
			while (temp != NULL) {
				// Adăugăm un indent pentru a vizualiza apartenența la cluster
				printf("  -> ");
				afisareMasina(temp->info);
				temp = temp->next;
			}
		}
		printf("------------------------------------------\n");
	}
}

void dezalocareTabelaDeMasini(HashTable *ht) {
	//sunt dezalocate toate masinile din tabela de dispersie
	if (ht == NULL || ht->vector == NULL) {
		return;
	}

	for (int i = 0; i < ht->dim; i++) {
		Nod* temp = ht->vector[i];
		while (temp != NULL) {
			// 1. Eliberam sirurile de caractere alocate din Masina
			if (temp->info.model != NULL) {
				free(temp->info.model);
				temp->info.model = NULL;
			}
			if (temp->info.numeSofer != NULL) {
				free(temp->info.numeSofer);
				temp->info.numeSofer = NULL;
			}

			// 2. Eliberam nodul curent, dar salvam adresa urmatorului
			Nod* deSters = temp;
			temp = temp->next;
			free(deSters);
		}
		// Setam capul listei de pe pozitia i ca fiind NULL
		ht->vector[i] = NULL;
	}

	// 3. Eliberam vectorul de liste
	free(ht->vector);
	ht->vector = NULL;
	ht->dim = 0;

	printf("Tabela a fost dezalocata cu succes.\n");
}

float* calculeazaPreturiMediiPerClustere(HashTable ht, int* nrClustere) {
	if (ht.vector == NULL || ht.dim <= 0) {
		*nrClustere = 0;
		return NULL;
	}

	// Alocăm un vector pentru a stoca mediile. 
	// Dimensiunea este egală cu dimensiunea tabelei (numărul de clustere).
	float* medii = (float*)malloc(sizeof(float) * ht.dim);
	if (!medii) return NULL;

	for (int i = 0; i < ht.dim; i++) {
		float sumaPreturi = 0.0f;
		int contorMasini = 0;
		Nod* temp = ht.vector[i];

		// Parcurgem lista din clusterul curent
		while (temp != NULL) {
			sumaPreturi += temp->info.pret;
			contorMasini++;
			temp = temp->next;
		}

		// Calculăm media (evităm împărțirea la zero dacă clusterul e gol)
		if (contorMasini > 0) {
			medii[i] = sumaPreturi / contorMasini;
		}
		else {
			medii[i] = 0.0f; // Sau o valoare sentință dacă clusterul e vid
		}
	}

	// Setăm numărul de elemente din vectorul returnat
	*nrClustere = ht.dim;
	return medii;
}

Masina getMasinaDupaCheie(HashTable ht /*valoarea pentru masina cautata*/) {
	Masina m;
	//cauta masina dupa valoarea atributului cheie folosit in calcularea hash-ului
	//trebuie sa modificam numele functiei 
	return m;
}

int main() {


	return 0;
}