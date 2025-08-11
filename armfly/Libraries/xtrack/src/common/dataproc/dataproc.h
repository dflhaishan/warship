#ifndef __DATA_PROC_H
#define __DATA_PROC_H

#include "datacenter.h"
#include "hal_def.h"
#include "dataproc_def.h"

#define DATA_PROC_INIT_DEF(name) void _DP_##name##_Init(Account* account)

void DataProc_Init();
void _DP_Storage_Init(Account* account);
void _DP_Clock_Init(Account* account);
void _DP_GPS_Init(Account* account);
void _DP_Power_Init(Account* account);
void _DP_SportStatus_Init(Account* account);
void _DP_Recorder_Init(Account* account);
void _DP_IMU_Init(Account* account);
void _DP_MAG_Init(Account* account);
void _DP_StatusBar_Init(Account* account);
void _DP_MusicPlayer_Init(Account* account);
void _DP_TzConv_Init(Account* account);
void _DP_SysConfig_Init(Account* account);
void _DP_TrackFilter_Init(Account* account);
namespace DataProc
{

DataCenter* Center();
uint32_t    GetTick();
uint32_t    GetTickElaps(uint32_t prevTick);
const char* MakeTimeString(uint64_t ms, char* buf, uint16_t len);

}

#endif
