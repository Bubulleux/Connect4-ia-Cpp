#include "threader.h"
#include <future>
#include <thread>

Threader::Threader(int threadCount, short depth)
{
    this->depth = depth;
    this->threadCount = threadCount;
    nextThreadIndex = 0;
    taskQueue = new TaskQueue[threadCount];
}

Threader::~Threader()
{
    delete [] taskQueue;
}

void Threader::addTask(PlayCalculator *play)
{
    taskQueue[nextThreadIndex].addTask(play);
    incrementThreadIndex();
}

void Threader::clearTask()
{
    for (int i = 0; i < threadCount; i++){
        taskQueue[i].clear();
    }
}

void Threader::process()
{
    std::thread threads[threadCount];

    for (int i = 0; i < threadCount; i++){
        threads[i] = std::thread(processTaskQueue,this, i);
    }
    for (int i = 0; i < threadCount; i++){
        threads[i].join();
    }
}

void Threader::incrementThreadIndex()
{
    nextThreadIndex++;
    nextThreadIndex %= threadCount;
}

void processTaskQueue(Threader* threader, int index)
{

}
