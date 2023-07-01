#include "../include/Board.h"
#include <iostream>
#include <fstream>
using namespace std;

Board::Board(string name)
{
    board = new short*[8];
    for(int i = 0;i<8;i++){
        board[i] = new short[8];}
    ifstream file;
    file.open(name);
    char l;
    for (size_t i = 0; i < 8; i++)
    {
        for (size_t j = 0; j < 9; j++)
        {
            file.get(l);
            if (j == 8) continue;
            //cout<<(short)(l-'0');
            board[i][j] = (short)(l-'0');
        }
    }
    file.close();
}

Board::Board()
{
    board = new short*[8];
    for(int i = 0;i<8;i++){
        board[i] = new short[8];
        for(int j=0;j<8;j++)
        {
            if(i<3)
            {
                if ((i&1) == 0)
                {
                    if((j&1) == 0) board[i][j] = 2;
                    else board[i][j] = 0;
                }
                else
                {
                    if((j&1) == 1) board[i][j] = 2;
                    else board[i][j] = 0;
                }
            }
            else if(i==3 || i==4)
            {
                if ((i&1) == 0)
                {
                    if((j&1) == 0) board[i][j] = 1;
                    else board[i][j] = 0;
                }
                else
                {
                    if((j&1) == 1) board[i][j] = 1;
                    else board[i][j] = 0;
                }
            }
            else
            {
                if ((i&1) == 0)
                {
                    if((j&1) == 0) board[i][j] = 3;
                    else board[i][j] = 0;
                }
                else
                {
                    if(j & 1 == 1) board[i][j] = 3;
                    else board[i][j] = 0;
                }
            }
            
        }
    }
}

Board::~Board()
{
}

void Board::display()
{
    cout<<"\t _______________\n";
    for(int i = 7;i>=0;i--)
    {
        cout<<"\t|";
        for(int j = 0;j<8;j++)
        {
            switch (board[i][j])
            {
            case 0: cout<<" "; break;
            case 1: cout<<"-"; break;
            case 2: cout<<"a"; break;
            case 3: cout<<"b"; break; 
            case 4: cout<<"A"; break;
            case 5: cout<<"B"; break;
            }
            if(j!=7) cout<<" ";
        }
        cout<<"|";
        cout<<endl;
    }
    // cout<<endl;
    cout<<"\t ````````````````\n";
    // cout<<"-----------------\n";

}

short Board::getFigure(short x, short y)
{
    if(x<0 || x>7 || y<0 || y>7) return -1;
    return board[x][y];
}

void Board::move(short x1, short y1, short x2, short y2, short direction, short queenSymbol)
{
    if(x1>7 || x1 <0) return;
    if(x2>7 || x2 <0) return;
    if(y1>7 || y1 <0) return;
    if(y2>7 || y2 <0) return;
    if(board[x1][y1] == 0 || board[x2][y2] == 0) return;
    if(board[x1][y1] == 1) return;
    if( (direction == -1 && x2 == 0) || ( direction == 1 && x2 == 7 ) )
        board[x2][y2] = queenSymbol;
    else
        board[x2][y2] = board[x1][y1];
    board[x1][y1] = 1;
}

void Board::remove(short x, short y)
{
    if( x<8 && x >= 0 && y<8 && y>=0 && board[x][y] != 0 && board[x][y] != 1)
    {
        board[x][y] = 1;
    }
    else
        cout<<"you try to remove empty square\n";
}