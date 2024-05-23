#ifndef Organizm_Defined
#define Organizm_Defined

#include <iostream>
#include <string.h>

using namespace std;

class Swiat;

class Organizm
{
protected:	
	int _sila;
	int _inicjatywa;
	int _x;
	int _y;
	int _wiek;
	Swiat* _swiat;
	virtual Organizm* StworzOrganizm(int x, int y, Swiat* swiat) = 0;
public:
	Organizm();
	Organizm(int sila, int ini, int x, int y, Swiat* swiat);

	void SetSila(int sila);
	void SetInicjatywa(int ini);
	void SetPolozenie(int x, int y);
	void SetWiek(int wiek);
	void SetSwiat(Swiat* swiat);
	virtual void SetRuch(char ruch) = 0;

	int GetSila() const;
	int GetInicjatywa() const;
	int GetX() const;
	int GetY() const;
	int GetWiek() const;
	Swiat* GetSwiat() const;
	virtual int GetOstatniRuch() const = 0;
	virtual char GetSymbol() const = 0;
	virtual string GetNazwa() const = 0;
	virtual string saveInfo() const = 0;

	virtual void Akcja() = 0;
	virtual void Kolizja(Organizm* atakujacy) = 0;
	void Rysowanie();
	virtual void DrawBack() = 0;
	virtual void RunAway() = 0;
	virtual bool CzyJestZwierzeciem() = 0;
	virtual void KillLog(Organizm* atakowany) = 0;
};

#endif