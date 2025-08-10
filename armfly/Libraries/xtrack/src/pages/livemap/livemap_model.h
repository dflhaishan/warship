#ifndef __LIVEMAP_MODEL_H
#define __LIVEMAP_MODEL_H

#include "lvgl.h"
#include "mapconv.h"
#include "tileconv.h"
#include "trackfilter.h"
#include "dataproc.h"
#include <vector>

namespace Page
{

class LiveMapModel
{
public:
    LiveMapModel();
    ~LiveMapModel() {}
    void Init();
    void Deinit();
    void GetGPS_Info(HAL::GPS_Info_t* info);
    void GetArrowTheme(char* buf, uint32_t size);

    bool GetTrackFilterActive()
    {
        DataProc::TrackFilter_Info_t info;
        account->Pull("TrackFilter", &info, sizeof(info));
        return info.isActive;
    }
 
    void TrackReload(TrackPointFilter::Callback_t callback, void* userData);

public:
    MapConv mapConv;
    TileConv tileConv;
    TrackPointFilter pointFilter;
    TrackLineFilter lineFilter;
    HAL::SportStatus_Info_t sportStatusInfo;
    
private:
    Account* account;

private:
    static int onEvent(Account* account, Account::EventParam_t* param);

private:
};

}

#endif
