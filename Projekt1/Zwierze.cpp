#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>

#include "Swiat.h"
#include "Organizm.h"
#include "Zwierze.h"

#include "Antylopa.h"
#include "Lis.h"
#include "Owca.h"
#include "Zolw.h"
#include "Wilk.h"


#define GORA 1
#define PRAWO 2
#define DOL 3
#define LEWO 4
#define SIZE 20

using namespace std;

Zwierze::Zwierze() : Organizm()
{
	_ostatni_ruch = NULL;
}

Zwierze::Zwierze(int sila, int ini, int x, int y, Swiat* swiat) : Organizm(sila, ini, x, y, swiat)
{
	_ostatni_ruch = NULL;
}

void Zwierze::SetRuch(char ruch)
{
	_ostatni_ruch = ruch;
}

int Zwierze::GetOstatniRuch() const
{
	return _ostatni_ruch;
}

string Zwierze::saveInfo() const
{
	return (this->GetNazwa() + " " + to_string(_sila) + " " + to_string(_inicjatywa) + " "
	+ to_string(_x) + " " + to_string(_y) + " " + to_string(_wiek));
	
}

void Zwierze::Akcja()
{
	string komentarz;
	_swiat->SetPolePlanszy(_x, _y, nullptr);
	vector <pair<int, int>> points;
	pair <int, int> para;
	vector <int> ruch;
	
	if (_x + 1 < _swiat->GetX() + 1)
	{
		para.first = _x + 1;
		para.second = _y;
		points.push_back(para);
		ruch.push_back(PRAWO);
	}
	if (_x - 1 > 0)
	{
		para.first = _x - 1;
		para.second = _y;
		points.push_back(para);
		ruch.push_back(LEWO);
	}
	if (_y - 1 > 0)
	{
		para.first = _x;
		para.second = _y - 1;
		points.push_back(para);
		ruch.push_back(GORA);
	}
	if (_y + 1 < _swiat->GetY() + 1)
	{
		para.first = _x;
		para.second = _y + 1;
		points.push_back(para);
		ruch.push_back(DOL);
	}

	komentarz = this->GetNazwa() + ": \tprzemieszczenie z (" + to_string(_x) 
	+ ", " + to_string(_y) + ") na (";

	if (points.size() != 0)
	{
		int los = rand() % points.size();
		_x = points[los].first;
		_y = points[los].second;
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

void Zwierze::Kolizja(Organizm* atakujacy)
{
	atakujacy->KillLog(this);
	if (this->GetSymbol() == atakujacy->GetSymbol())
	{
		if (atakujacy->GetWiek() > 0)
		{
			this->Rozmnazanie(atakujacy, _swiat);
		}
		else
		{
			atakujacy->DrawBack();
			string komentarz = "Proba rozmnozenia z mlodym organizmem";
			_swiat->AddComment(komentarz);
		}
	}
	else if (this->GetSila() > atakujacy->GetSila())
	{
		_swiat->DeleteOrganism(atakujacy);
	}
	else
	{
		_swiat->SetPolePlanszy(this->GetX(), this->GetY(), atakujacy);
		_swiat->DeleteOrganism(this);
		atakujacy->Rysowanie();
	}
}

void Zwierze::DrawBack()
{
	if (this->GetOstatniRuch() == PRAWO)
	{
	this->SetPolozenie(this->GetX() - 2, this->GetY() - 1);
	}
	else if (this->GetOstatniRuch() == LEWO)
	{
		this->SetPolozenie(this->GetX(), this->GetY() - 1);
	}
	else if (this->GetOstatniRuch() == GORA)
	{
		this->SetPolozenie(this->GetX() - 1, this->GetY());
	}
	else if (this->GetOstatniRuch() == DOL)
	{
		this->SetPolozenie(this->GetX() - 1, this->GetY() - 2);
	}
	this->Rysowanie();
}

void Zwierze::RunAway()
{
	Organizm* atakowany = _swiat->GetPolePlanszy(_x, _y);
	if (atakowany == this)
	{
		_swiat->SetPolePlanszy(_x, _y, nullptr);
	}
	string komentarz;
	vector <pair<int, int>> points;
	pair <int, int> para;
	vector <int> ruch;
	Organizm* org[4];
	org[0] = _swiat->GetPolePlanszy(_x, _y - 1);
	org[1] = _swiat->GetPolePlanszy(_x + 1, _y);
	org[2] = _swiat->GetPolePlanszy(_x, _y + 1);
	org[3] = _swiat->GetPolePlanszy(_x - 1, _y);
		
	if (_x + 1 != _swiat->GetX() + 1 && (org[1] == nullptr || org[1]->GetSila() <= _sila))
	{
		para.first = _x + 1;
		para.second = _y;
		points.push_back(para);
		ruch.push_back(PRAWO);
	}
	if (_x - 1 != 0 && (org[3] == nullptr || org[3]->GetSila() <= _sila))
	{
		para.first = _x - 1;
		para.second = _y;
		points.push_back(para);
		ruch.push_back(LEWO);
	}
	if (_y - 1 != 0 && (org[0] == nullptr || org[0]->GetSila() <= _sila))
	{
		para.first = _x;
		para.second = _y - 1;
		points.push_back(para);
		ruch.push_back(GORA);
	}

	if (_y + 1 != _swiat->GetY() + 1 && (org[2] == nullptr || org[2]->GetSila() <= _sila))
	{
		para.first = _x;
		para.second = _y + 1;
		points.push_back(para);
		ruch.push_back(DOL);
	}

	komentarz = this->GetNazwa() + ": \tprzemieszczenie z ("+ to_string(_x) 
		+ ", " + to_string(_y) + ") na (";

	if (points.size() != 0)
	{
		int los = rand() % points.size();
		_x = points[los].first;
		_y = points[los].second;
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

bool Zwierze::CzyJestZwierzeciem()
{
	return true;
}

void Zwierze::KillLog(Organizm* atakowany)
{
	string komentarz = this->GetNazwa() + ": \tzaatakowal/a " + atakowany->GetNazwa();
	_swiat->AddComment(komentarz);
}

void Zwierze::RuchNaWolnePole()
{
	_swiat->SetPolePlanszy(_x, _y, nullptr);
	vector<pair<int, int>> points;
	vector <int> ruch;
	_swiat->SzukanieWolnychPkt(_x, _y, points, ruch);

	int stary_x = _x;
	int stary_y = _y;
	if (points.size() != 0)
	{
		int los = rand() % points.size();
		_x = points[los].first;
		_y = points[los].second;
		_ostatni_ruch = ruch[los];
	}
	else
	{
		this->Rysowanie();
		_ostatni_ruch = 0;
	}

	string komentarz = this->GetNazwa() + ": \truch z (" + to_string(stary_x)
		+ ", " + to_string(stary_y) + ") do (" + to_string(_x) + ", " + to_string(_y) + ")";
	_swiat->AddComment(komentarz);
}

Organizm* Zwierze::StworzOrganizm(int x, int y, Swiat* swiat)
{
	if (typeid(*this) == typeid(Wilk))
	{
		Wilk* zw = new Wilk(x - 1, y - 1, swiat);
		return zw;
	}
	else if (typeid(*this) == typeid(Owca))
	{
		Owca* zw = new Owca(x - 1, y - 1, swiat);
		return zw;
	}
	else if (typeid(*this) == typeid(Lis))
	{
		Lis* zw = new Lis(x - 1, y - 1, swiat);
		return zw;
	}
	else if (typeid(*this) == typeid(Zolw))
	{
		Zolw* zw = new Zolw(x - 1, y - 1, swiat);
		return zw;
	}
	else if (typeid(*this) == typeid(Antylopa))
	{
		Antylopa* zw = new Antylopa(x - 1, y - 1, swiat);
		return zw;
	}
}

void Zwierze::Rozmnazanie(Organizm* atakujacy, Swiat* swiat)
{
	vector <pair<int, int>> position;
	vector <int> ruch;
	int point = 0;

	int x = 0;
	int y = 0;
	atakujacy->DrawBack();
	if (atakujacy->GetOstatniRuch() == GORA || atakujacy->GetOstatniRuch() == DOL)
	{
		swiat->SzukanieWolnychPkt(atakujacy->GetX(), atakujacy->GetY(), position, ruch);
		swiat->SzukanieWolnychPkt(this->GetX(), this->GetY(), position, ruch);

		if (position.size() != 0)
		{
			point = rand() % position.size();
			Organizm* org = this->StworzOrganizm(position[point].first, position[point].second, swiat);
			swiat->CreateOrganism(org);
		}
	}
	else if (atakujacy->GetOstatniRuch() == LEWO || atakujacy->GetOstatniRuch() == PRAWO)
	{
		swiat->SzukanieWolnychPkt(atakujacy->GetX(), atakujacy->GetY(), position, ruch);
		swiat->SzukanieWolnychPkt(this->GetX(), this->GetY(), position, ruch);

		if (position.size() != 0)
		{
			point = rand() % position.size();
			Organizm* org = this->StworzOrganizm(position[point].first, position[point].second, swiat);
			swiat->CreateOrganism(org);
		}
	}
}