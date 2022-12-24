#include "board.h"
#include <iostream>

Board::Board()
{
    this->clear();
}

char Board::getToken(int x, int y)
{
    return this->board[x][y];
}

void Board::setToken(int x, int y, char token_value)
{
    this->board[x][y] = token_value;    
}

void Board::play(int x) 
{
   play(x, getNextPlayer()); 
}

void Board::play(int x, char token) 
{
    setToken(x, getStackHeight(x), token);
}

int Board::getTokenCount() 
{
    int result = 0;
    for (int i = 0; i < BOARD_WIDTH; i++) 
    {
        result += this->getStackHeight(i);
    }
    return result;
}

int Board::getStackHeight(int x) 
{
    for (int i = 0; i < BOARD_HEIGHT; i++) 
    {
        if (this->getToken(x, i) == NO_TOKEN) {
            return i;
        }
    }
    return BOARD_HEIGHT;
}

char Board::getNextPlayer()
{
    int aTokenCount = 0;
    int bTokenCount = 0;

    for (int x = 0; x < BOARD_WIDTH; x++) {
        for (int y = 0; y < BOARD_HEIGHT; y++) {
            char token = this->getToken(x, y);
            switch (token) {
                case TOKEN_A:
                    aTokenCount++;
                    break;
                case TOKEN_B:
                    bTokenCount++;
                    break;
            }
        }
    }
    return aTokenCount == bTokenCount ? TOKEN_A : TOKEN_B;
}

void Board::clear()
{
    for (int x = 0; x < BOARD_WIDTH; x++) {
        for (int y = 0; y < BOARD_HEIGHT; y++) {
            setToken(x, y, NO_TOKEN);
        }    
    }
}

char Board::getWinPlayer() 
{
    return NO_TOKEN;
}

void Board::operator>>(std::ostream &out)
{
    for (int y = BOARD_HEIGHT - 1; y >= 0; y--) {
        for (int x = 0; x < BOARD_WIDTH; x++) {
            out << "|" << getToken(x, y);
        }
        out << "|" << std::endl;
    }
}

BoardLine Board::getLine(int start_x, int start_y, int vel_x, int vel_y, int size)
{
    BoardLine boardLine = {new char[size], size};
    for (int i = 0; i < size; i++) {
        boardLine.lineContent[i] = getToken(start_x + vel_x * i, start_y + vel_y * i);
    }
    return boardLine;
}

BoardLine* Board::getAllLines(int *size) {
    *size = BOARD_HEIGHT + BOARD_WIDTH + (BOARD_WIDTH + BOARD_HEIGHT - 7) * 2;
    for
}
