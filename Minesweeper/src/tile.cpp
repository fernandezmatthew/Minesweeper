#include "tile.h"

Tile::Tile() {
    string hiddenPath = "images/tile_hidden.png";
    hidden.setTexture(TextureManager::GetTexture(hiddenPath));
    string revealedPath = "images/tile_revealed.png";
    revealed.setTexture(TextureManager::GetTexture(revealedPath));
    mine = false;
    flagged = false;
    flipped = false;
    xLoc = 0.0;
    yLoc = 0.0;
}

sf::Sprite& Tile::getHidden() {
    return hidden;
}

sf::Sprite& Tile::getRevealed() {
return revealed;
}

vector<Tile*>& Tile::getAdjacentMines() {
    return adjacentMines;
}

vector<Tile*>& Tile::getAdjacentTiles() {
    return adjacentTiles;
}

void Tile::setMine(bool boolean) {
    if (boolean) {
        mine = true;
    }
    else {
        mine = false;
    }
}

void Tile::toggleFlagged() {
    if (flagged) {
        flagged = false;
    }
    else {
        flagged = true;
    }
}

void Tile::setPosition(float x, float y) {
    hidden.setPosition(x, y);
    revealed.setPosition(x, y);
    xLoc = x;
    yLoc = y;
}

void Tile::flip() {
    flipped = true;
    if (getNumAdjacentMines() == 0) {
        for (long unsigned int i = 0; i < adjacentTiles.size(); ++i) {
            if (!isMine()) {
                if (!adjacentTiles[i]->isFlipped()) {
                    if (!adjacentTiles[i]->isFlagged()) {
                        adjacentTiles[i]->flip();
                    }
                }
            }
        }
    }
}

bool Tile::isMine() {
    if (mine) {
        return true;
    }
    else {
        return false;
    }
}

bool Tile::isFlagged() {
    if (flagged) {
        return true;
    }
    else {
        return false;
    }
}

bool Tile::isFlipped() {
    if (flipped) {
        return true;
    }
    else {
        return false;
    }
}

int Tile::getNumAdjacentMines() {
    return (int) adjacentMines.size();
}