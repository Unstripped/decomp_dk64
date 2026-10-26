#include "common.h"

f32 func_80612D1C(f32);

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

s32 oscInit(GbNode **out, f32 *arg1, u8 type, u8 arg3, u8 arg4, u8 arg5) {
    GbNode *node;
    s32 ret = 0;

    if (arg5 == 0) {
        return 0;
    }
    if (D_807FF030) {
        node = D_807FF030;
        D_807FF030 = D_807FF030->next;
        node->type = type;
        *out = node;
        ret = arg5 << 14;
        switch (type) {
        case 1:
            node->unk24 = 0;
            node->unk22 = 0x103 - arg3;
            node->unk28.u.b = arg4 >> 1;
            node->unk28.u.c = 0x7F - node->unk28.u.b;
            *arg1 = node->unk28.u.c;
            break;
        case 0x80:
            node->unk28.f = oscVibratoDepthPow(arg4);
            node->unk24 = 0;
            node->unk22 = 0x103 - arg3;
            *arg1 = 1.0f;
            break;
        default:
            break;
        }
    }
    return ret;
}

s32 oscUpdate(GbNode *arg0, f32 *arg1) {
    f32 f;
    GbNode *node = arg0;
    s32 ret = 0x3E80;

    switch (node->type) {
    case 1:
        node->unk24++;
        if (node->unk24 >= node->unk22) {
            node->unk24 = 0;
        }
        f = (f32)node->unk24 / (f32)node->unk22;
        f = func_80612D1C(f * 6.283185482f);
        f = (f32)node->unk28.u.b * f;
        *arg1 = (f32)node->unk28.u.c + f;
        break;
    case 0x80:
        node->unk24++;
        if (node->unk24 >= node->unk22) {
            node->unk24 = 0;
        }
        f = (f32)node->unk24 / (f32)node->unk22;
        f = func_80612D1C(f * 6.283185482f) * node->unk28.f;
        *arg1 = alCents2Ratio((s32)f);
        break;
    default:
        break;
    }
    return ret;
}

void oscStop(GbNode *arg0) {
    GbNode *node = arg0;

    arg0->next = D_807FF030;
    D_807FF030 = arg0;
}

f32 oscSinAngle(f32 arg0) {
    return func_80612D1C(arg0 / 10430.37988f);
}

void oscSetupConfig(ALSeqpConfig *arg0, s32 count) {
    GbNode *ptr;
    s32 i;

    D_807FF030 = D_807FF034 = alHeapDBAlloc(NULL, 0, arg0->heap, count, 0x2C);
    D_807FF030 = D_807FF034;
    ptr = D_807FF034;
    for (i = 0; i < count - 1; i++) {
        ptr->next = D_807FF034 + i + 1;
        ptr = ptr->next;
    }
    ptr->next = NULL;
    arg0->initOsc = oscInit;
    arg0->updateOsc = oscUpdate;
    arg0->stopOsc = oscStop;
}
