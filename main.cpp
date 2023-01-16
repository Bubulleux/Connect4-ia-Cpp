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
    PlayCalculator* playCalculator = new PlayCalculator(board);

    int i = 0;
    int remainingProcess = 0;
    auto start = chrono::system_clock::now();
    auto now = start;
    bool canProcessMore = true;
    while (((chrono::duration<double>)(now - start)).count() < 30 && canProcessMore) {
        canProcessMore = playCalculator->process();
        now = chrono::system_clock::now();
        cout << "\r";
        printf("%d                          ", i);
        flush(cout);
        i++;
    }
    auto stop = chrono::system_clock::now();
    cout << endl;
    cout << "--------------------------" << endl;
    playCalculator->print(2);
    cout << endl << "--------------------------" << endl;
    playCalculator->printEndGame();
    playCalculator->printBestPlay();

    char* playsRanking = playCalculator->getPlaysRanking();
    for (char i = 0; i < BOARD_WIDTH; i++) {
        if (playsRanking[i] == NULL_PLAY)
        {
            continue;
        }
        cout << playsRanking[i] + 1 << ": " << formatScore(playCalculator->getChild(playsRanking[i])->getScore()) << ",   ";
    }
    cout << endl;
    cout << formatScore(playCalculator->getScore()) << endl;
    chrono::duration<double> diffTime = stop - start;
    cout << diffTime.count() << endl;
    char bestPlay = playCalculator->getBestPlay();
    if (bestPlay == NULL_PLAY)
    {
        printf("Error no best play\n");
        exit(1);
    }
    playCalculator->recursiveDelete();
    delete playCalculator;
    delete  [] playsRanking;
    board->play(bestPlay);
}

int main()
{
    Board board = Board(EXAMPLE_BOARD_5);
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

