#include <iostream>

#include "Swiat.h"
#include "Organizm.h"

using namespace std;

Organizm::Organizm()
{
	_sila = 0;
	_inicjatywa = 0;
	_x = 0;
	_y = 0;
	_swiat = nullptr;
	_wiek = 0;
}

Organizm::Organizm(int sila, int ini, int x, int y, Swiat* swiat)
{
	_sila = sila;
	_inicjatywa = ini;
	_x = x + 1;
	_y = y + 1;
	_swiat = swiat;
	_wiek = 0;
}

void Organizm::SetSila(int sila)
{
	_sila = sila;
}

void Organizm::SetInicjatywa(int ini)
{
	_inicjatywa = ini;
}

void Organizm::SetPolozenie(int x, int y)
{
	_x = x + 1;
	_y = y + 1;
}

void Organizm::SetWiek(int wiek)
{
	_wiek = wiek;
}

void Organizm::SetSwiat(Swiat* swiat)
{
	_swiat = swiat;
}

int Organizm::GetSila() const
{
	return _sila;
}

int Organizm::GetInicjatywa() const
{
	return _inicjatywa;
}

int Organizm::GetX() const
{
	return _x;
}

int Organizm::GetY() const
{
	return _y;
}

int Organizm::GetWiek() const
{
	return _wiek;
}

Swiat* Organizm::GetSwiat() const
{
	return _swiat;
}

void Organizm::Rysowanie()
{
	_swiat->SetPolePlanszy(_x, _y, this);
}