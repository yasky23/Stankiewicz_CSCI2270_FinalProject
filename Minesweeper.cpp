#include "Minesweeper.h"
#include <iostream>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <queue>
#include <windows.h>

using namespace std;

Minesweeper::Minesweeper()
{
    //ctor
}

//Displays the game board
void Minesweeper::displayBoard()
{
    //To get colors to show up on the board
    HANDLE hConsole;
        int k;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    cout << "==============================================" << endl;
    for(int i = 1; i < 10; i++)
    {
        cout << "|";
        for(int j = (i - 1) * 9; j < 9 *i; j++)
        {
            //empty the tile thats been visited and not touching any tiles
            if(allTiles[j].visitedMine && allTiles[j].touchingMines == 0)
            {
                cout << "   " << " |";
            }
            //flip the tiC:\Users\Lukasz\workspace\Minesweeper\Minesweeper.cbple that has been visited but is near a mine
            else if(allTiles[j].visitedMine)
            {
                SetConsoleTextAttribute(hConsole, 2);
                cout << "  " << allTiles[j].touchingMines << " |";
            }
            else
            {
                SetConsoleTextAttribute(hConsole, 3);
                cout << " " << allTiles[j].name << " |";
            }
        }
        cout << endl;
        cout << "----------------------------------------------" << endl;
    }

    cout << "==============================================" << endl;

}


//creates 81 tiles for a 9X9 board
void Minesweeper::createTiles()
{
    //tracks which mine it is
    int mineNumber = 1;
    //this will go through a loop make a 9X9 with 81 tiles
    string maps[] = {"A", "B", "C","D", "E","F","G","H","I", "J","K","L","M","N","O","P","Q","R","S","T","U"};
    for(int i = 1; i <= 9; i++)
    {
        //This puts all the tiles in a vector
        for(int j = 1; j <= 9; j++)
        {
            tile newTile;
            newTile.position = mineNumber;
            newTile.name = maps[i-1] + maps[j-1];
            newTile.mine = false;
            newTile.touchingMines = 0;
            newTile.visitedMine = false;

            allTiles.push_back(newTile);
            mineNumber++;
        }
    }

}

void Minesweeper::displayTileEdges()
{
    for(int i = 0; i < allTiles.size(); i++)
    {
        cout<<allTiles[i].name << "-->";
        for(int j = 0; j < allTiles[i].adj.size(); j++){
            cout<<allTiles[i].adj[j].t->name<<"***";
        }
        cout<<endl;
    }
}

//algorithim for creating edges between all the tiles
//as hard coding would be pretty ridicoulous
//2 cases
//either its a starting or ending row
//or its one of the middle ones
//I chose to only make one tile adjacent to one only and not the other way around as to not deal with repeated edges
void Minesweeper::createTileEdges()
{

    for(int i = 0; i < 9; i++)
    {
        //first corner
        if(allTiles[i].position == 1)
        {
            //finds the 3 adjacent tiles know ahead of time the bounds
            for(int j = 1; j < 11;j++)
            {
                if(allTiles[j].position == 2 || allTiles[j].position == 10 || allTiles[j].position == 11)
                {
                    adjTile aT;
                    aT.t = &allTiles[j];
                    allTiles[i].adj.push_back(aT);
                    //another vertex for edge in other direction
                    /*adjTile aT2;
                    aT2.t = &allTiles[i];
                    allTiles[j].adj.push_back(aT2);*/
                }
            }
        }
        //the second corner
        else if(allTiles[i].position == 9)
        {
            //finds the 3 adjacent tiles know ahead of time the bounds
            for(int j = 7; j < 18; j++)
            {
                if(allTiles[j].position == 8 || allTiles[j].position == 17 || allTiles[j].position == 18)
                {
                    adjTile aT;
                    aT.t = &allTiles[j];
                    allTiles[i].adj.push_back(aT);
                    /*
                    //another vertex for edge in other direction
                    adjTile aT2;
                    aT2.t = &allTiles[i];
                    allTiles[j].adj.push_back(aT2);*/
                }
            }
        }
        //all the tiles between the two corners
        else
        {
            //finds the 5 adjacent tiles
            for(int j = 0; j < 19;j++)
            {
                if(allTiles[j].position == allTiles[i].position - 1 || allTiles[j].position == allTiles[i].position + 1 || allTiles[j].position == allTiles[i].position + 9 || allTiles[j].position == allTiles[i].position + 10 || allTiles[j].position == allTiles[i].position + 8)
                {
                    adjTile aT;
                    aT.t = &allTiles[j];
                    allTiles[i].adj.push_back(aT);
                    //another vertex for edge in other direction
                    /*
                    adjTile aT2;
                    aT2.t = &allTiles[i];
                    allTiles[j].adj.push_back(aT2);*/
                }
            }
        }
    }

    //Here we do all the rest of the lines since the last row adj will be made from the second to last row
    for(int j = 9; j < 82; j++)
    {
        //2 cases here either an edge tile or tile in the middle
        //case 1 where it is an edge tile
        if(allTiles[j].position % 9 == 0 || allTiles[j].position % 9 == 1)
        {
            //corner on the left
            if(allTiles[j].position % 9 ==1)
            {
                for(int g = 0; g < 82;g++)
                {
                    if(allTiles[g].position == allTiles[j].position + 1 || allTiles[g].position == allTiles[j].position + 9 ||
                       allTiles[g].position == allTiles[j].position + 10 || allTiles[g].position == allTiles[j].position - 9 ||
                       allTiles[g].position == allTiles[j].position - 8)
                    {
                        adjTile aT;
                        aT.t = &allTiles[g];
                        allTiles[j].adj.push_back(aT);
                        //another vertex for edge in other direction
                        /*
                        adjTile aT2;
                        aT2.t = &allTiles[j];
                        allTiles[g].adj.push_back(aT2);*/
                    }
                }
            }
            //corner on the right
            else
            {
                for(int g = 0; g < 82;g++)
                {
                    if(allTiles[g].position == allTiles[j].position + -1 || allTiles[g].position == allTiles[j].position - 9
                       || allTiles[g].position == allTiles[j].position - 10 || allTiles[g].position == allTiles[j].position + 8
                       || allTiles[g].position == allTiles[j].position + 9)
                    {
                        adjTile aT;
                        aT.t = &allTiles[g];
                        allTiles[j].adj.push_back(aT);
                        //another vertex for edge in other direction
                        /*
                        adjTile aT2;
                        aT2.t = &allTiles[j];
                        allTiles[g].adj.push_back(aT2);*/
                    }
                }
            }
        }
        //case 2 where the tile has 8 adjacent tiles
        else
        {
            for(int g = 0; g < 82; g++)
            {
                if(allTiles[g].position == allTiles[j].position - 10 || allTiles[g].position == allTiles[j].position - 9 ||
                   allTiles[g].position == allTiles[j].position - 8 || allTiles[g].position == allTiles[j].position - 1 ||
                   allTiles[g].position == allTiles[j].position + 1 || allTiles[g].position == allTiles[j].position +8 ||
                   allTiles[g].position == allTiles[j].position +9 || allTiles[g].position == allTiles[j].position + 10)
                {
                    adjTile aT;
                    aT.t = &allTiles[g];
                    allTiles[j].adj.push_back(aT);
                    //another vertex for edge in other direction
                    /*
                    adjTile aT2;
                    aT2.t = &allTiles[j];
                    allTiles[g].adj.push_back(aT2);*/


                }
            }
        }
    }
}

//after finding a valid spot for all the numbers
//the 10 mines are assigned to valid spots
void Minesweeper::assignMines()
{
    for(int i = 0; i < minePlacemenet.size();i++)
    {
        cout << "This is where all the mines are " << minePlacemenet[i] << endl;
        allTiles[minePlacemenet[i]].mine = true;
    }
}


//After the initial guess the mines are created so you
//can't lose the game on the very first guess
void Minesweeper::createMines(string firstGuess)
{
    //need to find where the first guess mine is located
    tile *firstGuessTile;
    for(int k = 0; k < allTiles.size();k++)
    {
        if(firstGuess == allTiles[k].name)
        {
                firstGuessTile = &allTiles[k];
        }
    }
    cout << "positon of first guess tile is" << firstGuessTile->position << endl;
    //seed totally random numbers using time and srand function
    srand(time(NULL));
    //were going to need 10 mines
    //make sure you can't lose on first guess
    int mine = rand() % 81 +1;
    //to see if the same mine exists there
    bool duplicateMine = true;
    while(mine == firstGuessTile->position)
    {
        mine = rand() % 81+1;
    }
    //push the first mine
    minePlacemenet.push_back(mine);
    //get the other 9 times
    for(int i = 0; i < 9; i++)
    {
        int nextmine;
        //checks if a mine in that spot already exists
        while(duplicateMine)
        {
            //makes another mine
            nextmine = rand() % 81+1;
            //check if the mine is there
            duplicateMine = false;
            for(int j = 0; j < minePlacemenet.size(); j++)
            {
                if(nextmine == minePlacemenet[j])
                {//if there's a duplicate we make a different one
                    duplicateMine = true;
                }
            }
        }
        duplicateMine = true;
        //did not find a duplicate so add it to the vecotr
        minePlacemenet.push_back(nextmine);
    }
    //since all 10 posiitons are valid now with no repeats
    assignMines();
}

//for checking the first actual guess
void Minesweeper::firstCheck(string guess)
{
    tile *guessT;
    tile *qTile;
    //find the address of the guess
    for(int i = 0; i < allTiles.size(); i++)
    {
        if(guess == allTiles[i].name)
        {
            guessT = &allTiles[i];
        }
    }
    queue<tile*> myQue;
    guessT->visitedMine = true;
    guessT->touchingMines = minesByTile(guessT);
    for(int j = 0; j < guessT->adj.size(); j++)
    {
        if(guessT->adj[j].t->mine == false)
        {
            myQue.push(guessT->adj[j].t);
        }
    }
    while(!myQue.empty())
    {
        qTile = myQue.front();
        myQue.pop();
        qTile->touchingMines = minesByTile(qTile);
        if(qTile->touchingMines == 0)
        {
            qTile->visitedMine = true;
            for(int k = 0; k < qTile->adj.size();k++)
            {
                if(qTile->adj[k].t->visitedMine == false && qTile->adj[k].t->mine == false)
                {
                    myQue.push(qTile->adj[k].t);
                }
            }
        }
        else
        {
            qTile->visitedMine = true;
        }
    }
}

//new method of checking the tiles similar to the initial way of checking
bool Minesweeper::guessCheck(string guess)
{
    tile *guessT;
    tile *qTile;
    //find the address of the guess
    for(int i = 0; i < allTiles.size(); i++)
    {
        if(guess == allTiles[i].name)
        {
            guessT = &allTiles[i];
        }
    }
    //checks if it's a mine
    //if it is game over
    if(guessT->mine)
    {
        return false;
    }
    //otherwise the game keeps playing
    else
    {
        //que for adjacent tiles that aren't mines
        //asssigns variables to the inital tile
        queue<tile*> myQue;
        guessT->touchingMines = minesByTile(guessT);
        guessT->visitedMine = true;
        //we push all the neighbor tiles that aren't mines and haven't been visited
        for(int i =0; i < guessT->adj.size(); i++)
        {
            if(guessT->adj[i].t->mine == false && guessT->adj[i].t->visitedMine == false)
            {
                myQue.push(guessT->adj[i].t);
            }
        }
        //check all the pushed tiles see if we need to add more
        while(!myQue.empty())
        {
            qTile = myQue.front();
            myQue.pop();
            qTile->touchingMines = minesByTile(qTile);
            //if the tile has no mines around it we que up the adjacwent tiles
            if(qTile->touchingMines == 0)
            {
                qTile->visitedMine = true;
                for(int k = 0; k < qTile->adj.size();k++)
                {
                    //if the neighbor has not been visited before
                    if(qTile->adj[k].t->visitedMine == false && qTile->adj[k].t->mine == false)
                    {
                        myQue.push(qTile->adj[k].t);
                    }
                }
            }
            else
            {
                //aknowldge the tile is visited
                qTile->visitedMine = true;
            }
        }
        //return true to indicate the game is still going
        return true;
    }
}

//old algoritihm for checking mines didn't really work out
//checks the guess and clears up the board
/*
void Minesweeper::guessCheck(string guess)
{
    tile *guessTile;
    tile *tileInQ;
    //find the porpeties of the tile your tring to guess
    for(int i = 0; i < allTiles.size(); i++)
    {
        if(allTiles[i].name == guess);
        {
            guessTile = &allTiles[i];
            break;
        }
    }
    //just in case you hit a mine the games done
    //change this later to return booleans
    if(guessTile->mine)
    {
        cout << "you lose good day sit" << endl;
    }
    else
    {
        //since you didn't hit a mind we que the tile up and go through
        //the neighbors examinging their properties
        guessTile->visitedMine = true;
        queue<tile*> guessQue;
        guessQue.push(guessTile);
        tileTurned.push(guessTile);
        //we keep clearing until the neighbors are starting to touch mines
        while(!guessQue.empty())
        {
            tileInQ = guessQue.front();
            guessQue.pop();
            //determine the amount of mines touching it
            int minesNear = minesByTile(tileInQ);
            tileInQ->touchingMines = minesNear;
            for(int j = 0; j < tileInQ->adj.size(); j++)
            {
                //Case 1
                //add the adjacent tile to the que if its not a mine
                //and not touching any mines
                //and not visited before
                if(minesByTile(tileInQ->adj[j].t) == 0 && tileInQ->adj[j].t->visitedMine == false && tileInQ->adj[j].t->mine == false)
                {
                    //mark the que visited now
                    tileInQ->adj[j].t->visitedMine = true;
                    //push it onto the stack
                    guessQue.push(tileInQ->adj[j].t);
                }
                //Case 2
                //its not a mine but it is touching other mines
                //And hasn't been visited before so it'll be visited
                //but neighbors dont go into que so it doesn't auto solve
                else if(tileInQ->adj[j].t->visitedMine == false && tileInQ->adj[j].t->mine == false)
                {
                    int numberOfMines = minesByTile(tileInQ->adj[j].t);
                    tileInQ->adj[j].t->touchingMines = numberOfMines;
                    tileInQ->adj[j].t->visitedMine = true;
                }
            }
        }
    }
}
*/

//calculates the amount of mines a tile is touching
int Minesweeper::minesByTile(tile* mineCheck)
{
    int nearbyMines = 0;
    for(int i = 0; i < mineCheck->adj.size(); i++)
    {
        if(mineCheck->adj[i].t->mine)
        {
            nearbyMines++;
        }
    }
    return nearbyMines;
}

//this will go through and check to see if there is
//only 10 unvisited tiles left which means you win
bool Minesweeper::gameWon()
{
    int tilesGuessed = 0;
    for(int i = 0; i < allTiles.size();i++)
    {
        if(allTiles[i].visitedMine)
        {
            tilesGuessed++;
        }
    }
    if(tilesGuessed == 71)
        return true;
    else
        return false;
}

Minesweeper::~Minesweeper()
{
    //dtor
}
