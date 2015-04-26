#include <iostream>
#include <Minesweeper.h>

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
    while(menuOption != 1)
    {
        cout << "=============================" << endl;
        cout << "=============================" << endl;
        cout << "|                           |" << endl;
        cout << "|Welcome to MineSweeper v0.1|" << endl;
        cout << "|Please Select an Option    |" << endl;
        cout << "|1.Play the Game            |" << endl;
        cout << "=============================" << endl;
        cin >> menuOption;
        cout << "Enter the title Number to guess that tile" << endl;
        cout << "Enter a Guess: ";
        string initialGuess;
        cin.clear();
        cin.sync();
        getline(cin, initialGuess);
        m.createMines(initialGuess);
        m.firstCheck(initialGuess);
    }
    //keeps track if a mine was hit yet
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
            break;
        }
    }
    if(!gameOn)
    {
        m.displayBoard();
        cout << "BOOOO!!! You lost" << endl;
    }
}

