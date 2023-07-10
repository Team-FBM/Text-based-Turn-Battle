#include<iostream>
#include<random>
using namespace std;
#include"player.h"

Player *initialize();
Player *enemyState();
void roundInfo(Player*,Player*,int);


int main() 
{	
	Player*user=initialize();
	Player*enemy=enemyState();
	for (int i = 0;; i++)
	{
		roundInfo(user, enemy, i);
		string key;
		cin >> key;
	}
}




void roundInfo(Player*user, Player*enemy, int a) 
{
	cout << "------------------------------------------------------" << "\n";
	cout << "round " << a + 1 << "\n";
	enemy->Player::showState();
	user->Player::showState();
	cout << "Attack : Q" << "\n" << "Defense : W" << "\n" << "Healing : E" << "\n";
	cout << "------------------------------------------------------" << "\n";
}


