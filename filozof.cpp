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
    //pierwszym zajmowanym widelcem jest widelec z mniejszym ID
#pragma region zajmowanie widelcow
    if(lewy<prawy)
    {
        widelce[lewy].zajmij(ID);
    }
    else
    {
        widelce[prawy].zajmij(ID);
    }
    //czas podnoszenia widelca 0.5s-0.6s
    int random= rand()%10000;
    float czas = 500000+10*random;
    usleep(czas);
    if(lewy>prawy)
    {
        widelce[lewy].zajmij(ID);
    }
    else
    {
        widelce[prawy].zajmij(ID);
    }
    
    //czas podnoszenia widelca 0.5s-0.6s
    random= rand()%10000;
    czas = 500000+10*random;
    usleep(czas);

#pragma endregion

#pragma region jedzenie
    //czas jedzenia 2s-3s
    random=rand()%10000;
    czas = 2000000+(100*random);
    usleep(czas);
#pragma endregion
    //pierwszym zwalnianym widelcem jest widelec z większym ID
#pragma region zwalnianie widelcow
    if(lewy<prawy)
    {
        widelce[prawy].zwolnij();
    }
    else
    {
        widelce[lewy].zwolnij();
    }
    //czas odkładania widelca 0.4s-0.5s
    random= rand()%10000;
    czas = 400000+10*random;
    usleep(czas);
    if(lewy<prawy)
    {
        widelce[lewy].zwolnij();
    }
    else
    {
        widelce[prawy].zwolnij();
    }
    //czas odkładania widelca 0.4s-0.5s
    random= rand()%10000;
    czas = 400000+10*random;
    usleep(czas);
#pragma endregion

}

void Filozof::mysl()
{
    //czas myslenia 5s-6s
    int random=rand()%10000;
    int czas = 5000000+(100*random);
    usleep(czas);
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