// func_8065EB10 (src/global/63810.c): stage 3: structure rewritten from asm (array-indexed D_80748430[idx].sub[i] loops, direct D_807F9070[D_80748A84] stores, s32 count); 316 vs 312 insns, no callee-saved s0/frame -8 (target saves s0 for accum, reloads u8 arg0 with lbu 0xB(sp), keeps u8 count with andi), D_80748430[idx] address recomputed 3x in target; EFF0 trick: direct array indexing instead of pointer locals
#include "common.h"
#include "actor.h"

typedef struct RenderB63810_LightEntry {
    s16 unk0;
    u8 pad2[2];
    f32 unk4;
    f32 unk8;
    f32 unkC;
    s16 unk10;
    s16 unk12;
    s16 unk14;
    u8 unk16;
    u8 unk17;
    u8 unk18;
    u8 pad19[3];
} RenderB63810_LightEntry;

typedef struct RenderB63810_KeyFrame {
    f32 unk0;
    u8 r;
    u8 g;
    u8 b;
    u8 pad7;
    s16 unk8;
    s16 unkA;
} RenderB63810_KeyFrame;

typedef struct RenderB63810_KeyFrameSet {
    RenderB63810_KeyFrame sub[5];
} RenderB63810_KeyFrameSet;

extern RenderB63810_KeyFrameSet D_80748430[];
extern s16 D_80748A84;
extern s32 D_8076A064;
extern RenderB63810_LightEntry D_807F9070[];

void func_8065EB10(u8 arg0, s16 arg1, f32 arg2, f32 arg3, f32 arg4, s16 arg5, f32 arg6, s16 arg7) {
    u8 idx;
    s32 count;
    s32 i;
    s32 total;
    s32 temp_hi;
    s32 accum;
    s32 k;
    s32 next;
    RenderB63810_KeyFrame *cur;
    RenderB63810_KeyFrame *nxt;
    f32 t;
    f32 factor;
    f32 base;
    f64 d6;

    idx = arg0 - 1;
    if (D_80748A84 != 0x1E) {
        for (i = 0; i < D_80748A84; i++) {
            if (arg1 == D_807F9070[i].unk0) {
                return;
            }
        }

        total = 0;
        count = 0;
        for (i = 0; D_80748430[idx].sub[i].unkA != 0; i++) {
            total += D_80748430[idx].sub[i].unkA;
            count++;
        }

        temp_hi = (arg1 + D_8076A064) % total;
        accum = D_80748430[idx].sub[0].unkA;
        for (k = 1; temp_hi >= accum; k++) {
            accum += D_80748430[idx].sub[k].unkA;
        }

        k--;
        cur = &D_80748430[idx].sub[k];
        next = k + 1;
        if (next == count) {
            next = 0;
        }
        nxt = &D_80748430[idx].sub[next];

        t = (f32)(temp_hi - (accum - cur->unkA)) / (f32)cur->unkA;

        d6 = arg6;
        if (d6 < 0.8) {
            factor = 1.0f;
        } else {
            factor = 1.0 - ((d6 - 0.8) / 0.19999999999999996);
        }

        base = cur->unk0;
        base = (base + (nxt->unk0 - base) * t) * factor;

        D_807F9070[D_80748A84].unk16 = (u32)(((f32)(u32)cur->r + (f32)(nxt->r - cur->r) * t) * base);
        D_807F9070[D_80748A84].unk17 = (u32)(((f32)(u32)cur->g + (f32)(nxt->g - cur->g) * t) * base);
        D_807F9070[D_80748A84].unk18 = (u32)(((f32)(u32)cur->b + (f32)(nxt->b - cur->b) * t) * base);

        D_807F9070[D_80748A84].unk4 = arg2;
        D_807F9070[D_80748A84].unk8 = arg3;
        D_807F9070[D_80748A84].unkC = arg4;
        D_807F9070[D_80748A84].unk0 = arg1;
        D_807F9070[D_80748A84].unk12 = arg7;
        D_807F9070[D_80748A84].unk14 = arg5;
        D_807F9070[D_80748A84].unk10 = (s32)((f32)cur->unk8 + (f32)(nxt->unk8 - cur->unk8) * t);
        D_80748A84++;
    }
}
