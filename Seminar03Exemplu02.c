//#define _CRT_SECURE_NO_WARNINGS
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//
//struct structProdusElectronic {
//	int id;
//	int garantieLuni;
//	float pret;
//	char* denumire;
//	char* brand;
//	unsigned char categorie;
//};
//typedef struct structProdusElectronic ProdusElectronic;
//
//typedef struct Nod Nod;
//struct Nod {
//	ProdusElectronic info;
//	Nod* next;
//};
//
//ProdusElectronic citireProdusDinFisier(FILE* file) {
//	char buffer[100];
//	char sep[3] = ",\n";
//	fgets(buffer, 100, file);
//	char* aux;
//	ProdusElectronic p1;
//	aux = strtok(buffer, sep);
//	p1.id = atoi(aux);
//	p1.garantieLuni = atoi(strtok(NULL, sep));
//	p1.pret = (float)atof(strtok(NULL, sep));
//	aux = strtok(NULL, sep);
//	p1.denumire = (char*)malloc(strlen(aux) + 1);
//	strcpy(p1.denumire, aux);
//
//	aux = strtok(NULL, sep);
//	p1.brand = (char*)malloc(strlen(aux) + 1);
//	strcpy(p1.brand, aux);
//
//	p1.categorie = *strtok(NULL, sep);
//	return p1;
//}
//
//void afisareProdus(ProdusElectronic produs) {
//	printf("Id: %d\n", produs.id);
//	printf("Garantie luni: %d\n", produs.garantieLuni);
//	printf("Pret: %.2f\n", produs.pret);
//	printf("Denumire: %s\n", produs.denumire);
//	printf("Brand: %s\n", produs.brand);
//	printf("Categorie: %c\n\n", produs.categorie);
//}
//
//void afisareListaProduse(Nod* cap) {
//	while (cap != NULL) {
//		afisareProdus(cap->info);
//		cap = cap->next;
//	}
//}
//
//void adaugaLaInceputInLista(Nod** cap, ProdusElectronic produsNou) {
//	Nod* nodNou = (Nod*)malloc(sizeof(Nod));
//	nodNou->info = produsNou;
//	nodNou->next = *cap;
//	*cap = nodNou;
//}
//
//void adaugaProdusInLista(Nod** cap, ProdusElectronic produsNou) {
//	Nod* nodNou = (Nod*)malloc(sizeof(Nod));
//	nodNou->info = produsNou;
//	nodNou->next = NULL;
//	if ((*cap) == NULL) {
//		(*cap) = nodNou;
//	}
//	else {
//		Nod* aux = *cap;
//		while (aux->next != NULL) {
//			aux = aux->next;
//		}
//		aux->next = nodNou;
//	}
//}
//
//void* citireListaProduseDinFisier(const char* numeFisier) {
//	FILE* file = fopen(numeFisier, "r");
//
//	if (file) {
//		Nod* cap = NULL;
//		while (!feof(file)) {
//			adaugaProdusInLista(&cap, citireProdusDinFisier(file));
//		}
//		fclose(file);
//		return cap;
//	}
//	return NULL;
//}
//
//void dezalocareListaProduse(Nod** cap) {
//	while (*cap) {
//		Nod* p = *cap;
//		(*cap) = p->next;
//		if (p->info.denumire) free(p->info.denumire);
//		if (p->info.brand) free(p->info.brand);
//		free(p);
//	}
//}
//
//float calculeazaPretMediu(Nod* cap) {
//	float suma = 0;
//	int nr = 0;
//	while (cap) {
//		suma += cap->info.pret;
//		nr++;
//		cap = cap->next;
//	}
//	return (nr > 0) ? (suma / nr) : 0;
//}
//
//float calculeazaPretulProduselorUnuiBrand(Nod* cap, const char* brand) {
//	float suma = 0;
//	while (cap) {
//		if (strcmp(cap->info.brand, brand) == 0) {
//			suma += cap->info.pret;
//		}
//		cap = cap->next;
//	}
//	return suma;
//}
//
//void stergeProduseDinCategoria(Nod** cap, char categorieCautata) {
//
//	while ((*cap) && (*cap)->info.categorie == categorieCautata) {
//		Nod* temp = *cap;
//		(*cap) = temp->next;
//		if (temp->info.brand) {
//			free(temp->info.brand);
//		}
//		if (temp->info.denumire) {
//			free(temp->info.denumire);
//		}
//		free(temp);
//	}
//
//	Nod* p = *cap;
//	while (p) {
//		while (p->next && p->next->info.categorie != categorieCautata) {
//			p = p->next;
//		}
//		if (p->next) {
//			Nod* temp = p->next;
//			p->next = temp->next;
//
//			if (temp->info.denumire) {
//				free(temp->info.denumire);
//			}
//			if (temp->info.brand) {
//				free(temp->info.brand);
//			}
//			free(temp);
//		}
//		else {
//			p = p->next;
//		}
//	}
//}
//
//int main() {
//	Nod* cap = NULL;
//	cap = (Nod*)citireListaProduseDinFisier("electronice.txt");
//	printf("Lista initiala\n");
//	afisareListaProduse(cap);
//	printf("Pret mediu: %.2f\n", calculeazaPretMediu(cap));
//	const char* brandCautat = "Apple";
//	printf("Pret total produse %s: %.2f\n", brandCautat, calculeazaPretulProduselorUnuiBrand(cap, brandCautat));
//	printf("\nDupa stergerea categoriei T\n");
//	stergeProduseDinCategoria(&cap, 'T');
//	afisareListaProduse(cap);
//	dezalocareListaProduse(&cap);
//
//	return 0;
//}