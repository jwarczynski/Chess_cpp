#include "../include/Queen.h"
#include "../include/Pawn.h"
#include "../include/Board.h"
#include <map>
#include <algorithm>

Queen::Queen(short x, short y)
{
    point.x = x;
    point.y = y;
    oppPawnSymbol = 3;
    oppQueenSymbol = 5;
    myPawnSymbol = 2;
    myQueenSymbol = 4;
}
Queen::~Queen(){}

short Queen::getX()
{
    return point.x;
}
short Queen::getY()
{
    return point.y;
}

map <Point, vector<Point>> Queen::getKilled()
{
    return killed;
}
vector<Point> Queen::getMoves()
{
    return moves;
}

bool Queen::move(Board &b, short not_used)
{
    for(short ver_dir = -1; ver_dir < 2; ver_dir +=2)
    {
        for(short hor_dir = -1; hor_dir < 2; hor_dir +=2)
        {   
            for(short i = 1; i<8; i++)
            {
                if( b.getFigure(point.x + i*ver_dir, point.y + i*hor_dir) != 1) break;
                Point p;
                p.x = point.x + i*ver_dir;
                p.y = point.y + i*hor_dir;
                moves.push_back(p);
            }
        }
    }
    return true;
}
bool Queen::kill(short offX, short offY, Board &b, vector<Point> prev, short myPawn)
{
    bool end = true;
    for(int vertical_direction = -1; vertical_direction<2; vertical_direction+=2)
    {
        for(int horizontal_direction = -1; horizontal_direction<2; horizontal_direction+=2)
        {
            for(int counter = 1; counter<8; counter++)
            {
                if( b.getFigure(point.x + offX + counter*vertical_direction,
                    point.y + offY + counter*horizontal_direction) == myPawn ||
                    b.getFigure(point.x + offX + counter*vertical_direction,
                    point.y + offY + counter*horizontal_direction) == myPawn + 2)
                        break;
                if (b.getFigure(point.x + offX + counter*vertical_direction,
                    point.y + offY + counter*horizontal_direction) == -1)
                        break;
                if( b.getFigure(point.x + offX + counter*vertical_direction,
                    point.y + offY + counter*horizontal_direction) == 5-myPawn ||
                    b.getFigure(point.x + offX + counter*vertical_direction,
                    point.y + offY + counter*horizontal_direction) == 7-myPawn)
                    {
                        for(int l = 1; l<8-counter;l++)
                        {
                            if( b.getFigure(point.x + offX + (counter+l)*vertical_direction,
                                point.y + offY + (counter+l)*horizontal_direction) != 1 )
                                    break;
                            Point p;
                            p.x = point.x + offX + counter*vertical_direction;
                            p.y = point.y + offY + counter*horizontal_direction;
                            if ( find(prev.begin(), prev.end(), p) != prev.end() ) continue;
                            vector<Point> zbite = prev;
                            zbite.push_back(p);
                            end = false;
                            if( this->kill( /*point.x +*/ offX + (counter+l)*vertical_direction,
                                /*point.y +*/ offY + (counter+l)*horizontal_direction, b, zbite, myPawn) )
                                {
                                    Point k;
                                    k.x = point.x + offX + (counter+l)*vertical_direction;
                                    k.y = point.y + offY + (counter+l)*horizontal_direction;
                                    killed.insert(pair <Point, vector<Point>>(k, zbite));
                                }
                        }
                        counter = 8;
                    }
            }
        }
    }
    return end;
}

void Queen::setNewCoordinates(short x, short y)
{
    if(x<8 && x >=0 && y<8 && y>=0)
    {
        point.x = x;
        point.y = y;
    }
}

void Queen::clear_killed_and_moves()
{
    killed.clear();
    moves.clear();
}