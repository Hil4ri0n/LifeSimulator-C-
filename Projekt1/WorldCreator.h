#ifndef Generator_swiata_Defined
#define Generator_swiata_Defined

#include <iostream>
#include <string.h>

using namespace std;

class Swiat;

class WorldCreator
{
private:
	Swiat* world;
	void GenerowaniePunktowDlaOrganizmow(int* pola, int* ileZwZGat);
	void OdczytajWspolrzedne(int* pola, int* x, int* y, int* ktory);
	void WczytajOrganizm(string nazwa, int sila, int ini, int x, int y, int wiek);
public:
	WorldCreator(Swiat* swiat);

	void Generuj_swiat();
	bool Wczytaj_swiat();
	void Zapisz_swiat();

	~WorldCreator();
};
#endif;