#include "../include/Player.h"
#include "../include/Pawn.h"
#include "../include/Queen.h"
#include "../include/Board.h"
#include <algorithm>
#include <iostream>

using namespace std;

Player::Player(Board &b, short symbol, short direction)
{
    myPawnSymbol = symbol;
    myQueenSymbol = symbol + 2;
    oppPawnSymbol = 5-symbol;
    oppQueenSymbol = 7-symbol;
    move_direction = direction;
    for(short i = 0;i<8;i++)
    {
        for(short j = 0;j<8;j++)
        {
            if(b.getFigure(i, j) == myPawnSymbol)
            {
                figures_vector.push_back(new Pawn(i, j));
            }
            if(b.getFigure(i, j) == myQueenSymbol)
            {
                figures_vector.push_back(new Queen(i, j));
            }

        }
    }
}

void Player::compute_possible_kills(Board &b)
{
    for(auto &i: figures_vector)
    {
        vector<Point> v;
        i->kill(0,0,b,v, myPawnSymbol);
        map<Point, vector<Point>> u =  i->getKilled();
        if(!u.empty())
        {
        Point p;
        p.x = i->getX();
        p.y = i->getY();
        possible_kills[p] = u;
        //possible_kills.insert(p, i->getKilled());
        }
    }
}
void Player::compute_possible_moves(Board &b)
{
    for(auto &i: figures_vector)
    {
        vector<Point> u;
        i->move(b, move_direction);
        u = i->getMoves();
        if(u.empty()) continue;
        Point p;
        p.x = i->getX();
        p.y = i->getY();
        possible_moves[p] = u;
    }
    
}

void Player::show_possible_kills()
{
    for(auto &el: possible_kills)
    {
        // cout<<"na pole ";
        for(auto it = el.second.begin();it != el.second.end();++it)
        {
            // if(next(it) != el.second.end())
                cout<<"pionkiem ("<<el.first.x<<","<<el.first.y<<") -> ";
                cout<<"("<<(*it).first.x<<","<<(*it).first.y<<") zbite -> [(";
                for(auto zbite = (*it).second.begin(); zbite != (*it).second.end(); ++zbite)
                {
                    if(next(zbite) != (*it).second.end())
                        cout<<(*zbite).x<<","<<(*zbite).y<<"), (";
                    else
                        cout<<(*zbite).x<<","<<(*zbite).y<<")]\n";
                }
/*             else
            {
                cout<<(*it).first.x<<","<<(*it).first.y<<")]\n";
                cout<<"zbite pionki -> [( "<<;
            }
 *//*                 
            for(auto &el3: el2.second)
            {
                cout<<el3.x<<el3.y<<"\t";
            }
            cout<<endl;
 */
        }
    }
}
void Player::show_possible_moves()
{
    for(auto &el: possible_moves)
    {
        cout<<"pionkiem ("<<el.first.x<<","<<el.first.y<<") -> [(";
        // cout<<"na pole ";
        for(auto it = el.second.begin();it!=el.second.end(); ++it)
        {
            if(it != el.second.end()-1)
                cout<<(*it).x<<","<<(*it).y<<"), (";
            else
                cout<<(*it).x<<","<<(*it).y<<")]\n";

        }
    }
}

bool Player::read_move(Board &b, Player &plr, short x1, short y1, short x2, short y2)
{
    Point p1 = {x1,y1};
    Point p2 = {x2,y2};
    auto it = possible_kills.find(p1);
    if(it == possible_kills.end())
    {
        if( !possible_kills.empty() )
        {
            cout<<"musisz bić"<<endl;
            return false;
        }
        auto mv = possible_moves.find(p1);
        if(mv == possible_moves.end() || possible_moves.empty())
        {
            cout<<"nie dozwolony ruch"<<endl;
            return false;
        }
        auto dest = find(mv->second.begin(), mv->second.end(), p2);
        if(dest == mv->second.end())
        {
            cout<<"nie możesz przesunac tu pionka"<<endl;
            return false;
        }
        // tu funkcja wykonująca ruch
        move_figure(b, x1, y1, x2, y2);
        return true;
    }
    auto dest = it->second.find(p2);
    if(dest == it->second.end())
    {
        cout<< "nie możesz tu bić\n";
        return false;
    }
    for( auto k = dest->second.begin(); k != dest->second.end(); ++k)
    {
        //tu funkcja usuwająca zbite pionki z figure_vector przecwinika i z planszy
        if(k != dest->second.end())
            remove_figure(b, plr, k->x, k->y);
        // b.remove(k->x, k->y);
    }
    // tu funkcja przenoszaca figure i modyfikująca figure_vector 
    move_figure(b, x1, y1, x2, y2);
    //b.move(x1,y1,x2,y2, move_direction, myQueenSymbol);
    return true;
}

void Player::move_figure(Board &b, short x1, short y1, short x2, short y2)
{
    b.move(x1,y1,x2,y2, move_direction, myQueenSymbol);

//    b.move(x1, y1, x2, y2);
    for(auto it = figures_vector.begin(); it != figures_vector.end(); ++it)
    {
        if( (*it)->getX() == x1 && (*it)->getY() == y1 )
        {
            //damka
            if( (move_direction == -1 && x2 == 0) || ( move_direction == 1 && x2 == 7 ) )
            {
                figures_vector.erase(it);
                Figure* tmp = new Queen(x2, y2);
                figures_vector.push_back(tmp);
            }
            else
            {
                (*it)->setNewCoordinates(x2, y2);
            }
        }
    }
}
void Player::remove_figure(Board &b, Player &plr, short x, short y)
{
    b.remove(x,y);
    // for(auto &it: plr.figures_vector)
    for(auto it = plr.figures_vector.begin(); it != plr.figures_vector.end(); ++it)
    {
        // if(it == plr.figures_vector.end()) continue;
        // if(plr.figures_vector.empty()) continue;
        // cout<<"plr.figures_vector.end() = "<<plr.figures_vector.end()<<endl;
        if((*it)->getX() == x && (*it)->getY() == y)
        {
            plr.figures_vector.erase(it);
            if(plr.figures_vector.empty()) return;
        }
    }
}

short Player::getMyPawnSymbol()
{
    return myPawnSymbol;
}
short Player::getMyQueenSymbol()
{
    return myQueenSymbol;
}
short Player::getOppPawnSymbol()
{
    return oppPawnSymbol;
}
short Player::getOppQueenSymbol()
{
    return oppQueenSymbol;
}
void Player::clear_possible_kills_and_moves()
{
    for(auto &el: figures_vector)
    {
        el->clear_killed_and_moves();
    }
    possible_kills.clear();
    possible_moves.clear();
}

bool Player::isPossibleKill()
{
    if(possible_kills.empty()) return false;
    return true;
}

bool Player::AmILoose()
{
    return figures_vector.empty();
}