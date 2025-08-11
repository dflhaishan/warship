#include "dataproc.h"
#include "hal.h"

void _DP_MAG_Init(Account* account)
{
    HAL::MAG_SetCommitCallback([](void* info, void* userData){
        Account* account = (Account*)userData;
        return account->Commit(info, sizeof(HAL::MAG_Info_t));
    }, account);
}
