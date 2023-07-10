#include <iostream>
#include <random>
using namespace std;

bool getTrueWithProbability()
{
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> dis(0.0, 1.0);

    double randomValue = dis(gen);
    return randomValue <= 0.9;
}

class Player
{
public:
    string name;
    double hp;
    double curHp;
    int atk;
    int def;
    int agi;
    Player(string name, double hp, int atk, int deg, int agi)
    {
        this->name = name;
        this->hp = hp;
        this->curHp = hp;
        this->atk = atk;
        this->def = def;
        this->agi = agi;
    }
    Player(double hp, int atk, int deg, int agi)
    {
        string username;
        cin >> username;
        this-> name = username;
        this->hp = hp;
        this->curHp = hp;
        this->atk = atk;
        this->def = def;
        this->agi = agi;
    }
    void damaged(Player *opponent)
    {
        if (opponent->atk > this->def)
        {
            if (getTrueWithProbability())
            {
                cout << opponent->name << "attacked : -" << opponent->atk - this->def << endl;
                this->curHp -= (opponent->atk - this->def);
            }
            else
            {
                cout << opponent->name << "attacked, but missed." << endl;
            }
        }
    }
};
void printRoundInfo(Player *player, Player *enemy, int round)
{
    cout << "-------------------------------------------------" << endl;
    cout << "round " << round << endl;
    cout << enemy->name << endl;
    cout << "HP:  " << enemy->hp
         << "\tATK :  " << enemy->atk
         << "\tDEF :  " << enemy->def
         << "\tAGI :  " << enemy->agi << endl;
    cout << player->name << endl;
    cout << "HP:  " << player->hp
         << "\tATK :  " << player->atk
         << "\tDEF :  " << player->def
         << "\tAGI :  " << player->agi << endl;
}

Player * initializeCharacter()
{
    cout << "name : ";
    string username;
    cin >> username;
    Player *user = new Player(username, 100, 20, 20, 20);
    return user;
}
Player * initializeCharacter(string name)
{
    Player *enemy = new Player(name, 1000, 10, 10, 10);
    return enemy;


}


int main()
{
    Player ** players = new Player*[2];
    players[0]= new Player(100, 20, 20, 20);
    players[1]= new Player("enenmy",100, 20, 20, 20);
    
    for (int i = 0;; i++)
    {
        printRoundInfo(user, enemy, i);
        char action;
        cin >> action;
        switch (action)
        {
        case 'Q':
            if (user->agi >= enemy->agi)
            {
                enemy->damaged(user);
                user->damaged(enemy);
            }
            else
            {
                user->damaged(enemy);
                enemy->damaged(user);
            }
            break;
        case 'W':


        case 'E':
        }
    }
}