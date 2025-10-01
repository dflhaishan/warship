#include "hal.h"
#include "xtrack_config.h"
#include "SdFat.h"

static SdFatSdio SD;

static bool SD_IsReady = false;

static void SD_GetDataTime(uint16_t *data, uint16_t *time)
{
    HAL::Clock_Info_t clock;
    HAL::Clock_GetInfo(&clock);

    *data = FAT_DATE(clock.year, clock.month, clock.day);

    *time = FAT_TIME(clock.hour, clock.minute, clock.second);
}

static bool SD_CheckDir(const char *path)
{
    bool ret = true;
    if (!SD.exists(path))
    {
        Serial.printf("SD: Auo create path \"%s\"...", path);
        ret = SD.mkdir(path);
        Serial.println(ret ? "success" : "failed");
    }
    return ret;
}

bool HAL::SD_Init()
{
    bool ret = true;
    Serial.println("SD: init...");
    ret = SD.begin();

    if (ret)
    {
        SdFile::dateTimeCallback(SD_GetDataTime);
        SD_CheckDir(CONFIG_TRACK_RECORD_FILE_DIR_NAME);
        Serial.printf("SD: init success, Type : %s, Size %d MB\r\n", 
                        SD_GetTypeName(),
                        SD.card()->cardCapacity());
    }
    else
    {
        Serial.println("failed");
    }

    SD_IsReady = ret;
    return ret;
}

bool HAL::SD_GetReady()
{
    return SD_IsReady;
}

float HAL::SD_GetCardSizeMB()
{
    float size = SD.card()->cardCapacity();
    return size;
}

const char* HAL::SD_GetTypeName()
{
    const char *type = "Unknown";

    if (!SD.card()->cardCapacity())
    {
        goto failed;
    }

    switch (SD.card()->type())
    {
        case SD_CARD_TYPE_SD1:
            type = "SD1";
            break;

        case SD_CARD_TYPE_SD2:
            type = "SD2";
            break;

        case SD_CARD_TYPE_SDHC:
            type = (SD.card()->cardCapacity() < 70000000) ? "SDHC" : "SDXC";
            break;

        default:
            break;
    }

failed:
    return type;
}

void HAL::SD_SetEventCallback(SD_CallbackFunction_t callback)
{

}

void HAL::SD_Update()
{
    
}

#if 0
static void SD_Check(bool isInsert)
{
   
}
#endif
