#include <conio.h>
#include <string>
#include <Windows.h>

#include "Swiat.h"
#include "Organizm.h"
#include "Czlowiek.h"

#include "Wilcze_jagody.h"
#include "Barszcz_sosnowskiego.h"
#include "Trawa.h"
#include "Mlecz.h"
#include "Guarana.h"


#include "Wilk.h"
#include "Owca.h"
#include "Lis.h"
#include "Zolw.h"
#include "Antylopa.h"



#define WPROWADZENIE_ZNAKU 224
#define GORA 1
#define PRAWO 2
#define DOL 3
#define LEWO 4
#define UP_KEY 72
#define RIGHT_KEY 77
#define DOWN_KEY 80
#define LEFT_KEY 75
#define KOMENTARZE_NA_ORG 5
#define CornerX 0
#define CornerY 10

using namespace std;

Swiat::Swiat() : Swiat(20, 20)
{

}

Swiat::Swiat(int n, int m)
{
	_x = n;
	_y = m;
	_liczbaStarychOrganizmow = 0;
	_liczbaOrg = 0;
	_tura = 0;
	_isHumanAlive = false;
	_czlowiek = nullptr;
	_nrOfComments = 0;
	_organizmy = vector<Organizm*>(_x * _y);
	_plansza = vector<vector<Organizm*>>(_y + 2);

	for (int y = 0; y < (m + 2); y++)
	{
		_plansza[y] = vector<Organizm*>(_x + 2);
		fill(_plansza[y].begin(), _plansza[y].end(), nullptr);
	}
}

void Swiat::SetWymiaryPlanszy(int n, int m)
{
	_x = n;
	_y = m;
}

void Swiat::SetPolePlanszy(int x, int y, Organizm* org)
{
	_plansza[y][x] = org;
}

void Swiat::SetTura(int tura)
{
	_tura = tura;
}

void Swiat::AddComment(string komentarz)
{
	_comments.push_back(komentarz);
	_nrOfComments++;
}

int Swiat::GetX() const
{
	return _x;
}

int Swiat::GetY() const
{
	return _y;
}

int Swiat::GetLiczbaOrg() const
{
	return _liczbaOrg;
}

int Swiat::GetNrTury() const
{
	return _tura;
}

Organizm* Swiat::GetPolePlanszy(int x, int y) const
{
	if ((x > 0) && (x < (_x + 2)) && (y > 0) && (y < (_y + 2)))
	{
		return _plansza[y][x];
	}
	return nullptr;
}

Organizm* Swiat::GetOrganizm(int i) const
{
	return _organizmy[i];
}

Czlowiek* Swiat::GetCzlowiek() const
{
	return _czlowiek;
}

void Swiat::CreateOrganism(Organizm* org)
{
	string komentarz;
	if (_liczbaOrg >= _x * _y) {
		komentarz = "Nie mozna dodac kolejnego organizmu";
		this->AddComment(komentarz);
		delete org;
		return;
	}

	if (_plansza[org->GetY()][org->GetX()] != nullptr) {
		delete org;
		return;
	}

	_organizmy[_liczbaOrg] = org;
	_liczbaOrg++;

	if (_liczbaOrg > 1 && org->CzyJestZwierzeciem()) {
		int i = _liczbaOrg - 2;
		while (i >= 0 && _organizmy[i]->GetInicjatywa() < org->GetInicjatywa()) {
			_organizmy[i + 1] = _organizmy[i];
			i--;
		}
		_organizmy[i + 1] = org;
	}

	org->Rysowanie();
	if (typeid(*org) == typeid(Czlowiek)) {
		_isHumanAlive = true;
		_czlowiek = dynamic_cast<Czlowiek*>(org);
	}

	komentarz = org->GetNazwa() + ": \tutworzenie nowego organizmu na polu (" + to_string(org->GetX()) + ", ";
	komentarz += to_string(org->GetY()) + ")";
	this->AddComment(komentarz);
}


void Swiat::DeleteOrganism(Organizm* org)
{
	string komentarz;
	Organizm* atakowany;
	bool uciekl = true;
	if (org == _czlowiek && _czlowiek->CzyUmiejetnoscAktywowana())
	{
		_czlowiek->RunAway();
		if (_czlowiek->GetOstatniRuch() == 0)
		{
			uciekl = false;
		}
		else
		{
			komentarz = "Czlowiek uciekl";
			this->AddComment(komentarz);
			atakowany = _plansza[org->GetY()][org->GetX()];
			if (atakowany == nullptr)
			{
				_czlowiek->Rysowanie();
			}
			else
			{
				atakowany->Kolizja(_czlowiek);
			}
		}
	}
	if (org != _czlowiek || !_czlowiek->CzyUmiejetnoscAktywowana() || !uciekl)
	{
		atakowany = _plansza[org->GetY()][org->GetX()];
		if (atakowany == org)
		{
			_plansza[org->GetY()][org->GetX()] = nullptr;
		}
		if (typeid(*org) == typeid(Czlowiek))
		{
			_isHumanAlive = false;
		}
		for (int i = 0; i < _liczbaOrg; i++)
		{
			if (_organizmy[i] == org)
			{
				Organizm* temp;
				_organizmy[i] = nullptr;
				for (int j = i; j < _liczbaOrg - 1; j++)
				{
					temp = _organizmy[j];
					_organizmy[j] = _organizmy[j + 1];
					_organizmy[j + 1] = temp;
				}
				i = _liczbaOrg;
			}
		}
		_liczbaOrg--;
		_liczbaStarychOrganizmow--;

		komentarz = org->GetNazwa() + ": \tsmierc organizmu";
		this->AddComment(komentarz);
		delete org;
	}
}

void Swiat::SzukanieWolnychPkt(int x, int y, vector<pair<int, int>>& points, vector <int>& ruch)
{
	if (y - 1 != 0 && _plansza[y - 1][x] == nullptr)
	{
		pair <int, int> paraXY;
		paraXY.first = x;
		paraXY.second = y - 1;
		points.push_back(paraXY);
		ruch.push_back(GORA);
	}
	if (x + 1 != _x + 1 && _plansza[y][x + 1] == nullptr)
	{
		pair <int, int> paraXY;
		paraXY.first = x + 1;
		paraXY.second = y;
		points.push_back(paraXY);
		ruch.push_back(PRAWO);
	}
	if (y + 1 != _y + 1 && _plansza[y + 1][x] == nullptr)
	{
		pair <int, int> paraXY;
		paraXY.first = x;
		paraXY.second = y + 1;
		points.push_back(paraXY);
		ruch.push_back(DOL);
	}
	if (x - 1 != 0 && _plansza[y][x - 1] == nullptr)
	{
		pair <int, int> paraXY;
		paraXY.first = x - 1;
		paraXY.second = y;
		points.push_back(paraXY);
		ruch.push_back(LEWO);
	}
}

void Swiat::WykonajTure()
{
	_liczbaStarychOrganizmow = _liczbaOrg;
	if (_isHumanAlive)
	{
		cout << endl;
		if (_czlowiek->GetCooldown() == 0) {
			if (!_czlowiek->CzyUmiejetnoscAktywowana() && _czlowiek->GetTuryObecnegoStanuUmiejetnosci() >= 5)
			{
				cout << "Jesli chcesz aktywowac umiejetnosc (niesmiertelnosc wcisnij X)" << endl;
			}
		}
		else if (_czlowiek->GetCooldown() == 5) {
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 5);
			cout << "Superzdolnosc wylaczona" << endl;
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
		}
		cout << "Wykonaj ruch" << endl;

		unsigned char znak = _getch();
		if (znak == 'x')
		{
			if (!_czlowiek->CzyUmiejetnoscAktywowana())
			{
				if (_czlowiek->GetCooldown() == 0) {
					_czlowiek->AktywujUmiejetnosc();
				}
				else {
					cout << "Superzdolnosc dostepna za " << _czlowiek->GetCooldown() << " tur.";
				}
			}
			else
			{
				cout << "Nie mozesz aktywowac umiejetnosci ponownie" << endl;
			}
			znak = _getch();
			if (znak != WPROWADZENIE_ZNAKU)
			{
				cout << "Zly klawisz" << endl;
				return;
			}
		}

		if (znak == WPROWADZENIE_ZNAKU)
		{
			znak = _getch();
			_czlowiek->SetRuch(znak);
			Ruchy();
		}
		else
		{
			cout << "Zly klawisz" << endl;
		}
	}
	else
	{
		Ruchy();
	}
}

void Swiat::Ruchy()
{
	Organizm* org;
	Organizm* atakowany;
	Organizm* atakujacy;
	for (int i = 0; i < _liczbaStarychOrganizmow; i++)
	{

		org = _organizmy[i];
		org->Akcja();
		atakowany = _plansza[org->GetY()][org->GetX()];
		if (atakowany == nullptr || org->GetOstatniRuch() == 0)
		{
			org->Rysowanie();
		}
		else
		{
			atakowany->Kolizja(org);
		}
	}
	for (int i = 0; i < _liczbaStarychOrganizmow; i++)
	{
		org = _organizmy[i];
		org->SetWiek(org->GetWiek() + 1);
	}
	if (_isHumanAlive)
	{
		if (_czlowiek->CzyUmiejetnoscAktywowana()) {
			_czlowiek->SetTuryObecnegoStanuUmiejetnosci(_czlowiek->GetTuryObecnegoStanuUmiejetnosci() + 1);
		}
		if (_czlowiek->GetCooldown() != 0) {
			_czlowiek->SetCooldown(_czlowiek->GetCooldown() - 1);
		}
		if (_czlowiek->CzyUmiejetnoscAktywowana() && _czlowiek->GetTuryObecnegoStanuUmiejetnosci() == 5)
		{
			_czlowiek->DezaktywujUmiejetnosc();
		}
	}
	_tura++;
}

void Swiat::RysujPlansze()
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	cout << "Wydarzenia: " << endl;

	for (int i = 0; i < _nrOfComments; i++)
	{
		cout << _comments[i] << endl;
	}
	_comments.clear();
	_nrOfComments = 0;

	cout << endl;

	for (int i = 0; i < _liczbaOrg; i++)
	{
		_organizmy[i]->Rysowanie();
	}

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);

	cout << "a - antylopa" << endl;
	cout << "b - barszcz sosnowskiego" << endl;
	cout << "g - guarana" << endl;
	cout << "j - wilcze jagody" << endl;
	cout << "l - lis" << endl;
	cout << "m - mlecz" << endl;
	cout << "o - owca" << endl;
	cout << "t - trawa" << endl;
	cout << "w - wilk" << endl;
	cout << "z - zolw" << endl;
	cout << "X - gracz" << endl;
	cout << endl;

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);

	cout << "Tura: " << _tura << endl;
	cout << endl << "N) rozpocznij nowa gre" << endl;
	cout << "S) zapisz (przed rozpoczeciem tury)" << endl;
	cout << "Aby rozpoczac ture wcisnij spacje" << endl << endl;

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);

	for (int y = 0; y < (_y + 2); y++)
	{
		for (int x = 0; x < (_x + 2); x++)
		{
			if (GetPolePlanszy(x, y) == nullptr)
			{
				if ((x == 0) || (x == _x + 1))
					cout << "#";
				else if ((y == 0) || (y == _y + 1))
					cout << "##";
				else
					cout << " |";
			}
			else
			{
				char symbol = GetPolePlanszy(x, y)->GetSymbol();
				if (symbol == 'X') {
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
					cout << symbol;
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
					cout << "|";
				}
				else {
					cout << symbol << "|";
				}

			}
		}
		cout << endl;
		if ((y != 0) && (y != _y + 1) && (y != _y)) {
			for (int i = 0; i < _x + 2; i++) {
				if ((i == 0) || (i == _x + 1))
					cout << "#";
				else
					cout << "##";
			}
			cout << endl;
		}
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
}

Swiat::~Swiat()
{
	delete _czlowiek;
	for (int y = 0; y < _y; y++)
	{
		for (int x = 0; x < _x; x++)
		{
			delete _plansza[y][x];
		}
	}
}