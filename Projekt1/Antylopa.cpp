#include <iostream>
#include <string>

#include "Swiat.h"
#include "Organizm.h"
#include "Zwierze.h"
#include "Antylopa.h"

#define GORA 1
#define PRAWO 2
#define DOL 3
#define LEWO 4
#define SIZE 20

Antylopa::Antylopa() : Zwierze()
{
	_sila = 4;
	_inicjatywa = 4;
}

Antylopa::Antylopa(int x, int y, Swiat* swiat) : Zwierze(4, 4, x, y, swiat)
{

}

void Antylopa::SetRuch(char ruch)
{
	Zwierze::SetRuch(ruch);
}

int Antylopa::GetOstatniRuch() const
{
	return Zwierze::GetOstatniRuch();
}

string Antylopa::GetNazwa() const
{
	return "Antylopa";
}

char Antylopa::GetSymbol() const
{
	return _symbol;
}



void Antylopa::Kolizja(Organizm* atakujacy)
{
	int los = rand() % 100 + 1;
	if (los % 2 == 0 && atakujacy->GetSymbol() != _symbol)
	{
		this->RuchNaWolnePole();
		if (_ostatni_ruch != 0)
		{
			return;
		}
	}

	Zwierze::Kolizja(atakujacy);
}


void Antylopa::Akcja()
{
	_swiat->SetPolePlanszy(_x, _y, nullptr);
	string komentarz;
	int* pointsX = new int[4];
	int* pointsY = new int[4];
	int* ruch = new int[4];
	int pointsCount = 0;
	if (_y - 2 > 0)
	{
		pointsX[pointsCount] = _x;
		pointsY[pointsCount] = _y - 2;
		ruch[pointsCount] = GORA;
		pointsCount++;
	}
	if (_x + 2 < _swiat->GetX() + 1)
	{
		pointsX[pointsCount] = _x + 2;
		pointsY[pointsCount] = _y;
		ruch[pointsCount] = PRAWO;
		pointsCount++;
	}
	if (_y + 2 < _swiat->GetY() + 1)
	{
		pointsX[pointsCount] = _x;
		pointsY[pointsCount] = _y + 2;
		ruch[pointsCount] = DOL;
		pointsCount++;
	}
	if (_x - 2 > 0)
	{
		pointsX[pointsCount] = _x - 2;
		pointsY[pointsCount] = _y;
		ruch[pointsCount] = LEWO;
		pointsCount++;
	}

	komentarz = this->GetNazwa() + ": \tprzemieszczenie z (" + to_string(_x) + ", " + to_string(_y) + ") na (";

	if (pointsCount != 0)
	{
		int los = rand() % pointsCount;
		_x = pointsX[los];
		_y = pointsY[los];
		_ostatni_ruch = ruch[los];
	}
	else
	{
		this->Rysowanie();
		_ostatni_ruch = 0;
	}

	komentarz += to_string(_x) + ", " + to_string(_y) + ")";
	_swiat->AddComment(komentarz);
}

