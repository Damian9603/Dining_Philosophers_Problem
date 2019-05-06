#ifndef STOL_HPP
#define STOL_HPP
#include <vector>
#include <thread>

#include "filozof.hpp"
#include "widelec.hpp"



class Stol
{
private:
    
    std::vector<Filozof> filozofowie;           //wektor filozofów
    std::vector<std::thread> watkiFilozofow;    //wektor wątków
    Widelec * widelce;                          //wskaźnik na tablicę widelców
    WINDOW * okno;                              //aktualne okno ncurses
    int il;                                     //liczba filozofów przy stole
    void przygotuj();                           //metoda wpisująca współrzędne filozofom i widelcom
    void wyswietl();                            //wyświetlanie stołu i filozofów
    void rysuj();                               //wyświetlanie widelców
    bool kbhit();                               //funkcja sprawdzająca czy naciśnięto klawisz
public:
    
    Stol(int ilosc);
    ~Stol();
    void start();                               //rozpoczęcia działania stołu


};

#endif