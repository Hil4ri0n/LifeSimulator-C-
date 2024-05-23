#include <iostream>

#include "Swiat.h"
#include "Organizm.h"
#include "Roslina.h"
#include "Barszcz_sosnowskiego.h"

Barszcz_sosnowskiego::Barszcz_sosnowskiego() : Roslina()
{
	_sila = 10;
}

Barszcz_sosnowskiego::Barszcz_sosnowskiego(int x, int y, Swiat* swiat) : Roslina(10, x, y, swiat)
{

}



string Barszcz_sosnowskiego::GetNazwa() const
{
	return "Barszcz sosnowskiego";
}

char Barszcz_sosnowskiego::GetSymbol() const
{
	return _symbol;
}

void Barszcz_sosnowskiego::Akcja()
{
	Organizm** org = new Organizm * [4];
	org[0] = _swiat->GetPolePlanszy(_x, _y - 1);
	org[1] = _swiat->GetPolePlanszy(_x + 1, _y);
	org[2] = _swiat->GetPolePlanszy(_x, _y + 1);
	org[3] = _swiat->GetPolePlanszy(_x - 1, _y);

	for (int i = 0; i < 4; i++) {
		if ((org[i] != nullptr) && org[i]->CzyJestZwierzeciem())
		{
			this->KillLog(org[i]);
			_swiat->DeleteOrganism(org[i]);
		}
	}

	int los = rand() % 100;
	if (los < _prawdopodobienstwo)
	{
		Roslina::Akcja();
	}
	delete[] org;
}

void Barszcz_sosnowskiego::Kolizja(Organizm* atakujacy)
{
	atakujacy->KillLog(this);

	_swiat->DeleteOrganism(atakujacy);
}