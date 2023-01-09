#include <iostream>
#include <string>

#define BOARD_HEIGHT 6
#define BOARD_WIDTH 7
#define BOARD_LINES_COUNT BOARD_WIDTH + BOARD_HEIGHT + (BOARD_WIDTH + BOARD_HEIGHT - 7) * 2
#include <climits>

#define TOKEN_A (char)0b01
#define TOKEN_B (char)0b10
#define NO_TOKEN (char)0b00
#define TOKEN_ERROR (char)0b11

#define EXAMPLE_BOARD_1 "XOXOXOXXOXOXOXXOXOXOXOXOXOXOOXOXOXOOXOX_XO"
#define EXAMPLE_BOARD_2 "OXOXOXOOXOXOXOOXOXOXOXOXOXOXXOXOXOXXOXOXOXOXOXOXOOXOXOXOOXOX_XO"
#define EXAMPLE_BOARD_3 "OXOOXX___OOX____XXX______O________________"
#define EXAMPLE_BOARD_4 "OOXXOXO__XOX_O___XX_O___OX_____XO_________"
#define EXAMPLE_BOARD_5 "_OXXOX____OX_____XO_____O______X______O___"
#define EXAMPLE_BOARD_6 "___X______O______X______O______X__________"
#define EXAMPLE_BOARD_7 "X__XOXX___OXO____XOX____OO_____XO_____OX__"

#define CANT_WIN -1
#define PLAYER_A_WIN SHRT_MAX
#define PLAYER_B_WIN SHRT_MIN
#define NULL_PLAY (char)0xff

struct BoardLine
{
    char *lineContent = nullptr;
    char lineSize = 0;
};

struct LineWinValue 
{
    char a_best_alignment;
    char b_best_alignment;
    char a_token_count;
    char b_token_count;
};

class Board {
    public:
        Board();
        Board(std::string boardTXT);
        ~Board();
        Board* copy();
        char getToken(char x, char y);
        std::string getTokenString(char x, char y);
        void play(char x);
        void play(char x, char token);
        bool canPlayHere(char x);
        short getBoardScore();

        unsigned short getTokenCount();
        char getStackHeight(char x);
        char getNextPlayer();
        char getWinPlayer();

        void clear();

        void operator>>(std::ostream &out);
        std::string getBoardCode();
    
    private:
        char* board;
        char lastPlay;
        void setToken(char x, char y, char token_value);
        BoardLine getLine(char start_x, char start_y, char vel_x, char vel_y, char line_size);
        BoardLine* getAllLines();
        
};

LineWinValue getLinesScore(BoardLine line);
std::string formatScore(short score);
