#include <iostream>
#include <conio.h>
using namespace std;

const int sizey = 19;
const int sizex = 19;
char gameScreen[sizex][sizey];
char player = '@';
int playerx = 10;
int playery = 10;

void printScreen();
void populateScreen();

int main()
{
	int input;
	populateScreen();
	gameScreen[playerx][playery] = player;
	printScreen();
	bool gameloop = true;
	while (gameloop) {
		cout << "Move using 8,4,2,6";
		cin >> input;
		switch (input) {
			case 8:{
				if (playerx != 0) {
					playerx--;
					break;
				}
				else break;
			}
			case 4: {
				if (playery != 0) {
					playery--;
					break;
				}
				else break;
			}
			case 2: {
				if (playerx != 18) {
					playerx++;
					break;
				}
				else break;
			}
			case 6: {
				if (playery != 18) {
					playery++;
					break;
				}
				else break;
			}
		}
		system("CLS");
		populateScreen();
		gameScreen[playerx][playery] = player;
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