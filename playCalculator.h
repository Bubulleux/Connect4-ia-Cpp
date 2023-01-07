#include "board.h"
#include <future>
#include <ostream>
#include <unordered_map>
#include <chrono>

#define MAX_DEPTH 40
#define MIN_DEPTH 4

// Child proccessing Value
#define CHILD_MIDEL_CURSOR 10
#define POSITIVE_CHILD_MULTIPLIER 3
#define NEGATIVE_CHILD_MULTIPLIER 2

#define SLOP_MULTIPLYER 1
#define MAX_CHILD(depth) std::max(2.0, SLOP_MULTIPLYER * (float)(depth - MIN_DEPTH) + BOARD_WIDTH)


class PlayCalculator
{
    public:
        PlayCalculator(Board* board);
        ~PlayCalculator();
        void recursiveDelete();

        void setDepth(int newDepth);

        bool process();
        bool process(int processDepth);

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
        bool processChild();
        bool processChildAsync();

        void printBestPlay(int depth);

};

void newChildThread(PlayCalculator* child, int maxDepth, std::promise<bool> && promise);
