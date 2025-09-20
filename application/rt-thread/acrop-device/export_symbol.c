#include <drivers/pin.h>
#include <rthw.h>
#include <drivers/rtc.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <sys/select.h>
#include <signal.h>
#include "rt-atomic.h"



RTM_EXPORT(_ctype_);


RTM_EXPORT(strerror);
RTM_EXPORT(select);


//stdlib.h
RTM_EXPORT(getenv);
RTM_EXPORT(setenv);
RTM_EXPORT(unsetenv);

//stdio.h
RTM_EXPORT(remove);
RTM_EXPORT(vsprintf);
RTM_EXPORT(vsnprintf);
RTM_EXPORT(fflush);
RTM_EXPORT(strrchr);
RTM_EXPORT(strtod);
RTM_EXPORT(fprintf);
RTM_EXPORT(lrint);
RTM_EXPORT(fseeko);
RTM_EXPORT(fmod);
RTM_EXPORT(ftello);
RTM_EXPORT(signal);
RTM_EXPORT(strtok);
RTM_EXPORT(sscanf);
RTM_EXPORT(fread);
RTM_EXPORT(fopen);
RTM_EXPORT(fclose);
RTM_EXPORT(strcspn);
RTM_EXPORT(fputc);
RTM_EXPORT(freopen);
RTM_EXPORT(strspn);
RTM_EXPORT(hypot);

RTM_EXPORT(srand);

//memory
RTM_EXPORT(malloc);
RTM_EXPORT(free);
RTM_EXPORT(realloc);
RTM_EXPORT(calloc);

//math
RTM_EXPORT(fabs);
RTM_EXPORT(sqrt);
RTM_EXPORT(acos);
RTM_EXPORT(asin);
RTM_EXPORT(atan);
RTM_EXPORT(atan2);
RTM_EXPORT(cos);
RTM_EXPORT(exp);
RTM_EXPORT(log);
RTM_EXPORT(sin);
RTM_EXPORT(tan);
RTM_EXPORT(trunc);
RTM_EXPORT(cosh);
RTM_EXPORT(sinh);
RTM_EXPORT(tanh);
RTM_EXPORT(acosh);
RTM_EXPORT(expm1);
RTM_EXPORT(log1p);
RTM_EXPORT(log2);
RTM_EXPORT(log10);
RTM_EXPORT(cbrt);
RTM_EXPORT(asinh);
RTM_EXPORT(round);
RTM_EXPORT(ceil);
RTM_EXPORT(floor);
RTM_EXPORT(pow);
RTM_EXPORT(atanh);
RTM_EXPORT(fmin);
RTM_EXPORT(fmax);
RTM_EXPORT(atoi);


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

//rtc.h
RTM_EXPORT(get_timestamp);
RTM_EXPORT(set_timestamp);

RTM_EXPORT(rt_device_init);
RTM_EXPORT(rt_tick_get_millisecond);


//rt-atomic.h
RTM_EXPORT(__atomic_fetch_add_8);
RTM_EXPORT(__atomic_fetch_and_8);
RTM_EXPORT(__atomic_fetch_or_8);
RTM_EXPORT(__atomic_fetch_sub_8);
RTM_EXPORT(__atomic_fetch_xor_8);
RTM_EXPORT(__atomic_store_8);
RTM_EXPORT(__atomic_load_8);
RTM_EXPORT(__atomic_exchange_8);
RTM_EXPORT(__atomic_compare_exchange_8);
