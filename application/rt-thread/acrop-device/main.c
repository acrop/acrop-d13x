/*
 * Copyright (c) 2022-2024, ArtInChip Technology Co., Ltd
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Authors: weilin.peng@artinchip.com
 */

#include <rtthread.h>
#ifdef RT_USING_ULOG
#include <ulog.h>
#endif

#include "main.h"

int main(void)
{
#ifdef ULOG_USING_FILTER
    ulog_global_filter_lvl_set(ULOG_OUTPUT_LVL);
#endif
    //appimg_enter();
    return 0;
}
