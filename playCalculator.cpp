#include "playCalculator.h"
#include <algorithm>
#include <cstdint>
#include <string>


PlayCalculator::PlayCalculator(Board board, int depth, int maxDepth)
{
    this->board = board;
    this->depth = depth;
    this->maxDepth = maxDepth;
    boardStupidScore = board.getBoardScore();
    score = boardStupidScore;
    childGenerated = false;
    player = board.getNextPlayer();
    for (int i = 0; i < BOARD_WIDTH; i++) {
        childPlay[i] = nullptr;
    }
}


void PlayCalculator::setDepth(int newDepth) 
{
    depth = newDepth;
    for (int i = 0; i < BOARD_WIDTH; i++) {
        if (childPlay[i] != nullptr) {
            childPlay[i]->setDepth(newDepth + 1);
        }
    }
}

void PlayCalculator::setMaxDepth(int newMaxDepth)
{
    maxDepth = newMaxDepth;
    for (int i = 0; i < BOARD_WIDTH; i++) {
        if (childPlay[i] != nullptr) {
            childPlay[i]->setMaxDepth(maxDepth);
        }
    }
}

int PlayCalculator::process(int processCount)
{
    if (depth >= maxDepth || boardStupidScore == PLAYER_B_WIN || boardStupidScore == PLAYER_A_WIN)
    {
        return processCount;
    }
    int remainingProcess = processCount;

    remainingProcess =  generateChilds(remainingProcess);

    remainingProcess = processChild(remainingProcess);
    calculateChildScore();
    return remainingProcess;
}

int PlayCalculator::getScore()
{
    return score;
}

int* PlayCalculator::getPlaysScore()
{
    int* result = new int[BOARD_WIDTH];
    for (int i = 0; i < BOARD_WIDTH; i++) {
        if (childPlay[i] == nullptr)
        {
            continue;
        }
        result[i] = childPlay[i]->getScore();
    }
    return result;
}

int PlayCalculator::getBestPlay()
{
    int indexA = 0;
    int indexB = 0;
    int maxScore = PLAYER_B_WIN;
    int minScore = PLAYER_A_WIN;
    for (int i = 0; i < BOARD_WIDTH;  i++) {
        if (childPlay[i] == nullptr)
        {
            continue;
        }
        int currentScore = childPlay[i]->getScore();
        if (currentScore > maxScore)
        {
            maxScore = currentScore;
            indexA = i;
        }
        if (currentScore < minScore)
        {
            minScore = currentScore;
            indexB = i;
        }
    }
    return player == TOKEN_A ? indexA : indexB;
}

int PlayCalculator::getPositionCalculatedCount()
{
    int positionCalculatedCount = 1;
    for (int i = 0; i < BOARD_WIDTH; i++) {
        if (childPlay[i] == nullptr)
        {
            continue;
        }
        positionCalculatedCount += childPlay[i]->getPositionCalculatedCount();
    }
    return positionCalculatedCount;
}

float PlayCalculator::getProgress()
{
    if (depth >= maxDepth || boardStupidScore == PLAYER_A_WIN || boardStupidScore == PLAYER_B_WIN)
    {
        return 1.0;
    }
    float progess = 0.0;
    for (int i = 0; i < BOARD_WIDTH; i++) {
        if (childPlay[i] == nullptr)
        {
            progess += board.canPlayHere(i) ? 0 : 1.0 / (float)BOARD_WIDTH;
            continue;
        }
        progess += childPlay[i]->getProgress() / (float)BOARD_WIDTH;
    }
    return progess;
}

void PlayCalculator::print(int printMaxDepth)
{
    if (depth >= printMaxDepth)
    {
        return;
    }
    for (int i = 0; i < BOARD_WIDTH; i++) {
        if (childPlay[i] == nullptr)
        {
            continue;
        }
        for (int j = 0; j < depth; j++) {
            std::cout << "\t";
        }
        std::cout << i + 1 << ": " << formatScore(childPlay[i]->getScore()) << std::endl;
        childPlay[i]->print(printMaxDepth);
    }
}

std::string formatScore(int score)
{
    if (score > PLAYER_A_WIN - 500){
        return "AW" + std::to_string(PLAYER_A_WIN - score);
    }
    if (score < PLAYER_B_WIN + 500){
        return "BW" + std::to_string(score + PLAYER_B_WIN);
    }
    return std::to_string(score);
}

void PlayCalculator::calculateChildScore()
{
    if (!childGenerated)
    {
        score = boardStupidScore;
    }
    int minScore = PLAYER_A_WIN;
    int maxScore = PLAYER_B_WIN;
    for (int i = 0; i < BOARD_WIDTH; i++) {
        if (childPlay[i] == nullptr) {
            continue;
        }
        int currentScore = childPlay[i]->getScore();
        minScore = std::min(minScore, currentScore);
        maxScore = std::max(maxScore, currentScore);
    }
    score = player == TOKEN_A ? maxScore : minScore;
    if (score > PLAYER_A_WIN - 500)
    {
        score -= 1;
    }
    if (score < PLAYER_B_WIN + 500)
    {
        score += 1;
    }
}

int PlayCalculator::generateChilds(int processCount) {
    if (childGenerated || processCount == 0){
        return processCount;
    }
    int remainingProcess = processCount;
    
    for (int i = 0; i < BOARD_WIDTH; i++) { 
        bool sucess = generateChild(i);
        remainingProcess -= sucess ? 1 : 0;
        if (remainingProcess == 0)
        {
            return 0;
        }
    }
    childGenerated = true;
    return remainingProcess;
}

bool PlayCalculator::generateChild(int playPos)
{
    
    if (childPlay[playPos] != nullptr || !board.canPlayHere(playPos)){
        return false;
    }
    Board newBoard = board.copy();
    newBoard.play(playPos);
    childPlay[playPos] = new PlayCalculator(newBoard, depth + 1, maxDepth);
    return true;
}

int PlayCalculator::processChild(int processCount)
{
    int remainingProcess = processCount;
    for (int i = 0; i < BOARD_WIDTH; i++) {
        if (childPlay[i] == nullptr)
        {
            continue;
        }
        remainingProcess = childPlay[i]->process(remainingProcess);
    }
    return remainingProcess;
}

