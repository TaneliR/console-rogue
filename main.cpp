#include <iostream>
#include <conio.h>
using namespace std;

const int sizey = 19;
const int sizex = 19;
const int maxenemies = 100;
const int maxbutterflies = 100;
int enemies;
int butterflies;
int health;
int deadenemies;
char gameScreen[sizex][sizey];
char player = '@';
int playerx = 10;
int playery = 10;

struct entity {
	char character;
	int posx;
	int posy;
};
entity enemylist[maxenemies];
entity butterflylist[maxbutterflies];

entity stairs;

void printHealth();
void printScreen();
void createEnemies();
void createExit();
void newFloor();
void enemyMove();
void randomMove(entity entitylist[], int entity);
void gameOver();
void checkForHit(entity entitylist[]);
void hit(entity entitylist[], int entity);
void populateScreen();
void flashScreen();
void hitOrWalk(int targetx, int targety);


int main()
{
	enemies = 3;
	butterflies = 1;
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
	int catchedbutterflies = 0;
	for (int i = 0; i < enemies; i++) {
		gameScreen[butterflylist[i].posx][butterflylist[i].posy] = butterflylist[i].character;
		gameScreen[enemylist[i].posx][enemylist[i].posy] = enemylist[i].character;
		if (butterflylist[i].character == 'D')
		{
			catchedbutterflies++;
			if (catchedbutterflies >= butterflies)
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
	for (int i = 0; i < butterflies; i++) {
		butterflylist[i].character = '%';
		butterflylist[i].posx = rand() % 17;
		butterflylist[i].posy = rand() % 17;
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
		checkForHit(enemylist);
	}
	else if (gameScreen[targetx][targety] == '%')
	{
		checkForHit(butterflylist);
	}
	else if (gameScreen[targetx][targety] == '/')
	{
		
	}
	else if (gameScreen[targetx][targety] == 'O')
	{
		playerx = targetx;
		playery = targety;
		enemies++;
		newFloor();
	}
	else {
		playerx = targetx;
		playery = targety;
	}
	enemyMove();
	checkForHit(enemylist);
	checkForHit(butterflylist);
}

void checkForHit(entity entitylist[]) {
	for (int i = 0; i < enemies; i++) {
		if (entitylist[i].posx == playerx && entitylist[i].posy == playery)
		{
			flashScreen();
			hit(entitylist, i);
		}
	}
}

void hit(entity entitylist[], int entity) {
	entitylist[entity].character = 'D';
	entitylist[entity].posx = 100;
	entitylist[entity].posy = 100;
	if (entitylist = butterflylist){

	}
}

void enemyMove()
{
	for (int i = 0; i < enemies; i++) {
		if (enemylist[i].character == 'G')
		{
			randomMove(enemylist, i);
		}
	}
	for (int i = 0; i < butterflies; i++) {
		if (butterflylist[i].character == '%')
		{
			randomMove(butterflylist, i);
		}
	}
}

void randomMove(entity entitylist[], int entity)
{
	int randomizer = rand() % 4;
			switch (randomizer) {
			case 0: {
				if (entitylist[entity].posx != 0) {
					entitylist[entity].posx--;
					break;
				}
			}
			case 1: {
				if (entitylist[entity].posy != 0) {
					entitylist[entity].posy--;
					break;
				}
			}
			case 2: {
				if (entitylist[entity].posx != 18) {
					entitylist[entity].posx++;
					break;
				}
			}
			case 3: {
				if (entitylist[entity].posy != 18) {
					entitylist[entity].posy++;
					break;
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
	enemies = 3;
	health = 5;
	system("CLS");
	cout << "Game Over!" << endl;
	cout << "Press any key to try again" << endl;
	_getch();
	newFloor();
}