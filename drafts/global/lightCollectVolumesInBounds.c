// lightCollectVolumesInBounds (src/global/5E2F0.c): Light(r5): stage 5, text 6 (was 21; park replaced). Case 0 spelled via dist=unk14*3 + e1=dist copy, temp_fa1/e2 copy, e1=((unk14*1.3)/three)*3 + memory copy diff[1]=e1 used in last sub; case-1 stores: unk14 before unk4. Remaining: fa0/dist colour f2 vs target f12 (+ f14/f12 swap) and one extra swc1 f18,148(sp) from diff[1] copy. Tried: 5040 case-1 store orders, alias/inline/copy hill-climb, dead/self-assign hill-climb (no gain).
#include "common.h"

extern s16 D_80748300;
extern f32 sqrtf(f32);
typedef struct LightVolume {
    /* 0x00 */ f32 unk0;
    /* 0x04 */ f32 unk4;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ f32 unk10;
    /* 0x14 */ f32 unk14;
    /* 0x18 */ f32 x;
    /* 0x1C */ f32 y;
    /* 0x20 */ f32 z;
    /* 0x24 */ f32 unk24;
    /* 0x28 */ f32 unk28;
    /* 0x2C */ f32 unk2C;
    /* 0x30 */ s16 unk30;
    /* 0x32 */ s16 unk32;
    /* 0x34 */ s16 unk34;
    /* 0x36 */ u8 unk36;
    /* 0x37 */ u8 unk37;
    /* 0x38 */ u8 unk38;
    /* 0x39 */ u8 unk39;
    /* 0x3A */ u8 unk3A;
    /* 0x3B */ u8 pad3B;
} LightVolume;

extern LightVolume D_807F7500[];
typedef struct LightTrigger {
    /* 0x00 */ f32 unk0;
    /* 0x04 */ f32 unk4;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ f32 unk10;
    /* 0x14 */ f32 unk14;
    /* 0x18 */ s32 unk18;
    /* 0x1C */ f32 unk1C;
    /* 0x20 */ f32 unk20;
    /* 0x24 */ f32 unk24;
    /* 0x28 */ f32 unk28;
    /* 0x2C */ f32 unk2C;
    /* 0x30 */ f32 unk30;
    /* 0x34 */ f32 unk34;
    /* 0x38 */ s16 unk38;
    /* 0x3A */ s16 unk3A;
    /* 0x3C */ s16 unk3C;
    /* 0x3E */ u8 unk3E;
    /* 0x3F */ u8 unk3F;
} LightTrigger;

extern LightTrigger D_807F78C0[];
extern LightTrigger D_807F7BC8[];
extern s16 D_807F7BC0;
void lightAddDedupEntry(s16);
s32 lightCheckVolumeBounds(LightVolume *, f32, f32, f32, s16, s16, s16, s16, s16, s16, s32);
s16 lightCollectVolumesInBounds(f32 arg0, f32 arg1, f32 arg2, s16 arg3, s16 arg4, s16 arg5, s16 arg6, s16 arg7, s16 arg8, s32 arg9, s8 *arg10) {
    f32 diff[6];
    s32 i;
    f32 dist;
    f32 temp_fa0, temp_fa1;
    f32 temp_f1;
    f32 temp_ft4, temp_ft5;
    f32 three;
    f32 e1, e2;
    s16 a3 = arg3;
    s16 a4 = arg4;
    s16 a5 = arg5;
    s16 a6 = arg6;

    *arg10 = 0;
    D_807F7BC0 = 0;
    three = 3;
    for (i = 0; i < D_80748300; i++) {
        if (lightCheckVolumeBounds(&D_807F7500[i], arg0, arg1, arg2, a3, a4, a5, a6, arg7, arg8, arg9)) {
            if (D_807F7BC0 < 12) {
                if (D_807F7500[i].unk3A & 1) {
                    *arg10 = 1;
                }
                D_807F78C0[D_807F7BC0].unk3F = i;
                D_807F78C0[D_807F7BC0].unk38 = D_807F7500[i].x * 3.0f;
                D_807F78C0[D_807F7BC0].unk3A = D_807F7500[i].y * 3.0f;
                D_807F78C0[D_807F7BC0].unk3C = D_807F7500[i].z * 3.0f;
                D_807F78C0[D_807F7BC0].unk2C = (f64)(u32)D_807F7500[i].unk36 / 255.0;
                D_807F78C0[D_807F7BC0].unk30 = (f64)(u32)D_807F7500[i].unk37 / 255.0;
                D_807F78C0[D_807F7BC0].unk34 = (f64)(u32)D_807F7500[i].unk38 / 255.0;
                D_807F78C0[D_807F7BC0].unk3E = D_807F7500[i].unk39;
                switch ((u32)D_807F7500[i].unk39) {
                    if (!temp_ft4) {}  // FAKE: steers FP temp colours (random search)
                case 1:
                    diff[0] = D_807F7500[i].unk24 - D_807F7500[i].x;
                    diff[1] = D_807F7500[i].unk28 - D_807F7500[i].y;
                    diff[2] = D_807F7500[i].unk2C - D_807F7500[i].z;
                    dist = sqrtf((diff[0] * diff[0] + diff[1] * diff[1]) + diff[2] * diff[2]);
                    if (dist == 0.0f) {
                        dist = 0.1f;
                    }
                    D_807F78C0[D_807F7BC0].unkC = diff[0] / dist;
                    D_807F78C0[D_807F7BC0].unk10 = diff[1] / dist;
                    D_807F78C0[D_807F7BC0].unk14 = diff[2] / dist;
                    D_807F78C0[D_807F7BC0].unk4 = D_807F7500[i].unk4;
                    D_807F78C0[D_807F7BC0].unk18 = 0x127690;
                    D_807F78C0[D_807F7BC0].unk0 = D_807F7500[i].unkC;
                    D_807F78C0[D_807F7BC0].unk8 = D_807F7500[i].unk10;
                    break;
                case 0:
                    if (D_807F7500[i].unk14 == 0.0f) {
                        D_807F7500[i].unk14 = 0.1f;
                    }
                    dist = D_807F7500[i].unk14 * 3.0f;
                    e1 = dist;  // FAKE: split web of dist/fa0 (FP colour steer)
                    D_807F78C0[D_807F7BC0].unk18 = (s32)(dist * e1);
                    temp_fa1 = (D_807F7500[i].unk14 / three) * 3.0f;
                    e2 = temp_fa1;  // FAKE: copy steers FP colouring
                    D_807F78C0[D_807F7BC0].unk1C = 1.0f / (dist - temp_fa1);
                    D_807F78C0[D_807F7BC0].unk20 = temp_fa1;
                    e1 = ((D_807F7500[i].unk14 * 1.3f) / three) * 3.0f;
                    diff[1] = e1;  // FAKE: memory-resident copy steers FP colouring
                    D_807F78C0[D_807F7BC0].unk28 = e1;
                    D_807F78C0[D_807F7BC0].unk24 = 1.0f / (((D_807F7500[i].unk14 * 1.3f) * 3.0f) - diff[1]);
                    break;
                }
                lightAddDedupEntry(D_807F7BC0);
                D_807F7BC0++;
            }
        }
    }
    if (D_807F7BC0 > 0.0f) {}  // FAKE: steers FP temp colours (random search)
    if (arg10 && arg10) {}  // FAKE: deadsweep: arg10 priority above a3..a6 (s4)
    return D_807F7BC0;
}
