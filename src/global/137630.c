#include "common.h"
#include "proto/global/137120.h"
#include "proto/global/137630.h"
#include "proto/global/13ECE0.h"


f32 sinApprox(f32);

enum OscType {
    OSC_TREMOLO_SIN = 0x01,
    OSC_VIBRATO_SIN = 0x80
};

typedef struct OscState_s {
    struct OscState_s *next;
    u8 type;
    u8 pad5[0x22 - 5];
    u16 maxCount;
    u16 curCount;
    u8 pad26[2];
    union {
        struct {
            u8 halfDepth;
            u8 baseVol;
        } tremolo;
        f32 depthCents;
    } data;
} OscState;

extern OscState *D_807FF030;
extern OscState *D_807FF034;

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

ALMicroTime oscInit(void **oscState, f32 *initVal, u8 type, u8 rate, u8 depth, u8 delay) {
    OscState *osc;
    ALMicroTime ret = 0;

    if (delay == 0) {
        return 0;
    }
    if (D_807FF030) {
        osc = D_807FF030;
        D_807FF030 = D_807FF030->next;
        osc->type = type;
        *oscState = osc;
        ret = delay << 14;
        switch (type) {
        case OSC_TREMOLO_SIN:
            osc->curCount = 0;
            osc->maxCount = 259 - rate;
            osc->data.tremolo.halfDepth = depth >> 1;
            osc->data.tremolo.baseVol = 127 - osc->data.tremolo.halfDepth;
            *initVal = osc->data.tremolo.baseVol;
            break;
        case OSC_VIBRATO_SIN:
            osc->data.depthCents = oscVibratoDepthPow(depth);
            osc->curCount = 0;
            osc->maxCount = 259 - rate;
            *initVal = 1.0f;
            break;
        default:
            break;
        }
    }
    return ret;
}

ALMicroTime oscUpdate(void *oscState, f32 *updateVal) {
    f32 f;
    OscState *osc = oscState;
    ALMicroTime ret = 16000;

    switch (osc->type) {
    case OSC_TREMOLO_SIN:
        osc->curCount++;
        if (osc->curCount >= osc->maxCount) {
            osc->curCount = 0;
        }
        f = (f32)osc->curCount / (f32)osc->maxCount;
        f = sinApprox(f * 6.283185482f);
        f = osc->data.tremolo.halfDepth * f;
        *updateVal = osc->data.tremolo.baseVol + f;
        break;
    case OSC_VIBRATO_SIN:
        osc->curCount++;
        if (osc->curCount >= osc->maxCount) {
            osc->curCount = 0;
        }
        f = (f32)osc->curCount / (f32)osc->maxCount;
        f = sinApprox(f * 6.283185482f) * osc->data.depthCents;
        *updateVal = alCents2Ratio((s32)f);
        break;
    default:
        break;
    }
    return ret;
}

void oscStop(void *oscState) {
    OscState *osc = oscState;

    ((OscState *)oscState)->next = D_807FF030;
    D_807FF030 = oscState;
}

f32 oscSinAngle(f32 angle) {
    return sinApprox(angle / 10430.37988f);
}

void oscSetupConfig(ALSeqpConfig *config, s32 count) {
    OscState *ptr;
    s32 i;

    D_807FF030 = D_807FF034 = alHeapAlloc(config->heap, count, sizeof(OscState));
    D_807FF030 = &D_807FF034[0];
    ptr = D_807FF034;
    for (i = 0; i < count - 1; i++) {
        ptr->next = &D_807FF034[i + 1];
        ptr = ptr->next;
    }
    ptr->next = NULL;
    config->initOsc = oscInit;
    config->updateOsc = oscUpdate;
    config->stopOsc = oscStop;
}
