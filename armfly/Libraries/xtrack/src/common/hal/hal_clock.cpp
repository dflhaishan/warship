#include "hal.h"
#include "stm32f1xx_hal_rtc.h"

static RTC_HandleTypeDef RTC_Handler;

void HAL_RTC_MspInit(RTC_HandleTypeDef *hrtc)
{
    RCC_OscInitTypeDef RCC_OscInitStructure;
    RCC_PeriphCLKInitTypeDef PeriphClkInitStruct;

    __HAL_RCC_PWR_CLK_ENABLE();
    HAL_PWR_EnableBkUpAccess();
    __HAL_RCC_BKP_CLK_ENABLE();

    RCC_OscInitStructure.OscillatorType = RCC_OSCILLATORTYPE_LSE;
    RCC_OscInitStructure.PLL.PLLState = RCC_PLL_NONE;
    RCC_OscInitStructure.LSEState = RCC_LSE_ON;
    HAL_RCC_OscConfig(&RCC_OscInitStructure);

    PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_RTC;
    PeriphClkInitStruct.RTCClockSelection = RCC_RTCCLKSOURCE_LSE;
    HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct);

    __HAL_RCC_RTC_ENABLE();
}

void RTC_Init(void)
{
    RTC_DateTypeDef sDate;
    RTC_TimeTypeDef sTime;
    RTC_Handler.Instance = RTC;
    RTC_Handler.Init.AsynchPrediv = RTC_AUTO_1_SECOND;
    RTC_Handler.State = HAL_RTC_STATE_RESET;
    sDate.Year = 25;
    sDate.Month = 9;
    sDate.Date = 21;
    sTime.Hours = 12;
    sTime.Minutes = 0;
    sTime.Seconds = 0;
    if (HAL_RTC_Init(&RTC_Handler) != HAL_OK)
    {
        return;
    }

    if (HAL_RTCEx_BKUPRead(&RTC_Handler, RTC_BKP_DR1) != 0x5050)
    {
        HAL_RTC_SetDate(&RTC_Handler, &sDate, RTC_FORMAT_BIN);
        HAL_RTC_SetTime(&RTC_Handler, &sTime, RTC_FORMAT_BIN);
        HAL_RTCEx_BKUPWrite(&RTC_Handler, RTC_BKP_DR1, 0x5050);
    }
}

void HAL::Clock_Init()
{
    RTC_Init();

    Clock_Info_t info;
    Clock_GetInfo(&info);
    Serial.printf(
        "Clock: %04d-%02d-%02d %s %02d:%02d:%02d\r\n",
        info.year,
        info.month,
        info.day,
        Clock_GetWeekString(info.week),
        info.hour,
        info.minute,
        info.second
    );
}

void HAL::Clock_GetInfo(Clock_Info_t* info)
{
    RTC_TimeTypeDef sTime;
    RTC_DateTypeDef sDate;

    HAL_RTC_GetTime(&RTC_Handler, &sTime, RTC_FORMAT_BIN);
    HAL_RTC_GetDate(&RTC_Handler, &sDate, RTC_FORMAT_BIN);
    
    info->year = 2000 + sDate.Year;
    info->month = sDate.Month;
    info->day = sDate.Date;
    info->week = sDate.WeekDay;
    info->hour = sTime.Hours;
    info->minute = sTime.Minutes;
    info->second = sTime.Seconds;
    info->millisecond = 0;
}

void HAL::Clock_SetInfo(const Clock_Info_t* info)
{
    RTC_DateTypeDef sDate;
    RTC_TimeTypeDef sTime;
    sDate.Year = info->year - 2000;
    sDate.Month = info->month;
    sDate.Date = info->day;
    sTime.Hours = info->hour;
    sTime.Minutes = info->minute;
    sTime.Seconds = info->second;
    HAL_RTC_SetDate(&RTC_Handler, &sDate, RTC_FORMAT_BIN);
    HAL_RTC_SetTime(&RTC_Handler, &sTime, RTC_FORMAT_BIN);

}

const char* HAL::Clock_GetWeekString(uint8_t week)
{
    const char* week_str[] = {"SUN", "MON", "TUE", "WED", "THU", "FRI", "SAT"};
    return week < 7 ? week_str[week] : "";
}
