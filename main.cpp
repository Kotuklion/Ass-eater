#include <iostream>
#include <string>

using namespace std;

int main()
{
    cout << "Witamy w Faber Castell! Dziekujemy za wybranie naszej marki." << endl;

    // Wybór liczby graczy i ich imion
    bool wyborImion = true;
    while(wyborImion)
    {
        cout << "Prosze o wybranie liczby graczy." << endl;
        int liczbaGraczy = 0;
        while(liczbaGraczy<=1)       //Wybór liczby graczy
        {
          cin >> liczbaGraczy;
          if(liczbaGraczy<=1)
          {
              cout << "Liczba graczy nie moze byc mniejsza niz 1! Sprobuj znowu." << endl;
          }
        }
        string *imionaGraczy = new string[liczbaGraczy];
        for(int i = 0;i<liczbaGraczy;i++)
        {
            cout << endl << "Podaj imie dla gracza nr. " << i+1 << endl;
            cin >> imionaGraczy[i];
        }
        //Sprawdzenie poprawnoœci danych
        cout << "Czy jestes pewien, ze w rozgrywce ma brac udzial " << liczbaGraczy << " graczy";
        for(int i = 0;i<liczbaGraczy;i++)
        {
            if(i+1==liczbaGraczy)
            {
              cout << " i " << imionaGraczy[i] << "? y/n" << endl;
            }
            else
            {
                cout << ", " << imionaGraczy[i];
            }
        }
        char odpowiedz;
        cin >> odpowiedz;
        if(odpowiedz=='y')
        {
            wyborImion = false;
        }
    }

    cout << "Wraz z wyborem graczy możemy przejść do rozgrywki. Aby wygrać, należy zabić pozostałych graczy." << endl;
    cout << "Gra toczona jest na losowo generowanej dwuwymiarowej planszy 100x100." << endl;    //jeszcze nie zrobione
    cout << ""


}
