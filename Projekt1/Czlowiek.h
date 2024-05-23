#ifndef Czlowiek_Defined
#define Czlowiek_Defined

#include <iostream>
#include <string.h>

#include "Zwierze.h"

using namespace std;

class Swiat;
class Organizm;
class Zwierze;

class Czlowiek : public Zwierze
{
private:
	const char _symbol = 'X';
	bool _umiejetnoscAktywowana;
	int _turyObecnegoStanuUmiejetnosci;
	int cooldown;
public:
	Czlowiek(int x, int y, Swiat* swiat);

	void SetRuch(char ruch) override;
	void SetCzyUmiejetnoscAktywowana(bool umiejetnoscAktywowana);
	void SetTuryObecnegoStanuUmiejetnosci(int tury);
	void SetCooldown(int cooldown);

	int GetOstatniRuch() const override;
	bool CzyUmiejetnoscAktywowana() const;
	int GetTuryObecnegoStanuUmiejetnosci() const;
	char GetSymbol() const override;
	int GetCooldown() const;
	string GetNazwa() const override;
	string saveInfo() const override;

	void Akcja() override;
	void Kolizja(Organizm* atakujacy) override;
	void RunAway() override;
	void AktywujUmiejetnosc();
	void DezaktywujUmiejetnosc();
};
#endif