#include "stol.hpp"
#include <vector>
#include <unistd.h>
#include <ncurses.h>
#include <sys/ioctl.h>
#include <termios.h>
//flaga końca wątku
bool endFlag=false;

//funkcja wątków
void Fil(Filozof * fil)
{
    while(endFlag==false)
    {
        fil->mysl();
        fil->jedz();
    }
    fil->wstan();
}


Stol::Stol(int ilosc)
{
    //inicjalizacja okna ncurses
    okno=initscr();
    //tworzenie widelcow i przypisywanie im ID
    widelce=new Widelec[ilosc];
    for (int i=0; i<ilosc; i++)
    {
        widelce[i].setID(i);
    }
    //tworzenie filozofów o kolejnych ID
    filozofowie.resize(ilosc);
    for(int i=0; i<ilosc; i++)
    {
        Filozof filozof(i, ilosc, widelce, okno);
        filozofowie[i]=filozof;
    }

    il=ilosc;
    start_color();
    //inicjalizacja kolorów w oknie
    init_pair(1, COLOR_YELLOW, COLOR_BLACK);
    init_pair(2, COLOR_CYAN, COLOR_BLACK);
    init_pair( 3, COLOR_RED, COLOR_BLACK );
    init_pair(4, COLOR_GREEN, COLOR_BLACK);

}

Stol::~Stol()
{
}



void Stol::start()
{
    //wyswietlenie stanu poczatkowego stolu
    przygotuj();
    wyswietl();
    rysuj();
    sleep(1);
    //tworzenie watkow
    for (int i=0; i<il; i++)
    {
		Filozof * fil;
		fil= &(filozofowie[i]);	
		watkiFilozofow.push_back(std::thread(Fil, fil));
	}
    //wyswietlanie w petli stanu widelcow i filozofow
    bool koniec = false;
    while (koniec!=true)
    {
        usleep(100000);
        clear();
        wyswietl();
        rysuj();
        refresh();
        if(kbhit())
        {
           koniec=true;
        }
    }
    endFlag=true;
    //wyswietlanie w petli stanu widelcow i filozofow (konczenie pracy watkow i odchodzenie od stolu)
    int kon=75;
    for (int i=0; i<kon; i++)
    {
        clear();
        wyswietl();
        rysuj();
        refresh();
        usleep(300000);
    }
    //czekanie na zakonczenie wszystkich watkow
    for (int i=0; i<il; i++)
    {
        watkiFilozofow[i].join();
    }
    //zamkniecie okna ncurses
    endwin();
    
    
}

void Stol::przygotuj()
{
    //metoda przypisujaca wspolrzedne siedzenia filozofow oraz wspolrzedne widelcow,
    //gdy nie sa przez nikogo uzywane
    int fizxbok=il/4;
    int reszta=il%4;
    int bok[4];
    switch (reszta)
    {
    case 0:
        bok[0]=fizxbok;
        bok[1]=fizxbok;
        bok[2]=fizxbok;
        bok[3]=fizxbok;
        break;
    case 1:
        bok[0]=fizxbok+1;
        bok[1]=fizxbok;
        bok[2]=fizxbok;
        bok[3]=fizxbok;
        break;
    case 2:
        bok[0]=fizxbok+1;
        bok[1]=fizxbok;
        bok[2]=fizxbok+1;
        bok[3]=fizxbok;
        break;
    case 3:
        bok[0]=fizxbok+1;
        bok[1]=fizxbok+1;
        bok[2]=fizxbok+1;
        bok[3]=fizxbok;
        break;
    }
    int pozycja;
    int liczba=0;
    if(bok[0]>1)
    {
        pozycja = 15/(bok[0]);
    }
    else
    {
        pozycja = 10;
    }
    
    for(int i=0; i<bok[0];i++)
    {
        filozofowie[liczba].setx(9);
        filozofowie[liczba].sety(9+pozycja*(i+1));
        widelce[liczba].setx(11);
        widelce[liczba].sety(11+pozycja*(i+1));
        liczba++;
    }

    if(bok[1]>1)
    {
        pozycja = 10/(bok[1])-1;
    }
    else
    {
        pozycja = 6;
    }

    for(int i=0; i<bok[1];i++)
    {
        filozofowie[liczba].setx(9+pozycja*(i+1));
        filozofowie[liczba].sety(31);
        widelce[liczba].setx(10+pozycja*(i+1));
        widelce[liczba].sety(26);
        liczba++;
    }



    if(bok[2]>1)
    {
        pozycja = 15/(bok[2]);
    }
    else
    {
        pozycja = 10;
    }

    for(int i=0; i<bok[2];i++)
    {
        filozofowie[liczba].setx(21);
        filozofowie[liczba].sety(31-pozycja*(i+1));
        widelce[liczba].setx(18);
        widelce[liczba].sety(29-pozycja*(i+1));
        liczba++;
    }


    if(bok[3]>1)
    {
        pozycja = 10/(bok[3])-1;
    }
    else
    {
        pozycja = 6;
    }

    for(int i=0; i<bok[3];i++)
    {
        
        filozofowie[liczba].setx(21-pozycja*(i+1));
        filozofowie[liczba].sety(9);
        widelce[liczba].setx(19-pozycja*(i+1));
        widelce[liczba].sety(11);
        liczba++;
    }
}

void Stol::wyswietl()
{
#pragma region info
    mvprintw(0,0,"Wizualizacja problemu ucztujacych filozofow");
    mvprintw(1,0,"Metoda hierarchii zasobów");
    mvprintw(2,0, "Filozof siedzacy przy stole: ");
    attron( COLOR_PAIR( 3 ) );
    attron( A_BOLD );
    printw("o");
    attroff(COLOR_PAIR(3));
    attroff( A_BOLD);

    mvprintw(3,0,"Stany Filozofow: ");
    attron( COLOR_PAIR( 4) );
    attron( A_BOLD);
    printw("?");
    attroff( A_BOLD);
    attroff(COLOR_PAIR(4));
    printw(" - mysli, ");
    attron( COLOR_PAIR( 4) );
    attron( A_BOLD);
    printw(".");
    attroff( A_BOLD);
    attroff(COLOR_PAIR(4));
    printw(" - czeka, ");
    attron( COLOR_PAIR( 4) );
    attron( A_BOLD);
    printw("!");
    attroff( A_BOLD);
    attroff(COLOR_PAIR(4));
    printw(" - je");
    

    mvprintw(4,0, "Widelec nieuzywany: ");
    attron( COLOR_PAIR( 1 ) );
    printw("___");
    attroff(COLOR_PAIR(1));
    mvprintw(5,0, "Widelec uzywany: ");
    attron( COLOR_PAIR( 2 ) );
    printw("___");
    attroff(COLOR_PAIR(2));
    mvprintw(6,0, "Zakonczenie po nacisnieciu dowolnego klawisza");
#pragma endregion
#pragma region wyswietlanie stolu
    char pion[] = "|";
    char poziom[] ="_";
    for(int i=10;i<20;i++)
    {
        mvprintw( i, 10 , pion );
        mvprintw( i, 29 , pion );
    }
    for(int i=10;i<30;i++)
    {
        mvprintw(10, i, poziom);
        mvprintw(20, i, poziom);
    }
#pragma endregion

#pragma region wyswietlanie filozofow
    
    attron( A_BOLD );
    
    
    for (int i=0; i<il; i++)
    {
        if(filozofowie[i].getSiedzi())
        {
            attron( COLOR_PAIR( 3 ) );
            int x= filozofowie[i].getx();
            int y=filozofowie[i].gety();
            mvprintw(x, y, "o");
            attroff( COLOR_PAIR( 3 ) );
            attron( COLOR_PAIR( 4 ) );
            if(x!=21)
            {
                
                if(filozofowie[i].getStan()==0)
                {
                    mvprintw(x-1,y,"?");
                }
                else if(filozofowie[i].getStan()==1)
                {
                    mvprintw(x-1,y,".");
                }
                else if(filozofowie[i].getStan()==2)
                {
                    mvprintw(x-1,y,"!");
                }
                
            }
            else
            {
                if(filozofowie[i].getStan()==0)
                {
                    mvprintw(x+1,y,"?");
                }
                else if(filozofowie[i].getStan()==1)
                {
                    mvprintw(x+1,y,".");
                }
                else if(filozofowie[i].getStan()==2)
                {
                    mvprintw(x+1,y,"!");
                }
            }
            attroff(COLOR_PAIR(4));
            
        }
        else
        {
            mvprintw(filozofowie[i].getx(), filozofowie[i].gety(), " ");
        }
        
    }
    
    attroff(A_BOLD);
#pragma endregion
}


void Stol::rysuj()
{
    //metoda wyswietlajaca widelce
    char pion[]="|";
    char poziom[]="___";
    char pustypion[]=" ";
    char pustypoziom[]="   ";
    for(int i=0; i<il; i++)
    {
        int fil=widelce[i].getFil();
        //gdy widelec nie jest trzymany przez zadnego z filozofow
        if(fil==-1)
        {
            int x=widelce[i].getx();
            int y=widelce[i].gety();
            attron( COLOR_PAIR( 1 ) );
            if((x==11||x==18)&&(y!=26&&y!=11))
            {
                mvprintw(x,y,pion);
                mvprintw(x+1,y,pion);
            }
            else
            {
                mvprintw(x,y,poziom);
            }
            attroff( COLOR_PAIR( 1 ) );
            
        }
        //gdy widelec jest trzymany przez filozofa
        else
        {
            attron( COLOR_PAIR( 2 ) );
            int x;
            int y;
            x=filozofowie[fil].getx();
            y=filozofowie[fil].gety();
            if(filozofowie[fil].getLewy()==i)
            {
                if(x==9)
                {
                    mvprintw(x+2,y+1,pion);
                    mvprintw(x+3,y+1,pion);
                }
                else if(y == 31)
                {
                    mvprintw(x+1,y-5,poziom);
                }
                else if(x==21)
                {
                    mvprintw(x-2,y-1,pion);
                    mvprintw(x-3,y-1,pion);
                }
                else
                {
                    mvprintw(x-1,y+2,poziom);
                }
                
            }
            else
            {
                if(x==9)
                {
                    mvprintw(x+2,y-1,pion);
                    mvprintw(x+3,y-1,pion);
                }
                else if(y == 31)
                {
                    mvprintw(x-1,y-5,poziom);
                }
                else if(x==21)
                {
                    mvprintw(x-2,y+1,pion);
                    mvprintw(x-3,y+1,pion);
                }
                else
                {
                    mvprintw(x+1,y+2,poziom);
                }
            }
            attroff(COLOR_PAIR(2));
            
        }
        
    }
}

bool Stol::kbhit()
{
    int w;
    ioctl(0, 0x541B, &w);
    return w > 0;
}