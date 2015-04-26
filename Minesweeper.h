#ifndef MINESWEEPER_H
#define MINESWEEPER_H
#include <vector>
#include <iostream>
#include <queue>

//the structure of each tile

struct tile;

struct adjTile
{
    tile *t;
};
struct tile
{
    std::string name;
    int position;
    bool mine;
    int touchingMines;
    bool visitedMine;
    std::vector<adjTile> adj;
};


class Minesweeper
{
    public:
        Minesweeper();
        void createTiles();
        void createMines(std::string firstGuess);
        void createTileEdges();
        void displayTileEdges();
        void assignMines();
        void displayBoard();
        void firstCheck(std::string guess);
        bool guessCheck(std::string guess);
        int minesByTile(tile* mineCheck);
        bool gameWon();
        virtual ~Minesweeper();
    protected:
    private:
        //tracks where the mines are on the map
        std::vector<int> minePlacemenet;
        //the initial guess so a mine won't be made there
        int firstGuess;
        //vector of all the tiles
        std::vector<tile> allTiles;
        std::queue<tile*> tileTurned;
};

#endif // MINESWEEPER_H
