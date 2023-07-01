#ifndef Figure_h
#define Figure_h

#include <map>
#include <vector>

class Board;

using namespace std;

struct Point
{
    short x, y;
};

bool operator<(const Point& l, const Point& r);
bool operator==(const Point& l, const Point& r);

class Player;

class Figure
{
protected:
    short oppPawnSymbol;
    short oppQueenSymbol;
    short myPawnSymbol;
    short myQueenSymbol;
    struct Point point;
    map <Point, vector<Point>> killed;
    vector <Point> moves;  
public:
    //virtual Figure() = 0;
    virtual bool kill(short, short, Board& , vector<Point>, short) = 0;
    virtual bool move(Board&, short) = 0;
    virtual short getX() = 0;
    virtual map<Point, vector<Point>> getKilled() = 0;
    virtual vector<Point> getMoves() = 0;
    virtual short getY() = 0;
    virtual void setNewCoordinates(short, short) = 0;
    virtual void clear_killed_and_moves() = 0;
    //virtual ~Figure();
};

#endif