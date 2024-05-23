#ifndef Wilcze_jagody_Defined
#define Wilcze_jagody_Defined

#include <iostream>
#include <string.h>

#include "Roslina.h"

using namespace std;

class Swiat;
class Organizm;
class Roslina;

class Wilcze_jagody : public Roslina
{
private:
	const char _symbol = 'j';
	const int _prawdopodobienstwo = 20;
public:
	Wilcze_jagody();
	Wilcze_jagody(int x, int y, Swiat* swiat);

	char GetSymbol() const override;
	string GetNazwa() const override;

	void Akcja() override;
	void Kolizja(Organizm* atakujacy) override;
};

#endif