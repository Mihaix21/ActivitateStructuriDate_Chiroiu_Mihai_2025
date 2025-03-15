#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<malloc.h>

struct Masina {
	int id;
	int nrLocuri;
	char* marca;
	float capacitateC;
	char normaPoluare;
};

struct Masina initializare(int id, int nrLocuri, const char* marca, float capacitateC, char norma) {
	struct Masina m;
	m.id = id;
	m.capacitateC = capacitateC;
	m.nrLocuri = nrLocuri;

	m.normaPoluare = norma;
	if (marca == NULL)
		m.marca = NULL;
	else
	{
		m.marca = (char*)malloc((strlen(marca) + 1) * sizeof(char)); //se aloca numarul de octeti
		strcpy_s(m.marca, strlen(marca) + 1, marca);
	}
	return m;
}
void afisare(struct Masina m) {
	printf("ID masina: %d \nNr. Locuri: %d\nCapacitate:  %4.2f\nMarca: %s\nEuro%c\n\n", m.id, m.nrLocuri, m.capacitateC, m.marca, m.normaPoluare);
}

void modificaNrLocuri(struct Masina* m, int numarNou) {
	if (numarNou > 0)
		m->nrLocuri += numarNou;
}

void dezalocare(struct Masina* m) {

	free(m->marca);
	m->marca = NULL;
	// (*m).marca=NULL;
	// NU STERGEM NOI masina1! m este in stiva lui main, deci este gestionat automat - free(m); m = NULL;
}

void dezalocareV(struct Masina** vector, int* nrElemente) {
	for (int i = 0; i < *nrElemente; i++) {
		free((*vector)[i].marca);
	}
	free(*vector);
	*vector = NULL;
	*nrElemente = 0;  // resetare contor
}


void afisareVector(struct Masina* vector, int nrElemente) {
	for (int i = 0; i < nrElemente; i++)
		afisare(vector[i]);
}

struct Masina* copiazaPrimeleNElemente(struct Masina* vector, int nrElemente, int nrElementeCopiate) {

	struct Masina* vectorNou = NULL;
	vectorNou = (struct Masina*)malloc(nrElementeCopiate * sizeof(struct Masina));
	if (nrElementeCopiate > nrElemente)
		nrElementeCopiate = nrElemente;

	for (int i = 0; i < nrElementeCopiate; i++)
	{
		vectorNou[i] = initializare(vector[i].id, vector[i].nrLocuri, vector[i].marca, vector[i].capacitateC, vector[i].normaPoluare);

	}
	return vectorNou;
}



void copiazaMasiniCuCMare(struct Masina* vector, char nrElemente, float prag, struct Masina** vectorNou, int* dimensiune) {
	*dimensiune = 0;
	for (char i = 0; i < nrElemente; i++)
	{
		if (prag < vector[i].capacitateC)
			(*dimensiune)++;

	}
	if (*dimensiune > 0)
	{
		*vectorNou = (struct Masina*)malloc((*dimensiune) * sizeof(struct Masina));
		int j = 0;
		for (int i = 0; i < nrElemente; i++)
		{
			if (prag < vector[i].capacitateC)
			{

				(*vectorNou)[j] = vector[i];
				(*vectorNou)[j].marca = (char*)malloc(strlen(vector[i].marca) + 1);
				strcpy_s((*vectorNou)[j].marca, strlen(vector[i].marca) + 1, vector[i].marca);
				j++;
			}
		}
	}
}

struct Masina getPrimaMasinaDupaMArca(struct Masina* vector, int nrElemente, const char* conditie) {

	for (int i = 0; i < nrElemente; i++)
	{
		if (strcmp(vector[i].marca, conditie) == 0)
			return vector[i];
	}
	return initializare(1, 0, NULL, 0, '0');

}



int main() {
	struct Masina* vector;
	int nrElemente = 3;
	vector = (struct Masina*)malloc(nrElemente * sizeof(struct Masina));
	vector[0] = initializare(1, 3, "Dacia", 40, '5');
	vector[1] = initializare(2, 5, "Honda", 30, '6');
	vector[2] = initializare(3, 4, "Dacia", 50, '3');
	afisare(vector[0]);
	afisareVector(vector, nrElemente);
	struct Masina* vectorMasiniCopiate;
	int nrElementeCopiate = 2;
	printf("\n\nAfisare elemente copiate: \n");
	vectorMasiniCopiate = copiazaPrimeleNElemente(vector, nrElemente, nrElementeCopiate);
	afisareVector(vectorMasiniCopiate, nrElementeCopiate);
	dezalocareV(&vectorMasiniCopiate, &nrElementeCopiate);



	printf("\n\nAfisare masini cu capacitate cilindrica mare: \n\n");
	copiazaMasiniCuCMare(vector, (char)nrElemente, 35, &vectorMasiniCopiate, &nrElementeCopiate);
	afisareVector(vectorMasiniCopiate, nrElementeCopiate);
	dezalocareV(&vectorMasiniCopiate, &nrElementeCopiate);




	struct Masina m1 = getPrimaMasinaDupaMArca(vector, nrElemente, "Dacia");
	printf("Prima masina Dacia este: \n");
	afisare(m1);
	dezalocareV(&vector, &nrElemente);
	return 0;
}