/*
 * Copyright (c) 2023, Artinchip Technology Co., Ltd
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Mingfeng.Li <mingfeng.li@artinchip.com>
 * Dehuang Wu <dehuang.wu@artinchip.com>
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <aic_common.h>

#define MAX_PARTITION_NAME 64
struct aic_partition {
    char name[MAX_PARTITION_NAME];
    u32 start;
    u32 size;
    struct aic_partition *next;
};

struct aic_partition *aic_part_mtd_parse(char *parts);
struct aic_partition *aic_part_gpt_parse(char *parts);
struct aic_partition *aic_part_get_byname(struct aic_partition *head, char *name);
void aic_part_free(struct aic_partition *head);
void aic_part_dump(struct aic_partition *head);
