#ifndef Owca_Defined
#define Owca_Defined

#include <iostream>
#include <string.h>

#include "Zwierze.h"

using namespace std;

class Swiat;
class Organizm;
class Zwierze;

class Owca : public Zwierze
{
private:
	const char _symbol = 'o';
public:
	Owca();
	Owca(int x, int y, Swiat* swiat);

	void SetRuch(char ruch) override;

	int GetOstatniRuch() const override;
	char GetSymbol() const override;
	string GetNazwa() const override;

	void Akcja() override;
	void Kolizja(Organizm* atakujacy) override;
};

#endif