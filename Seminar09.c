//#define _CRT_SECURE_NO_WARNINGS
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//
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
//
//typedef struct Nod Nod;
//struct Nod {
//	Masina info;
//	Nod* stanga;
//	Nod* dreapta;
//
//};
//
//
//Masina citireMasinaDinFisier(FILE* file) {
//	char buffer[100];
//	char sep[3] = ",\n";
//	fgets(buffer, 100, file);
//	char* aux;
//	Masina m1;
//	aux = strtok(buffer, sep);
//	m1.id = atoi(aux);
//	m1.nrUsi = atoi(strtok(NULL, sep));
//	m1.pret = atof(strtok(NULL, sep));
//	aux = strtok(NULL, sep);
//	m1.model = malloc(strlen(aux) + 1);
//	strcpy_s(m1.model, strlen(aux) + 1, aux);
//
//	aux = strtok(NULL, sep);
//	m1.numeSofer = malloc(strlen(aux) + 1);
//	strcpy_s(m1.numeSofer, strlen(aux) + 1, aux);
//
//	m1.serie = *strtok(NULL, sep);
//	return m1;
//}
//
//void afisareMasina(Masina masina) {
//	printf("Id: %d\n", masina.id);
//	printf("Nr. usi : %d\n", masina.nrUsi);
//	printf("Pret: %.2f\n", masina.pret);
//	printf("Model: %s\n", masina.model);
//	printf("Nume sofer: %s\n", masina.numeSofer);
//	printf("Serie: %c\n\n", masina.serie);
//}
//
//int calculeazaInaltimeArbore(Nod* radacina) {
//	if (radacina) {
//		return max(calculeazaInaltimeArbore(radacina->stanga), calculeazaInaltimeArbore(radacina->dreapta)) + 1;
//	}
//	else {
//		return 0;
//	}
//}
//
//
//char calculGE(Nod* radacina) {
//	if (radacina) {
//		return calculeazaInaltimeArbore(radacina->stanga) - calculeazaInaltimeArbore(radacina->dreapta);
//	}
//	else {
//		return 0;
//	}
//
//}
//
//void rotireStanga(Nod** radacina) {
//	Nod* aux = (*radacina)->dreapta;
//	(*radacina)->dreapta = aux->stanga;
//	aux->stanga = *radacina;
//	(*radacina) = aux;
//
//}
//
//void rotireDreapta(Nod** radacina) {
//	Nod* aux = (*radacina)->stanga;
//	(*radacina)->stanga = aux->dreapta;
//	aux->dreapta = *radacina;
//	(*radacina) = aux;
//}
//
//
//void adaugaMasinaInArboreEchilibrat(Nod** radacina, Masina masinaNoua) {
//	if (*radacina) {
//		if (masinaNoua.id < (*radacina)->info.id) {
//			adaugaMasinaInArboreEchilibrat(&(*radacina)->stanga, masinaNoua);
//		}
//		else {
//			adaugaMasinaInArboreEchilibrat(&(*radacina)->dreapta, masinaNoua);
//		}
//		int grad = calculGE(*radacina);
//		if (grad == 2) { //dezechilibrat in partea stanga
//			if (calculGE((*radacina)->stanga) == -1) {
//				rotireStanga(&(*radacina)->stanga); //& se aplica pe left
//				rotireDreapta(radacina);
//			}
//			else {
//				rotireDreapta(radacina);
//			}
//		}
//		else {
//			if (grad == -2) {
//				if (calculGE((*radacina)->dreapta) == 1) {
//					rotireDreapta(&(*radacina)->dreapta);
//				}
//				rotireStanga(radacina);
//			}
//		}
//	}
//	else {
//		Nod* nou = (Nod*)malloc(sizeof(Nod));
//		nou->info = masinaNoua;
//		nou->stanga = nou->dreapta = NULL;
//		(*radacina) = nou;
//	}
//}
//
//Nod* citireArboreDeMasiniDinFisier(const char* numeFisier) {
//	//functia primeste numele fisierului, il deschide si citeste toate masinile din fisier
//	//prin apelul repetat al functiei citireMasinaDinFisier()
//	//ATENTIE - la final inchidem fisierul/stream-ul
//	FILE* f = fopen(numeFisier, "r");
//	Nod* arbore = NULL;
//	while (!feof(f)) {
//		adaugaMasinaInArboreEchilibrat(&arbore, citireMasinaDinFisier(f));
//	}
//	fclose(f);
//	return arbore;
//}
//
//void afisareMasiniDinArbore(Nod* radacina) {
//	if (radacina) {
//		afisareMasina(radacina->info);
//		afisareMasiniDinArbore(radacina->stanga);
//		afisareMasiniDinArbore(radacina->dreapta);
//	}
//}
//
//void dezalocareArboreDeMasini(Nod** radacina) {
//	if (*radacina) {
//		dezalocareArboreDeMasini(&(*radacina)->stanga);
//		dezalocareArboreDeMasini(&(*radacina)->dreapta);
//
//		free((*radacina)->info.numeSofer);
//		free((*radacina)->info.model);
//		free(*radacina);
//		*radacina = NULL;
//	}
//}
//
//Masina getMasinaByID(Nod* radacina, int id) {
//	if (radacina) {
//		if (radacina->info.id == id) {
//			Masina m = radacina->info;
//			m.model = (char*)malloc(strlen(radacina->info.model) + 1);
//			strcpy_s(m.model, strlen(radacina->info.model) + 1, radacina->info.model);
//			m.numeSofer = (char*)malloc(strlen(radacina->info.numeSofer) + 1);
//			strcpy_s(m.numeSofer, strlen(radacina->info.numeSofer) + 1, radacina->info.numeSofer);
//			return m;
//
//		}
//		if (radacina->info.id < id) {
//			return getMasinaByID(radacina->dreapta, id);
//
//		}
//		if (radacina->info.id > id) {
//			return getMasinaByID(radacina->stanga, id);
//		}
//	}
//	else {
//		Masina m;
//		m.id = -1;
//		return m;
//	}
//
//}
//
//int determinaNumarNoduri(Nod* radacina) {
//	if (radacina) {
//		int stanga = determinaNumarNoduri(radacina->stanga);
//		int dreapta = determinaNumarNoduri(radacina->dreapta);
//		return (1 + stanga + dreapta);
//	}
//	return 0;
//
//}
//
//float calculeazaPretTotal(Nod* radacina) {
//
//	if (radacina) {
//		return calculeazaPretTotal(radacina->stanga) + calculeazaPretTotal(radacina->dreapta) + radacina->info.pret;
//	}
//
//
//
//	return 0;
//}
//
//float calculeazaPretulMasinilorUnuiSofer(Nod* radacina, const char* numeSofer) {
//	float suma = 0;
//	if (radacina) {
//
//		suma += calculeazaPretulMasinilorUnuiSofer(radacina->stanga, numeSofer);
//		suma += calculeazaPretulMasinilorUnuiSofer(radacina->dreapta, numeSofer);
//		if (strcmp(radacina->info.numeSofer, numeSofer) == 0) {
//			suma += radacina->info.pret;
//
//		}
//
//
//	}
//	return suma;
//}
//
//int main() {
//	Nod* radacina = citireArboreDeMasiniDinFisier("masini.txt");
//	afisareMasiniDinArbore(radacina);
//	float suma = calculeazaPretulMasinilorUnuiSofer(radacina, "Ionescu");
//	printf("%f", suma);
//	Masina m = getMasinaByID(radacina, 5);
//	afisareMasina(m);
//	int nrNoduri = determinaNumarNoduri(radacina);
//	printf("%d", nrNoduri);
//
//	int h = calculeazaInaltimeArbore(radacina);
//	printf("%d", h);
//
//	float pret = calculeazaPretulMasinilorUnuiSofer(radacina, "Maria");
//	printf("%f", pret);
//	dezalocareArboreDeMasini(&radacina);
//	afisareMasiniDinArbore(radacina);
//
//	return 0;
//}