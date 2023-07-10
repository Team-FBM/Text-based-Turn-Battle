#include <iostream>
using namespace std;

class Player
{
public:
	string name;
	double HP;
	int ATK;
	int DEF;
	int AGI;

	Player(string name, double hp, int atk, int def, int agi);
	void showState();
};

class action : public Player
{
public:
	void attack(string key);
	void defense(string key);
	void heal(string key);
};

int randomfunction();