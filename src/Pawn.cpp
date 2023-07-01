#include "../include/Pawn.h"
#include "../include/Board.h"
#include <vector>
#include <algorithm>

using namespace std;

Pawn::Pawn(short x, short y)
{
    point.x = x;
    point.y = y;
    oppPawnSymbol = 3;
    oppQueenSymbol = 5;
}
Pawn::~Pawn(){}

bool operator<(const Point& l, const Point& r) {
     return (l.x<r.x || (l.x==r.x && l.y<r.y));
}
bool operator==(const Point& l, const Point& r)
{
    return (l.x == r.x && l.y == r.y);
}

short Pawn::getX()
{
    return point.x;
}
short Pawn::getY()
{
    return point.y;
}

bool Pawn::move(Board& b, short vertical_direction)
{
    for(int j =-1; j<=1; j+=2)
    {
        if(b.getFigure(point.x + vertical_direction, point.y + j) == 1)
        {
            Point p;
            p.x = point.x + vertical_direction;
            p.y = point.y + j;
            moves.push_back(p);
        }
            
    }
    return true;
}
bool Pawn::kill(short offX, short offY, Board &b, vector<Point> prev, short myPawn)
{
    short licznik = 0;
    for(int i = -1;i<=1;i+=2)
    {
        for(int j =-1; j<=1; j+=2)
        {
            if(b.getFigure(point.x + offX + i, point.y + offY + j) == 5-myPawn ||
                b.getFigure(point.x + offX + i, point.y + offY + j) == 7-myPawn)
                {
                    if(b.getFigure(point.x + offX + 2*i, point.y + offY + 2*j) == 1)
                    {
                        Point k;//polozenie piona przeciwnika do zbicia
                        k.x = point.x + offX + i;
                        k.y = point.y + offY + j;
                        if ( find(prev.begin(), prev.end(), k) != prev.end() ) continue;//wyklueczenie cyklicznego bicia tego samego piona
                        vector <Point> v = prev;
                        v.push_back(k);
                        licznik += 1;
                        if(this->kill(2*i+offX, 2*j+offY, b, v, myPawn))//czy po wykonaniu tego bicia mozna bedzie dalej bic true- jesli nie
                        {//nie mozna dalej bic
                            Point p;//polozenie wlasnego piona po wykonaniu wszytskihc obowiazkowyc bic
                            p.x = point.x + offX + 2*i;
                            p.y = point.y + offY + 2*j;
                            killed.insert(pair <Point, vector<Point>>(p, v));//wstawienie do mapy swojego polozenia po biciu
                        }//                                                    oraz poloznia wszytskich zbitych pionów(w wektorze)
                    }
                }
        }
    }
    if(licznik == 0) return true;
    return false;
}

vector<Point> Pawn::getMoves()
{
    return moves;
}
map<Point, vector<Point>> Pawn::getKilled()
{
    return killed;
}

void Pawn::setNewCoordinates(short x, short y)
{
    if(x<8 && x >=0 && y<8 && y>=0)
    {
        point.x = x;
        point.y = y;
    }
}

void Pawn::clear_killed_and_moves()
{
    killed.clear();
    moves.clear();
}