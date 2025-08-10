#ifndef __STARTUP_MODEL_H
#define __STARTUP_MODEL_H

#include "dataproc.h"
#include "hal.h"

namespace Page
{

class StartupModel
{
public:
    void Init();
    void Deinit();
    void PlayMusic(const char* music);
    void SetEncoderEnable(bool en)
    {
        HAL::Encoder_SetEnable(en);
    }

private:
    Account* account;
};

}

#endif
