#include "common.h"
#include "actor.h"

s16 mathAngleBetweenPoints2D(f32, f32, f32, f32);
f32 func_80611BB4(f32, f32);

void mathAngleBetweenPoints3D(s16 *arg0, s16 *arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6, f32 arg7) {
    f32 dx;
    f32 dz;

    *arg1 = mathAngleBetweenPoints2D(arg2, arg4, arg5, arg7);
    dx = arg5 - arg2;
    dz = arg7 - arg4;
    *arg0 = (s16)(s32)(((f64)func_80611BB4(arg6 - arg3, sqrtf((dx * dx) + (dz * dz))) * 2048.0) / 3.1415927410125732);
}

#define WRITE_GFX(pkt, _w0, _w1) { Gfx *_g = (Gfx *)(pkt); _g->words.w0 = (_w0); _g->words.w1 = (_w1); }

extern u8 D_807444FC;
extern s32 D_807FC924;
extern u8 D_807FC929;
extern Gfx D_2000180;
Gfx *renderSetSegment6AndFog(Gfx *, s16, u8);
Gfx *func_80614B34(Gfx *, Actor *);

void renderSetupSegmentsAndFog(Gfx *arg0, Actor *arg1) {
    WRITE_GFX(arg0++, 0xDA380007, osVirtualToPhysical((void *)((u8 *)D_807FC924 + (D_807FC929 * 0x2F0) + (D_807444FC << 6) + 0x88)));
    WRITE_GFX(arg0++, 0xDA380005, osVirtualToPhysical((void *)((u8 *)D_807FC924 + (D_807FC929 * 0x2F0) + (D_807444FC << 6) + 8)));
    WRITE_GFX(arg0++, 0xDA380003, (u32)&D_2000180);
    WRITE_GFX(arg0++, 0xE7000000, 0);
    WRITE_GFX(arg0++, 0xD9FDFFFF, 0);
    WRITE_GFX(arg0++, 0xFA0000FF, 0xFFFFFFFF);
    func_80614B34(renderSetSegment6AndFog(arg0, arg1->unk128, 1), arg1);
}

extern void *D_807FD580;
void animSetNodeItem(Actor *, s32, s16, s32);

typedef struct PlayerControlState {
    /* 0x000 */ u8 pad0[0x88];
    /* 0x088 */ s32 unk88;
    /* 0x08C */ u8 pad8C[0x1A4 - 0x8C];
    /* 0x1A4 */ u8 unk1A4;
    /* 0x1A5 */ u8 pad1A5[0x1EC - 0x1A5];
    /* 0x1EC */ u8 unk1EC;
    /* 0x1ED */ u8 pad1ED[0x1F0 - 0x1ED];
    /* 0x1F0 */ u32 unk1F0;
} PlayerControlState;

typedef struct PanSubState {
    /* 0x00 */ PlayerControlState *unk0;
    /* 0x04 */ s16 *unk4;
    /* 0x08 */ s32 unk8;
    /* 0x0C */ s32 unkC;
    /* 0x10 */ u16 unk10;
} PanSubState;

typedef struct CameraView {
    /* 0x000 */ u8 pad0[0x210];
    /* 0x210 */ f32 unk210;
    /* 0x214 */ f32 unk214;
    /* 0x218 */ f32 unk218;
    /* 0x21C */ u8 pad21C[0xC];
    /* 0x228 */ f32 unk228;
    /* 0x22C */ f32 unk22C;
    /* 0x230 */ f32 unk230;
} CameraView;

#define PAN_MIN(a, b) (((a) < (b)) ? (a) : (b))

extern Actor *D_807FBB40;

s32 func_806FFF88(void);
void func_80613C48(Actor *, s16, f32, f32);
void func_80614D00(Actor *, f32, f32);
void sfxPlayActorSound(void *, s32, s32, s32, s32, s32, f32, s32);
void sfxStopSlotSound(Actor *, s32);
void color5551CopyLerpToWhite(s16 *, s32 *, f32);
void slotQueueAddValue(s32, u8, s32);
s32 sfxAllocateChannel(s32, f32);
void func_80609140(s32, s32, f32, f32, s32, s32);
void renderCallbacksRegister(void *, void *, s32);
void mathAngleBetweenPoints3D(s16 *, s16 *, f32, f32, f32, f32, f32, f32);
s32 playerStateQueueCallback(s16, void *, u8);
void assetFreeBuffer(s32, s32, s32);
void heapFreeDeferred(Mtx *);
void actorDespawn(Actor *);
void actorUpdateModelMatrix(Actor *, s32);
void renderSetupSegmentsAndFog(Gfx *, Actor *);
void func_806FF628(void);

void func_80699284(void) {
    PanSubState *spEC;
    s16 spEA;
    s16 spE8;
    f32 mtx1[4][4];
    f32 mtx2[4][4];
    s16 sp66;
    s16 l1Angle;
    s32 *l1Dest; // FAKE: unused, reserves a frame word
    u8 sp5F;
    f32 t;

    spEC = D_807FBB40->unk174;
    sp5F = 0;
    if (!(D_807FBB40->unk60 & 0x10)) {
        spEC->unk10 = 0x5A;
        D_807FBB40->unk60 |= 0x400;
        D_807FBB40->unk12A = 0x3E8;
        spEC->unk4 = (s16 *)func_806FFF88();
        func_80613C48(D_807FBB40, 0x40B, 0, 0);
        func_80614D00(D_807FBB40, 0.15f, 0);
    }
    D_807FBB40->unk60 &= ~4;
    sp66 = 0x5A - spEC->unk10;
    if (sp66 == 0xD) {
        sfxPlayActorSound(D_807FBB40, 0x222, 0, 0, 0, 0xFF, 1.0f, -1);
    }
    if (sp66 == 0x1B) {
        sfxStopSlotSound(D_807FBB40, 0);
    }
    t = PAN_MIN(1.0, ((sp66 - 0x1E) < 0 ? 0 : (sp66 - 0x1E)) / 60.0f * 5.0);
    if (t < 1.0 && D_807FBB40->unk58 != 0xD9) {
        color5551CopyLerpToWhite((s16 *)spEC->unk4, &(&spEC->unk8)[D_807444FC], t);
        animSetNodeItem(D_807FBB40, 0, 0, (&spEC->unk8)[D_807444FC]);
    } else {
        animSetNodeItem(D_807FBB40, 0, 0, (s32)spEC->unk4);
        if (D_807FBB40->unk155[0] == 0) {
            if (((PlayerControlState *)D_807FD580)->unk1EC == 1) {
                slotQueueAddValue(0xC, ((PlayerControlState *)D_807FD580)->unk1A4, 1);
                sfxAllocateChannel(0x2E, 1.0f);
            } else if (((PlayerControlState *)D_807FD580)->unk1EC == 2) {
                func_80609140(0x98, 0x7FFF, 63.0f, 1.0f, 0, 0x80);
            }
            D_807FBB40->unk155[0]++;
        }
        if (((PlayerControlState *)D_807FD580)->unk1EC != 0xFF && spEC->unk10 != 0) {
            renderCallbacksRegister(&func_806FF628, D_807FBB40, 3);
        }
    }
    mathAngleBetweenPoints3D(&spE8, &spEA, ((CameraView *)D_807FC924)->unk210, ((CameraView *)D_807FC924)->unk214, ((CameraView *)D_807FC924)->unk218, ((CameraView *)D_807FC924)->unk228, ((CameraView *)D_807FC924)->unk22C, ((CameraView *)D_807FC924)->unk230);
    t = PAN_MIN(30.0, sp66) / 30.0;
    D_807FBB40->unkE6 = spEA;
    l1Angle = (f32)spE8 - (2048.0f + -2048.0f * t);
    D_807FBB40->unkE8 = l1Angle;
    guRotateF(mtx1, spE8 / 4095.0 * 360.0, 1.0f, 0.0f, 0.0f);
    guRotateF(mtx2, spEA / 4095.0 * 360.0, 0.0f, 1.0f, 0.0f);
    guMtxCatF(mtx1, mtx2, mtx1);
    guTranslateF(mtx2, ((CameraView *)D_807FC924)->unk210, ((CameraView *)D_807FC924)->unk214, ((CameraView *)D_807FC924)->unk218);
    guMtxCatF(mtx1, mtx2, mtx1);
    guMtxXFMF(mtx1, 0.0f, 0.0f, -30.0f * t, &D_807FBB40->unk7C, &D_807FBB40->unk80, &D_807FBB40->unk84);
    if (spEC->unk10 != 0) {
        spEC->unk10--;
    } else {
        D_807FBB40->unk60 &= ~0x8000;
        D_807FBB40->unk128 -= 0xA;
        if (D_807FBB40->unk128 <= 0) {
            sp5F = 1;
        }
    }
    if (sp5F || !(spEC->unk0->unk1F0 & 0x8000)) {
        if (spEC->unk0->unk1EC == 1) {
            playerStateQueueCallback(0x58, NULL, 0);
        }
        sfxStopSlotSound(D_807FBB40, 0);
        spEC->unk0->unk1F0 &= ~0x8000;
        spEC->unk0->unk1EC = 0xFF;
        if (D_807FBB40->unk58 == 0xD9) {
            assetFreeBuffer((s32)spEC->unk4, 0xF6, 0x45);
        } else {
            heapFreeDeferred((Mtx *)spEC->unk4);
        }
        spEC->unk0->unk88 = 0;
        actorDespawn(D_807FBB40);
    } else {
        guTranslateF((f32 (*)[4])((u8 *)D_807FBB40 + 0xC), 0.0f, -70.0f, 0.0f);
        actorUpdateModelMatrix(D_807FBB40, 1);
        renderCallbacksRegister(&renderSetupSegmentsAndFog, D_807FBB40, 3);
    }
}

void func_80699284(void);

void func_806998C8(void) {
    func_80699284();
}

/* Empty stub: the 8 bytes after func_806998C8 (a bare `jr ra; nop`) are a second
   function that splat merged into func_806998C8 for lack of a symbol. */
void func_806998E8(void) {
}

void func_80699958(u8, u8);

void func_806998F0(void) {
    func_80699958(8, 0);
}

extern Actor *D_807FBB40;

void func_80699914(void) {
    if (!(D_807FBB40->unk60 & 0x10)) {
        D_807FBB40->unk12A = 0x3E8;
    }
    func_80699958(0x1C, 1);
}

#ifdef NON_MATCHING
typedef struct WaveNode {
    /* 0x00 */ u8 unk0;
    /* 0x01 */ u8 unk1;
    /* 0x02 */ u8 pad2[2];
    /* 0x04 */ f32 unk4;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ f32 unkC;
} WaveNode;

typedef struct NodeListHead {
    /* 0x00 */ u8 pad0[0x24];
    /* 0x24 */ WaveNode *unk24;
} NodeListHead;

typedef struct ProximityEntry {
    /* 0x00 */ f32 unk0;
    /* 0x04 */ f32 unk4;
    /* 0x08 */ f32 unk8;
} ProximityEntry;

typedef struct ProximityGlobals {
    /* 0x00 */ u8 pad0[0x39];
    /* 0x39 */ u8 unk39;
    /* 0x3A */ u8 pad3A[2];
    /* 0x3C */ ProximityEntry entries[4];
    /* 0x6C */ u8 pad6C[0x10];
    /* 0x7C */ void *unk7C[4];
} ProximityGlobals;

typedef struct WaveState {
    /* 0x000 */ s16 unk0;
    /* 0x002 */ u8 pad2[2];
    /* 0x004 */ f32 unk4[28];
    /* 0x074 */ void *unk74[4];
    /* 0x084 */ f32 unk84[4];
    /* 0x094 */ u8 unk94;
    /* 0x095 */ u8 pad95[3];
    /* 0x098 */ f32 unk98[4];
    /* 0x0A8 */ f32 unkA8[4];
    /* 0x0B8 */ u8 unkB8[4];
} WaveState;

extern u8 D_807FBBEC;
extern ActorGlobalState D_807FBB70;
void func_80613C48(Actor *, s16, f32, f32);
void func_80614D00(Actor *, f32, f32);
Mtx *heapAlloc(s32);
void actorUpdateModelMatrix(Actor *, s32);
s32 func_8069A750(void);
void actorAddNodeForceSlot(f32, u8);
f32 sinApprox(f32);
void *memcpy(void *, const void *, unsigned int);

void func_80699958(u8 arg0, u8 arg1) {
    f32 sp128[32];
    f32 spC0[26];
    f32 var_fa0;
    WaveState *state;
    s32 i;
    s32 j;
    u8 found;
    f32 dist;

    state = (WaveState *)D_807FBB40->unk174;
    if (!(D_807FBB40->unk60 & 0x10)) {
        ((NodeListHead *)D_807FBB40->unk4)->unk24 = (WaveNode *)heapAlloc((arg0 + 1) * 0x10);
        for (i = 0; i < arg0; i++) {
            ((WaveNode *)((NodeListHead *)D_807FBB40->unk4)->unk24)[i].unk0 = i;
            if (i != arg0 - 1) {
                ((WaveNode *)((NodeListHead *)D_807FBB40->unk4)->unk24)[i].unk1 = i + 1;
            } else {
                ((WaveNode *)((NodeListHead *)D_807FBB40->unk4)->unk24)[i].unk1 = 0xFF;
            }
            ((WaveNode *)((NodeListHead *)D_807FBB40->unk4)->unk24)[i].unk4 = 0.0f;
            ((WaveNode *)((NodeListHead *)D_807FBB40->unk4)->unk24)[i].unkC = 0.0f;
            ((WaveNode *)((NodeListHead *)D_807FBB40->unk4)->unk24)[i].unk8 = 0.0f;
        }
        ((WaveNode *)((NodeListHead *)D_807FBB40->unk4)->unk24)[arg0].unk0 = 0xFF;
        for (i = 0; i < arg0; i++) {
            state->unk4[i] = 0.0f;
        }
        state->unk0 = -1;
        state->unk94 = 0;
        state->unkB8[1] = 0;
        state->unkB8[2] = 0;
        state->unkB8[3] = 0;
        state->unkB8[0] = 0;
    }
    if ((func_8069A750() != 0) && (state->unk0 == -1)) {
        state->unk0 = 10;
    }
    if (state->unk0 > 0) {
        state->unk0--;
    }
    if (state->unk0 == 0) {
        func_80613C48(D_807FBB40, 0x403, 0, 1.0f);
        func_80614D00(D_807FBB40, 4.0f, 1.0f);
        state->unk0 = -2;
    }
    for (i = 0; i < arg0; i++) {
        sp128[i] = 0.0f;
        spC0[i] = 0.0f;
    }
    i = 0;
    if ((s32)D_807FBB70.unk39 > 0) {
        do {
            found = 0;
            j = 0;
            while (j < (s32)state->unk94 && found == 0) {
                if (state->unk74[j] == ((ProximityGlobals *)&D_807FBB70)->unk7C[i]) {
                    found = 1;
                } else {
                    j++;
                }
            }
            if (!found) {
                switch (arg1) {
                case 0:
                    actorAddNodeForceSlot(((ProximityGlobals *)&D_807FBB70)->entries[i].unk8, arg1);
                    break;
                case 1:
                    actorAddNodeForceSlot(((ProximityGlobals *)&D_807FBB70)->entries[i].unk0, arg1);
                    break;
                }
            }
            i++;
        } while (i < (s32)D_807FBB70.unk39);
        i = 0;
    }
    if ((s32)state->unk94 > 0) {
        do {
            found = 0;
            j = 0;
            while (j < (s32)D_807FBB70.unk39 && found == 0) {
                if (state->unk74[i] == ((ProximityGlobals *)&D_807FBB70)->unk7C[j]) {
                    found = 1;
                } else {
                    j++;
                }
            }
            if (!found) {
                actorAddNodeForceSlot(state->unk84[i], arg1);
            }
            i++;
        } while (i < (s32)state->unk94);
        i = 0;
    }
    memcpy(state->unk74, &D_807FBBEC, 0x10);
    state->unk94 = D_807FBB70.unk39;
    if ((s32)state->unk94 > 0) {
        do {
            switch (arg1) {
            case 0:
                state->unk84[i] = ((ProximityGlobals *)&D_807FBB70)->entries[i].unk8;
                break;
            case 1:
                state->unk84[i] = ((ProximityGlobals *)&D_807FBB70)->entries[i].unk8;
                break;
            }
            i++;
        } while (i < (s32)state->unk94);
        i = 0;
    }
    if ((s32)D_807FBB70.unk39 > 0) {
        do {
            switch (arg1) {
            case 0:
                if ((f64)((ProximityGlobals *)&D_807FBB70)->entries[i].unk8 / 843.0 > 0) {
                    var_fa0 = (f32)((f64)((ProximityGlobals *)&D_807FBB70)->entries[i].unk8 / 843.0);
                } else {
                    var_fa0 = (f32)-((f64)((ProximityGlobals *)&D_807FBB70)->entries[i].unk8 / 843.0);
                }
                break;
            case 1:
                if ((f64)((ProximityGlobals *)&D_807FBB70)->entries[i].unk0 / 480.0 > 0) {
                    var_fa0 = (f32)((f64)((ProximityGlobals *)&D_807FBB70)->entries[i].unk0 / 480.0);
                } else {
                    var_fa0 = (f32)-((f64)((ProximityGlobals *)&D_807FBB70)->entries[i].unk0 / 480.0);
                }
                break;
            }
            i++;
            for (j = 0; j < arg0; j++) {
                if (var_fa0 < (f32)j) {
                    dist = (f32)j - var_fa0;
                } else {
                    dist = -((f32)j - var_fa0);
                }
                switch (arg1) {
                case 0:
                    dist = (f32)(3.0 - (f64)dist);
                    if (dist < 0.0) {
                        dist = 0.0f;
                    }
                    sp128[j] -= 45.0f * dist;
                    break;
                case 1:
                    dist = (f32)(7.0 - (f64)dist);
                    if (dist < 0.0) {
                        dist = 0.0f;
                    }
                    sp128[j] -= 70.0f * dist;
                    break;
                }
            }
        } while (i < (s32)D_807FBB70.unk39);
        i = 0;
    }
    for (i = 0; i < 4; i++) {
        if (state->unkB8[i] != 0) {
            for (j = 0; j < arg0; j++) {
                if (state->unk98[i] < (f32)j) {
                    dist = (f32)j - state->unk98[i];
                } else {
                    dist = -((f32)j - state->unk98[i]);
                }
                dist = (f32)(3.0 - (f64)dist);
                if (dist < 0.0) {
                    dist = 0.0f;
                }
                var_fa0 = sinApprox((f32)((f64)state->unkB8[i] * 0.5));
                spC0[j] = ((dist * state->unkA8[i]) * var_fa0) + spC0[j];

            }
            state->unkA8[i] = (f32)((f64)state->unkA8[i] - ((f64)state->unkA8[i] / 20.0));
            if ((f64)state->unkA8[i] < 0.5) {
                state->unkB8[i] = 0;
            } else {
                state->unkB8[i]++;
            }
        }
    }
    i = 0;
    if (arg0 > 0) {
        do {
            if (state->unk4[i] < sp128[i]) {
                switch (arg1) {
                case 0:
                    state->unk4[i] = (f32)((f64)state->unk4[i] + ((f64)(sp128[i] - state->unk4[i]) * 0.25));
                    break;
                case 1:
                    state->unk4[i] = (f32)((f64)state->unk4[i] + ((f64)(sp128[i] - state->unk4[i]) / 15.0));
                    break;
                }
                if (sp128[i] < state->unk4[i]) {
                    state->unk4[i] = sp128[i];
                }
            }
            if (sp128[i] < state->unk4[i]) {
                switch (arg1) {
                case 0:
                    state->unk4[i] = (f32)((f64)state->unk4[i] - ((f64)(state->unk4[i] - sp128[i]) * 0.5f));
                    break;
                case 1:
                    state->unk4[i] = (f32)((f64)state->unk4[i] - ((f64)(state->unk4[i] - sp128[i]) * 0.125));
                    break;
                }
                if (state->unk4[i] < sp128[i]) {
                    state->unk4[i] = sp128[i];
                }
            }
            ((WaveNode *)((NodeListHead *)D_807FBB40->unk4)->unk24)[i].unk8 = spC0[i] + state->unk4[i];
            i++;
        } while (i < arg0);
    }
    ((WaveNode *)((NodeListHead *)D_807FBB40->unk4)->unk24)[0].unk8 = 0.0f;
    *(f32 *)((u8 *)((NodeListHead *)D_807FBB40->unk4)->unk24 + (arg0 << 4) - 8) = 0.0f;  // FAKE: byte-offset form stops the CSE of arg0 * 16 across the calls
    actorUpdateModelMatrix(D_807FBB40, 0);
}
#else

#pragma GLOBAL_ASM("asm/global/nonmatchings/9DD70/func_80699958.s")
#endif

typedef struct {
    u8 pad0[0x98];
    f32 unk98[4];
    f32 unkA8[4];
    u8 unkB8[4];
} ActorMotionSlots;

/* arg1 is u8: IDO homes the raw incoming a1 to its caller slot (sw a1,4(sp))
   even in this leaf function and re-narrows it with andi before use. */
void actorAddNodeForceSlot(f32 arg0, u8 arg1) {
    ActorMotionSlots *slots = (ActorMotionSlots *)D_807FBB40->unk174;
    s16 i;
    s32 found;
    f64 temp;

    found = 0;
    i = 0;
    do {
        if (slots->unkB8[i] == 0) {
            found = 1;
        } else {
            i++;
        }
    } while (i < 4 && found == 0);
    if (found != 0) {
        slots->unkB8[i] = 1;
        switch (arg1) {
        case 0:
            slots->unkA8[i] = 10.0f;
            temp = (f64)arg0 / 843.0;
            if (temp > 0.0) {
                slots->unk98[i] = (f32)temp;
                return;
            }
            slots->unk98[i] = (f32)-temp;
            return;
        case 1:
            slots->unkA8[i] = 12.0f;
            temp = (f64)arg0 / 480.0;
            if (temp > 0.0) {
                slots->unk98[i] = (f32)temp;
                return;
            }
            slots->unk98[i] = (f32)-temp;
            break;
        }
    }
}

extern ActorGlobalState D_807FBB70;

#pragma GLOBAL_ASM("asm/global/nonmatchings/9DD70/func_8069A750.s")

Mtx *heapAlloc(s32);

typedef struct {
    u8 unk0;
    u8 unk1;
    u8 pad2[2];
    f32 unk4;
    f32 unk8;
    f32 unkC;
    u8 unk10;
    u8 pad11[3];
} ModelNodeRecord;

typedef struct {
    u8 pad0[0x24];
    ModelNodeRecord *unk24;
} ModelNodeList;

typedef struct {
    f32 unk0;
    u8 unk4;
    u8 pad5[3];
    f32 unk8;
    s32 unkC;
} ProximityState;

typedef struct {
    f32 unk0;
    f32 unk4;
    f32 unk8;
} ProximitySample;

typedef struct {
    u8 pad0[0xB8];
    f32 unkB8;
} ProximityNode;

typedef struct {
    u8 pad0[0x3C];
    ProximitySample entries[4];
    u8 pad6C[0x10];
    ProximityNode *nodes[4];
} ProximitySource;

f32 sinApprox(f32);
void actorUpdateModelMatrix(Actor *, s32);

#define PROX_SRC ((ProximitySource *)&D_807FBB70)

void func_8069A7C8(void) {
    ProximityState *state;
    f32 acc;
    f32 dist;
    f32 value;
    s32 flags;
    s32 i;

    flags = D_807FBB40->unk60;
    acc = 0.0f;
    state = (ProximityState *)D_807FBB40->unk174;
    if (!(flags & 0x10)) {
        D_807FBB40->unk60 = flags | 0x400;
        ((ModelNodeList *)D_807FBB40->unk4)->unk24 = (ModelNodeRecord *)heapAlloc(0x20);
        ((ModelNodeList *)D_807FBB40->unk4)->unk24->unk0 = 1;
        ((ModelNodeList *)D_807FBB40->unk4)->unk24->unk1 = 0xFF;
        ((ModelNodeList *)D_807FBB40->unk4)->unk24->unk4 = 0.0f;
        ((ModelNodeList *)D_807FBB40->unk4)->unk24->unkC = 0.0f;
        ((ModelNodeList *)D_807FBB40->unk4)->unk24->unk8 = 0.0f;
        ((ModelNodeList *)D_807FBB40->unk4)->unk24->unk10 = 0xFF;
        D_807FBB40->unk12A = 0x3E8;
        state->unk4 = 0;
        state->unkC = 0;
        state->unk0 = 0.0f;
        state->unk8 = 0.0f;
    }
    for (i = 0; i < (s32)D_807FBB70.unk39; i++) {
        dist = sqrtf((PROX_SRC->entries[i].unk0 * PROX_SRC->entries[i].unk0) + (PROX_SRC->entries[i].unk8 * PROX_SRC->entries[i].unk8));
        if (dist > 1347.0f) {
            dist = 1347.0f;
        }
        dist = 1347.0f - dist;
        acc += dist;
        value = PROX_SRC->nodes[i]->unkB8;
        value = (f32)((f64)value * 0.1);
        if (state->unk8 < value) {
            state->unk8 = value;
        }
    }
    if (acc > 1347.0f) {
        acc = 1347.0f;
    }
    acc = (f32)((f64)acc / 10.0);
    if (state->unk0 < acc) {
        state->unk0 = (f32)((f64)state->unk0 + ((f64)(acc - state->unk0) * 0.25));
        if (acc < state->unk0) {
            state->unk0 = acc;
        }
    }
    if (acc < state->unk0) {
        state->unk0 = (f32)((f64)state->unk0 - ((f64)(state->unk0 - acc) * 0.5f));
        if (state->unk0 < acc) {
            state->unk0 = acc;
        }
    }
    state->unkC++;
    if ((f64)state->unk8 == 0.0) {
        state->unkC = 0;
    }
    if (state->unk4 != D_807FBB70.unk39) {
        state->unk8 = 12.0f;
    }
    state->unk8 = (f32)((f64)state->unk8 - ((f64)state->unk8 / 40.0));
    if ((f64)state->unk8 < 0.5) {
        state->unk8 = 0.0f;
    }
    ((ModelNodeList *)D_807FBB40->unk4)->unk24->unk8 = 0.0 - (sinApprox((f32)((f64)state->unkC * 0.5)) * state->unk8 + state->unk0);
    state->unk4 = D_807FBB70.unk39;
    actorUpdateModelMatrix(D_807FBB40, 0);
}
#undef PROX_SRC

typedef struct {
    s16 unk0;
    u8 pad2[2];
    f32 unk4;
} S9B_BossTimer;

typedef struct {
    f32 unk0;
    s32 unk4;
    s32 unk8;
    s32 unkC;
    f32 unk10;
    f32 unk14;
} S9B_BossNode;

void actorScriptStart(Actor *, s32);
void func_80613C48(Actor *, s16, f32, f32);
void actorUpdateModelMatrix(Actor *, s32);
extern u8 D_807FBD70;
extern s32 D_8076A0A8;
extern s16 D_807503A0;
void lightSetFovAngles(f32, f32);
void lightSetFlags(u8);
void lightSetTargetId(s16);
s32 actorGetNodePos(Actor *, s32, f32 *, f32 *, f32 *);
void lightAdd(f32, f32, f32, f32, f32, f32, f32, s32, s32, s32, s32);

void func_8069AB74(void) {
    f32 sp74;
    f32 sp70;
    f32 sp6C;
    s32 pad60[3]; // FAKE: reserves frame bytes 0x60-0x6B
    u16 sp5E;
    u16 sp5C;
    u16 sp5A;
    S9B_BossTimer *sp54;

    sp54 = (S9B_BossTimer *)D_807FBB40->unk174;
    if (!(D_807FBB40->unk60 & 0x10)) {
        func_80613C48(D_807FBB40, 0x402, 0, 1.0f);
        if (D_8076A0A8 == 6) {
            actorScriptStart(D_807FBB40, 0x297);
        }
        D_807FBB40->unk60 |= 0x400;
        sp54->unk0 = 0;
        sp54->unk4 = 1.0f;
    }
    func_80614D00(D_807FBB40, ((S9B_BossNode *)D_807FBB40->unk124)->unk0, 1.0f);
    if (D_807FBD70 == 4) {
        sp54->unk0 = D_807503A0;
        sp54->unk4 = 0.0f;
    }
    if (sp54->unk0 == 0) {
        sp5E = ((S9B_BossNode *)D_807FBB40->unk124)->unk4;
        sp5C = ((S9B_BossNode *)D_807FBB40->unk124)->unk8;
        sp5A = ((S9B_BossNode *)D_807FBB40->unk124)->unkC;
        sp5E = (u16)(u32)((f64)(u32)sp5E * (f64)sp54->unk4);
        sp5C = (u16)(u32)((f64)(u32)sp5C * (f64)sp54->unk4);
        sp5A = (u16)(u32)((f64)(u32)sp5A * (f64)sp54->unk4);
        sp54->unk4 = (f32)((f64)sp54->unk4 + 0.05);
        if (sp54->unk4 > 1.0) {
            sp54->unk4 = 1.0f;
        }
        if (D_807FBB40->unk60 & 0x10) {
            if ((f64)((S9B_BossNode *)D_807FBB40->unk124)->unk10 != 0.0 || (f64)((S9B_BossNode *)D_807FBB40->unk124)->unk14 != 0.0) {
                lightSetFovAngles(((S9B_BossNode *)D_807FBB40->unk124)->unk10, ((S9B_BossNode *)D_807FBB40->unk124)->unk14);
            }
            lightSetFlags(2);
            lightSetTargetId(*(s16 *)D_807FBB40->unk12C);
            actorGetNodePos(D_807FBB40, 2, &sp6C, &sp70, &sp74);
            lightAdd((f32)((f64)D_807FBB40->unk7C + 0.3), D_807FBB40->unk80, D_807FBB40->unk84, sp6C, sp70, sp74, 0.0f, 1, sp5E, sp5C, sp5A);
        }
    } else {
        sp54->unk0 = sp54->unk0 - 1;
    }
    actorUpdateModelMatrix(D_807FBB40, 0);
}

void func_8069AB74(void);

void func_8069AFF0(void) {
    func_8069AB74();
}

typedef struct S9DCamView {
    u8 pad0[0x210];
    f32 unk210;
    f32 unk214;
    f32 unk218;
    u8 pad21C[0xC];
    f32 unk228;
    f32 unk22C;
    f32 unk230;
} S9DCamView;

typedef struct S9DLinkView {
    u8 pad0[0xEC];
    s16 unkEC;
    u8 padEE[0x66];
    u8 unk154;
    u8 pad155[0xA];
    u8 unk15F;
} S9DLinkView;

extern Actor *D_807FBB4C;
extern s16 D_80750378;
extern s32 D_8076A068;
extern u8 D_8071FE08[];
extern u8 D_80720E14[];
void effectScaleSpinUpdate();
void actorDespawn(Actor *);
void actorSetCollisionRadius(Actor *, f32);
void func_8067ACB4(Actor *);
void func_8065D254(Actor *, s32, s32, s32, s32, s32, s32, s32, s32, s32, f32);
void actorAppendCallback(Actor *, Actor *, s32, u8, s32, void *);
void actorAppendModelNode(Actor *, f32, f32, f32, f32, s32);
void actorAppendModelSubNode(Actor *, f32, f32, f32, s32);
void collisionCheckActorFloor(Actor *, f32, f32, f32, f32 *);
void sfxPlayFromActorWithAltitudeCheck(Actor *, s32, s32, s32, s32);
void func_8071498C(void *);
void func_807149B8(u8);
void func_807149FC(s32);
s32 func_80714C08(void *, f32, Actor *, s32, s32);
s32 func_80714CC0(void *, f32, f32, f32, f32);
f32 mathAngleBetweenPointsDeg(s32, s32, s32, s32);

void func_8069B010(void) {
    s32 *p = D_807FBB40->unk174;
    S9DLinkView *link;

    if (!(D_807FBB40->unk60 & 0x10)) {
        D_807FBB40->unk6A &= 0xFFFE;
        D_807FBB40->unk144 = 2;
        actorSetCollisionRadius(D_807FBB40, 60.0f);
        actorAppendModelNode(D_807FBB40, 0.0f, 0.0f, 0.0f, 60.0f, -1);
        actorAppendModelSubNode(D_807FBB40, 0.0f, 0.0f, 0.0f, -1);
        func_807149FC(-1);
        func_807149B8(1);
        func_8071498C(effectScaleSpinUpdate);
        func_80714C08(D_80720E14, 0.9f, D_807FBB40, 1, 2);
        *p = D_8076A068;
        D_807FBB40->unk60 |= 0x80000;
        collisionCheckActorFloor(D_807FBB40, D_807FBB40->unk7C, D_807FBB40->unk80, D_807FBB40->unk84, &D_807FBB40->unkA4);
    }
    func_8067ACB4(D_807FBB40);
    func_8065D254(D_807FBB40, 0x3C8, 0x40, 0x40, 0x1E, 0x1E, 1, 0x4B, 0x78, 0, 1.0f);
    link = (S9DLinkView *)D_807FBB40->unk11C;
    if (link != NULL) {
        if (link->unk154 != 2 && link->unk154 != 0x26) {
            actorDespawn(D_807FBB40);
            return;
        }
        if (D_807FBB40->unk15F == link->unk15F) {
            if ((D_807FBB40->unk7C - D_807FBB4C->unk7C) * (D_807FBB40->unk7C - D_807FBB4C->unk7C) + (D_807FBB40->unk84 - D_807FBB4C->unk84) * (D_807FBB40->unk84 - D_807FBB4C->unk84) > 900.0f) {
                ((S9DLinkView *)D_807FBB40->unk11C)->unkEC = (s16)(mathAngleBetweenPointsDeg((s32)D_807FBB40->unk7C, (s32)D_807FBB40->unk84, (s32)D_807FBB4C->unk7C, (s32)D_807FBB4C->unk84) - mathAngleBetweenPointsDeg((s32)((S9DCamView *)D_807FC924)->unk228, (s32)((S9DCamView *)D_807FC924)->unk230, (s32)((S9DCamView *)D_807FC924)->unk210, (s32)((S9DCamView *)D_807FC924)->unk218));
            }
            lightAdd(D_807FBB40->unk7C, D_807FBB40->unk80, D_807FBB40->unk84, 0.0f, 0.0f, 0.0f, 100.0f, 0, 0xFF, 0xFF, 0);
        }
        if (D_807FBD70 == 9) {
            sfxPlayFromActorWithAltitudeCheck(D_807FBB40, 0x1CE, 0xFF, 0x7F, 0x1E);
            func_80714CC0(D_8071FE08, 1.0f, D_807FBB40->unk7C, D_807FBB40->unk80, D_807FBB40->unk84);
            actorAppendCallback((Actor *)D_807FBB40->unk11C, D_807FBB40, 0x02000000, D_807FBB40->unk15F, 0, 0);
            actorDespawn(D_807FBB40);
        }
        if (D_8076A0A8 != 0x48 && D_8076A0A8 != 0x11 && (u32)(*p + D_80750378) < (u32)D_8076A068) {
            actorAppendCallback((Actor *)D_807FBB40->unk11C, D_807FBB40, 0x02000000, 0xFF, 0, 0);
            actorDespawn(D_807FBB40);
        }
    } else {
        actorDespawn(D_807FBB40);
    }
}

extern u8 D_8071FC58;
extern u8 D_8071FC8C;
extern u8 D_8071FCC0;
void func_80717D4C(void);
s32 randomNonNegative(void);
void func_80714950(s32);
void sfxStopChannel(s32, s32);

void func_8069B3FC(void) {
    s16 *p = D_807FBB40->unk174;
    S9DCamView *cam = D_807FBB4C->unk174;
    s32 i;
    f32 x;
    f32 y;
    f32 z;
    s32 j;
    void *sel;

    if (!(D_807FBB40->unk60 & 0x10)) {
        D_807FBB40->unk144 = 1;
        D_807FBB40->unk60 |= 0x400;
        actorScriptStart(D_807FBB40, 0x298);
        *p = 0;
        sfxAllocateChannel(0x3B, 1.0f);
    } else {
        actorGetNodePos(D_807FBB40, 1, &x, &y, &z);
        cam->unk210 = x;
        cam->unk214 = y;
        cam->unk218 = z;
        if (D_807FBB40->unk155[0] < 4) {
            for (j = 2; j < 3; j++) {
                for (i = 0; i < 2; i++) {
                    func_8071498C(func_80717D4C);
                    func_807149B8(1);
                    func_80714950((randomNonNegative() >> 15) % 10000 % 120 + 0x50);
                    switch ((randomNonNegative() >> 15) % 10000 % 3) {
                        case 0:
                            sel = &D_8071FC58;
                            break;
                        case 1:
                            sel = &D_8071FC8C;
                            break;
                        case 2:
                            sel = &D_8071FCC0;
                            break;
                    }
                    func_80714C08(sel, 0.6f, D_807FBB40, j, 0);
                }
            }
        }
        switch (D_807FBB40->unk155[0]) {
            case 0:
                *p += 0x1E;
                break;
            case 1:
                D_807FBB4C->unk155[0]++;
                D_807FBB40->unk155[0]++;
                break;
            case 2:
                *p -= 0x2A;
                if (*p < 0) {
                    *p = 0;
                }
                break;
            case 3:
                *p -= 0x2A;
                if (*p < 0) {
                    *p = 0;
                }
                D_807FBB4C->unk155[0]++;
                D_807FBB40->unk60 &= ~0x8000;
                D_807FBB40->unk128 = 0xFF;
                D_807FBB40->unk155[0]++;
                break;
            case 4:
                *p -= 0x2A;
                if (*p < 0) {
                    *p = 0;
                }
                D_807FBB40->unk128 -= 0x28;
                if (D_807FBB40->unk128 < 0x28) {
                    D_807FBB4C->unk155[0]++;
                    sfxStopChannel(0x3B, 0);
                    actorDespawn(D_807FBB40);
                }
                break;
        }
    }
    D_807FBB40->unkE6 += *p;
    actorUpdateModelMatrix(D_807FBB40, 0);
}

extern s16 D_80744490;
s32 actorTableContains();
void func_8069B908(void);
void func_80689114(s16, f32, f32, f32, s16, f32, s32);
s32 flagGet(s32, s32);

s32 actorHasCallbackTargetThisFrame(void) {
    ActorCallbackNode *node = D_807FBB40->unk13C;

    while (node != NULL) {
        if ((u32)node->callback == 0x8000) {
            Actor *actor;
            void *sub;
            if (actorTableContains(node->unk8) != 0) {
                actor = (Actor *)node->unk8;
                if (actor->unk5C & 1) {
                    sub = actor->unk174;
                    if ((u32)(D_8076A068 - *(s32 *)((u8 *)sub + 0x120)) < 2) {
                        return 1;
                    }
                }
            }
        }
        node = node->next;
    }
    return 0;
}

#ifdef NON_MATCHING

typedef struct L3b_Sub174 {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ f32 unk4;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ f32 unk10;
    /* 0x14 */ Actor *unk14;
    /* 0x18 */ u8 pad18[4];
    /* 0x1C */ s32 unk1C;
    /* 0x20 */ f32 unk20;
    /* 0x24 */ f32 unk24;
    /* 0x28 */ u8 unk28;
    /* 0x29 */ u8 pad29[1];
    /* 0x2A */ u16 unk2A;
} L3b_Sub174;

typedef struct L3b_Sub124 {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ s32 unk4;
} L3b_Sub124;

typedef struct L3b_NameTable {
    /* 0x0 */ s32 unk0;
    /* 0x4 */ s32 unk4;
} L3b_NameTable;

extern Actor *D_807FBB98;
extern u8 D_807FBB85;
extern u8 D_807FBB94;
extern u8 D_807FBB95;
extern u8 D_807FBB9C;
extern u8 D_807FBDC4;
extern f32 D_807FBC60;
extern f32 D_807FBC64;
extern s16 D_807502D0;
extern f32 D_807502E4;
extern u8 D_80720340;
extern L3b_NameTable D_807503A4;

s32 actorHasActiveMovementFlags(Actor *);
s32 actorListFindIdByActor(Actor *);
void actorListSetPosByActor(Actor *, f32, f32, f32);
void actorListSpawnNodeEntry(s16, f32, f32, f32, s16, f32, s32, s32);
void actorApplyVelocity(Actor *);
void actorUpdateFloorContactAndTilt(Actor *, f32);
void func_806791DC(Actor *, s32);
void func_806791EC(Actor *, s32);
void func_8067A170(void *, s32);
void func_8068A2FC(Actor *);
void func_806CF4B8(Actor *);
void sfxSetVolumeAndPan(u8, f32, f32);
void actorSpawnNodeEntryScaled(s32, f32, f32, f32, s32, s32, s32, s32);
s32 actorAngleInArc(Actor *, s16);
f32 func_806119FC(void);
void func_8071496C(s16);
void func_80714998(s32);
void camStartShake(s32, s32, s32);
void func_8071A8B0(void);
void func_8071910C(void);

void func_8069B908(void) {
    L3b_Sub174 *sp13C;
    f32 mtxA[4][4];
    f32 mtxB[4][4];
    f32 dx;
    f32 dy;
    f32 dz;
    f32 spAC;
    f32 spB0;
    f32 spA4;
    L3b_NameTable sp9C;
    s32 i;
    s32 var_v0;
    s16 ang;
    s32 pad84[3];
    s32 sp7C[2];
    s32 sp78;
    s32 pad74;
    s32 sp70;

    sp13C = D_807FBB40->unk174;
    if (!(D_807FBB40->unk60 & 0x10)) {
        *(s16 *)((u8 *)D_807FBB40 + 0xFA) = 0x270F;
        D_807FBB40->unkA4 = 99999.0f;
        actorUpdateFloorContactAndTilt(D_807FBB40, 0);
        if (actorHasActiveMovementFlags(D_807FBB40) != 0) {
            D_807FBB40->unk144 = 2;
            D_807FBB40->unk68 |= 1;
            D_807FBB40->unk154 = 2;
            *(u8 *)((u8 *)D_807FBB40 + 0x155) = 1;
            sp13C->unk1C = 0x1E;
        }
        sp13C->unk28 = ((L3b_Sub124 *)D_807FBB40->unk124)->unk0;
        if (sp13C->unk28 != 0) {
            sp13C->unk4 = D_807FBB40->unk7C;
            sp13C->unk8 = D_807FBB40->unk80;
            sp13C->unkC = D_807FBB40->unk84;
            sp13C->unk10 = D_807FBB40->unk4->unk34 / 0.15;
        }
        if (((L3b_Sub124 *)D_807FBB40->unk124)->unk4 == 1) {
            D_807FBB40->unk132 = 2;
        } else {
            D_807FBB40->unk132 = 1;
        }
        switch (D_807FBB40->unk58) {
        case 0x43:
            if (flagGet(0x9A, 0) != 0) {
                func_8068A2FC(D_807FBB40);
            }
            break;
        case 0x3D:
            if (D_8076A0A8 == 0xC3) {
                if (flagGet(0x267, 0) != 0) {
                    func_8068A2FC(D_807FBB40);
                }
            }
            if (D_8076A0A8 == 0x26) {
                D_807FBB40->unk64 |= 0x400;
            }
            break;
        }
        if (D_807FBB40->unk58 == 0x3F || D_807FBB40->unk58 == 0x40 ||
            D_807FBB40->unk58 == 0x41 || D_807FBB40->unk58 == 0x42) {
            D_807FBB40->unk64 |= 0x420;
        }
    }
    if (D_807FBB94 != 0) {
        sp13C->unk14 = D_807FBB98;
        D_807FBB40->unk154 = 1;
        func_806791EC(D_807FBB40, 0x8000);
        func_8067A170(sp13C->unk14, 1);
        D_807FBB40->unk144 = 0x2C;
    }
    if (D_807FBB95 != 0) {
        D_807FBB40->unk154 = 2;
        *(u8 *)((u8 *)D_807FBB40 + 0x155) = 0;
        sp13C->unk1C = 0x1E;
        D_807FBB40->unk144 = 0x3C;
        func_806791DC(D_807FBB40, 0x8000);
        if (D_8076A0A8 == 7 && actorListFindIdByActor(D_807FBB40) == 0x17) {
            actorListSetPosByActor(D_807FBB40, D_807FBB40->unk7C, D_807FBB40->unkA4, D_807FBB40->unk84);
        }
    }
    if (D_8076A0A8 == 0x22 && D_807FBB40->unk58 == 0x3D &&
        (D_807FBB40->unk154 == 0 || D_807FBB40->unk154 == 2)) {
        if (D_807FBB40->unk7C >= 3242.0 && D_807FBB40->unk84 >= 252.0 &&
            D_807FBB40->unk7C <= 3842.0 && D_807FBB40->unk84 <= 852.0) {
            D_807FBB40->unk154 = 4;
        }
    }
    if (D_807FBB85 != 0 || D_807FBD70 == 9) {
        D_807FBB40->unk154 = 4;
        func_806CF4B8(D_807FBB40);
    }
    if (D_807FBB9C != 0) {
        D_807FBB40->unk154 = 3;
        D_807FBB40->unk144 = 0x3C;
        func_806791DC(D_807FBB40, 0x8000);
        D_807FBB40->unkE6 = *(s16 *)((u8 *)&D_807FBB70 + 0x36);
        *(s16 *)((u8 *)D_807FBB40 + 0xEE) = *(s16 *)((u8 *)&D_807FBB70 + 0x36);
        *(f32 *)((u8 *)D_807FBB40 + 0xC0) = *(f32 *)((u8 *)&D_807FBB70 + 0x30);
        D_807FBB40->unkB8 = (f32)*(s16 *)((u8 *)&D_807FBB70 + 0x34);
        func_8067A170(sp13C->unk14, 1);
        if (D_807FBB40->unk58 == 0x43 && D_8076A0A8 == 0x1E) {
            D_807FBB40->unk60 |= 0x200000;
            sp13C->unk0 = D_8076A068;
        }
    }
    if (D_807FBB40->unk58 == 0x55) {
        if (actorHasActiveMovementFlags(D_807FBB40) != 0) {
            D_807FBB40->unk60 |= 0x400;
        } else {
            D_807FBB40->unk60 &= ~0x400;
        }
    }
    func_8067ACB4(D_807FBB40);
    if (D_807FBB40->unk58 == 0x3F || D_807FBB40->unk58 == 0x40 ||
        D_807FBB40->unk58 == 0x41 || D_807FBB40->unk58 == 0x42) {
        for (i = 0; i < D_807FBDC4; i++) {
            if (D_807FBB70.unk258[i] == 1) {
                sp13C->unk2A = 0;
                D_807FBB40->unk154 = 5;
            }
        }
    }
    switch (D_807FBB40->unk154) {
    case 0:
        D_807FBB40->unk144 = 2;
        D_807FBB40->unk64 |= 8;
        D_807FBB40->unk60 |= 0x80000000;
        D_807FBB40->unk68 |= 1;
        if (actorHasCallbackTargetThisFrame() != 0) {
            D_807FBB40->unk154 = 4;
        }
        break;
    case 1:
        D_807FBB40->unk68 &= 0xFFFE;
        D_807FBB40->unk64 &= ~8;
        D_807FBB40->unk60 &= 0x7FFFFFFF;
        sp13C->unk20 = (f32)(((f64)sp13C->unk14->unkE6 / 4095.0) * 360.0);
        break;
    case 2:
        D_807FBB40->unk64 &= ~8;
        D_807FBB40->unk60 &= 0x7FFFFFFF;
        if (sp13C->unk1C != 0) {
            sp13C->unk1C--;
        }
        if (sp13C->unk1C == 0 && (D_807FBB40->unk6A & 1)) {
            D_807FBB40->unk154 = 0;
        } else if (actorHasActiveMovementFlags(D_807FBB40) != 0) {
            sp13C->unk1C = 0x1E;
        }
        if ((D_807FBB40->unk6A & 1) && *(u8 *)((u8 *)D_807FBB40 + 0x155) == 0) {
            if (D_807FBB40->unk58 == 0x55) {
                sfxPlayFromActorWithAltitudeCheck(D_807FBB40, 0x8B, 0x64, 0x7F, 0x14);
                sfxPlayFromActorWithAltitudeCheck(D_807FBB40, 0x97, 0x64, 0x7F, 0x14);
            } else {
                sfxPlayFromActorWithAltitudeCheck(D_807FBB40, 0x97, 0xFF, 0x7F, 0x14);
            }
            (*(u8 *)((u8 *)D_807FBB40 + 0x155))++;
        }
        *(f32 *)((u8 *)D_807FBB40 + 0xC0) = -200.0f;
        D_807FBB40->unkB8 = 0.0f;
        D_807FBB40->unk68 |= 1;
        if (actorHasCallbackTargetThisFrame() != 0) {
            D_807FBB40->unk154 = 4;
        }
        break;
    case 3:
        *(f32 *)((u8 *)D_807FBB40 + 0xC0) = *(f32 *)((u8 *)D_807FBB40 + 0xC0) + D_807502E4;
        if (*(f32 *)((u8 *)D_807FBB40 + 0xC0) < (f32)D_807502D0) {
            *(f32 *)((u8 *)D_807FBB40 + 0xC0) = (f32)D_807502D0;
        }
        var_v0 = 0;
        sp13C->unk24 = sp13C->unk24 - 10.0f;
        if (D_807FBB40->unk58 == 0x43 && D_8076A0A8 == 0x1E &&
            (u32)(D_8076A068 - sp13C->unk0) >= 0x5B) {
            var_v0 = 1;
        }
        if (var_v0 != 0 || (D_807FBB40->unkFC != 0 && actorAngleInArc(D_807FBB40, D_807FBB40->unkE6) == 0)) {
            D_807FBB40->unk154 = 4;
        }
        D_807FBB40->unk68 &= 0xFFFE;
        D_807FBB40->unk64 &= ~8;
        D_807FBB40->unk60 &= 0x7FFFFFFF;
        break;
    case 4:
        if (D_807FBB40->unk58 == 0x3D && sp13C->unk28 == 0) {
            switch (actorListFindIdByActor(D_807FBB40)) {
            case 0x17:
                if (flagGet(0x19, 0) == 0) {
                    actorSpawnNodeEntryScaled(0x2D, D_807FBB40->unk7C, D_807FBB40->unk80 + 10.0f,
                                  D_807FBB40->unk84, 0, 2, 0x19, 0);
                    sfxAllocateChannel(0x14, 1.0f);
                }
                break;
            case 6:
                if (flagGet(0x1D, 0) == 0) {
                    actorSpawnNodeEntryScaled(0x6E, D_807FBB40->unk7C, D_807FBB40->unk80 + 10.0f,
                                  D_807FBB40->unk84, 0, 2, 0x1D, 0);
                }
                break;
            }
        }
        sfxPlayFromActorWithAltitudeCheck(D_807FBB40, 0x162, 0xFF, 0x7F, 0x1E);
        if (sp13C->unk28 == 0) {
            actorDespawn(D_807FBB40);
        }
        if (D_807FBB70.unk0 == 0) {
            sp9C = D_807503A4;
            for (sp70 = 0; sp70 != 0x10; sp70 += 2) {
                spAC = (f32)(((f64)((randomNonNegative() >> 15) % 8191) / 200.0) - 20.0);
                spB0 = (f32)(((f64)((randomNonNegative() >> 15) % 8191) / 200.0) - 20.0);
                spA4 = (f32)(((f64)((randomNonNegative() >> 15) % 8191) / 200.0) - 20.0);
                func_8071496C(sp70);
                func_807149B8(1);
                if (sp70 == 0) {
                    func_80714950(0x100FA);
                    func_8071498C((void *)func_8071A8B0);
                } else {
                    func_8071498C((void *)func_80717D4C);
                    func_80714950(-0x96 - ((randomNonNegative() >> 15) % 50));
                }
                func_80714CC0(&D_80720340, 1.6f, D_807FBB40->unk7C + spAC,
                              D_807FBB40->unk80 + spB0, D_807FBB40->unk84 + spA4);
                if (D_807FBB40->unk58 == 0x3D) {
                    spAC = (2.0f * func_806119FC()) - 1.0f;
                    spB0 = (2.0f * func_806119FC()) - 1.0f;
                    spA4 = (2.0f * func_806119FC()) - 1.0f;
                    spAC *= 30.0f;
                    spB0 *= 30.0f;
                    spA4 *= 30.0f;
                    spB0 += 30.0f;
                    func_807149B8(1);
                    func_807149FC(0x3C);
                    func_8071498C((void *)func_8071910C);
                    func_80714998(2);
                    func_80714950(2);
                    sp78 = randomNonNegative();
                    func_80714CC0((void *)((s32 *)&sp9C)[(sp78 >> 15) % 2],
                                  (f32)(((f64)func_806119FC() * 0.5) + 0.2),
                                  D_807FBB40->unk7C + spAC, D_807FBB40->unk80 + spB0,
                                  D_807FBB40->unk84 + spA4);
                }
            }
            camStartShake(*(s32 *)((u8 *)D_807FBB4C->unk174 + 0x104), 0x14, 0xF);
        }
        if (sp13C->unk28 != 0) {
            D_807FBB40->unk154 = 0xA;
            D_807FBB40->unk138 = 0;
            D_807FBB40->unk144 = 1;
            D_807FBB40->unk60 &= ~4;
        }
        break;
    case 5:
        D_807FBB40->unk64 &= ~8;
        D_807FBB40->unk60 &= 0x7FFFFFFF;
        D_807FBB40->unk68 &= 0xFFFE;
        sp13C->unk2A = sp13C->unk2A + 2;
        if (sp13C->unk2A >= 0xFB) {
            sp13C->unk2A = 0xFA;
        }
        if (*(s16 *)((u8 *)D_807FBB40 + 0x6E) == -1) {
            sfxPlayActorSound(D_807FBB40, 0x11A, 0x64, 1, 0, 0x64, 1.0f, 0);
        } else {
            sfxSetVolumeAndPan(*(s16 *)((u8 *)D_807FBB40 + 0x6E),
                               (f32)(((f64)(u32)sp13C->unk2A / 400.0) + 0.5), 2.0f);
        }
        lightAdd(D_807FBB40->unk7C, D_807FBB40->unk80 + 30.0f, D_807FBB40->unk84,
                 0, 0.0f, 0.0f, (f32)(((f64)(u32)sp13C->unk2A / 250.0) * 100.0), 0, 0xFF, 0xFF, 0);
        D_807FBB40->unkE6 = D_807FBB40->unkE6 + sp13C->unk2A;
        D_807FBB40->unk80 = D_807FBB40->unkA4;
        break;
    case 10:
        dz = D_807FBB4C->unk84 - sp13C->unkC;
        dx = D_807FBB4C->unk7C - sp13C->unk4;
        dy = D_807FBB4C->unk80 - sp13C->unk8;
        if ((dz * dz) + ((dx * dx) + (dy * dy)) > 2500.0f) {
            sp7C[0] = sp13C->unk28;
            if (D_807FBB40->unk132 == 2) {
                sp7C[1] = 1;
            } else {
                sp7C[1] = 0;
            }
            actorListSpawnNodeEntry(*(s16 *)((u8 *)D_807FBB40 + 0x5A), sp13C->unk4, sp13C->unk8,
                                    sp13C->unkC, 0, sp13C->unk10, 0, (s32)sp7C);
            actorDespawn(D_807FBB40);
        }
        break;
    case 0x63:
        break;
    }
    if (D_807FBB40->unk154 == 2 || D_807FBB40->unk154 == 3) {
        *(s16 *)((u8 *)D_807FBB40 + 0xEE) = D_807FBB40->unkE6;
        actorApplyVelocity(D_807FBB40);
        actorUpdateFloorContactAndTilt(D_807FBB40, 0);
        if (D_807FBB40->unk154 == 3 && (D_807FBB40->unk6A & 1) && !(D_807FBB40->unk6C & 1)) {
            D_807FBB40->unk154 = 4;
        }
        if (D_807FBB40->unk154 == 2 && (D_807FBB40->unk6A & 4)) {
            D_807FBB40->unk154 = 4;
        }
        *(s16 *)((u8 *)D_807FBB40 + 0xDC) = 0x3FF;
        *(s16 *)((u8 *)D_807FBB40 + 0xDE) = 0x3FF;
    } else {
        D_807FBB40->unk110 = 0;
        D_807FBB40->unk6A &= 0xFBF7;
    }
    if (D_8076A0A8 == 0x26 || D_8076A0A8 == 0x71 || D_8076A0A8 == 0xC2) {
        if (D_807FBB40->unk58 == 0x3D) {
            if (D_807FBB40->unk110 == 1) {
                D_807FBB40->unk60 |= 0x200000;
            } else {
                D_807FBB40->unk60 &= ~0x200000;
            }
        }
    }
    if (D_807FBB40->unk154 != 0x63) {
        func_8065D254(D_807FBB40, 0x3C8, 0x40, 0x40, 0x14, 0x14, 1, 0x64, 0x78, 0, 1.0f);
    }
    guScaleF(mtxA, D_807FBB40->unk4->unk34, D_807FBB40->unk4->unk38, D_807FBB40->unk4->unk3C);
    guRotateF(mtxB, sp13C->unk24, 0.0, 1.0f, 0.0);
    guMtxCatF(mtxA, mtxB, mtxA);
    guRotateF(mtxB, (f32)(((f64)D_807FBB40->unkE6 / 4095.0) * 360.0), 0.0, 1.0f, 0.0);
    guMtxCatF(mtxA, mtxB, mtxA);
    guRotateF(mtxB, (f32)(0.0 - (f64)D_807FBC60), 1.0f, 0.0, 0.0);
    guMtxCatF(mtxA, mtxB, mtxA);
    guRotateF(mtxB, (sp13C->unk20 + 90.0f) - D_807FBC64, 0.0, 1.0f, 0.0);
    guMtxCatF(mtxA, mtxB, mtxA);
    if (D_807FBB40->unk154 == 3) {
        ang = *(s16 *)((u8 *)D_807FBB40 + 0xDE);

        if (ang < 0x3E8) {
            guRotateF(mtxB, (f32)(-(((f64)*(s16 *)((u8 *)D_807FBB40 + 0xDC) / 4095.0) * 360.0)),
                      0.0, 1.0f, 0.0);
            guMtxCatF(mtxA, mtxB, mtxA);
            ang = *(s16 *)((u8 *)D_807FBB40 + 0xDE);
        }
        guRotateF(mtxB, (f32)(90.0 - (((f64)ang / 4095.0) * 360.0)), 1.0f, 0.0, 0.0);
        guMtxCatF(mtxA, mtxB, mtxA);
        if (*(s16 *)((u8 *)D_807FBB40 + 0xDE) < 0x3E8) {
            guRotateF(mtxB, (f32)(((f64)*(s16 *)((u8 *)D_807FBB40 + 0xDC) / 4095.0) * 360.0),
                      0.0, 1.0f, 0.0);
            guMtxCatF(mtxA, mtxB, mtxA);
        }
    }
    guTranslateF(mtxB, D_807FBB40->unk7C, D_807FBB40->unk80, D_807FBB40->unk84);
    guMtxCatF(mtxA, mtxB, (f32 (*)[4])((u8 *)D_807FBB40 + 0xC));
}
#else

#pragma GLOBAL_ASM("asm/global/nonmatchings/9DD70/func_8069B908.s")
#endif


typedef struct CameraPos {
    u8 pad0[0x210];
    f32 unk210;
    f32 unk214;
    f32 unk218;
} CameraPos;

void actorUpdateTimerBarAndRange(void) {
    f32 frac;
    f32 dzTmp;
    f32 dx;
    f32 dz;
    f32 dy;
    f32 dist;
    u32 val;

    if (!(D_807FBB40->unk60 & 0x10)) {
        frac = D_807FBB40->unk4->unk34 / 0.15;
        frac = frac - 1.0;
        if (frac < 0.0) {
            frac = 0.0f;
        }
        val = (u32)(80.0f * frac);
        D_807FBB40->unk12C[4] = val;
        D_807FBB40->unk12C[5] = val;
        D_807FBB40->unk12A = 0x2BC;
    }
    /* dz is computed before dx into a temp: this is what makes IDO emit the
       target's dx, dz, dy float load/sub scheduling (dx, dy, dz otherwise). */
    dzTmp = D_807FBB40->unk84 - ((CameraPos *)D_807FC924)->unk218;
    dx = D_807FBB40->unk7C - ((CameraPos *)D_807FC924)->unk210;
    dz = dzTmp;
    dy = D_807FBB40->unk80 - ((CameraPos *)D_807FC924)->unk214;
    dist = dx * dx + dy * dy;
    if (dz * dz + dist < 18000.0) {
        D_807FBB40->unk60 |= 0x400;
    } else {
        D_807FBB40->unk60 &= ~0x400;
    }
    func_8069B908();
}

void actorSpawnEffectAndTick(void) {
    if (!(D_807FBB40->unk60 & 0x10)) {
        D_807FBB40->unk12C[4] = 0x3C;
        D_807FBB40->unk12C[5] = 0x3C;
        func_80689114(0x83, D_807FBB40->unk7C, D_807FBB40->unk80, D_807FBB40->unk84,
                      0, 1.0f, (s32)D_807FBB40);
    }
    func_8069B908();
    if (!(D_807FBB40->unk60 & 0x10)) {
        if (*(s32 *)((u8 *)D_807FBB40->unk124 + 0x8) == 1) {
            if (flagGet(0xFD, 0) != 0) {
                D_807FBB40->unk132 = 4;
            }
        }
    }
}

void func_8069D018(void) {
    Actor *actor = D_807FBB40;

    if (!(actor->unk60 & 0x10)) {
        actor->unk12A = 0x2BC;
    }
    func_8069B908();
}

void func_8069D058(void) {
    func_8069D018();
}

void func_8069D078(void) {
    func_8069D018();
}

void func_8069D098(void) {
    func_8069D018();
}

void func_8069D0B8(void) {
    func_8069D018();
}

void func_8069D0D8(void) {
    func_8069B908();
}

typedef struct TextMarkerState {
    void *unk0;
    u16 unk4;
    u16 unk6;
    u8 unk8;
    u8 unk9;
    u8 unkA;
} TextMarkerState;

s32 actorSpawn(s32, s32);
s32 gfxResourceCreate(s16, s32, s32, f32, f32, f32);
s32 textGetStringWidth(s16, s32);
extern Actor *D_807FBB44;

void textSpawnMarker(u8 arg0, s16 arg1, s16 arg2, s32 arg3, u16 arg4, u16 arg5, u8 arg6, u8 arg7) {
    s32 len;
    TextMarkerState *sub;

    if (actorSpawn(0xE8, 0) != 0) {
        sub = D_807FBB44->unk174;
        if (arg0 & 0x80) {
            sub->unkA = gfxResourceCreate((s16)(arg0 & 0xFF7F), arg3, 2, 160.0f, (f32)arg2, 0.0f);
            *(s16 *)((u8 *)D_807FBB44 + 0xEE) = 1;
            D_807FBB44->unk80 = (f32)arg2;
            return;
        }
        if (arg1 == 0) {
            D_807FBB44->unk7C = (f32)((D_80744490 - textGetStringWidth((s16)arg0, arg3)) * 2);
        } else {
            D_807FBB44->unk7C = (f32)(arg1 * 4);
        }
        D_807FBB44->unk80 = (f32)(arg2 * 4);
        D_807FBB44->unk84 = (f32)arg0;
        D_807FBB44->unk16A = 0xFF;
        D_807FBB44->unk16B = 0xFF;
        D_807FBB44->unk16C = 0xFF;
        len = strlen((char *)arg3) + 1;
        sub->unk0 = (void *)heapAlloc(len);
        _strcpy((char *)sub->unk0, (char *)arg3);
        sub->unk4 = arg4;
        sub->unk6 = arg5;
        sub->unk8 = arg6;
        sub->unk9 = arg7;
    }
}

extern u8 D_807FC928;
s32 func_80714450();
s32 func_807142D8();
s32 func_8071432C();
s32 func_80712658();
void textSpawnMarker(u8, s16, s16, s32, u16, u16, u8, u8);

void textSpawnMarkerChecked(u8 arg0, s16 arg1, s16 arg2, s32 arg3, u16 arg4, u16 arg5, u8 arg6, u8 arg7) {
    if (D_807FC928 < 2) {
        if (func_80714450() == 0) {
            if (func_807142D8() == 0) {
                if (func_8071432C() != 0 || func_80712658() != 0) {
                    textSpawnMarker(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7);
                }
            }
        }
    }
}

typedef struct ActorPositionView {
    u8 pad0[0x7C];
    f32 unk7C;
    f32 unk80;
} ActorPositionView;

void heapFreeDeferred(Mtx *);

void *renderAppendScaledMatrix(void *arg0, ActorPositionView *arg1, s16 arg2, f32 arg3) {
    Mtx *temp;
    f32 mtxA[4][4];
    f32 mtxB[4][4];

    temp = heapAlloc(0x40);
    heapFreeDeferred(temp);
    guScaleF(mtxA, arg3, arg3, 1.0f);
    guTranslateF(mtxB, (f32)((f64)arg1->unk7C + 2.0 * (f64)arg2), arg1->unk80, 0.0f);
    guMtxCatF(mtxA, mtxB, mtxA);
    guMtxF2L(mtxA, temp);
    ((u32 *)arg0)[0] = 0xDA380003;
    ((u32 *)arg0)[1] = (u32)temp;
    return (u8 *)arg0 + 8;
}

extern Gfx D_1000118;

#ifdef NON_MATCHING
#define S9D_GFX(pkt, _w0, _w1) { Gfx *_g = (Gfx *)(pkt); _g->words.w0 = (_w0); _g->words.w1 = (u32)(_w1); }

extern s32 D_8074E880[];
void func_80717404(void);
void func_8071495C(void);
void vtxGradientSetPosition(s16);
extern Gfx *textDrawStringVtx(Gfx *, s16, s16, s16, char *, u8);

void func_8069D424(Gfx *gfx, Actor *actor) {
    char **sub;
    s16 x;
    s16 y;
    u8 state;
    u8 mode;
    s16 width;

    if (&state == 0) {} // FAKE: keeps state/mode/width/x/y in spill-style home slots
    sub = actor->unk174;
    state = 3;
    mode = (u8)actor->unk84;
    S9D_GFX(gfx++, 0xDE000000, &D_1000118);
    S9D_GFX(gfx++, 0xFC119623, 0xFF2FFFFF);

    x = actor->unk155[0];
    switch (x) {
        case 2:
            vtxGradientSetPosition((s16)(actor->unk15F * 3 + 0x4000));
            break;
        case 0:
            if (actor->unk84 == 1.0f) {
                s16 w2;

                w2 = (s16)(s32)((((f64)actor->unk15F * 0.0078125 > 1.0 ? 1.0 : (f64)actor->unk15F * 0.0078125) * 0.9) * (f64)textGetStringWidth((s16)(s32)actor->unk84, (s32)*sub) + (f64)actor->unk7C * 0.25);
                func_807149B8(1);
                func_8071498C(func_80717404);
                func_80714950(0xA);
                func_8071495C();
                func_80714CC0((void *)D_8074E880[((randomNonNegative() >> 0xF) % 1000) % 3], 1.0f, (f32)w2, (f32)((f64)actor->unk80 * 0.25 + 12.0), -5.0f);
            }
        default:
            vtxGradientSetPosition((s16)(actor->unk15F * 3));
            break;
    }

    x = (s16)(s32)actor->unk7C;
    y = (s16)(s32)actor->unk80;
    switch (mode) {
        case 1:
            width = textGetStringWidth((s16)(s32)actor->unk84, (s32)*sub);
            state = 0x13;
            gfx = renderAppendScaledMatrix(gfx, (ActorPositionView *)actor, width, 0.8f);
            state &= 0xFFFE;
            x = -(width * 2);
            y = 0;
            break;
        case 6:
            state = 0x23;
            S9D_GFX(gfx++, 0xE3000A01, 0x100000);
            S9D_GFX(gfx++, 0xE200001C, 0x0C184240);
            break;
        case 0:
            mode = 6;
            width = textGetStringWidth(6, (s32)*sub);
            actor->unk7C = (f32)((D_80744490 - width) * 2);
            gfx = renderAppendScaledMatrix(gfx, (ActorPositionView *)actor, width, 0.8f);
            state = 0;
            x = -(width * 2);
            y = 0;
            break;
        case 10:
            mode = 6;
            gfx = renderAppendScaledMatrix(gfx, (ActorPositionView *)actor, 0, 0.8f);
            state = 0;
            x = 0;
            y = 0;
            break;
    }

    S9D_GFX(gfx++, 0xFA000000, (actor->unk16A << 24) | (actor->unk16B << 16) | (actor->unk16C << 8) | actor->unk15F);
    textDrawStringVtx(gfx, (s16)mode, x, y, *sub, state);
}
#else

#pragma GLOBAL_ASM("asm/global/nonmatchings/9DD70/func_8069D424.s")
#endif

#define WRITE_GFX_U32(pkt, _w0, _w1) { Gfx *_g = (Gfx *)(pkt); _g->words.w0 = (_w0); _g->words.w1 = (u32)(_w1); }

Gfx *textDrawAnimated(Gfx *, s32, s32, f32, f32, f32, f32);

Gfx *textMarkerRender(Gfx *gfx, Actor *actor) {
    void *model;

    model = actor->unk174;
    WRITE_GFX_U32(gfx++, 0xDE000000, &D_1000118);
    WRITE_GFX_U32(gfx++, 0xE7000000, 0);
    WRITE_GFX_U32(gfx++, 0xFA000000, 0xFFFFFFFF);
    WRITE_GFX_U32(gfx++, 0xFC11FE23, 0xFFFFF3F9);
    WRITE_GFX_U32(gfx++, 0xDA380003, &D_2000180);
    if (actor->unk168++ < 100) {
        gfx = textDrawAnimated(gfx, *(u8 *)((u8 *)model + 0xA), 2, 160.0f, actor->unk80, 0.0f, 1.0f);
    } else {
        gfx = textDrawAnimated(gfx, *(u8 *)((u8 *)model + 0xA), 1, 160.0f, actor->unk80, 0.0f, 1.0f);
    }
    return gfx;
}

void renderCallbacksRegister(void *, void *, s32);
void heapFree(void *);
void func_8069D424(Gfx *, Actor *);

void textMarkerUpdate(void) {
    u8 *model;

    model = (u8 *)D_807FBB40->unk174;
    if (D_807FBB40->unkEE != 0) {
        renderCallbacksRegister(textMarkerRender, D_807FBB40, 3);
        return;
    }
    if (!(D_807FBB40->unk60 & 0x10)) {
        D_807FBB40->unk168 = *(u16 *)(model + 4);
    }
    switch (D_807FBB40->unk154) {
    case 0:
        if (D_807FBB40->unk168 != 0) {
            D_807FBB40->unk168--;
        } else {
            D_807FBB40->unk154 = 1;
        }
        break;
    case 1:
        if (D_807FBB40->unk155[0] != 3) {
            renderCallbacksRegister(func_8069D424, D_807FBB40, 3);
        }
        switch (D_807FBB40->unk155[0]) {
        case 0:
            if (D_807FBB40->unk15F <= 0xFF - model[8]) {
                D_807FBB40->unk15F += model[8];
            } else {
                D_807FBB40->unk15F = 0xFF;
                D_807FBB40->unk155[0]++;
                D_807FBB40->unk168 = *(u16 *)(model + 6);
            }
            break;
        case 1:
            if (D_807FBB40->unk168 != 0) {
                D_807FBB40->unk168--;
            } else {
                D_807FBB40->unk155[0]++;
            }
            break;
        case 2:
            if (D_807FBB40->unk15F >= model[9]) {
                D_807FBB40->unk15F -= model[9];
            } else {
                D_807FBB40->unk155[0]++;
                D_807FBB40->unk15F = 0;
            }
            break;
        case 3:
            heapFree(*(void **)model);
            actorDespawn(D_807FBB40);
            break;
        }
        break;
    }
}

/* Row-major copy: the target keeps the row offset (i * arg2) * 4 as the loop
   invariant and adds arg1 + j * 4 inside, so arg1 is written before the offset. */
void textCopyGlyphBlock(s32 *arg0, s32 *arg1, u8 arg2) {
    s16 i;
    s16 j;

    i = 0;
    do {
        for (j = 0; j < arg2; j++) {
            *arg0++ = *(s32 *)((u8 *)arg1 + j * 4 + i * arg2 * 4);
        }
        i++;
    } while (i < 0x20);
}

void *textFontLoadSheet(s16);
void animSetLoopLimit(Actor *, s32, s16);
void animSetSpeed(Actor *, s32, f32);

s32 textBuildDigitNode(u8 arg0, void *arg1, u8 arg2, u8 arg3, u8 arg4) {
    void *temp;

    temp = textFontLoadSheet(arg0 + arg3);
    if (arg1 != NULL) {
        heapFreeDeferred((Mtx *)arg1);
    }
    /* Reusing the parameter keeps both pointers in one callee-saved register. */
    arg1 = (void *)heapAlloc(arg4 << 7);
    textCopyGlyphBlock((s32 *)arg1, (s32 *)temp, arg4);
    animSetLoopLimit(D_807FBB40, arg2, -1);
    animSetSpeed(D_807FBB40, arg2, 0.0f);
    animSetNodeItem(D_807FBB40, arg2, 0, (s32)arg1);
    return (s32)arg1;
}

extern u8 D_8076A0AB;
extern u16 D_807FC930[];
extern u16 D_807446C0[];
u8 func_805FF030(u8, u8);
void csModelStateSetFirstByte(s32, s32);
s32 textBuildDigitNode(u8, void *, u8, u8, u8);

void textUpdateThreeDigitCounter(void) {
    s32 *model;
    s32 dummy;
    s32 t;
    s32 ten;
    s32 unk;
    u16 val;

    model = (s32 *)D_807FBB40->unk174;
    if (!(D_807FBB40->unk60 & 0x10) || (*(u32 *)((u8 *)D_807FD580 + 0x1F0) & 0x20000)) {
        t = func_805FF030(D_8076A0AB, 0);
        if (t >= 8) {
            t = 0;
        }
        unk = t << 1;
        val = *(u16 *)((u8 *)D_807FC930 + unk);
        model[0] = textBuildDigitNode(0x21, (void *)model[0], 0, val / 100, 0x20);
        model[1] = textBuildDigitNode(0x21, (void *)model[1], 1, val % 100 / 10, 0x20);
        model[2] = textBuildDigitNode(0x21, (void *)model[2], 2, val % 10, 0x20);
        D_807FBB40->unk16A = 0xFF;
        D_807FBB40->unk16B = 0xFF;
        D_807FBB40->unk16C = 0xFF;
        D_807FBB40->unk60 |= 0x800000;
        *(u32 *)((u8 *)D_807FD580 + 0x1F0) &= ~0x20000;
        if (val >= *(u16 *)((u8 *)D_807446C0 + unk)) {
            D_807FBB40->unk60 &= ~0x8000;
            D_807FBB40->unk128 = 0;
            D_807FBB40->unk144 = 1;
            csModelStateSetFirstByte(8, 2);
            ten = 10;
            csModelStateSetFirstByte(9, ten);
            csModelStateSetFirstByte(ten, ten);
            csModelStateSetFirstByte(11, ten);
            csModelStateSetFirstByte(13, ten);
            csModelStateSetFirstByte(12, ten);
        }
    }
    actorUpdateModelMatrix(D_807FBB40, 0);
}

void textUpdateTwoDigitCounter(void) {
    s32 *model;
    Actor *actor;

    actor = D_807FBB40;
    model = (s32 *)actor->unk174;
    if (!(actor->unk60 & 0x10)) {
        model[0] = textBuildDigitNode(0x14, (void *)model[0], 0, actor->unk155[0] / 10, 0x10);
        model[1] = textBuildDigitNode(0x14, (void *)model[1], 1, D_807FBB40->unk155[0] % 10, 0x10);
        actor = D_807FBB40;
    }
    actorUpdateModelMatrix(actor, 0);
}

void func_8069E018(void) {
    actorUpdateModelMatrix(D_807FBB40, 0);
}

void actorPlaySoundAndFinish(void) {
    if (!(D_807FBB40->unk60 & 0x10)) {
        actorScriptStart(D_807FBB40, 0x299);
    }
    actorUpdateModelMatrix(D_807FBB40, 0);
}

void flagSet(s32, s32, s32);
void func_8070E8DC(s32);
s32 func_80600530(void);
void func_8070D8C0(Actor *, s32, u8);

extern s8 D_807F6951;
extern s8 D_807F6950;

void func_8069E088(void) {
    s16 unk;

    if (!(D_807FBB40->unk60 & 0x10)) {
        func_80613C48(D_807FBB40, 0x5ED, 0.0f, 0.0f);
    }
    D_807FBB40->unk15E = 0x14;
    if (D_807FBB40->unk154 < 0x1E) {
        D_807FBB40->unk154++;
    }
    if (D_807FBB40->unk154 == 0x1E) {
        unk = 0;
        D_807FBB40->unk154 = 0x64;
        func_8070E8DC(1);
        if (flagGet(0x178, 0) == 0) {
            flagSet(0x178, 1, 0);
        } else {
            unk = func_80600530() * 5 + D_807F6951 + 1;
        }
        func_8070D8C0(D_807FBB40, 0x29, unk);
    }
    if (D_807F6950 != 0) {
        actorDespawn(D_807FBB40);
    }
    D_807FBB40->unk4->unk34 = 0.0f;
    D_807FBB40->unk4->unk38 = 0.0f;
    D_807FBB40->unk4->unk3C = 0.0f;
    actorUpdateModelMatrix(D_807FBB40, 0);
}
