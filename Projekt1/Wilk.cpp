#include <iostream>

#include "Swiat.h"
#include "Organizm.h"
#include "Zwierze.h"
#include "Wilk.h"

Wilk::Wilk() : Zwierze()
{
	_sila = 9;
	_inicjatywa = 5;
}

Wilk::Wilk(int x, int y, Swiat* swiat) : Zwierze(9, 5, x, y, swiat)
{

}

void Wilk::SetRuch(char ruch)
{
	Zwierze::SetRuch(ruch);
}

int Wilk::GetOstatniRuch() const
{
	return Zwierze::GetOstatniRuch();
}

char Wilk::GetSymbol() const
{
	return _symbol;
}

string Wilk::GetNazwa() const
{
	return "Wilk";
}

void Wilk::Akcja()
{
	Zwierze::Akcja();
}

void Wilk::Kolizja(Organizm* atakujacy)
{
	Zwierze::Kolizja(atakujacy);
}