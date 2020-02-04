#include <iostream>
#include <sstream>
#include <iomanip>
#include "game.h"

using namespace std;

Gra::Gra() {
	for(int i = 0; i < 3; i++) {
		for(int j = 0; j < 3; j++) {
			plansza[i][j] = '-';
		}
	}
}

void Gra::rysujPlansze() {
	system("cls");
	cout << "\x1b[31m";
	cout << R"(
 ______   __     ______     ______   ______     ______     ______   ______     ______    
/\__  _\ /\ \   /\  ___\   /\__  _\ /\  __ \   /\  ___\   /\__  _\ /\  __ \   /\  ___\   
\/_/\ \/ \ \ \  \ \ \____  \/_/\ \/ \ \  __ \  \ \ \____  \/_/\ \/ \ \ \/\ \  \ \  __\   
   \ \_\  \ \_\  \ \_____\    \ \_\  \ \_\ \_\  \ \_____\    \ \_\  \ \_____\  \ \_____\ 
    \/_/   \/_/   \/_____/     \/_/   \/_/\/_/   \/_____/     \/_/   \/_____/   \/_____/ 
                                                                                         
)" << endl;


	cout << "\x1b[36m				-------------------";
	for(int i = 0; i < 3; i++) {
		cout << '\n' << "				|";
		for(int j = 0; j < 3; j++) {
			cout << setw(3) << plansza[i][j] << setw(3) << " |";
		}
	}
	cout << '\n' << "				-------------------" << "\n\n";
	cout << "\x1b[0m";
}



bool Gra::Koniec() {
	if (czyWygrana(CZLOWIEK)) {
		return true;
	}
	else if (czyWygrana(AI)) {
		return true;
	}

	bool puste = false;
	for(int i = 0; i < 3; i++) {
		if(plansza[i][0] == '-' || plansza[i][1] == '-' || plansza[i][2] == '-')
			puste = true;
	}
	return !puste;
}

bool Gra::czyWygrana(Gracz player) {
	char Gracz;
	if(player == CZLOWIEK) Gracz = czlowiek;
	else Gracz = ai;

	for(int i = 0; i < 3; i++) {
		if(plansza[i][0] == Gracz && plansza[i][1] == Gracz
			&& plansza[i][2] == Gracz)
			return true;

		if(plansza[0][i] == Gracz && plansza[1][i] == Gracz
			&& plansza[2][i] == Gracz)
			return true;
	}
	if (plansza[0][0] == Gracz && plansza[1][1] == Gracz 
		&& plansza[2][2] == Gracz) {
		return true;
	} else if (plansza[0][2] == Gracz && plansza[1][1] == Gracz 
		&& plansza[2][0] == Gracz) {
		return true;
	}

	return false;
}

int Gra::wynik() {
	if(czyWygrana(CZLOWIEK)) { return 10; }
	else if(czyWygrana(AI)) { return -10; }
	return 0; //REMIS
}

Ruch Gra::minimax(char planszaAI[3][3]) { 
	int punktyNajlepszyRuch = 100;
	Ruch najlepszyRuch;

	for(int i = 0; i < 3; i++) {
		for(int j = 0; j < 3; j++) {
			if(planszaAI[i][j] == '-') {
				planszaAI[i][j] = ai;
				int tempPunkty = max(planszaAI);
				if(tempPunkty <= punktyNajlepszyRuch) {
					punktyNajlepszyRuch = tempPunkty;
					najlepszyRuch.x = i;
					najlepszyRuch.y = j;
				}
				planszaAI[i][j] = '-';
			}
		}
	}

	return najlepszyRuch;
}

int Gra::max(char planszaAI[3][3]) {
	if(Koniec()) return wynik();
	Ruch najlepszyRuch;

	int punktyNajlepszyRuch = -1000;
	for(int i = 0; i < 3; i++) {
		for(int j = 0; j < 3; j++) {
			if(planszaAI[i][j] == '-') {
				planszaAI[i][j] = czlowiek;
				int tempPunkty = min(planszaAI);
				if(tempPunkty >= punktyNajlepszyRuch) {
					punktyNajlepszyRuch = tempPunkty;
					najlepszyRuch.x = i;
					najlepszyRuch.y = j;
				}
				planszaAI[i][j] = '-';
			}
		}
	}

	return punktyNajlepszyRuch;
}

int Gra::min(char planszaAI[3][3]) {
	if(Koniec()) return wynik();
	Ruch najlepszyRuch;

	int punktyNajlepszyRuch = 1000; 
	for(int i = 0; i < 3; i++) {
		for(int j = 0; j < 3; j++) {
			if(planszaAI[i][j] == '-') {
				planszaAI[i][j] = ai;
				int tempPunkty = max(planszaAI);
				if(tempPunkty <= punktyNajlepszyRuch) {
					punktyNajlepszyRuch = tempPunkty;
					najlepszyRuch.x = i;
					najlepszyRuch.y = j;
				}
				planszaAI[i][j] = '-';
			}
		}
	}

	return punktyNajlepszyRuch;
}

void Gra::pobierzRuch() {
	int x = -1;
	int y = -1;
	while(x < 0 || x > 2 || y < 0 || y > 2) {
		cout << "			     Gdzie chcesz sie postawic?" << endl;
		cout << "					X: ";
		cin >> x;
		x--;
		if (x < 0 || x > 2)
		{
			cout << "			     Ta kolumna nie istnieje!";
			_getch();
			system("cls");
			rysujPlansze();
			pobierzRuch();
		}
		cout << "					Y: ";
		cin >> y;
		y--;
		if (y < 0 || y > 2)
		{
			cout << "			     Ten wiersz nie istnieje!";
			_getch();
			system("cls");
			rysujPlansze();
			pobierzRuch();
		}
	}
	if (plansza[y][x] == ai || plansza[y][x] == czlowiek)
	{
		cout << "			     To pole jest juz zajete!";
		_getch();
		system("cls");
		rysujPlansze();
		pobierzRuch();
	}
	plansza[y][x] = czlowiek;
}

void Gra::start() {
	int tura = 0;
	rysujPlansze();
	while(!czyWygrana(CZLOWIEK) && !czyWygrana(AI) && !Koniec()) {
		if(tura % 2 == 0) {
			pobierzRuch();
			if (czyWygrana(CZLOWIEK))
			{
				rysujPlansze();
				cout << "			        Uzytkownik wygrywa!!!" << endl;
			}
			else {
				tura++;
				rysujPlansze();
			}
		} else {
			Ruch ruchAI = minimax(plansza);
			plansza[ruchAI.x][ruchAI.y] = ai;
			if (czyWygrana(AI))
			{
				rysujPlansze();
				cout << "			        Komputer wygrywa!!!" << endl;
			}
			else {
				tura++;
				rysujPlansze();
			}
		}
	}
}

void ERROR() {
	cout << R"(

 _________________ ___________     ___ _____    ___ 
|  ___| ___ \ ___ \  _  | ___ \   /   |  _  |  /   |
| |__ | |_/ / |_/ / | | | |_/ /  / /| | |/' | / /| |
|  __||    /|    /| | | |    /  / /_| |  /| |/ /_| |
| |___| |\ \| |\ \\ \_/ / |\ \  \___  \ |_/ /\___  |
\____/\_| \_\_| \_|\___/\_| \_|     |_/\___/     |_/
                                                    
                                                    
                                                                                                                                                               
)" << endl;
	system("pause");
	exit(0);
}