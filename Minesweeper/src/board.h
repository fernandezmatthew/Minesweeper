#pragma once
#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>
#include "random.h"
#include "textureManager.h"
#include "tile.h"

class Board {
private:
public:
    int width; //width of the board, which will be proportional to the window
    int height; //height of board
    int mineCount; //total mines for randomized games
    int currentMines; //how many mines are unaccounted for
    bool isInDebug; //tells if the board is in debug mode
    int tilesFlipped; //tells how many tiles are currently flipped
    int tilesToWin; //tells how many tiles need to be flipped to win
    vector<vector<Tile*>> tiles; //holds all the tiles in a 2 dimensional array //tiles[y][x] with origin in top left
    Board(); //constructs a default board with default values
    Board(int _width, int _height, int _mineCount); //constructs a board with passed in values
    void set(); //sets the board with all its tiles and randomizes mineCount mines
    void clear(); //clears the tiles vector to be reused
    void load(string filePath); //will create a board based on a .brd file, which is a 2d array of 1's (mines) and 0's (empty spaces)
    void reset(); //will both clear and set the board
    void toggleDebug(); //changes the debug boolean
    void display(sf::RenderWindow& window); //draws all of the board resources to the screen, called in main()
    ~Board(); //Destructor to delete all of the Tiles that are pointed to in memory
};
