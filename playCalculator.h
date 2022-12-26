#include "board.h"
#include <ostream>

#define MAX_DEPTH 7

class PlayCalculator
{
    public:
        PlayCalculator(Board board, int depth, int maxDepth);
        void setDepth(int newDepth);
        void setMaxDepth(int newMaxDepth);
        int process(int processCount);
        int getScore();
        int* getPlaysScore();
        int getBestPlay();
        int getPositionCalculatedCount();
        float getProgress();
        void print(int printMaxDepth);

    private:
        Board board;
        int depth;
        int maxDepth;
        PlayCalculator* childPlay[BOARD_WIDTH];
        int score;
        int boardStupidScore;
        char player;
        bool childGenerated;
        void calculateChildScore();
        int generateChilds(int processCount);
        bool generateChild(int playPos);
        int processChild(int processCount);

};
