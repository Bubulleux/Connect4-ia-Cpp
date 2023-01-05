#include "playCalculator.h"
#include <algorithm>
#include <chrono>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <unordered_map>
#include <math.h>
#include <thread>
using namespace std;

PlayCalculator::PlayCalculator(Board* board)
{
    new (this) PlayCalculator(board, 0, 0, new unordered_map<string, PlayCalculator*>);
}

PlayCalculator::PlayCalculator(Board* board, int depth, int maxDepth, std::unordered_map<std::string, PlayCalculator*>* playsHashMap)
{
    this->board = board->copy();
    this->depth = depth;
    this->maxDepth = maxDepth;
    this->playsHashMap = playsHashMap;
    boardStupidScore = board->getBoardScore();
    score = boardStupidScore;
    childGenerated = false;
    player = board->getNextPlayer();
    childCount = 0; 
    for (int i = 0; i < BOARD_WIDTH; i++) {
        childPlay[i] = nullptr;
    }
}

PlayCalculator::~PlayCalculator()
{
    delete board;
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

void PlayCalculator::process()
{
    process(maxDepth + 1);
}

void PlayCalculator::process(int processDepth)
{
    if (depth >= processDepth || depth >= MAX_DEPTH || getScore() < PLAYER_B_WIN + 500 || getScore() > PLAYER_A_WIN - 500) return;

    maxDepth = processDepth;
    childCount = 0;
    generateChilds();

    disableChilds();
    processChild();
    calculateChildScore();
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
    int indexA = -1;
    int indexB = -1;
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

int* PlayCalculator::getPlaysRanking()
{
    int* result = new int[BOARD_WIDTH];
    for (int i = 0; i < BOARD_WIDTH; i++) {
        result[i] = -1;
    }
    for (int i = 0; i < BOARD_WIDTH; i++) {
        if (childPlay[i] == nullptr)
        {
            continue;
        }
        int currentScore = childPlay[i]->getScore();
        result[i] = i;
        for (int j = i - 1; j >= 0; j--) {
            if (result[j] != -1 && (childPlay[result[j]]->getScore() > currentScore ^ player == TOKEN_B ))
            {
                continue;
            }
            int temp = result[j];
            result[j] = i;
            result[j + 1] = temp;
        }
    }
    return result;
}

int PlayCalculator::getPositionCalculatedCount()
{
    if (childCount != 0)
    {
        return childCount;
    }
    int childCount = 1;
    for (int i = 0; i < BOARD_WIDTH; i++) {
        if (childPlay[i] == nullptr)
        {
            continue;
        }
        childCount += childPlay[i]->getPositionCalculatedCount();
    }
    return childCount;
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
            progess += board->canPlayHere(i) ? 0 : 1.0 / (float)BOARD_WIDTH;
            continue;
        }
        progess += childPlay[i]->getProgress() / (float)BOARD_WIDTH;
    }
    return progess;
}

PlayCalculator* PlayCalculator::getChild(int index)
{
    return childPlay[index];
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
        std::cout << i + 1 << ": " << formatScore(childPlay[i]->getScore()) << "(" << childPlay[i]->getPositionCalculatedCount() << ")" << std::endl;
        childPlay[i]->print(printMaxDepth);
    }
}

void PlayCalculator::printBestPlay()
{
    printBestPlay(0);
    std::cout << std::endl;
}

void PlayCalculator::printBestPlay(int depth)
{
    int bestPlay = getBestPlay();
    if (bestPlay == -1) 
    {
        std::cout << formatScore(boardStupidScore);
        return;
    }
    std::cout << bestPlay + 1 << ":"<< formatScore(childPlay[bestPlay]->getScore()) << "(" << formatScore(boardStupidScore) << "),     ";
    childPlay[bestPlay]->printBestPlay(depth + 1);
}

void PlayCalculator::printEndGame()
{
    int bestPlay = getBestPlay();
    if (bestPlay == -1)
    {
        *board >> std::cout;
        calculateChildScore();
        std::cout << formatScore(getScore()) << ", " << formatScore(board->getBoardScore()) << "," << getPositionCalculatedCount() << "," << getPlayCount() << std::endl;
        return;
    }
    childPlay[bestPlay]->printEndGame();
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
    if (!childGenerated || getPlayCount() == 0)
    {
        score = boardStupidScore;
        return;
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

void PlayCalculator::generateChilds() {
    if (childGenerated) return;

    for (int i = 0; i < BOARD_WIDTH; i++) { 
        generateChild(i);
    }
    childGenerated = true;
}

void PlayCalculator::generateChild(int playPos)
{
    
    if (childPlay[playPos] != nullptr || !board->canPlayHere(playPos)) return;

    Board* newBoard = board->copy();
    newBoard->play(playPos);
    std::string boardString = newBoard->getBoardCode();
    if (playsHashMap->find(boardString) == playsHashMap->end())
    {
        childPlay[playPos] = new PlayCalculator(newBoard, depth + 1, maxDepth, playsHashMap);
        (*playsHashMap)[boardString] = childPlay[playPos];
    }
    else 
    {
        childPlay[playPos] = (*playsHashMap)[boardString];
    }
    delete newBoard;
}

int PlayCalculator::getPlayCount()
{
    if (!childGenerated)
    {
        return 0;
    }
    int result = 0;
    for (int i = 0; i < BOARD_WIDTH; i++) {
        if (childPlay[i] == nullptr)
        {
            continue;
        }
        result++;
    }
    return result;
}

int getMaxChild(int depth)
{
    return (int)(pow(2, (double)(- depth + MIN_DEPTH) * SLOP_MULTIPLYER)
            * (double)(BOARD_WIDTH - 2) + 2);
}

void PlayCalculator::disableChilds()
{
    if (maxDepth - depth < MIN_DEPTH) return;

    int maxChild = getMaxChild(maxDepth - depth);
    int previousMaxChild = getMaxChild(maxDepth - depth - 1);

    if (previousMaxChild == maxChild) return;
    
    if (depth == 0)
    {
        printf("%d\t%d\t%d", maxChild, previousMaxChild, maxDepth);
    }

    int* bestPlay = getPlaysRanking();
    for (int i = maxChild + 1; i < BOARD_WIDTH; i++) {
        if (bestPlay[i] == -1) continue;
        childPlay[bestPlay[i]] = nullptr;
    }
}

void PlayCalculator::processChild()
{
    for (int i = 0; i < BOARD_WIDTH; i++) {
        if (childPlay[i] == nullptr) continue;
        childPlay[i]->process(maxDepth);
    }
}

