#ifndef WIDELEC_HPP
#define WIDELEC_HPP

#include <semaphore.h>
#include <mutex>

class Widelec
{
    private:
    int ID;
    int fil=-1;
    std::mutex mut;
    int x;
    int y;

    public:
    Widelec();
    Widelec(int indeks);
    void setFil(int f);
    int getFil();
    void zajmij(int filozof);
    void zwolnij();
    void setx(int a);
    void sety(int b);
    int getx();
    int gety();
    void setID(int d);

};

#endif