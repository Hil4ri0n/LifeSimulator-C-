#include <iostream>

#include "Swiat.h"
#include "Organizm.h"
#include "Roslina.h"
#include "Wilcze_jagody.h"

Wilcze_jagody::Wilcze_jagody() : Roslina()
{
	_sila = 99;
}

Wilcze_jagody::Wilcze_jagody(int x, int y, Swiat* swiat) : Roslina(99, x, y, swiat)
{

}

char Wilcze_jagody::GetSymbol() const
{
	return _symbol;
}

string Wilcze_jagody::GetNazwa() const
{
	return "Wilcze jagody";
}

void Wilcze_jagody::Akcja()
{
	int los = rand() % 100;
	if (los < _prawdopodobienstwo)
	{
		Roslina::Akcja();
	}
}

void Wilcze_jagody::Kolizja(Organizm* atakujacy)
{
	atakujacy->KillLog(this);

	_swiat->DeleteOrganism(atakujacy);
}