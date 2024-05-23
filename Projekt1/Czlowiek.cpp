#include <iostream>
#include <string>

#include "Swiat.h"
#include "Organizm.h"
#include "Zwierze.h"
#include "Czlowiek.h"

#define UP_KEY 72
#define RIGHT_KEY 77
#define DOWN_KEY 80
#define LEFT_KEY 75
#define GORA 1
#define PRAWO 2
#define DOL 3
#define LEWO 4

using namespace std;

Czlowiek::Czlowiek(int x, int y, Swiat* swiat) : Zwierze(5, 4, x, y, swiat)
{
	cooldown = 0;
	_turyObecnegoStanuUmiejetnosci = 5;
	_umiejetnoscAktywowana = false;
}



void Czlowiek::SetCzyUmiejetnoscAktywowana(bool umiejetnoscAktywowana)
{
	_umiejetnoscAktywowana = umiejetnoscAktywowana;
}

void Czlowiek::SetCooldown(int cooldown) {
	this->cooldown = cooldown;
}

void Czlowiek::SetTuryObecnegoStanuUmiejetnosci(int tury)
{
	_turyObecnegoStanuUmiejetnosci = tury;
}

void Czlowiek::SetRuch(char ruch)
{
	switch (ruch) {
	case UP_KEY:
		_ostatni_ruch = GORA;
		break;
	case RIGHT_KEY:
		_ostatni_ruch = PRAWO;
		break;
	case DOWN_KEY:
		_ostatni_ruch = DOL;
		break;
	case LEFT_KEY:
		_ostatni_ruch = LEWO;
		break;
	}
}



int Czlowiek::GetOstatniRuch() const
{
	return Zwierze::GetOstatniRuch();
}

bool Czlowiek::CzyUmiejetnoscAktywowana() const
{
	return _umiejetnoscAktywowana;
}

int Czlowiek::GetTuryObecnegoStanuUmiejetnosci() const
{
	return _turyObecnegoStanuUmiejetnosci;
}

int Czlowiek::GetCooldown() const
{
	return cooldown;
}

char Czlowiek::GetSymbol() const
{
	return _symbol;
}

string Czlowiek::GetNazwa() const
{
	return "Czlowiek";
}

string Czlowiek::saveInfo() const
{
	return (this->GetNazwa() + " " + to_string(_sila) + " " + to_string(_inicjatywa) + " " + to_string(_x) + " " + to_string(_y)
	+ " " + to_string(_wiek) +" " + to_string(_umiejetnoscAktywowana) 
	+ " " + to_string(_turyObecnegoStanuUmiejetnosci) + " " + to_string(cooldown));
}

void Czlowiek::Akcja()
{
	string komentarz;
	komentarz = this->GetNazwa() + ": \tprzemieszczenie z (" + to_string(_x) + ", " + to_string(_y) + ") na (";

	_swiat->SetPolePlanszy(_x, _y, nullptr);
	if ((_ostatni_ruch == GORA) && (_y - 1 != 0))
	{
		_y --;
	}
	else if ((_ostatni_ruch == PRAWO) && (_x + 1 != _swiat->GetX() + 1))
	{
		_x ++;
	}
	else if ((_ostatni_ruch == DOL) && (_y + 1 != _swiat->GetY() + 1))
	{
		_y ++;
	}
	else if ((_ostatni_ruch == LEWO) && (_x - 1 != 0))
	{
		_x --;
	}
	else
	{
		_ostatni_ruch = 0;
		this->Rysowanie();
	}

	komentarz += to_string(_x) + ", " + to_string(_y) + ")";
	_swiat->AddComment(komentarz);
}

void Czlowiek::Kolizja(Organizm* atakujacy)
{
	Zwierze::Kolizja(atakujacy);
}

void Czlowiek::RunAway()
{
	Zwierze::RunAway();
}

void Czlowiek::AktywujUmiejetnosc()
{
	_umiejetnoscAktywowana = true;
	_turyObecnegoStanuUmiejetnosci = 0;
	cout << "Superzdolnosc wlaczona" << endl;
}

void Czlowiek::DezaktywujUmiejetnosc()
{
	_umiejetnoscAktywowana = false;
	_turyObecnegoStanuUmiejetnosci = 0;
	cooldown = 5;
}