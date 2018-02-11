#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include "functions.h"



int main()
{

    cout << "Witamy w Faber Castell! Dziekujemy za wybranie naszej marki." << endl;
    cout << "Czy chciałbyś zagrać? Jeżeli nie, po prostu napisz n" << endl;
    char answer;
    cin >> answer;
    cinfail();
    if (answer == 'n')
    {
        return 0;
    }
    manual();
    vector<player>players = playerSelect();
    setPosition(players);
    theGame(players);
}
