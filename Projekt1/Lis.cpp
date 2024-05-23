#include <iostream>

#include "Swiat.h"
#include "Organizm.h"
#include "Zwierze.h"
#include "Lis.h"

Lis::Lis() : Zwierze()
{
	_sila = 3;
	_inicjatywa = 7;
}

Lis::Lis(int x, int y, Swiat* swiat) : Zwierze(3, 7, x, y, swiat)
{

}

void Lis::SetRuch(char ruch)
{
	Zwierze::SetRuch(ruch);
}

int Lis::GetOstatniRuch() const
{
	return Zwierze::GetOstatniRuch();
}

char Lis::GetSymbol() const
{
	return _symbol;
}

string Lis::GetNazwa() const
{
	return "Lis";
}

void Lis::Akcja()
{
	Zwierze::RunAway();
}

void Lis::Kolizja(Organizm* atakujacy)
{
	Zwierze::Kolizja(atakujacy);
}