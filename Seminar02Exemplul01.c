#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct StructuraCarte {
    int id;
    int nrPagini;
    float pret;
    char* titlu;
    char* numeAutor;
    unsigned char categorie;
};
typedef struct StructuraCarte Carte;

void afisareCarte(Carte c) {
    printf("ID: %d ", c.id);
    printf("Pagini: %d ", c.nrPagini);
    printf("Pret: %.2f ", c.pret);
    printf("Titlu: %s ", c.titlu);
    printf("Autor: %s ", c.numeAutor);
    printf("Cat: %c\n", c.categorie);
}

void afisareVectorCarti(Carte* carti, int nrCarti) {

    for (int i = 0; i < nrCarti; i++) {
        afisareCarte(carti[i]);
    }
    printf("\n\n");
}

void adaugaCarteInVector(Carte** carti, int* nrCarti, Carte carteNoua) {

    Carte* temp = (Carte*)malloc(sizeof(Carte) * ((*nrCarti) + 1));

    for (int i = 0; i < *nrCarti; i++) {
        temp[i] = (*carti)[i];
    }
    temp[*nrCarti] = carteNoua;
    if (*carti != NULL) {
        free(*carti);
    }

    *carti = temp;
    (*nrCarti)++;
}

Carte citireCarteFisier(FILE* file) {
    Carte c;
    char buffer[100]; 
    char sep[] = ",\n";

    if (fgets(buffer, 100, file)) {
        char* token = strtok(buffer, sep);
        c.id = atoi(token);
        c.nrPagini = atoi(strtok(NULL, sep));
        c.pret = (float)atof(strtok(NULL, sep));

        char* aux;
        aux = strtok(NULL, sep);
        c.titlu = (char*)malloc(strlen(aux) + 1);
        strcpy(c.titlu, aux);

        aux = strtok(NULL, sep);
        c.numeAutor = (char*)malloc(strlen(aux) + 1);
        strcpy(c.numeAutor, aux);

        c.categorie = strtok(NULL, sep)[0];
    }
    return c;
}

Carte* citireVectorCartiFisier(const char* numeFisier, int* nrCartiCitite) {
    FILE* file = fopen(numeFisier, "r");
    if (!file) {
        printf("Eroare la deschiderea fisierului\n");
        return NULL;
    }

    Carte* carti = NULL;
    *nrCartiCitite = 0;

  
    while (!feof(file)) {

        adaugaCarteInVector(&carti, nrCartiCitite, citireCarteFisier(file));
    }
    fclose(file);

    return carti;
}

void dezalocareVectorCarti(Carte** vector, int* nrCarti) {
    for (int i = 0; i < (*nrCarti); i++) {
        free((*vector)[i].titlu);
        free((*vector)[i].numeAutor);
    }
    free(*vector);
    *vector = NULL;
    *nrCarti = 0;
}

int main() {
    Carte* carti = NULL;
    int nrCarti = 0;

   
    carti = citireVectorCartiFisier("carti.txt", &nrCarti);

    if (carti != NULL) {
        afisareVectorCarti(carti, nrCarti);
        dezalocareVectorCarti(&carti, &nrCarti);
        
    }

    return 0;
}