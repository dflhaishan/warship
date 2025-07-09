#ifndef __MILLISTASKMANAGER_H
#define __MILLISTASKMANAGER_H

#define MTM_USE_CPU_USAGE   0

#include <stdint.h>

class MillisTaskManager
{
public:
    typedef void (*TaskFunction_t)(void);
    struct Task
    {
        bool State;
        TaskFunction_t Function;
        uint32_t Time;
        uint32_t TimePrev;
        uint32_t TimeCost;
        uint32_t TimeError;
        struct Task* Next;
    };
    typedef struct Task Task_t;

    MillisTaskManager(bool priorityEnable = false);
    ~MillisTaskManager();

    Task_t* Register(TaskFunction_t func, uint32_t timeMs, bool State = true);
    Task_t* Find(TaskFunction_t func);
    Task_t* GetPrev(Task_t *task);
    bool Logout(TaskFunction_t func);
    bool SetState(TaskFunction_t func, bool state);
    bool SetIntervalTime(TaskFunction_t func, uint32_t timeMs);
    uint32_t GetTimeCost(TaskFunction_t func);
    uint32_t GetTickElaps(uint32_t nowTick, uint32_t prevTick);
#if (MTM_USE_CPU_USAGE == 1)
    float GetCPU_Usage();
#endif
    void Running(uint32_t tick);

private:
    Task_t* Head;
    Task_t* Tail;
    bool PriorityEnable;

};

#endif