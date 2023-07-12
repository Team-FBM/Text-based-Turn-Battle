#include<iostream>
using namespace std;

class Actor
{
protected:
	string NAME;
	double HP;
	double curHp;
	int ATK;
	int DEF;
	int AGI;
public:
void ShowState()
	{
		cout << this->NAME << "\n";
		cout << "HP : " << this->curHp << "   ATK : " << this->ATK << "   DEF : "
			 << this->DEF << "   AGi : " << this->AGI << "\n";
	}


};

class User:public Actor
{
public:
	User(double hp, int atk, int def, int agi)
	{
		string username;
		cin >> username;
		this->NAME = username;
		this->HP = hp;
		this->curHp = HP;
		this->ATK = atk;
		this->DEF = def;
		this->AGI = agi;
	}
};

class Enemy:public Actor
{
public:
	Enemy(string enemyname, double hp, int atk, int def, int agi)
	{
		this->NAME = enemyname;
		this->HP = hp;
		this->curHp = HP;
		this->ATK = atk;
		this->DEF = def;
		this->AGI = agi;
	}
};

void Initialize(Actor* &A, Actor* &B);
void RoundInfo(int i, Actor* &A, Actor*&B);

int main()
{
	Actor *user,*enemy;
	Initialize(user,enemy);
	cout<<"hi";

	for(int i;;i++)
	{
		RoundInfo(i,user,enemy);
	}

}





void Initialize(Actor* &A, Actor* &B)
{
	cout << "Enter your name : ";
	A =new User(200, 20, 10, 30);
	B =new Enemy("enemy", 1000, 30, 20, 40);
	cout << "\nStart the battle.\n";
}

void RoundInfo(int i,Actor *&A,Actor *&B)
{
	cout << "--------------------------------------------------\n";
	cout << "round " << i + 1 << "\n";
	A->ShowState();
	B->ShowState();

	cout << "\nAttack : Q\n";
	cout << "Defense : W\n";
	cout << "Healing : E\n";
}