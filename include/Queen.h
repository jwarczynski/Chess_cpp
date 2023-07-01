#ifndef Queen_h
#define Queen_h

#include "Figure.h"


class Queen: public Figure
{
private:

public:
    Queen(short, short);
    ~Queen();
    bool kill(short, short, Board& , vector<Point>, short);
    bool move(Board&, short);

    short getX();
    short getY();

    void setNewCoordinates(short, short);

    map<Point, vector<Point>> getKilled();
    vector<Point> getMoves();

    void clear_killed_and_moves();
};

#endif