#include "board.h"

Board::Board() {

    width = 20;
    height = 20;
    mineCount = 20;
    currentMines = 20;
    tilesFlipped = 0;
    tilesToWin = width * height - mineCount;
    isInDebug = false;

    set();
}

Board::Board(int _width, int _height, int _mineCount) {

    width = _width;
    height = _height;
    mineCount = _mineCount;
    currentMines = _mineCount;
    tilesFlipped = 0;
    tilesToWin = width * height - mineCount;
    isInDebug = false;

    set();
}

void Board::set() {
    //Creates a 2D array containing each tile on the board
    for (int i = 0; i < height; ++i) {
        vector<Tile*> horizontalTiles;
        for (int j = 0; j < width; ++j) {
            Tile* newTile = new Tile;
            horizontalTiles.push_back(newTile);
        }
        tiles.push_back(horizontalTiles);
    }

    //Sets the positions (for the purposes of Sprite locations) of each tile in the window
    float xPos = 0.0;
    float yPos = 0.0;

    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            tiles[i][j]->setPosition(xPos, yPos);
            xPos += 32.0;
        }
        yPos += 32.0;
        xPos = 0;
    }

    //Sets the mines randomly amongst the board, based on the given mineCount.
    int minesSet = 0;
    int randomHeight = 0;
    int randomWidth = 0;

    while (minesSet < mineCount) {
        randomHeight = Random::Int(0, height - 1);
        randomWidth = Random::Int(0, width - 1);
        if (tiles[randomHeight][randomWidth]->isMine()) {
        }
        else if (!tiles[randomHeight][randomWidth]->isMine()) {
            tiles[randomHeight][randomWidth]->setMine(true);
            minesSet += 1;
        }
    }

    //Set the adjacentMines and adjacentTiles vectors for each tile (it's a lot)
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            Tile* currentTile = tiles[i][j];
            if (i == 0) {
                if (j == 0) { //3poss //the top left corner

                    currentTile->getAdjacentTiles().push_back(tiles[i + 1][j]);
                    currentTile->getAdjacentTiles().push_back(tiles[i + 1][j + 1]);
                    currentTile->getAdjacentTiles().push_back(tiles[i][j + 1]);

                    if (tiles[i + 1][j]->isMine()) {
                        currentTile->getAdjacentMines().push_back(tiles[i + 1][j]);
                    }
                    if (tiles[i + 1][j + 1]->isMine()) {
                        currentTile->getAdjacentMines().push_back(tiles[i + 1][j + 1]);
                    }
                    if (tiles[i][j + 1]->isMine()) {
                        currentTile->getAdjacentMines().push_back(tiles[i][j + 1]);
                    }
                }
                else if (j == width - 1) {//3poss //the top right corner

                    currentTile->getAdjacentTiles().push_back(tiles[i + 1][j]);
                    currentTile->getAdjacentTiles().push_back(tiles[i + 1][j - 1]);
                    currentTile->getAdjacentTiles().push_back(tiles[i][j - 1]);

                    if (tiles[i + 1][j]->isMine()) {
                        currentTile->getAdjacentMines().push_back(tiles[i + 1][j]);
                    }
                    if (tiles[i + 1][j - 1]->isMine()) {
                        currentTile->getAdjacentMines().push_back(tiles[i + 1][j - 1]);
                    }
                    if (tiles[i][j - 1]->isMine()) {
                        currentTile->getAdjacentMines().push_back(tiles[i][j - 1]);
                    }
                }
                else { //5poss //the top row (not corner)

                    currentTile->getAdjacentTiles().push_back(tiles[i][j - 1]);
                    currentTile->getAdjacentTiles().push_back(tiles[i + 1][j - 1]);
                    currentTile->getAdjacentTiles().push_back(tiles[i + 1][j]);
                    currentTile->getAdjacentTiles().push_back(tiles[i + 1][j + 1]);
                    currentTile->getAdjacentTiles().push_back(tiles[i][j + 1]);

                    if (tiles[i][j - 1]->isMine()) {
                        currentTile->getAdjacentMines().push_back(tiles[i][j - 1]);
                    }
                    if (tiles[i + 1][j - 1]->isMine()) {
                        currentTile->getAdjacentMines().push_back(tiles[i + 1][j - 1]);
                    }
                    if (tiles[i + 1][j]->isMine()) {
                        currentTile->getAdjacentMines().push_back(tiles[i + 1][j]);
                    }
                    if (tiles[i + 1][j + 1]->isMine()) {
                        currentTile->getAdjacentMines().push_back(tiles[i + 1][j + 1]);
                    }
                    if (tiles[i][j + 1]->isMine()) {
                        currentTile->getAdjacentMines().push_back(tiles[i][j + 1]);
                    }
                }
            }
            else if (i == height - 1) {
                if (j == 0) {//3poss //the bottom left corner

                    currentTile->getAdjacentTiles().push_back(tiles[i - 1][j]);
                    currentTile->getAdjacentTiles().push_back(tiles[i - 1][j + 1]);
                    currentTile->getAdjacentTiles().push_back(tiles[i][j + 1]);

                    if (tiles[i - 1][j]->isMine()) {
                        currentTile->getAdjacentMines().push_back(tiles[i - 1][j]);
                    }
                    if (tiles[i - 1][j + 1]->isMine()) {
                        currentTile->getAdjacentMines().push_back(tiles[i - 1][j + 1]);
                    }
                    if (tiles[i][j + 1]->isMine()) {
                        currentTile->getAdjacentMines().push_back(tiles[i][j + 1]);
                    }
                }
                else if (j == width - 1) {//3poss //the bottom right corner

                    currentTile->getAdjacentTiles().push_back(tiles[i - 1][j]);
                    currentTile->getAdjacentTiles().push_back(tiles[i - 1][j - 1]);
                    currentTile->getAdjacentTiles().push_back(tiles[i][j - 1]);

                    if (tiles[i - 1][j]->isMine()) {
                        currentTile->getAdjacentMines().push_back(tiles[i - 1][j]);
                    }
                    if (tiles[i - 1][j - 1]->isMine()) {
                        currentTile->getAdjacentMines().push_back(tiles[i - 1][j - 1]);
                    }
                    if (tiles[i][j - 1]->isMine()) {
                        currentTile->getAdjacentMines().push_back(tiles[i][j - 1]);
                    }
                }
                else {//5poss //the bottom tow (not corner)

                    currentTile->getAdjacentTiles().push_back(tiles[i][j - 1]);
                    currentTile->getAdjacentTiles().push_back(tiles[i - 1][j - 1]);
                    currentTile->getAdjacentTiles().push_back(tiles[i - 1][j]);
                    currentTile->getAdjacentTiles().push_back(tiles[i - 1][j + 1]);
                    currentTile->getAdjacentTiles().push_back(tiles[i][j + 1]);

                    if (tiles[i][j - 1]->isMine()) {
                        currentTile->getAdjacentMines().push_back(tiles[i][j - 1]);
                    }
                    if (tiles[i - 1][j - 1]->isMine()) {
                        currentTile->getAdjacentMines().push_back(tiles[i - 1][j - 1]);
                    }
                    if (tiles[i - 1][j]->isMine()) {
                        currentTile->getAdjacentMines().push_back(tiles[i - 1][j]);
                    }
                    if (tiles[i - 1][j + 1]->isMine()) {
                        currentTile->getAdjacentMines().push_back(tiles[i - 1][j + 1]);
                    }
                    if (tiles[i][j + 1]->isMine()) {
                        currentTile->getAdjacentMines().push_back(tiles[i][j + 1]);
                    }
                }
            }
            else if (j == 0) {//5poss //the left column (not corner)

                currentTile->getAdjacentTiles().push_back(tiles[i - 1][j]);
                currentTile->getAdjacentTiles().push_back(tiles[i - 1][j + 1]);
                currentTile->getAdjacentTiles().push_back(tiles[i][j + 1]);
                currentTile->getAdjacentTiles().push_back(tiles[i + 1][j + 1]);
                currentTile->getAdjacentTiles().push_back(tiles[i + 1][j]);

                if (tiles[i - 1][j]->isMine()) {
                    currentTile->getAdjacentMines().push_back(tiles[i - 1][j]);
                }
                if (tiles[i - 1][j + 1]->isMine()) {
                    currentTile->getAdjacentMines().push_back(tiles[i - 1][j + 1]);
                }
                if (tiles[i][j + 1]->isMine()) {
                    currentTile->getAdjacentMines().push_back(tiles[i][j + 1]);
                }
                if (tiles[i + 1][j + 1]->isMine()) {
                    currentTile->getAdjacentMines().push_back(tiles[i + 1][j + 1]);
                }
                if (tiles[i + 1][j]->isMine()) {
                    currentTile->getAdjacentMines().push_back(tiles[i + 1][j]);
                }
            }
            else if (j == width - 1) {//5poss //the right column (not corner)

                currentTile->getAdjacentTiles().push_back(tiles[i - 1][j]);
                currentTile->getAdjacentTiles().push_back(tiles[i - 1][j - 1]);
                currentTile->getAdjacentTiles().push_back(tiles[i][j - 1]);
                currentTile->getAdjacentTiles().push_back(tiles[i + 1][j - 1]);
                currentTile->getAdjacentTiles().push_back(tiles[i + 1][j]);

                if (tiles[i - 1][j]->isMine()) {
                    currentTile->getAdjacentMines().push_back(tiles[i - 1][j]);
                }
                if (tiles[i - 1][j - 1]->isMine()) {
                    currentTile->getAdjacentMines().push_back(tiles[i - 1][j - 1]);
                }
                if (tiles[i][j - 1]->isMine()) {
                    currentTile->getAdjacentMines().push_back(tiles[i][j - 1]);
                }
                if (tiles[i + 1][j - 1]->isMine()) {
                    currentTile->getAdjacentMines().push_back(tiles[i + 1][j - 1]);
                }
                if (tiles[i + 1][j]->isMine()) {
                    currentTile->getAdjacentMines().push_back(tiles[i + 1][j]);
                }
            }
            else {//8poss //the middle tiles

                currentTile->getAdjacentTiles().push_back(tiles[i - 1][j]);
                currentTile->getAdjacentTiles().push_back(tiles[i - 1][j + 1]);
                currentTile->getAdjacentTiles().push_back(tiles[i][j + 1]);
                currentTile->getAdjacentTiles().push_back(tiles[i + 1][j + 1]);
                currentTile->getAdjacentTiles().push_back(tiles[i + 1][j]);
                currentTile->getAdjacentTiles().push_back(tiles[i + 1][j - 1]);
                currentTile->getAdjacentTiles().push_back(tiles[i][j - 1]);
                currentTile->getAdjacentTiles().push_back(tiles[i - 1][j - 1]);

                if (tiles[i - 1][j]->isMine()) {
                    currentTile->getAdjacentMines().push_back(tiles[i - 1][j]);
                }
                if (tiles[i - 1][j + 1]->isMine()) {
                    currentTile->getAdjacentMines().push_back(tiles[i - 1][j + 1]);
                }
                if (tiles[i][j + 1]->isMine()) {
                    currentTile->getAdjacentMines().push_back(tiles[i][j + 1]);
                }
                if (tiles[i + 1][j + 1]->isMine()) {
                    currentTile->getAdjacentMines().push_back(tiles[i + 1][j + 1]);
                }
                if (tiles[i + 1][j]->isMine()) {
                    currentTile->getAdjacentMines().push_back(tiles[i + 1][j]);
                }
                if (tiles[i + 1][j - 1]->isMine()) {
                    currentTile->getAdjacentMines().push_back(tiles[i + 1][j - 1]);
                }
                if (tiles[i][j - 1]->isMine()) {
                    currentTile->getAdjacentMines().push_back(tiles[i][j - 1]);
                }
                if (tiles[i - 1][j - 1]->isMine()) {
                    currentTile->getAdjacentMines().push_back(tiles[i - 1][j - 1]);
                }
            }
        }
    }
}

void Board::clear() {
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            delete tiles[i][j];
        }
    }
    tiles.clear();
}

void Board::load(string filePath) {

    try { //in a try block so that if there is a dimensional mismatch between the .brd and the .cfg, the program will not crash

        string line;
        vector<string> fileContents;
        ifstream file(filePath);
        if (file.is_open()) {
            while(getline(file, line)) {
                fileContents.push_back(line);
            }
        }
        else {
            cout << "File improperly loaded" << endl;
        }

        if (fileContents.size() != height || fileContents[0].size() != width) {
            throw exception();
        }

        clear();
        currentMines = 0;
        //Creates a 2D array containing each tile on the board
        for (int i = 0; i < height; ++i) {
            vector<Tile*> horizontalTiles;
            for (int j = 0; j < width; ++j) {
                Tile* newTile = new Tile;
                horizontalTiles.push_back(newTile);
            }
            tiles.push_back(horizontalTiles);
        }

        //Sets the positions (for the purposes of Sprite locations) of each tile in the window
        float xPos = 0.0;
        float yPos = 0.0;

        for (int i = 0; i < height; ++i) {
            for (int j = 0; j < width; ++j) {
                tiles[i][j]->setPosition(xPos, yPos);
                xPos += 32.0;
            }
            yPos += 32.0;
            xPos = 0;
        }

        //this only works if the config dimensions match the .brd dimensions, sets mines wherever a '1' was
        for (long unsigned int i = 0; i < fileContents.size(); ++i) {
            for (long unsigned int j = 0; j < fileContents[i].size(); ++j) {
                if (fileContents[i].at(j) == '1') {
                    tiles[i][j]->setMine(true);
                    currentMines += 1;
                }
            }
        }
        tilesToWin = width * height - currentMines;

        //Set the adjacentMines and adjacentTiles vectors for each tile (it's a lot)
        for (int i = 0; i < height; ++i) {
            for (int j = 0; j < width; ++j) {
                Tile* currentTile = tiles[i][j];
                if (i == 0) {
                    if (j == 0) { //3poss //the top left corner

                        currentTile->getAdjacentTiles().push_back(tiles[i + 1][j]);
                        currentTile->getAdjacentTiles().push_back(tiles[i + 1][j + 1]);
                        currentTile->getAdjacentTiles().push_back(tiles[i][j + 1]);

                        if (tiles[i + 1][j]->isMine()) {
                            currentTile->getAdjacentMines().push_back(tiles[i + 1][j]);
                        }
                        if (tiles[i + 1][j + 1]->isMine()) {
                            currentTile->getAdjacentMines().push_back(tiles[i + 1][j + 1]);
                        }
                        if (tiles[i][j + 1]->isMine()) {
                            currentTile->getAdjacentMines().push_back(tiles[i][j + 1]);
                        }
                    }
                    else if (j == width - 1) {//3poss //the top right corner

                        currentTile->getAdjacentTiles().push_back(tiles[i + 1][j]);
                        currentTile->getAdjacentTiles().push_back(tiles[i + 1][j - 1]);
                        currentTile->getAdjacentTiles().push_back(tiles[i][j - 1]);

                        if (tiles[i + 1][j]->isMine()) {
                            currentTile->getAdjacentMines().push_back(tiles[i + 1][j]);
                        }
                        if (tiles[i + 1][j - 1]->isMine()) {
                            currentTile->getAdjacentMines().push_back(tiles[i + 1][j - 1]);
                        }
                        if (tiles[i][j - 1]->isMine()) {
                            currentTile->getAdjacentMines().push_back(tiles[i][j - 1]);
                        }
                    }
                    else { //5poss //the top row (not corner)

                        currentTile->getAdjacentTiles().push_back(tiles[i][j - 1]);
                        currentTile->getAdjacentTiles().push_back(tiles[i + 1][j - 1]);
                        currentTile->getAdjacentTiles().push_back(tiles[i + 1][j]);
                        currentTile->getAdjacentTiles().push_back(tiles[i + 1][j + 1]);
                        currentTile->getAdjacentTiles().push_back(tiles[i][j + 1]);

                        if (tiles[i][j - 1]->isMine()) {
                            currentTile->getAdjacentMines().push_back(tiles[i][j - 1]);
                        }
                        if (tiles[i + 1][j - 1]->isMine()) {
                            currentTile->getAdjacentMines().push_back(tiles[i + 1][j - 1]);
                        }
                        if (tiles[i + 1][j]->isMine()) {
                            currentTile->getAdjacentMines().push_back(tiles[i + 1][j]);
                        }
                        if (tiles[i + 1][j + 1]->isMine()) {
                            currentTile->getAdjacentMines().push_back(tiles[i + 1][j + 1]);
                        }
                        if (tiles[i][j + 1]->isMine()) {
                            currentTile->getAdjacentMines().push_back(tiles[i][j + 1]);
                        }
                    }
                }
                else if (i == height - 1) {
                    if (j == 0) {//3poss //the bottom left corner

                        currentTile->getAdjacentTiles().push_back(tiles[i - 1][j]);
                        currentTile->getAdjacentTiles().push_back(tiles[i - 1][j + 1]);
                        currentTile->getAdjacentTiles().push_back(tiles[i][j + 1]);

                        if (tiles[i - 1][j]->isMine()) {
                            currentTile->getAdjacentMines().push_back(tiles[i - 1][j]);
                        }
                        if (tiles[i - 1][j + 1]->isMine()) {
                            currentTile->getAdjacentMines().push_back(tiles[i - 1][j + 1]);
                        }
                        if (tiles[i][j + 1]->isMine()) {
                            currentTile->getAdjacentMines().push_back(tiles[i][j + 1]);
                        }
                    }
                    else if (j == width - 1) {//3poss //the bottom right corner

                        currentTile->getAdjacentTiles().push_back(tiles[i - 1][j]);
                        currentTile->getAdjacentTiles().push_back(tiles[i - 1][j - 1]);
                        currentTile->getAdjacentTiles().push_back(tiles[i][j - 1]);

                        if (tiles[i - 1][j]->isMine()) {
                            currentTile->getAdjacentMines().push_back(tiles[i - 1][j]);
                        }
                        if (tiles[i - 1][j - 1]->isMine()) {
                            currentTile->getAdjacentMines().push_back(tiles[i - 1][j - 1]);
                        }
                        if (tiles[i][j - 1]->isMine()) {
                            currentTile->getAdjacentMines().push_back(tiles[i][j - 1]);
                        }
                    }
                    else {//5poss //the bottom tow (not corner)

                        currentTile->getAdjacentTiles().push_back(tiles[i][j - 1]);
                        currentTile->getAdjacentTiles().push_back(tiles[i - 1][j - 1]);
                        currentTile->getAdjacentTiles().push_back(tiles[i - 1][j]);
                        currentTile->getAdjacentTiles().push_back(tiles[i - 1][j + 1]);
                        currentTile->getAdjacentTiles().push_back(tiles[i][j + 1]);

                        if (tiles[i][j - 1]->isMine()) {
                            currentTile->getAdjacentMines().push_back(tiles[i][j - 1]);
                        }
                        if (tiles[i - 1][j - 1]->isMine()) {
                            currentTile->getAdjacentMines().push_back(tiles[i - 1][j - 1]);
                        }
                        if (tiles[i - 1][j]->isMine()) {
                            currentTile->getAdjacentMines().push_back(tiles[i - 1][j]);
                        }
                        if (tiles[i - 1][j + 1]->isMine()) {
                            currentTile->getAdjacentMines().push_back(tiles[i - 1][j + 1]);
                        }
                        if (tiles[i][j + 1]->isMine()) {
                            currentTile->getAdjacentMines().push_back(tiles[i][j + 1]);
                        }
                    }
                }
                else if (j == 0) {//5poss //the left column (not corner)

                    currentTile->getAdjacentTiles().push_back(tiles[i - 1][j]);
                    currentTile->getAdjacentTiles().push_back(tiles[i - 1][j + 1]);
                    currentTile->getAdjacentTiles().push_back(tiles[i][j + 1]);
                    currentTile->getAdjacentTiles().push_back(tiles[i + 1][j + 1]);
                    currentTile->getAdjacentTiles().push_back(tiles[i + 1][j]);

                    if (tiles[i - 1][j]->isMine()) {
                        currentTile->getAdjacentMines().push_back(tiles[i - 1][j]);
                    }
                    if (tiles[i - 1][j + 1]->isMine()) {
                        currentTile->getAdjacentMines().push_back(tiles[i - 1][j + 1]);
                    }
                    if (tiles[i][j + 1]->isMine()) {
                        currentTile->getAdjacentMines().push_back(tiles[i][j + 1]);
                    }
                    if (tiles[i + 1][j + 1]->isMine()) {
                        currentTile->getAdjacentMines().push_back(tiles[i + 1][j + 1]);
                    }
                    if (tiles[i + 1][j]->isMine()) {
                        currentTile->getAdjacentMines().push_back(tiles[i + 1][j]);
                    }
                }
                else if (j == width - 1) {//5poss //the right column (not corner)

                    currentTile->getAdjacentTiles().push_back(tiles[i - 1][j]);
                    currentTile->getAdjacentTiles().push_back(tiles[i - 1][j - 1]);
                    currentTile->getAdjacentTiles().push_back(tiles[i][j - 1]);
                    currentTile->getAdjacentTiles().push_back(tiles[i + 1][j - 1]);
                    currentTile->getAdjacentTiles().push_back(tiles[i + 1][j]);

                    if (tiles[i - 1][j]->isMine()) {
                        currentTile->getAdjacentMines().push_back(tiles[i - 1][j]);
                    }
                    if (tiles[i - 1][j - 1]->isMine()) {
                        currentTile->getAdjacentMines().push_back(tiles[i - 1][j - 1]);
                    }
                    if (tiles[i][j - 1]->isMine()) {
                        currentTile->getAdjacentMines().push_back(tiles[i][j - 1]);
                    }
                    if (tiles[i + 1][j - 1]->isMine()) {
                        currentTile->getAdjacentMines().push_back(tiles[i + 1][j - 1]);
                    }
                    if (tiles[i + 1][j]->isMine()) {
                        currentTile->getAdjacentMines().push_back(tiles[i + 1][j]);
                    }
                }
                else {//8poss //the middle tiles

                    currentTile->getAdjacentTiles().push_back(tiles[i - 1][j]);
                    currentTile->getAdjacentTiles().push_back(tiles[i - 1][j + 1]);
                    currentTile->getAdjacentTiles().push_back(tiles[i][j + 1]);
                    currentTile->getAdjacentTiles().push_back(tiles[i + 1][j + 1]);
                    currentTile->getAdjacentTiles().push_back(tiles[i + 1][j]);
                    currentTile->getAdjacentTiles().push_back(tiles[i + 1][j - 1]);
                    currentTile->getAdjacentTiles().push_back(tiles[i][j - 1]);
                    currentTile->getAdjacentTiles().push_back(tiles[i - 1][j - 1]);

                    if (tiles[i - 1][j]->isMine()) {
                        currentTile->getAdjacentMines().push_back(tiles[i - 1][j]);
                    }
                    if (tiles[i - 1][j + 1]->isMine()) {
                        currentTile->getAdjacentMines().push_back(tiles[i - 1][j + 1]);
                    }
                    if (tiles[i][j + 1]->isMine()) {
                        currentTile->getAdjacentMines().push_back(tiles[i][j + 1]);
                    }
                    if (tiles[i + 1][j + 1]->isMine()) {
                        currentTile->getAdjacentMines().push_back(tiles[i + 1][j + 1]);
                    }
                    if (tiles[i + 1][j]->isMine()) {
                        currentTile->getAdjacentMines().push_back(tiles[i + 1][j]);
                    }
                    if (tiles[i + 1][j - 1]->isMine()) {
                        currentTile->getAdjacentMines().push_back(tiles[i + 1][j - 1]);
                    }
                    if (tiles[i][j - 1]->isMine()) {
                        currentTile->getAdjacentMines().push_back(tiles[i][j - 1]);
                    }
                    if (tiles[i - 1][j - 1]->isMine()) {
                        currentTile->getAdjacentMines().push_back(tiles[i - 1][j - 1]);
                    }
                }
            }
        }
    }
    catch (exception&) { //Stops the board from crashing and states the issue
        cout << "The test board that you tried to load does not match the dimensions of the initializing config.cfg file" << endl;
    }
}

void Board::reset() {
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            delete tiles[i][j];
        }
    }
    tiles.clear();
    tilesToWin = width * height - mineCount;
    set();
    currentMines = mineCount;
}

void Board::toggleDebug() {
    if (isInDebug) {
        isInDebug = false;
    }
    else {
        isInDebug = true;
    }
}

void Board::display(sf::RenderWindow& window) {
    float xPos = 0.0;
    float yPos = 0.0;

    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            if (!tiles[i][j]->isFlipped()) {
                window.draw(tiles.at(i).at(j)->getHidden());

                if (isInDebug) {
                    if (tiles[i][j]->isMine()) {
                        sf::Sprite bomb;
                        bomb.setTexture(TextureManager::GetTexture("images/mine.png"));
                        bomb.setPosition(tiles[i][j]->xLoc,tiles[i][j]->yLoc);
                        window.draw(bomb);
                    }
                }

                if (tiles[i][j]->isFlagged()) {
                    sf::Sprite flag;
                    flag.setTexture(TextureManager::GetTexture("images/flag.png"));
                    flag.setPosition(tiles[i][j]->xLoc,tiles[i][j]->yLoc);
                    window.draw(flag);
                }
            }
            else {

                window.draw(tiles.at(i).at(j)->getRevealed());
                if (tiles[i][j]->isMine()) {
                    sf::Sprite bomb;
                    bomb.setTexture(TextureManager::GetTexture("images/mine.png"));
                    bomb.setPosition(tiles[i][j]->xLoc,tiles[i][j]->yLoc);
                    window.draw(bomb);
                }
                else {
                    int numBombs = tiles[i][j]->getNumAdjacentMines();
                    if (numBombs > 0) {
                        sf::Sprite numBombsImage;
                        string numPath = "images/number_";
                        numPath += to_string(numBombs);
                        numPath += ".png";
                        numBombsImage.setTexture(TextureManager::GetTexture(numPath));
                        numBombsImage.setPosition(tiles[i][j]->xLoc,tiles[i][j]->yLoc);
                        window.draw(numBombsImage);
                    }
                    else {

                    }

                }
            }
        }
    }
}

Board::~Board() {
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            delete tiles[i][j];
        }
    }
}