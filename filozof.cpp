#include <pthread.h>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <unistd.h>

#include "filozof.hpp"
#include "widelec.hpp"


Filozof::Filozof()
{
    ID=-1;
}

Filozof::Filozof(int indeks, int max, Widelec * wid, WINDOW * ok )
{
    ID=indeks;
    lewy=indeks;
    widelce=wid;
    okno=ok;
    if(indeks>0)
    {
        prawy=indeks-1;
    }
    else
    {
        prawy=max-1;
    }
    siadz();
    
}

void Filozof::jedz()
{
#pragma region zajmowanie widelcow
    if(lewy<prawy)
    {
        widelce[lewy].zajmij(ID);
    }
    else
    {
        widelce[prawy].zajmij(ID);
    }
    int random= rand()%100;
    float czas = 500000+random;
    usleep(czas);
    if(lewy>prawy)
    {
        widelce[lewy].zajmij(ID);
    }
    else
    {
        widelce[prawy].zajmij(ID);
    }
    

    random= rand()%100;
    czas = 500000+random;
    usleep(czas);

#pragma endregion

#pragma region jedzenie
    random=rand()%20000;
    czas = 2+(0.0001*random);
    sleep(czas);
#pragma endregion

#pragma region zwalnianie widelcow
    if(lewy<prawy)
    {
        widelce[prawy].zwolnij();
    }
    else
    {
        widelce[lewy].zwolnij();
    }
    random= rand()%100;
    czas = 500000+random;
    usleep(czas);
    if(lewy<prawy)
    {
        widelce[lewy].zwolnij();
    }
    else
    {
        widelce[prawy].zwolnij();
    }
    random= rand()%100;
    czas = 500000+random;
    usleep(czas);
#pragma endregion

}

void Filozof::mysl()
{
    int random=rand()%20000;
    float czas = 5+(0.0001*random);
    sleep(czas);
}

int Filozof::getID()
{
    return ID;
}

void Filozof::setx(int a)
{
    x=a;
}

void Filozof::sety(int b)
{
    y=b;
}

int Filozof::getx()
{
    return x;
}

int Filozof::gety()
{
    return y;
}

int Filozof::getPrawy()
{
    return prawy;
}

int Filozof::getLewy()
{
    return lewy;
}

void Filozof::siadz()
{
    siedzi=true;
}

void Filozof::wstan()
{
    siedzi=false;
}

bool Filozof::getSiedzi()
{
    return siedzi;
}