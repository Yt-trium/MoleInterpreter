#ifndef MOLE_H
#define MOLE_H

#include <iostream>
#include <fstream>
#include <vector>
#include <stack>

#include "struct.h"

using namespace std;

class Mole
{
    public:
        Mole();
        virtual ~Mole();
        void setSrcFile(string filename);
        void showSrc();
        int load();
        int run();
        int debug();

    protected:

    private:
        stack<int> stack;
        string filename;
        vector<vector<vector<char> > > src;
        int size_x, size_y, size_z;
        int step();

        point cursor;
        Direction direction;
        Mode mode;
};

#endif // MOLE_H
