#include <iostream>
#include <conio.h>
using namespace std;

const int sizey = 19;
const int sizex = 19;
const int maxenemies = 3;
int enemies;
char gameScreen[sizex][sizey];
char player = '@';
int playerx = 10;
int playery = 10;

char enemy = 'G';
int enemyx = 5;
int enemyy = 5;

void printScreen();
void createEnemies();
void createExit();
void newFloor();
void populateScreen();
void flashScreen();
void hitOrWalk(int targetx, int targety);

struct entity {
	char character;
	int posx;
	int posy;
};
entity enemylist[maxenemies];

entity stairs;
int main()
{
	enemies = maxenemies;
	int input;
	int direction;
	
	createEnemies();
	createExit();
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
	for (int i = 0; i < enemies; i++) {
		gameScreen[enemylist[i].posx][enemylist[i].posy] = enemylist[i].character;
	}
	gameScreen[stairs.posx][stairs.posy] = stairs.character;
}

void createEnemies() {
	for (int i = 0; i < enemies; i++) {
		enemylist[i].character = 'G';
		enemylist[i].posx = rand() % 17;
		enemylist[i].posy = rand() % 17;
	}
}

void createExit() {
	stairs.character = '/';
	stairs.posx = rand() % 17;
	stairs.posy = rand() % 17;
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
		for (int i = 0; i < enemies; i++) {
			if (enemylist[i].posx == targetx && enemylist[i].posy == targety)
			{
				enemylist[i].character = 'D';
				enemylist[i].posx = 100;
				enemylist[i].posy = 100;
			}
		}
	}
	else if (gameScreen[targetx][targety] == stairs.character)
	{
		playerx = targetx;
		playery = targety;
		newFloor();
	}
	else {
		playerx = targetx;
		playery = targety;
	}
}

void newFloor()
{
	int playerx = 10;
	int playery = 10;
	createEnemies();
	createExit();
	populateScreen();
	printScreen();
}

void flashScreen() {
	system("CLS");
	for (int i = 0; i < sizex; ++i)
	{
		for (int j = 0; j < sizey; ++j)
		{
			gameScreen[i][j] = 'X';
		}
	}
	printScreen();
}