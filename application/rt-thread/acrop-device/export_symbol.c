#include <drivers/pin.h>
#include <rthw.h>
#include <stdlib.h>

RTM_EXPORT(rt_pin_mode);
RTM_EXPORT(rt_pin_write);
RTM_EXPORT(rt_pin_read);
RTM_EXPORT(rt_pin_get);

//rtc
RTM_EXPORT(rt_hw_cpu_reset);

//memory
RTM_EXPORT(malloc);
RTM_EXPORT(free);
RTM_EXPORT(realloc);
RTM_EXPORT(calloc);
