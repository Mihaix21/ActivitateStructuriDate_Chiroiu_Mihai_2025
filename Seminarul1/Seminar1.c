#include<stdio.h>
#include<stdlib.h>

struct Masina {
	int id; // 4
	int nrLocuri; // 4
	char* marca;  //sir de caractere; depinde de lungimea pointerului - 4 sau 8
	float capacitateC; // 4
	char normaPoluare; //un singur caracter; 4
};

struct Masina initializare(int id, int nrLocuri, const char* marca, float capacitateC, char normaPoluare) { //se pune const char* pentru ca se da un sir constant de caractere "ceva"
	struct Masina m;
	m.id = 1;
	m.nrLocuri = nrLocuri;
	m.capacitateC = capacitateC;
	m.normaPoluare = normaPoluare;
	m.marca = (char*)malloc(strlen(marca) + 1);
	strcpy_s(m.marca, strlen(marca) + 1, marca);

	return m;
}

void afisare(struct Masina m) {
	printf("ID masina: %d\nNr. locuri: %d\nCapacitate cilindrica: %f\nMarca: %s\nNorma poluare: EURO%c\n", m.id, m.nrLocuri, m.capacitateC, m.marca, m.normaPoluare);
}

void modifica_nrLocuri(struct Masina* m, int nrNou) {
	if (nrNou > 0)
		m->nrLocuri = nrNou; //setter
}

void dezalocare(struct Masina* m) {
	free(m->marca);
	//m->marca = NULL;
	(*m).marca = NULL;
	m = NULL;

}

int main() {
	struct Masina masina = initializare(1, 5, "Dacia", 1.5, '4'); //articol
	// "4", '4' - "sir de caracter + \0" - 2 octeti, 'un singur caracter' - 1 octet

	afisare(masina);

	modifica_nrLocuri(&masina, 6);
	afisare(masina);

	dezalocare(&masina);
	afisare(masina);

	printf("%d\n", sizeof(char*));
	printf("%d\n", sizeof(struct Masina*));

	printf("%d\n", sizeof(masina));

	return 0;
}