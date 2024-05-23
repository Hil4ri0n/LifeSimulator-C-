#ifndef Zolw_Defined
#define Zolw_Defined

#include <iostream>
#include <string.h>

#include "Zwierze.h"

using namespace std;

class Swiat;
class Organizm;
class Zwierze;

class Zolw : public Zwierze
{
private:
	const char _symbol = 'z';
public:
	Zolw();
	Zolw(int x, int y, Swiat* swiat);

	void SetRuch(char ruch) override;

	int GetOstatniRuch() const override;
	char GetSymbol() const override;
	string GetNazwa() const override;

	void Akcja() override;
	void Kolizja(Organizm* atakujacy) override;
};

#endif