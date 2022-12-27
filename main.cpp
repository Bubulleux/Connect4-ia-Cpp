#include <algorithm>
#include <cstdio>
#include <iostream>
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

void makeIAPlay(Board* board)
{
    PlayCalculator playCalculator = PlayCalculator(*board, 0, MAX_DEPTH);
    int i = 0;
    int remainingProcess = 0;
    while (i < 20) {
        remainingProcess += 50000;
        remainingProcess = playCalculator.process(remainingProcess);
        i++;
        cout << "\r";
        printf("Progess: %f\t Pos Calculated %d, %d                   ", playCalculator.getProgress(), playCalculator.getPositionCalculatedCount(), i);
        fflush(stdout);
    }
    cout << endl;
    cout << "--------------------------" << endl;
    playCalculator.print(2);
    cout << endl << "--------------------------" << endl;
    playCalculator.printEndGame();
    playCalculator.printBestPlay();

    int* playsRanking = playCalculator.getPlaysRanking();
    for (int i = 0; i < BOARD_WIDTH; i++) {
        if (playsRanking[i] == -1)
        {
            continue;
        }
        cout << playsRanking[i] + 1 << ": " << formatScore(playCalculator.getChild(playsRanking[i]).getScore()) << ",   ";
    }
    cout << endl;
    cout << formatScore(playCalculator.getScore()) << endl;
    board->play(playCalculator.getBestPlay());
}

int main()
{
    Board board = Board();
    while (true) {
        board >> cout;
        cout << "Board Score: " << board.getBoardScore() << endl;
        
        if (board.getNextPlayer() == PLAYER_TOKEN)
        {
            makePlayerPlay(&board);
        } else 
        {
            makeIAPlay(&board);
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

