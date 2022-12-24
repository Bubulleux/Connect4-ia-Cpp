#include <iostream>

#define BOARD_HEIGHT 6
#define BOARD_WIDTH 7

#define TOKEN_A (char)0x58
#define TOKEN_B (char)0x4f
#define NO_TOKEN (char)0x20

struct BoardLine
{
    char *lineContent;
    int lineSize;
};

class Board {
    public:
        Board();
        Board copy();
        char getToken(int x, int y);
        void play(int x);
        void play(int x, char token);

        int getTokenCount();
        int getStackHeight(int x);
        char getNextPlayer();
        char getWinPlayer();

        void clear();

        void operator>>(std::ostream &out);
    
    private:
        char board[BOARD_WIDTH][BOARD_HEIGHT];
        void setToken(int x, int y, char token_value);
        BoardLine getLine(int start_x, int start_y, int vel_x, int vel_y, int line_size);
        BoardLine* getAllLines(int *size);
        
};

int getLinesScore(BoardLine line);
