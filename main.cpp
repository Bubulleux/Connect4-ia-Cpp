#include <iostream>
#include "board.h"
using namespace std;

int main()
{
    cout << "Hello World" << endl;
    Board board;
    while (true) {
        board >> cout;
        int play = 0;
        cout << " Where do you play?";
        cin >> play;
        board.play(play - 1);
    }
    return 0;
}
