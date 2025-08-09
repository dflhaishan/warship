#include "xtrack_app.h"
#include "appfactory.h"
#include "pagemanager.h"
#include "resourcepool.h"
#include "millis_task_manager.h"
#include "lvgl.h"
#include "bsp.h"
#include "dataproc.h"
#include "hal.h"

extern uint32_t SystemTickCount;
#define SYSTICK_TICK_FREQ       (1000)
#define SYSTICK_TICK_INTERVAL   (1000 / SYSTICK_TICK_FREQ)
#define SYSTICK_MILLIS          (SystemTickCount * SYSTICK_TICK_INTERVAL)

static MillisTaskManager taskManager;

void LED1_Update()
{
    bsp_LedToggle(1);
}

void LED2_Update()
{
    bsp_LedToggle(2);
}

void xtrack_app_init(void)
{
    static AppFactory factory;
    static PageManager manager(&factory);

    DataProc_Init();

    manager.Install("Template",         "Pages/_Template");
    manager.Install("LiveMap",          "Pages/LiveMap");
    manager.Install("Dialplate",        "Pages/Dialplate");
    manager.Install("SystemInfos",      "Pages/SystemInfos");
    manager.Install("StartUp",         "Pages/StartUp");

    manager.SetGlobalLoadAnimType(PageManager::LOAD_ANIM_OVER_TOP, 500);

    manager.Push("Pages/Startup");

    taskManager.Register(HAL::Power_EventMonitor, 100);
    taskManager.Register(HAL::GPS_Update, 200);
    taskManager.Register(HAL::SD_Update, 500);
    taskManager.Register(HAL::Memory_DumpInfo, 1000);
    taskManager.Register(LED1_Update, 1000);
    taskManager.Register(LED2_Update, 500);
}

void xtrack_app_update(void)
{
    taskManager.Running(SYSTICK_MILLIS);
}