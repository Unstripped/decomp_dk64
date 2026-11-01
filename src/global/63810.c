#include "common.h"
#include "actor.h"

typedef struct QueuedLightEntry {
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
} QueuedLightEntry;

extern s16 gLightQueueCount;
extern QueuedLightEntry gLightQueue[];

typedef struct LightKeyframe {
    f32 unk0;
    u8 r;
    u8 g;
    u8 b;
    u8 pad7;
    s16 unk8;
    s16 unkA;
} LightKeyframe;

typedef struct LightKeyframeSet {
    LightKeyframe sub[5];
} LightKeyframeSet;

extern LightKeyframeSet gLightKeyframeTable[];
extern s32 gFrameCounter;

void lightQueueKeyframed(u8 arg0, s16 arg1, f32 arg2, f32 arg3, f32 arg4, s16 arg5, f32 arg6, s16 arg7) {
    u8 count;
    s32 i;
    s32 total;
    s32 temp_hi;
    s32 accum;
    s32 next;
    f32 t;
    f32 factor;
    f32 base;
    f64 d6;

    arg0 = arg0 - 1;
    if (gLightQueueCount != 0x1E) {
        for (i = 0; i < gLightQueueCount; i++) {
            if (arg1 == gLightQueue[i].unk0) {
                return;
            }
        }

        total = 0;
        count = 0;
        for (i = 0; gLightKeyframeTable[arg0].sub[i].unkA != 0; count++, i++) {
            total += gLightKeyframeTable[arg0].sub[i].unkA;
        }

        temp_hi = (arg1 + gFrameCounter) % total;
        accum = gLightKeyframeTable[arg0].sub[0].unkA;
        i = 1;
        while (temp_hi >= accum) {
            accum += gLightKeyframeTable[arg0].sub[i].unkA;
            i++;
        }

        i--;
        accum -= gLightKeyframeTable[arg0].sub[i].unkA;
        temp_hi -= accum;
        t = (f32)temp_hi / (f32)gLightKeyframeTable[arg0].sub[i].unkA;
        next = i + 1;
        if (next == count) {
            next = 0;
        }


        d6 = arg6;
        if (d6 < 0.8) {
            factor = 1.0f;
        } else {
            factor = 1.0 - ((d6 - 0.8) / 0.19999999999999996);
        }

        base = gLightKeyframeTable[arg0].sub[i].unk0 + (gLightKeyframeTable[arg0].sub[next].unk0 - gLightKeyframeTable[arg0].sub[i].unk0) * t;
        base = base * factor;

        gLightQueue[gLightQueueCount].unk16 = (u32)(((f32)(u32)gLightKeyframeTable[arg0].sub[i].r + (f32)(gLightKeyframeTable[arg0].sub[next].r - gLightKeyframeTable[arg0].sub[i].r) * t) * base);
        gLightQueue[gLightQueueCount].unk17 = (u32)(((f32)(u32)gLightKeyframeTable[arg0].sub[i].g + (f32)(gLightKeyframeTable[arg0].sub[next].g - gLightKeyframeTable[arg0].sub[i].g) * t) * base);
        gLightQueue[gLightQueueCount].unk18 = (u32)(((f32)(u32)gLightKeyframeTable[arg0].sub[i].b + (f32)(gLightKeyframeTable[arg0].sub[next].b - gLightKeyframeTable[arg0].sub[i].b) * t) * base);
        gLightQueue[gLightQueueCount].unk10 = (s32)((f32)gLightKeyframeTable[arg0].sub[i].unk8 + (f32)(gLightKeyframeTable[arg0].sub[next].unk8 - gLightKeyframeTable[arg0].sub[i].unk8) * t);
        gLightQueue[gLightQueueCount].unk4 = arg2;
        gLightQueue[gLightQueueCount].unk8 = arg3;
        gLightQueue[gLightQueueCount].unkC = arg4;
        gLightQueue[gLightQueueCount].unk12 = arg7;
        gLightQueue[gLightQueueCount].unk14 = arg5;
        gLightQueue[gLightQueueCount++].unk0 = arg1;
    }
}





extern s32 gCurrentMap;
extern Actor *D_807FBB4C;
extern s32 D_807FBB60;
extern s32 D_807FBB68;

void lightSetFlags(u8);
void lightSetTargetId(s16);
void lightSetRadius(s16);
void lightAdd(f32, f32, f32, f32, f32, f32, f32, u8, u8, u8, u8);

void lightFlushQueued(void) {
    s32 i;

    if (gCurrentMap == 0x30 && !(((Struct807FD580 *)D_807FBB4C->unk174)->unk1F0 & 0x100000)) {
        gLightQueueCount = 0;
        return;
    }

    if (!(D_807FBB60 & 2)) {
        for (i = 0; i < gLightQueueCount; i++) {
            if (!(D_807FBB68 & 4)) {
                lightSetFlags(2);
            }
            lightSetTargetId(gLightQueue[i].unk12);
            lightSetRadius(gLightQueue[i].unk14);
            lightAdd(gLightQueue[i].unk4, gLightQueue[i].unk8, gLightQueue[i].unkC, 0.0f, 0.0f, 0.0f, gLightQueue[i].unk10, 0, gLightQueue[i].unk16, gLightQueue[i].unk17, gLightQueue[i].unk18);
        }
    }
    gLightQueueCount = 0;
}

typedef struct ActorSlotEntry {
    u8 pad0[0x20];
    u8 *unk20;
    u8 pad24[0x62];
    s16 unk86;
    u8 pad88[0x8];
} ActorSlotEntry;

extern ActorSlotEntry *D_807F6000;
s32 hashTableLookup(s32);

void actorSetTargetSlotByte(s32 arg0, u8 arg1) {
    u8 *volatile sp1C;
    s16 temp_a0;
    s32 temp_v0;
    u8 *temp_v1;

    temp_v0 = hashTableLookup(arg0);
    if (temp_v0 != -1) {
        temp_v1 = (u8 *)D_807F6000 + (temp_v0 * 0x90);
        temp_a0 = *(s16 *)(temp_v1 + 0x86);
        if (temp_a0 != 1) {
            if (temp_a0 == 2) {
                sp1C = *(u8 **)(temp_v1 + 0x20) + 0x5B;
            }
        } else {
            sp1C = *(u8 **)(temp_v1 + 0x20) + 0xC3;
        }
        *sp1C = arg1;
    }
}
