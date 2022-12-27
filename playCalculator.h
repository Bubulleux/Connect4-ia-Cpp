#include "board.h"
#include <ostream>

#define MAX_DEPTH 20
#define MIN_DEPTH 2

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
        int* getPlaysRanking();
        int getPositionCalculatedCount();
        float getProgress();
        PlayCalculator getChild(int index);
        int getPlayCount();
        void print(int printMaxDepth);
        void printBestPlay();
        void printEndGame();

    private:
        Board board;
        int depth;
        int maxDepth;
        PlayCalculator* childPlay[BOARD_WIDTH];
        int score;
        int boardStupidScore;
        int childCount;
        char player;
        bool childGenerated;
        void calculateChildScore();
        int generateChilds(int processCount);
        bool generateChild(int playPos);
        int processChild(int processCount);
        void printBestPlay(int depth);

};
