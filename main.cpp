#include <iostream>

#include "Mole.h"

using namespace std;

int main()
{
    cout << "Mole Interpreter 1.0" << endl;

    Mole *m = new Mole();
    m->setSrcFile("examples/helloworld.mole");

    // Load and Run
    m->load();
    m->showSrc();
    m->run();

    return 0;
}
