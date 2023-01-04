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

#define MAX_CHILD(depth) depth - MIN_DEPTH > BOARD_WIDTH ? 2 : BOARD_WIDTH - depth + MIN_DEPTH


class PlayCalculator
{
    public:
        PlayCalculator(Board* board);
        ~PlayCalculator();

        void setDepth(int newDepth);

        void process();
        void process(int processDepth);

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

    private:
        PlayCalculator(Board* board, int depth, int maxDepth, std::unordered_map<std::string, PlayCalculator*>* playsHashMap);

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
        void generateChilds();
        void generateChild(int playPos);
        void disableChilds();
        void processChild();

        void printBestPlay(int depth);

};
