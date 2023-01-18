#include "taskQueue.h"

TaskQueue::TaskQueue()
{

}

TaskQueue::~TaskQueue()
{
    clear();
}

void TaskQueue::addTask(PlayCalculator* play)
{
    TaskElement* task = new TaskElement{play, nullptr};
    if (lastTask != nullptr)
    {
        lastTask->next = task;
    }
    lastTask = task;
    size ++;
}

PlayCalculator* TaskQueue::popTask()
{
    if (isEmpty()) return nullptr;
    TaskElement* task = topTask;
    PlayCalculator* result = topTask->play;
    topTask = task->next;
    delete task;
    size --;
    if (isEmpty()) lastTask = nullptr;
    return result;
}

bool TaskQueue::isEmpty()
{
    return size == 0;
}

void TaskQueue::clear()
{
    while(!isEmpty()){
        popTask();
    }
}

int TaskQueue::getSize()
{
    return size;
}
