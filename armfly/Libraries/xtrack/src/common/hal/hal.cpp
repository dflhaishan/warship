#include "hal.h"
#include "version.h"
#include "millis_task_manager.h"

static MillisTaskManager taskManager;

void HAL::HAL_Init()
{
    Serial.begin(115200);
    Serial.println(VERSION_FIRMWARE_NAME);
    Serial.println("Version: " VERSION_SOFTWARE);
    Serial.println("Author: "  VERSION_AUTHOR_NAME);
    Serial.println("Project: " VERSION_PROJECT_LINK);

    FaultHandle_Init();

    Memory_DumpInfo();

    Power_Init();
    Backlight_Init();
    Encoder_Init();
    Clock_Init();
    Buzz_init();
    GPS_Init();
#if CONFIG_SENSOR_ENABLE
    HAL_Sensor_Init();
#endif
    Audio_Init();
    SD_Init();

    Display_Init();

    taskManager.Register(Power_EventMonitor, 100);
    taskManager.Register(GPS_Update, 200);
    taskManager.Register(SD_Update, 500);
#if CONFIG_SENSOR_ENABLE
    taskManager.Register(HAL_SensorUpdate, 1000);
#endif
    taskManager.Register(Memory_DumpInfo, 1000);

    // Timer_SetInterrupt(CONFIG_HAL_UPDATE_TIM, 10 * 1000, HAL_TimerInterrputUpdate);
    // Timer_SetEnable(CONFIG_HAL_UPDATE_TIM, true);   
}

void HAL::HAL_Update()
{
    taskManager.Running(millis());
}
