#ifndef WIDELEC_HPP
#define WIDELEC_HPP

#include <mutex>

class Widelec
{
    private:
    int ID;             //id widelca
    int fil=-1;         //filozof korzystajacy z widelca (gdy rowne -1 nikt z niego nie korzysta)
    std::mutex mut;     //mutex widelca
    int x;              //współrzędna widelca
    int y;              //współrzędna widelca

    public:
    Widelec();
    Widelec(int indeks);
    void setFil(int f);         //ustawienie ID filozofa, który aktualnie korzysta z widelca
    int getFil();               //pozyskanie ID filozofa, który aktualnie korzysta z widelca
    void zajmij(int filozof);   //zajecie widelca
    void zwolnij();             //zwolnienie widelca
    void setx(int a);           //ustawienie wpółrzędnej widelca
    void sety(int b);           //ustawienie wpółrzędnej widelca
    int getx();                 //pozyskanie wpółrzędnej widelca
    int gety();                 //pozyskanie wpółrzędnej widelca
    void setID(int d);          //ustawienie ID widelca

};

#endif