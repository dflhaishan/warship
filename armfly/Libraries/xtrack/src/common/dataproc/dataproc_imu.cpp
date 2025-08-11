#include "dataproc.h"
#include "hal.h"

void _DP_IMU_Init(Account* account)
{
    HAL::IMU_SetCommitCallback([](void* info, void* userData){
        Account* account = (Account*)userData;
        return account->Commit(info, sizeof(HAL::IMU_Info_t));
    }, account);
}
