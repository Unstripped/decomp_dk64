#include "common.h"
#include "compiler/ido/memory.h"
#include "actor.h"
#include "sched.h"
#define PROTO_SKIP_renderAppendScaledMatrix // stand-in: definition retyped to Gfx *, header regenerated at merge
#define PROTO_SKIP_textBuildDigitNode // stand-in: definition retyped to return void *, header regenerated at merge
#define PROTO_SKIP_actorUpdatePrevContactFlags // FAKE: callee prototype steer (owner returns void; see the declaration below)
#include "proto/boot/3630.h"
#include "proto/global/100180.h"
#include "proto/global/1025E0.h"
#include "proto/global/103AB0.h"
#include "proto/global/112080.h"
#include "proto/global/117190.h"
#include "proto/global/119370.h"
#include "proto/global/11BC10.h"
#include "proto/global/135D30.h"
#include "proto/global/15050.h"
#include "proto/global/166A0.h"
#include "proto/global/17B90.h"
#include "proto/global/19A00.h"
#include "proto/global/201B0.h"
#include "proto/global/35000.h"
#include "proto/global/3C10.h"
#include "proto/global/42630.h"
#include "proto/global/5230.h"
#include "proto/global/5E2F0.h"
#include "proto/global/61AA0.h"
#include "proto/global/69E60.h"
#include "proto/global/6AD90.h"
#include "proto/global/70FD0.h"
#include "proto/global/7130.h"
#include "proto/global/7CA80.h"
#include "proto/global/8CA50.h"
#include "proto/global/8D3E0.h"
#include "proto/global/90D80.h"
#include "proto/global/9DD70.h"
#include "proto/global/AA960.h"
#include "proto/global/CEAE0.h"
#include "proto/global/EFDC0.h"
#include "proto/global/FCCD0.h"

Gfx *renderAppendScaledMatrix(Gfx *, Actor *, s16, f32);
void *textBuildDigitNode(u8, void *, u8, u8, u8);
s32 actorUpdatePrevContactFlags(Actor *);

void mathAngleBetweenPoints3D(s16 *pitch, s16 *yaw, f32 x1, f32 y1, f32 z1, f32 x2, f32 y2, f32 z2) {
    f32 dx;
    f32 dz;

    *yaw = mathAngleBetweenPoints2D(x1, z1, x2, z2);
    dx = x2 - x1;
    dz = z2 - z1;
    *pitch = (s16)(s32)(((f64)mathAtan2(y2 - y1, sqrtf((dx * dx) + (dz * dz))) * 2048.0) / 3.1415927410125732);
}

extern u8 gGfxBufferIndex;
extern PlayerStruct *gPlayerSlots;
extern u8 gCurrentPlayerIndex;
extern Gfx D_2000180;

void renderSetupSegmentsAndFog(Gfx *glistp, Actor *actor) {
    gSPMatrix(glistp++, osVirtualToPhysical(&gPlayerSlots[gCurrentPlayerIndex].projMtx[gGfxBufferIndex]), G_MTX_PROJECTION | G_MTX_LOAD | G_MTX_NOPUSH);
    gSPMatrix(glistp++, osVirtualToPhysical(&gPlayerSlots[gCurrentPlayerIndex].viewMtx[gGfxBufferIndex]), G_MTX_PROJECTION | G_MTX_MUL | G_MTX_NOPUSH);
    gSPMatrix(glistp++, &D_2000180, G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH);
    gDPPipeSync(glistp++);
    gSPClearGeometryMode(glistp++, G_LIGHTING);
    gDPSetPrimColor(glistp++, 0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF);
    renderActorDisplayList(renderSetSegment6AndFog(glistp, actor->alpha, 1), actor);
}

extern PlayerState *gActivePlayerState;

typedef struct PanSubState {
    /* 0x00 */ PlayerState *player;
    /* 0x04 */ u16 *texture;
    /* 0x08 */ s16 *fadeTextures[2]; // per-frame-buffer copies of texture
    /* 0x10 */ u16 timer;
} PanSubState;

#define PAN_MIN(a, b) (((a) < (b)) ? (a) : (b))

extern Actor *gCurrentActor;


void actorPhotoUpdate(void) {
    PanSubState *subState;
    s16 yaw;
    s16 pitch;
    f32 mtx1[4][4];
    f32 mtx2[4][4];
    s16 frameElapsed;
    s32 roll;
    u8 fadedOut;
    f32 t;

    subState = gCurrentActor->customState;
    fadedOut = 0;
    if (!(gCurrentActor->flags & 0x10)) {
        subState->timer = 0x5A;
        gCurrentActor->flags |= 0x400;
        gCurrentActor->drawDistance = 0x3E8;
        subState->texture = func_806FFF88();
        controllerAnimSetStateIfChanged(gCurrentActor, 0x40B, 0, 0);
        scriptSetActorRampTarget(gCurrentActor, 0.15f, 0);
    }
    gCurrentActor->flags &= ~4;
    frameElapsed = 0x5A - subState->timer;
    if (frameElapsed == 0xD) {
        sfxPlayActorSound(gCurrentActor, 0x222, 0, 0, 0, 0xFF, 1.0f, -1);
    }
    if (frameElapsed == 0x1B) {
        sfxStopSlotSound(gCurrentActor, 0);
    }
    t = PAN_MIN(1.0, ((frameElapsed - 0x1E) < 0 ? 0 : (frameElapsed - 0x1E)) / 60.0f * 5.0);
    if (t < 1.0 && gCurrentActor->actorType != 0xD9) {
        color5551CopyLerpToWhite(subState->texture, &subState->fadeTextures[gGfxBufferIndex], t);
        animSetNodeItem(gCurrentActor, 0, 0, (s32)subState->fadeTextures[gGfxBufferIndex]);
    } else {
        animSetNodeItem(gCurrentActor, 0, 0, (s32)subState->texture);
        if (gCurrentActor->unk155 == 0) {
            if (gActivePlayerState->unk1EC == 1) {
                slotQueueAddValue(0xC, gActivePlayerState->playerIndex, 1);
                sfxAllocateChannel(0x2E, 1.0f);
            } else if (gActivePlayerState->unk1EC == 2) {
                sfxPlayOnFreeSlot(0x98, 0x7FFF, 63.0f, 1.0f, 0, 0x80);
            }
            gCurrentActor->unk155++;
        }
        if (gActivePlayerState->unk1EC != 0xFF && subState->timer != 0) {
            renderCallbacksRegister(&func_806FF628, gCurrentActor, 3);
        }
    }
    mathAngleBetweenPoints3D(&pitch, &yaw, gPlayerSlots->camX, gPlayerSlots->camY, gPlayerSlots->camZ, gPlayerSlots->focusX, gPlayerSlots->focusY, gPlayerSlots->focusZ);
    t = PAN_MIN(30.0, frameElapsed) / 30.0;
    gCurrentActor->yaw = yaw;
    roll = (f32)pitch - (2048.0f + -2048.0f * t);
    gCurrentActor->roll = roll;
    guRotateF(mtx1, pitch / 4095.0 * 360.0, 1.0f, 0.0f, 0.0f);
    guRotateF(mtx2, yaw / 4095.0 * 360.0, 0.0f, 1.0f, 0.0f);
    guMtxCatF(mtx1, mtx2, mtx1);
    guTranslateF(mtx2, gPlayerSlots->camX, gPlayerSlots->camY, gPlayerSlots->camZ);
    guMtxCatF(mtx1, mtx2, mtx1);
    guMtxXFMF(mtx1, 0.0f, 0.0f, -30.0f * t, &gCurrentActor->x, &gCurrentActor->y, &gCurrentActor->z);
    if (subState->timer != 0) {
        subState->timer--;
    } else {
        gCurrentActor->flags &= ~0x8000;
        gCurrentActor->alpha -= 0xA;
        if (gCurrentActor->alpha <= 0) {
            fadedOut = 1;
        }
    }
    if (fadedOut || !(subState->player->stateFlags & 0x8000)) {
        if (subState->player->unk1EC == 1) {
            playerStateQueueCallback(0x58, NULL, 0);
        }
        sfxStopSlotSound(gCurrentActor, 0);
        subState->player->stateFlags &= ~0x8000;
        subState->player->unk1EC = 0xFF;
        if (gCurrentActor->actorType == 0xD9) {
            assetFreeBuffer(subState->texture, 0xF6, 0x45);
        } else {
            heapFreeDeferred(subState->texture);
        }
        subState->player->actor = NULL;
        actorDespawn(gCurrentActor);
    } else {
        guTranslateF(gCurrentActor->modelMtx, 0.0f, -70.0f, 0.0f);
        actorUpdateModelMatrix(gCurrentActor, 1);
        renderCallbacksRegister(&renderSetupSegmentsAndFog, gCurrentActor, 3);
    }
}


void actorPhotoUpdateEntry(void) {
    actorPhotoUpdate();
}

/* Empty stub: the 8 bytes after actorPhotoUpdateEntry (a bare `jr ra; nop`) are a second
   function that splat merged into actorPhotoUpdateEntry for lack of a symbol. */
void func_806998E8(void) {
}


void func_806998F0(void) {
    actorSagWaveUpdate(8, 0);
}

void func_80699914(void) {
    if (!(gCurrentActor->flags & 0x10)) {
        gCurrentActor->drawDistance = 0x3E8;
    }
    actorSagWaveUpdate(0x1C, 1);
}



typedef struct WaveState {
    /* 0x000 */ s16 animDelay;
    /* 0x002 */ u8 pad2[2];
    /* 0x004 */ f32 nodeY[28];
    /* 0x074 */ void *trackedActors[4];
    /* 0x084 */ f32 trackedPos[4];
    /* 0x094 */ u8 trackedCount;
    /* 0x095 */ u8 pad95[3];
    /* 0x098 */ f32 slotPos[4];
    /* 0x0A8 */ f32 slotAmp[4];
    /* 0x0B8 */ u8 slotPhase[4];
} WaveState;


void actorSagWaveUpdate(u8 numNodes, u8 waveType) {
    f32 posOffsets[32];
    f32 nodeForces[26];
    f32 waveForce;
    WaveState *state;
    s32 i;
    s32 j;
    u8 found;
    f32 dist;

    state = gCurrentActor->customState;
    if (!(gCurrentActor->flags & 0x10)) {
        gCurrentActor->sub4->boneOffsets = (BoneVector *)heapAlloc((numNodes + 1) * 0x10);
        for (i = 0; i < numNodes; i++) {
            gCurrentActor->sub4->boneOffsets[i].bone = i;
            if (i != numNodes - 1) {
                gCurrentActor->sub4->boneOffsets[i].lastBone = i + 1;
            } else {
                gCurrentActor->sub4->boneOffsets[i].lastBone = 0xFF;
            }
            gCurrentActor->sub4->boneOffsets[i].x = 0.0f;
            gCurrentActor->sub4->boneOffsets[i].z = 0.0f;
            gCurrentActor->sub4->boneOffsets[i].y = 0.0f;
        }
        gCurrentActor->sub4->boneOffsets[numNodes].bone = 0xFF;
        for (i = 0; i < numNodes; i++) {
            state->nodeY[i] = 0.0f;
        }
        state->animDelay = -1;
        state->trackedCount = 0;
        for (i = 0; i < 4; i++) {
            state->slotPhase[i] = 0;
        }
    }
    if ((actorCheckAlwaysFalse() != 0) && (state->animDelay == -1)) {
        state->animDelay = 10;
    }
    if (state->animDelay > 0) {
        state->animDelay--;
    }
    if (state->animDelay == 0) {
        controllerAnimSetStateIfChanged(gCurrentActor, 0x403, 0, 1.0f);
        scriptSetActorRampTarget(gCurrentActor, 4.0f, 1.0f);
        state->animDelay = -2;
    }
    for (i = 0; i < numNodes; i++) {
        posOffsets[i] = 0.0f;
        nodeForces[i] = 0.0f;
    }
    i = 0;
    if ((s32)gActorGlobalState.unk39 > 0) {
        do {
            found = 0;
            j = 0;
            while (j < (s32)state->trackedCount && found == 0) {
                if (state->trackedActors[j] == gActorGlobalState.unk7C[i]) {
                    found = 1;
                } else {
                    j++;
                }
            }
            if (!found) {
                switch (waveType) {
                case 0:
                    actorAddNodeForceSlot(gActorGlobalState.unk3C[i][2], waveType);
                    break;
                case 1:
                    actorAddNodeForceSlot(gActorGlobalState.unk3C[i][0], waveType);
                    break;
                }
            }
            i++;
        } while (i < (s32)gActorGlobalState.unk39);
        i = 0;
    }
    if ((s32)state->trackedCount > 0) {
        do {
            found = 0;
            j = 0;
            while (j < (s32)gActorGlobalState.unk39 && found == 0) {
                if (state->trackedActors[i] == gActorGlobalState.unk7C[j]) {
                    found = 1;
                } else {
                    j++;
                }
            }
            if (!found) {
                actorAddNodeForceSlot(state->trackedPos[i], waveType);
            }
            i++;
        } while (i < (s32)state->trackedCount);
        i = 0;
    }
    memcpy(state->trackedActors, gActorGlobalState.unk7C, 0x10);
    state->trackedCount = gActorGlobalState.unk39;
    if ((s32)state->trackedCount > 0) {
        do {
            switch (waveType) {
            case 0:
                state->trackedPos[i] = gActorGlobalState.unk3C[i][2];
                break;
            case 1:
                state->trackedPos[i] = gActorGlobalState.unk3C[i][2];
                break;
            }
            i++;
        } while (i < (s32)state->trackedCount);
        i = 0;
    }
    if ((s32)gActorGlobalState.unk39 > 0) {
        do {
            switch (waveType) {
            case 0:
                if ((f64)gActorGlobalState.unk3C[i][2] / 843.0 > 0) {
                    waveForce = (f32)((f64)gActorGlobalState.unk3C[i][2] / 843.0);
                } else {
                    waveForce = (f32)-((f64)gActorGlobalState.unk3C[i][2] / 843.0);
                }
                break;
            case 1:
                if ((f64)gActorGlobalState.unk3C[i][0] / 480.0 > 0) {
                    waveForce = (f32)((f64)gActorGlobalState.unk3C[i][0] / 480.0);
                } else {
                    waveForce = (f32)-((f64)gActorGlobalState.unk3C[i][0] / 480.0);
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
        } while (i < (s32)gActorGlobalState.unk39);
        i = 0;
    }
    for (i = 0; i < 4; i++) {
        if (state->slotPhase[i] != 0) {
            for (j = 0; j < numNodes; j++) {
                if (state->slotPos[i] < (f32)j) {
                    dist = (f32)j - state->slotPos[i];
                } else {
                    dist = -((f32)j - state->slotPos[i]);
                }
                dist = (f32)(3.0 - (f64)dist);
                if (dist < 0.0) {
                    dist = 0.0f;
                }
                waveForce = sinApprox((f32)((f64)state->slotPhase[i] * 0.5));
                nodeForces[j] = ((dist * state->slotAmp[i]) * waveForce) + nodeForces[j];

            }
            state->slotAmp[i] = (f32)((f64)state->slotAmp[i] - ((f64)state->slotAmp[i] / 20.0));
            if ((f64)state->slotAmp[i] < 0.5) {
                state->slotPhase[i] = 0;
            } else {
                state->slotPhase[i]++;
            }
        }
    }
    for (i = 0; i < numNodes; i++) {
        if (state->nodeY[i] < posOffsets[i]) {
            switch (waveType) {
            case 0:
                state->nodeY[i] = (f32)(((f64)(posOffsets[i] - state->nodeY[i]) * 0.25) + (f64)state->nodeY[i]);
                break;
            case 1:
                state->nodeY[i] = (f32)(((f64)(posOffsets[i] - state->nodeY[i]) / 15.0) + (f64)state->nodeY[i]);
                break;
            }
            if (posOffsets[i] < state->nodeY[i]) {
                state->nodeY[i] = posOffsets[i];
            }
        }
        if (posOffsets[i] < state->nodeY[i]) {
            switch (waveType) {
            case 0:
                state->nodeY[i] = (f32)((f64)state->nodeY[i] - ((f64)(state->nodeY[i] - posOffsets[i]) * 0.5f));
                break;
            case 1:
                state->nodeY[i] = (f32)((f64)state->nodeY[i] - ((f64)(state->nodeY[i] - posOffsets[i]) * 0.125));
                break;
            }
            if (state->nodeY[i] < posOffsets[i]) {
                state->nodeY[i] = posOffsets[i];
            }
        }
        gCurrentActor->sub4->boneOffsets[i].y = state->nodeY[i] + nodeForces[i];
    }
    gCurrentActor->sub4->boneOffsets[0].y = 0.0f;
    *(f32 *)((u8 *)gCurrentActor->sub4->boneOffsets + (numNodes << 4) - 8) = 0.0f;  // FAKE: byte-offset form stops the CSE of numNodes * 16 across the calls
    actorUpdateModelMatrix(gCurrentActor, 0);
}

/* slotMode is u8: IDO homes the raw incoming a1 to its caller slot (sw a1,4(sp))
   even in this leaf function and re-narrows it with andi before use. */
void actorAddNodeForceSlot(f32 forceMagnitude, u8 slotMode) {
    WaveState *slots = gCurrentActor->customState;
    s16 i;
    s32 found;
    f64 temp;

    found = 0;
    i = 0;
    do {
        if (slots->slotPhase[i] == 0) {
            found = 1;
        } else {
            i++;
        }
    } while (i < 4 && found == 0);
    if (found != 0) {
        slots->slotPhase[i] = 1;
        switch (slotMode) {
        case 0:
            slots->slotAmp[i] = 10.0f;
            temp = (f64)forceMagnitude / 843.0;
            if (temp > 0.0) {
                slots->slotPos[i] = (f32)temp;
                return;
            }
            slots->slotPos[i] = (f32)-temp;
            return;
        case 1:
            slots->slotAmp[i] = 12.0f;
            temp = (f64)forceMagnitude / 480.0;
            if (temp > 0.0) {
                slots->slotPos[i] = (f32)temp;
                return;
            }
            slots->slotPos[i] = (f32)-temp;
            break;
        }
    }
}




s32 actorCheckAlwaysFalse(void) {
    s32 i;
    s32 v;

    for (i = 0; i < gActorGlobalState.unk39; i++) {
        v = gActorGlobalState.unk7C[i]->actorType;
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


typedef struct {
    f32 sag;
    u8 prevCount;
    u8 pad5[3];
    f32 bounceAmp;
    s32 bounceTimer;
} ProximityState;






void actorSagSingleUpdate(void) {
    ProximityState *state;
    f32 acc;
    f32 dist;
    f32 value;
    s32 i;

    acc = 0.0f;
    state = (ProximityState *)gCurrentActor->customState;
    if (!(gCurrentActor->flags & 0x10)) {
        gCurrentActor->flags |= 0x400;
        gCurrentActor->sub4->boneOffsets = (BoneVector *)heapAlloc(0x20);
        gCurrentActor->sub4->boneOffsets->bone = 1;
        gCurrentActor->sub4->boneOffsets->lastBone = 0xFF;
        gCurrentActor->sub4->boneOffsets->x = 0.0f;
        gCurrentActor->sub4->boneOffsets->z = 0.0f;
        gCurrentActor->sub4->boneOffsets->y = 0.0f;
        gCurrentActor->sub4->boneOffsets[1].bone = 0xFF;
        gCurrentActor->drawDistance = 0x3E8;
        state->prevCount = 0;
        state->bounceTimer = 0;
        state->sag = 0.0f;
        state->bounceAmp = 0.0f;
    }
    for (i = 0; i < (s32)gActorGlobalState.unk39; i++) {
        dist = sqrtf((gActorGlobalState.unk3C[i][0] * gActorGlobalState.unk3C[i][0]) + (gActorGlobalState.unk3C[i][2] * gActorGlobalState.unk3C[i][2]));
        if (dist > 1347.0f) {
            dist = 1347.0f;
        }
        dist = 1347.0f - dist;
        acc += dist;
        value = gActorGlobalState.unk7C[i]->speedXZ;
        value = (f32)((f64)value * 0.1);
        if (state->bounceAmp < value) {
            state->bounceAmp = value;
        }
    }
    if (acc > 1347.0f) {
        acc = 1347.0f;
    }
    acc = (f32)((f64)acc / 10.0);
    if (state->sag < acc) {
        state->sag = (f32)((f64)state->sag + ((f64)(acc - state->sag) * 0.25));
        if (acc < state->sag) {
            state->sag = acc;
        }
    }
    if (acc < state->sag) {
        state->sag = (f32)((f64)state->sag - ((f64)(state->sag - acc) * 0.5f));
        if (state->sag < acc) {
            state->sag = acc;
        }
    }
    state->bounceTimer++;
    if ((f64)state->bounceAmp == 0.0) {
        state->bounceTimer = 0;
    }
    if (state->prevCount != gActorGlobalState.unk39) {
        state->bounceAmp = 12.0f;
    }
    state->bounceAmp = (f32)((f64)state->bounceAmp - ((f64)state->bounceAmp / 40.0));
    if ((f64)state->bounceAmp < 0.5) {
        state->bounceAmp = 0.0f;
    }
    gCurrentActor->sub4->boneOffsets->y = 0.0 - (sinApprox((f32)((f64)state->bounceTimer * 0.5)) * state->bounceAmp + state->sag);
    state->prevCount = gActorGlobalState.unk39;
    actorUpdateModelMatrix(gCurrentActor, 0);
}

typedef struct {
    s16 delay;
    u8 pad2[2];
    f32 brightness;
} SpotLightState;

typedef struct {
    f32 rampTarget;
    s32 red;
    s32 green;
    s32 blue;
    f32 fovAngleA;
    f32 fovAngleB;
} SpotLightConfig;

extern s32 gCurrentMap;
extern s16 D_807503A0;

void actorSpotLightUpdate(void) {
    f32 targetPos[3];
    f32 sourcePos[3];
    u16 red;
    u16 green;
    u16 blue;
    SpotLightState *lightState;

    lightState = gCurrentActor->customState;
    if (!(gCurrentActor->flags & 0x10)) {
        controllerAnimSetStateIfChanged(gCurrentActor, 0x402, 0, 1.0f);
        if (gCurrentMap == 6) {
            actorScriptStart(gCurrentActor, 0x297);
        }
        gCurrentActor->flags |= 0x400;
        lightState->delay = 0;
        lightState->brightness = 1.0f;
    }
    scriptSetActorRampTarget(gCurrentActor, ((SpotLightConfig *)gCurrentActor->spawnData)->rampTarget, 1.0f);
    if (gActorGlobalState.bossFightPhase == 4) {
        lightState->delay = D_807503A0;
        lightState->brightness = 0.0f;
    }
    if (lightState->delay == 0) {
        red = ((SpotLightConfig *)gCurrentActor->spawnData)->red;
        green = ((SpotLightConfig *)gCurrentActor->spawnData)->green;
        blue = ((SpotLightConfig *)gCurrentActor->spawnData)->blue;
        red = (u16)(u32)((f64)(u32)red * (f64)lightState->brightness);
        green = (u16)(u32)((f64)(u32)green * (f64)lightState->brightness);
        blue = (u16)(u32)((f64)(u32)blue * (f64)lightState->brightness);
        lightState->brightness = (f32)((f64)lightState->brightness + 0.05);
        if (lightState->brightness > 1.0) {
            lightState->brightness = 1.0f;
        }
        if (gCurrentActor->flags & 0x10) {
            if ((f64)((SpotLightConfig *)gCurrentActor->spawnData)->fovAngleA != 0.0 || (f64)((SpotLightConfig *)gCurrentActor->spawnData)->fovAngleB != 0.0) {
                lightSetFovAngles(((SpotLightConfig *)gCurrentActor->spawnData)->fovAngleA, ((SpotLightConfig *)gCurrentActor->spawnData)->fovAngleB);
            }
            lightSetFlags(2);
            lightSetTargetId(gCurrentActor->chunkIndex);
            actorGetNodePos(gCurrentActor, 2, &targetPos[0], &targetPos[1], &targetPos[2]);
            lightAdd((f32)((f64)gCurrentActor->x + 0.3), gCurrentActor->y, gCurrentActor->z, targetPos[0], targetPos[1], targetPos[2], 0.0f, 1, red, green, blue);
        }
    } else {
        lightState->delay = lightState->delay - 1;
    }
    actorUpdateModelMatrix(gCurrentActor, 0);
}


void actorSpotLightUpdateEntry(void) {
    actorSpotLightUpdate();
}

extern Actor *gPrimaryPlayerActor;
extern s16 D_80750378;
extern u8 D_8071FE08[];
extern u8 D_80720E14[];

void func_8069B010(void) {
    s32 *spawnFrame = gCurrentActor->customState;
    Actor *parent;

    if (!(gCurrentActor->flags & 0x10)) {
        gCurrentActor->contactFlags &= 0xFFFE;
        gCurrentActor->unk144 = 2;
        actorSetCollisionRadius(gCurrentActor, 60.0f);
        actorAppendModelNode(gCurrentActor, 0.0f, 0.0f, 0.0f, 60.0f, -1);
        actorAppendModelSubNode(gCurrentActor, 0.0f, 0.0f, 0.0f, -1);
        effectSetDuration(-1);
        effectSetDepth(1);
        effectSetCallback(effectScaleSpinUpdate);
        effectCreateAtActorBone(D_80720E14, 0.9f, gCurrentActor, 1, 2);
        *spawnFrame = gGameFrameCounter;
        gCurrentActor->flags |= 0x80000;
        collisionCheckActorFloor(gCurrentActor, gCurrentActor->x, gCurrentActor->y, gCurrentActor->z, &gCurrentActor->floorY);
    }
    actorUpdatePrevContactFlags(gCurrentActor);
    billboardSubmit(gCurrentActor, 0x3C8, 0x40, 0x40, 0x1E, 0x1E, 1, 0x4B, 0x78, 0, 1.0f);
    parent = gCurrentActor->parentActor;
    if (parent != NULL) {
        if (parent->state != 2 && parent->state != 0x26) {
            actorDespawn(gCurrentActor);
            return;
        }
        if (gCurrentActor->unk15F == parent->unk15F) {
            if ((gCurrentActor->x - gPrimaryPlayerActor->x) * (gCurrentActor->x - gPrimaryPlayerActor->x) + (gCurrentActor->z - gPrimaryPlayerActor->z) * (gCurrentActor->z - gPrimaryPlayerActor->z) > 900.0f) {
                gCurrentActor->parentActor->unkEC = (s16)(mathAngleBetweenPointsDeg((s32)gCurrentActor->x, (s32)gCurrentActor->z, (s32)gPrimaryPlayerActor->x, (s32)gPrimaryPlayerActor->z) - mathAngleBetweenPointsDeg((s32)gPlayerSlots->focusX, (s32)gPlayerSlots->focusZ, (s32)gPlayerSlots->camX, (s32)gPlayerSlots->camZ));
            }
            lightAdd(gCurrentActor->x, gCurrentActor->y, gCurrentActor->z, 0.0f, 0.0f, 0.0f, 100.0f, 0, 0xFF, 0xFF, 0);
        }
        if (gActorGlobalState.bossFightPhase == 9) {
            sfxPlayFromActorWithAltitudeCheck(gCurrentActor, 0x1CE, 0xFF, 0x7F, 0x1E);
            effectCreateAtPosition(D_8071FE08, 1.0f, gCurrentActor->x, gCurrentActor->y, gCurrentActor->z);
            actorAppendCallback(gCurrentActor->parentActor, gCurrentActor, 0x02000000, gCurrentActor->unk15F, 0, 0);
            actorDespawn(gCurrentActor);
        }
        if (gCurrentMap != 0x48 && gCurrentMap != 0x11 && *spawnFrame + D_80750378 < gGameFrameCounter) {
            actorAppendCallback(gCurrentActor->parentActor, gCurrentActor, 0x02000000, 0xFF, 0, 0);
            actorDespawn(gCurrentActor);
        }
    } else {
        actorDespawn(gCurrentActor);
    }
}

extern u8 D_8071FC58;
extern u8 D_8071FC8C;
extern u8 D_8071FCC0;

void func_8069B3FC(void) {
    s16 *spinSpeed = gCurrentActor->customState;
    PlayerState *player = gPrimaryPlayerActor->customState;
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
        *spinSpeed = 0;
        sfxAllocateChannel(0x3B, 1.0f);
    } else {
        actorGetNodePos(gCurrentActor, 1, &x, &y, &z);
        player->unk210 = x;
        player->unk214 = y;
        player->unk218 = z;
        if (gCurrentActor->unk155 < 4) {
            for (j = 2; j < 3; j++) {
                for (i = 0; i < 2; i++) {
                    effectSetCallback(func_80717D4C);
                    effectSetDepth(1);
                    effectSetSpeed((randomNonNegative() >> 15) % 10000 % 120 + 0x50);
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
                    effectCreateAtActorBone(sel, 0.6f, gCurrentActor, j, 0);
                }
            }
        }
        switch (gCurrentActor->unk155) {
            case 0:
                *spinSpeed += 0x1E;
                break;
            case 1:
                gPrimaryPlayerActor->unk155++;
                gCurrentActor->unk155++;
                break;
            case 2:
                *spinSpeed -= 0x2A;
                if (*spinSpeed < 0) {
                    *spinSpeed = 0;
                }
                break;
            case 3:
                *spinSpeed -= 0x2A;
                if (*spinSpeed < 0) {
                    *spinSpeed = 0;
                }
                gPrimaryPlayerActor->unk155++;
                gCurrentActor->flags &= ~0x8000;
                gCurrentActor->alpha = 0xFF;
                gCurrentActor->unk155++;
                break;
            case 4:
                *spinSpeed -= 0x2A;
                if (*spinSpeed < 0) {
                    *spinSpeed = 0;
                }
                gCurrentActor->alpha -= 0x28;
                if (gCurrentActor->alpha < 0x28) {
                    gPrimaryPlayerActor->unk155++;
                    sfxStopChannel(0x3B, 0);
                    actorDespawn(gCurrentActor);
                }
                break;
        }
    }
    gCurrentActor->yaw += *spinSpeed;
    actorUpdateModelMatrix(gCurrentActor, 0);
}

extern s16 gScreenWidth;

s32 actorHasCallbackTargetThisFrame(void) {
    ActorCallbackNode *node = gCurrentActor->callbacks;

    while (node != NULL) {
        if ((u32)node->callback == 0x8000) {
            Actor *source;
            PlayerState *player;
            if (actorTableContains(node->source) != 0) {
                source = node->source;
                if (source->collisionFlags & 1) {
                    player = source->customState;
                    if (gGameFrameCounter - player->lastFrame < 2) {
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
    /* 0x00 */ s32 throwFrame;
    /* 0x04 */ f32 homeX;
    /* 0x08 */ f32 homeY;
    /* 0x0C */ f32 homeZ;
    /* 0x10 */ f32 homeScale;
    /* 0x14 */ Actor *holder;
    /* 0x18 */ u8 pad18[4];
    /* 0x1C */ s32 settleTimer;
    /* 0x20 */ f32 holdYaw;
    /* 0x24 */ f32 spinYaw;
    /* 0x28 */ u8 respawns;
    /* 0x29 */ u8 pad29[1];
    /* 0x2A */ u16 spinSpeed;
} ActorSub174View;

typedef struct ActorSub124View {
    /* 0x00 */ s32 respawns;
    /* 0x04 */ s32 interactionMode;
} ActorSub124View;

typedef struct SpritePair {
    /* 0x0 */ void *sprites[2];
} SpritePair;

extern s16 D_807502D0;
extern f32 D_807502E4;
extern u8 D_80720340;
extern SpritePair D_807503A4;


void textMarkerUpdateMatrix(void) {
    ActorSub174View *state;
    f32 mtxA[4][4];
    f32 mtxB[4][4];
    f32 dx;
    f32 dy;
    f32 dz;
    f32 offsetX;
    f32 offsetY;
    f32 offsetZ;
    SpritePair spritePair;
    s32 i;
    s32 timedOut;
    s32 pad[4];
    s32 spawnArgs[2];
    s32 randVal;
    f32 scale;
    s32 particleLoopIdx;
    void *volatile callback;  // FAKE: retain the callback's original stack home

    state = gCurrentActor->customState;
    if (!(gCurrentActor->flags & 0x10)) {
        gCurrentActor->unkFA = 0x270F;
        gCurrentActor->floorY = 99999.0f;
        actorUpdateFloorContactAndTilt(gCurrentActor, 0);
        if (actorHasActiveMovementFlags(gCurrentActor) != 0) {
            gCurrentActor->unk144 = 2;
            gCurrentActor->flags2 |= 1;
            gCurrentActor->state = 2;
            gCurrentActor->unk155 = 1;
            state->settleTimer = 0x1E;
        }
        state->respawns = ((ActorSub124View *)gCurrentActor->spawnData)->respawns;
        if (state->respawns != 0) {
            state->homeX = gCurrentActor->x;
            state->homeY = gCurrentActor->y;
            state->homeZ = gCurrentActor->z;
            state->homeScale = gCurrentActor->sub4->scaleX / 0.15;
        }
        if (((ActorSub124View *)gCurrentActor->spawnData)->interactionMode == 1) {
            gCurrentActor->interactionType = 2;
        } else {
            gCurrentActor->interactionType = 1;
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
    if (gActorGlobalState.unk24 != 0) {
        state->holder = gActorGlobalState.unk28;
        gCurrentActor->state = 1;
        actorCallbackMaskDisable(gCurrentActor, 0x8000);
        actorCollisionEventsCancel(state->holder, 1);
        gCurrentActor->unk144 = 0x2C;
    }
    if (gActorGlobalState.unk25 != 0) {
        gCurrentActor->state = 2;
        gCurrentActor->unk155 = 0;
        state->settleTimer = 0x1E;
        gCurrentActor->unk144 = 0x3C;
        actorCallbackMaskEnable(gCurrentActor, 0x8000);
        if (gCurrentMap == 7 && actorListFindIdByActor(gCurrentActor) == 0x17) {
            actorListSetPosByActor(gCurrentActor, gCurrentActor->x, gCurrentActor->floorY, gCurrentActor->z);
        }
    }
    if (gCurrentMap == 0x22 && gCurrentActor->actorType == 0x3D &&
        (gCurrentActor->state == 0 || gCurrentActor->state == 2)) {
        if (gCurrentActor->x >= 3242.0 && gCurrentActor->z >= 252.0 &&
            gCurrentActor->x <= 3842.0 && gCurrentActor->z <= 852.0) {
            gCurrentActor->state = 4;
        }
    }
    if (gActorGlobalState.unk15 != 0 || gActorGlobalState.bossFightPhase == 9) {
        gCurrentActor->state = 4;
        actorReleaseFromPlayerHold(gCurrentActor);
    }
    if (gActorGlobalState.unk2C != 0) {
        gCurrentActor->state = 3;
        gCurrentActor->unk144 = 0x3C;
        actorCallbackMaskEnable(gCurrentActor, 0x8000);
        gCurrentActor->yaw = gActorGlobalState.unk36;
        gCurrentActor->moveYaw = gActorGlobalState.unk36;
        gCurrentActor->speedY = gActorGlobalState.unk30;
        gCurrentActor->speedXZ = (f32)gActorGlobalState.unk34;
        actorCollisionEventsCancel(state->holder, 1);
        if (gCurrentActor->actorType == 0x43 && gCurrentMap == 0x1E) {
            gCurrentActor->flags |= 0x200000;
            state->throwFrame = gGameFrameCounter;
        }
    }
    if (gCurrentActor->actorType == 0x55) {
        if (actorHasActiveMovementFlags(gCurrentActor) != 0) {
            gCurrentActor->flags |= 0x400;
        } else {
            gCurrentActor->flags &= ~0x400;
        }
    }
    actorUpdatePrevContactFlags(gCurrentActor);
    switch (gCurrentActor->actorType) {
    case 0x3F:
    case 0x40:
    case 0x41:
    case 0x42:
        for (i = 0; i < gActorGlobalState.volumeTriggerQueueCount; i++) {
            if (gActorGlobalState.volumeTriggerQueueOp[i] == 1) {
                state->spinSpeed = 0;
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
        state->holdYaw = (f32)(((f64)state->holder->yaw / 4095.0) * 360.0);
        break;
    case 2:
        gCurrentActor->renderFlags &= ~8;
        gCurrentActor->flags &= 0x7FFFFFFF;
        if (state->settleTimer != 0) {
            state->settleTimer--;
        }
        if (state->settleTimer == 0 && (gCurrentActor->contactFlags & 1)) {
            gCurrentActor->state = 0;
        } else if (actorHasActiveMovementFlags(gCurrentActor) != 0) {
            state->settleTimer = 0x1E;
        }
        if ((gCurrentActor->contactFlags & 1) && gCurrentActor->unk155 == 0) {
            if (gCurrentActor->actorType == 0x55) {
                sfxPlayFromActorWithAltitudeCheck(gCurrentActor, 0x8B, 0x64, 0x7F, 0x14);
                sfxPlayFromActorWithAltitudeCheck(gCurrentActor, 0x97, 0x64, 0x7F, 0x14);
            } else {
                sfxPlayFromActorWithAltitudeCheck(gCurrentActor, 0x97, 0xFF, 0x7F, 0x14);
            }
            gCurrentActor->unk155++;
        }
        gCurrentActor->speedY = -200.0f;
        gCurrentActor->speedXZ = 0.0f;
        gCurrentActor->flags2 |= 1;
        if (actorHasCallbackTargetThisFrame() != 0) {
            gCurrentActor->state = 4;
        }
        break;
    case 3:
        gCurrentActor->speedY += D_807502E4;
        if (gCurrentActor->speedY < (f32)D_807502D0) {
            gCurrentActor->speedY = (f32)D_807502D0;
        }
        timedOut = 0;
        state->spinYaw = state->spinYaw - 10.0f;
        if (gCurrentActor->actorType == 0x43 && gCurrentMap == 0x1E &&
            gGameFrameCounter - state->throwFrame >= 0x5B) {
            timedOut = 1;
        }
        if (timedOut != 0 || (gCurrentActor->hasArcBounds != 0 && actorAngleInArc(gCurrentActor, gCurrentActor->yaw) == 0)) {
            gCurrentActor->state = 4;
        }
        gCurrentActor->flags2 &= 0xFFFE;
        gCurrentActor->renderFlags &= ~8;
        gCurrentActor->flags &= 0x7FFFFFFF;
        break;
    case 4:
        if (gCurrentActor->actorType == 0x3D && state->respawns == 0) {
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
        if (state->respawns == 0) {
            actorDespawn(gCurrentActor);
        }
        if (gActorGlobalState.unk0 == 0) {
            spritePair = D_807503A4;
            for (particleLoopIdx = 0; particleLoopIdx != 0x10; particleLoopIdx += 2) {
                offsetX = (f32)(((f64)((randomNonNegative() >> 15) % 8191) / 200.0) - 20.0);
                offsetY = (f32)(((f64)((randomNonNegative() >> 15) % 8191) / 200.0) - 20.0);
                offsetZ = (f32)(((f64)((randomNonNegative() >> 15) % 8191) / 200.0) - 20.0);
                effectSetAngle(particleLoopIdx);
                effectSetDepth(1);
                if (particleLoopIdx == 0) {
                    callback = effectLightPulseOscillate; effectSetSpeed(0x100FA);  // LAYOUT: keep the callback store in the call's delay slot
                    effectSetCallback(callback);
                } else {
                    effectSetCallback(func_80717D4C);
                    effectSetSpeed(-0x96 - ((randomNonNegative() >> 15) % 50));
                }
                effectCreateAtPosition(&D_80720340, 1.6f, gCurrentActor->x + offsetX,
                              gCurrentActor->y + offsetY, gCurrentActor->z + offsetZ);
                if (gCurrentActor->actorType == 0x3D) {
                    offsetX = (2.0f * randomFloat()) - 1.0f;
                    offsetY = (2.0f * randomFloat()) - 1.0f;
                    offsetZ = (2.0f * randomFloat()) - 1.0f;
                    offsetX *= 30.0f;
                    offsetY *= 30.0f;
                    offsetZ *= 30.0f;
                    offsetY += 30.0f;
                    effectSetDepth(1);
                    effectSetDuration(0x3C);
                    effectSetCallback(effectTumbleBounceUpdate);
                    effectSetMode(2);
                    effectSetSpeed(2);
                    randVal = randomNonNegative();
                    if (randVal) {}  // FAKE: block split between the randVal def and the call (steers ugen ring / uopt colouring)
                    scale = randomFloat();
                    effectCreateAtPosition(spritePair.sprites[(randVal >> 15) % 2],
                                  (f32)(((f64)scale * 0.5) + 0.2),
                                  gCurrentActor->x + offsetX, gCurrentActor->y + offsetY,
                                  gCurrentActor->z + offsetZ);
                }
            }
            camStartShake(((PlayerState *)gPrimaryPlayerActor->customState)->camActor, 0x14, 0xF);
        }
        if (state->respawns != 0) {
            gCurrentActor->state = 0xA;
            gCurrentActor->callbackMask = 0;
            gCurrentActor->unk144 = 1;
            gCurrentActor->flags &= ~4;
        }
        break;
    case 5:
        gCurrentActor->renderFlags &= ~8;
        gCurrentActor->flags &= 0x7FFFFFFF;
        gCurrentActor->flags2 &= 0xFFFE;
        state->spinSpeed = state->spinSpeed + 2;
        if (state->spinSpeed >= 0xFB) {
            state->spinSpeed = 0xFA;
        }
        if (gCurrentActor->soundSlots[0] == -1) {
            sfxPlayActorSound(gCurrentActor, 0x11A, 0x64, 1, 0, 0x64, 1.0f, 0);
        } else {
            sfxSetVolumeAndPan(gCurrentActor->soundSlots[0],
                               (f32)(((f64)state->spinSpeed / 400.0) + 0.5), 2.0f);
        }
        lightAdd(gCurrentActor->x, gCurrentActor->y + 30.0f, gCurrentActor->z,
                 0, 0.0f, 0.0, (f32)(((f64)state->spinSpeed / 250.0) * 100.0), 0, 0xFF, 0xFF, 0);
        gCurrentActor->yaw = gCurrentActor->yaw + state->spinSpeed;
        gCurrentActor->y = gCurrentActor->floorY;
        break;
    case 10:
        dz = gPrimaryPlayerActor->z - state->homeZ;
        dx = gPrimaryPlayerActor->x - state->homeX;
        dy = gPrimaryPlayerActor->y - state->homeY;
        if ((dz * dz) + ((dx * dx) + (dy * dy)) > 2500.0f) {
            spawnArgs[0] = state->respawns;
            if (gCurrentActor->interactionType == 2) {
                spawnArgs[1] = 1;
            } else {
                spawnArgs[1] = 0;
            }
            actorListSpawnNodeEntry((s16)gCurrentActor->actorType, state->homeX, state->homeY,
                                    state->homeZ, 0, state->homeScale, NULL, spawnArgs);
            actorDespawn(gCurrentActor);
        }
        break;
    case 0x63:
        break;
    }
    if (gCurrentActor->state == 2 || gCurrentActor->state == 3) {
        gCurrentActor->moveYaw = gCurrentActor->yaw;
        actorApplyVelocity(gCurrentActor);
        actorUpdateFloorContactAndTilt(gCurrentActor, 0);
        if (gCurrentActor->state == 3 && (gCurrentActor->contactFlags & 1) && !(gCurrentActor->prevContactFlags & 1)) {
            gCurrentActor->state = 4;
        }
        if (gCurrentActor->state == 2 && (gCurrentActor->contactFlags & 4)) {
            gCurrentActor->state = 4;
        }
        gCurrentActor->floorSlopeYaw = 0x3FF;
        gCurrentActor->floorSlopePitch = 0x3FF;
    } else {
        gCurrentActor->attachMode = 0;
        gCurrentActor->contactFlags &= 0xFBF7;
    }
    switch (gCurrentMap) {
    case 0x26:
    case 0x71:
    case 0xC2:
        if (gCurrentActor->actorType == 0x3D) {
            if (gCurrentActor->attachMode == 1) {
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
    guScaleF(mtxA, gCurrentActor->sub4->scaleX, gCurrentActor->sub4->scaleY, gCurrentActor->sub4->scaleZ);
    guRotateF(mtxB, state->spinYaw, 0.0, 1.0f, 0.0);
    guMtxCatF(mtxA, mtxB, mtxA);
    guRotateF(mtxB, (f32)(((f64)gCurrentActor->yaw / 4095.0) * 360.0), 0.0, 1.0f, 0.0);
    guMtxCatF(mtxA, mtxB, mtxA);
    guRotateF(mtxB, (f32)(0.0 - (f64)gActorGlobalState.unkF0), 1.0f, 0.0, 0.0);
    guMtxCatF(mtxA, mtxB, mtxA);
    guRotateF(mtxB, (state->holdYaw + 90.0f) - gActorGlobalState.unkF4, 0.0, 1.0f, 0.0);
    guMtxCatF(mtxA, mtxB, mtxA);
    if (gCurrentActor->state == 3) {
        if (gCurrentActor->floorSlopePitch < 0x3E8) {
            guRotateF(mtxB, (f32)(-(((f64)gCurrentActor->floorSlopeYaw / 4095.0) * 360.0)),
                      0.0, 1.0f, 0.0);
            guMtxCatF(mtxA, mtxB, mtxA);
        }
        guRotateF(mtxB, (f32)(90.0 - (((f64)gCurrentActor->floorSlopePitch / 4095.0) * 360.0)), 1.0f, 0.0, 0.0);
        guMtxCatF(mtxA, mtxB, mtxA);
        if (gCurrentActor->floorSlopePitch < 0x3E8) {
            guRotateF(mtxB, (f32)(((f64)gCurrentActor->floorSlopeYaw / 4095.0) * 360.0),
                      0.0, 1.0f, 0.0);
            guMtxCatF(mtxA, mtxB, mtxA);
        }
    }
    guTranslateF(mtxB, gCurrentActor->x, gCurrentActor->y, gCurrentActor->z);
    guMtxCatF(mtxA, mtxB, gCurrentActor->modelMtx);
}

void actorUpdateTimerBarAndRange(void) {
    f32 frac;
    f32 dx;
    f32 dz;
    f32 dy;
    f32 dist;
    u32 val;

    if (!(gCurrentActor->flags & 0x10)) {
        frac = gCurrentActor->sub4->scaleX / 0.15;
        frac = frac - 1.0;
        if (frac < 0.0) {
            frac = 0.0f;
        }
        val = (u32)(80.0f * frac);
        gCurrentActor->cullMarginX = val;
        gCurrentActor->cullMarginY = val;
        gCurrentActor->drawDistance = 0x2BC;
    }
    dz = gCurrentActor->z - gPlayerSlots->camZ;
    dx = gCurrentActor->x - gPlayerSlots->camX;
    dy = gCurrentActor->y - gPlayerSlots->camY;
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
        gCurrentActor->cullMarginX = 0x3C;
        gCurrentActor->cullMarginY = 0x3C;
        actorListSpawnNodeEntryDefault(0x83, gCurrentActor->x, gCurrentActor->y, gCurrentActor->z,
                      0, 1.0f, gCurrentActor);
    }
    textMarkerUpdateMatrix();
    if (!(gCurrentActor->flags & 0x10)) {
        if (((s32 *)gCurrentActor->spawnData)[2] == 1) {
            if (flagGet(0xFD, 0) != 0) {
                gCurrentActor->interactionType = 4;
            }
        }
    }
}

void func_8069D018(void) {
    Actor *actor = gCurrentActor;

    if (!(actor->flags & 0x10)) {
        actor->drawDistance = 0x2BC;
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
    /* 0x0 */ u8 *text;
    /* 0x4 */ u16 startDelay;  // frames before the fade-in starts
    /* 0x6 */ u16 holdTime;    // frames shown at full alpha
    /* 0x8 */ u8 fadeInStep;   // alpha added per frame
    /* 0x9 */ u8 fadeOutStep;  // alpha removed per frame
    /* 0xA */ u8 resourceId;   // gfxResourceCreate handle (fontStyle & 0x80)
} TextMarkerState;

extern Actor *gSpawnedActor;

void textSpawnMarker(u8 fontStyle, s16 x, s16 y, u8 *textStr, u16 startDelay, u16 holdTime, u8 fadeInStep, u8 fadeOutStep) {
    s32 len;
    TextMarkerState *marker;

    if (actorSpawn(0xE8, 0) != 0) {
        marker = gSpawnedActor->customState;
        if (fontStyle & 0x80) {
            marker->resourceId = gfxResourceCreate((s16)(fontStyle & 0xFF7F), textStr, 2, 160.0f, y, 0.0f);
            gSpawnedActor->moveYaw = 1;
            gSpawnedActor->y = y;
            return;
        }
        if (x == 0) {
            gSpawnedActor->x = (gScreenWidth - textGetStringWidth((s16)fontStyle, textStr)) * 2;
        } else {
            gSpawnedActor->x = x * 4;
        }
        gSpawnedActor->y = y * 4;
        gSpawnedActor->z = fontStyle;
        gSpawnedActor->tintR = 0xFF;
        gSpawnedActor->tintG = 0xFF;
        gSpawnedActor->tintB = 0xFF;
        len = strlen(textStr) + 1;
        marker->text = heapAlloc(len);
        _strcpy(marker->text, textStr);
        marker->startDelay = startDelay;
        marker->holdTime = holdTime;
        marker->fadeInStep = fadeInStep;
        marker->fadeOutStep = fadeOutStep;
    }
}

extern u8 gPlayerCount;

void textSpawnMarkerChecked(u8 fontStyle, s16 x, s16 y, u8 *textStr, u16 startDelay, u16 holdTime, u8 fadeInStep, u8 fadeOutStep) {
    if (gPlayerCount < 2) {
        if (menuIsTransitionType5() == 0) {
            if (func_807142D8() == 0) {
                if (menuIsTransitionType6() != 0 || menuIsTransitionTypeB() != 0) {
                    textSpawnMarker(fontStyle, x, y, textStr, startDelay, holdTime, fadeInStep, fadeOutStep);
                }
            }
        }
    }
}

Gfx *renderAppendScaledMatrix(Gfx *glistp, Actor *actor, s16 xOffset, f32 scale) {
    Mtx *mtx;
    f32 mtxA[4][4];
    f32 mtxB[4][4];

    mtx = heapAlloc(sizeof(Mtx));
    heapFreeDeferred(mtx);
    guScaleF(mtxA, scale, scale, 1.0f);
    guTranslateF(mtxB, (f32)((f64)actor->x + 2.0 * (f64)xOffset), actor->y, 0.0f);
    guMtxCatF(mtxA, mtxB, mtxA);
    guMtxF2L(mtxA, mtx);
    gSPMatrix(glistp++, mtx, G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH);
    return glistp;
}

extern Gfx D_1000118;

extern void *D_8074E880[];

Gfx *textMarkerRenderString(Gfx *gfx, Actor *actor) {
    TextMarkerState *marker;
    s16 x;
    s16 y;
    u8 state;
    u8 mode;
    s16 width;

    if (&state == 0) {} // FAKE: keeps state/mode/width/x/y in spill-style home slots
    marker = actor->customState;
    state = 3;
    mode = (u8)actor->z;
    gSPDisplayList(gfx++, &D_1000118);
    gDPSetCombine(gfx++, 0x119623, 0xFF2FFFFF);

    x = actor->unk155; // FAKE: x reused as the unk155 switch selector (direct switch on actor->unk155 scores 15)
    switch (x) {
        case 2:
            vtxGradientSetPosition((s16)(actor->unk15F * 3 + 0x4000));
            break;
        case 0:
            if (actor->z == 1.0f) {
                s16 confettiX;

                confettiX = (s16)(s32)((((f64)actor->unk15F * 0.0078125 > 1.0 ? 1.0 : (f64)actor->unk15F * 0.0078125) * 0.9) * (f64)textGetStringWidth((s16)(s32)actor->z, marker->text) + (f64)actor->x * 0.25);
                effectSetDepth(1);
                effectSetCallback(effectConfettiPhysicsUpdate);
                effectSetSpeed(0xA);
                effectEnableFade();
                effectCreateAtPosition(D_8074E880[((randomNonNegative() >> 0xF) % 1000) % 3], 1.0f, (f32)confettiX, (f32)((f64)actor->y * 0.25 + 12.0), -5.0f);
            }
        default:
            vtxGradientSetPosition((s16)(actor->unk15F * 3));
            break;
    }

    x = (s16)(s32)actor->x;
    y = (s16)(s32)actor->y;
    switch (mode) {
        case 1:
            width = textGetStringWidth((s16)(s32)actor->z, marker->text);
            state = 0x13;
            gfx = renderAppendScaledMatrix(gfx, actor, width, 0.8f);
            state &= 0xFFFE;
            x = -(width * 2);
            y = 0;
            break;
        case 6:
            state = 0x23;
            gDPSetCycleType(gfx++, G_CYC_2CYCLE);
            gDPSetRenderMode(gfx++, G_RM_PASS, G_RM_XLU_SURF2);
            break;
        case 0:
            mode = 6;
            width = textGetStringWidth(6, marker->text);
            actor->x = (f32)((gScreenWidth - width) * 2);
            gfx = renderAppendScaledMatrix(gfx, actor, width, 0.8f);
            state = 0;
            x = -(width * 2);
            y = 0;
            break;
        case 10:
            mode = 6;
            gfx = renderAppendScaledMatrix(gfx, actor, 0, 0.8f);
            state = 0;
            x = 0;
            y = 0;
            break;
    }

    gDPSetPrimColor(gfx++, 0, 0, actor->tintR, actor->tintG, actor->tintB, actor->unk15F);
    return textDrawStringVtx(gfx, (s16)mode, x, y, marker->text, state);
}

Gfx *textMarkerRender(Gfx *gfx, Actor *actor) {
    TextMarkerState *marker;

    marker = actor->customState;
    gSPDisplayList(gfx++, &D_1000118);
    gDPPipeSync(gfx++);
    gDPSetPrimColor(gfx++, 0, 0, 0xFF, 0xFF, 0xFF, 0xFF);
    gDPSetCombine(gfx++, 0x11FE23, 0xFFFFF3F9);
    gSPMatrix(gfx++, &D_2000180, G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH);
    if (actor->yawSpeed++ < 100) {
        gfx = textDrawAnimated(gfx, marker->resourceId, 2, 160.0f, actor->y, 0.0f, 1.0f);
    } else {
        gfx = textDrawAnimated(gfx, marker->resourceId, 1, 160.0f, actor->y, 0.0f, 1.0f);
    }
    return gfx;
}


void textMarkerUpdate(void) {
    TextMarkerState *marker;

    marker = gCurrentActor->customState;
    if (gCurrentActor->moveYaw != 0) {
        renderCallbacksRegister(textMarkerRender, gCurrentActor, 3);
        return;
    }
    if (!(gCurrentActor->flags & 0x10)) {
        gCurrentActor->yawSpeed = marker->startDelay;
    }
    switch (gCurrentActor->state) {
    case 0:
        if (gCurrentActor->yawSpeed != 0) {
            gCurrentActor->yawSpeed--;
        } else {
            gCurrentActor->state = 1;
        }
        break;
    case 1:
        if (gCurrentActor->unk155 != 3) {
            renderCallbacksRegister(textMarkerRenderString, gCurrentActor, 3);
        }
        switch (gCurrentActor->unk155) {
        case 0:
            if (gCurrentActor->unk15F <= 0xFF - marker->fadeInStep) {
                gCurrentActor->unk15F += marker->fadeInStep;
            } else {
                gCurrentActor->unk15F = 0xFF;
                gCurrentActor->unk155++;
                gCurrentActor->yawSpeed = marker->holdTime;
            }
            break;
        case 1:
            if (gCurrentActor->yawSpeed != 0) {
                gCurrentActor->yawSpeed--;
            } else {
                gCurrentActor->unk155++;
            }
            break;
        case 2:
            if (gCurrentActor->unk15F >= marker->fadeOutStep) {
                gCurrentActor->unk15F -= marker->fadeOutStep;
            } else {
                gCurrentActor->unk155++;
                gCurrentActor->unk15F = 0;
            }
            break;
        case 3:
            heapFree(marker->text);
            actorDespawn(gCurrentActor);
            break;
        }
        break;
    }
}

/* Row-major copy: the target keeps the row offset (i * rowWidth) * 4 as the loop
   invariant and adds src + j * 4 inside, so src is written before the offset. */
void textCopyGlyphBlock(s32 *dst, s32 *src, u8 rowWidth) {
    s16 i;
    s16 j;

    i = 0;
    do {
        for (j = 0; j < rowWidth; j++) {
            *dst++ = src[j + i * rowWidth];
        }
        i++;
    } while (i < 0x20);
}


void *textBuildDigitNode(u8 baseFont, void *nodeBuffer, u8 nodeSlot, u8 digit, u8 glyphWidth) {
    void *glyphSheet;

    glyphSheet = textFontLoadSheet(baseFont + digit);
    if (nodeBuffer != NULL) {
        heapFreeDeferred(nodeBuffer);
    }
    nodeBuffer = heapAlloc(glyphWidth << 7);
    textCopyGlyphBlock(nodeBuffer, glyphSheet, glyphWidth);
    animSetLoopLimit(gCurrentActor, nodeSlot, -1);
    animSetSpeed(gCurrentActor, nodeSlot, 0.0f);
    animSetNodeItem(gCurrentActor, nodeSlot, 0, (s32)nodeBuffer);
    return nodeBuffer;
}

extern u8 gCurrentWorldId;
extern u16 gLevelCollectibleCounts[];
extern u16 D_807446C0[];

void textUpdateThreeDigitCounter(void) {
    s32 pad[3];
    void **digits;
    s32 world;
    u16 count;

    digits = gCurrentActor->customState;
    if (!(gCurrentActor->flags & 0x10) || (gActivePlayerState->stateFlags & 0x20000)) {
        world = mapGetHubWorldIndex(gCurrentWorldId, 0);
        if (world >= 8) {
            world = 0;
        }
        count = gLevelCollectibleCounts[world];
        digits[0] = textBuildDigitNode(0x21, digits[0], 0, count / 100, 0x20);
        digits[1] = textBuildDigitNode(0x21, digits[1], 1, count % 100 / 10, 0x20);
        digits[2] = textBuildDigitNode(0x21, digits[2], 2, count % 10, 0x20);
        gCurrentActor->tintR = 0xFF;
        gCurrentActor->tintG = 0xFF;
        gCurrentActor->tintB = 0xFF;
        gCurrentActor->flags |= 0x800000;
        gActivePlayerState->stateFlags &= ~0x20000;
        if (count >= D_807446C0[world]) {
            gCurrentActor->flags &= ~0x8000;
            gCurrentActor->alpha = 0;
            gCurrentActor->unk144 = 1;
            csModelStateSetFirstByte(8, 2);
            csModelStateSetFirstByte(9, 10);
            csModelStateSetFirstByte(10, 10);
            csModelStateSetFirstByte(11, 10);
            csModelStateSetFirstByte(13, 10);
            csModelStateSetFirstByte(12, 10);
        }
    }
    actorUpdateModelMatrix(gCurrentActor, 0);
}

void textUpdateTwoDigitCounter(void) {
    void **digits;

    digits = gCurrentActor->customState;
    if (!(gCurrentActor->flags & 0x10)) {
        digits[0] = textBuildDigitNode(0x14, digits[0], 0, gCurrentActor->unk155 / 10, 0x10);
        digits[1] = textBuildDigitNode(0x14, digits[1], 1, gCurrentActor->unk155 % 10, 0x10);
    }
    actorUpdateModelMatrix(gCurrentActor, 0);
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


extern s8 D_807F6951;
extern s8 D_807F6950;

void func_8069E088(void) {
    s16 textIndex;

    if (!(gCurrentActor->flags & 0x10)) {
        controllerAnimSetStateIfChanged(gCurrentActor, 0x5ED, 0.0f, 0.0f);
    }
    gCurrentActor->eyeHeight = 0x14;
    if (gCurrentActor->state < 0x1E) {
        gCurrentActor->state++;
    }
    if (gCurrentActor->state == 0x1E) {
        textIndex = 0;
        gCurrentActor->state = 0x64;
        resQueueSetValue(1);
        if (flagGet(0x178, 0) == 0) {
            flagSet(0x178, 1, 0);
        } else {
            textIndex = frameTimingGetMapIndex() * 5 + D_807F6951 + 1;
        }
        resQueueAttachActor(gCurrentActor, 0x29, textIndex);
    }
    if (D_807F6950 != 0) {
        actorDespawn(gCurrentActor);
    }
    gCurrentActor->sub4->scaleX = 0.0f;
    gCurrentActor->sub4->scaleY = 0.0f;
    gCurrentActor->sub4->scaleZ = 0.0f;
    actorUpdateModelMatrix(gCurrentActor, 0);
}
