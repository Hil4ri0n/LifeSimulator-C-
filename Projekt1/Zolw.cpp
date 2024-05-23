#include <iostream>

#include "Swiat.h"
#include "Organizm.h"
#include "Zwierze.h"
#include "Zolw.h"

#define GORA 1
#define PRAWO 2
#define DOL 3
#define LEWO 4

Zolw::Zolw() : Zwierze()
{
	_sila = 2;
	_inicjatywa = 1;
}

Zolw::Zolw(int x, int y, Swiat* swiat) : Zwierze(2, 1, x, y, swiat)
{

}

void Zolw::SetRuch(char ruch)
{
	Zwierze::SetRuch(ruch);
}

int Zolw::GetOstatniRuch() const
{
	return Zwierze::GetOstatniRuch();
}

char Zolw::GetSymbol() const
{
	return _symbol;
}

string Zolw::GetNazwa() const
{
	return "Zolw";
}

void Zolw::Akcja()
{
	int los = rand() % 100 + 1;
	if (los % 4 == 0)
	{
		Zwierze::Akcja();
	}
	else
	{
		_ostatni_ruch = 0;
	}
}

void Zolw::Kolizja(Organizm* atakujacy)
{
	if (atakujacy->GetSila() < 5 && atakujacy->GetSymbol() != _symbol)
	{
		atakujacy->DrawBack();
	}
	else
	{
		Zwierze::Kolizja(atakujacy);
	}	
}