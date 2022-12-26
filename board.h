#include <iostream>
#include <string>

#define BOARD_HEIGHT 6
#define BOARD_WIDTH 7
#define BOARD_LINES_COUNT BOARD_WIDTH + BOARD_HEIGHT + (BOARD_WIDTH + BOARD_HEIGHT - 7) * 2
#include <climits>

#define TOKEN_A (char)0x58
#define TOKEN_B (char)0x4f
#define NO_TOKEN (char)0x5F
#define TOKEN_ERROR (char)0x3f

#define EXAMPLE_BOARD_1 "XOXOXOXXOXOXOXXOXOXOXOXOXOXOOXOXOXOOXOX_XO"
#define EXAMPLE_BOARD_2 "OXOXOXOOXOXOXOOXOXOXOXOXOXOXXOXOXOXXOXOXOXOXOXOXOOXOXOXOOXOX_XO"
#define EXAMPLE_BOARD_3 "OXOOXX___OOX____XXX______O________________"

#define CANT_WIN -1
#define PLAYER_A_WIN INT_MAX
#define PLAYER_B_WIN INT_MIN

struct BoardLine
{
    char *lineContent;
    int lineSize;
};

struct LineWinValue 
{
    int a_best_alignment;
    int b_best_alignment;
    int a_token_count;
    int b_token_count;
};

class Board {
    public:
        Board();
        Board(std::string boardTXT);
        Board copy();
        char getToken(int x, int y);
        std::string getTokenString(int x, int y);
        void play(int x);
        void play(int x, char token);
        bool canPlayHere(int x);
        int getBoardScore();

        int getTokenCount();
        int getStackHeight(int x);
        char getNextPlayer();
        char getWinPlayer();

        void clear();

        void operator>>(std::ostream &out);
        std::string getBoardCode();
    
    private:
        char board[BOARD_WIDTH][BOARD_HEIGHT];
        int lastPlay;
        void setToken(int x, int y, char token_value);
        BoardLine getLine(int start_x, int start_y, int vel_x, int vel_y, int line_size);
        BoardLine* getAllLines();
        
};

LineWinValue getLinesScore(BoardLine line);
std::string formatScore(int score);
