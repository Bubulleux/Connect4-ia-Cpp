#include "taskQueue.h"
#include <future>

#define THREAD_COUNT 4

class Threader
{
    public:
        Threader(int threadCount, short depth);
        ~Threader();
        
        void addTask(PlayCalculator* play);
        void clearTask();
        void process();

    private:
        int threadCount;
        int nextThreadIndex;
        TaskQueue* taskQueue;
        void incrementThreadIndex();
};
