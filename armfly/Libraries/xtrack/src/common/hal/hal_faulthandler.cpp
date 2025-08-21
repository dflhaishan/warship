#include "hal.h"
#include "version.h"
#include "cm_backtrace.h"

static void Reboot(void)
{
    NVIC_SystemReset();
}

void HAL::FaultHandle_Init(void)
{
    cm_backtrace_init(
        VERSION_FIRMWARE_NAME,
        VERSION_HARDWARE,
        VERSION_SOFTWARE
    );
}

void cmb_printf(const char *__restrict __format, ...)
{
    char printf_buf[256];

    va_list args;
    va_start(args, __format);
    vsnprintf(printf_buf, sizeof(printf_buf), __format, args);
    va_end(args);

    Serial.print(printf_buf);
}

extern "C"
{
    void vApplicationHardFaultHook(void)
    {
        HAL::Display_DumpCrashInfo("FXXK HardFault!");
        Reboot();
    }

    void HardFault_Handler(void)
    {
        asm volatile (            
        "mov r0, lr;"
        "mov r1, sp;"
        "bl cm_backtrace_fault;"
        "bl vApplicationHardFaultHook;"
        
        "fault_loop:\n\t"
        "b fault_loop;"
        );
    }
}