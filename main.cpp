#include <iostream>
#include "filozof.hpp"
#include "widelec.hpp"
#include "stol.hpp"

using namespace std;

int main(int argc, char *argv[])
{
    int x = atoi(argv[argc-1]);
    Stol stol(x);
    stol.start();
    return 0;
}