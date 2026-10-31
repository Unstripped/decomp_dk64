#include "common.h"
#include "actor.h"

extern Actor *D_807FBB40;

void actorUpdateModelMatrix(Actor *, s32);

typedef struct ActorView {
    u8 pad0[0x130];
    u8 unk130;
    u8 unk131;
    u8 pad132[0x178 - 0x132];
    void *unk178;
} ActorView;

typedef struct ActorSubView {
    u8 pad0[0xEC];
    s16 unkEC;
    u8 padEE[0x15F - 0xEE];
    u8 unk15F;
} ActorSubView;

typedef struct PlayerState {
    u8 unk0;
    u8 pad1[0x20F];
    f32 unk210;
    f32 unk214;
    f32 unk218;
    u8 pad21C[0xC];
    f32 unk228;
    f32 unk22C;
    f32 unk230;
} PlayerState;

extern Actor *D_807FBB4C;
extern PlayerState *D_807FC924;
extern u8 D_807506C0[];
extern u8 D_807FBD70;

s16 actorListFindIdByActor(Actor *);
void *spawnNodeActivate(s32, s32);
void animSetStartFrame(Actor *, s32, s32);
s32 animIsPlaying(Actor *, s32);
void animSetSpeed(Actor *, s32, f32);
void animSetLoopLimit(Actor *, s32, s32);
void animSetFinished(Actor *, s32, s32);
void animSetFrameAndSubframe(Actor *, s32, s16, f32);
f32 mathAngleBetweenPointsDeg(s32, s32, s32, s32);
void actorAppendCallback(void *, s32, s32, u8, s32, void *);
void sfxAllocateChannel(s32, f32);

void actorSeekTargetUpdate(void) {
    s16 sp36;
    ActorSubView *sp30;
    f32 sp2C;
    f32 dx;
    f32 dz;

    sp36 = actorListFindIdByActor(D_807FBB40);
    sp30 = spawnNodeActivate(2, 0);
    if (!(D_807FBB40->unk60 & 0x10)) {
        ((ActorView *)D_807FBB40)->unk130 = 0x46;
        ((ActorView *)D_807FBB40)->unk131 = 0x32;
        D_807FBB40->unk6A &= ~1;
        D_807FBB40->unk144 = 2;
        D_807FBB40->unk60 |= 0x80000000;
        D_807FBB40->unk64 |= 0x28;
        animSetStartFrame(D_807FBB40, 0, 1);
    }
    dx = D_807FBB4C->unk7C - D_807FBB40->unk7C;
    dz = D_807FBB4C->unk84 - D_807FBB40->unk84;
    if (dx * dx + dz * dz < 50000.0f) {
        D_807FBB40->unk60 |= 0x400;
    } else {
        D_807FBB40->unk60 &= ~0x400;
    }
    if (sp30 != NULL) {
        if (sp36 == D_807506C0[sp30->unk15F]) {
            dx = D_807FBB40->unk7C - D_807FBB4C->unk7C;
            dz = D_807FBB40->unk84 - D_807FBB4C->unk84;
            if (dx * dx + dz * dz > 900.0f) {
                sp2C = mathAngleBetweenPointsDeg((s32)D_807FBB40->unk7C, (s32)D_807FBB40->unk84, (s32)D_807FBB4C->unk7C, (s32)D_807FBB4C->unk84);
                sp30->unkEC = (s16)(sp2C - mathAngleBetweenPointsDeg((s32)D_807FC924->unk228, (s32)D_807FC924->unk230, (s32)D_807FC924->unk210, (s32)D_807FC924->unk218));
            }
            if (animIsPlaying(D_807FBB40, 0) == 0) {
                animSetSpeed(D_807FBB40, 0, 1.0f);
                animSetLoopLimit(D_807FBB40, 0, -1);
            }
        } else if (animIsPlaying(D_807FBB40, 0) != 0) {
            animSetFinished(D_807FBB40, 0, 1);
            animSetFrameAndSubframe(D_807FBB40, 0, 0, 0);
        }
        if (D_807FBD70 == 4) {
            if (D_807FBB40->unk132 == 4) {
                D_807FBB40->unk132 = 8;
                sfxAllocateChannel(0x43, 1.0f);
                actorAppendCallback(sp30, (s32)D_807FBB40, 0x02000000, (u8)sp36, 0, NULL);
            } else {
                D_807FBB40->unk132 *= 2;
            }
        }
        if ((D_807FBB4C->unk6A & 1) && D_807FBB4C->unk110 == 0) {
            D_807FBB40->unk132 = 1;
        }
    }
    actorUpdateModelMatrix(D_807FBB40, 0);
}


typedef struct ActorSub178 {
    u8 unk0;
    u8 unk1;
} ActorSub178;

typedef struct ActorParentRamp {
    u8 pad0[0xB8];
    f32 unkB8;
} ActorParentRamp;

typedef struct ActorModelScript {
    u8 pad0[0x64];
    u16 unk64;
} ActorModelScript;

void func_80724CA4(s32, s32);
void actorCopyPoseAndScale(Actor *, void *, f32);
void actorUpdatePulseIntensity(s32);
void actorScriptStart(Actor *, s32);
void scriptSetActorRampTarget(void *, f32, f32);
void func_8065D254(void *, s32, s32, s32, s32, s32, s32, s32, s32, s32, f32);

void actorUpdateRampTarget(void) {
    ActorSub178 *sp44;
    ActorParentRamp *sp40;

    sp44 = ((ActorView *)D_807FBB40)->unk178;
    sp40 = (ActorParentRamp *)D_807FBB40->unk11C;
    if (!(D_807FBB40->unk60 & 0x10)) {
        func_80724CA4(2, 2);
    }
    actorCopyPoseAndScale(D_807FBB40, sp40, 0.15f);
    if (D_807FBB40->unk154 != 0) {
        actorUpdatePulseIntensity(1);
        if (sp44->unk1 == 0) {
            D_807FBB40->unk154 = 0;
        }
    }
    if (0.0f != sp40->unkB8) {
        if (sp40->unkB8 > 50.0f && ((ActorModelScript *)D_807FBB40->unk4)->unk64 != 0x233) {
            actorScriptStart(D_807FBB40, 0x233);
        } else if (50.0f >= sp40->unkB8) {
            if (((ActorModelScript *)D_807FBB40->unk4)->unk64 != 0x232) {
                actorScriptStart(D_807FBB40, 0x232);
            }
        }
        scriptSetActorRampTarget(D_807FBB40, sp40->unkB8 * 0.01, 4.0f);
    } else {
        if (((ActorModelScript *)D_807FBB40->unk4)->unk64 != 0x234) {
            actorScriptStart(D_807FBB40, 0x234);
        }
    }
    func_8065D254(D_807FBB40, 0x3C8, 0x40, 0x40, 0xA, 0xA, 1, 0x12C, 0xC8, 0, 1.0f);
    actorUpdateModelMatrix(D_807FBB40, 0);
}

void func_806A1ABC(void) {
}

extern s32 D_8076A064;
extern s32 D_8071FFA0;
extern ActorGlobalState D_807FBB70;

s32 flagGet(s16, s32);
void func_80613C48(Actor *, s16, f32, f32);
void func_80728950(s32);
void actorSetUniformScale(Actor *, f32);
void currentActorAnimSetFrame(s32, s32);
void resQueueRemove(Actor *);
void func_8070D8C0(Actor *, s32, s32);
void camStartPath(Actor *, s32, s32);
void flagSet(s32, s32, s32);
s32 randomNonNegative(void);
void effectDecelDriftFadeUpdate(void);
void func_8071498C(void *);
void func_80714950(s32);
void func_807149B8(s32);
void func_807149C8(s32, s32, s32, s32);
void func_80714998(s32);
void func_80714CC0(void *, f32, f32, f32, f32);
void func_8072881C(s32, void *);

void func_806A1AC4(void) {
    f32 speed;
    s16 i;

    if (!(D_807FBB40->unk60 & 0x10)) {
        D_807FBB40->unk60 &= ~0x8000;
        func_80728950(0);
        actorSetUniformScale(D_807FBB40, 1.2f);
        D_807FBB40->unk60 |= 0x400;
        D_807FBB40->unk12A = 0x3E8;
        if (flagGet(0xFB, 0) != 0) {
            func_80613C48(D_807FBB40, 0x597, 0.0f, 0.0f);
            currentActorAnimSetFrame(0, 0);
            D_807FBB40->unk154 = 3;
        } else {
            func_80613C48(D_807FBB40, 0x598, 0.0f, 0.0f);
            scriptSetActorRampTarget(D_807FBB40, 0.0f, 0.0f);
            D_807FBB40->unk144 = 1;
            D_807FBB40->unk60 &= ~4;
        }
    }
    switch (D_807FBB40->unk154) {
    case 0:
        if (D_807FBB70.unk254 != 0 && D_807FBB70.unk258[0] == 1) {
            resQueueRemove(D_807FBB40);
            func_8070D8C0(D_807FBB40, 0x1F, 1);
            camStartPath(D_807FBB40, 0x12, 1);
            flagSet(0xFB, 1, 0);
            D_807FBB40->unk154 = 1;
        } else if (flagGet(0xFB, 0) == 0 && flagGet(0x21, 2) == 0) {
            if ((D_807FBB40->unk7C - D_807FBB4C->unk7C) * (D_807FBB40->unk7C - D_807FBB4C->unk7C) + (D_807FBB40->unk84 - D_807FBB4C->unk84) * (D_807FBB40->unk84 - D_807FBB4C->unk84) < 19600.0f) {
                func_8070D8C0(D_807FBB4C, 0x1F, 0);
                flagSet(0x21, 1, 2);
            }
        }
        break;
    case 1:
        if (D_807FBB70.unk254 != 0 && D_807FBB70.unk258[0] == 1) {
            actorScriptStart(D_807FBB40, 0x328);
            D_807FBB40->unk154 = 2;
            D_807FBB40->unk144 = 2;
            D_807FBB40->unk60 |= 4;
        }
        break;
    case 2:
        switch (D_807FBB40->unk155[0]) {
        case 0:
            if (!(D_8076A064 & 7)) {
                for (i = 0; i < 0xC; i++) {
                    speed = (((randomNonNegative() >> 15) % 32767) % 171 + 0x96) * 0.01;
                    func_8071498C((void *)effectDecelDriftFadeUpdate);
                    func_80714950(i);
                    func_807149B8(1);
                    func_807149C8(0x8C, 0x8C, 0x8C, 0xFF);
                    func_80714998(5);
                    func_80714CC0(&D_8071FFA0, speed, D_807FBB40->unk7C, D_807FBB40->unk80 + 50.0f, D_807FBB40->unk84);
                }
            }
            break;
        case 2:
            currentActorAnimSetFrame(0, 0);
            D_807FBB40->unk155[0]++;
            break;
        case 4:
            currentActorAnimSetFrame(0, 2);
            D_807FBB40->unk155[0]++;
            break;
        case 6:
            currentActorAnimSetFrame(0, 0);
            D_807FBB40->unk154++;
            break;
        }
        break;
    case 3:
        func_8072881C(0, (u8 *)D_807FBB40 + 0xEC);
        break;
    }
    actorUpdateModelMatrix(D_807FBB40, 0);
}

void actorFinishInRange(void) {
    D_807FBB40->unk60 |= 0x400;
    actorUpdateModelMatrix(D_807FBB40, 0);
}

s32 camIsCutsceneActive(void);

void actorPlaySoundVariantAndFinish(void) {
    if (camIsCutsceneActive() != 0) {
        func_80613C48(D_807FBB40, 0x640, 0, 8.0f);
    } else {
        func_80613C48(D_807FBB40, 0x63F, 0, 8.0f);
    }
    actorUpdateModelMatrix(D_807FBB40, 0);
}

static void stub_806A1FD0(void) {
}

typedef struct ActorSinkState {
    s16 unk0;
    u8 pad2[2];
    f32 unk4;
    f32 unk8;
} ActorSinkState;

extern s32 D_8071FF18;

void actorDespawn(Actor *);
s32 actorListLookupEntry(u16);
s32 actorTableContains(Actor *);
void actorGetNodePos(Actor *, s32, f32 *, f32 *, f32 *);
void func_80717D4C(void);

void actorSpawnNodeEntryScaled(s32, f32, f32, f32, s32, s32, s32, s32);
void sfxPlayFromActorWithAltitudeCheck(Actor *, s32, s32, s32, s32);

void actorSinkAndDespawn(void) {
    s32 count;
    s32 i;
    s32 node;
    u8 found;
    f32 sp54;
    f32 sp50;
    f32 sp4C;
    ActorSinkState *sub;
    Actor *act;

    sub = D_807FBB40->unk174;
    if (!(D_807FBB40->unk60 & 0x10)) {
        D_807FBB40->unk64 |= 8;
        sub->unk0 = 0;
        sub->unk4 = 0.0f;
        sub->unk8 = D_807FBB40->unk80;
        ((ActorView *)D_807FBB40)->unk130 = 0x46;
        ((ActorView *)D_807FBB40)->unk131 = 0x14;
        node = actorListFindIdByActor(D_807FBB40);
        i = actorListLookupEntry(node);
        if (flagGet(i, 0) != 0) {
            actorDespawn(D_807FBB40);
        }
    }
    if (D_807FBB4C->unk154 == 0x2D && D_807FBB4C->unk155[0] != 0) {
        found = 0;
        if (D_807FBB40->unk114 != NULL) {
            count = D_807FBB40->unk114->count;
            do { i = 0; } while (0);
            if (count != 0) {
                do {
                    act = (Actor *)D_807FBB40->unk114->items[i];
                    if (actorTableContains(act) != 0 && act == D_807FBB4C) {
                        found = 1;
                    }
                    count--;
                    i++;
                } while (count != 0 && found == 0);
            }
        }
        if (found != 0) {
            node = 1;
            if (sub->unk0 == 0) {
                do {
                    func_80714998(2);
                    func_807149B8(1);
                    func_8071498C(&func_80717D4C);
                    func_80714950(-0x64);
                    func_807149C8(0x64, 0x46, 0x1E, 0xFF);
                    actorGetNodePos(D_807FBB40, node, &sp54, &sp50, &sp4C);
                    func_80714CC0(&D_8071FF18, 2.0f, sp54, sp50 + 10.0, sp4C);
                    node++;
                } while (node != 9);
                sub->unk0 = 0xF;
                sfxPlayFromActorWithAltitudeCheck(D_807FBB40, 0x1C1, 0xFF, 0x7F, 1);
            }
        }
    }
    if (sub->unk0 >= 2) {
        sub->unk0--;
    }
    if (sub->unk0 == 2) {
        node = actorListFindIdByActor(D_807FBB40);
        i = actorListLookupEntry(node);
        actorSpawnNodeEntryScaled(0x8C, D_807FBB40->unk7C, D_807FBB40->unk80 + 10.0f, D_807FBB40->unk84, 0, 1, i, 0);
    }
    if (sub->unk0 < 0xA && sub->unk0 != 0) {
        sub->unk4 = sub->unk4 + 1.0;
        if (sub->unk4 > 20.0) {
            sfxAllocateChannel(0x90, 1.0f);
            actorDespawn(D_807FBB40);
        }
    }
    D_807FBB40->unk80 -= sub->unk4;
    actorUpdateModelMatrix(D_807FBB40, 0);
    D_807FBB40->unk80 = sub->unk8;
}


typedef struct MidpointOrbitActorView {
    u8 pad0[0xEC];
    s16 unkEC;
    u8 padEE[0xFA - 0xEE];
    s16 unkFA;
} MidpointOrbitActorView;

typedef struct MidpointOrbitConfig {
    u8 pad0[4];
    f32 unk4;
    u8 pad8[4];
    f32 unkC;
} MidpointOrbitConfig;

typedef struct MidpointOrbitState {
    s16 unk0;
    s16 unk2;
    s16 unk4;
    s16 unk6;
    s16 unk8;
} MidpointOrbitState;

#define ORBIT_ACTOR ((MidpointOrbitActorView *)D_807FBB40)

void billboardSetFlags(s16);
void func_8067ACB4(Actor *);
f32 func_80612790(s16);
f32 func_80612794(s16);
void actorUpdateFloorContactAndTilt(Actor *, f32);
void sfxPlayAtPositionPooled(f32, f32, f32, s16, s32, s32, s32, s32, f32, s32);
s16 mathAngleBetweenPoints2D(f32, f32, f32, f32);

void actorMidpointOrbitUpdate(void) {
    MidpointOrbitState *sub;
    f32 ratio;
    Actor *p;

    sub = D_807FBB40->unk174;
    if (!(D_807FBB40->unk60 & 0x10)) {
        D_807FBB40->unk60 |= 0x1000;
        actorSetUniformScale(D_807FBB40, ((MidpointOrbitConfig *)D_807FBB40->unk124)->unkC);
        D_807FBB40->unk168 = mathAngleBetweenPoints2D(D_807FBB40->unk7C, D_807FBB40->unk84, D_807FBB4C->unk7C, D_807FBB4C->unk84);
        D_807FBB40->unkF0 = (D_807FBB4C->unk80 + (f32)D_807FBB4C->unk15E - D_807FBB40->unk80) * 0.5;
        ORBIT_ACTOR->unkEC = sqrtf((D_807FBB40->unk7C - D_807FBB4C->unk7C) * (D_807FBB40->unk7C - D_807FBB4C->unk7C) + (D_807FBB40->unk84 - D_807FBB4C->unk84) * (D_807FBB40->unk84 - D_807FBB4C->unk84)) * 0.5;
        sub->unk0 = D_807FBB40->unk7C + (D_807FBB4C->unk7C - D_807FBB40->unk7C) * 0.5;
        sub->unk2 = D_807FBB40->unk80 + (D_807FBB4C->unk80 - D_807FBB40->unk80) * 0.5;
        sub->unk4 = D_807FBB40->unk84 + (D_807FBB4C->unk84 - D_807FBB40->unk84) * 0.5;
        D_807FBB40->unk144 = 0x24;
        ORBIT_ACTOR->unkFA = 0x2328;
        D_807FBB40->unk160 = ((MidpointOrbitConfig *)D_807FBB40->unk124)->unk4;
        {
            f64 v = D_807FBB40->unk160 * (ORBIT_ACTOR->unkEC * 0.01);
            D_807FBB40->unk160 = (v > 15.0 ? v : 15.0) < 150.0 ? (v > 15.0 ? v : 15.0) : 150.0;
        }
        sub->unk8 = D_807FBB40->unk160;
    }
    func_8067ACB4(D_807FBB40);
    ratio = (sub->unk8 / D_807FBB40->unk160) * -4096.0 + 4096.0;
    sub->unk6 = D_807FBB40->unk168 + ratio;
    D_807FBB40->unk7C = func_80612794(sub->unk6) * ORBIT_ACTOR->unkEC + sub->unk0;
    D_807FBB40->unk84 = func_80612790(sub->unk6) * ORBIT_ACTOR->unkEC + sub->unk4;
    D_807FBB40->unk80 = func_80612790(2048.0f + ratio) * D_807FBB40->unkF0 + sub->unk2;
    actorUpdateFloorContactAndTilt(D_807FBB40, 0);
    D_807FBB40->unkE6 += 0x12C;
    if ((D_807FBB40->unkE6 & 0x7FF) < 0x12C) {
        sfxPlayAtPositionPooled(D_807FBB40->unk7C, D_807FBB40->unk80, D_807FBB40->unk84, 0x1DF, 0xFF, 0x7F, 0x14, 0x3C, 0.7f, 0);
    }
    if (sub->unk8 != 0) {
        sub->unk8 = sub->unk8 - 1;
        if (sub->unk8 == 0xB) {
            p = (Actor *)D_807FBB40->unk11C;
            if (p != NULL) {
                p->unk155[0]++;
            }
        }
    } else {
        actorDespawn(D_807FBB40);
    }
    billboardSetFlags(1);
    func_8065D254(D_807FBB40, 0x3C8, 0x40, 0x40, 0x1E, 0x1E, 1, 0x12C, 0xB4, 0, 1.0f);
    actorUpdateModelMatrix(D_807FBB40, 0);
}

void mathAngleBetweenPoints3D(s16 *, s16 *, f32, f32, f32, f32, f32, f32);

void actorPlaceModelAtCamera(void) {
    s16 spBE;
    s16 spBC;
    f32 mtx1[4][4];
    f32 mtx2[4][4];

    mathAngleBetweenPoints3D(&spBE, &spBC, D_807FC924->unk210, D_807FC924->unk214, D_807FC924->unk218, D_807FC924->unk228, D_807FC924->unk22C, D_807FC924->unk230);
    D_807FBB40->unkE6 = spBC;
    D_807FBB40->unkE8 = spBE;
    guRotateF(mtx1, spBE / 4095.0 * 360.0, 1.0f, 0.0f, 0.0f);
    guRotateF(mtx2, spBC / 4095.0 * 360.0, 0.0f, 1.0f, 0.0f);
    guMtxCatF(mtx1, mtx2, mtx1);
    guTranslateF(mtx2, D_807FC924->unk210, D_807FC924->unk214, D_807FC924->unk218);
    guMtxCatF(mtx1, mtx2, mtx1);
    guMtxXFMF(mtx1, 0.0f, 0.0f, -11.0f, &D_807FBB40->unk7C, &D_807FBB40->unk80, &D_807FBB40->unk84);
    guTranslateF((f32 (*)[4])((u8 *)D_807FBB40 + 0xC), 0.0f, -20.0f, 0.0f);
    actorUpdateModelMatrix(D_807FBB40, 1);
}
