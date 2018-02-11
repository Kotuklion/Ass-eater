#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <ctime>
#include <conio.h>
#include "functions.h"

using namespace std;


int skillCheck()
{
    int x = time(0);
    x = x % 10;
    if (x <= 4)
        return 0;
    else if(x <=8)
        return 1;
    else
        return 2;
}

bool cinfail()
{
      if(cin.fail())
          {
              cin.clear();
              cin.ignore(32767,'\n');
              cout << "zle!!!!" << endl;
              return true;
          }
}

bool positionCheck(vector<player> player, int i)
{
    for (int k = 0;k<player.size();k++)
                {
                    if(player[i].x == player[k].x && player[i].y == player[k].y && k != i)
                    {
                        cout << endl << "test" << endl << player[i].x << endl << player[1].x << endl << player[i].y << endl << player[1].y << endl;
                        cout << endl << "i = " << i;
                        cout << "Wszedłeś na innego gracza!!" << endl;
                        return true;
                    }
                }
}

void manual()
{
    cout << endl << "Wraz z wyborem graczy możemy przejść do rozgrywki. Aby wygrać, należy zabić pozostałych graczy." << endl;
    cout << "Gra toczona jest na losowo generowanej dwuwymiarowej planszy 100x100." << endl;    //jeszcze nie zrobione
    cout << "Orientacja następuje przy użyciu zmiennych x i y, mapa obejmuje więc obszar " << endl;
    cout << "od x = 0,y = 0 do x = 100, y = 100." << endl << endl;
}


vector<player> playerSelect()
{
     bool nameSelect = true;
    while(nameSelect)
    {
        cout << "Prosze o wybranie liczby graczy." << endl;
        int playerNumber = 0;
        while(playerNumber<=1)       //Wybór liczby graczy
        {
          cin >> playerNumber;
          if(cin.fail())
          cinfail();
          else if(playerNumber<=1)
          {
              cout << "Liczba graczy nie moze byc mniejsza niz 1! Sprobuj znowu." << endl;
          }
        }
        vector<player> playerNames;
        playerNames.resize(playerNumber);
        for(int i = 0;i<playerNumber;i++)
        {
            cout << endl << "Podaj imie dla gracza nr. " << i+1 << endl;
            cin >> playerNames[i].name;
            cin.ignore(32767, '\n');
            for(int k = 0;k<i;k++)  //sprawdza czy przypadkiem nie uzyto takich samych imion dla dwoch graczy
            {
                if(playerNames[i].name == playerNames[k].name)
                {
                    cout << "Podałeś takie samo imię jakie ma gracz " << playerNames[k].name << "! Wybierz inne." << endl;
                    i--;
                }
            }
        }
        //Sprawdzenie poprawnoœci danych
        cout << "Czy jestes pewien, ze w rozgrywce ma brac udzial " << playerNumber << " graczy";
        for(int i = 0;i<playerNumber;i++)
        {
            if(i+1==playerNumber)
            {
              cout << " i " << playerNames[i].name << "? y/n" << endl;
            }
            else
            {
                cout << ", " << playerNames[i].name;
            }
        }
        char answer;
        cin >> answer;
        if(answer=='y')
        {
            nameSelect = false;
            return playerNames;

        }
    }
}
void setPosition(vector<player>& players)
{
    bool x_check = true;    //Bool sprawdza czy parametry x zostały prawidłowo wpisane, żeby nie prosić o nie ponownie, gdy
                            //parametry y są nieprawidłowe

    bool showParameters = true;     //Bool pilnuje żeby ostatecznie wybrane parametry zostały pokazane tylko raz

    for(int i = 0;i<players.size();i++)
    {
        showParameters = true;
        if (x_check)
        {
            cout << "Podaj parametr x dla pozycji gracza " << players[i].name << endl;
            cin >> players[i].x;
        }

        if(cinfail())
                i--;

        else if (players[i].x<0 || players[i].x>100)

        {
            cout << "Wybierz x w zakresie 0-100" << endl;
            i--;
        }
        else
        {
            x_check = false;
            cout << "Podaj parametr y dla pozycji gracza " << players[i].name << endl;
            cin >> players[i].y;

            if(cinfail())
                i--;

            else if (players[i].y<0 || players[i].y>100)
            {
                cout << "Wybierz y w zakresie 0-100" << endl;
                i--;
            }
            else
            {
                for(int k = 0;k<i;k++)  //sprawdza czy przypadkiem nie uzyto takich samych parametrow dla dwoch graczy
                {
                    if(players[i].x == players[k].x && players[i].y == players[k].y)
                    {
                        cout << "Podales takie same parametry jakie ma gracz " << players[k].name << "! Wybierz inne." << endl;
                        i--;
                        x_check = true;
                        showParameters = false;
                    }
                }
                if(showParameters)
                {
                    x_check = true;
                }
            }
        }
    }
}

int theGame(vector<player> player)
{
    cout << endl << "Zaczynamy!" << endl;
    for(int i = 0;i<player.size();i++)
    {
        player[i].hp = 2;
        player[i].round = 1;
    }
    int i = 0;
    while(true)
    {
        cout << " Teraz " << player[i].round << " runda gracza " << player[i].name << "." << endl;
        cout << "Wybierz swoją akcję, wpisz \"help\", aby zobaczyć listę akcji" << endl;
        string akcja;
        cin >> akcja;
        if(akcja == "help")
        {
            cout << "\"idz\" - służy do poruszania się o najwyżej 5 jednostek podczas tury." << endl;
            cout << "\"strzel\" - służy do strzelenia w przeciwnika. Strzał spowoduje włączenie skill-checka," << endl
            << " który wylosuje zdarzenie zadane przeciwnikowi." << endl;
        }
        else if(akcja == "idz")
        while(true)
        {
            char answer;
            cout << "Wybierz, w jakiej osi(x/y) chcesz się przesunąć i o ile:" << endl;
            cin >> answer;
            if (cinfail())
            {
                cout << "Wpisałeś coś bardzo złego." << endl;
                break;
            }

            else if(answer == 'y')
            {
                cout << "Podaj, o ile chcesz się przesunąć. Możesz nawet podać wartość na minusie." << endl;
                int answer2;
                cin >> answer2;
                if(positionCheck(player,i))
                    break;
                else if (cinfail())
                {
                    cout << "Miales podać wartość o jaką chciałeś się przesunąć... :0" << endl;
                    break;
                }
                else if(player[i].y + answer2 > 100 || player[i].y + answer2 < 0)
                {
                    cout << "Jeżeli o tyle się posuniesz, wyjdziesz poza granice mapy!!" << endl;
                    break;
                }
                else if(abs(answer2) > 5)
                {
                    cout << "możesz się poruszyć o max 5 jednostek!!" << endl;
                    break;
                }
                else
                {
                    player[i].y += answer2;
                    cout << "Ok, od teraz wartość y to " << player[i].y << "!";
                    if (!(answer2 == 5))
                    {
                        cout << "Chcesz jeszcze przesunąć się w osi x?" << endl << "y/n" << endl;
                        cin >> answer;
                        cout << "Wybrałeś odpowiedź" << answer << endl;
                        if(answer == 'y')
                        {
                            cout << "Podaj, o ile chcesz się przesunąć. Pamiętaj, że podczas tury możesz zrobić max. 5 kroków!" << endl;
                            int answer3;
                            cin >> answer3;
                            if(positionCheck(player,i))
                            {
                                player[i].y -= answer2;
                                break;
                            }
                            else if (cinfail())
                            {
                                cout << "Miales podać wartość o jaką chciałeś się przesunąć... :0" << endl;
                                player[i].y -= answer2;
                                break;
                            }
                            else if(player[i].x + answer3 > 100 || player[i].x + answer3 < 0)
                            {
                                cout << "Jeżeli o tyle się posuniesz, wyjdziesz poza granice mapy!!" << endl;
                                player[i].y -= answer2;
                                break;
                            }
                            else if(abs(answer2+answer3) > 5)
                            {
                                cout << "możesz się poruszyć o max 5 jednostek!!" << endl;
                                player[i].y -= answer2;
                                break;
                            }
                            else
                            {
                                player[i].x += answer3;
                                cout << "Ok, od teraz wartość x to " << player[i].x << "!";
                                player[i].round++;
                            }
                        }
                        else
                        {
                            cout << "dobra, jak chcesz :)" << endl;
                            player[i].round++;
                        }
                    }
                    else
                    {
                        cout << "Jako że nie możesz się już przesunąć, kończysz " << player[i].round << " rundę." << endl;
                        player[i].round++;
                        break;
                    }
                }
            }
            else if(answer == 'x')
            {
                cout << "Podaj, o ile chcesz się przesunąć. Możesz nawet podać wartość na minusie." << endl;
                int answer2;
                cin >> answer2;
                if(positionCheck(player,i))
                    break;
                else if (cinfail())
                {
                    cout << "Miales podać wartość o jaką chciałeś się przesunąć... :0" << endl;
                    break;
                }
                else if(player[i].x + answer2 > 100 || player[i].x + answer2 < 0)
                {
                    cout << "Jeżeli o tyle się posuniesz, wyjdziesz poza granice mapy!!" << endl;
                    break;
                }
                else if(abs(answer2) > 5)
                {
                    cout << "możesz się poruszyć o max 5 jednostek!!" << endl;
                    break;
                }
                else
                {
                    player[i].x += answer2;
                    cout << "Ok, od teraz wartość x to " << player[i].x << "!";
                    if (!(abs(answer2) == 5))
                    {
                        cout << "Chcesz jeszcze przesunąć się w osi y?" << endl << "y/n" << endl;
                        cin >> answer;
                        cout << "Wybrałeś odpowiedź" << answer << endl;
                        if(answer == 'y')
                        {
                            cout << "Podaj, o ile chcesz się przesunąć. Pamiętaj, że podczas tury możesz zrobić max. 5 kroków!" << endl;
                            int answer3;
                            cin >> answer3;
                            if(positionCheck(player,i))
                            {
                                break;
                                player[i].x -= answer2;
                            }
                            else if (cinfail())
                            {
                                cout << "Miales podać wartość o jaką chciałeś się przesunąć... :0" << endl;
                                player[i].x -= answer2;
                                break;
                            }
                            else if(player[i].y + answer3 > 100 || player[i].y + answer3 < 0)
                            {
                                cout << "Jeżeli o tyle się posuniesz, wyjdziesz poza granice mapy!!" << endl;
                                player[i].x -= answer2;
                                break;
                            }
                            else if(abs(answer2)+abs(answer3) > 5)
                            {
                                cout << "możesz się poruszyć o max 5 jednostek!!" << endl;
                                player[i].x -= answer2;
                                break;
                            }
                            else
                            {
                                player[i].x += answer3;
                                cout << "Ok, od teraz wartość y to " << player[i].y << "!";
                                player[i].round++;
                                break;
                            }
                        }
                        else
                        {
                            cout << "Dobra, nie to nie" << endl;
                            player[i].round++;
                            break;
                        }
                    }
                    else
                    {
                        cout << "Jako, że nie możesz się już poruszyć, kończysz rundę." << endl;
                        player[i].round++;
                        break;
                    }
                }
            }
        }
        else if(akcja == "strzel")
        {
            cout << "No, to do kogo chcesz strzelić?" << endl;
            string strzelanyGracz;
            cin >> strzelanyGracz;
            for(int gracz = 0;gracz<player.size();gracz++)
            {
                if(strzelanyGracz==player[i].name)
                {
                    cout << "nie strzelaj w siebie!!" << endl;
                    break;
                }

                else if(strzelanyGracz==player[gracz].name)
                {
                    cout << "Strzelasz w gracza " << player[gracz].name << endl;

                    // tutaj będzie mechanizm wykrywania ścian

                    cout << "Jesteś pewien? Uruchomienie skill-checka nastąpi po wciśnięciu jakiegokolwiek przycisku." << endl;
                    getch();
                    int i = skillCheck();
                    switch(i)
                    {
                    case 0:
                        cout << "nic sie nie stało, " << player[gracz].name << " uniknol." << endl;
                        player[i].round++;
                        break;
                    case 1:
                        cout << "trafiles go w obojczyk!! Zabierasz mu jeden punkt zdrowia!!" << endl;
                        player[gracz].hp -= 1;
                        player[i].round++;
                        break;
                    case 2:
                        cout << "FABER CASTELL!!! FABER CASTELL!!!! ZABIJASZ GO!!!" << endl;
                        player[gracz].hp == 0;
                        player[i].round++;
                        break;
                    }


                }
            }
        }
        else if(akcja == "status")
        {
            cout << endl << "Wyświetlam status wszystkich graczy:" << endl;
            for(int b = 0;b<player.size();b++)
            {
                cout << endl << "Imię: " << player[b].name << endl << "Pozycja x: " << player[b].x << endl;
                cout << "Pozycja y: " << player[b].y << endl << "Hp: " << player[b].hp << endl << "runda: " << player[b].round << endl;
            }
        }
        else
        {
            cout << "cos chyba zle wpisales" << endl;
        }
        if(player[i].round == 3)
        {
            player[i].round = 1;
            i++;
            if(i==player.size())
                i = 0;
        }
    }
}
