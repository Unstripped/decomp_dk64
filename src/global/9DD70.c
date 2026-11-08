#include "common.h"
#include "actor.h"

s16 mathAngleBetweenPoints2D(f32, f32, f32, f32);
f32 mathAtan2(f32, f32);

void mathAngleBetweenPoints3D(s16 *pitch, s16 *yaw, f32 x1, f32 y1, f32 z1, f32 x2, f32 y2, f32 z2) {
    f32 dx;
    f32 dz;

    *yaw = mathAngleBetweenPoints2D(x1, z1, x2, z2);
    dx = x2 - x1;
    dz = z2 - z1;
    *pitch = (s16)(s32)(((f64)mathAtan2(y2 - y1, sqrtf((dx * dx) + (dz * dz))) * 2048.0) / 3.1415927410125732);
}

#define WRITE_GFX(pkt, _w0, _w1) { Gfx *_g = (Gfx *)(pkt); _g->words.w0 = (_w0); _g->words.w1 = (_w1); }

extern u8 D_807444FC;
extern s32 gPlayerSlots;
extern u8 gCurrentPlayerIndex;
extern Gfx D_2000180;
Gfx *renderSetSegment6AndFog(Gfx *, s16, u8);
Gfx *renderActorDisplayList(Gfx *, Actor *);

void renderSetupSegmentsAndFog(Gfx *glistp, Actor *actor) {
    WRITE_GFX(glistp++, 0xDA380007, osVirtualToPhysical((void *)((u8 *)gPlayerSlots + (gCurrentPlayerIndex * 0x2F0) + (D_807444FC << 6) + 0x88)));
    WRITE_GFX(glistp++, 0xDA380005, osVirtualToPhysical((void *)((u8 *)gPlayerSlots + (gCurrentPlayerIndex * 0x2F0) + (D_807444FC << 6) + 8)));
    WRITE_GFX(glistp++, 0xDA380003, (u32)&D_2000180);
    WRITE_GFX(glistp++, 0xE7000000, 0);
    WRITE_GFX(glistp++, 0xD9FDFFFF, 0);
    WRITE_GFX(glistp++, 0xFA0000FF, 0xFFFFFFFF);
    renderActorDisplayList(renderSetSegment6AndFog(glistp, actor->unk128, 1), actor);
}

extern void *gActivePlayerState;
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

extern Actor *gCurrentActor;

s32 func_806FFF88(void);
void func_80613C48(Actor *, s16, f32, f32);
void scriptSetActorRampTarget(Actor *, f32, f32);
void sfxPlayActorSound(void *, s32, s32, s32, s32, s32, f32, s32);
void sfxStopSlotSound(Actor *, s32);
void color5551CopyLerpToWhite(s16 *, s32 *, f32);
void slotQueueAddValue(s32, u8, s32);
s32 sfxAllocateChannel(s32, f32);
void sfxPlayOnFreeSlot(s32, s32, f32, f32, s32, s32);
void renderCallbacksRegister(void *, void *, s32);
void mathAngleBetweenPoints3D(s16 *, s16 *, f32, f32, f32, f32, f32, f32);
s32 playerStateQueueCallback(s16, void *, u8);
void assetFreeBuffer(s32, s32, s32);
void heapFreeDeferred(Mtx *);
void actorDespawn(Actor *);
void actorUpdateModelMatrix(Actor *, s32);
void renderSetupSegmentsAndFog(Gfx *, Actor *);
void func_806FF628(void);

void actorPhotoUpdate(void) {
    PanSubState *subState;
    s16 yaw;
    s16 pitch;
    f32 mtx1[4][4];
    f32 mtx2[4][4];
    s16 frameElapsed;
    s32 l1Angle;
    u8 pad;
    f32 t;

    subState = gCurrentActor->unk174;
    pad = 0;
    if (!(gCurrentActor->flags & 0x10)) {
        subState->unk10 = 0x5A;
        gCurrentActor->flags |= 0x400;
        gCurrentActor->unk12A = 0x3E8;
        subState->unk4 = (s16 *)func_806FFF88();
        func_80613C48(gCurrentActor, 0x40B, 0, 0);
        scriptSetActorRampTarget(gCurrentActor, 0.15f, 0);
    }
    gCurrentActor->flags &= ~4;
    frameElapsed = 0x5A - subState->unk10;
    if (frameElapsed == 0xD) {
        sfxPlayActorSound(gCurrentActor, 0x222, 0, 0, 0, 0xFF, 1.0f, -1);
    }
    if (frameElapsed == 0x1B) {
        sfxStopSlotSound(gCurrentActor, 0);
    }
    t = PAN_MIN(1.0, ((frameElapsed - 0x1E) < 0 ? 0 : (frameElapsed - 0x1E)) / 60.0f * 5.0);
    if (t < 1.0 && gCurrentActor->actorType != 0xD9) {
        color5551CopyLerpToWhite((s16 *)subState->unk4, &(&subState->unk8)[D_807444FC], t);
        animSetNodeItem(gCurrentActor, 0, 0, (&subState->unk8)[D_807444FC]);
    } else {
        animSetNodeItem(gCurrentActor, 0, 0, (s32)subState->unk4);
        if (gCurrentActor->unk155[0] == 0) {
            if (((PlayerControlState *)gActivePlayerState)->unk1EC == 1) {
                slotQueueAddValue(0xC, ((PlayerControlState *)gActivePlayerState)->unk1A4, 1);
                sfxAllocateChannel(0x2E, 1.0f);
            } else if (((PlayerControlState *)gActivePlayerState)->unk1EC == 2) {
                sfxPlayOnFreeSlot(0x98, 0x7FFF, 63.0f, 1.0f, 0, 0x80);
            }
            gCurrentActor->unk155[0]++;
        }
        if (((PlayerControlState *)gActivePlayerState)->unk1EC != 0xFF && subState->unk10 != 0) {
            renderCallbacksRegister(&func_806FF628, gCurrentActor, 3);
        }
    }
    mathAngleBetweenPoints3D(&pitch, &yaw, ((CameraView *)gPlayerSlots)->unk210, ((CameraView *)gPlayerSlots)->unk214, ((CameraView *)gPlayerSlots)->unk218, ((CameraView *)gPlayerSlots)->unk228, ((CameraView *)gPlayerSlots)->unk22C, ((CameraView *)gPlayerSlots)->unk230);
    t = PAN_MIN(30.0, frameElapsed) / 30.0;
    gCurrentActor->yaw = yaw;
    l1Angle = (f32)pitch - (2048.0f + -2048.0f * t);
    gCurrentActor->roll = l1Angle;
    guRotateF(mtx1, pitch / 4095.0 * 360.0, 1.0f, 0.0f, 0.0f);
    guRotateF(mtx2, yaw / 4095.0 * 360.0, 0.0f, 1.0f, 0.0f);
    guMtxCatF(mtx1, mtx2, mtx1);
    guTranslateF(mtx2, ((CameraView *)gPlayerSlots)->unk210, ((CameraView *)gPlayerSlots)->unk214, ((CameraView *)gPlayerSlots)->unk218);
    guMtxCatF(mtx1, mtx2, mtx1);
    guMtxXFMF(mtx1, 0.0f, 0.0f, -30.0f * t, &gCurrentActor->x, &gCurrentActor->y, &gCurrentActor->z);
    if (subState->unk10 != 0) {
        subState->unk10--;
    } else {
        gCurrentActor->flags &= ~0x8000;
        gCurrentActor->unk128 -= 0xA;
        if (gCurrentActor->unk128 <= 0) {
            pad = 1;
        }
    }
    if (pad || !(subState->unk0->unk1F0 & 0x8000)) {
        if (subState->unk0->unk1EC == 1) {
            playerStateQueueCallback(0x58, NULL, 0);
        }
        sfxStopSlotSound(gCurrentActor, 0);
        subState->unk0->unk1F0 &= ~0x8000;
        subState->unk0->unk1EC = 0xFF;
        if (gCurrentActor->actorType == 0xD9) {
            assetFreeBuffer((s32)subState->unk4, 0xF6, 0x45);
        } else {
            heapFreeDeferred((Mtx *)subState->unk4);
        }
        subState->unk0->unk88 = 0;
        actorDespawn(gCurrentActor);
    } else {
        guTranslateF((f32 (*)[4])((u8 *)gCurrentActor + 0xC), 0.0f, -70.0f, 0.0f);
        actorUpdateModelMatrix(gCurrentActor, 1);
        renderCallbacksRegister(&renderSetupSegmentsAndFog, gCurrentActor, 3);
    }
}

void actorPhotoUpdate(void);

void actorPhotoUpdateEntry(void) {
    actorPhotoUpdate();
}

/* Empty stub: the 8 bytes after actorPhotoUpdateEntry (a bare `jr ra; nop`) are a second
   function that splat merged into actorPhotoUpdateEntry for lack of a symbol. */
void func_806998E8(void) {
}

void actorSagWaveUpdate(u8, u8);

void func_806998F0(void) {
    actorSagWaveUpdate(8, 0);
}

extern Actor *gCurrentActor;

void func_80699914(void) {
    if (!(gCurrentActor->flags & 0x10)) {
        gCurrentActor->unk12A = 0x3E8;
    }
    actorSagWaveUpdate(0x1C, 1);
}

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
void scriptSetActorRampTarget(Actor *, f32, f32);
Mtx *heapAlloc(s32);
void actorUpdateModelMatrix(Actor *, s32);
s32 actorCheckAlwaysFalse(void);
void actorAddNodeForceSlot(f32, u8);
f32 sinApprox(f32);
void *memcpy(void *, const void *, unsigned int);

void actorSagWaveUpdate(u8 numNodes, u8 waveType) {
    f32 posOffsets[32];
    f32 nodeForces[26];
    f32 waveForce;
    WaveState *state;
    s32 i;
    s32 j;
    u8 found;
    f32 dist;

    state = (WaveState *)gCurrentActor->unk174;
    if (!(gCurrentActor->flags & 0x10)) {
        ((NodeListHead *)gCurrentActor->unk4)->unk24 = (WaveNode *)heapAlloc((numNodes + 1) * 0x10);
        for (i = 0; i < numNodes; i++) {
            ((WaveNode *)((NodeListHead *)gCurrentActor->unk4)->unk24)[i].unk0 = i;
            if (i != numNodes - 1) {
                ((WaveNode *)((NodeListHead *)gCurrentActor->unk4)->unk24)[i].unk1 = i + 1;
            } else {
                ((WaveNode *)((NodeListHead *)gCurrentActor->unk4)->unk24)[i].unk1 = 0xFF;
            }
            ((WaveNode *)((NodeListHead *)gCurrentActor->unk4)->unk24)[i].unk4 = 0.0f;
            ((WaveNode *)((NodeListHead *)gCurrentActor->unk4)->unk24)[i].unkC = 0.0f;
            ((WaveNode *)((NodeListHead *)gCurrentActor->unk4)->unk24)[i].unk8 = 0.0f;
        }
        ((WaveNode *)((NodeListHead *)gCurrentActor->unk4)->unk24)[numNodes].unk0 = 0xFF;
        for (i = 0; i < numNodes; i++) {
            state->unk4[i] = 0.0f;
        }
        state->unk0 = -1;
        state->unk94 = 0;
        for (i = 0; i < 4; i++) {
            state->unkB8[i] = 0;
        }
    }
    if ((actorCheckAlwaysFalse() != 0) && (state->unk0 == -1)) {
        state->unk0 = 10;
    }
    if (state->unk0 > 0) {
        state->unk0--;
    }
    if (state->unk0 == 0) {
        func_80613C48(gCurrentActor, 0x403, 0, 1.0f);
        scriptSetActorRampTarget(gCurrentActor, 4.0f, 1.0f);
        state->unk0 = -2;
    }
    for (i = 0; i < numNodes; i++) {
        posOffsets[i] = 0.0f;
        nodeForces[i] = 0.0f;
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
                switch (waveType) {
                case 0:
                    actorAddNodeForceSlot(((ProximityGlobals *)&D_807FBB70)->entries[i].unk8, waveType);
                    break;
                case 1:
                    actorAddNodeForceSlot(((ProximityGlobals *)&D_807FBB70)->entries[i].unk0, waveType);
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
                actorAddNodeForceSlot(state->unk84[i], waveType);
            }
            i++;
        } while (i < (s32)state->unk94);
        i = 0;
    }
    memcpy(state->unk74, &D_807FBBEC, 0x10);
    state->unk94 = D_807FBB70.unk39;
    if ((s32)state->unk94 > 0) {
        do {
            switch (waveType) {
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
            switch (waveType) {
            case 0:
                if ((f64)((ProximityGlobals *)&D_807FBB70)->entries[i].unk8 / 843.0 > 0) {
                    waveForce = (f32)((f64)((ProximityGlobals *)&D_807FBB70)->entries[i].unk8 / 843.0);
                } else {
                    waveForce = (f32)-((f64)((ProximityGlobals *)&D_807FBB70)->entries[i].unk8 / 843.0);
                }
                break;
            case 1:
                if ((f64)((ProximityGlobals *)&D_807FBB70)->entries[i].unk0 / 480.0 > 0) {
                    waveForce = (f32)((f64)((ProximityGlobals *)&D_807FBB70)->entries[i].unk0 / 480.0);
                } else {
                    waveForce = (f32)-((f64)((ProximityGlobals *)&D_807FBB70)->entries[i].unk0 / 480.0);
                }
                break;
            }
            i++;
            for (j = 0; j < numNodes; j++) {
                if (waveForce < (f32)j) {
                    dist = (f32)j - waveForce;
                } else {
                    dist = -((f32)j - waveForce);
                }
                switch (waveType) {
                case 0:
                    dist = (f32)(3.0 - (f64)dist);
                    if (dist < 0.0) {
                        dist = 0.0f;
                    }
                    posOffsets[j] -= 45.0f * dist;
                    break;
                case 1:
                    dist = (f32)(7.0 - (f64)dist);
                    if (dist < 0.0) {
                        dist = 0.0f;
                    }
                    posOffsets[j] -= 70.0f * dist;
                    break;
                }
            }
        } while (i < (s32)D_807FBB70.unk39);
        i = 0;
    }
    for (i = 0; i < 4; i++) {
        if (state->unkB8[i] != 0) {
            for (j = 0; j < numNodes; j++) {
                if (state->unk98[i] < (f32)j) {
                    dist = (f32)j - state->unk98[i];
                } else {
                    dist = -((f32)j - state->unk98[i]);
                }
                dist = (f32)(3.0 - (f64)dist);
                if (dist < 0.0) {
                    dist = 0.0f;
                }
                waveForce = sinApprox((f32)((f64)state->unkB8[i] * 0.5));
                nodeForces[j] = ((dist * state->unkA8[i]) * waveForce) + nodeForces[j];

            }
            state->unkA8[i] = (f32)((f64)state->unkA8[i] - ((f64)state->unkA8[i] / 20.0));
            if ((f64)state->unkA8[i] < 0.5) {
                state->unkB8[i] = 0;
            } else {
                state->unkB8[i]++;
            }
        }
    }
    for (i = 0; i < numNodes; i++) {
        if (state->unk4[i] < posOffsets[i]) {
            switch (waveType) {
            case 0:
                state->unk4[i] = (f32)(((f64)(posOffsets[i] - state->unk4[i]) * 0.25) + (f64)state->unk4[i]);
                break;
            case 1:
                state->unk4[i] = (f32)(((f64)(posOffsets[i] - state->unk4[i]) / 15.0) + (f64)state->unk4[i]);
                break;
            }
            if (posOffsets[i] < state->unk4[i]) {
                state->unk4[i] = posOffsets[i];
            }
        }
        if (posOffsets[i] < state->unk4[i]) {
            switch (waveType) {
            case 0:
                state->unk4[i] = (f32)((f64)state->unk4[i] - ((f64)(state->unk4[i] - posOffsets[i]) * 0.5f));
                break;
            case 1:
                state->unk4[i] = (f32)((f64)state->unk4[i] - ((f64)(state->unk4[i] - posOffsets[i]) * 0.125));
                break;
            }
            if (state->unk4[i] < posOffsets[i]) {
                state->unk4[i] = posOffsets[i];
            }
        }
        ((WaveNode *)((NodeListHead *)gCurrentActor->unk4)->unk24)[i].unk8 = state->unk4[i] + nodeForces[i];
    }
    ((WaveNode *)((NodeListHead *)gCurrentActor->unk4)->unk24)[0].unk8 = 0.0f;
    *(f32 *)((u8 *)((NodeListHead *)gCurrentActor->unk4)->unk24 + (numNodes << 4) - 8) = 0.0f;  // FAKE: byte-offset form stops the CSE of numNodes * 16 across the calls
    actorUpdateModelMatrix(gCurrentActor, 0);
}

typedef struct {
    u8 pad0[0x98];
    f32 unk98[4];
    f32 unkA8[4];
    u8 unkB8[4];
} ActorMotionSlots;

/* arg1 is u8: IDO homes the raw incoming a1 to its caller slot (sw a1,4(sp))
   even in this leaf function and re-narrows it with andi before use. */
void actorAddNodeForceSlot(f32 forceMagnitude, u8 slotMode) {
    ActorMotionSlots *slots = (ActorMotionSlots *)gCurrentActor->unk174;
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
        switch (slotMode) {
        case 0:
            slots->unkA8[i] = 10.0f;
            temp = (f64)forceMagnitude / 843.0;
            if (temp > 0.0) {
                slots->unk98[i] = (f32)temp;
                return;
            }
            slots->unk98[i] = (f32)-temp;
            return;
        case 1:
            slots->unkA8[i] = 12.0f;
            temp = (f64)forceMagnitude / 480.0;
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

extern u8 D_807FBBA9;

typedef struct {
    u8 pad0[0x7C];
    Actor *unk7C[4];
} TextActorList;

s32 actorCheckAlwaysFalse(void) {
    s32 i;
    s32 v;

    for (i = 0; i < D_807FBBA9; i++) {
        v = ((TextActorList *)&D_807FBB70)->unk7C[i]->actorType;
        if (v != 2 && v != 3) { // FAKE: keeps both state tests as beq-to-latch (dead carrier v)
            v = 0;
        }
        if (v == 5) {} // FAKE: dead test of the carrier
        if (i == 5) {} // FAKE: consumes a ring temp (t0)
    }
    if (gCurrentActor->actorType == 0x1F) {
        return 0;
    }
    return 0;
}

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

void actorSagSingleUpdate(void) {
    ProximityState *state;
    f32 acc;
    f32 dist;
    f32 value;
    s32 flags;
    s32 i;

    flags = gCurrentActor->flags;
    acc = 0.0f;
    state = (ProximityState *)gCurrentActor->unk174;
    if (!(flags & 0x10)) {
        gCurrentActor->flags = flags | 0x400;
        ((ModelNodeList *)gCurrentActor->unk4)->unk24 = (ModelNodeRecord *)heapAlloc(0x20);
        ((ModelNodeList *)gCurrentActor->unk4)->unk24->unk0 = 1;
        ((ModelNodeList *)gCurrentActor->unk4)->unk24->unk1 = 0xFF;
        ((ModelNodeList *)gCurrentActor->unk4)->unk24->unk4 = 0.0f;
        ((ModelNodeList *)gCurrentActor->unk4)->unk24->unkC = 0.0f;
        ((ModelNodeList *)gCurrentActor->unk4)->unk24->unk8 = 0.0f;
        ((ModelNodeList *)gCurrentActor->unk4)->unk24->unk10 = 0xFF;
        gCurrentActor->unk12A = 0x3E8;
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
    ((ModelNodeList *)gCurrentActor->unk4)->unk24->unk8 = 0.0 - (sinApprox((f32)((f64)state->unkC * 0.5)) * state->unk8 + state->unk0);
    state->unk4 = D_807FBB70.unk39;
    actorUpdateModelMatrix(gCurrentActor, 0);
}
#undef PROX_SRC

typedef struct {
    s16 unk0;
    u8 pad2[2];
    f32 unk4;
} SpotLightState;

typedef struct {
    f32 unk0;
    s32 unk4;
    s32 unk8;
    s32 unkC;
    f32 unk10;
    f32 unk14;
} SpotLightConfig;

void actorScriptStart(Actor *, s32);
void func_80613C48(Actor *, s16, f32, f32);
void actorUpdateModelMatrix(Actor *, s32);
extern u8 D_807FBD70;
extern s32 gCurrentMap;
extern s16 D_807503A0;
void lightSetFovAngles(f32, f32);
void lightSetFlags(u8);
void lightSetTargetId(s16);
s32 actorGetNodePos(Actor *, s32, f32 *, f32 *, f32 *);
void lightAdd(f32, f32, f32, f32, f32, f32, f32, s32, s32, s32, s32);

void actorSpotLightUpdate(void) {
    f32 targetPos[3];
    f32 sourcePos[3];
    u16 red;
    u16 green;
    u16 blue;
    SpotLightState *lightState;

    lightState = (SpotLightState *)gCurrentActor->unk174;
    if (!(gCurrentActor->flags & 0x10)) {
        func_80613C48(gCurrentActor, 0x402, 0, 1.0f);
        if (gCurrentMap == 6) {
            actorScriptStart(gCurrentActor, 0x297);
        }
        gCurrentActor->flags |= 0x400;
        lightState->unk0 = 0;
        lightState->unk4 = 1.0f;
    }
    scriptSetActorRampTarget(gCurrentActor, ((SpotLightConfig *)gCurrentActor->unk124)->unk0, 1.0f);
    if (D_807FBD70 == 4) {
        lightState->unk0 = D_807503A0;
        lightState->unk4 = 0.0f;
    }
    if (lightState->unk0 == 0) {
        red = ((SpotLightConfig *)gCurrentActor->unk124)->unk4;
        green = ((SpotLightConfig *)gCurrentActor->unk124)->unk8;
        blue = ((SpotLightConfig *)gCurrentActor->unk124)->unkC;
        red = (u16)(u32)((f64)(u32)red * (f64)lightState->unk4);
        green = (u16)(u32)((f64)(u32)green * (f64)lightState->unk4);
        blue = (u16)(u32)((f64)(u32)blue * (f64)lightState->unk4);
        lightState->unk4 = (f32)((f64)lightState->unk4 + 0.05);
        if (lightState->unk4 > 1.0) {
            lightState->unk4 = 1.0f;
        }
        if (gCurrentActor->flags & 0x10) {
            if ((f64)((SpotLightConfig *)gCurrentActor->unk124)->unk10 != 0.0 || (f64)((SpotLightConfig *)gCurrentActor->unk124)->unk14 != 0.0) {
                lightSetFovAngles(((SpotLightConfig *)gCurrentActor->unk124)->unk10, ((SpotLightConfig *)gCurrentActor->unk124)->unk14);
            }
            lightSetFlags(2);
            lightSetTargetId(gCurrentActor->chunkIndex);
            actorGetNodePos(gCurrentActor, 2, &targetPos[0], &targetPos[1], &targetPos[2]);
            lightAdd((f32)((f64)gCurrentActor->x + 0.3), gCurrentActor->y, gCurrentActor->z, targetPos[0], targetPos[1], targetPos[2], 0.0f, 1, red, green, blue);
        }
    } else {
        lightState->unk0 = lightState->unk0 - 1;
    }
    actorUpdateModelMatrix(gCurrentActor, 0);
}

void actorSpotLightUpdate(void);

void actorSpotLightUpdateEntry(void) {
    actorSpotLightUpdate();
}

typedef struct CameraPoseView {
    u8 pad0[0x210];
    f32 unk210;
    f32 unk214;
    f32 unk218;
    u8 pad21C[0xC];
    f32 unk228;
    f32 unk22C;
    f32 unk230;
} CameraPoseView;

typedef struct LinkedActorView {
    u8 pad0[0xEC];
    s16 unkEC;
    u8 padEE[0x66];
    u8 unk154;
    u8 pad155[0xA];
    u8 unk15F;
} LinkedActorView;

extern Actor *D_807FBB4C;
extern s16 D_80750378;
extern s32 D_8076A068;
extern u8 D_8071FE08[];
extern u8 D_80720E14[];
void effectScaleSpinUpdate();
void actorDespawn(Actor *);
void actorSetCollisionRadius(Actor *, f32);
void func_8067ACB4(Actor *);
void billboardSubmit(Actor *, s32, s32, s32, s32, s32, s32, s32, s32, s32, f32);
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
    s32 *p = gCurrentActor->unk174;
    LinkedActorView *link;

    if (!(gCurrentActor->flags & 0x10)) {
        gCurrentActor->contactFlags &= 0xFFFE;
        gCurrentActor->unk144 = 2;
        actorSetCollisionRadius(gCurrentActor, 60.0f);
        actorAppendModelNode(gCurrentActor, 0.0f, 0.0f, 0.0f, 60.0f, -1);
        actorAppendModelSubNode(gCurrentActor, 0.0f, 0.0f, 0.0f, -1);
        func_807149FC(-1);
        func_807149B8(1);
        func_8071498C(effectScaleSpinUpdate);
        func_80714C08(D_80720E14, 0.9f, gCurrentActor, 1, 2);
        *p = D_8076A068;
        gCurrentActor->flags |= 0x80000;
        collisionCheckActorFloor(gCurrentActor, gCurrentActor->x, gCurrentActor->y, gCurrentActor->z, &gCurrentActor->unkA4);
    }
    func_8067ACB4(gCurrentActor);
    billboardSubmit(gCurrentActor, 0x3C8, 0x40, 0x40, 0x1E, 0x1E, 1, 0x4B, 0x78, 0, 1.0f);
    link = (LinkedActorView *)gCurrentActor->unk11C;
    if (link != NULL) {
        if (link->unk154 != 2 && link->unk154 != 0x26) {
            actorDespawn(gCurrentActor);
            return;
        }
        if (gCurrentActor->unk15F == link->unk15F) {
            if ((gCurrentActor->x - D_807FBB4C->x) * (gCurrentActor->x - D_807FBB4C->x) + (gCurrentActor->z - D_807FBB4C->z) * (gCurrentActor->z - D_807FBB4C->z) > 900.0f) {
                ((LinkedActorView *)gCurrentActor->unk11C)->unkEC = (s16)(mathAngleBetweenPointsDeg((s32)gCurrentActor->x, (s32)gCurrentActor->z, (s32)D_807FBB4C->x, (s32)D_807FBB4C->z) - mathAngleBetweenPointsDeg((s32)((CameraPoseView *)gPlayerSlots)->unk228, (s32)((CameraPoseView *)gPlayerSlots)->unk230, (s32)((CameraPoseView *)gPlayerSlots)->unk210, (s32)((CameraPoseView *)gPlayerSlots)->unk218));
            }
            lightAdd(gCurrentActor->x, gCurrentActor->y, gCurrentActor->z, 0.0f, 0.0f, 0.0f, 100.0f, 0, 0xFF, 0xFF, 0);
        }
        if (D_807FBD70 == 9) {
            sfxPlayFromActorWithAltitudeCheck(gCurrentActor, 0x1CE, 0xFF, 0x7F, 0x1E);
            func_80714CC0(D_8071FE08, 1.0f, gCurrentActor->x, gCurrentActor->y, gCurrentActor->z);
            actorAppendCallback((Actor *)gCurrentActor->unk11C, gCurrentActor, 0x02000000, gCurrentActor->unk15F, 0, 0);
            actorDespawn(gCurrentActor);
        }
        if (gCurrentMap != 0x48 && gCurrentMap != 0x11 && (u32)(*p + D_80750378) < (u32)D_8076A068) {
            actorAppendCallback((Actor *)gCurrentActor->unk11C, gCurrentActor, 0x02000000, 0xFF, 0, 0);
            actorDespawn(gCurrentActor);
        }
    } else {
        actorDespawn(gCurrentActor);
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
    s16 *p = gCurrentActor->unk174;
    CameraPoseView *cam = D_807FBB4C->unk174;
    s32 i;
    f32 x;
    f32 y;
    f32 z;
    s32 j;
    void *sel;

    if (!(gCurrentActor->flags & 0x10)) {
        gCurrentActor->unk144 = 1;
        gCurrentActor->flags |= 0x400;
        actorScriptStart(gCurrentActor, 0x298);
        *p = 0;
        sfxAllocateChannel(0x3B, 1.0f);
    } else {
        actorGetNodePos(gCurrentActor, 1, &x, &y, &z);
        cam->unk210 = x;
        cam->unk214 = y;
        cam->unk218 = z;
        if (gCurrentActor->unk155[0] < 4) {
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
                    func_80714C08(sel, 0.6f, gCurrentActor, j, 0);
                }
            }
        }
        switch (gCurrentActor->unk155[0]) {
            case 0:
                *p += 0x1E;
                break;
            case 1:
                D_807FBB4C->unk155[0]++;
                gCurrentActor->unk155[0]++;
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
                gCurrentActor->flags &= ~0x8000;
                gCurrentActor->unk128 = 0xFF;
                gCurrentActor->unk155[0]++;
                break;
            case 4:
                *p -= 0x2A;
                if (*p < 0) {
                    *p = 0;
                }
                gCurrentActor->unk128 -= 0x28;
                if (gCurrentActor->unk128 < 0x28) {
                    D_807FBB4C->unk155[0]++;
                    sfxStopChannel(0x3B, 0);
                    actorDespawn(gCurrentActor);
                }
                break;
        }
    }
    gCurrentActor->yaw += *p;
    actorUpdateModelMatrix(gCurrentActor, 0);
}

extern s16 D_80744490;
s32 actorTableContains();
void textMarkerUpdateMatrix(void);
void actorListSpawnNodeEntryDefault(s16, f32, f32, f32, s16, f32, s32);
s32 flagGet(s32, s32);

s32 actorHasCallbackTargetThisFrame(void) {
    ActorCallbackNode *node = gCurrentActor->callbacks;

    while (node != NULL) {
        if ((u32)node->callback == 0x8000) {
            Actor *actor;
            void *sub;
            if (actorTableContains(node->unk8) != 0) {
                actor = (Actor *)node->unk8;
                if (actor->collisionFlags & 1) {
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


typedef struct ActorSub174View {
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
} ActorSub174View;

typedef struct ActorSub124View {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ s32 unk4;
} ActorSub124View;

typedef struct ActorNamePair {
    /* 0x0 */ s32 unk0;
    /* 0x4 */ s32 unk4;
} ActorNamePair;

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
extern ActorNamePair D_807503A4;

s32 actorHasActiveMovementFlags(Actor *);
s32 actorListFindIdByActor(Actor *);
void actorListSetPosByActor(Actor *, f32, f32, f32);
void actorListSpawnNodeEntry(s16, f32, f32, f32, s16, f32, s32, s32);
void actorApplyVelocity(Actor *);
void actorUpdateFloorContactAndTilt(Actor *, f32);
void actorCallbackMaskEnable(Actor *, s32);
void actorCallbackMaskDisable(Actor *, s32);
void actorCollisionEventsCancel(void *, s32);
void func_8068A2FC(Actor *);
void actorReleaseFromPlayerHold(Actor *);
void sfxSetVolumeAndPan(u8, f32, f32);
void actorSpawnNodeEntryScaled(s32, f32, f32, f32, s32, s32, s32, s32);
s32 actorAngleInArc(Actor *, s16);
f32 randomFloat(void);
void func_8071496C(s16);
void func_80714998(s32);
void camStartShake(s32, s32, s32);
void effectLightPulseOscillate(void);
void effectTumbleBounceUpdate(void);

void textMarkerUpdateMatrix(void) {
    ActorSub174View *markerView;
    f32 mtxA[4][4];
    f32 mtxB[4][4];
    f32 dx;
    f32 dy;
    f32 dz;
    f32 offsetX;
    f32 offsetY;
    f32 offsetZ;
    ActorNamePair namePair;
    s32 i;
    s32 stateActive;
    s16 ang;
    s32 pad84[3];
    s32 spawnArgs[2];
    s32 randVal;
    s32 pad74;  // pad: keeps particleLoopIdx at 0x70
    s32 particleLoopIdx;
    void (*volatile callback)(void);  // FAKE: retain the callback's original stack home

    markerView = gCurrentActor->unk174;
    if (!(gCurrentActor->flags & 0x10)) {
        *(s16 *)((u8 *)gCurrentActor + 0xFA) = 0x270F;
        gCurrentActor->unkA4 = 99999.0f;
        actorUpdateFloorContactAndTilt(gCurrentActor, 0);
        if (actorHasActiveMovementFlags(gCurrentActor) != 0) {
            gCurrentActor->unk144 = 2;
            gCurrentActor->flags2 |= 1;
            gCurrentActor->state = 2;
            *(u8 *)((u8 *)gCurrentActor + 0x155) = 1;
            markerView->unk1C = 0x1E;
        }
        markerView->unk28 = ((ActorSub124View *)gCurrentActor->unk124)->unk0;
        if (markerView->unk28 != 0) {
            markerView->unk4 = gCurrentActor->x;
            markerView->unk8 = gCurrentActor->y;
            markerView->unkC = gCurrentActor->z;
            markerView->unk10 = gCurrentActor->unk4->unk34 / 0.15;
        }
        if (((ActorSub124View *)gCurrentActor->unk124)->unk4 == 1) {
            gCurrentActor->unk132 = 2;
        } else {
            gCurrentActor->unk132 = 1;
        }
        switch (gCurrentActor->actorType) {
        case 0x43:
            if (flagGet(0x9A, 0) != 0) {
                func_8068A2FC(gCurrentActor);
            }
            break;
        case 0x3D:
            if (gCurrentMap == 0xC3) {
                if (flagGet(0x267, 0) != 0) {
                    func_8068A2FC(gCurrentActor);
                }
            }
            if (gCurrentMap == 0x26) {
                gCurrentActor->renderFlags |= 0x400;
            }
            break;
        }
        switch (gCurrentActor->actorType) {
        case 0x3F:
        case 0x40:
        case 0x41:
        case 0x42:
            gCurrentActor->renderFlags |= 0x420;
            break;
        }
    }
    if (D_807FBB94 != 0) {
        markerView->unk14 = D_807FBB98;
        gCurrentActor->state = 1;
        actorCallbackMaskDisable(gCurrentActor, 0x8000);
        actorCollisionEventsCancel(markerView->unk14, 1);
        gCurrentActor->unk144 = 0x2C;
    }
    if (D_807FBB95 != 0) {
        gCurrentActor->state = 2;
        *(u8 *)((u8 *)gCurrentActor + 0x155) = 0;
        markerView->unk1C = 0x1E;
        gCurrentActor->unk144 = 0x3C;
        actorCallbackMaskEnable(gCurrentActor, 0x8000);
        if (gCurrentMap == 7 && actorListFindIdByActor(gCurrentActor) == 0x17) {
            actorListSetPosByActor(gCurrentActor, gCurrentActor->x, gCurrentActor->unkA4, gCurrentActor->z);
        }
    }
    if (gCurrentMap == 0x22 && gCurrentActor->actorType == 0x3D &&
        (gCurrentActor->state == 0 || gCurrentActor->state == 2)) {
        if (gCurrentActor->x >= 3242.0 && gCurrentActor->z >= 252.0 &&
            gCurrentActor->x <= 3842.0 && gCurrentActor->z <= 852.0) {
            gCurrentActor->state = 4;
        }
    }
    if (D_807FBB85 != 0 || D_807FBD70 == 9) {
        gCurrentActor->state = 4;
        actorReleaseFromPlayerHold(gCurrentActor);
    }
    if (D_807FBB9C != 0) {
        gCurrentActor->state = 3;
        gCurrentActor->unk144 = 0x3C;
        actorCallbackMaskEnable(gCurrentActor, 0x8000);
        gCurrentActor->yaw = *(s16 *)((u8 *)&D_807FBB70 + 0x36);
        *(s16 *)((u8 *)gCurrentActor + 0xEE) = *(s16 *)((u8 *)&D_807FBB70 + 0x36);
        *(f32 *)((u8 *)gCurrentActor + 0xC0) = *(f32 *)((u8 *)&D_807FBB70 + 0x30);
        gCurrentActor->speedXZ = (f32)*(s16 *)((u8 *)&D_807FBB70 + 0x34);
        actorCollisionEventsCancel(markerView->unk14, 1);
        if (gCurrentActor->actorType == 0x43 && gCurrentMap == 0x1E) {
            gCurrentActor->flags |= 0x200000;
            markerView->unk0 = D_8076A068;
        }
    }
    if (gCurrentActor->actorType == 0x55) {
        if (actorHasActiveMovementFlags(gCurrentActor) != 0) {
            gCurrentActor->flags |= 0x400;
        } else {
            gCurrentActor->flags &= ~0x400;
        }
    }
    func_8067ACB4(gCurrentActor);
    switch (gCurrentActor->actorType) {
    case 0x3F:
    case 0x40:
    case 0x41:
    case 0x42:
        for (i = 0; i < D_807FBDC4; i++) {
            if (D_807FBB70.unk258[i] == 1) {
                markerView->unk2A = 0;
                gCurrentActor->state = 5;
            }
        }
        break;
    }
    switch (gCurrentActor->state) {
    case 0:
        gCurrentActor->unk144 = 2;
        gCurrentActor->renderFlags |= 8;
        gCurrentActor->flags |= 0x80000000;
        gCurrentActor->flags2 |= 1;
        if (actorHasCallbackTargetThisFrame() != 0) {
            gCurrentActor->state = 4;
        }
        break;
    case 1:
        gCurrentActor->flags2 &= 0xFFFE;
        gCurrentActor->renderFlags &= ~8;
        gCurrentActor->flags &= 0x7FFFFFFF;
        markerView->unk20 = (f32)(((f64)markerView->unk14->yaw / 4095.0) * 360.0);
        break;
    case 2:
        gCurrentActor->renderFlags &= ~8;
        gCurrentActor->flags &= 0x7FFFFFFF;
        if (markerView->unk1C != 0) {
            markerView->unk1C--;
        }
        if (markerView->unk1C == 0 && (gCurrentActor->contactFlags & 1)) {
            gCurrentActor->state = 0;
        } else if (actorHasActiveMovementFlags(gCurrentActor) != 0) {
            markerView->unk1C = 0x1E;
        }
        if ((gCurrentActor->contactFlags & 1) && *(u8 *)((u8 *)gCurrentActor + 0x155) == 0) {
            if (gCurrentActor->actorType == 0x55) {
                sfxPlayFromActorWithAltitudeCheck(gCurrentActor, 0x8B, 0x64, 0x7F, 0x14);
                sfxPlayFromActorWithAltitudeCheck(gCurrentActor, 0x97, 0x64, 0x7F, 0x14);
            } else {
                sfxPlayFromActorWithAltitudeCheck(gCurrentActor, 0x97, 0xFF, 0x7F, 0x14);
            }
            (*(u8 *)((u8 *)gCurrentActor + 0x155))++;
        }
        *(f32 *)((u8 *)gCurrentActor + 0xC0) = -200.0f;
        gCurrentActor->speedXZ = 0.0f;
        gCurrentActor->flags2 |= 1;
        if (actorHasCallbackTargetThisFrame() != 0) {
            gCurrentActor->state = 4;
        }
        break;
    case 3:
        *(f32 *)((u8 *)gCurrentActor + 0xC0) = *(f32 *)((u8 *)gCurrentActor + 0xC0) + D_807502E4;
        if (*(f32 *)((u8 *)gCurrentActor + 0xC0) < (f32)D_807502D0) {
            *(f32 *)((u8 *)gCurrentActor + 0xC0) = (f32)D_807502D0;
        }
        stateActive = 0;
        markerView->unk24 = markerView->unk24 - 10.0f;
        if (gCurrentActor->actorType == 0x43 && gCurrentMap == 0x1E &&
            (u32)(D_8076A068 - markerView->unk0) >= 0x5B) {
            stateActive = 1;
        }
        if (stateActive != 0 || (gCurrentActor->hasArcBounds != 0 && actorAngleInArc(gCurrentActor, gCurrentActor->yaw) == 0)) {
            gCurrentActor->state = 4;
        }
        gCurrentActor->flags2 &= 0xFFFE;
        gCurrentActor->renderFlags &= ~8;
        gCurrentActor->flags &= 0x7FFFFFFF;
        break;
    case 4:
        if (gCurrentActor->actorType == 0x3D && markerView->unk28 == 0) {
            switch (actorListFindIdByActor(gCurrentActor)) {
            case 0x17:
                if (flagGet(0x19, 0) == 0) {
                    actorSpawnNodeEntryScaled(0x2D, gCurrentActor->x, gCurrentActor->y + 10.0f,
                                  gCurrentActor->z, 0, 2, 0x19, 0);
                    sfxAllocateChannel(0x14, 1.0f);
                }
                break;
            case 6:
                if (flagGet(0x1D, 0) == 0) {
                    actorSpawnNodeEntryScaled(0x6E, gCurrentActor->x, gCurrentActor->y + 10.0f,
                                  gCurrentActor->z, 0, 2, 0x1D, 0);
                }
                break;
            }
        }
        sfxPlayFromActorWithAltitudeCheck(gCurrentActor, 0x162, 0xFF, 0x7F, 0x1E);
        if (!D_807FBC64) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
        if (markerView->unk28 == 0) {
            actorDespawn(gCurrentActor);
        }
        if (D_807FBB70.unk0 == 0) {
            namePair = D_807503A4;
            for (particleLoopIdx = 0; particleLoopIdx != 0x10; particleLoopIdx += 2) {
                offsetX = (f32)(((f64)((randomNonNegative() >> 15) % 8191) / 200.0) - 20.0);
                offsetY = (f32)(((f64)((randomNonNegative() >> 15) % 8191) / 200.0) - 20.0);
                offsetZ = (f32)(((f64)((randomNonNegative() >> 15) % 8191) / 200.0) - 20.0);
                func_8071496C(particleLoopIdx);
                if (D_807FBB94 && D_807FBB94) {}  // FAKE: ghost candidate: two reads in the particleLoopIdx loop make D_807FBB94 a high-priority v0 web (with the two tests below) that forces the shared switch temp to v1 / early markerView piece to v0
                func_807149B8(1);
                if (particleLoopIdx == 0) {
                    callback = effectLightPulseOscillate; func_80714950(0x100FA);  // LAYOUT: keep the callback store in the call's delay slot
                    func_8071498C(callback);
                } else {
                    func_8071498C(func_80717D4C);
                    func_80714950(-0x96 - ((randomNonNegative() >> 15) % 50));
                }
                func_80714CC0(&D_80720340, 1.6f, gCurrentActor->x + offsetX,
                              gCurrentActor->y + offsetY, gCurrentActor->z + offsetZ);
                if (gCurrentActor->actorType == 0x3D) {
                    offsetX = (2.0f * randomFloat()) - 1.0f;
                    offsetY = (2.0f * randomFloat()) - 1.0f;
                    offsetZ = (2.0f * randomFloat()) - 1.0f;
                    offsetX *= 30.0f;
                    offsetY *= 30.0f;
                    offsetZ *= 30.0f;
                    offsetY += 30.0f;
                    func_807149B8(1);
                    func_807149FC(0x3C);
                    func_8071498C(effectTumbleBounceUpdate);
                    func_80714998(2);
                    func_80714950(2);
                    randVal = randomNonNegative();
                    if (randVal) {}  // FAKE: block split between the randVal def and the call (steers ugen ring / uopt colouring)
                    dz = randomFloat();
                    func_80714CC0((void *)((s32 *)&namePair)[(randVal >> 15) % 2],
                                  (f32)(((f64)dz * 0.5) + 0.2),
                                  gCurrentActor->x + offsetX, gCurrentActor->y + offsetY,
                                  gCurrentActor->z + offsetZ);
                }
            }
            camStartShake(*(s32 *)((u8 *)D_807FBB4C->unk174 + 0x104), 0x14, 0xF);
        }
        if (markerView->unk28 != 0) {
            gCurrentActor->state = 0xA;
            gCurrentActor->unk138 = 0;
            gCurrentActor->unk144 = 1;
            gCurrentActor->flags &= ~4;
        }
        break;
    case 5:
        gCurrentActor->renderFlags &= ~8;
        gCurrentActor->flags &= 0x7FFFFFFF;
        gCurrentActor->flags2 &= 0xFFFE;
        markerView->unk2A = markerView->unk2A + 2;
        if (markerView->unk2A >= 0xFB) {
            markerView->unk2A = 0xFA;
        }
        if (*(s16 *)((u8 *)gCurrentActor + 0x6E) == -1) {
            sfxPlayActorSound(gCurrentActor, 0x11A, 0x64, 1, 0, 0x64, 1.0f, 0);
        } else {
            sfxSetVolumeAndPan(*(s16 *)((u8 *)gCurrentActor + 0x6E),
                               (f32)(((f64)(u32)markerView->unk2A / 400.0) + 0.5), 2.0f);
        }
        lightAdd(gCurrentActor->x, gCurrentActor->y + 30.0f, gCurrentActor->z,
                 0, 0.0f, .0f, (f32)(((f64)(u32)markerView->unk2A / 250.0) * 100.0), 0, 0xFF, 0xFF, 0);  // FAKE: .0f spelling = separate zero web (target: two distinct lightAdd zero webs)
        gCurrentActor->yaw = gCurrentActor->yaw + markerView->unk2A;
        gCurrentActor->y = gCurrentActor->unkA4;
        break;
    case 10:
        dz = D_807FBB4C->z - markerView->unkC;
        dx = D_807FBB4C->x - markerView->unk4;
        dy = D_807FBB4C->y - markerView->unk8;
        if ((dz * dz) + ((dx * dx) + (dy * dy)) > 2500.0f) {
            spawnArgs[0] = markerView->unk28;
            if (gCurrentActor->unk132 == 2) {
                spawnArgs[1] = 1;
            } else {
                spawnArgs[1] = 0;
            }
            actorListSpawnNodeEntry(*(s16 *)((u8 *)gCurrentActor + 0x5A), markerView->unk4, markerView->unk8,
                                    markerView->unkC, 0, markerView->unk10, 0, (s32)spawnArgs);
            actorDespawn(gCurrentActor);
        }
        break;
    case 0x63:
        break;
    }
    if (gCurrentActor->state == 2 || gCurrentActor->state == 3) {
        *(s16 *)((u8 *)gCurrentActor + 0xEE) = gCurrentActor->yaw;
        actorApplyVelocity(gCurrentActor);
        actorUpdateFloorContactAndTilt(gCurrentActor, 0);
        if (gCurrentActor->state == 3 && (gCurrentActor->contactFlags & 1) && !(gCurrentActor->prevContactFlags & 1)) {
            gCurrentActor->state = 4;
        }
        if (gCurrentActor->state == 2 && (gCurrentActor->contactFlags & 4)) {
            gCurrentActor->state = 4;
        }
        *(s16 *)((u8 *)gCurrentActor + 0xDC) = 0x3FF;
        *(s16 *)((u8 *)gCurrentActor + 0xDE) = 0x3FF;
    } else {
        gCurrentActor->unk110 = 0;
        gCurrentActor->contactFlags &= 0xFBF7;
    }
    if (D_807FBB94) {}  // FAKE: ghost candidate, extends the D_807FBB94 web over the gCurrentMap switch temp
    switch (gCurrentMap) {
    case 0x26:
    case 0x71:
    case 0xC2:
        if (gCurrentActor->actorType == 0x3D) {
            if (gCurrentActor->unk110 == 1) {
                if (D_807FBB94) {}  // FAKE: ghost candidate (see the particleLoopIdx loop), keeps the D_807FBB94 web live across the gCurrentMap switch
                gCurrentActor->flags |= 0x200000;
            } else {
                gCurrentActor->flags &= ~0x200000;
            }
        }
        break;
    }
    if (gCurrentActor->state != 0x63) {
        billboardSubmit(gCurrentActor, 0x3C8, 0x40, 0x40, 0x14, 0x14, 1, 0x64, 0x78, 0, 1.0f);
    }
    guScaleF(mtxA, gCurrentActor->unk4->unk34, gCurrentActor->unk4->unk38, gCurrentActor->unk4->unk3C);
    guRotateF(mtxB, markerView->unk24, 0.0, 1.0f, 0.0);
    guMtxCatF(mtxA, mtxB, mtxA);
    guRotateF(mtxB, (f32)(((f64)gCurrentActor->yaw / 4095.0) * 360.0), 0.0, 1.0f, 0.0);
    guMtxCatF(mtxA, mtxB, mtxA);
    guRotateF(mtxB, (f32)(0.0 - (f64)D_807FBC60), 1.0f, 0.0, 0.0);
    guMtxCatF(mtxA, mtxB, mtxA);
    guRotateF(mtxB, (markerView->unk20 + 90.0f) - D_807FBC64, 0.0, 1.0f, 0.0);
    guMtxCatF(mtxA, mtxB, mtxA);
    if (gCurrentActor->state == 3) {
        ang = *(s16 *)((u8 *)gCurrentActor + 0xDE);

        if (ang < 0x3E8) {
            guRotateF(mtxB, (f32)(-(((f64)*(s16 *)((u8 *)gCurrentActor + 0xDC) / 4095.0) * 360.0)),
                      0.0, 1.0f, 0.0);
            guMtxCatF(mtxA, mtxB, mtxA);
            ang = *(s16 *)((u8 *)gCurrentActor + 0xDE);
        }
        guRotateF(mtxB, (f32)(90.0 - (((f64)ang / 4095.0) * 360.0)), 1.0f, 0.0, 0.0);
        guMtxCatF(mtxA, mtxB, mtxA);
        if (*(s16 *)((u8 *)gCurrentActor + 0xDE) < 0x3E8) {
            guRotateF(mtxB, (f32)(((f64)*(s16 *)((u8 *)gCurrentActor + 0xDC) / 4095.0) * 360.0),
                      0.0, 1.0f, 0.0);
            guMtxCatF(mtxA, mtxB, mtxA);
        }
    }
    guTranslateF(mtxB, gCurrentActor->x, gCurrentActor->y, gCurrentActor->z);
    guMtxCatF(mtxA, mtxB, (f32 (*)[4])((u8 *)gCurrentActor + 0xC));
}


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

    if (!(gCurrentActor->flags & 0x10)) {
        frac = gCurrentActor->unk4->unk34 / 0.15;
        frac = frac - 1.0;
        if (frac < 0.0) {
            frac = 0.0f;
        }
        val = (u32)(80.0f * frac);
        gCurrentActor->unk130 = val;
        gCurrentActor->unk131 = val;
        gCurrentActor->unk12A = 0x2BC;
    }
    /* dz is computed before dx into a temp: this is what makes IDO emit the
       target's dx, dz, dy float load/sub scheduling (dx, dy, dz otherwise). */
    dzTmp = gCurrentActor->z - ((CameraPos *)gPlayerSlots)->unk218;
    dx = gCurrentActor->x - ((CameraPos *)gPlayerSlots)->unk210;
    dz = dzTmp;
    dy = gCurrentActor->y - ((CameraPos *)gPlayerSlots)->unk214;
    dist = dx * dx + dy * dy;
    if (dz * dz + dist < 18000.0) {
        gCurrentActor->flags |= 0x400;
    } else {
        gCurrentActor->flags &= ~0x400;
    }
    textMarkerUpdateMatrix();
}

void actorSpawnEffectAndTick(void) {
    if (!(gCurrentActor->flags & 0x10)) {
        gCurrentActor->unk130 = 0x3C;
        gCurrentActor->unk131 = 0x3C;
        actorListSpawnNodeEntryDefault(0x83, gCurrentActor->x, gCurrentActor->y, gCurrentActor->z,
                      0, 1.0f, (s32)gCurrentActor);
    }
    textMarkerUpdateMatrix();
    if (!(gCurrentActor->flags & 0x10)) {
        if (*(s32 *)((u8 *)gCurrentActor->unk124 + 0x8) == 1) {
            if (flagGet(0xFD, 0) != 0) {
                gCurrentActor->unk132 = 4;
            }
        }
    }
}

void func_8069D018(void) {
    Actor *actor = gCurrentActor;

    if (!(actor->flags & 0x10)) {
        actor->unk12A = 0x2BC;
    }
    textMarkerUpdateMatrix();
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
    textMarkerUpdateMatrix();
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
extern Actor *gSpawnedActor;

void textSpawnMarker(u8 fontStyle, s16 x, s16 y, s32 textStr, u16 duration, u16 delay, u8 colorMode, u8 extraFlags) {
    s32 len;
    TextMarkerState *sub;

    if (actorSpawn(0xE8, 0) != 0) {
        sub = gSpawnedActor->unk174;
        if (fontStyle & 0x80) {
            sub->unkA = gfxResourceCreate((s16)(fontStyle & 0xFF7F), textStr, 2, 160.0f, (f32)y, 0.0f);
            *(s16 *)((u8 *)gSpawnedActor + 0xEE) = 1;
            gSpawnedActor->y = (f32)y;
            return;
        }
        if (x == 0) {
            gSpawnedActor->x = (f32)((D_80744490 - textGetStringWidth((s16)fontStyle, textStr)) * 2);
        } else {
            gSpawnedActor->x = (f32)(x * 4);
        }
        gSpawnedActor->y = (f32)(y * 4);
        gSpawnedActor->z = (f32)fontStyle;
        gSpawnedActor->unk16A = 0xFF;
        gSpawnedActor->unk16B = 0xFF;
        gSpawnedActor->unk16C = 0xFF;
        len = strlen((char *)textStr) + 1;
        sub->unk0 = (void *)heapAlloc(len);
        _strcpy((char *)sub->unk0, (char *)textStr);
        sub->unk4 = duration;
        sub->unk6 = delay;
        sub->unk8 = colorMode;
        sub->unk9 = extraFlags;
    }
}

extern u8 gPlayerCount;
s32 func_80714450();
s32 func_807142D8();
s32 func_8071432C();
s32 menuIsTransitionTypeB();
void textSpawnMarker(u8, s16, s16, s32, u16, u16, u8, u8);

void textSpawnMarkerChecked(u8 fontStyle, s16 x, s16 y, s32 textStr, u16 duration, u16 delay, u8 colorMode, u8 extraFlags) {
    if (gPlayerCount < 2) {
        if (func_80714450() == 0) {
            if (func_807142D8() == 0) {
                if (func_8071432C() != 0 || menuIsTransitionTypeB() != 0) {
                    textSpawnMarker(fontStyle, x, y, textStr, duration, delay, colorMode, extraFlags);
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

void *renderAppendScaledMatrix(void *glistp, ActorPositionView *actor, s16 xOffset, f32 scale) {
    Mtx *temp;
    f32 mtxA[4][4];
    f32 mtxB[4][4];

    temp = heapAlloc(0x40);
    heapFreeDeferred(temp);
    guScaleF(mtxA, scale, scale, 1.0f);
    guTranslateF(mtxB, (f32)((f64)actor->unk7C + 2.0 * (f64)xOffset), actor->unk80, 0.0f);
    guMtxCatF(mtxA, mtxB, mtxA);
    guMtxF2L(mtxA, temp);
    ((u32 *)glistp)[0] = 0xDA380003;
    ((u32 *)glistp)[1] = (u32)temp;
    return (u8 *)glistp + 8;
}

extern Gfx D_1000118;

#define TEXT_MARKER_GFX(pkt, _w0, _w1) { Gfx *_g = (Gfx *)(pkt); _g->words.w0 = (_w0); _g->words.w1 = (u32)(_w1); }

extern s32 D_8074E880[];
void effectConfettiPhysicsUpdate(void);
void func_8071495C(void);
void vtxGradientSetPosition(s16);
extern Gfx *textDrawStringVtx(Gfx *, s16, s16, s16, char *, u8);

Gfx *textMarkerRenderString(Gfx *gfx, Actor *actor) {
    char **sub;
    s16 x;
    s16 y;
    u8 state;
    u8 mode;
    s16 width;

    if (&state == 0) {} // FAKE: keeps state/mode/width/x/y in spill-style home slots
    sub = actor->unk174;
    state = 3;
    mode = (u8)actor->z;
    TEXT_MARKER_GFX(gfx++, 0xDE000000, &D_1000118);
    TEXT_MARKER_GFX(gfx++, 0xFC119623, 0xFF2FFFFF);

    x = actor->unk155[0];
    switch (x) {
        case 2:
            vtxGradientSetPosition((s16)(actor->unk15F * 3 + 0x4000));
            break;
        case 0:
            if (actor->z == 1.0f) {
                s16 w2;

                w2 = (s16)(s32)((((f64)actor->unk15F * 0.0078125 > 1.0 ? 1.0 : (f64)actor->unk15F * 0.0078125) * 0.9) * (f64)textGetStringWidth((s16)(s32)actor->z, (s32)*sub) + (f64)actor->x * 0.25);
                func_807149B8(1);
                func_8071498C(effectConfettiPhysicsUpdate);
                func_80714950(0xA);
                func_8071495C();
                func_80714CC0((void *)D_8074E880[((randomNonNegative() >> 0xF) % 1000) % 3], 1.0f, (f32)w2, (f32)((f64)actor->y * 0.25 + 12.0), -5.0f);
            }
        default:
            vtxGradientSetPosition((s16)(actor->unk15F * 3));
            break;
    }

    x = (s16)(s32)actor->x;
    y = (s16)(s32)actor->y;
    switch (mode) {
        case 1:
            width = textGetStringWidth((s16)(s32)actor->z, (s32)*sub);
            state = 0x13;
            gfx = renderAppendScaledMatrix(gfx, (ActorPositionView *)actor, width, 0.8f);
            state &= 0xFFFE;
            x = -(width * 2);
            y = 0;
            break;
        case 6:
            state = 0x23;
            TEXT_MARKER_GFX(gfx++, 0xE3000A01, 0x100000);
            TEXT_MARKER_GFX(gfx++, 0xE200001C, 0x0C184240);
            break;
        case 0:
            mode = 6;
            width = textGetStringWidth(6, (s32)*sub);
            actor->x = (f32)((D_80744490 - width) * 2);
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

    gDPSetPrimColor(gfx++, 0, 0, actor->unk16A, actor->unk16B, actor->unk16C, actor->unk15F);
    return textDrawStringVtx(gfx, (s16)mode, x, y, *sub, state);
}

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
        gfx = textDrawAnimated(gfx, *(u8 *)((u8 *)model + 0xA), 2, 160.0f, actor->y, 0.0f, 1.0f);
    } else {
        gfx = textDrawAnimated(gfx, *(u8 *)((u8 *)model + 0xA), 1, 160.0f, actor->y, 0.0f, 1.0f);
    }
    return gfx;
}

void renderCallbacksRegister(void *, void *, s32);
void heapFree(void *);
Gfx *textMarkerRenderString(Gfx *, Actor *);

void textMarkerUpdate(void) {
    u8 *model;

    model = (u8 *)gCurrentActor->unk174;
    if (gCurrentActor->moveYaw != 0) {
        renderCallbacksRegister(textMarkerRender, gCurrentActor, 3);
        return;
    }
    if (!(gCurrentActor->flags & 0x10)) {
        gCurrentActor->unk168 = *(u16 *)(model + 4);
    }
    switch (gCurrentActor->state) {
    case 0:
        if (gCurrentActor->unk168 != 0) {
            gCurrentActor->unk168--;
        } else {
            gCurrentActor->state = 1;
        }
        break;
    case 1:
        if (gCurrentActor->unk155[0] != 3) {
            renderCallbacksRegister(textMarkerRenderString, gCurrentActor, 3);
        }
        switch (gCurrentActor->unk155[0]) {
        case 0:
            if (gCurrentActor->unk15F <= 0xFF - model[8]) {
                gCurrentActor->unk15F += model[8];
            } else {
                gCurrentActor->unk15F = 0xFF;
                gCurrentActor->unk155[0]++;
                gCurrentActor->unk168 = *(u16 *)(model + 6);
            }
            break;
        case 1:
            if (gCurrentActor->unk168 != 0) {
                gCurrentActor->unk168--;
            } else {
                gCurrentActor->unk155[0]++;
            }
            break;
        case 2:
            if (gCurrentActor->unk15F >= model[9]) {
                gCurrentActor->unk15F -= model[9];
            } else {
                gCurrentActor->unk155[0]++;
                gCurrentActor->unk15F = 0;
            }
            break;
        case 3:
            heapFree(*(void **)model);
            actorDespawn(gCurrentActor);
            break;
        }
        break;
    }
}

/* Row-major copy: the target keeps the row offset (i * arg2) * 4 as the loop
   invariant and adds arg1 + j * 4 inside, so arg1 is written before the offset. */
void textCopyGlyphBlock(s32 *dst, s32 *src, u8 rowWidth) {
    s16 i;
    s16 j;

    i = 0;
    do {
        for (j = 0; j < rowWidth; j++) {
            *dst++ = *(s32 *)((u8 *)src + j * 4 + i * rowWidth * 4);
        }
        i++;
    } while (i < 0x20);
}

void *textFontLoadSheet(s16);
void animSetLoopLimit(Actor *, s32, s16);
void animSetSpeed(Actor *, s32, f32);

s32 textBuildDigitNode(u8 baseFont, void *nodeBuffer, u8 nodeSlot, u8 digit, u8 glyphWidth) {
    void *temp;

    temp = textFontLoadSheet(baseFont + digit);
    if (nodeBuffer != NULL) {
        heapFreeDeferred((Mtx *)nodeBuffer);
    }
    /* Reusing the parameter keeps both pointers in one callee-saved register. */
    nodeBuffer = (void *)heapAlloc(glyphWidth << 7);
    textCopyGlyphBlock((s32 *)nodeBuffer, (s32 *)temp, glyphWidth);
    animSetLoopLimit(gCurrentActor, nodeSlot, -1);
    animSetSpeed(gCurrentActor, nodeSlot, 0.0f);
    animSetNodeItem(gCurrentActor, nodeSlot, 0, (s32)nodeBuffer);
    return (s32)nodeBuffer;
}

extern u8 D_8076A0AB;
extern u16 D_807FC930[];
extern u16 D_807446C0[];
u8 mapGetHubWorldIndex(u8, u8);
void csModelStateSetFirstByte(s32, s32);
s32 textBuildDigitNode(u8, void *, u8, u8, u8);

void textUpdateThreeDigitCounter(void) {
    s32 *model;
    s32 dummy;
    s32 t;
    s32 ten;
    s32 unk;
    u16 val;

    model = (s32 *)gCurrentActor->unk174;
    if (!(gCurrentActor->flags & 0x10) || (*(u32 *)((u8 *)gActivePlayerState + 0x1F0) & 0x20000)) {
        t = mapGetHubWorldIndex(D_8076A0AB, 0);
        if (t >= 8) {
            t = 0;
        }
        unk = t << 1;
        val = *(u16 *)((u8 *)D_807FC930 + unk);
        model[0] = textBuildDigitNode(0x21, (void *)model[0], 0, val / 100, 0x20);
        model[1] = textBuildDigitNode(0x21, (void *)model[1], 1, val % 100 / 10, 0x20);
        model[2] = textBuildDigitNode(0x21, (void *)model[2], 2, val % 10, 0x20);
        gCurrentActor->unk16A = 0xFF;
        gCurrentActor->unk16B = 0xFF;
        gCurrentActor->unk16C = 0xFF;
        gCurrentActor->flags |= 0x800000;
        *(u32 *)((u8 *)gActivePlayerState + 0x1F0) &= ~0x20000;
        if (val >= *(u16 *)((u8 *)D_807446C0 + unk)) {
            gCurrentActor->flags &= ~0x8000;
            gCurrentActor->unk128 = 0;
            gCurrentActor->unk144 = 1;
            csModelStateSetFirstByte(8, 2);
            ten = 10;
            csModelStateSetFirstByte(9, ten);
            csModelStateSetFirstByte(ten, ten);
            csModelStateSetFirstByte(11, ten);
            csModelStateSetFirstByte(13, ten);
            csModelStateSetFirstByte(12, ten);
        }
    }
    actorUpdateModelMatrix(gCurrentActor, 0);
}

void textUpdateTwoDigitCounter(void) {
    s32 *model;
    Actor *actor;

    actor = gCurrentActor;
    model = (s32 *)actor->unk174;
    if (!(actor->flags & 0x10)) {
        model[0] = textBuildDigitNode(0x14, (void *)model[0], 0, actor->unk155[0] / 10, 0x10);
        model[1] = textBuildDigitNode(0x14, (void *)model[1], 1, gCurrentActor->unk155[0] % 10, 0x10);
        actor = gCurrentActor;
    }
    actorUpdateModelMatrix(actor, 0);
}

void func_8069E018(void) {
    actorUpdateModelMatrix(gCurrentActor, 0);
}

void actorPlaySoundAndFinish(void) {
    if (!(gCurrentActor->flags & 0x10)) {
        actorScriptStart(gCurrentActor, 0x299);
    }
    actorUpdateModelMatrix(gCurrentActor, 0);
}

void flagSet(s32, s32, s32);
void func_8070E8DC(s32);
s32 frameTimingGetMapIndex(void);
void func_8070D8C0(Actor *, s32, u8);

extern s8 D_807F6951;
extern s8 D_807F6950;

void func_8069E088(void) {
    s16 unk;

    if (!(gCurrentActor->flags & 0x10)) {
        func_80613C48(gCurrentActor, 0x5ED, 0.0f, 0.0f);
    }
    gCurrentActor->unk15E = 0x14;
    if (gCurrentActor->state < 0x1E) {
        gCurrentActor->state++;
    }
    if (gCurrentActor->state == 0x1E) {
        unk = 0;
        gCurrentActor->state = 0x64;
        func_8070E8DC(1);
        if (flagGet(0x178, 0) == 0) {
            flagSet(0x178, 1, 0);
        } else {
            unk = frameTimingGetMapIndex() * 5 + D_807F6951 + 1;
        }
        func_8070D8C0(gCurrentActor, 0x29, unk);
    }
    if (D_807F6950 != 0) {
        actorDespawn(gCurrentActor);
    }
    gCurrentActor->unk4->unk34 = 0.0f;
    gCurrentActor->unk4->unk38 = 0.0f;
    gCurrentActor->unk4->unk3C = 0.0f;
    actorUpdateModelMatrix(gCurrentActor, 0);
}
