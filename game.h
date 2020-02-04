#include <iostream>
#include <conio.h>

using namespace std;

const char czlowiek = 'X';
const char ai = 'O';

void ERROR();

enum Gracz { CZLOWIEK, AI };

struct Ruch {
	int x;
	int y;
};

class Gra {
	char plansza[3][3];

public:
	Gra();

	void rysujPlansze();

	bool Koniec();

	bool czyWygrana(Gracz player);

	void start();

	void pobierzRuch();

	int wynik();

	Ruch minimax(char planszaAI[3][3]);

	int min(char planszaAI[3][3]);

	int max(char planszaAI[3][3]);
};