#include "common.h"
#include "actor.h"

typedef struct Struct_5390 {
    f32 arr[3];
} Struct_5390;

typedef struct Actor174_5390 {
    f32 unk0;
    u16 unk4;
    u8 unk6;
} Actor174_5390;

typedef struct Actor338 {
    u8 pad[0x338];
    void *unk338;
} Actor338;

extern Actor *D_807FBB40;
extern Actor *D_807FBB44;
extern Struct_5390 D_8074E88C;
extern void *D_8074E880[];
extern u32 gFrameCounter;
extern u8 D_80750AD0;
extern s32 D_8071FC0C;
extern s32 D_8071FE08;
extern s32 D_8071FED0;
extern s32 D_8071FF18;
extern s32 D_8071FF40;
extern s32 D_8071FFA0;
extern s32 D_8072006C;
extern s32 D_80720120;
extern s32 D_80720558;
extern s32 D_8072073C;
extern s32 D_80720B58;
extern s32 D_807210EC;
extern s32 D_80721158;
extern s32 D_8072139C;

s32 actorSpawn();
void actorDespawn(Actor *);
void sfxAllocateChannel(s32, f32);
void sfxPlayFromActorWithAltitudeCheck(void *, s32, s32, s32, s32);
void sfxPlayOnFreeSlot(s32, s32, f32, f32, s32, s32);
s32 randomLcgNext(void);
s32 randomNonNegative(void);
void actorScriptStart(Actor *, s32);
void actorUpdateModelMatrix(Actor *, s32);
void triggerZoneCheckEntry(Actor *);
s32 func_80665AAC(Actor *);
void actorGetNodePos(Actor *, s32, f32 *, f32 *, f32 *);
void actorCopyPoseAndScale(Actor *, Actor *, f32);
void effectSpawnBoneWhite(Actor *, s16, f32, f32, f32, f32, s32);
void effectSpawnBoneDefault(Actor *, s16, f32, f32, f32, f32, s32);
void effectSpawnBone(Actor *, s16, f32, f32, f32, f32, s32);
void effectActorCheckGroundScaleSpawn(Actor *);
void effectSpawnDebrisParticles(Actor *, f32, f32, f32, f32);
void animSetSpeed(Actor *, s32, f32);
void animSetLoopLimit(Actor *, s32, s32);
s32 animIsPlaying(Actor *, s32);
void actorSpawnAttachedTo(Actor *);
void func_80714950();
void func_8071495C(void);
void func_8071496C(s32);
void func_8071498C(void (*)(void));
void func_80714998(s32);
void func_807149B8(s32);
void func_807149C8(s32, s32, s32, s32);
void func_807149FC(s32);
void func_80714A28(s32);
void func_80714C08(void *, f32, Actor *, s32, s32);
Actor338 *func_80714CC0(void *, f32, f32, f32, f32);
void func_80717930(void);
void func_80717D4C(void);
void func_80718080(void);
void func_8071827C(void);
void effectGroundDecalSpinUpdate(void);
void effectTumbleBounceUpdate(void);
void effectDecelerateDriftUpdate(void);
void timedEffectCountdownTick(void);
void effectSpiralRiseUpdate(void);
void effectSpriteMotionUpdate(void);
void effectFollowParentUpdate(void);
void effectFloorFallUpdate(void);
void effectActorOrbitFollowUpdate(void);
void func_8071E110(void *, s32, s32, f32, f32, s32);
void effectArcAroundActorUpdate(void);
void effectBurstParticleUpdate(void);
void func_8071EFDC(void);

void effectSpawnActorBone(s32 arg0, u8 arg1, f32 arg2) {
    func_807149B8(1);
    func_8071498C(effectFollowParentUpdate);
    func_80714950(arg0);
    func_80714A28(4);
    func_80714C08(&D_80720120, arg2, D_807FBB40, arg1, 0);
}

void effectSpawnRandomBoneDebris(u8 arg0, u8 arg1) {
    f32 sp2C;
    u8 sp2B;

    if (!(gFrameCounter & 3)) {
        sp2C = (f32)(D_807FBB40->unk4->unk38 / 0.15);
        sp2B = ((randomNonNegative() >> 15) % 0x7FFF) % ((arg1 - arg0) + 1) + arg0;
        func_80714998(3);
        func_807149C8(0xE6, 0xE6, 0xE6, 0xE6);
        effectSpawnBoneDefault(D_807FBB40, sp2B, sp2C, 0.0f, 0.0f, 0.0f, -0x78);
    }
}

void actorSpawnEffectChild(f32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, Actor *arg5, u8 arg6) {
    s32 var_a1 = 0xAD;

    if (arg5 != NULL) {
        switch (arg5->unk58) {
        case 5:
        case 0xF4:
            var_a1 = 0xD1;
            break;
        case 4:
        case 0xF3:
            var_a1 = 0xD0;
            break;
        case 6:
        case 0xF5:
            var_a1 = 0xCF;
            break;
        case 3:
        case 0xF2:
            var_a1 = 0xAE;
            break;
        }
    }
    actorSpawn(0xFF, var_a1, arg5);
    D_807FBB44->unk11C = (s32)arg5;
    D_807FBB44->unk4->unk34 = arg3;
    D_807FBB44->unk4->unk3C = arg3;
    D_807FBB44->unk4->unk38 = arg4;
    D_807FBB44->unk7C = arg0;
    D_807FBB44->unk80 = arg1;
    D_807FBB44->unk84 = arg2;
    if ((arg5 != NULL) && (arg5->unk5C & 1)) {
        if (arg6 != 0) {
            D_807FBB44->unk168 = 0xF;
            *(f64*)&D_807FBB44->unk160 = 1.11;
            D_807FBB44->unk15F = 1;
            return;
        }
        D_807FBB44->unk168 = 0x19;
        *(f64*)&D_807FBB44->unk160 = 1.09;
        return;
    }
    D_807FBB44->unk168 = 0x20;
    *(f64*)&D_807FBB44->unk160 = 1.07;
    D_807FBB44->unk15F = 0;
}

extern s32 D_8071FF58;
void effectWobbleScaleUpdate(void);

void effectSpawnSmoke(u8 arg0) {
    if (!(gFrameCounter & 0x1F)) {
        func_80714998(2);
        func_807149B8(1);
        func_807149FC(0x3C);
        func_8071498C(effectWobbleScaleUpdate);
        if (arg0) {
            func_80714C08(&D_8071FF58, 0.05f, D_807FBB40, (u8)arg0, 0);
        } else {
            func_80714CC0(&D_8071FF58, 0.05f, D_807FBB40->unk7C, D_807FBB40->unk80, D_807FBB40->unk84);
        }
    }
}

void effectSpawnBurst(u8 arg0) {
    if (arg0) {
        func_80714950(((s32)(randomNonNegative() >> 15) % 10) + 0x8008);
    } else {
        func_80714950(((s32)(randomNonNegative() >> 15) % 8) + 6);
    }
    func_807149FC(2);
    func_8071498C(func_80717930);
    func_807149B8(1);
    func_80714A28(4);
    func_80714C08(&D_8072139C, (f32)(((f64)((s32)(randomNonNegative() >> 15) % 50) / 80.0) + 0.1), D_807FBB40, 8, 0);
}

void effectSpawnBoneDebris(s16 arg0, s8 arg1) {
    f32 sp3C;
    f32 sp38;
    f32 sp34;
    f32 sp30;

    sp30 = (f32)(D_807FBB40->unk4->unk38 / 0.15);
    actorGetNodePos(D_807FBB40, arg0, &sp3C, &sp38, &sp34);
    func_80714950((((s32)(randomNonNegative() >> 15) % 100) + 0x190) * arg1);
    func_8071498C(func_80717D4C);
    func_807149B8(1);
    func_80714CC0(D_8074E880[((randomNonNegative() >> 15) % 1000) % 3],
                   (f32)((f64)sp30 * 0.8),
                   (f32)((randomNonNegative() >> 15) % 20) + (sp3C - 10.0f),
                   sp38,
                   (f32)((randomNonNegative() >> 15) % 20) + (sp34 - 10.0f));
}

void func_8071F2F8(void);

void effectSpawnBoneDebrisScaled(s16 arg0, s16 arg1, s16 arg2) {
    f32 sp54;
    f32 sp50;
    f32 sp4C;
    f32 sp48;
    f64 var_fv1;

    sp48 = (f32)((f64)D_807FBB40->unk4->unk38 / 0.15);
    actorGetNodePos(D_807FBB40, arg0, &sp54, &sp50, &sp4C);
    func_80714950(arg1 + (arg2 << 16));
    func_8071498C(func_8071F2F8);
    func_807149B8(1);
    if (((f64)arg2 * 0.02) < 2.0) {
        var_fv1 = 2.0;
    } else {
        var_fv1 = (f64)arg2 * 0.02;
    }
    func_807149FC((s32)var_fv1);
    func_80714CC0(D_8074E880[((randomNonNegative() >> 15) % 1000) % 3],
                   (f32)((f64)sp48 * 0.8),
                   (f32)((randomNonNegative() >> 15) % 60) + (sp54 - 30.0f),
                   sp50,
                   (f32)((randomNonNegative() >> 15) % 60) + (sp4C - 30.0f));
}

extern s32 D_8071FC40;
void effectWobbleRiseUpdate(void);

void effectSpawnAuraBurst(u8 arg0) {
    s32 i;
    f32 x, y, z;

    if ((((u32)randomLcgNext() / 10000) % arg0) == 0) {
        if (D_80750AD0 == 0) {
            for (i = 0; i != 4U; i++) {
                x = (f32)(((f64)(f32)((u32)randomLcgNext() / 10000 % 200) / 10.0) - 5.0);
                y = (f32)(((f64)(f32)((u32)randomLcgNext() / 10000 % 200) / 10.0) - 5.0);
                z = (f32)(((f64)(f32)((u32)randomLcgNext() / 10000 % 200) / 10.0) - 5.0);
                func_807149B8(1);
                func_80714950(1);
                func_807149FC(-1);
                func_8071498C(effectWobbleRiseUpdate);
                func_80714A28(4);
                func_80714CC0(&D_8071FC40, 0.0f, D_807FBB40->unk7C + x, D_807FBB40->unk80 + y, D_807FBB40->unk84 + z);
            }
        }
    }
}

void effectSpawnSparks(u8 arg0, u8 arg1) {
    if (!(arg0 & gFrameCounter)) {
        func_8071498C(effectWobbleRiseUpdate);
        func_807149B8(1);
        func_807149FC(-1);
        func_80714A28(4);
        if (arg1) {
            func_80714C08(&D_8071FC40, 0.0f, D_807FBB40, (u8)arg1, 0);
        } else {
            func_80714CC0(&D_8071FC40, 0.0f, D_807FBB40->unk7C, D_807FBB40->unk80, D_807FBB40->unk84);
        }
    }
}

void effectSpawnRing(void) {
    f32 temp;
    s32 i;

    temp = (f32)(D_807FBB40->unk4->unk38 / 0.15);
    func_807149B8(0);
    func_807149FC(1);
    func_80714CC0(&D_8071FE08, (f32)((f64)temp * 0.75), D_807FBB40->unk7C, D_807FBB40->unk80, D_807FBB40->unk84);
    for (i = 0; i < 7; i++) {
        func_807149B8(1);
        func_807149FC(0xA);
        func_8071498C(effectTumbleBounceUpdate);
        func_80714998(2);
        func_80714950(0);
        func_80714CC0(&D_8072073C, (f32)((f64)temp * 0.15), D_807FBB40->unk7C, D_807FBB40->unk80, D_807FBB40->unk84);
    }
}

void func_80685210(f32 arg0, s16 arg1, s16 arg2) {
    if (((gFrameCounter % 3) == 0) && ((f32)arg1 < D_807FBB40->unkB8)) {
        func_80714998(2);
        func_807149B8(1);
        func_8071498C(func_80717D4C);
        func_80714950(-0x32);
        func_80714A28(4);
        func_80714C08(&D_8071FF18, arg0, D_807FBB40, arg2, 0);
    }
}

void effectSpawnOctagonRing(f32 arg0, f32 arg1, f32 arg2, f32 arg3) {
    s16 var_s0;

    for (var_s0 = 0; var_s0 < 8; var_s0++) {
        func_8071498C(effectDecelerateDriftUpdate);
        func_80714950(var_s0);
        func_807149B8(1);
        func_807149C8(0xFF, 0xFF, 0xFF, 0xC8);
        func_80714CC0(&D_8071FFA0, arg0, arg1, arg2, arg3);
    }
}

void actorScaleGrowthUpdate(void) {
    Actor174_5390 *temp_v0 = D_807FBB40->unk174;
    Struct_5390 sp20 = D_8074E88C;

    if (!(D_807FBB40->unk60 & 0x10)) {
        temp_v0->unk0 = D_807FBB40->unk4->unk38;
    }
    temp_v0->unk4++;
    switch (D_807FBB40->unk154) {
    case 0:
        D_807FBB40->unk4->unk38 = sp20.arr[temp_v0->unk6] * (temp_v0->unk0 * (f32)(u32)temp_v0->unk4 * 0.33333334f);
        if ((f32)(u32)temp_v0->unk4 > 3.0f) {
            D_807FBB40->unk154 = 1;
            temp_v0->unk4 = 0;
            animSetLoopLimit(D_807FBB40, 0, 1);
            animSetSpeed(D_807FBB40, 0, 0.5f);
        }
        break;
    case 1:
        if (animIsPlaying(D_807FBB40, 0) == 0) {
            actorDespawn(D_807FBB40);
        }
        break;
    }
    actorUpdateModelMatrix(D_807FBB40, 0);
}

void effectSpawnMultiTierRing(f32 arg0, u8 arg1, f32 arg2, f32 arg3, f32 arg4) {
    s32 temp_t6;
    s32 var_s0;

    temp_t6 = arg1;
    if (D_80750AD0 == 0) {
        if (temp_t6 > 0) {
            effectSpawnOctagonRing(arg0, arg2, arg3, arg4);
        }
        if (temp_t6 >= 2) {
            for (var_s0 = 0; var_s0 < 8; var_s0++) {
                func_8071498C(timedEffectCountdownTick);
                func_80714950(var_s0);
                func_807149B8(1);
                func_807149FC(-1);
                func_807149C8(0xFF, 0xFF, 0xFF, 0xFF);
                func_80714CC0(&D_8071FF40, (f32)((f64)arg0 * 0.5), arg2, arg3, arg4);
            }
        }
        if (temp_t6 >= 3) {
            for (var_s0 = 0; var_s0 < 9; var_s0++) {
                func_8071498C(effectSpiralRiseUpdate);
                func_80714950(var_s0);
                func_807149B8(1);
                func_807149FC(-1);
                func_807149C8(0xFF, 0xFF, 0xFF, 0xFF);
                func_80714CC0(D_8074E880[var_s0 % 3], arg0, arg2, arg3, arg4);
            }
        }
    }
}

typedef struct MultiTierRingParams {
    s32 a[4];
} MultiTierRingParams;

extern MultiTierRingParams D_8074E898;

void effectSpawnMultiTierRingWithActor(Actor *arg0, u8 arg1) {
    s32 pad0[1];
    MultiTierRingParams sp34;
    f32 temp_scale;
    void *sub;
    s32 pad1[1];

    temp_scale = (f32)((f64)arg0->unk4->unk38 / 0.15);
    sp34 = D_8074E898;
    if (arg1) {
        effectSpawnMultiTierRing((f32)((f64)temp_scale * 0.36), arg1, arg0->unk7C, arg0->unk80 + 4.0f, arg0->unk84);
        actorSpawn(0x145, sp34.a[arg1]);
        actorCopyPoseAndScale(D_807FBB44, arg0, arg0->unk4->unk38 * 0.5f);
        sub = D_807FBB44->unk174;
        ((Actor174_5390 *)sub)->unk6 = arg1 - 1;
    }
}

void effectSpawnBoneWhite(Actor *arg0, s16 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, s32 arg6) {
    func_80714998(2);
    func_807149C8(0xFF, 0xFF, 0xFF, 0xC8);
    effectSpawnBoneDefault(arg0, arg1, arg2, arg3, arg4, arg5, arg6);
}

void effectSpawnBoneDefault(Actor *arg0, s16 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, s32 arg6) {
    func_807149B8(1);
    effectSpawnBone(arg0, arg1, arg2, arg3, arg4, arg5, arg6);
}

void effectSpawnBone(Actor *arg0, s16 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, s32 arg6) {
    Actor338 *temp;

    if (arg0 != NULL && arg1 != 0) {
        actorGetNodePos(arg0, arg1, &arg3, &arg4, &arg5);
    }
    func_8071498C(func_80718080);
    func_80714950(arg6);
    temp = func_80714CC0(&D_8071FFA0, arg2, arg3, arg4 + 5.0f, arg5);
    temp->unk338 = arg0;
}

void effectSpawnScatter(f32 arg0, f32 arg1, f32 arg2, f32 arg3) {
    s32 pad[2];
    s32 sp24;
    s32 mod100k;
    s32 mod10;
    if (((randomNonNegative() >> 15) % 100) >= 51) {
        func_80714998(2);
        func_80714950((randomNonNegative() >> 15) % 360);
        func_807149B8(1);
        func_807149C8(0x9B, 0x9B, 0x9B, 0xC8);
        func_8071498C(effectSpriteMotionUpdate);
        sp24 = randomNonNegative();
        mod100k = 100000;
        mod10 = 10;
        func_80714CC0(&D_8071FFA0, arg0, (f32)(((sp24 >> 15) % mod100k) % mod10) + (arg1 - 5.0f), arg2, (f32)(((randomNonNegative() >> 15) % mod100k) % mod10) + (arg3 - 5.0f));
    }
}
void func_807180F4(void);

void effectSpawnScatterRandom(void *arg0, u8 arg1, f32 arg2, u8 arg3, u8 arg4, s16 arg5, s16 arg6, s16 arg7, s16 arg8) {
    s16 var_s1;
    s8 dx;
    s8 dz;

    var_s1 = 0;
    if (arg3 > 0) {
        do {
            dx = ((randomNonNegative() >> 15) % 32767 % (arg4 * 2)) + (-arg4);
            dz = ((randomNonNegative() >> 15) % 32767 % (arg4 * 2)) + (-arg4);
            func_80714950(-arg5 - ((randomNonNegative() >> 15) % 80));
            func_8071498C(func_807180F4);
            func_807149B8(1);
            func_80714998(2);
            if (arg1) {
                func_8071496C((s16)arg1);
            }
            func_80714CC0(arg0, arg2, (f32)(arg6 + dx), (f32)arg7, (f32)(arg8 + dz));
            var_s1 = (s16)(var_s1 + 1);
        } while (var_s1 < arg3);
    }
}

void actorUpdateEffects(Actor *arg0) {
    if (!(arg0->unk64 & 4)) {
        if ((arg0->unk60 & 0x10) && ((arg0->unk6A ^ arg0->unk6C) & 4)) {
            effectSpawnDebrisParticles(arg0, 0.0f, arg0->unk7C, arg0->unkAC, arg0->unk84);
        }
        if (arg0->unk6A & 4) {
            effectActorCheckGroundScaleSpawn(arg0);
        }
    }
    if ((arg0->unk68 & 0x40) && func_80665AAC(arg0) && !(arg0->unk6A & 0x800) && (arg0->unkA4 <= arg0->unk80)) {
        actorSpawnAttachedTo(arg0);
    }
    if (arg0->unk68 & 0x80) {
        triggerZoneCheckEntry(arg0);
    }
}

void effectSpawnActorScale(Actor *arg0) {
    s32 pad;
    f32 sp28;

    sp28 = (arg0->unk4 != NULL) ? (f64)arg0->unk4->unk38 / 0.15 : 1.0;
    func_80714998(3);
    func_807149B8(1);
    func_807149FC(1);
    func_8071498C(effectGroundDecalSpinUpdate);
    func_80714A28(4);
    func_807149C8(0xC8, 0xFF, 0xFF, 0xC8);
    ((Actor338 *)func_80714CC0(&D_8071FED0, (f64) sp28 * 0.6, arg0->unk7C, arg0->unkAC, arg0->unk84))->unk338 = arg0;
}

typedef struct EffectPlayerData {
    u8 pad0[0x2C0];
    u8 unk2C0;
    u8 pad2C1[0x2F0 - 0x2C1];
} EffectPlayerData;

typedef struct ActorFloorContact {
    u8 pad0[0x10];
    s16 unk10;
} ActorFloorContact;

extern EffectPlayerData *gPlayerSlots;
extern u8 gCurrentPlayerIndex;
extern s16 D_80753A08[];
extern s16 D_80753A18[];

void effectActorCheckGroundScaleSpawn(Actor *arg0) {
    register f32 var_fv0;
    u8 var_v1;
    var_v1 = 0;
    if (*(void **)arg0->unk00 != NULL && arg0->unk4 != NULL) {
        if (arg0->unk5C == 1) {
            if (gPlayerSlots[gCurrentPlayerIndex].unk2C0 == 1) {
                var_fv0 = D_80753A08[arg0->unk58];
            } else {
                var_fv0 = D_80753A18[arg0->unk58];
            }
        } else {
            var_fv0 = (f32)(u32)arg0->unk15E;
        }
        if ((arg0->unkAC - var_fv0) <= arg0->unk80) {
            if (!(gFrameCounter & 3)) {
                var_v1 = (f64)arg0->unkB8 != 0.0;
                if (*(ActorFloorContact **)arg0->unk118 != NULL && (*(ActorFloorContact **)arg0->unk118)->unk10 != 0) {
                    var_v1 = 1;
                }
            }
            if (var_v1) {
                func_80714950(1);
            } else if (((f64)arg0->unkB8 == 0.0) && (((u32)gFrameCounter % 24 == 0) || ((f64)arg0->unkBC != 0.0))) {
                var_v1 = 1;
            }
            if (var_v1) {
                effectSpawnActorScale(arg0);
            }
        }
    }
}

void effectSpawnBurstParticles(Actor *arg0) {
    f32 var_fs0;
    f32 scale01;
    u8 count;
    u8 i;

    var_fs0 = (arg0->unk4 != NULL) ? (f64)arg0->unk4->unk38 / 0.15 : 1.0;
    if (arg0->unk58 == 0x1E) {
        var_fs0 *= 2;
        effectSpawnBoneDefault(arg0, 0, 4.0f, arg0->unk7C, arg0->unk80, arg0->unk84, -0x96);
        actorDespawn(arg0);
    }
    sfxPlayFromActorWithAltitudeCheck(arg0, 0xC, 0xFF, 0x7F, 1);
    func_807149B8(1);
    func_807149FC(1);
    func_807149C8(0xFF, 0xFF, 0xFF, 0xFF);
    func_80714CC0(&D_8071FC0C, (f64)var_fs0 * 0.65, arg0->unk7C, arg0->unkAC + 15.0f, arg0->unk84);
    if (D_80750AD0 == 0) {
        count = (randomLcgNext() & 3) + 4;
        i = 0;
        if (count > 0) {
            scale01 = (f64)var_fs0 * 0.1;
            do {
                func_807149B8(1);
                func_807149FC(-1);
                func_8071498C(effectFloorFallUpdate);
                func_80714A28(4);
                func_80714CC0(&D_80720B58, scale01, arg0->unk7C, arg0->unkAC, arg0->unk84);
                i++;
            } while (i < count);
        }
    }
}

void particleInitDefaultState(void) {
    func_807149B8(1);
    func_807149FC(0x14);
    func_8071498C(func_8071827C);
    func_807149C8(0xFF, 0xFF, 0xFF, 0xC8);
    func_80714A28(4);
}

extern s32 D_8071FBF4;

void effectSpawnDebrisParticles(Actor *arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4) {
    f32 f;
    f32 scale;

    if (arg0 != NULL) {
        scale = (arg0->unk4 != NULL) ? (f64)arg0->unk4->unk38 / 0.15 : 1.0;
        if (arg0->unk6A & 4) {
            f32 limit;

            if (arg0->unkC0 > -10.0f || (arg0->unk6A & arg0->unk6C & 1)) {
                f = 0.0f;
            } else {
                f = arg0->unkA0 - arg0->unk80;
            }
            limit = (arg0->unkAC - arg0->unkA4) * 2;
            f = (f < limit ? f : limit) < 0.0f ? 0.0f : (f < limit ? f : limit);

            if (arg0->unk58 == 0x29 || arg0->unk58 == 0x32) {
                sfxPlayFromActorWithAltitudeCheck(arg0, 0x2C7, 0xFF, 0x7F, 1);
            } else if (f < 10.0f) {
                sfxPlayFromActorWithAltitudeCheck(arg0, 0x10, (u8)((f64)f * 25.5), 0x7F, 1);
            } else if (f < 20.0f) {
                sfxPlayFromActorWithAltitudeCheck(arg0, 0xF, 0xFF, 0x7F, 1);
            } else {
                effectSpawnBurstParticles(arg0);
            }
        }
    } else {
        scale = arg1;
    }
    particleInitDefaultState();
    func_80714CC0(&D_8071FBF4, (f32)((f64)scale * 0.3), arg2, arg3, arg4);
    particleInitDefaultState();
    func_8071496C(2);
    func_80714CC0(&D_8071FBF4, (f32)((f64)scale * 0.05),
        (f32)((randomNonNegative() >> 15) % (u8)(30.0f * scale)) + arg2 - (f32)(u8)(15.0f * scale),
        arg3,
        (f32)((randomNonNegative() >> 15) % (u8)(30.0f * scale)) + arg4 - (f32)(u8)(15.0f * scale));
    particleInitDefaultState();
    func_8071496C(4);
    func_80714CC0(&D_8071FBF4, (f32)((f64)scale * 0.05),
        (f32)((randomNonNegative() >> 15) % (u8)(30.0f * scale)) + arg2 - (f32)(u8)(15.0f * scale),
        arg3,
        (f32)((randomNonNegative() >> 15) % (u8)(30.0f * scale)) + arg4 - (f32)(u8)(15.0f * scale));
}

void effectSpawnActorOrbitParticles(Actor *arg0) {
    s32 i;

    for (i = 0; i < 16; i++) {
        func_807149B8(1);
        func_807149FC(-1);
        func_80714950(arg0);
        func_8071498C(effectActorOrbitFollowUpdate);
        func_80714CC0((void *)D_8074E880[i % 3], 0.7f, arg0->unk7C, arg0->unk80, arg0->unk84);
    }
}

void effectSpawnRingBursts(Actor *arg0, f32 arg1, f32 arg2, s32 arg3) {
    s32 i;

    for (i = 0; i < 3; i++) {
        func_807149B8(1);
        func_807149FC(-1);
        func_80714950(arg0);
        func_8071498C(effectArcAroundActorUpdate);
        func_8071E110(func_80714CC0((void *)D_8074E880[i], 0.7f, arg0->unk7C, arg0->unk80, arg0->unk84), 1, (u16)(i * 1365.3334f), arg1, arg2, arg3);
    }
    for (i = 0; i != 3; i++) {
        func_807149B8(1);
        func_807149FC(-1);
        func_80714950(arg0);
        func_8071498C(effectArcAroundActorUpdate);
        func_8071E110(func_80714CC0((void *)D_8074E880[i], 0.7f, arg0->unk7C, arg0->unk80, arg0->unk84), 0, (u16)(i * 1365.3334f), arg1, arg2, arg3);
    }
}

void func_80686CF8(Actor *arg0) {
    s32 i;

    for (i = 0; i < 30; i++) {
        func_807149B8(1);
        func_807149FC(1);
        func_8071498C(effectBurstParticleUpdate);
        func_8071496C((s16)(i / 7));
        func_80714CC0((void *)D_8074E880[i % 3], 1.4f, arg0->unk7C, arg0->unk80 + 10.0f, arg0->unk84);
    }
}

void func_80686E40(f32 arg0, f32 arg1, f32 arg2, void *arg3) {
    s32 i;
    s32 var_s4;
    s32 var_s5;

    var_s5 = (D_80750AD0 != 0) ? 3 : 16;
    var_s4 = (D_80750AD0 != 0) ? 0 : 2;

    for (i = 0; i < var_s5; i++) {
        func_807149B8(1);
        func_807149FC(1);
        func_8071498C(func_80717930);
        func_8071496C((s16)(i >> var_s4));
        func_80714950(arg3);
        func_80714CC0((void *)D_8074E880[i % 3], 0.5f, arg0, arg1, arg2);
    }
}

void effectSpawnChildAtNode(u8 arg0, s16 arg1, s16 arg2) {
    u8 temp;

    actorSpawn(0x109, 0xC0);
    temp = arg0;
    if (temp) {
        actorGetNodePos(D_807FBB40, temp, &D_807FBB44->unk7C, &D_807FBB44->unk80, &D_807FBB44->unk84);
    } else {
        D_807FBB44->unk7C = D_807FBB40->unk7C;
        D_807FBB44->unk80 = D_807FBB40->unk80;
        D_807FBB44->unk84 = D_807FBB40->unk84;
    }
    D_807FBB44->unkE6 = arg1;
    D_807FBB44->unkE8 = arg2;
    D_807FBB44->unk4->unk38 = (f32)(D_807FBB44->unk4->unk38 * 0.01);
}

void effectActorGrowthTick(void) {
    if (!(D_807FBB40->unk60 & 0x10)) {
        D_807FBB40->unk60 &= ~0x8000;
        D_807FBB40->unk60 |= 0x800000;
        D_807FBB40->unk16A = 0xFF;
        D_807FBB40->unk16B = ((randomNonNegative() >> 15) % 75) + 0xB4;
        D_807FBB40->unk16C = 0x28;
        D_807FBB40->unk128 = 0xFF;
    }
    if ((f64)D_807FBB40->unk4->unk38 > 1.0) {
        D_807FBB40->unk128 -= 0x28;
        if (D_807FBB40->unk128 < 0) {
            actorDespawn(D_807FBB40);
        }
    } else {
        D_807FBB40->unk4->unk38 = (f32)(D_807FBB40->unk4->unk38 * 1.8);
        D_807FBB40->unk4->unk34 = (f32)(D_807FBB40->unk4->unk34 * 1.1);
        D_807FBB40->unk4->unk3C = (f32)(D_807FBB40->unk4->unk3C * 1.1);
    }
    actorUpdateModelMatrix(D_807FBB40, 0);
}

void effectSpawnActorBoneEffects(u8 arg0) {
    s32 var_s2;
    s16 var_s4;
    s32 var_v0;
    s32 var_s0;  // FAKE: separate post-dispatch web (chain var stays in v0, var_s0 takes s0)

    var_s2 = (((gFrameCounter & 3) * 4) + 3) & 0xFF;
    for (var_s4 = 0; var_s4 < 4; var_s4++) {
        var_v0 = var_s2;
        if ((var_s2 | 0) == 0x10) {  // FAKE: |0 keeps the constant-first operand order (bne s6,s2)
            var_v0 = 0x14;
        } else if ((var_v0 | 0) == 0x11) {  // FAKE: |0 blocks copy propagation so the compare reads the copy
            var_v0 = 0x15;
        } else {
            var_v0 = var_s2 & 0xFF;
        }

        switch (arg0 + 0U) {  // FAKE: +0U types the selector u32 (separate const-1 web) and keeps andi s3 hoisted
        case 3:
            if (var_v0 < 10) {
                break;
            }
            /* fallthrough */
        case 1:
            var_s0 = var_v0;
            func_80714998(1);
            func_807149C8(0xB4, 0xB4, 0xB4, 0xC8);
            effectSpawnBoneDefault(D_807FBB40, (var_s0 | 0), 2.0f, 0.0f, 0.0f, 0.0f, -0x78);  // FAKE: |0 blocks copy propagation
            break;

        case 2:
            if ((var_v0 * 1) < 10) {  // FAKE: *1 reorders the delay-slot copies in the dispatch block
                break;
            }
            /* fallthrough */
        case 0:
            var_s0 = (var_v0 * 1);  // FAKE: *1 reorders the delay-slot copies in the dispatch block
            func_807149B8(1);
            if (var_s0) {}  // FAKE: dead read steers uopt/as1 scheduling of the case-0 copy
            func_8071498C(func_80717D4C);
            func_80714950(-0x3E8);
            func_807149C8(0xFF, 0xD7, 0x58, 0xFF);
            func_80714C08(&D_80720120, (f32)(((f64)((randomNonNegative() >> 15) % 100) / 30.0) + 1.0), D_807FBB40, var_s0, 0);
            break;
        }
        var_s2 = (var_s2 + 1) & 0xFF;
    }
}

void func_80687400(void) {
    sfxPlayOnFreeSlot(0x2D4, 0x7FFF, 63.0f, 1.0f, 0, 0);
    func_807149FC(0xC8);
    func_8071495C();
    func_8071498C(func_8071EFDC);
    func_80714CC0(&D_80721158, 1.0f, 160.0f, 120.0f, -10.0f);
}

void actorSpawnAttachment(Actor *arg0, f32 arg1) {
    actorSpawn(0xB3, 0x5D);
    D_807FBB44->unk60 |= 0x400;
    actorScriptStart(D_807FBB44, 0x334);
    actorCopyPoseAndScale(D_807FBB44, arg0, arg0->unk4->unk38 * arg1);
}

f32 func_80612790(s16);
f32 func_80612794(s16);

void effectSpawnKongRing(void) {
    s32 var_a1;
    f32 sp98;
    f32 sp94;
    f32 sp90;
    f32 temp_fs4;
    f32 var_fs0;
    s16 var_s1;
    s32 i;

    var_s1 = (randomNonNegative() >> 15) % 4096;
    temp_fs4 = (f32)(D_807FBB40->unk4->unk38 * (20.0 / 3.0));
    switch (D_807FBB40->unk58) {
    case 2:
    case 5:
        var_a1 = 15;
        break;
    case 3:
    case 4:
    case 6:
        var_a1 = 13;
        break;
    default:
        return;
    }

    actorGetNodePos(D_807FBB40, var_a1, &sp98, &sp94, &sp90);
    for (i = 0; i < 64; i++) {
        var_s1 += (randomNonNegative() >> 15) % 1024;
        var_s1 &= 0xFFF;
        func_80714998(2);
        func_807149B8(1);
        func_8071498C(func_80717D4C);
        func_80714950((void *)(s32)((f32)((((randomNonNegative() >> 15) % 0x7FFF) % 51) + 100) * temp_fs4));
        func_8071496C((s16)(s32)((f32)i * (1.0f / 3.0f)));
        func_80714A28(0x20);
        var_fs0 = (func_80612794(var_s1) * (temp_fs4 * 18.0f)) + sp98;
        func_80714CC0((void *)D_8074E880[i % 3], temp_fs4 * 0.3f, var_fs0, sp94, (func_80612790(var_s1) * (temp_fs4 * 18.0f)) + sp90);
    }
}

void func_806877C8(arg0)
u8 arg0;
{
    func_807149B8(1);
    func_80714C08(&D_8072006C, 1.0f, D_807FBB40, arg0, 0);
}

void camProjectToScreen(f32, f32, f32, f32 *, f32 *, s32, f32, s32);
s32 mathAngleBetweenPoints2D(f32, f32, f32, f32);
void lightSetFlags(s32);
void lightAdd(f32, f32, f32, f32, f32, f32, f32, s32, s32, s32, s32);
void sfxPlayAtPositionPooled(f32, f32, f32, s32, s32, s32, s32, s32, f32, s32);
void func_8071E028(void);
extern s32 D_80720B24;

void effectSpawnJointBeam(arg0, arg1, arg2, arg3)
u8 arg0;
u8 arg1;
u8 arg2;
u8 arg3;
{
    f32 sp74;
    f32 sp70;
    f32 sp6C;
    f32 sp68;
    f32 sp64;
    f32 sp60;
    f32 sp5C;
    f32 sp58;
    f32 sp54;
    f32 sp50;
    f32 sp4C;
    f32 sp48;
    u8 sp44[4];

    sp44[1] = ((randomNonNegative() >> 15) % 0x7FFF) % ((arg1 - arg0) + 1) + arg0;
    sp44[0] = ((randomNonNegative() >> 15) % 0x7FFF) % ((arg3 - arg2) + 1) + arg2;
    actorGetNodePos(D_807FBB40, sp44[1], &sp74, &sp70, &sp6C);
    actorGetNodePos(D_807FBB40, sp44[0], &sp68, &sp64, &sp60);
    camProjectToScreen(sp74, sp70, sp6C, &sp58, &sp54, 0, 1.0f, 0);
    camProjectToScreen(sp68, sp64, sp60, &sp50, &sp4C, 0, 1.0f, 0);
    {
        f32 temp = (f32)(((s32)(mathAngleBetweenPoints2D(sp50, sp4C, sp58, sp54) * 360) / 4096) + 90);
        sp5C = temp;
        if (temp < 270.0f) {
            sp5C = temp + 180.0f;
        }
    }
    sp48 = sqrtf(((sp58 - sp50) * (sp58 - sp50)) + ((sp54 - sp4C) * (sp54 - sp4C)));
    func_807149B8(1);
    func_807149FC(1);
    func_80714950((s32)sp5C);
    func_8071498C(func_8071E028);
    func_80714CC0(&D_80720B24, (f32)((f64)sp48 * 0.008), (f32)((f64)(sp74 + sp68) * 0.5), (f32)((f64)(sp70 + sp64) * 0.5), (f32)((f64)(sp6C + sp60) * 0.5));
    if (((randomNonNegative() >> 15) % 1000) & 1) {
        lightSetFlags(1);
        lightAdd(D_807FBB40->unk7C, D_807FBB40->unk80, D_807FBB40->unk84, 0.0f, 0.0f, 0.0f, 150.0f, 0, 150, 100, 255);
    }
    if ((D_807FBB40->unk58 == 0xB9) && (((randomNonNegative() >> 15) % 1000) >= 0x385)) {
        func_806877C8((((randomNonNegative() >> 15) % 0x7FFF) % 10) + 13 & 0xFF);
        sfxPlayAtPositionPooled(D_807FBB40->unk7C, D_807FBB40->unk80, D_807FBB40->unk84, (((randomNonNegative() >> 15) % 1000) >= 501) ? 0x8A : 0xA1, 0xFF, 0x7F, 0x28, 0, 0.3f, 0);
    }
}

void func_80687C48(void) {
    sfxPlayOnFreeSlot(0xF2, 0x7FFF, 63.0f, 1.0f, 0, 0);
    sfxAllocateChannel(0x97, 1.0f);
    func_807149FC(0xC8);
    func_8071495C();
    func_8071498C(func_8071EFDC);
    func_80714CC0(&D_80720558, 1.0f, 160.0f, 120.0f, -10.0f);
}

void func_80687CC8(void) {
    sfxPlayOnFreeSlot(0xF2, 0x7FFF, 63.0f, 1.0f, 0, 0);
    sfxAllocateChannel(0x97, 1.0f);
    func_807149FC(0xC8);
    func_8071495C();
    func_8071498C(func_8071EFDC);
    func_80714CC0(&D_807210EC, 1.0f, 160.0f, 120.0f, -10.0f);
}
