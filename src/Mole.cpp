#include "Mole.h"

Mole::Mole()
{
    //ctor
}

Mole::~Mole()
{
    //dtor
}

void Mole::setSrcFile(string filename)
{
    this->filename = filename;
}

void Mole::showSrc()
{
    int x,y,z;

    for(x=0;x<size_x+2;x++)
        cout << '*';
    cout << endl;

    for(z=0;z<size_z;z++)
    {
        for(y=0;y<size_y;y++)
        {
            cout << '*';
            for(x=0;x<size_x;x++)
            {
                cout << src[x][y][z];
            }
            cout << '*';
            cout << endl;
        }
        for(x=0;x<size_x+2;x++)
            cout << '*';
        cout << endl;
    }
}

int Mole::load()
{
    ifstream  file(filename.c_str());
    int x,y,z,i,j;
    string l;

    file >> size_x;
    file >> size_y;
    file >> size_z;

    src.resize(size_x);
    for (i = 0; i < size_x; ++i)
    {
        src[i].resize(size_y);

        for (j = 0; j < size_y; ++j)
            src[i][j].resize(size_z);
    }

    x = 0;
    y = 0;
    z = 0;

    getline(file, l);

    for(z=0;z<size_z;z++)
    {
        for(y=0;y<size_y;y++)
        {
            getline(file, l);

            for(x=0;x<size_x;x++)
            {
                src[x][y][z] = l[x];
            }
        }
        getline(file, l);
    }


    file.close();
    return 0;
}

int Mole::step()
{
    char now;
    int arg1, arg2;
    int l = 1;
    now = src[cursor.x][cursor.y][cursor.z];

    if(mode == STRING && now != '"')
        stack.push((int)now);
    else
    {
    switch(now)
    {
        // Direction
        case '^':
            direction = N;
        break;
        case 'v':
            direction = S;
        break;
        case '>':
            direction = E;
        break;
        case '<':
            direction = W;
        break;
        case 'H':
            direction = U;
        break;
        case 'o':
            direction = D;
        break;

        // Condition
        case '_':
            arg1 = stack.top();
            stack.pop();
            if(arg1 == 0)
                direction = E;
            else
                direction = W;
        break;
        case '|':
            arg1 = stack.top();
            stack.pop();
            if(arg1 == 0)
                direction = S;
            else
                direction = N;
        break;
        case 'O':
            arg1 = stack.top();
            stack.pop();
            if(arg1 == 0)
                direction = D;
            else
                direction = U;
        break;

        // Push
        case '0':
            stack.push(0);
        break;
        case '1':
            stack.push(1);
        break;
        case '2':
            stack.push(2);
        break;
        case '3':
            stack.push(3);
        break;
        case '4':
            stack.push(4);
        break;
        case '5':
            stack.push(5);
        break;
        case '6':
            stack.push(6);
        break;
        case '7':
            stack.push(7);
        break;
        case '8':
            stack.push(8);
        break;
        case '9':
            stack.push(9);
        break;

        // Special
        case '"':
        if(mode == STRING)
            mode = NORMAL;
        else
            mode = STRING;
        break;

        case ':':
            stack.push(stack.top());
        break;

        case '#':   // TODO : Jump with length
            l = 2;
        break;

        case ',':
            cout << (char)stack.top();
            stack.pop();
        break;

        case '@':       // END
            return 42;
        break;

        case ' ':

        break;

        default:        // Unknown
                return 100;
        break;
    }
    }

    switch(direction)
    {
        case N:
            cursor.y-=l;
        break;
        case S:
            cursor.y+=l;
        break;
        case E:
            cursor.x+=l;
        break;
        case W:
            cursor.x-=l;
        break;
        case U:
            cursor.z-=l;
        break;
        case D:
            cursor.z+=l;
        break;
    }

    if(   cursor.x < 0 || cursor.x > size_x
       || cursor.y < 0 || cursor.y > size_y
       || cursor.z < 0 || cursor.z > size_z)
        return 1;   // OUT OF SOURCE

    return 0;
}

int Mole::run()
{
    cursor.x = 0;
    cursor.y = 0;
    cursor.z = 0;
    direction = N;
    mode = NORMAL;

    int s;

    while((s = step()) == 0)
    {

    }

    if(s == 42)
        return 0;
    else
        return 1;
}

int Mole::debug()
{
    cursor.x = 0;
    cursor.y = 0;
    cursor.z = 0;
    direction = N;
    mode = NORMAL;

    int s;

    while((s = step()) == 0)
    {
        cout << "return code : " << s << endl;
        cout << "source code : " << src[cursor.x][cursor.y][cursor.z] << endl;
        cout << "x           : " << cursor.x << endl;
        cout << "y           : " << cursor.y << endl;
        cout << "z           : " << cursor.z << endl;
        cout << "direction   : " << direction << endl;
        cout << "mode        : " << mode << endl;
        cout << "--------------------------------------------------" << endl;
    }
    cout << "END OF DEBUG" << endl;
}
