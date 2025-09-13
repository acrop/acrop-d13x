#include <drivers/pin.h>
#include <rthw.h>
#include <stdlib.h>
#include <aic_common.h>
#include <aic_time.h>

//rthw.h
RTM_EXPORT(rt_hw_cpu_reset);
RTM_EXPORT(rt_hw_cpu_shutdown);
RTM_EXPORT(rt_hw_stack_init);
RTM_EXPORT(rt_hw_context_switch);
RTM_EXPORT(rt_hw_context_switch_to);
RTM_EXPORT(rt_hw_context_switch_interrupt);
RTM_EXPORT(rt_hw_us_delay);


RTM_EXPORT(rt_pin_mode);
RTM_EXPORT(rt_pin_write);
RTM_EXPORT(rt_pin_read);
RTM_EXPORT(rt_pin_get);

//memory
RTM_EXPORT(malloc);
RTM_EXPORT(free);
RTM_EXPORT(realloc);
RTM_EXPORT(calloc);

//delay
RTM_EXPORT(aic_mdelay);
RTM_EXPORT(aic_udelay);
