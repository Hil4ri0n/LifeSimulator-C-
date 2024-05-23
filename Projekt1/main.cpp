#include <iostream>
#include <conio.h>
#include <string>
#include <time.h>

#include "WorldCreator.h"
#include "Swiat.h"

#define WPROWADZENIE_ZNAKU 224
#define SPACE 32
#define SAVE 115
#define READ 114
#define NEW 110
#define LICZBA_GATUNKOW 10
#define PUSTEPOLA 18

using namespace std;

int main() {
	int n = 0, m = 0;
	char wybor1 = 0, wybor2 = 0;
	Swiat* swiat = nullptr;
	WorldCreator* creator = nullptr;

	srand(time(NULL));

	while (true) {
		cout << "Menu:" << endl;
		cout << "N - Nowa gra" << endl;
		cout << "R - Wczytaj gre" << endl;
		wybor1 = _getch();

		if (wybor1 == READ) {
			swiat = new Swiat();
			creator = new WorldCreator(swiat);

			if (creator->Wczytaj_swiat() == false) {
				cout << "Wybierz jeszcze raz" << endl;
				continue;
			}
		}
		else if (wybor1 == NEW) {
			do {
				cout << "Podaj wymiary planszy: ";
				cin >> n >> m;
				system("cls");
			} while (n * m < (LICZBA_GATUNKOW + PUSTEPOLA));

			swiat = new Swiat(n, m);
			creator = new WorldCreator(swiat);
			creator->Generuj_swiat();
		}
		else {
			cout << "Zly przycisk" << endl;
			continue;
		}

		system("cls");
		swiat->RysujPlansze();

		while (true) {
			wybor2 = _getch();

			if (wybor2 == SAVE) {
				creator->Zapisz_swiat();
			}
			else if (wybor2 == SPACE) {
				swiat->WykonajTure();
				system("cls");
				swiat->RysujPlansze();
			}
			else if (wybor2 == NEW) {
				system("cls");
				cout << "Nowa gra" << endl << endl;

				do {
					cout << "Podaj wymiary planszy: ";
					cin >> n >> m;
					system("cls");
				} while (n * m < (LICZBA_GATUNKOW + PUSTEPOLA));

				swiat = new Swiat(n, m);
				creator = new WorldCreator(swiat);
				creator->Generuj_swiat();
				system("cls");
				swiat->RysujPlansze();
			}
			else {
				cout << "Zly przycisk" << endl;
			}
		}

		delete creator;
		delete swiat;

		return 0;
	}
}