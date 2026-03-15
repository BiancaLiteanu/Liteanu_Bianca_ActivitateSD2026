#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <string.h>


struct structClinicaAnimalute {
	int cod;
	int varsta;
	float greutate;
	char* specie;
	char* nume;
	unsigned char gen;
};
typedef struct structClinicaAnimalute ClinicaAnimalute;


typedef struct Nod Nod;
struct Nod {
	ClinicaAnimalute info;
	Nod* next;
};


ClinicaAnimalute citireAnimalutDinFisier(FILE* f) {
	char buffer[100]; 
	char sep[3] = ",\n";
	fgets(buffer, 50, f);
	ClinicaAnimalute c;
	char* aux;

	c.cod = atoi(strtok(buffer, sep));
	c.varsta = atoi(strtok(NULL, sep));
	c.greutate = atof(strtok(NULL, sep));
	aux = strtok(NULL, sep);
	c.specie = malloc(strlen(aux) + 1);
	strcpy(c.specie, aux);

	aux = strtok(NULL, sep);
	c.nume = malloc(strlen(aux) + 1);
	strcpy(c.nume, aux);

	c.gen = *strtok(NULL, sep);


	return c;

}

void afisareAnimalut(ClinicaAnimalute c) {
	printf("%d\n", c.cod);
	printf("%d\n", c.varsta);
	printf("%.2f\n", c.greutate);
	printf("%s\n", c.specie);
	printf("%s\n", c.nume);
	printf("%c\n", c.gen);

}


void afisareListaAnimalute(Nod* cap) {
	while (cap != NULL) {
		afisareAnimalut(cap->info);
		cap = cap->next;
	}
}


void adaugaLaInceputInLista(Nod** cap, ClinicaAnimalute animalutNou) {

	Nod* aux = (Nod*)malloc(sizeof(Nod));
	aux->info = animalutNou;
	aux->next = *cap;
	*cap = aux;

}

void adaugaLaSfarsitnLista(Nod** cap, ClinicaAnimalute animalutNou) {
	Nod* nodNou = (Nod*)malloc(sizeof(Nod));
	nodNou->info = animalutNou;
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

void* citireListaAnimaluteDinFisier(const char* numeFisier) {
	FILE* file = fopen(numeFisier, "r");
	if (file) {
		Nod* cap = NULL;
		while (!feof(file)) {
			adaugaLaSfarsitnLista(&cap, citireAnimalutDinFisier(file));
		}
		fclose(file);
		return cap;
	}
	return NULL;
}

void dezalocareListaAnimalute(Nod** cap) {
	while (*cap) {
		Nod* p = *cap;
		(*cap) = p->next;
		if (p->info.specie) free(p->info.specie);
		if (p->info.nume) free(p->info.nume);
		free(p);
	}
}

void stergePacientiDupaGen(Nod** cap, char genCautat) {
	
	while ((*cap) && (*cap)->info.gen == genCautat) {
		Nod* temp = *cap;
		(*cap) = temp->next;
		if (temp->info.specie) {
			free(temp->info.specie);
		}
		if (temp->info.nume) {
			free(temp->info.nume);
		}
		free(temp); 
	}

	Nod* p = *cap;
	while (p) {
		while (p->next && p->next->info.gen != genCautat) {
			p = p->next;
		}
		if (p->next) {
			Nod* temp = p->next;
			p->next = temp->next; 
			if (temp->info.specie) {
				free(temp->info.specie);
			}
			if (temp->info.nume) {
				free(temp->info.nume);
			}
			free(temp);
		}
		else {
			p = p->next; 
		}
	}
}

float calculGreutateMedieSpecie(Nod* cap, const char* specieCautata) {
	float suma = 0;
	int contor = 0;
	while (cap != NULL) {
		if (strcmp(cap->info.specie, specieCautata) == 0) {
			suma = suma + cap->info.greutate;
			contor = contor + 1;
		}
		cap = cap->next;
	}
	if (contor > 0) {
		return suma / contor;
	}
	return 0;
}

int getCodCelMaiTanarDupaGen(Nod* cap, char genCautat) {
	int minVarsta = 999;
	int codGasit = -1;

	while (cap != NULL) {
		if (cap->info.gen == genCautat) {
			if (cap->info.varsta < minVarsta) {
				minVarsta = cap->info.varsta;
				codGasit = cap->info.cod;
			}
		}
		cap = cap->next;
	}
	return codGasit;
}

int main() {
	Nod* cap = NULL;
	cap = (Nod*)citireListaAnimaluteDinFisier("animalute.txt");
	afisareListaAnimalute(cap);

	const char* specieCautata = "Caine";
	printf("\nGreutate medie pentru %s: %.2f kg\n", specieCautata, calculGreutateMedieSpecie(cap, specieCautata));

	char genCautat = 'M';
	printf("Cod cel mai tanar pacient gen %c: %d\n", genCautat, getCodCelMaiTanarDupaGen(cap, genCautat));

	printf("\nDupa stergerea animalutelor de gen F\n");
	stergePacientiDupaGen(&cap, 'F');
	afisareListaAnimalute(cap);
	dezalocareListaAnimalute(&cap);
	return 0;
}