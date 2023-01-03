#include <algorithm>
#include <bits/chrono.h>
#include <cstdio>
#include <iostream>
#include <string>
#include <unordered_map>
#include "main.h"
using namespace std;

void makePlayerPlay(Board* board)
{ 
    int play = 0;
    cout << " Where do you play? ";
    cin >> play;
    if (play < 1 || play > BOARD_WIDTH){
        return;
    }
    board->play(play - 1);
}

void makeIAPlay(Board* board, unordered_map<std::string, PlayCalculator*>* playsHashMap)
{
    PlayCalculator* playCalculator = nullptr;
    if (playsHashMap->find(board->getBoardCode()) == playsHashMap->end())
    {
        playCalculator = new PlayCalculator(board, 0, MAX_DEPTH, playsHashMap);
        playCalculator->generateChildTime = 0;
    }
    else {
        playCalculator = (*playsHashMap)[board->getBoardCode()];
        playCalculator->setDepth(0);
    }
    playCalculator->generateChildTime = new std::chrono::duration<double>;
    *(playCalculator->generateChildTime) = std::chrono::seconds::zero();

    int i = 0;
    int remainingProcess = 0;
    auto start = chrono::system_clock::now();
    while (i < 1) {
        remainingProcess += 1000000;
        remainingProcess = playCalculator->process(remainingProcess);
        i++;
        cout << "\r";
        printf("Progess: %f\t Pos Calculated %d, %d                   ", playCalculator->getProgress(), playCalculator->getPositionCalculatedCount(), i);
        fflush(stdout);
    }
    auto stop = chrono::system_clock::now();
    cout << endl;
    cout << "--------------------------" << endl;
    playCalculator->print(2);
    cout << endl << "--------------------------" << endl;
    playCalculator->printEndGame();
    playCalculator->printBestPlay();

    int* playsRanking = playCalculator->getPlaysRanking();
    for (int i = 0; i < BOARD_WIDTH; i++) {
        if (playsRanking[i] == -1)
        {
            continue;
        }
        cout << playsRanking[i] + 1 << ": " << formatScore(playCalculator->getChild(playsRanking[i])->getScore()) << ",   ";
    }
    cout << endl;
    cout << formatScore(playCalculator->getScore()) << endl;
    cout << playCalculator->generateChildTime->count() << endl;
    chrono::duration<double> diffTime = stop - start;
    cout << diffTime.count() << endl;
    board->play(playCalculator->getBestPlay());
}

int main()
{
    Board board = Board();
    unordered_map<std::string, PlayCalculator*>* playsHashMap = new unordered_map<string, PlayCalculator*>();
    while (true) {
        board >> cout;
        cout << "Board Score: " << board.getBoardScore() << endl;
        
        if (board.getNextPlayer() == PLAYER_TOKEN)
        {
            makePlayerPlay(&board);
        } else 
        {
            makeIAPlay(&board, playsHashMap);
        }

        char win = board.getWinPlayer();
        if (win != NO_TOKEN) {
            board >> cout;
            cout << "Game end" << endl;
            return 0;
        }
    }
    return 0;
}

