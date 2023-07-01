#ifndef Board_h
#define Board_h

#include <string>

using namespace std;

class Board
{
private:
    short** board;
public:
    Board();
    Board(string);
    ~Board();
    void display();
    short getFigure(short, short);
    void move(short, short, short, short, short, short);
    void remove(short, short);
};

#endif

