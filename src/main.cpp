#include "../include/Board.h"
#include "../include/Pawn.h"
#include "../include/Queen.h"
#include "../include/Player.h"
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;


void game()
{
    string name = "../txt/test_dama.txt";
    // Board board(name);
    Board board;
    board.display();    

    Player player1(board, 2, 1);
    Player player2(board, 3, -1);

    while (true)
    {
        short x1, x2, y1, y2;
        player2.compute_possible_kills(board);
        player2.compute_possible_moves(board);

        player2.show_possible_kills();
        if(!player2.isPossibleKill())
            player2.show_possible_moves();

        cin>>x1>>y1>>x2>>y2;
        while( !player2.read_move(board,player1,x1,y1,x2,y2) )
        {
            cin>>x1>>y1>>x2>>y2;
        }
        // fflush(stdin);
        system("cls");
        // if (system("CLS")) system("clear");

        board.display(); 
        player2.clear_possible_kills_and_moves();
        if(player1.AmILoose())
        {
            cout<<"\tKONIEC GRY!\n";
            return;
        }

        player1.compute_possible_kills(board);
        player1.compute_possible_moves(board);

        player1.show_possible_kills();
        if(!player1.isPossibleKill())
            player1.show_possible_moves();

        cin>>x1>>y1>>x2>>y2;
        while( !player1.read_move(board, player2,x1,y1,x2,y2) )
        {
            cin>>x1>>y1>>x2>>y2;
        }
        system("cls");
        board.display(); 
        player1.clear_possible_kills_and_moves();
        if(player2.AmILoose())
        {
            cout<<"\tKONIEC GRY!\n";
            return;
        }
    }

}

int main(int argc, char* argv[])
{
    game();


    sf::RenderWindow window(sf::VideoMode(199, 200), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);
    bool held = false;

    while (window.isOpen())
    {
        sf::Vector2i mouse_pos;
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            if(held)
            {
                held = false;
                mouse_pos = sf::Mouse::getPosition(window);
                cout<<"Mouse pos: "<<mouse_pos.x<<" "<<mouse_pos.y<<endl;
                cout<<"held: "<<held<<endl;
            }
            else
            {
                held = true;
                cout<<"held: "<<held<<endl;
            }
        }
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(shape);
        window.display();
    }

}
