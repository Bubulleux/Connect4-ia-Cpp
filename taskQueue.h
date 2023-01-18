#include "playCalculator.h"

struct TaskElement
{
    PlayCalculator* play;
    TaskElement* next;
};

class TaskQueue
{
    public:
        TaskQueue();
        ~TaskQueue();

        void addTask(PlayCalculator* play);
        PlayCalculator* popTask();
        bool isEmpty();
        void clear();
        int getSize();

    private:
        TaskElement* topTask;
        TaskElement* lastTask;
        int size;
};




