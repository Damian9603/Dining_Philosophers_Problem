#ifndef FILOZOF_HPP
#define FILOZOF_HPP
#include <vector>
#include <iostream>
#include <ncurses.h>

#include "widelec.hpp"


class Filozof
{
    private:
    int ID;             //ID filozofa
    int prawy;          //ID widelca po prawej stronie filozofa
    int lewy;           //ID widelca po lewej stronie filozofa
    Widelec * widelce;  //wskaźnik na tablicę widelców
    WINDOW * okno;      //wskaźnik na okno ncurses
    int x;              //współrzędna filozofa
    int y;              //współrzędna filozofa
    bool siedzi=false;  //argument, w którym przechowywane jest to czy filozof siedzi przy stole
    int stan=-1;         //stan filozofa 0-mysli, 1-czeka, 2-je, -1-stan początkowy

    public:
    Filozof(int idneks, int max, Widelec * wid, WINDOW * ok);
    Filozof();
    void jedz();        //metoda odpowiadająca za jedzenie
    void mysl();        //metoda odpowiadająca za myślenie
    int getID();        //pozyskanie ID filozofa
    void setx(int a);   //ustawienie współrzędnej filozofa
    void sety(int b);   //ustawienie współrzędnej filozofa
    int getx();         //pobranie współrzędnej filozofa
    int gety();         //pobranie współrzędnej filozofa
    int getPrawy();     //pobranie indeksu prawego widelca filozofa
    int getLewy();      //pobranie indeksu lewego widelca filozofa
    void siadz();       //metoda odpowiadająca za siadanie filozofa przy stole
    void wstan();       //metoda odpowiadająca za wstawanie filozofa od stołu
    bool getSiedzi();   //sprawdzenie czy filozof siedzi przy stole
    int getStan();      //sprawdzanie co filozof aktualnie robi
};

#endif
