//#define _CRT_SECURE_NO_WARNINGS
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
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
//typedef struct Nod Nod;
//struct Nod {
//	Masina info;
//	Nod* next;
//	Nod* prev;
//};
//
//typedef struct ListaDubla ListaDubla;
//struct ListaDubla {
//	int nrNoduri;
//	Nod* first;
//	Nod* last;
//};
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
//void afisareListaMasini(ListaDubla lista) {
//	printf("Lista contine %d noduri:\n", lista.nrNoduri);
//	Nod* nod = lista.first;
//	while (nod) {
//		afisareMasina(nod->info);
//		nod = nod->next;
//	}
//}
//
//void afisareInversaListaMasini(ListaDubla lista) {
//	Nod* nod = lista.last;
//	while (nod) {
//		afisareMasina(nod->info);
//		nod = nod->prev;
//	}
//}
//
//void adaugaMasinaInLista(ListaDubla* lista, Masina masinaNoua) {
//	Nod* nod = (Nod*)malloc(sizeof(Nod));
//	nod->info = masinaNoua;
//	nod->prev = lista->last;
//	nod->next = NULL;
//	if (lista->last) {
//		lista->last->next = nod;
//	}
//	else {
//		lista->first = nod;
//	}
//	lista->last = nod;
//	lista->nrNoduri++;
//}
//
//void adaugaLaInceputInLista(ListaDubla* lista, Masina masinaNoua) {
//	Nod* nod = (Nod*)malloc(sizeof(Nod));
//	nod->info = masinaNoua;
//	nod->prev = NULL;
//	nod->next = lista->first;
//	if (lista->first) {
//		lista->first->prev = nod;
//	}
//	else {
//		lista->last = nod;
//	}
//	lista->first = nod;
//	lista->nrNoduri++;
//}
//
//ListaDubla citireLDMasiniDinFisier(const char* numeFisier) {
//	FILE* f = fopen(numeFisier, "r");
//	ListaDubla lista;
//	lista.last = NULL;
//	lista.first = NULL;
//	lista.nrNoduri = 0;
//	if (!f)
//	{
//		return lista;
//	}
//	while (!feof(f)) {
//		adaugaMasinaInLista(&lista, citireMasinaDinFisier(f));
//	}
//	fclose(f);
//	return lista;
//
//
//}
//
//void dezalocareLDMasini(ListaDubla* lista) {
//	Nod* nod = lista->first;
//	while (nod) {
//		Nod* aux = nod;
//		nod = nod->next;
//		if (aux->info.model) { free(aux->info.model); }
//		if (aux->info.numeSofer) { free(aux->info.numeSofer); }
//		free(aux);
//	}
//	lista->first = NULL;
//	lista->last = NULL;
//	lista->nrNoduri = 0;
//}
//
//float calculeazaPretMediu(ListaDubla lista) {
//	float pret = 0;
//	if (lista.first == NULL) {
//		return 0;
//	}
//	else {
//		/*Nod* nod = lista.first;*/
//		/*while (nod) {
//			pret += nod->info.pret;
//			nod = nod->next;
//		}*/
//		for (Nod* nod = lista.first; nod != NULL; nod = nod->next) {
//			pret += nod->info.pret;
//			nod = nod->next;
//		}
//	}
//
//	return pret / lista.nrNoduri;
//}
//
//void stergeMasinaDupaID(ListaDubla* lista, int id) {
//	if (lista->first) {
//		Nod* nod;
//		for (nod = lista->first; nod != NULL && nod->info.id != id; nod = nod->next);
//		if (!nod) return;
//		else {
//			if (nod->prev == NULL) {
//				if (nod->next) {
//					nod->next->prev = NULL;
//				}
//				else {
//					lista->last = NULL;
//				}
//				lista->first = nod->next;
//				free(nod->info.model);
//				free(nod->info.numeSofer);
//				free(nod);
//
//			}
//			else {
//				nod->prev->next = nod->next; //ne gandim sa ocoleasca nodul
//				if (nod->prev)
//				{
//					nod->next->prev = nod->prev;
//				}
//				else {
//					lista->last = nod->prev;
//				}
//				free(nod->info.model);
//				free(nod->info.numeSofer);
//				free(nod);
//			}
//			lista->nrNoduri--;
//		}
//
//
//	}
//}
//
//char* getNumeSoferMasinaScumpa(ListaDubla lista) {
//
//	if (lista.first == NULL) return NULL;
//	Nod* nodMaxim = lista.first;
//	float pretMaxim = lista.first->info.pret;
//	Nod* curent = lista.first->next;
//	while (curent != NULL) {
//		if (curent->info.pret > pretMaxim) {
//			pretMaxim = curent->info.pret;
//			nodMaxim = curent;
//		}
//		curent = curent->next;
//	}
//	return nodMaxim->info.numeSofer;
//}
//
//int main() {
//
//	ListaDubla lista = citireLDMasiniDinFisier("masini.txt");
//	afisareListaMasini(lista);
//	float pret = 0;
//	pret = calculeazaPretMediu(lista);
//	printf("%f", pret);
//	stergeMasinaDupaID(&lista, 1);
//	afisareListaMasini(lista);
//	char* sofer = getNumeSoferMasinaScumpa(lista);
//	printf("Soferul cu masina cea mai scumpa este: %s\n", sofer);
//	dezalocareLDMasini(&lista);
//	afisareListaMasini(lista);
//
//	return 0;
//}