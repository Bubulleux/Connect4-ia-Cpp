#include "board.h"
#include <ostream>
#include <unordered_map>
#include <chrono>

#define MAX_DEPTH 40
#define MIN_DEPTH 2

// Child proccessing Value
#define CHILD_MIDEL_CURSOR 10
#define POSITIVE_CHILD_MULTIPLIER 3
#define NEGATIVE_CHILD_MULTIPLIER 2


class PlayCalculator
{
    public:
        PlayCalculator(Board* board, int depth, int maxDepth, std::unordered_map<std::string, PlayCalculator*>* playsHashMap);
        ~PlayCalculator();
        void setDepth(int newDepth);
        void setMaxDepth(int newMaxDepth);
        int process(int processCount);
        int getScore();
        int* getPlaysScore();
        int getBestPlay();
        int* getPlaysRanking();
        int getPositionCalculatedCount();
        float getProgress();
        PlayCalculator* getChild(int index);
        int getPlayCount();
        void print(int printMaxDepth);
        void printBestPlay();
        void printEndGame();
        std::chrono::duration<double>* generateChildTime;

    private:
        Board* board;
        int depth;
        int maxDepth;
        PlayCalculator* childPlay[BOARD_WIDTH];
        std::unordered_map<std::string, PlayCalculator*>* playsHashMap;
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
