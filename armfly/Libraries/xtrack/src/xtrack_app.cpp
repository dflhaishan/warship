#include "xtrack_app.h"
#include "appfactory.h"
#include "pagemanager.h"
#include "resourcepool.h"
#include "millis_task_manager.h"
#include "lvgl.h"
#include "bsp.h"
#include "dataproc.h"
#include "hal.h"
#include "resourcepool.h"
#include "statusbar.h"
#include "Arduino.h"
#include "WSerial.h"

extern uint32_t SystemTickCount;
#define SYSTICK_TICK_FREQ       (1000)
#define SYSTICK_TICK_INTERVAL   (1000 / SYSTICK_TICK_FREQ)
#define SYSTICK_MILLIS          (SystemTickCount * SYSTICK_TICK_INTERVAL)

static MillisTaskManager taskManager;

#define ACCOUNT_SEND_CMD(ACT, CMD)\
do{\
    DataProc::ACT##_Info_t info;\
    memset(&info, 0, sizeof(info));\
    info.cmd = DataProc::CMD;\
    DataProc::Center()->AccountMain.Notify(#ACT, &info, sizeof(info));\
}while(0)

void led1_update(void)
{
    bsp_LedToggle(1);
}

void led2_update(void)
{
    bsp_LedToggle(2);
}

void xtrack_app_init(void)
{
#if 0
    static AppFactory factory;
    static PageManager manager(&factory);

    DataProc_Init();

    do
    {
        DataProc::Storage_Info_t info;
        memset(&info, 0, sizeof(info));
        info.cmd = DataProc::STORAGE_CMD_LOAD;
        DataProc::Center()->AccountMain.Notify("Storage", &info, sizeof(info));
    }while(0);

    do
    {
        DataProc::SysConfig_Info_t info;
        memset(&info, 0, sizeof(info));
        info.cmd = DataProc::SYSCONFIG_CMD_LOAD;
        DataProc::Center()->AccountMain.Notify("SysConfig", &info, sizeof(info));
    }while(0);
    
    lv_obj_t* scr = lv_scr_act();
    lv_obj_remove_style_all(scr);
    lv_obj_clear_flag(scr, LV_OBJ_FLAG_SCROLLABLE);
    lv_disp_set_bg_color(lv_disp_get_default(), lv_color_black());

    ResourcePool::Init();

    StatusBar::Init(lv_layer_top());

    manager.Install("Template",         "Pages/_Template");
    manager.Install("LiveMap",          "Pages/LiveMap");
    manager.Install("Dialplate",        "Pages/Dialplate");
    manager.Install("SystemInfos",      "Pages/SystemInfos");
    manager.Install("Startup",          "Pages/Startup");

    manager.SetGlobalLoadAnimType(PageManager::LOAD_ANIM_OVER_TOP, 500);

    manager.Push("Pages/Startup");
#if 0
    taskManager.Register(HAL::Power_EventMonitor, 100);
    taskManager.Register(HAL::GPS_Update, 200);
    taskManager.Register(HAL::SD_Update, 500);
    taskManager.Register(HAL::Memory_DumpInfo, 1000);
#endif
    taskManager.Register(led1_update, 5000);
    taskManager.Register(led2_update, 1000);
#else
    Serial.begin(115200);
    Serial.println("hello world");
    Serial.print("this is a test\r\n");
#endif
}

void xtrack_app_update(void)
{
    taskManager.Running(SYSTICK_MILLIS);
}