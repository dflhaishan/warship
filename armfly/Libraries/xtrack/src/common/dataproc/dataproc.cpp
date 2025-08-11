#include "dataproc.h"
#include "hal.h"
#include "datacenter_log.h"

static DataCenter center("CENTER");

DataCenter* DataProc::Center()
{
    return &center;
}

#if 1
void DataProc_Init()
{
    Account* actStorage = new Account("Storage", &center, 0);
    Account* actClock = new Account("Clock", &center, 0);
    Account* actGPS = new Account("GPS", &center, sizeof(HAL::GPS_Info_t));
    Account* actPower = new Account("Power", &center, 0);
    Account* actSportStatus = new Account("SportStatus", &center, sizeof(HAL::SportStatus_Info_t));
    Account* actRecorder = new Account("Recorder", &center, 0);
    Account* actIMU = new Account("IMU", &center, sizeof(HAL::IMU_Info_t));
    Account* actMAG = new Account("MAG", &center, sizeof(HAL::MAG_Info_t));
    Account* actStatusBar = new Account("StatusBar", &center, 0);
    Account* actMusicPlayer = new Account("MusicPlayer", &center, 0);
    Account* actTzConv = new Account("TzConv", &center, 0);
    Account* actSysConfig = new Account("SysConfig", &center, 0);
    Account* actTrackFilter = new Account("TrackFilter", &center, 0);    

    _DP_Storage_Init(actStorage);
    _DP_Clock_Init(actClock);
    _DP_GPS_Init(actGPS);
    _DP_Power_Init(actPower);
    _DP_SportStatus_Init(actSportStatus);
    _DP_Recorder_Init(actRecorder);
    _DP_IMU_Init(actIMU);
    _DP_MAG_Init(actMAG);
    _DP_StatusBar_Init(actStatusBar);
    _DP_MusicPlayer_Init(actMusicPlayer);
    _DP_TzConv_Init(actTzConv);
    _DP_SysConfig_Init(actSysConfig);
    _DP_TrackFilter_Init(actTrackFilter);
}
#else

void DataProc_Init()
{
#define DP_DEF(NODE_NAME, BUFFER_SIZE)\
    Account* act##NODE_NAME = new Account(#NODE_NAME, &center, BUFFER_SIZE);
#  include "dp_list.inc"
#undef DP_DEF

#define DP_DEF(NODE_NAME, BUFFER_SIZE)\
do{\
    DATA_PROC_INIT_DEF(NODE_NAME);\
    _DP_##NODE_NAME##_Init(act##NODE_NAME);\
}while(0)
#  include "dp_list.inc"
#undef DP_DEF

}

#endif