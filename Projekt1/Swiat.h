#ifndef Swiat_Defined
#define Swiat_Defined

#include <iostream>
#include <string.h>
#include <vector>

using namespace std;

class Organizm;
class Czlowiek;

class Swiat
{
private:
	vector<Organizm*> _organizmy;
	Czlowiek* _czlowiek;
	int _liczbaOrg;
	int _liczbaStarychOrganizmow;
	vector <vector<Organizm*>> _plansza;
	int _x;
	int _y;
	int _tura;
	bool _isHumanAlive;
	vector<string> _comments;
	int _nrOfComments;
	void Ruchy();
public:
	Swiat();
	Swiat(int n, int m);

	void SetWymiaryPlanszy(int n, int m);
	void SetPolePlanszy(int x, int y, Organizm* org);
	void SetTura(int tura);
	void AddComment(string komentarz);	

	int GetX() const;
	int GetY() const;
	int GetLiczbaOrg() const;
	int GetNrTury() const;
	Organizm* GetPolePlanszy(int x, int y) const;
	Organizm* GetOrganizm(int i) const;
	Czlowiek* GetCzlowiek() const;

	void CreateOrganism(Organizm* org);
	void DeleteOrganism(Organizm* org);
	void SzukanieWolnychPkt(int x, int y, vector<pair<int, int>> &points, vector <int> &ruch);

	void WykonajTure();
	void RysujPlansze();

	~Swiat();
};
#endif;