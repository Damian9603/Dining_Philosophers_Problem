#include "widelec.hpp"
#include <iostream>


Widelec::Widelec()
{
    ID=-1;
}
Widelec::Widelec(int indeks)
{
    ID=indeks;
}


void Widelec::setFil(int f)
{
    f=fil;
}

int Widelec::getFil()
{
    return fil;
}

void Widelec::zwolnij()
{
    fil=-1;
    mut.unlock();
}

void Widelec::zajmij(int filozof)
{
    mut.lock();
    fil=filozof;
}

void Widelec::setx(int a)
{
    x=a;
}

void Widelec::sety(int b)
{
    y=b;
}

int Widelec::getx()
{
    return x;
}

int Widelec::gety()
{
    return y;
}

void Widelec::setID(int d)
{
    ID=d;
}