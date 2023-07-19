#include<iostream>
#include<random>
#include<windows.h>
using namespace std;
class Actor;
class User;
class Enemy;


int GetRandom()
{
	random_device rd;
	mt19937 mt(rd());
	uniform_int_distribution<int>dist(0, 9);
	int randNum = dist(mt);
	return randNum;
}
int GetRandomNum()
{
	random_device rd;
	mt19937 mt(rd());
	uniform_int_distribution<int>dist(-10, 10);
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
	int TempAGI;
public:
	void ShowState()
	{
		cout << this->NAME << "\n";
		cout << "HP : " << this->curHP << "   ATK : " << this->ATK << "   DEF : "
			<< this->DEF << "   AGi : " << this->AGI << "\n";
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

};
class User :public Actor
{
	friend class Observer;
	friend class Enemy;
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

	int UAC(string A)//UAC=User Action Control
	{	
		int key;
		if (A == "Q" || A == "q")//when user attack
			return 1;
		else if (A == "W" || A == "w")//when user attack
			return 2;
		else if (A == "E" || A == "e")//when user attack
			return 3;
	}
	friend class Observer;
};

class Enemy :public Actor
{
	friend class Observer;

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

	int EAC(User *A)//EAC=Enemy Action Control
	{
		int RandNum = GetRandom();
		int key;
		if (((this->curHP) * 100 / this->HP) >= ((A->curHP) * 100 / A->HP))//when eneny HP bigger than user HP
		{
			if (RandNum > 7)//enemy attack 
			{
				key = 1;
				return key;
			}
			else if (RandNum <= 7 && RandNum > 3)//enemy defense
			{
				key = 2;
				return key;
			}
			else if (RandNum >= 0 && RandNum < 4)//enemy healing
			{
				key = 3;
				return key;
			}
		}
		else if (((this->curHP) * 100 / this->HP) < ((A->curHP) * 100 / A->HP))//when enemy HP small than user HP
		{
			if (RandNum > 2)//enmey attack
			{
				key = 1;
				return key;
			}
			else if (RandNum == 1 || RandNum == 2)//eneny defense
			{

				key = 2;
				return key;
			}
			else if (RandNum == 0)//enmey healing
			{
				key = 3;
				return key;
			}
		}
	}
	friend class Observer;
};



class Observer:Actor
{
	friend class User;
	friend class Enemy;
public:

	void StateMachine(User *A,Enemy* B,string C)
	{	
		int U = A->UAC(C);
		int E = B->EAC(A);

		int UserAGI = A->Get("AGI");
		int EnemyAGI = B->Get("AGI");

		if (UserAGI >= EnemyAGI)
		{
			if (U == 1 && E == 1)
			{
				UserAttack(A,B);
				EnemyAttack(A,B);
			}
			else if (U == 1 && E == 2)
			{
				UserAttack(A,B);
				EnemyDefense();
			}
			else if (U == 1 && E == 3)
			{
				UserAttack(A,B);
				EnemyHealing(B);
			}
			else if (U == 2 && E == 1)
			{
				UserDefense();
				EnemyAttack(A,B);
			}
			else if (U == 2 && E == 2)
			{
				UserDefense();
				EnemyDefense();
			}
			else if (U == 2 && E == 3)
			{
				UserDefense();
				EnemyHealing(B);
			}
			else if (U == 3 && E == 1)
			{
				UserHealing(A);
				EnemyAttack(A,B);
			}
			else if (U == 3 && E == 2)
			{
				UserHealing(A);
				EnemyDefense();
			}
			else if (U == 3 && E == 3)
			{
				UserHealing(A);
				EnemyHealing(B);
			}

		}
		else if (UserAGI < EnemyAGI)
		{
			if (U == 1 && E == 1)
			{
				EnemyAttack(A,B);
				UserAttack(A,B);
			}
			else if (U == 1 && E == 2)
			{
				EnemyDefense();
				UserAttack(A,B);
			}
			else if (U == 1 && E == 3)
			{
				EnemyHealing(B);
				UserAttack(A,B);
			}
			else if (U == 2 && E == 1)
			{
				EnemyAttack(A,B);
				UserDefense();
			}
			else if (U == 2 && E == 2)
			{
				EnemyDefense();
				UserDefense();
			}
			else if (U == 2 && E == 3)
			{
				EnemyHealing(B);
				UserDefense();
			}
			else if (U == 3 && E == 1)
			{
				EnemyAttack(A,B);
				UserHealing(A);
			}
			else if (U == 3 && E == 2)
			{
				EnemyDefense();
				UserHealing(A);
			}
			else if (U == 3 && E == 3)
			{
				EnemyHealing(B);
				UserHealing(A);
			}
		}

		
		
	}


	void UserAttack(User *A, Enemy*B)//A->B this->A,
	{
		int RandNum1 = GetRandom();
		int RandNum2 = GetRandom();
		bool EnemyDefenseKey =CheckEnemyDefenseKey();
		if (EnemyDefenseKey == true)
		{
			int ATKDEF = A->ATK - B->DEF;
			if (ATKDEF < 0)
				ATKDEF = 0;

			cout << A->NAME << " attacked, but " << B->NAME << " defended. : " << -ATKDEF << "\n";
			ReturnEnemyDefenseKey();
		}



		else
		{
			if (RandNum1 < 9)
			{
				EnemyDamaged(A,B);
				cout << A->NAME << " Attacked : -" << A->ATK << "\n";
				if (RandNum2 == 9)
				{
					int Rate = GetRandomNum();
					B->TempAGI = B->AGI - (A->ATK + (A->ATK * Rate / 10));
					B->AGI = B->TempAGI;
					cout << B->NAME << " AGI has been reduced for one turn due to " << A->NAME << "'s attack! : "
						<< -(A->ATK + (A->ATK * Rate / 10)) << "\n";
				}
			}
			else if (RandNum1 == 9)
			{
				cout << A->NAME << " Attacked, but you missed it. : -0\n";
			}
		}
	}


	void UserHealing(User*A)
	{
		A->curHP = curHP + ATK + DEF;

		if (curHP >= 200)
			curHP = 200;

		cout << this->NAME << "Healed : +" << this->ATK + this->DEF << "\n";
	}

	/////////////////////////////////////////////////////////

	void EnemyAction(User* A,Enemy*B)//this->B
	{
		int RandNum = GetRandom();
		if (((B->curHP) * 100 / B->HP) > ((A->curHP) * 100 / A->HP))
		{
			if (RandNum > 7)
				EnemyAttack(A,B);
			else if (RandNum <= 7 && RandNum > 3)
				EnemyDefense();
			else if (RandNum >= 0 && RandNum < 4)
				EnemyHealing(B);
		}
		else if (((B->curHP) * 100 / B->HP) < ((A->curHP) * 100 / A->HP))
		{
			if (RandNum > 2)
				EnemyAttack(A,B);
			else if (RandNum == 1 || RandNum == 2)
				EnemyDefense();
			else if (RandNum == 0)
				EnemyHealing(B);
		}
	}

	void EnemyAttack(User* A,Enemy*B)//this->B
	{
		int RandNum1 = GetRandom();
		int RandNum2 = GetRandom();
		bool UserDefenseKey = CheckUserDefenseKey();
		if (UserDefenseKey == true)
		{
			int ATKDEF = B->ATK - A->DEF;
			if (ATKDEF < 0)
				ATKDEF = 0;


			cout << B->NAME << " attacked, but " << A->NAME << " defended. : " << -ATKDEF << "\n";
			ReturnUserDefenseKey();
		}
		else
		{
			if (RandNum1 < 9)
			{
				UserDamaged(A,B);
				cout << B->NAME << " attacked : -" << B->ATK << "\n";

				if (RandNum2 == 9)
				{
					int Rate = GetRandomNum();
					A->TempAGI = A->AGI - (B->ATK + (B->ATK * Rate / 10));
					A->AGI = A->TempAGI;
					cout << B->NAME << " AGI has been reduced for one turn due to " << A->NAME << "'s attack! : "
						<< -(B->ATK + (B->ATK * Rate / 10)) << "\n";
				}

			}
			else if (RandNum1 == 9)
			{
				cout << B->NAME << " attacked but missed. : -0\n";
			}
		}
	}
	void EnemyHealing(Enemy*B)
	{
		B->curHP = B->curHP + B->ATK + B->DEF;

		if (B->curHP >= 1000)
			B->curHP = 1000;

		cout << B->NAME << "Healed : +" << B->ATK + B->DEF << "\n";
	}
	int UserDefenseKey;

	void UserDefense()
	{
		UserDefenseKey = 1;
	}
	bool CheckUserDefenseKey()
	{
		if (UserDefenseKey == 1)
			return true;
		else
			return false;
	}
	int ReturnUserDefenseKey()
	{
		UserDefenseKey = 0;
		return UserDefenseKey;
	}
	
	int EnemyDefenseKey;

	void EnemyDefense()
	{
		EnemyDefenseKey = 1;
	}
	bool CheckEnemyDefenseKey()
	{
		if (EnemyDefenseKey == 1)
			return true;
		else
			return false;
	}
	int ReturnEnemyDefenseKey()
	{
		EnemyDefenseKey = 0;
		return EnemyDefenseKey;
	}
	void UserDamaged(User* A, Enemy* B)
	{
		A->curHP = A->curHP - B->ATK;
	}
	void EnemyDamaged(User* A, Enemy* B)
	{
		B->curHP = B->curHP - A->ATK;
	}
};



void Initialize(User*& A, Enemy*& B);
void RoundInfo(int i, User*& A, Enemy*& B);





int main()
{
	User* user;
	Enemy* enemy;
	Observer* observer = new Observer();
	Initialize(user, enemy);


	for (int i = 0;; i++)
	{

		RoundInfo(i, user, enemy);
		string A;
		string key;//User Action Control Key
		cin >> key;
		cout << "--------------------------------------------------\n";
		
		double UserHP = user->GetHP("curHP");
		double EnemyHP = enemy->GetHP("curHP");

		observer->StateMachine(user, enemy, key);

		if (UserHP == 0 || EnemyHP == 0)
			break;
		
		cout << "Enter any key to proceed next round\n";
		cin >> A;
		system("cls");
		
	}

}







void Initialize(User*& A, Enemy*& B)
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

