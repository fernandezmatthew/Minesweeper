#pragma once
#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>
#include "textureManager.h"

using namespace std;

class Tile {
private:
    sf::Sprite hidden; //the hidden tile
    sf::Sprite revealed; //the flipped tile
    vector<Tile*> adjacentMines; //pointers to all adjacent mines
    vector<Tile*> adjacentTiles; //pointers to all adjacent tiles
    bool mine; //will say if the tile is a mine
    bool flagged; //will say if the tile is flagged
    bool flipped; //will say if the tile is flipped
public:
    float xLoc; //the x location of the tile (for sprite positioning)
    float yLoc; //the y location of the tile (for sprite positioning)

    Tile();
    sf::Sprite& getHidden(); //returns reference to the hidden tile sprite
    sf::Sprite& getRevealed(); //same but for flipped
    vector<Tile*>& getAdjacentMines(); //returns reference to the mine pointer vector
    vector<Tile*>& getAdjacentTiles(); //same but for all adjacent tiles
    void setMine(bool boolean); //sets mine to true or false
    void toggleFlagged(); //flips the flagged boolean
    void setPosition(float x, float y); //sets xLoc, yLoc, and sprite positions
    void flip(); //sets flipped to true, and flips adjacent tiles as well (if not flagged and not next to mines)
    bool isMine(); //returns true if mine
    bool isFlagged(); //returns true if flagged
    bool isFlipped(); //returns true if flipped
    int getNumAdjacentMines(); //returns the number of adjacent mines
};
