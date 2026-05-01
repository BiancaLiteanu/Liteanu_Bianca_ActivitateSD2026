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
	Nod* stanga;
	Nod* dreapta;
};

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


void adaugaMasinaInArbore(Nod** radacina, Masina masinaNoua) {

	if (*radacina) {
		if ((*radacina)->info.id < masinaNoua.id) {
			adaugaMasinaInArbore(&(*radacina)->dreapta, masinaNoua);
		}
		if ((*radacina)->info.id > masinaNoua.id) {
			adaugaMasinaInArbore(&(*radacina)->stanga, masinaNoua);
		}
	}
	else {
		Nod* nou = (Nod*)malloc(sizeof(Nod));
		nou->info = masinaNoua;
		nou->stanga = nou->dreapta = NULL;
		(*radacina) = nou;
	}
  }


Nod* citireArboreDeMasiniDinFisier(const char* numeFisier) {

	Nod* radacina = NULL;
	FILE* f = fopen(numeFisier, "r");
	while (!feof(f)) {
		adaugaMasinaInArbore(&radacina, citireMasinaDinFisier(f));
	}
	fclose(f);
	return radacina;
}

void afisareMasiniDinArbore(Nod* radacina) {
	//preordine - R-S-D
	//postordine - S-D-R
	//inordine - S-R-D
	if (radacina) {
		afisareMasina(radacina->info);
		afisareMasiniDinArbore(radacina->stanga);
		afisareMasiniDinArbore(radacina->dreapta);
	}

}

void afisareMasiniDinArboreInordine(Nod* radacina) {
	//preordine - R-S-D
	//postordine - S-D-R
	//inordine - S-R-D
	if (radacina) {
		afisareMasiniDinArboreInordine(radacina->stanga);
		afisareMasina(radacina->info);
		afisareMasiniDinArboreInordine(radacina->dreapta);
	}

}

void dezalocareArboreDeMasini(Nod** radacina) {
	//sunt dezalocate toate masinile si arborele de elemente
	//trebuie postordine
	if (*radacina) {
		dezalocareArboreDeMasini(&(*radacina)->stanga);
		dezalocareArboreDeMasini(&(*radacina)->dreapta);
		free((*radacina)->info.model);
		free((*radacina)->info.numeSofer);
		free(*radacina);
		*radacina = NULL;

	}
}

Masina getMasinaByID(Nod* radacina, int id) {
	if (radacina) {
		if (radacina->info.id == id) {
			Masina m = radacina->info;
			m.model = (char*)malloc(strlen(radacina->info.model) + 1);
			strcpy_s(m.model, strlen(radacina->info.model) + 1, radacina->info.model);
			m.numeSofer = (char*)malloc(strlen(radacina->info.numeSofer) + 1);
			strcpy_s(m.numeSofer, strlen(radacina->info.numeSofer) + 1, radacina->info.numeSofer);
			return m;

		}
		if (radacina->info.id < id) {
			return getMasinaByID(radacina->dreapta, id);

		}
		if (radacina->info.id > id) {
			return getMasinaByID(radacina->stanga, id);
		}
	}
	else {
		Masina m;
		m.id = -1;
		return m;
	}



}

int determinaNumarNoduri(Nod* radacina) {
	if (radacina) {
		int stanga = determinaNumarNoduri(radacina->stanga);
		int dreapta = determinaNumarNoduri(radacina->dreapta);
		return (1 + stanga + dreapta);
	}
	return 0;
}

int calculeazaInaltimeArbore(Nod* radacina) {
	//calculeaza inaltimea arborelui care este data de 
	//lungimea maxima de la radacina pana la cel mai indepartat nod frunza
	if (radacina) {
		int inaltimeStanga = calculeazaInaltimeArbore(radacina->stanga);
		int inaltimeDreapta = calculeazaInaltimeArbore(radacina->dreapta);
		return (1 + max(inaltimeStanga, inaltimeDreapta));
	}



	return 0;
}

float calculeazaPretTotal(Nod* radacina) {
	//calculeaza pretul tuturor masinilor din arbore.

	if (radacina) {
		return calculeazaPretTotal(radacina->stanga) + calculeazaPretTotal(radacina->dreapta) + radacina->info.pret;
	}



	return 0;
}

float calculeazaPretulMasinilorUnuiSofer(Nod* radacina, const char* numeSofer) {
	//calculeaza pretul tuturor masinilor unui sofer.
	if (radacina) {
		float suma = calculeazaPretulMasinilorUnuiSofer(radacina->dreapta, numeSofer)
			+ calculeazaPretulMasinilorUnuiSofer(radacina->stanga, numeSofer);
		if (strcmp(radacina->info.numeSofer, numeSofer) == 0) {
			return radacina->info.pret + suma;
		}
		else {
			return suma;
		}
	}
	else {
		return 0;
	}


}

int main() {
	Nod* radacina = citireArboreDeMasiniDinFisier("masini_arbore.txt");
	afisareMasiniDinArboreInordine(radacina);

	afisareMasiniDinArbore(radacina);
	Masina m = getMasinaByID(radacina, 5);
	afisareMasina(m);
	int nrNoduri = determinaNumarNoduri(radacina);
	printf("%d", nrNoduri);

	int h = calculeazaInaltimeArbore(radacina);
	printf("%d", h);

	float pret = calculeazaPretulMasinilorUnuiSofer(radacina, "Maria");
	printf("%f", pret);

	dezalocareArboreDeMasini(&radacina);



	return 0;
}