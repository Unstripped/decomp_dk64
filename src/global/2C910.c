#include "common.h"
#include "actor.h"

extern Actor *gSpawnedActor;

typedef struct {
    u8 r;
    u8 g;
    u8 b;
} Rgb8;

const Rgb8 D_80757F70[8] = {
    { 0xFF, 0xFF, 0xFF },
    { 0xC8, 0x00, 0x32 },
    { 0xDC, 0xC8, 0x00 },
    { 0x32, 0xC8, 0x00 },
    { 0xCA, 0x5B, 0xFF },
    { 0x00, 0x96, 0xFF },
    { 0x32, 0x32, 0xFA },
    { 0x00, 0x00, 0x00 },
};

void actorSetTintFromPalette(u8 arg0) {
    gSpawnedActor->tintR = D_80757F70[arg0].r;
    gSpawnedActor->tintG = D_80757F70[arg0].g;
    gSpawnedActor->tintB = D_80757F70[arg0].b;
}

u8 *_strchr(u8 *, s32);
u32 _strcspn(u8 *, char *);
u8 *_strncpy(u8 *, u8 *, u32);
s32 textGetStringWidth();
u8 *textTableGetString(s32, s32, s32);
void textSpawnMarkerChecked(s32, s32, s32, u8 *, s32, s32, s32, s32);
u32 strlen(u8 *);

void textSpawnSubtitle(arg0, arg1, arg2)
u8 arg0;
u16 arg1;
u8 arg2;
{
    u8 *s;
    u8 sp98[0x3C];
    u8 sp58[0x40];
    u8 sp44[0x14];
    s16 idx;

    s = textTableGetString(1, arg0, 1);
    if (_strchr(s, 0x3A) != 0) {
        _strncpy(sp44, s, idx = _strcspn(s, ":") + 1);
        sp44[idx] = 0;
        textSpawnMarkerChecked(0xA, 0x14, 0x18, sp44, 0, (s16)arg1, 0x32, 0x32);
        actorSetTintFromPalette(arg2);
        s += strlen(sp44);
    }
    if ((s16)textGetStringWidth(6, s) >= 0x12D) {
        idx = (s32)strlen(s) / 2;
        if (s[idx] != 0x20) {
            do {
                idx--;
            } while (s[idx] != 0x20);
        }
        _strncpy(sp98, s, idx);
        sp98[idx] = 0;
        _strncpy(sp58, s + idx + 1, 0xFF);
        textSpawnMarkerChecked(0, 0, 0xCD, sp98, 0, arg1, 0x32, 0x32);
        actorSetTintFromPalette(arg2);
        textSpawnMarkerChecked(0, 0, 0xD7, sp58, 0, arg1, 0x32, 0x32);
        actorSetTintFromPalette(arg2);
        return;
    }
    textSpawnMarkerChecked(0, 0, 0xCD, s, 0, arg1, 0x32, 0x32);
    actorSetTintFromPalette(arg2);
}

extern Actor *gPrimaryPlayerActor;
Actor *spawnNodeActivate(s16, s32);

Actor *actorFromSpawnNodeOrDefault(s16 arg0) {
    Actor *v;

    if (arg0 != 0) {
        v = spawnNodeActivate(arg0, 0);
    }
    if ((arg0 == 0) || (v == 0)) {
        v = gPrimaryPlayerActor;
    }
    return v;
}


#define Matcher14_OFF(p, T, o) (*(T *)((u8 *)(p) + (o)))

extern u8 D_807457E4[];
extern u16 D_80747750[];
extern s8 D_8075536C;
extern s8 D_8076AEE0;
extern s16 D_8076AEF2;
extern s32 D_8076D1F8;
extern s32 D_8076D1FC;
extern void *gCamActor;
extern u8 D_807F5D6C[];
extern u8 D_807F5D70[];
extern s16 D_807F5D7C;
extern Actor *gActivePlayerActor;
extern s32 gGlobalCutsceneFlags;
extern void *gPlayerSlots;
extern f32 gScreenFadeRate;

void actorClearMovementFlags(void *);
s32 actorFindActiveByType(s16, void *);
void actorScriptStart(void *, s32);
s32 actorSpawn(s32, s32);
void commandSetFlags(s8, s8);
void commandSetParameters(s16, s16, s16, u8, u8, u8);
void effectNodeSetTargetPosition(s32, f32, f32, f32);
void func_80028EE8(s32, s32, s32, s32, s32, s32, s32, s32);
void mapRequestTransition(s32, s32);
void mapTransitionToMenuOrPrevious(void);
s16 sfxPlayAtPositionPooled(f32, f32, f32, s16, u8, s16, u8, u8, f32, u8);
void controllerAnimSetState(void *, s16, f32, f32);
void controllerStepMotionWindows(void *);
void actorCheckWorldBounds(void *);
void scriptSetActorRampTarget(void *, f32, f32);
u8 camCueTimerIsRunning(void);
s32 camSetFlags(s32, s32);
void camPausePath(void);
void camSetPathLookAhead(s16);
void camSetPathLookActor(void *, s16);
void camSetPath(u8);
void camLoopPathStep(u8, u8);
void camSetRollBlend(s16, s16, u16);
void camStartShake(s32, u8, u16);
void screenWipeStart();
void actorUpdateModelMatrix(void *, u8);
void csModelStateSetFirstByte();
void func_80641874(s16, s16);
void actorAppendCallbackPayloadA69C(s32, void *, f32, f32, u8, u8);
void func_8067AB20(s32, void *, s32, u8, void *, u8);
void actorCopyPoseAndScale(void *, void *, f32);
void func_80687C48(void);
void playerSetKongByActorType(s16);
void playerResumeLocomotion(void *);
void func_806F0C18(void *);
void playerWaypointPathStartPacked(s32, s32, s16, s16);
void transitionSetState(u8);
void func_8070D8C0(void *, s32, u8);
void func_8070E8DC(s8);
void menuTransitionToMap(s32, s32);
void menuSetTransitionTypeBFlag(void);
void menuTransitionToCreditsOrMap28(s32);
void func_80712830(void *, s32);
void func_80713EB0(s32, s32, s32);
void func_80724994(u8, s16, s16, s16, s16);
void zoneEntrySpawnEffect(s16, s16, s16, s16);
void func_80729AA4(u8);
void mapChunkEffectSetFlag(s16, s16, u8, u8);
s32 mathAngleBetweenPoints2D(f32, f32, f32, f32);
void *n_alSndpPlay(void *, s16, u16, u8, f32, u8, void *);
void n_alSndpStop(s32);
s32 playerStateQueueCallback(s16, void *, u8);
void sfxAllocateChannel(s32, f32);
void sfxPlayActorSound(void *, s16, u8, u8, u8, u8, f32, s8);
void sfxSetMode(s32);
void sfxStopChannel(s32, s32);
void sfxStopSlotSound(void *, u8);
void *spawnNodeSpawnById(s16, s16, s16, s16, s16, s16, s16);
void spawnNodesSetActorStateByFlag(u16, u8);
void zoneEntryGetPosition(u8, u8, f32 *, f32 *, f32 *);

void camPathCommandDispatch(s32 arg0, s32 arg1, s32 arg2) {
    s16 spA0[4];
    void *sp9C;
    void *sp98;
    void *sp94;
    void *q;
    s32 a;
    s32 b;
    f32 sp84;
    f32 sp80;
    f32 sp7C;
    s32 c;
    s32 d;
    s16 sp72;
    s16 node;
    void *p;

    sp9C = Matcher14_OFF(gPrimaryPlayerActor, void *, 0x174);
    actorFindActiveByType(0xC, &sp94);
    p = (void *)((u32)arg1 >> 16); // FAKE: dead store; makes the ushr item precede the (s16)arg1 item (spilltemps slot order)
    b = (s16)(arg1 & 0xFFFF);
    a = (s16)((u32)arg1 >> 16);
    spA0[0] = a;
    spA0[1] = b;
    c = (s16)((u32)arg2 >> 16);
    spA0[2] = c;
    d = (s16)(arg2 & 0xFFFF);
    spA0[3] = d;
    if ((u32)d < 0U) { // FAKE: unreachable call precolors d, keeping its item spilled
        sfxSetMode(d);
    }
    switch (arg0 & 0xFF) {
        case 0x45:
            spawnNodesSetActorStateByFlag(2, 0x40);
            return;
        case 0x42:
            textSpawnSubtitle(a & 0xFF, (s16)(b != 0 ? b : 0x5A), (u8)c);
            return;
        case 0x41:
            mapTransitionToMenuOrPrevious();
            return;
        case 0x3D:
            mapRequestTransition(D_8076AEF2, 0);
            return;
        case 0x3E:
            mapRequestTransition(0x22, 0xC);
            return;
        case 0x40:
            menuTransitionToCreditsOrMap28(0);
            return;
        case 0x36:
            playerSetKongByActorType(a + 2);
            func_806F0C18(gPrimaryPlayerActor);
            return;
        case 0x33:
            q = Matcher14_OFF(actorFromSpawnNodeOrDefault(a), void *, 0x17C);
            Matcher14_OFF(q, u8, 0x30) = 0xFE;
            Matcher14_OFF(q, u8, 0x33) = b;
            Matcher14_OFF(q, u8, 0x22) = c;
            Matcher14_OFF(q, u8, 0x32) = d;
            Matcher14_OFF(q, u8, 0x31) = 1;
            return;
        case 0x34:
            q = Matcher14_OFF(actorFromSpawnNodeOrDefault(a), void *, 0x17C);
            Matcher14_OFF(q, u8, 0x30) = 0xFF;
            return;
        case 0x0:
            Matcher14_OFF(sp9C, s16, 0x70) = Matcher14_OFF(gPrimaryPlayerActor, s16, 0xE6);
            Matcher14_OFF(sp9C, f32, 0x74) = b;
            Matcher14_OFF(sp9C, f32, 0x6C) = a;
            playerStateQueueCallback(0x17, 0, 0);
            return;
        case 0x1:
            func_80028EE8((c + 6) & 0xFF, 0, 0xC8, a & 0xFF, 0, b + 0x28, 0x64, 0xFF);
            return;
        case 0x2:
            Matcher14_OFF(sp9C, s32, 0x1F0) |= 8;
            return;
        case 0x3:
            Matcher14_OFF(sp9C, s32, 0x1F0) &= ~8;
            return;
        case 0x24:
            func_80724994(1, a, b, c, d);
            return;
        case 0x5:
            spawnNodeSpawnById(a, 0, 0, 0, 0, 0, 0);
            return;
        case 0x4:
            if (a != 0) {
                func_80724994(3, a, b, c, d);
                return;
            }
            if (b == 2) {
                Matcher14_OFF(Matcher14_OFF(Matcher14_OFF(gActivePlayerActor, void *, 4), void *, 0), s16, 0x10) = -1;
                actorScriptStart(gActivePlayerActor, D_80747750[c]);
                if (d != 0) {
                    scriptSetActorRampTarget(gActivePlayerActor, d / 100.0, 0);
                    return;
                }
            }
        default:
            return;
        case 0x6:
            camSetPathLookActor(spawnNodeActivate(a, 0), b);
            return;
        case 0x7:
            camLoopPathStep(a, (u8)b);
            return;
        case 0x2D:
            camSetPathLookAhead(a);
            return;
        case 0x2E:
            Matcher14_OFF(actorFromSpawnNodeOrDefault(a), u8, 0x15E) = b;
            return;
        case 0x25:
            playerWaypointPathStartPacked((s32)gPrimaryPlayerActor, 0, a, 0);
            return;
        case 0x26:
            func_80641874(a, b);
            return;
        case 0x27:
            node = a;
            sp72 = b;
            mapChunkEffectSetFlag(node, sp72, 0, (u8)c);
            mapChunkEffectSetFlag(node, sp72, 1, (u8)c);
            mapChunkEffectSetFlag(node, sp72, 2, (u8)c);
            mapChunkEffectSetFlag(node, sp72, 3, (u8)c);
            return;
        case 0x8:
            camSetPath(a);
            return;
        case 0x2B:
            transitionSetState(a);
            return;
        case 0x9:
            camSetRollBlend(a, b, c);
            return;
        case 0x10:
            camStartShake((s32)gCamActor, b, a);
            return;
        case 0xA:
            if (a != 0) {
                p = spawnNodeActivate(a, 0);
                if (b != 0) {
                    Matcher14_OFF(p, s32, 0x60) |= 4;
                    return;
                }
                Matcher14_OFF(p, s32, 0x60) &= ~4;
                return;
            }
            sp72 = 1;
            p = spawnNodeActivate(sp72++, 0);
            if (p != NULL) {
                do {
                    if (b != 0) {
                        Matcher14_OFF(p, s32, 0x60) |= 4;
                    } else {
                        Matcher14_OFF(p, s32, 0x60) &= ~4;
                    }
                    p = spawnNodeActivate(sp72++, 0);
                } while (p != NULL);
                return;
            }
            break;
        case 0xB:
            zoneEntrySpawnEffect(a, b, c, d);
            return;
        case 0x11:
            screenWipeStart(((u32)arg1 >> 16) & 0xFF);
            return;
        case 0xC:
            func_8067AB20((s32)gCamActor, sp94, 0x01000000, 1, spA0, 0);
            return;
        case 0xD:
            func_8067AB20((s32)gCamActor, sp94, 0x01000000, 0x10, spA0, 0);
            spA0[3] = -1;
            func_8067AB20((s32)gCamActor, sp94, 0x01000000, 0xE, spA0, 0);
            return;
        case 0x12:
            func_8067AB20((s32)gCamActor, sp94, 0x01000000, 0x14, spA0, 0);
            return;
        case 0x31:
            if (d != 0) {
                commandSetParameters(0x320, 0x82, 0, 0x64, 0x64, 0x64);
                commandSetFlags(1, 1);
                return;
            }
            commandSetParameters(0x320, 0x82, 0, a, b, c);
            commandSetFlags(1, 0);
            return;
        case 0x32:
            effectNodeSetTargetPosition(a, b, c, d * 0.01);
            return;
        case 0xE:
            func_80729AA4(a);
            return;
        case 0x16:
            sp98 = spawnNodeActivate(a, 0);
            if (sp98 != NULL) {
                if (gGlobalCutsceneFlags & 2) {
                    actorCopyPoseAndScale(gPrimaryPlayerActor, sp98, Matcher14_OFF(Matcher14_OFF(sp98, void *, 4), f32, 0x38));
                } else {
                    actorCopyPoseAndScale(gPrimaryPlayerActor, sp98, 0.15f);
                    Matcher14_OFF(gPlayerSlots, u8, 0x2C0) = 1;
                }
                playerResumeLocomotion(gPrimaryPlayerActor);
                Matcher14_OFF(gPrimaryPlayerActor, s32, 0x60) |= 4;
                Matcher14_OFF(sp98, u8, 0x154) = 0x40;
                return;
            }
            break;
        case 0x20:
            p = spawnNodeActivate(a, 0);
            if (p != NULL) {
                actorCopyPoseAndScale(p, gPrimaryPlayerActor, Matcher14_OFF(Matcher14_OFF(gPrimaryPlayerActor, void *, 4), f32, 0x38));
                Matcher14_OFF(gPrimaryPlayerActor, u8, 0x154) = 0x77;
                Matcher14_OFF(gPrimaryPlayerActor, u8, 0x155) = 0;
                return;
            }
            break;
        case 0x29:
            if (camCueTimerIsRunning() == 0) {
                menuTransitionToMap(a, b);
                return;
            }
            break;
        case 0x43:
            if (camCueTimerIsRunning() == 0) {
                D_8075536C = c;
                menuTransitionToMap(a, b);
                return;
            }
            break;
        case 0x3F:
            func_80713EB0(a, b, c);
            return;
        case 0x2A:
            p = spawnNodeActivate(a, 0);
            if (p != NULL) {
                Matcher14_OFF(p, u8, 0x154) = 0x3C;
                return;
            }
            break;
        case 0x28:
            sp98 = spawnNodeActivate(a, 0);
            if (sp98 != NULL) {
                q = spawnNodeActivate(b, 0);
                if (q != NULL) {
                                        actorCopyPoseAndScale(sp98, q, Matcher14_OFF(Matcher14_OFF(q, void *, 4), f32, 0x38));
                    controllerAnimSetState(sp98, Matcher14_OFF(Matcher14_OFF(Matcher14_OFF(q, void *, 4), void *, 0), s16, 0x10), Matcher14_OFF(Matcher14_OFF(Matcher14_OFF(q, void *, 4), void *, 0), f32, 4), 0.0f);
                    controllerStepMotionWindows(sp98);
                    Matcher14_OFF(sp98, s32, 0x60) |= 4;
                    Matcher14_OFF(q, s32, 0x60) &= ~4;
                    return;
                }
            }
            break;
        case 0x13:
            if (a != 0) {
                sp98 = spawnNodeActivate(a, 0);
            } else {
                actorClearMovementFlags(sp98 = gPrimaryPlayerActor);
            }
            zoneEntryGetPosition(b, c, &Matcher14_OFF(sp98, f32, 0x7C), &Matcher14_OFF(sp98, f32, 0x80), &Matcher14_OFF(sp98, f32, 0x84));
            actorAppendCallbackPayloadA69C(0, sp98, Matcher14_OFF(sp98, f32, 0x7C), Matcher14_OFF(sp98, f32, 0x84), 2, 1);
            {
                s32 t = (d << 12) / 360;
                Matcher14_OFF(sp98, s16, 0xEE) = t;
                Matcher14_OFF(sp98, s16, 0xE6) = t;
            }
            Matcher14_OFF(sp98, f32, 0x9C) = Matcher14_OFF(sp98, f32, 0x80);
            actorUpdateModelMatrix(sp98, 0);
            actorCheckWorldBounds(sp98);
            return;
        case 0x14:
            if (a >= 0) {
                if (a != 0) {
                    sp98 = spawnNodeActivate(a, 0);
                } else {
                    sp98 = gPrimaryPlayerActor;
                }
                D_807F5D7C = sfxPlayAtPositionPooled(Matcher14_OFF(sp98, f32, 0x7C), Matcher14_OFF(sp98, f32, 0x80), Matcher14_OFF(sp98, f32, 0x84), b, (u32)(c != 0 ? (f64)c : 127.5), d != 0 ? d : 0x7F, 0, 0, 0.0f, 0);
                return;
            }
            if (b < 0x800) {
                n_alSndpPlay((void *)D_8076D1F8, b, (u32)(c != 0 ? ((f64)c / 255.0) * 32767.0 : 16383.5), 0x3F, d != 0 ? (f64)d / 127.0 : 1.0, 0, (u8 *)D_807F5D6C + -(a * 4));
                return;
            }
            n_alSndpPlay((void *)D_8076D1FC, (s16)(b - 0x7FF), (u32)(c != 0 ? ((f64)c / 255.0) * 32767.0 : 16383.5), 0x3F, d != 0 ? (f64)d / 127.0 : 1.0, 0, (u8 *)D_807F5D6C + -(a * 4));
            return;
        case 0x19:
            node = (a > 0 ? a : -a) <= 0 ? 0 : (a > 0 ? a : -a) - 1;
            sp72 = node;
            n_alSndpStop(*(s32 *)(D_807F5D70 + sp72 * 4));
            return;
        case 0x1A:
            n_alSndpStop(*(s32 *)(D_807457E4 + D_807F5D7C * 4));
            return;
        case 0x38:
            if (a != 0) {
                sp98 = spawnNodeActivate(a, 0);
            } else {
                sp98 = gPrimaryPlayerActor;
            }
            sfxPlayActorSound(sp98, b, 0, 1, 0, c != 0 ? c : 0xFF, 1.0f, d);
            return;
        case 0x37:
            if (a != 0) {
                sp98 = spawnNodeActivate(a, 0);
            } else {
                sp98 = gPrimaryPlayerActor;
            }
            sfxStopSlotSound(sp98, 0);
            return;
        case 0x1B:
            sfxStopChannel(a, 0);
            return;
        case 0x44:
            sfxSetMode(a & 0xFF);
            return;
        case 0x3C:
            q = Matcher14_OFF(spawnNodeActivate(1, 0), void *, 0x17C);
            Matcher14_OFF(q, u8, 0xD) |= a;
            return;
        case 0x3B:
            Matcher14_OFF(actorFromSpawnNodeOrDefault(a), s16, 0x146) = b;
            return;
        case 0x1C:
            Matcher14_OFF(actorFromSpawnNodeOrDefault(a), s16, 0xE6) = Matcher14_OFF(gPlayerSlots, s16, 0x2C8) & 0xFFF;
            return;
        case 0x30:
            p = actorFromSpawnNodeOrDefault(a);
            if (b >= 0) {
                Matcher14_OFF(p, u8, 0x16A) = b;
                Matcher14_OFF(p, s32, 0x60) |= 0x800000;
                Matcher14_OFF(p, u8, 0x16B) = c;
                Matcher14_OFF(p, u8, 0x16C) = d;
                return;
            }
            Matcher14_OFF(p, s32, 0x60) &= 0xFF7FFFFF;
            return;
        case 0x2C:
            sp98 = actorFromSpawnNodeOrDefault(a);
            zoneEntryGetPosition(b, (u8)c, &sp84, &sp80, &sp7C);
            Matcher14_OFF(sp98, s16, 0xE6) = mathAngleBetweenPoints2D(sp84, sp7C, Matcher14_OFF(sp98, f32, 0x7C), Matcher14_OFF(sp98, f32, 0x84));
            return;
        case 0x2F:
            csModelStateSetFirstByte((s16)a, (s16)(u16)d); // FAKE: prevents sharing this narrowing across calls
            if (b != 0) {
                csModelStateSetFirstByte(b, (s16)d);
            }
            if (c != 0) {
                csModelStateSetFirstByte((s16)c, (s16)d);
                return;
            }
            break;
        case 0x15:
            csModelStateSetFirstByte((s16)a, (s16)b);
            return;
        case 0x17:
            sfxAllocateChannel(a, b != 0 ? (f64)b / 255.0 : 1.0);
            return;
        case 0x18:
            func_8070E8DC(1);
            /* fallthrough */
        case 0x39:
            func_8070D8C0(actorFromSpawnNodeOrDefault(a), (u16)b, (u8)c);
            return;
        case 0x1E:
            actorSpawn(0x108, 0x1D);
            Matcher14_OFF(gSpawnedActor, s16, 0xF0) = c;
            func_8070D8C0(gSpawnedActor, a & 0xFFFF, (u8)b);
            return;
        case 0x1D:
            camPausePath();
            return;
        case 0x21:
            camSetFlags((s32)gCamActor, 0x8000);
            return;
        case 0x22:
            if (a != 0) {
                mapRequestTransition(a, b);
                return;
            }
            func_80712830(gPrimaryPlayerActor, 0);
            return;
        case 0x23:
            D_8076AEE0 = a;
            gScreenFadeRate = b / 100.0;
            return;
        case 0x3A:
            menuSetTransitionTypeBFlag();
            return;
        case 0x35:
            if (a == 0) {
                func_80687C48();
            }
            break;
    }
}
#undef Matcher14_OFF


extern Actor *gCurrentActor;

s32 currentActorTestClearFlag(void) {
    s32 r = 0;

    if (gCurrentActor->contactFlags & 0x100) {
        gCurrentActor->contactFlags &= 0xFEFF;
        r = 1;
    }
    return r;
}

void currentActorClearFlag(void) {
    gCurrentActor->contactFlags &= 0xFEFF;
}
