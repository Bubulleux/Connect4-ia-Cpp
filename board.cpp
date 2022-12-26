#include "board.h"
#include <algorithm>
#include <cstdio>
#include <iostream>
#include <ostream>
#include <string>


Board::Board()
{
    this->clear();
    lastPlay = -1;
}

Board::Board(std::string boardTxt) {
    clear();
    for (int i = 0; i < boardTxt.length(); i++) {
        setToken(i % BOARD_WIDTH, i / BOARD_WIDTH, boardTxt[i]);    
    }
    lastPlay = - 1;
}

char Board::getToken(int x, int y)
{
    if (x < 0 || x >= BOARD_WIDTH || y < 0 || y >= BOARD_HEIGHT) {
        return TOKEN_ERROR;
    }
    return this->board[x][y];
}

Board Board::copy()
{
    Board board = Board();
    for (int x = 0; x < BOARD_WIDTH; x++) {
        for (int y = 0; y < BOARD_HEIGHT; y++) {
            board.setToken(x, y, getToken(x, y));
        } 
    }
    board.lastPlay = lastPlay;
    return board;
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
    if (!canPlayHere(x)) {
        return;
    }
    lastPlay = x;
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
    BoardLine *linesContent = getAllLines();
    for (int i = 0; i < BOARD_LINES_COUNT; i++) {
        LineWinValue linesWin = getLinesScore(linesContent[i]);
        /*for (int j = 0; j < linesContent[i].lineSize; j++) {
            std::cout << linesContent[i].lineContent[j];
        }
        std::printf("\t a count: %i, \t b count: %i, \t a alignment: %i, \t b alignment %i\n", linesWin.a_token_count, linesWin.b_token_count, linesWin.a_best_alignment, linesWin.b_best_alignment);
        */
        if (linesWin.a_best_alignment >= 4 || linesWin.b_best_alignment >= 4) 
        {
            return linesWin.a_best_alignment >= 4 ? TOKEN_A : TOKEN_B;
        }
    }
    return NO_TOKEN;
}


std::string Board::getTokenString(int x, int y) 
{
    char token = getToken(x, y);
    switch (token) {
        case NO_TOKEN:
            return "  ";
            break;
        case TOKEN_A:
            return "\u2588\u2588";
            break;
        case TOKEN_B:
            return "\u2592\u2592";
            break;
    
    }
    return "";
}


void Board::operator>>(std::ostream &out)
{
    std::cout << getBoardCode() << std::endl << std::endl;
    if (lastPlay != -1)
    {
        out << " ";
        for (int i = 0; i < lastPlay; i++) {
            out << "   ";
        }
        out << "\\/" << std::endl;
    }
    for (int y = BOARD_HEIGHT - 1; y >= 0; y--) {
        for (int x = 0; x < BOARD_WIDTH; x++) {
            out << "|" << getTokenString(x, y);
        }
        out << "|" << std::endl;
    }
    out << " ";
    for (int i = 0; i < BOARD_WIDTH; i++) {
        out << i + 1 << "  ";
    }
    out << std::endl;
}

std::string Board::getBoardCode()
{
    std::string result = "";
    for (int i = 0; i < BOARD_HEIGHT * BOARD_WIDTH; i++) {
        result += getToken(i % BOARD_WIDTH, i / BOARD_WIDTH);
    }
    return result;
}

BoardLine Board::getLine(int start_x, int start_y, int vel_x, int vel_y, int size)
{
    BoardLine boardLine = {new char[size], size};
    for (int i = 0; i < size; i++) {
        boardLine.lineContent[i] = getToken(start_x + vel_x * i, start_y + vel_y * i);
    }
    return boardLine;
}

BoardLine* Board::getAllLines() {
    BoardLine *result = new BoardLine[BOARD_LINES_COUNT];
    int boardLineIndex = 0;

    for (int i = 0; i < BOARD_WIDTH; i++) {
        result[boardLineIndex] = getLine(i, 0, 0, 1, BOARD_HEIGHT);
        boardLineIndex++;
    }

    for (int i = 0; i < BOARD_HEIGHT; i++) {
        result[boardLineIndex] = getLine(0, i, 1, 0, BOARD_WIDTH);
        boardLineIndex++;
    }

    for (int i = 0; i < (BOARD_WIDTH + BOARD_HEIGHT - 7); i++) {
        result[boardLineIndex] = getLine(i < BOARD_HEIGHT - 4 ? 0 : i - BOARD_HEIGHT + 4, i < BOARD_HEIGHT - 4 ? BOARD_HEIGHT - 4 - i : 0, 1, 1, 
                BOARD_HEIGHT - (i < BOARD_HEIGHT - 4 ? BOARD_HEIGHT - 4 - i : 0) - (i > BOARD_WIDTH - 4 ? i - BOARD_WIDTH + 4 : 0));
        boardLineIndex ++;
    }
    
    for (int i = 0; i < (BOARD_WIDTH + BOARD_HEIGHT - 7); i++) {
        result[boardLineIndex] = getLine(i < BOARD_HEIGHT - 4 ? BOARD_WIDTH - 1 : BOARD_WIDTH - i + BOARD_HEIGHT - 5, i < BOARD_HEIGHT - 4 ? BOARD_HEIGHT - 4 - i : 0, -1, 1, 
                BOARD_HEIGHT - (i < BOARD_HEIGHT - 4 ? BOARD_HEIGHT - 4 - i : 0) - (i > BOARD_WIDTH - 4 ? i - BOARD_WIDTH + 4 : 0));
        boardLineIndex ++;
    }

    return result;
}

bool Board::canPlayHere(int x) 
{
    return getStackHeight(x) < BOARD_HEIGHT;
}

int Board::getBoardScore()
{
    BoardLine *lines = getAllLines();
    int aScore = 0;
    int bScore = 0;
    for (int i = 0; i < BOARD_LINES_COUNT; i++) {
        BoardLine line = lines[i];
        LineWinValue score = getLinesScore(line);
        aScore += score.a_best_alignment ^ 2 + score.a_token_count;
        bScore += score.b_best_alignment ^2 + score.b_best_alignment;
        if (score.a_best_alignment >= 4 || score.b_best_alignment >= 4) {
            return score.a_best_alignment >= 4 ? PLAYER_A_WIN : PLAYER_B_WIN;
        }
    }
    return aScore - bScore;
}

LineWinValue getLinesScore(BoardLine line) {
    LineWinValue lineWinValue = {0, 0, 0, 0};
    char playerSpace = NO_TOKEN;
    int spaceSize = 0;
    int token_count = 0;
    int lastSpaceSize = 0;
    char previousToken = TOKEN_ERROR;
    int bestAlignment = 0;
    for (int i = 0; i <= line.lineSize; i++) {
        char token = line.lineContent[i];
        if ((playerSpace != token && token != NO_TOKEN) || i == line.lineSize)
        {
            if (playerSpace == TOKEN_A) {
                lineWinValue.a_token_count = std::max(lineWinValue.a_token_count, spaceSize >= 4 ? token_count : 0);
                lineWinValue.a_best_alignment = std::max(lineWinValue.a_best_alignment, spaceSize >= 4 ? bestAlignment : 0);
            }

            if (playerSpace == TOKEN_B) {
                lineWinValue.b_token_count = std::max(lineWinValue.b_token_count, spaceSize >= 4 ? token_count : 0);
                lineWinValue.b_best_alignment = std::max(lineWinValue.b_best_alignment, spaceSize >= 4 ? bestAlignment : 0);
            }

            playerSpace = token;
            spaceSize = previousToken == NO_TOKEN ? lastSpaceSize : 0;
            token_count = 0;
            bestAlignment = 0;
            if (i == line.lineSize)
            {
                break;
            }
        }
        if (token != previousToken) {
            lastSpaceSize = 0;
        }

        lastSpaceSize++;
        spaceSize++;

        if (token != NO_TOKEN) {
            bestAlignment = std::max(bestAlignment, lastSpaceSize);
            token_count++;
        }
        previousToken = token;

    }
    return lineWinValue;
}
