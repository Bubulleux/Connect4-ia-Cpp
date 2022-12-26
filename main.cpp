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
    while (i < 30) {
        int remainingProcess = playCalculator.process(50000);
        i++;
        cout << "\r";
        printf("Progess: %f\t Pos Calculated %d                   ", playCalculator.getProgress(), playCalculator.getPositionCalculatedCount());
        if (remainingProcess != 0)
        {
            break;
        }
    }
    cout << endl << endl;
    playCalculator.print(2); 
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

