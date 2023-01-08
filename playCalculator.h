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

        void setDepth(unsigned short newDepth);

        bool process();
        bool process(unsigned short processDepth);

        short getScore();
        short* getPlaysScore();
        char getBestPlay();
        char* getPlaysRanking();
        int getPositionCalculatedCount();
        float getProgress();
        PlayCalculator* getChild(unsigned short index);
        char getPlayCount();

        void print(unsigned short printMaxDepth);
        void printBestPlay();
        void printEndGame();

    private:
        PlayCalculator(Board* board, unsigned short depth, unsigned short maxDepth, std::unordered_map<std::string, PlayCalculator*>* playsHashMap);

        Board* board;
        unsigned short depth;
        unsigned short maxDepth;
        PlayCalculator* childPlay[BOARD_WIDTH];
        std::unordered_map<std::string, PlayCalculator*>* playsHashMap;
        short score;
        short boardStupidScore;
        int childCount;
        char player;
        bool childGenerated;

        void calculateChildScore();
        void generateChilds();
        void generateChild(char playPos);
        void disableChilds();
        bool processChild();
        bool processChildAsync();

        void printBestPlay(unsigned short depth);

};

void newChildThread(PlayCalculator* child, int maxDepth, std::promise<bool> && promise);
