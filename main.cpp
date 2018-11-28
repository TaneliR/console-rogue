#include <iostream>
#include <conio.h>
using namespace std;

const int sizey = 19;
const int sizex = 19;
char gameScreen[sizex][sizey];
char player = '@';
int playerx = 10;
int playery = 10;

char enemy = 'G';
int enemyx = 5;
int enemyy = 5;

void printScreen();
void populateScreen();
void flashScreen();
void hitOrWalk(int targetx, int targety);

int main()
{
	int input;
	int direction;
	populateScreen();
	printScreen();
	bool gameloop = true;
	while (gameloop) {
		cout << "Move using the arrow keys";
		input = _getch();
		switch (input) {
			case 72:{						// Pelaaja liikkuu ylös
				if (playerx != 0) {
					int tempx = playerx;
					int tempy = playery;
					hitOrWalk(--tempx, tempy); //playerx--
					break;
				}
				else break;
			}
			case 75: {						// Pelaaja liikkuu vasemmalle
				if (playery != 0) {
					int tempx = playerx;
					int tempy = playery;
					hitOrWalk(tempx, --tempy); //playery--
					break;
				}
				else break;
			}
			case 80: {						// Pelaaja liikkuu alas
				if (playerx != 18) {
					int tempx = playerx;
					int tempy = playery;
					hitOrWalk(++tempx, tempy); //playerx++
					break;
				}
				else break;
			}
			case 77: {						// Pelaaja liikkuu oikealle
				if (playery != 18) {
					int tempx = playerx;
					int tempy = playery;
					hitOrWalk(tempx, ++tempy); //playery++	
					break;
				}
				else break;
			}
		}
		system("CLS");
		populateScreen();
		printScreen();
	}
	system("pause");
}

void populateScreen() {
	for (int i = 0; i < sizex; ++i)
	{
		for (int j = 0; j < sizey; ++j)
		{
			gameScreen[i][j] = '.';
		}
	}
	gameScreen[playerx][playery] = player;
	gameScreen[enemyx][enemyy] = enemy;
}

void printScreen() {
	for (int i = 0; i < sizex; ++i)
	{
		for (int j = 0; j < sizey; ++j)
		{
			cout << gameScreen[i][j];
		}
		cout << endl;
	}
}

void hitOrWalk(int targetx,int targety) {
	if (gameScreen[targetx][targety] == 'G')
	{
		flashScreen();
	}
	else {
		playerx = targetx;
		playery = targety;
	}
}

void flashScreen() {
	for (int i = 0; i < sizex; ++i)
	{
		for (int j = 0; j < sizey; ++j)
		{
			gameScreen[i][j] = 'X';
		}
	}
	printScreen();
}