#include <iostream>

#include "Swiat.h"
#include "Organizm.h"
#include "Roslina.h"
#include "Guarana.h"

Guarana::Guarana() : Roslina()
{
	_sila = 0;
}

Guarana::Guarana(int x, int y, Swiat* swiat) : Roslina(0, x, y, swiat)
{

}

char Guarana::GetSymbol() const
{
	return _symbol;
}

string Guarana::GetNazwa() const
{
	return "Guarana";
}

void Guarana::Akcja()
{
	int los = rand() % 100;
	if (los < _prawdopodobienstwo)
	{
		Roslina::Akcja();
	}
}

void Guarana::Kolizja(Organizm* atakujacy)
{
	if (this->GetSila() > atakujacy->GetSila())
	{
		this->KillLog(atakujacy);
		_swiat->DeleteOrganism(atakujacy);
	}
	else
	{
		atakujacy->KillLog(this);
		atakujacy->SetSila(atakujacy->GetSila() + 3);

		string komentarz = this->GetNazwa() + ": \twzmocnienie " + atakujacy->GetNazwa() + " o 3 pkt";
		_swiat->AddComment(komentarz);

		_swiat->SetPolePlanszy(this->GetX(), this->GetY(), atakujacy);
		_swiat->DeleteOrganism(this);
		atakujacy->Rysowanie();
	}
}