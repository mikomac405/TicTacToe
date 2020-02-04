#include <iostream>
#include "game.h"
#include <fstream>

using namespace std;

int main() {

	///////////////////////////////////////////////////

	string pole[3];
	int wynik[3];

	fstream plik;
	plik.open("wyniki.txt", ios::in);

	for (int i = 0; i < 3; i++)
	{
		plik >> pole[i];
		plik >> wynik[i];
	}

	plik.close();
	
	//////////////////////////////////////////////////

	Gra tictactoe;

	tictactoe.start();

	if (tictactoe.czyWygrana(CZLOWIEK) == true) wynik[0]++;
	if (tictactoe.czyWygrana(AI) == true) wynik[1]++;
	if (tictactoe.czyWygrana(CZLOWIEK) == false && tictactoe.czyWygrana(AI) == false) {
		wynik[2]++;
		cout << "				        REMIS!!!" << endl;
	}

	/////////////////////////////////////////////////
	
	plik.open("wyniki.txt", ios::trunc);
	plik.close();

	plik.open("wyniki.txt", ios::out);

	for(int i=0;i<3;i++)
	{
		plik << pole[i] << "	" << wynik[i] << endl;
	}

	plik.close();

	////////////////////////////////////////////////
	
	cout << "			    ";
	system("pause");
	return 0;
}