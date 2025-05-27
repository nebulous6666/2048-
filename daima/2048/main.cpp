#include<iostream>
#include<cstring>
#include<vector>
#include"Game.hpp"
#include<conio.h>
using namespace std;
int main()
{
    Game game(4);
    char command;
    while (true)
    {
        game.display();
        cout << "Enter command (w/a/s/d to move, u to undo, q to quit): ";
        command=_getch();
        if (command == 'q' || command == 'Q')
            break;
        else if (command == 'u' || command == 'U')
            game.undo();
        else
            game.move(command);
        if (game.isGameOver())
        {
            cout << "Game Over!" << endl;
            break;
        }
        system("cls");
    }
    return 0;
}