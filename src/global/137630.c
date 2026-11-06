#include "common.h"

f32 sinApprox(f32);

f32 oscVibratoDepthPow(u8 n) {
    f32 base = 1.030992985f;
    f32 result = 1.0f;

    while (n != 0) {
        if (n & 1) {
            result = result * base;
        }
        base = base * base;
        n >>= 1;
    }
    return result;
}

struct GbNode_s;

typedef struct GbNode_s {
    struct GbNode_s *next;
    u8 type;
    u8 pad5[0x22 - 5];
    u16 unk22;
    u16 unk24;
    u8 pad26[2];
    union {
        struct {
            u8 b;
            u8 c;
        } u;
        f32 f;
    } unk28;
} GbNode;

extern GbNode *D_807FF030;
extern GbNode *D_807FF034;

s32 oscInit(GbNode **out, f32 *outVal, u8 type, u8 rate, u8 depth, u8 delay) {
    GbNode *node;
    s32 ret = 0;

    if (delay == 0) {
        return 0;
    }
    if (D_807FF030) {
        node = D_807FF030;
        D_807FF030 = D_807FF030->next;
        node->type = type;
        *out = node;
        ret = delay << 14;
        switch (type) {
        case 1:
            node->unk24 = 0;
            node->unk22 = 0x103 - rate;
            node->unk28.u.b = depth >> 1;
            node->unk28.u.c = 0x7F - node->unk28.u.b;
            *outVal = node->unk28.u.c;
            break;
        case 0x80:
            node->unk28.f = oscVibratoDepthPow(depth);
            node->unk24 = 0;
            node->unk22 = 0x103 - rate;
            *outVal = 1.0f;
            break;
        default:
            break;
        }
    }
    return ret;
}

s32 oscUpdate(GbNode *oscNode, f32 *outVal) {
    f32 f;
    GbNode *node = oscNode;
    s32 ret = 0x3E80;

    switch (node->type) {
    case 1:
        node->unk24++;
        if (node->unk24 >= node->unk22) {
            node->unk24 = 0;
        }
        f = (f32)node->unk24 / (f32)node->unk22;
        f = sinApprox(f * 6.283185482f);
        f = (f32)node->unk28.u.b * f;
        *outVal = (f32)node->unk28.u.c + f;
        break;
    case 0x80:
        node->unk24++;
        if (node->unk24 >= node->unk22) {
            node->unk24 = 0;
        }
        f = (f32)node->unk24 / (f32)node->unk22;
        f = sinApprox(f * 6.283185482f) * node->unk28.f;
        *outVal = alCents2Ratio((s32)f);
        break;
    default:
        break;
    }
    return ret;
}

void oscStop(GbNode *oscNode) {
    GbNode *node = oscNode;

    oscNode->next = D_807FF030;
    D_807FF030 = oscNode;
}

f32 oscSinAngle(f32 angle) {
    return sinApprox(angle / 10430.37988f);
}

void oscSetupConfig(ALSeqpConfig *config, s32 count) {
    GbNode *ptr;
    s32 i;

    D_807FF030 = D_807FF034 = alHeapDBAlloc(NULL, 0, config->heap, count, 0x2C);
    D_807FF030 = D_807FF034;
    ptr = D_807FF034;
    for (i = 0; i < count - 1; i++) {
        ptr->next = D_807FF034 + i + 1;
        ptr = ptr->next;
    }
    ptr->next = NULL;
    config->initOsc = oscInit;
    config->updateOsc = oscUpdate;
    config->stopOsc = oscStop;
}
