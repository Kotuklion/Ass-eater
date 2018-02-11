#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include <string>

using namespace std;
 struct player
{
    string name;
    int x;
    int y;
    int hp;
    int round;
};

int skillCheck(); //Sprawdza czy masz Faber Castlla
void manual();  //wyœwietla instrukcjê
vector<player> playerSelect(); //Wybór graczy i ich imion
void setPosition(vector<player>& players); //Wybór pozycji na mapie
int theGame(vector<player> player); // g  r  a
bool cinfail(); //czyści std::cin gdy jest przepełnione
bool positionCheck(vector<player> player); //sprawdza czy wszedłeś na innego gracza




#endif
