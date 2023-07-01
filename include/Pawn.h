#ifndef Pawn_h
#define Pawn_h

#include "Figure.h"



class Pawn: public Figure{
private:

public:
    Pawn(short, short);
    ~Pawn();
    bool kill(short, short, Board&, vector<Point>, short);
    short getX();
    short getY();
    bool move(Board&, short);
    map<Point, vector<Point>> getKilled();
    vector<Point> getMoves();
    void setNewCoordinates(short, short);
    void clear_killed_and_moves();
};


#endif