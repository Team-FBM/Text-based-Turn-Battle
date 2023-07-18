#include<iostream>
#include<random>
using namespace std;

int GetRandom()
{
	random_device rd;
	mt19937 mt(rd());
	uniform_int_distribution<int>dist(0, 9);
	int randNum = dist(mt);
	return randNum;
}

class Actor
{
protected:
	string NAME;
	double HP;
	double curHP;
	int ATK;
	int DEF;
	int AGI;
public:
	void ShowState()
	{
		cout << this->NAME << "\n";
		cout << "HP : " << this->curHP << "   ATK : " << this->ATK << "   DEF : "
			<< this->DEF << "   AGi : " << this->AGI << "\n";
	}

	void Damaged(Actor* A)
	{

		A->curHP = A->curHP - ATK;
	}

	int Get(string A)
	{
		if (A == "ATK")
			return ATK;
		if (A == "DEF")
			return DEF;
		if (A == "AGI")
			return AGI;
	}

	double GetHP(string A)
	{
		if (A == "HP")
			return HP;
		if (A == "curHP")
			return curHP;
	}

	void UserAttack(Actor* A)
	{
		int RandNum = GetRandom();

		if (RandNum < 9)
		{
			Damaged(A);
			cout << this->NAME << " Attacked : -" << this->ATK << "\n";
		}
		else if (RandNum == 9)
		{
			cout << this->NAME << " Attacked, but you missed it. : -0\n";
		}

	}

	void UserHealing()
	{
		this->curHP = curHP + ATK + DEF;

		if (curHP >= 200)
			curHP = 200;

		cout << this->NAME << "Healed : +" << this->ATK + this->DEF << "\n";
	}

	/*void Deffense()
	{

	}*/

};

class User :public Actor
{
public:
	User(double hp, int atk, int def, int agi)
	{
		string username;
		cin >> username;
		this->NAME = username;
		this->HP = hp;
		this->curHP = HP;
		this->ATK = atk;
		this->DEF = def;
		this->AGI = agi;
	}



	friend class Enemy;




};

class Enemy :public Actor
{
public:
	Enemy(string enemyname, double hp, int atk, int def, int agi)
	{
		this->NAME = enemyname;
		this->HP = hp;
		this->curHP = HP;
		this->ATK = atk;
		this->DEF = def;
		this->AGI = agi;
	}

	void EnemyAction(User* A)
	{
		GetHP("curHP");
		int RandNum = GetRandom();
		if (((this->curHP) * 100 / this->HP) > ((A->curHP) * 100 / A->HP))
		{
			if (RandNum > 7)
				EnemyAttack(A);
			/*else if (RandNum <= 7 && RandNum > 3)
				EnemyDeffense();*/
			else if (RandNum >= 0 && RandNum < 4)
				EnemyHealing();
		}
		else if (((this->curHP) * 100 / this->HP) < ((A->curHP) * 100 / A->HP))
		{
			if (RandNum > 2)
				EnemyAttack(A);
			/*else if (RandNum == 1 || RandNum == 2)
				EnemyDeffense();*/
			else if (RandNum == 0)
				EnemyHealing();
		}
	}

	void EnemyAttack(Actor* A)
	{
		int RandNum = GetRandom();

		if (RandNum < 9)
		{
			Damaged(A);
			cout << this->NAME << " attacked : -" << this->ATK << "\n";
		}
		else if (RandNum == 9)
		{
			cout << this->NAME << " attacked but missed. : -0\n";
		}
	}

	/*void EnemyDeffense()
	{

	}*/

	void EnemyHealing()
	{
		this->curHP = curHP + ATK + DEF;

		if (curHP >= 1000)
			curHP = 1000;

		cout << this->NAME << "Healed : +" << this->ATK + this->DEF << "\n";
	}
};



void Initialize(User*& A, Enemy*& B);
void RoundInfo(int i, User*& A, Enemy*& B);





int main()
{
	User* user;
	Enemy* enemy;
	Initialize(user, enemy);

	for (int i = 0;; i++)
	{
		RoundInfo(i, user, enemy);
		string key;
		cin >> key;
		cout << "--------------------------------------------------\n";
		if (key == "Q" || key == "q")
			user->UserAttack(enemy);

		else if (key == "E" || key == "e")
			user->UserHealing();

		enemy->EnemyAction(user);

		// if(User->curHP==0)
		// break;
		// else if(Enemy->curHP==0)
	}

}





void Initialize(User *& A, Enemy *& B)
{
	cout << "Enter your name : ";
	A = new User(200, 20, 10, 30);
	B = new Enemy("enemy", 1000, 30, 20, 40);
	cout << "\nStart the battle.\n";
}

void RoundInfo(int i, User*& A, Enemy*& B)
{
	cout << "--------------------------------------------------\n";
	cout << "round " << i + 1 << "\n";
	A->ShowState();
	B->ShowState();

	cout << "\nAttack : Q\n";
	cout << "Defense : W\n";
	cout << "Healing : E\n";
	cout << "--------------------------------------------------\n";
}