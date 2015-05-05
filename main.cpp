#include <iostream>
#include "Minesweeper.h"

using namespace std;

//intro page

int main()
{
    Minesweeper m;
    m.createTiles();
    m.createTileEdges();
    //m.displayTileEdges();
    m.displayBoard();
    int menuOption = 6;
    while(menuOption != 2)
    {
        cout << "=============================" << endl;
        cout << "=============================" << endl;
        cout << "|                           |" << endl;
        cout << "|Welcome to MineSweeper v0.1|" << endl;
        cout << "|Please Select an Option    |" << endl;
        cout << "|1.Play the Game            |" << endl;
        cout << "|2. Quit                    |" << endl;
        cout << "=============================" << endl;
        cin >> menuOption;
        if (menuOption == 1)
        {
            cout << "Enter the tile Number to guess that tile" << endl;
            cout << "Enter a Guess: ";
            string initialGuess;
            cin.clear();
            cin.sync();
            getline(cin, initialGuess);
            m.createMines(initialGuess);
            m.firstCheck(initialGuess);
            bool gameOn = true;
            //the tile being guessed
            string guess;
            while(gameOn)
            {
                cout << "You guessed correctly!!! Keep going!!" << endl;
                m.displayBoard();
                cout << "Enter a Guess: ";
                cin.clear();
                cin.sync();
                getline(cin, guess);
                gameOn = m.guessCheck(guess);
                if(m.gameWon())
                {
                    cout << "You Win !!!" << endl;
                    gameOn = false;
                }
            }
            if(!gameOn)
            {
                if (!m.gameWon())
                {
                     m.displayBoard();
                    cout << "BOOOO!!! You lost" << endl;
                }
            }
        }
        else if (menuOption == 2)
        {
            cout << "Goodbye!" << endl;
        }
        else
        {
            cout << "Menu input must be in range (1...2), please try again." << endl;
        }
    //keeps track if a mine was hit yet
    }
}

