#include <fstream>
#include <string>
#include <Windows.h>

#include "Swiat.h"
#include "WorldCreator.h"

#include "Trawa.h"
#include "Mlecz.h"
#include "Guarana.h"
#include "Wilcze_jagody.h"
#include "Barszcz_sosnowskiego.h"

#include "Organizm.h"
#include "Czlowiek.h"
#include "Wilk.h"
#include "Owca.h"
#include "Lis.h"
#include "Zolw.h"
#include "Antylopa.h"



#define LICZBA_GATUNKOW 10
#define PUSTEPOLA 20

using namespace std;

WorldCreator::WorldCreator(Swiat* swiat)
{
	world = swiat;
}

bool WorldCreator::Wczytaj_swiat()
{
	ifstream odczyt("save.txt");
	if (!odczyt.good())
	{
		cout << "Nie znaleziono pliku" << endl;
		Sleep(2000);
		return false;
	}
	int n, m, tura, liczbaOrg;
	odczyt >> n >> m >> tura >> liczbaOrg;
	world->SetWymiaryPlanszy(n, m);
	world->SetTura(tura);

	for (int i = 0; i < liczbaOrg; i++)
	{
		string nazwa;
		odczyt >> nazwa;

		if (nazwa == "Wilcze" || nazwa == "Barszcz")
		{
			string nazwa2;
			odczyt >> nazwa2;
			nazwa += " " + nazwa2;
		}

		int sila, inicjatywa, x, y, wiek, umiejetnoscAktywowana, turyZUmiejetnoscia, cooldown;
		bool aktywowana;

		odczyt >> sila >> inicjatywa >> x >> y >> wiek;

		if (nazwa == "Czlowiek")
		{
			odczyt >> umiejetnoscAktywowana >> turyZUmiejetnoscia>>cooldown;
			Organizm* org = new Czlowiek(x - 1, y - 1, world);
			org->SetSila(sila);
			org->SetInicjatywa(inicjatywa);
			org->SetWiek(wiek);
			

			if (umiejetnoscAktywowana == 0)
				aktywowana = false;
			else
				aktywowana = true;

			world->CreateOrganism(org);
			world->GetCzlowiek()->SetCzyUmiejetnoscAktywowana(aktywowana);
			world->GetCzlowiek()->SetTuryObecnegoStanuUmiejetnosci(turyZUmiejetnoscia);
			world->GetCzlowiek()->SetCooldown(cooldown);
		}
		else
		{
			WczytajOrganizm(nazwa, sila, inicjatywa, x - 1, y - 1, wiek);
		}
	}

	odczyt.close();
	return true;
}

void WorldCreator::Zapisz_swiat()
{
	ofstream zapis("save.txt");

	int liczbaOrg = world->GetLiczbaOrg();
	zapis << world->GetX() << " " << world->GetY() << " " << world->GetNrTury() << " " << liczbaOrg << endl;
	Organizm* org = nullptr;
	for (int i = 0; i < liczbaOrg; i++)
	{
		org = world->GetOrganizm(i);
		zapis << org->saveInfo() << endl;
	}

	zapis.close();
	cout << "Stan gry zapisano" << endl;
}

void WorldCreator::Generuj_swiat()
{
	int x = world->GetX();
	int y = world->GetY();
	int ileZwierzatZGatunku = x * y / (LICZBA_GATUNKOW + PUSTEPOLA);
	int* polaZajete = new int[ileZwierzatZGatunku * LICZBA_GATUNKOW + 1];
	this->GenerowaniePunktowDlaOrganizmow(polaZajete, &ileZwierzatZGatunku);
	int j = 0;
	int positionx = polaZajete[j] % x;
	int positiony = (polaZajete[j] - positionx) / x;
	Organizm* gracz = new Czlowiek(positionx, positiony, world);
	world->CreateOrganism(gracz);
	j++;
	for (int i = 0; i < ileZwierzatZGatunku; i++)
	{
		OdczytajWspolrzedne(polaZajete, &positionx, &positiony, &j);
		Organizm* wilk = new Wilk(positionx, positiony, world);
		world->CreateOrganism(wilk);

		OdczytajWspolrzedne(polaZajete, &positionx, &positiony, &j);
		Organizm* owca = new Owca(positionx, positiony, world);
		world->CreateOrganism(owca);

		OdczytajWspolrzedne(polaZajete, &positionx, &positiony, &j);
		Organizm* lis = new Lis(positionx, positiony, world);
		world->CreateOrganism(lis);

		OdczytajWspolrzedne(polaZajete, &positionx, &positiony, &j);
		Organizm* zolw = new Zolw(positionx, positiony, world);
		world->CreateOrganism(zolw);

		OdczytajWspolrzedne(polaZajete, &positionx, &positiony, &j);
		Organizm* antylopa = new Antylopa(positionx, positiony, world);
		world->CreateOrganism(antylopa);

		OdczytajWspolrzedne(polaZajete, &positionx, &positiony, &j);
		Organizm* trawa = new Trawa(positionx, positiony, world);
		world->CreateOrganism(trawa);

		OdczytajWspolrzedne(polaZajete, &positionx, &positiony, &j);
		Organizm* mlecz = new Mlecz(positionx, positiony, world);
		world->CreateOrganism(mlecz);

		OdczytajWspolrzedne(polaZajete, &positionx, &positiony, &j);
		Organizm* guarana = new Guarana(positionx, positiony, world);
		world->CreateOrganism(guarana);

		OdczytajWspolrzedne(polaZajete, &positionx, &positiony, &j);
		Organizm* jagoda = new Wilcze_jagody(positionx, positiony, world);
		world->CreateOrganism(jagoda);

		OdczytajWspolrzedne(polaZajete, &positionx, &positiony, &j);
		Organizm* barszcz = new Barszcz_sosnowskiego(positionx, positiony, world);
		world->CreateOrganism(barszcz);
	}
	delete[] polaZajete;
}

void WorldCreator::GenerowaniePunktowDlaOrganizmow(int* pola, int* ileZwZGat)
{
	int x = world->GetX();
	int y = world->GetY();
	int ilePol = (*ileZwZGat) * LICZBA_GATUNKOW + 1;		//+1 bo czlowiek
	int* wszystkiePola = new int[x * y];
	int los;
	for (int i = 0; i < x * y; i++)
	{
		wszystkiePola[i] = 0;
	}
	for (int i = 0; i < ilePol; i++)
	{
		do
		{
			los = rand() % (x * y);
		} while (wszystkiePola[los] == 1);
		wszystkiePola[los] = 1;
		pola[i] = los;
	}
	delete[] wszystkiePola;
}

void WorldCreator::OdczytajWspolrzedne(int* pola, int* x, int* y, int* ktory)
{
	int n = world->GetX();
	*x = pola[*ktory] % n;
	*y = (pola[*ktory] - *x) / n;
	(*ktory)++;
}

void WorldCreator::WczytajOrganizm(string nazwa, int sila, int ini, int x, int y, int wiek)
{
	Organizm* org = nullptr;
	
	if (nazwa == "Trawa")
	{
		org = new Trawa(x, y, world);
	}
	else if (nazwa == "Mlecz")
	{
		org = new Mlecz(x, y, world);
	}
	else if (nazwa == "Guarana")
	{
		org = new Guarana(x, y, world);
	}
	else if (nazwa == "Barszcz sosnowskiego")
	{
		org = new Barszcz_sosnowskiego(x, y, world);
	}
	else if (nazwa == "Wilcze jagody")
	{
		org = new Wilcze_jagody(x, y, world);
	}
	else if (nazwa == "Wilk")
	{
		org = new Wilk(x, y, world);
	}
	else if (nazwa == "Owca")
	{
		org = new Owca(x, y, world);
	}
	else if (nazwa == "Lis")
	{
		org = new Lis(x, y, world);
	}
	else if (nazwa == "Zolw")
	{
		org = new Zolw(x, y, world);
	}
	else if (nazwa == "Antylopa")
	{
		org = new Antylopa(x, y, world);
	}

	if (org != nullptr)
	{
		org->SetSila(sila);
		org->SetInicjatywa(ini);
		org->SetWiek(wiek);
		world->CreateOrganism(org);
	}
	else
	{
		cout << "Blad wczytywania organizmu." << nazwa << endl;
	}
}

WorldCreator::~WorldCreator()
{
	delete world;
}