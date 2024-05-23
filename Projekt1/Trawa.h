#ifndef Trawa_Defined
#define Trawa_Defined

#include <iostream>
#include <string.h>

#include "Roslina.h"

using namespace std;

class Swiat;
class Organizm;
class Roslina;

class Trawa : public Roslina
{
private:
	const char _symbol = 't';
	const int _prawdopodobienstwo = 50;
public:
	Trawa();
	Trawa(int x, int y, Swiat* swiat);

	char GetSymbol() const override;
	string GetNazwa() const override;

	void Akcja() override;
	void Kolizja(Organizm* atakujacy) override;
};

#endif