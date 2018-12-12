#include <iostream>
#include <conio.h>
#include <windows.h>
using namespace std;

const int sizey = 19;
const int sizex = 19;
const int maxenemies = 100;
const int maxbutterflies = 100;
int enemies;
int floornumber;
int butterflies;
int health;
int score;
int deadenemies;
char gameScreen[100][100];
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
void createEntities();
void newFloor();
void entityMove();
void randomMove(entity entitylist[], int entity);
void gameOver();
void checkForHit(entity entitylist[], int targetx, int targety);
void hit(entity entitylist[], int entity);
void populateScreen();
void hitScreen();
void catchScreen();
void hitOrWalk(int targetx, int targety);
void printSlow(string stringtoprint);
void gotoxy(int x, int y);

int main()
{
	score = 0;
	health = 5;
	enemies = 4;
	butterflies = 2;
	floornumber = 1;
	system("color 81");
	createEntities();						//Luodaan kentt‰‰n viholliset, ker‰tt‰v‰t perhoset, sek‰ portaat seuraavaan kentt‰‰n
	populateScreen();						//Laitetaan kaikki luodut asiat paikoilleen ja t‰ytet‰‰n loppukentt‰ "." merkeill‰
	printScreen();							//Printataan kentt‰ konsoli-ikkunaan

	int input = 0;
	while (input != 27) {
		gotoxy(sizex+1, 0);
		cout << "HEALTH: ";
		printHealth();
		gotoxy(sizex + 1, 1);
		cout << "FLOOR: " << floornumber;
		gotoxy(sizex + 1, 2);
		cout << "SCORE: " << score;
		gotoxy(sizex + 1, 3);
		cout << "Move using the arrow keys";
		gotoxy(sizex + 1, 4);
		cout << "Try to catch every butterfly(%)";
		gotoxy(sizex + 1, 5);
		cout << "and stairs to the next floor will open(O)";
		gotoxy(sizex + 1, 7);
		cout << "Watch out for the goblins(G), though!";
		gotoxy(0, 0);
		input = _getch();
		switch (input) {
			case 72:{						// Pelaaja koittaa liikkua ylˆs
				if (playerx != 0) {			// Kent‰n raja
					int tempx = playerx;	// L‰hetet‰‰n temp muuttujat oikeiden sijaan (ettei pelaaja kulje asioiden l‰vitse)
					int tempy = playery;
					hitOrWalk(--tempx, tempy); // Testataan mit‰ pelaaja tekee liikkuessaan ylˆs
					break;
				}
				else break;
			}
			case 75: {						// Pelaaja koittaa liikkua vasemmalle
				if (playery != 0) {			// Kent‰n raja
					int tempx = playerx;
					int tempy = playery;
					hitOrWalk(tempx, --tempy); // Testataan mit‰ pelaaja tekee liikkuessaan vasemmalle
					break;
				}
				else break;
			}
			case 80: {						// Pelaaja koittaa liikkua alas
				if (playerx != 18) {		// Kent‰n raja
					int tempx = playerx;
					int tempy = playery;
					hitOrWalk(++tempx, tempy); // Testataan mit‰ pelaaja tekee liikkuessaan alas
					break;
				}
				else break;
			}
			case 77: {						// Pelaaja koittaa liikkua oikealle
				if (playery != 18) {		// Kent‰n raja
					int tempx = playerx;
					int tempy = playery;
					hitOrWalk(tempx, ++tempy); // Testataan mit‰ pelaaja tekee liikkuessaan oikealle
					break;
				}
				else break;
			}
		}
		system("CLS");						//Tyhjennet‰‰n konsoli-ikkuna
		populateScreen();					//T‰ytet‰‰n pelikentt‰ uusiksi pelaajan ja muiden hahmojen liikkumisen mukaan
		printScreen();						//Printataan p‰ivittynyt kentt‰
	}
}

void populateScreen() {
	for (int i = 0; i < sizex; i++)			// K‰yd‰‰n pelikentt‰ l‰pi ja lis‰t‰‰n "." jokaiseen 'peliruutuun'
	{
		for (int j = 0; j < sizey; j++)
		{
			gameScreen[i][j] = '.';
		}
	}
	gameScreen[playerx][playery] = player;					// Lis‰t‰‰n pelaaja paikalleen
	int catchedbutterflies = 0;								// Alustetaan kent‰n voittoehto myˆhemp‰‰ tarkastelua varten
	for (int i = 0; i < enemies; i++) {
		gameScreen[enemylist[i].posx][enemylist[i].posy] = enemylist[i].character; // Lis‰t‰‰n viholliset paikoilleen
	}
	for (int i = 0; i < butterflies; i++) {					// Lis‰t‰‰n perhoset paikoilleen
		gameScreen[butterflylist[i].posx][butterflylist[i].posy] = butterflylist[i].character;
		if (butterflylist[i].character == 'D')				// Katsotaan listalta ker‰ttyjen perhosten m‰‰r‰ (ker‰tty perhonen menee pois pelikent‰lt‰ ja sen merkki muuttuu "D" merkiksi)
		{
			catchedbutterflies++;
			if (catchedbutterflies >= butterflies)			// Jos pelaaja on ker‰nnyt kent‰n kaikki perhoset...
			{
				stairs.character = 'O';						//...muuttuu portaat seuraavaan kerrokseen merkiksi "O", jolloin sinne voi menn‰
			}
		}
	}
	gameScreen[stairs.posx][stairs.posy] = stairs.character; // Asetetaan portaat paikoilleen
}

void createEntities() {										// K‰yd‰‰n sek‰ vihollislista, ett‰ perhoslista l‰pi ja randomisoidaan molempien 
	for (int i = 0; i < enemies; i++) {						// paikat kent‰ll‰ kent‰n koon mukaan, randomisoidaan myˆs portaat
		enemylist[i].character = 'G';
		enemylist[i].posx = rand() % sizex;
		enemylist[i].posy = rand() % sizey;
	}
	for (int i = 0; i < butterflies; i++) {
		butterflylist[i].character = '%';
		butterflylist[i].posx = rand() % sizex;
		butterflylist[i].posy = rand() % sizey;
	}
	stairs.character = '/';
	stairs.posx = rand() % sizex;
	stairs.posy = rand() % sizey;
}


void printScreen() {								// K‰yd‰‰n pelikentt‰ l‰pi ja printataan
	for (int i = 0; i < sizex; ++i)
	{
		for (int j = 0; j < sizey; ++j)
		{
			cout << gameScreen[i][j];
		}
		cout << endl;
	}
}

void printHealth() {								// Tulostetaan el‰m‰pisteiden m‰‰r‰ UI:n
	for (int i = 0; i < health; i++)
	{
		cout << "*";
	}
}

void hitOrWalk(int targetx,int targety) {			// Tarkastellaan mit‰ tapahtuu, kun pelaaja koittaa liikkua
	if (gameScreen[targetx][targety] == 'G')		// Jos halutussa paikassa on jo vihollinen
	{
		checkForHit(enemylist, targetx, targety);	// Tarkastetaan osuma viholliseen
	}
	else if (gameScreen[targetx][targety] == '%')	// Jos halutussa paikassa on jo perhonen
	{
		checkForHit(butterflylist, targetx, targety); // Tarkastetaan osuma perhoseen
	}
	else if (gameScreen[targetx][targety] == '/')	// Jos kohdassa on suljetut portaat
	{
													// ƒl‰ tee mit‰‰n (ei mahdollista kulkea suljettujen portaiden l‰pi)
	}
	else if (gameScreen[targetx][targety] == 'O')	// Jos kohdassa avatut portaat
	{
		playerx = targetx;							// Liiku kohtaan
		playery = targety;
		newFloor();									// ja aloita uusi kentt‰
	}
	else {
		playerx = targetx;							// Muuten liiku normaalisti
		playery = targety;
	}
	entityMove();									// Kutsutaan muiden liikkumista k‰sittelev‰‰ funktiota
	checkForHit(enemylist, playerx, playery);		// Tarkastetaan viel‰ osumaa siin‰ kohdalla miss‰ olemme, 
	checkForHit(butterflylist, playerx, playery);	// silt‰ varalta ett‰ vihollinen tai perhonen on liikkunut siihen samalla vuorolla
}

void checkForHit(entity entitylist[], int targetx, int targety) {	// Tarkastellaan osumista muihin asioihin
	for (int i = 0; i < enemies; i++) {
		if (entitylist[i].posx == targetx && entitylist[i].posy == targety)
		{
			hit(entitylist, i);						// Osuessa kutsutaan funktiota joka h‰vitt‰‰ kohteen
			if (entitylist == butterflylist) {
				catchScreen();						// Jos osutaan perhoseen menn‰‰n catchScreen funktioon
			}
			else hitScreen();						// Jos osutaan viholliseen, menn‰‰n hitScreen funktioon
		}
	}
}

void hit(entity entitylist[], int entity) {		// Piilotetaan "kuolleet" asiat pois pelikent‰lt‰ ja muutetaan niitten merkki "D" 
	entitylist[entity].character = 'D';
	entitylist[entity].posx = 100;
	entitylist[entity].posy = 100;
}

void entityMove()								// Perhosten ja vihollisten liikkuminen
{
	for (int i = 0; i < enemies; i++) {
		if (enemylist[i].character == 'G')
		{
			randomMove(enemylist, i);			// Annetaan jokaiselle asialle k‰sky liikkua randomMove mukaan
		}
	}
	for (int i = 0; i < butterflies; i++) {
		if (butterflylist[i].character == '%')
		{
			randomMove(butterflylist, i);
		}
	}
}

void randomMove(entity entitylist[], int entity)// Randomisoidaan asioiden liikkuminen yksinkertaisella funktiolla
{
	int randomizer = rand() % 4;				// Random numero 0-3, joka annetaan switch case -rakenteelle 
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

void newFloor()							// Asetetaan seuraavalle kent‰lle uudet m‰‰reet
{
	floornumber++;
	enemies++;
	butterflies = enemies / 2;
	createEntities();
	populateScreen();
	printScreen();
}

void hitScreen() {						// Osumisruutu
	system("CLS");						// Tyhjennet‰‰n ruutu
	health--;							// V‰hennet‰‰n el‰m‰piste
	if (health <= 0) {
		gameOver();						// Jos el‰m‰pisteet 0, Game Over -ruutuun
	}
	for (int i = 0; i < sizex; ++i)
	{
		for (int j = 0; j < sizey; ++j)
		{
			gameScreen[i][j] = 'X';		// V‰l‰ytet‰‰n n‰yttˆ‰, jossa koko pelikentt‰ t‰ynn‰ "X" -merkki‰
		}
	}
	printScreen();
}

void catchScreen() {					// Ker‰‰misruutu
	score += floornumber;				// Lis‰t‰‰n pelaajalle pisteit‰ riippuen kuinka pitk‰ll‰ peliss‰ on
	system("CLS");						// Tyhjennet‰‰n ruutu
	for (int i = 0; i < sizex; ++i)
	{
		for (int j = 0; j < sizey; ++j)
		{
			gameScreen[i][j] = '*';		// V‰l‰ytet‰‰n n‰yttˆ‰, jossa koko pelikentt‰ t‰ynn‰ "*" -merkki‰
		}
	}
	printScreen();
}

void gameOver()							// Jos pelaaja menett‰‰ kaikki el‰m‰pisteet, printataan seuraavat asiat
{
	floornumber = 0;					// Alustetaan kerrosnumero uudelle pelikerralle
	enemies = 3;						// Alustetaan vihollism‰‰r‰ uudelle pelikerralle
	health = 5;							// Alustetaan el‰m‰pisteet uudelle pelikerralle 
	system("CLS");						// Tyhjennet‰‰n ruutu
	//cout << "Game Over!" << endl;
	//printSlow("           Game Over!");
	//cout << endl;
	//printSlow("    Press any key to try again");
	//cout << endl;
	//printSlow("-------------------------------------");
	string offset = " ";
	while (!_kbhit()) { // Odotetaan k‰ytt‰j‰n inputtia
		char R[15] = { '1','2','3','4','5','6','7','8','9','A','B','C','D','E','F' };
		char color_string[20];
		int Ra = rand() % 15;
		int Rb = rand() % 15;
		sprintf_s(color_string, "color %c%c", R[Ra], R[Rb]);
		system(color_string);
		Sleep(20);
		printSlow("GAME OVER   ---press any key---   ");
		offset += " ";
	}
	newFloor();							// Uusi kentt‰
}

void printSlow(string stringtoprint) { // Printtaa stringin kirjain kerrallaan
	for (int i = 0; i < stringtoprint.size(); i++) {
		cout << stringtoprint[i];
		Sleep(10);
	}
}

void gotoxy(int x, int y)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}