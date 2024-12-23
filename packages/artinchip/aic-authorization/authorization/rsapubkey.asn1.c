/*
 * Copyright (c) 2022-2024, ArtInChip Technology Co., Ltd
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Authors: Xiong Hao <hao.xiong@artinchip.com>
 */

#include <asn1_ber_bytecode.h>
#include "rsapubkey.asn1.h"

enum rsapubkey_actions {
    ACT_rsa_get_e = 0,
    ACT_rsa_get_n = 1,
    NR__rsapubkey_actions = 2
};

static const asn1_action_t rsapubkey_action_table[NR__rsapubkey_actions] = {
    [0] = rsa_get_e,
    [1] = rsa_get_n,
};

static const unsigned char rsapubkey_machine[] = {
    // RsaPubKey
    [0] = ASN1_OP_MATCH,
    [1] = _tag(UNIV, CONS, SEQ),
    [2] = ASN1_OP_MATCH_ACT, // n
    [3] = _tag(UNIV, PRIM, INT),
    [4] = _action(ACT_rsa_get_n),
    [5] = ASN1_OP_MATCH_ACT, // e
    [6] = _tag(UNIV, PRIM, INT),
    [7] = _action(ACT_rsa_get_e),
    [8] = ASN1_OP_END_SEQ,
    [9] = ASN1_OP_COMPLETE,
};

const struct asn1_decoder rsapubkey_decoder = {
    .machine = rsapubkey_machine,
    .machlen = sizeof(rsapubkey_machine),
    .actions = rsapubkey_action_table,
};
