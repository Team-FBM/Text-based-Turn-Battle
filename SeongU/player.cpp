#include<iostream>
#include<random>
using namespace std;
#include"player.h";

Player::Player(string name, double hp, int atk, int def, int agi)
{
	this->name = name;
	this->HP = hp;
	this->ATK = atk;
	this->DEF = def;
	this->AGI = agi;
}

void Player::showState() 
{
	cout << this->name << endl;
	cout << "HP : " << this->HP << "   ";
	cout << "ATK : " << this->ATK << "   ";
	cout << "DEF : " << this->DEF << "   ";
	cout << "AGI : " << this->AGI << endl;
}

Player *initialize()
{	
	string username;
	cout << "Enter your name : ";
	cin >> username;
	Player* user = new Player(username, 200, 20, 10, 30);
	cout << "Start the battle." << "\n";
	return user;
}

Player* enemyState()
{
	Player* enemy = new Player("enemy", 1000, 30, 20, 40);
	return enemy;
}

// int randomfucntion(int num)
// {
// 	random_device rd;
// 	mt19937 mt(rd());
// 	uniform_int_distribution<int>dist(0, 9);
// 	num = dist(mt);

// 	return num;
// }

// void action::attack(string key)
// {
// 	int CHP = this->HP;

// }