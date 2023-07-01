#ifndef Player_h
#define Player_h

#include "Figure.h"


class Player
{
private:
    short move_direction;
    short oppPawnSymbol;
    short oppQueenSymbol;
    short myPawnSymbol;
    short myQueenSymbol;
    map <Point, map<Point, vector<Point>>> possible_kills;
    map <Point, vector<Point>> possible_moves;
    vector <Figure*> figures_vector;
public:
    Player(Board&, short = 2, short = 1);
    //~Player();
    void compute_possible_kills(Board&);
    void compute_possible_moves(Board&);
    void show_possible_kills();
    void show_possible_moves();
    bool read_move(Board&, Player&, short, short, short, short);
    void move_figure(Board&, short, short, short, short);
    void remove_figure(Board&, Player&, short, short);
    short getMyPawnSymbol();
    short getMyQueenSymbol();
    short getOppPawnSymbol();
    short getOppQueenSymbol();
    void clear_possible_kills_and_moves();
    bool isPossibleKill();
    bool AmILoose();
};

#endif