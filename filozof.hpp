#ifndef FILOZOF_HPP
#define FILOZOF_HPP
#include <vector>
#include <iostream>
#include <ncurses.h>

#include "widelec.hpp"


class Filozof
{
    private:
    int ID;
    int prawy;
    int lewy;
    Widelec * widelce;
    WINDOW * okno;
    int x;
    int y;
    bool siedzi=false;

    public:
    Filozof(int idneks, int max, Widelec * wid, WINDOW * ok);
    Filozof();
    void jedz();
    void mysl();
    int getID();
    void setx(int a);
    void sety(int b);
    int getx();
    int gety();
    int getPrawy();
    int getLewy();
    void siadz();
    void wstan();
    bool getSiedzi();
};

#endif
