#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>
#include "random.h"
#include "textureManager.h"
#include "board.h"
#include "tile.h"
#include <ctime>
using namespace std;

//CHANGELOG:

//Please note that if the config file dimensions do not match the testBoard file dimensions, the test board buttons will not change the board!
int main() {

    // The following reads the config file to set the dimensions of the window, and consequentially, the board
    int width = 0;
    int height = 0;
    int mineCount = 0;
    string tempConfigLine;
    vector<string> configContents;

    ifstream file("boards/config.cfg");
    if (file.is_open()) {
        while(getline(file, tempConfigLine)) {
            configContents.push_back(tempConfigLine);
        }
    }
    else {
        cout << "File improperly loaded" << endl;
    }
    file.close();

    width = stoi(configContents[0]);
    height = stoi(configContents[1]);
    mineCount = stoi(configContents[2]);


    Board board(width, height, mineCount); //builds the board for the first time

    //sets all of the non-board buttons
    sf::Sprite test1;
    sf::Sprite test2;
    sf::Sprite test3;
    test1.setTexture(TextureManager::GetTexture("images/test_1.png"));
    test2.setTexture(TextureManager::GetTexture("images/test_2.png"));
    test3.setTexture(TextureManager::GetTexture("images/test_3.png"));
    test1.setPosition(width * 32 - 192, height * 32);
    test2.setPosition(width * 32 - 128, height * 32);
    test3.setPosition(width * 32 - 64, height * 32);

    sf::Sprite debugButton;
    debugButton.setTexture(TextureManager::GetTexture("images/debug.png"));
    debugButton.setPosition(width * 32 - 256, height * 32);

    sf::Sprite resetButton;
    sf::Sprite happyResetButton;
    sf::Sprite sadResetButton;
    resetButton.setTexture(TextureManager::GetTexture("images/face_happy.png"));
    happyResetButton.setTexture(TextureManager::GetTexture("images/face_win.png"));
    sadResetButton.setTexture(TextureManager::GetTexture("images/face_lose.png"));
    resetButton.setPosition(((width * 32) / 2.0) - 32, height * 32);
    happyResetButton.setPosition(((width * 32) / 2.0) - 32, height * 32);
    sadResetButton.setPosition(((width * 32) / 2.0) - 32, height * 32);

    //sets the mine counter
    int digit3 = 0;
    int digit2 = 0;
    int digit1 = 0;
    sf::Sprite digit3Image;
    sf::Sprite digit2Image;
    sf::Sprite digit1Image;
    sf::Sprite negativeDigitImage;
    digit3Image.setTexture(TextureManager::GetTexture("images/digits.png"));
    digit2Image.setTexture(TextureManager::GetTexture("images/digits.png"));
    digit1Image.setTexture(TextureManager::GetTexture("images/digits.png"));
    negativeDigitImage.setTexture(TextureManager::GetTexture("images/digits.png"));
    negativeDigitImage.setTextureRect(sf::IntRect(21 * 10, 0, 21, 32));
    digit3Image.setPosition(32, height * 32);
    digit2Image.setPosition(64, height * 32);
    digit1Image.setPosition(96, height * 32);
    negativeDigitImage.setPosition(0, height * 32);


    //The window
    bool won = false;
    bool lost = false;
    sf::RenderWindow window(sf::VideoMode(width * 32, (height * 32) + 88), "Minesweeper"); //Opens the window based on the config dimensions

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                TextureManager::Clear(); //should this go here?
                window.close();
            }
            else if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2i position = sf::Mouse::getPosition(window);

                    if (test1.getGlobalBounds().contains(position.x, position.y)) {
                        board.load("boards/testboard1.brd");
                        lost = false;
                        won = false;
                    }
                    if (test2.getGlobalBounds().contains(position.x, position.y)) {
                        board.load("boards/testboard2.brd");
                        lost = false;
                        won = false;
                    }
                    if (test3.getGlobalBounds().contains(position.x, position.y)) {
                        board.load("boards/testboard3.brd");
                        lost = false;
                        won = false;
                    }
                    if (debugButton.getGlobalBounds().contains(position.x, position.y)) {
                        if (!won && !lost) {
                            board.toggleDebug();
                        }
                    }
                    if (resetButton.getGlobalBounds().contains(position.x, position.y)) {
                        board.reset();
                        lost = false;
                        won = false;
                    }

                    for (int i = 0; i < board.height; ++i) {
                        for (int j = 0; j < board.width; ++j) {
                            if (board.tiles[i][j]->getHidden().getGlobalBounds().contains(position.x, position.y)) { //will flip the tile if it is not already flipped
                                if (!won && !lost) {
                                    if (!board.tiles[i][j]->isFlagged()) {
                                        board.tiles[i][j]->flip();
                                        //cout << position.x << " " << position.y << endl;
                                    }
                                }
                            }
                        }
                    }
                }
                else if (event.mouseButton.button == sf::Mouse::Right) {
                    sf::Vector2i position = sf::Mouse::getPosition(window);
                    for (int i = 0; i < board.height; ++i) { //Looks to see if an unflipped tile was clicked
                        for (int j = 0; j < board.width; ++j) {
                            if (board.tiles[i][j]->getHidden().getGlobalBounds().contains(position.x, position.y)) {
                                if (!board.tiles[i][j]->isFlipped()) {
                                    if (!won && !lost) {
                                        board.tiles[i][j]->toggleFlagged();
                                        if (board.tiles[i][j]->isFlagged()) {
                                            board.currentMines -= 1;
                                        }
                                        else {
                                            board.currentMines += 1;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        window.clear(); //clear last stage

        //the number of mines (subtracted by 1 for each flag present
        if (board.currentMines > 0) {
            digit3 = board.currentMines / 100;
            digit2 = (board.currentMines % 100) / 10;
            digit1 = (board.currentMines % 10);
        }
        else {
            digit3 = -1 * board.currentMines / 100;
            digit2 = -1 * (board.currentMines % 100) / 10;
            digit1 = -1 * (board.currentMines % 10);
        }

        digit3Image.setTextureRect(sf::IntRect(21 * digit3, 0, 21, 32));
        digit2Image.setTextureRect(sf::IntRect(21 * digit2, 0, 21, 32));
        digit1Image.setTextureRect(sf::IntRect(21 * digit1, 0, 21, 32));

        if (lost) {
            for (int i = 0; i < height; ++i) {
                for (int j = 0; j < width; ++j) {
                    if (!board.tiles[i][j]->isFlipped()) {
                        if (board.tiles[i][j]->isMine()) {
                            board.tiles[i][j]->flip();
                        }
                    }
                }
            }
            if (board.isInDebug) {
                board.toggleDebug();
            }
        }

        if (!lost) {
            //polls to see if any mines have been flipped, causing the player to lose
            for (int i = 0; i < board.height; ++i) {
                for (int j = 0; j < board.width; ++j) {
                    if (board.tiles[i][j]->isFlipped()) {
                        if (board.tiles[i][j]->isMine()) {
                            lost = true;
                        }
                    }
                }
            }
        }

        if (!lost) {
            //polls how many tiles are flipped compared to how many need to be flipped to win
            //might have to delete tilesFlipped = 0 in multiple places in board.cpp
            board.tilesFlipped = 0;
            for (int i = 0; i < board.height; ++i) {
                for (int j = 0; j < board.width; ++j) {
                    if (board.tiles[i][j]->isFlipped()) {
                        board.tilesFlipped += 1;
                    }
                }
            }
            if (board.tilesFlipped == board.tilesToWin) {
                won = true;
            }
        }

        if (won) {
            for (int i = 0; i < height; ++i) {
                for (int j = 0; j < width; ++j) {
                    if (!board.tiles[i][j]->isFlipped()) {
                        if (board.tiles[i][j]->isMine()) {
                            if (!board.tiles[i][j]->isFlagged()) {
                                board.tiles[i][j]->toggleFlagged();
                                board.currentMines -= 1;
                            }
                        }
                    }
                }
            }
            if (board.isInDebug) {
                board.toggleDebug();
            }
        }


        if (board.currentMines < 0) {
            window.draw(negativeDigitImage);
        }

        //Draw everything to the screen
        board.display(window);
        window.draw(digit3Image);
        window.draw(digit2Image);
        window.draw(digit1Image);
        window.draw(test1);
        window.draw(test2);
        window.draw(test3);
        window.draw(debugButton);

        //Chooses which smiley face to display based on the game-state
        if (won) {
            window.draw(happyResetButton);
        }
        else if (lost) {
            window.draw(sadResetButton);
        }
        else {
            window.draw(resetButton);
        }

        window.display(); //display new stage
    }

    return 0;
}