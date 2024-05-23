#include <iostream>

#include "Swiat.h"
#include "Organizm.h"
#include "Roslina.h"
#include "Mlecz.h"

Mlecz::Mlecz() : Roslina()
{
	_sila = 0;
}

Mlecz::Mlecz(int x, int y, Swiat* swiat) : Roslina(0, x, y, swiat)
{

}

char Mlecz::GetSymbol() const
{
	return _symbol;
}

string Mlecz::GetNazwa() const
{
	return "Mlecz";
}

void Mlecz::Akcja()
{
	int los;
	for (int i = 0; i < 3; i++)
	{
		los = rand() % 100;
		if (los < _prawdopodobienstwo)
		{
			Roslina::Akcja();
		}
	}
}

void Mlecz::Kolizja(Organizm* atakujacy)
{
	Roslina::Kolizja(atakujacy);
}