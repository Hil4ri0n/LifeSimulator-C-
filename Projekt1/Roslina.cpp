#include <iostream>
#include <string>

#include "Roslina.h"
#include "Swiat.h"
#include "Organizm.h"

#include "Wilcze_jagody.h"
#include "Trawa.h"
#include "Mlecz.h"
#include "Barszcz_sosnowskiego.h"
#include "Guarana.h"
using namespace std;

Roslina::Roslina() : Organizm()
{
	
}

Roslina::Roslina(int sila, int x, int y, Swiat* swiat) : Organizm(sila, 0, x, y, swiat)
{

}

int Roslina::GetOstatniRuch() const
{
	return 0;
}

string Roslina::saveInfo() const
{
	return (this->GetNazwa() + " " + to_string(this->GetSila()) + " " + to_string(this->GetInicjatywa())
	+ " " + to_string(this->GetX()) + " " + to_string(this->GetY()) + " " + to_string(this->GetWiek()));
	
}

void Roslina::Akcja()
{
	vector<pair<int, int>> points;
	vector <int> ruch;
	_swiat->SzukanieWolnychPkt(_x, _y, points, ruch);
	if (points.size() != 0) {
		int los = rand() % points.size();
		Organizm* org = this->StworzOrganizm(points[los].first, points[los].second, _swiat);
		_swiat->CreateOrganism(org);

		string komentarz = (this->GetNazwa() + ": \trozprzestrzenienie rosliny z (" + to_string(_x) +
		", " + to_string(_y) + ") na pole (" + to_string(points[los].first) + ", " 
			+ to_string(points[los].second) + ")");
		_swiat->AddComment(komentarz);
	}
}

void Roslina::Kolizja(Organizm* atakujacy)
{
	atakujacy->KillLog(this);

	if (this->GetSila() > atakujacy->GetSila())
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

bool Roslina::CzyJestZwierzeciem()
{
	return false;
}


void Roslina::KillLog(Organizm* atakowany)
{
	string komentarz;
	komentarz = this->GetNazwa() + ": \tzaatakowal organizm " + atakowany->GetNazwa();
	_swiat->AddComment(komentarz);
}

Organizm* Roslina::StworzOrganizm(int x, int y, Swiat* swiat)
{
	if (typeid(*this) == typeid(Trawa))
	{
		Trawa* r = new Trawa(x - 1, y - 1, swiat);
		return r;
	}
	else if (typeid(*this) == typeid(Mlecz))
	{
		Mlecz* r = new Mlecz(x - 1, y - 1, swiat);
		return r;
	}
	else if (typeid(*this) == typeid(Guarana))
	{
		Guarana* r = new Guarana(x - 1, y - 1, swiat);
		return r;
	}
	else if (typeid(*this) == typeid(Wilcze_jagody))
	{
		Wilcze_jagody* r = new Wilcze_jagody(x - 1, y - 1, swiat);
		return r;
	}
	else if (typeid(*this) == typeid(Barszcz_sosnowskiego))
	{
		Barszcz_sosnowskiego* r = new Barszcz_sosnowskiego(x - 1, y - 1, swiat);
		return r;
	}
}

void Roslina::SetRuch(char ruch)
{
	cout << "Blad: proba wywolania metody Roslina::SetRuch()" << endl;
}

void Roslina::DrawBack()
{
	cout << "Blad: proba wywolania metody Roslina::Cofniecie()" << endl;
}

void Roslina::RunAway()
{
	cout << "Blad: proba wywoalania Roslina::Uciekaj()" << endl;
}