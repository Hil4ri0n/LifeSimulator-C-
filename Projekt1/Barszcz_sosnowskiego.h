#ifndef Barszcz_sosnowskiego_Defined
#define Barszcz_sosnowskiego_Defined

#include <iostream>
#include <string.h>

#include "Roslina.h"

using namespace std;

class Swiat;
class Organizm;
class Roslina;

class Barszcz_sosnowskiego : public Roslina
{
private:
	const char _symbol = 'b';
	const int _prawdopodobienstwo = 10;
public:
	Barszcz_sosnowskiego();
	Barszcz_sosnowskiego(int x, int y, Swiat* swiat);

	char GetSymbol() const override;
	string GetNazwa() const override;

	void Akcja() override;
	void Kolizja(Organizm* atakujacy) override;
};

#endif