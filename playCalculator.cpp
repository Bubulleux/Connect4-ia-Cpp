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
#include <future>
using namespace std;

PlayCalculator::PlayCalculator(Board* board)
{
    new (this) PlayCalculator(board, 0, 0, new unordered_map<string, PlayCalculator*>);
}

PlayCalculator::PlayCalculator(Board* board, unsigned short depth, unsigned short maxDepth, std::unordered_map<std::string, PlayCalculator*>* playsHashMap)
{
    this->board = board->copy();
    this->depth = depth;
    this->maxDepth = maxDepth;
    this->playsHashMap = playsHashMap;
    boardStupidScore = board->getBoardScore();
    score = 0;
    score = boardStupidScore;
    childGenerated = false;
    player = board->getNextPlayer();
    childCount = 0; 
    for (char i = 0; i < BOARD_WIDTH; i++) {
        childPlay[i] = nullptr;
    }
}

PlayCalculator::~PlayCalculator()
{
    delete board;
}

void PlayCalculator::recursiveDelete()
{
    for (char i = 0; i < BOARD_WIDTH; i++) {
        if (childPlay[i] == nullptr) continue;
        childPlay[i]->recursiveDelete();
        delete childPlay[i];
    }
}

void PlayCalculator::setDepth(unsigned short newDepth) 
{
    depth = newDepth;
    for (char i = 0; i < BOARD_WIDTH; i++) {
        if (childPlay[i] != nullptr) {
            childPlay[i]->setDepth(newDepth + 1);
        }
    }
}

bool PlayCalculator::process()
{
    return process(maxDepth + 1);
}

bool PlayCalculator::process(unsigned short processDepth)
{
    if (depth >= processDepth) return true;
    if (depth >= MAX_DEPTH || getScore() < PLAYER_B_WIN + 500 || getScore() > PLAYER_A_WIN - 500) return false;

    maxDepth = processDepth;
    childCount = 0;
    generateChilds();

    disableChilds();
    bool result = processChild();
    calculateChildScore();
    return result;
}

short PlayCalculator::getScore()
{
    return score;
}

short* PlayCalculator::getPlaysScore()
{
    short* result = new short[BOARD_WIDTH];
    for (char i = 0; i < BOARD_WIDTH; i++) {
        if (childPlay[i] == nullptr)
        {
            continue;
        }
        result[i] = childPlay[i]->getScore();
    }
    return result;
}

char PlayCalculator::getBestPlay()
{
    char indexA = NULL_PLAY;
    char indexB = NULL_PLAY;
    short maxScore = PLAYER_B_WIN;
    short minScore = PLAYER_A_WIN;
    for (char i = 0; i < BOARD_WIDTH;  i++) {
        if (childPlay[i] == nullptr)
        {
            continue;
        }
        short currentScore = childPlay[i]->getScore();
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

char* PlayCalculator::getPlaysRanking()
{
    char* result = new char[BOARD_WIDTH];
    for (char i = 0; i < BOARD_WIDTH; i++) {
        result[i] = NULL_PLAY;
    }
    for (short i = 0; i < BOARD_WIDTH; i++) {
        if (childPlay[i] == nullptr)
        {
            continue;
        }
        char currentScore = childPlay[i]->getScore();
        result[i] = i;
        for (short j = i - 1; j >= 0; j--) {
            if (result[j] != NULL_PLAY && (childPlay[result[j]]->getScore() > currentScore ^ player == TOKEN_B ))
            {
                continue;
            }
            char temp = result[j];
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
    for (char i = 0; i < BOARD_WIDTH; i++) {
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
    for (char i = 0; i < BOARD_WIDTH; i++) {
        if (childPlay[i] == nullptr)
        {
            progess += board->canPlayHere(i) ? 0 : 1.0 / (float)BOARD_WIDTH;
            continue;
        }
        progess += childPlay[i]->getProgress() / (float)BOARD_WIDTH;
    }
    return progess;
}

PlayCalculator* PlayCalculator::getChild(char index)
{
    return childPlay[index];
}

void PlayCalculator::print(unsigned short printMaxDepth)
{
    if (depth >= printMaxDepth)
    {
        return;
    }
    for (char i = 0; i < BOARD_WIDTH; i++) {
        if (childPlay[i] == nullptr)
        {
            continue;
        }
        for (unsigned short j = 0; j < depth; j++) {
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

void PlayCalculator::printBestPlay(unsigned short depth)
{
    char bestPlay = getBestPlay();
    if (bestPlay == NULL_PLAY) 
    {
        std::cout << formatScore(boardStupidScore);
        return;
    }
    std::cout << bestPlay + 1 << ":"<< formatScore(childPlay[bestPlay]->getScore()) << "(" << formatScore(boardStupidScore) << "),     ";
    childPlay[bestPlay]->printBestPlay(depth + 1);
}

void PlayCalculator::printEndGame()
{
    char bestPlay = getBestPlay();
    if (bestPlay == NULL_PLAY)
    {
        *board >> std::cout;
        calculateChildScore();
        std::cout << formatScore(getScore()) << ", " << formatScore(board->getBoardScore()) << "," << getPositionCalculatedCount() << "," << getPlayCount() << std::endl;
        return;
    }
    childPlay[bestPlay]->printEndGame();
}

std::string formatScore(short score)
{
    if (score > PLAYER_A_WIN - 500){
        return "AW" + std::to_string(PLAYER_A_WIN - score);
    }
    if (score < PLAYER_B_WIN + 500){
        return "BW" + std::to_string(score - PLAYER_B_WIN);
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
    short minScore = PLAYER_A_WIN;
    short maxScore = PLAYER_B_WIN;
    for (char i = 0; i < BOARD_WIDTH; i++) {
        if (childPlay[i] == nullptr) {
            continue;
        }
        char currentScore = childPlay[i]->getScore();
        minScore = (int)std::min((int)minScore, (int)currentScore);
        maxScore = (int)std::max((int)maxScore, (int)currentScore);
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

    for (char i = 0; i < BOARD_WIDTH; i++) { 
        generateChild(i);
    }
    childGenerated = true;
}

void PlayCalculator::generateChild(char playPos)
{
    
    if (childPlay[playPos] != nullptr || !board->canPlayHere(playPos)) return;

    Board* newBoard = board->copy();
    newBoard->play(playPos);
    std::string boardString = newBoard->getBoardCode();
    if (playsHashMap->find(boardString) == playsHashMap->end() || true)
    {
        childPlay[playPos] = new PlayCalculator(newBoard, depth + 1, maxDepth, playsHashMap);
        //(*playsHashMap)[boardString] = childPlay[playPos];
    }
    else 
    {
        childPlay[playPos] = (*playsHashMap)[boardString];
    }
    delete newBoard;
}

char PlayCalculator::getPlayCount()
{
    if (!childGenerated)
    {
        return 0;
    }
    char result = 0;
    for (char i = 0; i < BOARD_WIDTH; i++) {
        if (childPlay[i] == nullptr)
        {
            continue;
        }
        result++;
    }
    return result;
}

char getMaxChild(unsigned short depth)
{
    return (char)(pow(2, (double)(- depth + MIN_DEPTH) * SLOP_MULTIPLYER)
            * (double)(BOARD_WIDTH - 2) + 2);
}

short getMaxScoreDiif(unsigned short depth)
{
    return (short)(pow(2, (double)(-depth + 5) * 0.3) * 10.0);
}

void PlayCalculator::disableChilds()
{
    if (maxDepth - depth < 4) return;
    short maxScoreDiff = getMaxScoreDiif(maxDepth - depth);
    short previousMaxScoreDiff = getMaxScoreDiif(maxDepth - depth - 1);

    if (previousMaxScoreDiff - maxScoreDiff < 1) return;
    
    char* bestPlays = getPlaysRanking();
    if (bestPlays[0] == NULL_PLAY) return;
    char bestPlay = childPlay[bestPlays[0]]->getScore();

    for (char i = 1; i < BOARD_WIDTH; i++) {
        if (bestPlays[i] == NULL_PLAY 
                || abs(bestPlay - childPlay[bestPlays[i]]->getScore()) <= maxScoreDiff) continue;

        childPlay[bestPlays[i]]->recursiveDelete();
        delete childPlay[bestPlays[i]];
        childPlay[bestPlays[i]] = nullptr;
    }
    delete [] bestPlays;
}

bool PlayCalculator::processChild()
{
    char maxChild = getMaxChild(maxDepth - depth);
    if (maxChild < 4 && maxChild > 1)
    {
        return processChildAsync();
    }
    
    bool result = false;

    for (char i = 0; i < BOARD_WIDTH; i++) {
        if (childPlay[i] == nullptr) continue;
        result |= childPlay[i]->process(maxDepth);
    }
    return result;
}

bool PlayCalculator::processChildAsync()
{
    std::thread threads[BOARD_WIDTH];
    std::future<bool> results[BOARD_WIDTH];
    for (char i = 0; i < BOARD_WIDTH; i++)
    {
        if (childPlay[i] == nullptr) continue;
        std::promise<bool> promise;
        results[i] = promise.get_future();
        threads[i] = std::thread(newChildThread, childPlay[i], maxDepth, std::move(promise));
    }

    bool result = false;
    for (char i = 0; i < BOARD_WIDTH; i++)
    {
        if (!threads[i].joinable()) continue;
        threads[i].join();
        result |= results[i].get();
    }
    return result;
}

void newChildThread(PlayCalculator* child, unsigned short maxDepth, std::promise<bool> &&promise)
{
    bool result = child->process(maxDepth);
    promise.set_value(result);
}
