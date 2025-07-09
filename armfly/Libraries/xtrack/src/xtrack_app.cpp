#include "xtrack_app.h"
#include "appfactory.h"
#include "pagemanager.h"
#include "resourcepool.h"
#include "millis_task_manager.h"
#include "lvgl.h"
#include "bsp.h"

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

    taskManager.Register(LED1_Update, 1000);
    taskManager.Register(LED2_Update, 500);
}

void xtrack_app_update(void)
{
    taskManager.Running(SYSTICK_MILLIS);
}