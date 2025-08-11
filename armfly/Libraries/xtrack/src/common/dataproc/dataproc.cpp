#include "dataproc.h"
#include "hal.h"

static DataCenter center("CENTER");

DataCenter* DataProc::Center()
{
    return &center;
}

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
    _DP_Storage_Init(actClock);
    _DP_Storage_Init(actGPS);
    _DP_Storage_Init(actPower);
    _DP_Storage_Init(actSportStatus);
    _DP_Storage_Init(actRecorder);
    _DP_Storage_Init(actIMU);
    _DP_Storage_Init(actMAG);
    _DP_Storage_Init(actStatusBar);
    _DP_Storage_Init(actMusicPlayer);
    _DP_Storage_Init(actTzConv);
    _DP_Storage_Init(actSysConfig);
    _DP_Storage_Init(actTrackFilter);
}
