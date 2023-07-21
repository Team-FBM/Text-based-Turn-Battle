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
	int SaveAGI;
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
		this->SaveAGI = this->AGI;
	}

	int USM(string A)//USM=User State Machine
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
		this->SaveAGI = this->AGI;
	}

	int ESM(User* A)//ESM=Enemy State Machine
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



class Observer :Actor
{
	friend class User;
	friend class Enemy;
public:
	int UserAGIDecreaseRound = 0;
	int EnemyAGIDecreaseRound = 0;

	void ActionControl(User* A, Enemy* B, string C, int i)
	{
		int U = A->USM(C);
		int E = B->ESM(A);
		int UserAGI = A->Get("AGI");
		int EnemyAGI = B->Get("AGI");

		if (UserAGI >= EnemyAGI)
		{
			if (U == 1 && E == 1)
			{
				UserAttack(A, B, i);
				EnemyAttack(A, B, i);
				UserRestoreAGI(A, EnemyAGIDecreaseRound, i);
				EnemyRestoreAGI(B, UserAGIDecreaseRound, i);
			}
			else if (U == 1 && E == 2)
			{
				UserAttack(A, B, i);
				EnemyDefense();
				UserRestoreAGI(A, EnemyAGIDecreaseRound, i);
				EnemyRestoreAGI(B, UserAGIDecreaseRound, i);
			}
			else if (U == 1 && E == 3)
			{
				UserAttack(A, B, i);
				EnemyHealing(B);
				UserRestoreAGI(A, EnemyAGIDecreaseRound, i);
				EnemyRestoreAGI(B, UserAGIDecreaseRound, i);
			}
			else if (U == 2 && E == 1)
			{
				UserDefense();
				EnemyAttack(A, B, i);
				UserRestoreAGI(A, EnemyAGIDecreaseRound, i);
				EnemyRestoreAGI(B, UserAGIDecreaseRound, i);
			}
			else if (U == 2 && E == 2)
			{
				UserDefense();
				EnemyDefense();
				UserRestoreAGI(A, EnemyAGIDecreaseRound, i);
				EnemyRestoreAGI(B, UserAGIDecreaseRound, i);
			}
			else if (U == 2 && E == 3)
			{
				UserDefense();
				EnemyHealing(B);
				UserRestoreAGI(A, EnemyAGIDecreaseRound, i);
				EnemyRestoreAGI(B, UserAGIDecreaseRound, i);
			}
			else if (U == 3 && E == 1)
			{
				UserHealing(A);
				EnemyAttack(A, B, i);
				UserRestoreAGI(A, EnemyAGIDecreaseRound, i);
				EnemyRestoreAGI(B, UserAGIDecreaseRound, i);
			}
			else if (U == 3 && E == 2)
			{
				UserHealing(A);
				EnemyDefense();
				UserRestoreAGI(A, EnemyAGIDecreaseRound, i);
				EnemyRestoreAGI(B, UserAGIDecreaseRound, i);
			}
			else if (U == 3 && E == 3)
			{
				UserHealing(A);
				EnemyHealing(B);
				UserRestoreAGI(A, EnemyAGIDecreaseRound, i);
				EnemyRestoreAGI(B, UserAGIDecreaseRound, i);
			}

		}
		else if (UserAGI < EnemyAGI)
		{
			if (U == 1 && E == 1)
			{
				EnemyAttack(A, B, i);
				UserAttack(A, B, i);
				UserRestoreAGI(A, EnemyAGIDecreaseRound, i);
				EnemyRestoreAGI(B, UserAGIDecreaseRound, i);
			}
			else if (U == 1 && E == 2)
			{
				EnemyDefense();
				UserAttack(A, B, i);
				UserRestoreAGI(A, EnemyAGIDecreaseRound, i);
				EnemyRestoreAGI(B, UserAGIDecreaseRound, i);
			}
			else if (U == 1 && E == 3)
			{
				EnemyHealing(B);
				UserAttack(A, B, i);
				UserRestoreAGI(A, EnemyAGIDecreaseRound, i);
				EnemyRestoreAGI(B, UserAGIDecreaseRound, i);
			}
			else if (U == 2 && E == 1)
			{
				EnemyAttack(A, B, i);
				UserDefense();
				UserRestoreAGI(A, EnemyAGIDecreaseRound, i);
				EnemyRestoreAGI(B, UserAGIDecreaseRound, i);
			}
			else if (U == 2 && E == 2)
			{
				EnemyDefense();
				UserDefense();
				UserRestoreAGI(A, EnemyAGIDecreaseRound, i);
				EnemyRestoreAGI(B, UserAGIDecreaseRound, i);
				
			}
			else if (U == 2 && E == 3)
			{
				EnemyHealing(B);
				UserDefense();
				UserRestoreAGI(A, EnemyAGIDecreaseRound, i);
				EnemyRestoreAGI(B, UserAGIDecreaseRound, i);
			}
			else if (U == 3 && E == 1)
			{
				EnemyAttack(A, B, i);
				UserHealing(A);
				UserRestoreAGI(A, EnemyAGIDecreaseRound, i);
				EnemyRestoreAGI(B, UserAGIDecreaseRound, i);
			}
			else if (U == 3 && E == 2)
			{
				EnemyDefense();
				UserHealing(A);
				UserRestoreAGI(A, EnemyAGIDecreaseRound, i);
				EnemyRestoreAGI(B, UserAGIDecreaseRound, i);
			}
			else if (U == 3 && E == 3)
			{
				EnemyHealing(B);
				UserHealing(A);
				UserRestoreAGI(A, EnemyAGIDecreaseRound, i);
				EnemyRestoreAGI(B, UserAGIDecreaseRound, i);
			}
		}



	}


	void UserAttack(User* A, Enemy* B, int i)
	{
		int RandNum1 = GetRandom();
		int RandNum2 = GetRandom();
		bool EnemyDefenseKey = CheckEnemyDefenseKey();//check opponent defenFded.

		if (EnemyDefenseKey == true)//when opponent defended
		{
			int ATKDEF = A->ATK - B->DEF;
			if (ATKDEF < 0)//if ATK-DEF is negative, treat it 0
				ATKDEF = 0;

			cout << A->NAME << " attacked, but " << B->NAME << " defended. : " << -ATKDEF << "\n";
			ReturnEnemyDefenseKey();
		}



		else//when opponent doesn't defended
		{
			if (RandNum1 < 9)//when attack
			{
				EnemyDamaged(A, B);
				cout << A->NAME << " Attacked : -" << A->ATK << "\n";
				if (RandNum2 == 9)//when attack and decrease AGI
				{
					DecreaseAGI(A, B);
					EnemyAGIDecreaseRound = i;
				}
			}
			else if (RandNum1 == 9)//when attack miss
			{
				cout << A->NAME << " Attacked, but you missed it. : -0\n";
			}
		}
	}


	void UserHealing(User* A)
	{
		A->curHP = A->curHP + A->ATK + A->DEF;

		if (A->curHP >= 200)//max enemyHp it 200
			A->curHP = 200;

		cout << A->NAME << "Healed : +" << A->ATK + A->DEF << "\n";
	}


	void EnemyAction(User* A, Enemy* B, int i)
	{
		int RandNum = GetRandom();
		if (((B->curHP) * 100 / B->HP) >= ((A->curHP) * 100 / A->HP))//when enemyHP>=userHP
		{
			if (RandNum > 7)
				EnemyAttack(A, B, i);
			else if (RandNum <= 7 && RandNum > 3)
				EnemyDefense();
			else if (RandNum >= 0 && RandNum < 4)
				EnemyHealing(B);
		}
		else if (((B->curHP) * 100 / B->HP) < ((A->curHP) * 100 / A->HP))//when userHP<enemyHP
		{
			if (RandNum > 2)
				EnemyAttack(A, B, i);
			else if (RandNum == 1 || RandNum == 2)
				EnemyDefense();
			else if (RandNum == 0)
				EnemyHealing(B);
		}
	}

	void EnemyAttack(User* A, Enemy* B, int i)//this->B
	{
		int RandNum1 = GetRandom();
		int RandNum2 = GetRandom();
		bool UserDefenseKey = CheckUserDefenseKey();//check opponent defended
		if (UserDefenseKey == true)//when opponent defended
		{
			int ATKDEF = B->ATK - A->DEF;
			if (ATKDEF < 0)//if ATK-DEF is negative, treat it 0
				ATKDEF = 0;


			cout << B->NAME << " attacked, but " << A->NAME << " defended. : " << -ATKDEF << "\n";
			ReturnUserDefenseKey();
		}
		else//when opponent doesn't defended
		{
			if (RandNum1 < 9)//when attack
			{
				UserDamaged(A, B);
				cout << B->NAME << " attacked : -" << B->ATK << "\n";

				if (RandNum2 == 9)//when attack and decrease AGI
				{
					DecreaseAGI(A, B);
					UserAGIDecreaseRound = i;
				}

			}
			else if (RandNum1 == 9)//when attack miss
			{
				cout << B->NAME << " attacked but missed. : -0\n";
			}
		}
	}
	void EnemyHealing(Enemy* B)
	{
		B->curHP = B->curHP + B->ATK + B->DEF;

		if (B->curHP >= 1000)//max enemyHP is 1000
			B->curHP = 1000;

		cout << B->NAME << "Healed : +" << B->ATK + B->DEF << "\n";
	}
	int UserDefenseKey;

	void UserDefense()
	{
		UserDefenseKey = 1;
	}
	bool CheckUserDefenseKey()//check user defense
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

	void EnemyDefense()//check enemy defense
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

	void UserRestoreAGI(User *A, int a, int i)
	{
		if (a + 2 == i)
		{
			A->AGI = A->SaveAGI;
		}
	}
	void EnemyRestoreAGI(Enemy* A, int a, int i)
	{
		if (a + 2 == i)
		{
			A->AGI = A->SaveAGI;
		}
	}

	void DecreaseAGI(User* A, Enemy* B)
	{
		int Rate = GetRandomNum();
		A->TempAGI = A->AGI - (B->ATK + (B->ATK * Rate / 10));
		A->AGI = A->TempAGI;
		cout << B->NAME << " AGI has been reduced for one turn due to " << A->NAME << "'s attack! : "
			<< -(B->ATK + (B->ATK * Rate / 10)) << "\n";
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

		observer->ActionControl(user, enemy, key, i);

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

