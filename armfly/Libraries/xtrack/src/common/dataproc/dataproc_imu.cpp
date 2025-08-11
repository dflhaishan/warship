#include "dataproc.h"
#include "hal.h"

#if 1
void _DP_IMU_Init(Account* account)
{
    HAL::IMU_SetCommitCallback([](void* info, void* userData){
        Account* account = (Account*)userData;
        return account->Commit(info, sizeof(HAL::IMU_Info_t));
    }, account);
}
#else
DATA_PROC_INIT_DEF(IMU)
{
    HAL::IMU_SetCommitCallback([](void* info, void* userData){
        Account* account = (Account*)userData;
        return account->Commit(info, sizeof(HAL::IMU_Info_t));
    }, account);
}
#endif