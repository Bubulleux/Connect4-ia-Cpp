#include "board.h"
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <ostream>
#include <string>

const int boardSize = (BOARD_WIDTH * BOARD_WIDTH * 2) / 8 + 1;
const char cellSymbolArray[4] = {0x5F, 0x58, 0x4f, 0x3f};

Board::Board()
{
    board = new char[boardSize];
    clear();
    lastPlay = NULL_PLAY;
}

Board::Board(std::string boardTxt) {
    board = new char[boardSize];
    clear();
    for (int i = 0; i < boardTxt.length(); i++) {
        for (char j = 0; j < 4; j++) {
            if (cellSymbolArray[j] != boardTxt[i]) continue;
            setToken(i % BOARD_WIDTH, i / BOARD_WIDTH, j);    
            break;
        }
    }
    lastPlay = - 1;
}

Board::~Board() 
{
    delete [] board;
}

char Board::getToken(char x, char y)
{
    if (x < 0 || x >= BOARD_WIDTH || y < 0 || y >= BOARD_HEIGHT) {
        return TOKEN_ERROR;
    }
    int bitIndex = x + y * BOARD_WIDTH;
    char cellValue = (board[bitIndex / 4] >> ((bitIndex % 4) * 2)) & 0b11;
    return cellValue; 
}

Board* Board::copy()
{
    Board* board = new Board();
    for (char x = 0; x < BOARD_WIDTH; x++) {
        for (char y = 0; y < BOARD_HEIGHT; y++) {
            board->setToken(x, y, getToken(x, y));
        } 
    }
    board->lastPlay = lastPlay;
    return board;
}

void Board::setToken(char x, char y, char token_value)
{
    int bitIndex = x + y * BOARD_WIDTH;
    int offset = (bitIndex % 4) * 2;
    char cellValue = (board[bitIndex / 4] & ~(0b11 << offset)) |
        (token_value << offset);
    board[bitIndex / 4] = cellValue;
}

void Board::play(char x) 
{
   play(x, getNextPlayer()); 
}

void Board::play(char x, char token) 
{
    if (!canPlayHere(x)) {
        return;
    }
    lastPlay = x;
    setToken(x, getStackHeight(x), token);
}

unsigned short Board::getTokenCount() 
{
    unsigned short result = 0;
    for (char i = 0; i < BOARD_WIDTH; i++) 
    {
        result += this->getStackHeight(i);
    }
    return result;
}

char Board::getStackHeight(char x) 
{
    for (char i = 0; i < BOARD_HEIGHT; i++) 
    {
        if (this->getToken(x, i) == NO_TOKEN) {
            return i;
        }
    }
    return BOARD_HEIGHT;
}

char Board::getNextPlayer()
{
    unsigned short aTokenCount = 0;
    unsigned short bTokenCount = 0;

    for (char x = 0; x < BOARD_WIDTH; x++) {
        for (char y = 0; y < BOARD_HEIGHT; y++) {
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
    for(int i = 0; i < boardSize; i++)
    {
        board[i] = 0;
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


std::string Board::getTokenString(char x, char y) 
{
    char token = getToken(x, y);
    switch (token) {
        case NO_TOKEN:
            return "  ";
            break;
        case TOKEN_A:
            return "\u2B24 ";
            break;
        case TOKEN_B:
            return "\u25EF ";
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
        result += cellSymbolArray[getToken(i % BOARD_WIDTH, i / BOARD_WIDTH)];
    }
    return result;
}

BoardLine Board::getLine(char start_x, char start_y, char vel_x, char vel_y, char size)
{
    BoardLine boardLine = {new char[size + 1], size};
    for (char i = 0; i < size; i++) {
        boardLine.lineContent[i] = getToken(start_x + vel_x * i, start_y + vel_y * i);
    }
    return boardLine;
}

BoardLine* Board::getAllLines() {
    BoardLine* result = new BoardLine[BOARD_LINES_COUNT];
    int boardLineIndex = 0;

    for (char i = 0; i < BOARD_WIDTH; i++) {
        result[boardLineIndex] = getLine(i, 0, 0, 1, BOARD_HEIGHT);
        boardLineIndex++;
    }

    for (char i = 0; i < BOARD_HEIGHT; i++) {
        result[boardLineIndex] = getLine(0, i, 1, 0, BOARD_WIDTH);
        boardLineIndex++;
    }

    for (char i = 0; i < (BOARD_WIDTH + BOARD_HEIGHT - 7); i++) {
        result[boardLineIndex] = getLine(i < BOARD_HEIGHT - 4 ? 0 : i - BOARD_HEIGHT + 4, i < BOARD_HEIGHT - 4 ? BOARD_HEIGHT - 4 - i : 0, 1, 1, 
                BOARD_HEIGHT - (i < BOARD_HEIGHT - 4 ? BOARD_HEIGHT - 4 - i : 0) - (i > BOARD_WIDTH - 4 ? i - BOARD_WIDTH + 4 : 0));
        boardLineIndex ++;
    }
    
    for (char i = 0; i < (BOARD_WIDTH + BOARD_HEIGHT - 7); i++) {
        result[boardLineIndex] = getLine(i < BOARD_HEIGHT - 4 ? BOARD_WIDTH - 1 : BOARD_WIDTH - i + BOARD_HEIGHT - 5, i < BOARD_HEIGHT - 4 ? BOARD_HEIGHT - 4 - i : 0, -1, 1, 
                BOARD_HEIGHT - (i < BOARD_HEIGHT - 4 ? BOARD_HEIGHT - 4 - i : 0) - (i > BOARD_WIDTH - 4 ? i - BOARD_WIDTH + 4 : 0));
        boardLineIndex ++;
    }

    return result;
}

bool Board::canPlayHere(char x) 
{
    return getStackHeight(x) < BOARD_HEIGHT;
}

short Board::getBoardScore()
{
    BoardLine *lines = getAllLines();
    short aScore = 0;
    short bScore = 0;
    for (int i = 0; i < BOARD_LINES_COUNT; i++) {
        BoardLine line = lines[i];
        LineWinValue score = getLinesScore(line);
        delete [] line.lineContent;
        aScore += score.a_token_count * score.a_token_count;
        bScore += score.b_token_count * score.b_token_count;
        if (score.a_best_alignment >= 4 || score.b_best_alignment >= 4) {
            return score.a_best_alignment >= 4 ? PLAYER_A_WIN : PLAYER_B_WIN;
        }

    }
    delete[] lines;
    return aScore - bScore;
}

LineWinValue getLinesScore(BoardLine line) {
    LineWinValue lineWinValue = {0, 0, 0, 0};
    char playerSpace = NO_TOKEN;
    char spaceSize = 0;
    char token_count = 0;
    char lastSpaceSize = 0;
    char previousToken = TOKEN_ERROR;
    char bestAlignment = 0;
    for (char i = 0; i <= line.lineSize; i++) {
        char token = 0;
        token = line.lineContent[i];
        if ((playerSpace != token && token != NO_TOKEN) || i == line.lineSize)
        {
            if (playerSpace == TOKEN_A) {
                lineWinValue.a_token_count = (int)std::max((int)lineWinValue.a_token_count, spaceSize >= 4 ? (int)token_count : 0);
                lineWinValue.a_best_alignment = (int)std::max((int)lineWinValue.a_best_alignment, spaceSize >= 4 ? (int)bestAlignment : 0);
            }

            if (playerSpace == TOKEN_B) {
                lineWinValue.b_token_count = (int)std::max((int)lineWinValue.b_token_count, spaceSize >= 4 ? token_count : 0);
                lineWinValue.b_best_alignment = (int)std::max((int)lineWinValue.b_best_alignment, spaceSize >= 4 ? bestAlignment : 0);
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
