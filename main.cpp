#include <iostream>
#include <conio.h>
using namespace std;

const int sizey = 19;
const int sizex = 19;
const int maxenemies = 3;
int enemies;
int health;
int deadenemies;
char gameScreen[sizex][sizey];
char player = '@';
int playerx = 10;
int playery = 10;


void printHealth();
void printScreen();
void createEnemies();
void createExit();
void newFloor();
void enemyMove();
void gameOver();
void checkForHit();
void hit(int entity);
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
	health = 5;

	createEnemies();
	createExit();
	populateScreen();
	printScreen();
	bool gameloop = true;
	while (gameloop) {
		cout << "HEALTH: ";
		printHealth();
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
	int deadenemies = 0;
	for (int i = 0; i < enemies; i++) {
		gameScreen[enemylist[i].posx][enemylist[i].posy] = enemylist[i].character;
		if (enemylist[i].character == 'D')
		{
			deadenemies++;
			if (deadenemies >= enemies)
			{
				stairs.character = 'O';
			}
		}
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

void printHealth() {
	for (int i = 0; i < health; i++)
	{
		cout << "*";
	}
	cout << endl;
}

void hitOrWalk(int targetx,int targety) {
	if (gameScreen[targetx][targety] == 'G')
	{
		flashScreen();
		for (int i = 0; i < enemies; i++) {
			if (enemylist[i].posx == targetx && enemylist[i].posy == targety)
			{
				hit(i);
			}
		}
	}
	else if (gameScreen[targetx][targety] == '/')
	{
		
	}
	else if (gameScreen[targetx][targety] == 'O')
	{
		playerx = targetx;
		playery = targety;
		newFloor();
	}
	else {
		playerx = targetx;
		playery = targety;
	}
	enemyMove();
	checkForHit();
}

void checkForHit() {
	for (int i = 0; i < enemies; i++) {
		if (enemylist[i].posx == playerx && enemylist[i].posy == playery)
		{
			flashScreen();
			hit(i);
		}
	}
}

void hit(int entity) {
	enemylist[entity].character = 'D';
	enemylist[entity].posx = 100;
	enemylist[entity].posy = 100;
}

void enemyMove()
{
	for (int i = 0; i < enemies; i++) {
		if (enemylist[i].character == 'G')
		{
			int randomizer = rand() % 4;
			switch (randomizer) {
			case 0: {
				if (enemylist[i].posx != 0) {
					enemylist[i].posx--;
					break;
				}
			}
			case 1: {
				if (enemylist[i].posy != 0) {
					enemylist[i].posy--;
					break;
				}
			}
			case 2: {
				if (enemylist[i].posx != 18) {
					enemylist[i].posx++;
					break;
				}
			}
			case 3: {
				if (enemylist[i].posy != 18) {
					enemylist[i].posy++;
					break;
				}
			}
			}
		}
	}
}

void newFloor()
{
	health += 2;
	int playerx = 10;
	int playery = 10;
	createEnemies();
	createExit();
	populateScreen();
	printScreen();
}

void flashScreen() {
	system("CLS");
	health--;
	if (health <= 0) {
		gameOver();
		health = 5;
	}
	for (int i = 0; i < sizex; ++i)
	{
		for (int j = 0; j < sizey; ++j)
		{
			gameScreen[i][j] = 'X';
		}
	}
	printScreen();
}

void gameOver()
{
	system("CLS");
	cout << "Game Over!" << endl;
	cout << "Press any key to try again" << endl;
	_getch();
	newFloor();
}