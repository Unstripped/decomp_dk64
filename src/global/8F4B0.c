#include "common.h"
#include "actor.h"

s32 actorSpawn(s32, s32);
void func_8072E868(void);
void func_80727678(void);
void spawnNodesUpdate(void);

void actorSpawnInitialSet(void) {
    actorSpawn(0xA, 0);
    actorSpawn(0xB, 0);
    actorSpawn(0xC, 0);
    actorSpawn(0xD, 0);
    actorSpawn(0xE, 0);
    actorSpawn(0xF, 0);
}

void func_8068A810(void) {
    func_8072E868();
}

void func_8068A830(void) {
    func_80727678();
    spawnNodesUpdate();
}
#ifdef NON_MATCHING
typedef struct {
    /* 0x00 */ u8 unk0;
    /* 0x01 */ u8 unk1;
    /* 0x02 */ s16 unk2;
    /* 0x04 */ s16 unk4;
    /* 0x06 */ s16 unk6;
    /* 0x08 */ s16 unk8;
    /* 0x0A */ s16 unkA;
    /* 0x0C */ s16 unkC;
} KaN6_Entry0E;

extern s32 D_8076A064;
extern Actor *D_807FBB40;
extern u8 D_807FC621;
extern u8 D_807FC622;
extern u8 D_807501C0[][3];
extern KaN6_Entry0E D_80750194[];

f32 func_80612790(s16);
f32 func_80612794(s16);
void lightSetFovAngles(f32, f32);
void lightAdd(f32, f32, f32, f32, f32, f32, f32, s32, s32, s32, s32);

void func_8068A858(u8 *arg0, u8 *arg1, u8 *arg2) {
    f32 pad;
    f32 sp40;
    f32 sp3C;
    f32 sp38;
    u8 temp_v1;
    u8 idx;
    KaN6_Entry0E *entry;

    if (D_807FBB40->unk60 & 4) {
        switch (D_807FC622) {
        case 0:
            *arg0 = 0xFF;
            *arg1 = 0xFF;
            *arg2 = 0xFF;
            break;
        case 1:
            if (!(D_8076A064 & 0xF)) {
                goto set_color;
            }
            break;
        case 2:
            if (!(D_8076A064 & 3)) {
set_color:
                idx = (u32)(func_80612790(D_8076A064 * 200) * 4.0f + 4.0f);
                *arg0 = D_807501C0[idx][0];
                *arg1 = D_807501C0[idx][1];
                *arg2 = D_807501C0[idx][2];
            }
            break;
        }

        {
            u8 *ptr = &D_807FC621;
            if (D_80750194) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
            if ((*ptr & 0x80) && (temp_v1 = *ptr & 0x7F)) {
                entry = &D_80750194[temp_v1];
                if (D_807501C0 && D_807501C0) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
                sp40 = (f32)(entry - 1)->unk8;
                sp3C = (f32)(entry - 1)->unkA;
                sp38 = (f32)(entry - 1)->unkC;
                *ptr = temp_v1;
                if (D_807FC622 != 0) {
                    sp40 += 80.0f * func_80612794(D_8076A064 * 400);
                    sp38 += 80.0f * func_80612790(D_8076A064 * 200);
                    entry = &D_80750194[D_807FC621];
                }
                lightSetFovAngles((f32)(u32)(entry - 1)->unk0, (f32)(u32)(entry - 1)->unk1);
                entry = &D_80750194[D_807FC621];
                lightAdd((f32)(entry - 1)->unk2, (f32)(entry - 1)->unk4, (f32)(entry - 1)->unk6, sp40, sp3C, sp38, 0.0f, 1, *arg0, *arg1, *arg2);
            }
        }
    }
}
#else

#pragma GLOBAL_ASM("asm/global/nonmatchings/8F4B0/func_8068A858.s")
#endif

#pragma GLOBAL_ASM("asm/global/nonmatchings/8F4B0/func_8068ABE0.s")

typedef struct {
    /* 0x00 */ u8 unk0;
    /* 0x01 */ u8 unk1[3];
    /* 0x04 */ f32 unk4;
    /* 0x08 */ s16 unk8;
    /* 0x0A */ s16 unkA;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ f32 unk10;
    /* 0x14 */ f32 unk14;
    /* 0x18 */ u8 unk18;
    /* 0x19 */ u8 unk19;
    /* 0x1A */ s16 unk1A;
    /* 0x1C */ s16 unk1C;
    /* 0x1E */ s16 unk1E;
    /* 0x20 */ u8 unk20;
    /* 0x21 */ u8 unk21;
} KaL4_Actor174;
typedef struct {
    char pad[0x100];
    u32 unk100;
    char pad104[0x1F0 - 0x104];
    u32 unk1F0;
} KaL4_FD580;
typedef struct {
    char pad[0x1F0];
    u32 unk1F0;
} KaL4_Actor174_Player;
typedef struct {
    char pad[0x4];
    Actor *unk4;
} KaL4_FC924;
typedef struct {
    char pad[0xC4];
    f32 unkC4;
} KaL4_Actor_BB48;
struct ActorPlayerPos;

void lightGetColor(void *, void *, void *, s32);
void lightSetOverrideColor(f32, f32, f32);
void func_8070B308(s32);
void func_805FF158(s32);
s32 func_8068ABE0(s16);
void func_805FF378();
void func_806F3BEC(void *, s16, s16, s32);
void func_805FF4D8(s16, s16);
void func_805FF9AC(s16, s16, s16, s32);
void func_805FF628(s16, s16);
void func_806C92C4(s16);
void func_805FF898(void);
void func_805FF8F8(void);
void func_805FF660(u8);
s32 func_805FF030(u8, s32);
void func_80600044(s32);
void func_806F397C(void *, s32, s16, s32);
void sfxPlayFromActorWithAltitudeCheck(void *, s16, s32, s32, s32);
void sfxAllocateChannel(s16, f32);
void sfxStopChannel(s16, s32);
void commandSetColor(s32, s32, s32);
void commandSetParameters(s32, s32, s32, s32, s32, s32);
void mapChunkSetFlagBit3(s16);
void lightLerpColors(f32, f32, f32, f32, s16);
void lightSetTargetColor(f32, f32, f32, s16);
void func_80711BD0(f32, s16, s16, s32);
void func_80711950(f32, s16, s16);
void func_80711F90(f32, s16, f32, s16, f32);
s32 randomNonNegative(void);
void lightSetColor(f32, f32, f32, s16);
void func_80608DA8(s32, s32, s32, s32, s32);
void func_80711410(f32, s16, f32, s16, f32);
s32 func_807122B4(void);
void actorUpdateEntryEmitters(void);
void particleSpawnPathTrail(void);

extern Actor *D_807FBB40;
extern u8 D_807FBDC4;
extern ActorGlobalState D_807FBB70;
extern s16 D_807FDCBC;
extern s16 D_807FDCB8;
extern s32 D_807FBB60;
extern void *D_807FBB4C;
extern s32 D_8076A0A8;
extern KaL4_FD580 *D_807FD580;
extern struct ActorPlayerPos *D_807FC924;
extern u16 D_80744700[];
extern u8 D_8076A0AB;
extern s32 D_8076A0AC;
extern Actor *D_807FBB48;
extern u8 D_807FC621;
extern u8 D_807FC622;
extern u16 D_807ECD48;
extern u16 D_8076A0A6;
extern u8 D_80750190;
extern u8 D_807FC620;

void func_8068AD7C(void) {
    KaL4_Actor174 *temp_s1;
    s32 i;
    f32 pad;
    s16 *temp_s0;
    s32 var_s0;
    s32 var_v0;
    s16 temp_a0;
    s16 temp_v0_2;

    temp_s1 = (KaL4_Actor174 *)D_807FBB40->unk174;
    if (!(D_807FBB40->unk60 & 0x10)) {
        temp_s1->unk0 = 0;
        temp_s1->unk1A = -1;
        temp_s1->unk21 = 0;
        lightGetColor(&temp_s1->unkC, &temp_s1->unk10, &temp_s1->unk14, 0);
    }

    for (i = 0; i < D_807FBDC4; i++) {
        temp_s0 = D_807FBB70.unk278[i];
        switch (D_807FBB70.unk258[i]) {
        case 0xFF:
            temp_s1->unk1E = 0;
            temp_s1->unk0 = 0xFF;
            break;
        case 0xF:
            lightSetOverrideColor((f64)temp_s0[0] / 255.0, (f64)temp_s0[1] / 255.0, (f64)temp_s0[2] / 255.0);
            break;
        case 0xE:
            temp_s1->unkC = (f64)temp_s0[0] / 255.0;
            temp_s1->unk10 = (f64)temp_s0[1] / 255.0;
            temp_s1->unk14 = (f64)temp_s0[2] / 255.0;
            temp_s1->unk1A = temp_s0[3];
            break;
        case 0x10:
            temp_s1->unk1C = temp_s0[3];
            temp_s1->unk1E = temp_s1->unk1C;
            break;
        case 0x1:
            if ((D_8076A0A8 != 0x30) || !(D_807FD580->unk1F0 & 0x200000)) {
                temp_s1->unk0 = temp_s0[0];
                temp_s1->unk1A = temp_s0[1];
                temp_s1->unk4 = (f64)(f32)temp_s0[2] / 100.0;
                temp_s1->unk8 = temp_s0[3];
            }
            break;
        case 0x2:
            if ((D_8076A0A8 != 0x30) || !(D_807FD580->unk1F0 & 0x200000)) {
                temp_s1->unk0 = 0xFF;
            }
            break;
        case 0x3:
            if (!(D_807FBB60 & 0x400)) {
                if (temp_s0[2] != 0) {
                    func_8070B308(2);
                    func_805FF158(0);
                }
                temp_a0 = temp_s0[0];
                if (temp_a0 == 0x11) {
                    if (func_8068ABE0(temp_a0) == 0) {
                        func_805FF378(temp_s0[0], temp_s0[1]);
                    }
                } else {
                    func_805FF378(temp_a0, temp_s0[1]);
                }
                func_806F3BEC(D_807FBB4C, D_807FDCB8, D_807FDCBC, 0x46);
            }
            break;
        case 0x15:
            if (!(D_807FBB60 & 0x400)) {
                func_805FF4D8(temp_s0[0], temp_s0[1]);
            }
            break;
        case 0x4:
            if (!(D_807FBB60 & 0x400)) {
                temp_v0_2 = temp_s0[2];
                if (temp_v0_2 != 0) {
                    if (temp_v0_2 == 1) {
                        func_8070B308(2);
                    }
                    func_805FF158(0);
                }
                func_805FF9AC(temp_s0[0], temp_s0[1], 0, 0);
                func_806F3BEC(D_807FBB4C, D_807FDCB8, D_807FDCBC, 0x46);
            }
            break;
        case 0x5:
            if (!(D_807FBB60 & 0x400)) {
                func_805FF628(temp_s0[0], temp_s0[1]);
                func_806F3BEC(D_807FBB4C, D_807FDCB8, D_807FDCBC, 0x46);
            }
            break;
        case 0x6:
            D_807FD580->unk100 = 1;
            func_806C92C4(temp_s0[0]);
            break;
        case 0x7:
            if (!(D_807FBB60 & 0x400)) {
                func_805FF9AC(temp_s0[0], temp_s0[1], temp_s0[2], 2);
                func_806F3BEC(D_807FBB4C, D_807FDCB8, D_807FDCBC, 0x46);
            }
            break;
        case 0x8:
            if (!(D_807FBB60 & 0x400)) {
                func_805FF898();
                func_806F3BEC(D_807FBB4C, D_807FDCB8, D_807FDCBC, 0x46);
            }
            break;
        case 0x19:
            func_805FF8F8();
            break;
        case 0x9:
            func_805FF660(((u8 *)temp_s0)[1]);
            break;
        case 0xA:
            ((KaL4_Actor174_Player *)((KaL4_FC924 *)D_807FC924)->unk4->unk174)->unk1F0 |= 0x40000800;
            break;
        case 0xB:
            func_805FF378(D_80744700[func_805FF030(D_8076A0AB, 0)], D_8076A0AC);
            func_806F3BEC(D_807FBB4C, D_807FDCB8, D_807FDCBC, 0x46);
            break;
        case 0xC:
            if (temp_s0[1] != 0) {
                var_v0 = 0;
            } else {
                var_v0 = 0x8000;
            }
            func_806F397C(D_807FBB4C, 0, temp_s0[0] + var_v0, 0);
            break;
        case 0xD:
            if (((Actor *)D_807FBB4C)->unkB8 > 250.0f) {
                sfxPlayFromActorWithAltitudeCheck(D_807FBB4C, temp_s0[0], 0xFF, 0x7F, 0x1E);
            }
            break;
        case 0x16:
            sfxAllocateChannel(temp_s0[0], 1.0f);
            break;
        case 0x17:
            sfxStopChannel(temp_s0[0], 0);
            break;
        case 0x11:
            ((KaL4_Actor_BB48 *)D_807FBB48)->unkC4 = (f64)temp_s0[0] / 10.0;
            break;
        case 0x12:
            D_807FBB48->unk6A |= 0x200;
            break;
        case 0x13:
            D_807FBB48->unk6A &= ~0x200;
            break;
        case 0x14:
            D_807FC621 = temp_s0[0];
            D_807FC622 = temp_s0[1];
            if (D_807FC622 != 0) {
                commandSetColor(0x35, 0x18, 0x28);
                commandSetParameters(0x320, 0x82, 0, 0x64, 0x64, 0x64);
            }
            break;
        case 0x18:
            func_80600044(func_805FF030(D_8076A0AB, 0));
            break;
        case 0x1C:
            if (D_80744700 == 0) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
            D_8076A0A6 = D_807ECD48;
            break;
        case 0x1A:
            ((KaL4_Actor174_Player *)((KaL4_FC924 *)D_807FC924)->unk4->unk174)->unk1F0 |= 0x80000000;
            break;
        case 0x1B:
            mapChunkSetFlagBit3(temp_s0[1]);
            break;
        }
    }

    if (temp_s1->unk1E != 0) {
        temp_s1->unk1E--;
        pad = (f32)temp_s1->unk1E / (f32)temp_s1->unk1C;
        lightLerpColors(temp_s1->unkC, temp_s1->unk10, temp_s1->unk14, pad, temp_s1->unk1A);
        if (temp_s1->unk1E == 0) {
            lightSetTargetColor(temp_s1->unkC, temp_s1->unk10, temp_s1->unk14, temp_s1->unk1A);
        }
    }

    switch (temp_s1->unk0) {
    case 0x6:
        func_80711BD0(temp_s1->unk4, temp_s1->unk8, temp_s1->unk1A, 4);
        break;
    case 0x7:
        func_80711BD0(temp_s1->unk4, temp_s1->unk8, temp_s1->unk1A, 5);
        break;
    case 0x5:
        func_80711BD0(temp_s1->unk4, temp_s1->unk8, temp_s1->unk1A, 3);
        break;
    case 0x1:
        func_80711950(temp_s1->unk4, temp_s1->unk8, temp_s1->unk1A);
        break;
    case 0x4:
        func_80711F90(temp_s1->unk4, temp_s1->unk8, 1.0f, temp_s1->unk1A, 4.0f);
        break;
    case 0x3:
        if (((randomNonNegative() >> 15) % 50) == 15) {
            D_807FC620 = 1;
        }
        /* fallthrough */
    case 0x2:
        if (temp_s1->unk21 != 0) {
            temp_s1->unk21--;
        }
        if (D_807FC620 != 0) {
            temp_s1->unk18 = 0x28;
            D_807FC620 = 0;
        }
        if (temp_s1->unk18 != 0) {
            if ((temp_s1->unk18 == 0x28) || (((randomNonNegative() >> 15) % 10) == 5)) {
                lightSetColor(1.0f, 1.0f, 1.0f, temp_s1->unk1A);
                if ((D_80750190 == 0) && (temp_s1->unk21 == 0)) {
                    var_s0 = 0x46;
                    if (D_8076A0A8 == 0x57) {
                        var_s0 = 0x2D;
                    }
                    func_80608DA8(0x9C, (u8)var_s0, 0x7F, 0x1E, (randomNonNegative() >> 15) % 3);
                    if (D_8076A0A8 == 0x6F) {
                        temp_s1->unk21 = 0x50;
                    } else {
                        temp_s1->unk21 = 0x32;
                    }
                }
                temp_s1->unk1E = (temp_s1->unk1E >= 5) ? temp_s1->unk1E : 4;
                temp_s1->unk1C = temp_s1->unk1E;
            }
            temp_s1->unk18--;
        }
        func_80711410(temp_s1->unk4, temp_s1->unk8, 1.0f, temp_s1->unk1A, 1.0f);
        break;
    case 0xFF:
        if (func_807122B4() != 0) {
            temp_s1->unk0 = 0;
        }
        break;
    }

    actorUpdateEntryEmitters();
    particleSpawnPathTrail();
    D_807FC621 |= 0x80;
}


void func_8068B80C(void) {
    D_807FC620 = 1;
}

void func_8068B81C(void) {
    D_807FC621 = 0;
    D_807FC622 = 0;
}
typedef struct {
    /* 0x00 */ u8 unk0;
    /* 0x01 */ u8 unk1[3];
    /* 0x04 */ f32 unk4;
    /* 0x08 */ s16 unk8;
    /* 0x0A */ s16 unkA;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ f32 unk10;
    /* 0x14 */ f32 unk14;
    /* 0x18 */ u8 unk18;
    /* 0x19 */ u8 unk19[3];
    /* 0x1C */ s16 unk1C;
    /* 0x1E */ s16 unk1E;
} Actor174;

void actorFindActiveByType(s32, void *);

void func_8068B830(s16 arg0, s16 arg1, s16 arg2) {
    Actor *sp1C;
    Actor174 *temp_v0;

    actorFindActiveByType(0xC, &sp1C);
    temp_v0 = (Actor174 *)sp1C->unk174;
    temp_v0->unk0 = arg0;
    temp_v0->unk4 = (f64)(f32)arg1 / 100.0;
    temp_v0->unk8 = arg2;
}

void func_8068B8A4(f32 arg0) {
    Actor *sp1C;
    Actor174 *temp_v0;

    actorFindActiveByType(0xC, &sp1C);
    temp_v0 = (Actor174 *)sp1C->unk174;
    temp_v0->unkC = arg0;
    temp_v0->unk10 = arg0;
    temp_v0->unk14 = arg0;
    if (temp_v0->unk18 == 0) {
        temp_v0->unk1C = 1;
        temp_v0->unk1E = temp_v0->unk1C;
    }
}

void func_8068B8FC(void) {
    Actor *sp1C;
    u8 *ptr;

    actorFindActiveByType(0xC, &sp1C);
    ptr = sp1C->unk174;
    *ptr = 0xFF;
}

void csModelStateSetFirstByte(s16, s16);
void func_8062BAE4(void);
void actorListDispatchEvent(s16, void *);

void func_8068B930(void) {
    s32 i;
    s16 *ptr;

    for (i = 0; i < D_807FBDC4; i++) {
        ptr = D_807FBB70.unk278[i];
        if (D_807FBB70.unk258[i] == 1) {
            csModelStateSetFirstByte(ptr[0], ptr[1]);
        }
    }
    func_8062BAE4();
}

void func_8068B9B4(void) {
    s32 i;
    s16 *ptr;

    for (i = 0; i < D_807FBDC4; i++) {
        ptr = D_807FBB70.unk278[i];
        if (D_807FBB70.unk258[i] == 1) {
            actorListDispatchEvent(ptr[1], ptr);
        }
    }
}

typedef struct {
    char pad[0xAC];
    u32 unkAC;
} ActorSub174;

typedef struct {
    char pad[0x104];
    Actor *unk104;
    char pad108[0x1F0 - 0x108];
    u32 unk1F0;
} Actor174Player;

typedef struct ActorPlayerPos {
    char pad[0x210];
    f32 unk210;
    f32 unk214;
    f32 unk218;
    char pad21C[0xC];
    f32 unk228;
    f32 unk22C;
    f32 unk230;
} ActorPlayerPos;

extern ActorPlayerPos *D_807FC924;
void camStartPath(s32, s32, u8);
void func_8072167C(s16, s16, s16, s16);
void lightAdd(f32, f32, f32, f32, f32, f32, f32, s32, s32, s32, s32);

void func_8068BA2C(void) {
    s32 pad;
    ActorSub174 *sp58;
    Actor174Player *s1;
    s32 var_s3;
    s16 i;
    s16 *ptr;
    s32 var_v0;

    s1 = D_807FBB48->unk174;
    var_s3 = 0;
    sp58 = ((Actor *)s1->unk104)->unk174;
    for (i = 0; i < D_807FBB70.unk254; i++) {
        ptr = D_807FBB70.unk278[i];
        switch ((u32)D_807FBB70.unk258[i]) {
        case 1:
            var_v0 = (ptr[1] != 0) ? 4 : 0;
            camStartPath(0, ptr[0], var_v0 | 1);
            break;
        case 2:
            func_8072167C(ptr[0], ptr[1], ptr[2], ptr[3]);
            break;
        case 3:
            var_s3 = 1;
            if (!(s1->unk1F0 & 0x04000000)) {
                s1->unk1F0 |= 0x04000000;
            }
            break;
        }
    }
    if (var_s3 == 0) {
        s1->unk1F0 &= ~0x04000000;
    }
    if (sp58->unkAC & 1) {
        lightAdd(D_807FC924->unk210, D_807FC924->unk214, D_807FC924->unk218, D_807FC924->unk228, D_807FC924->unk22C, D_807FC924->unk230, 0.0f, 1, 0xFF, 0xFF, 0xFF);
    }
}

#ifdef NON_MATCHING
typedef struct {
    char pad[0xE4];
    s16 unkE4;
    s16 unkE6;
    char padE8[0x4];
    s16 unkEC;
} KaN6_ActorE4;

void func_80609140(s32, s32, f32, f32, s32, s32);
f32 func_80612794(s16);
void camUpdate(void *, void *, void *, void *, void *, void *, void *, void *, void *, void *);
s16 mathAngleBetweenPoints2D(f32, f32, f32, f32);
f32 mathAngleBetweenPointsRad(f32, f32, f32, f32);
void func_806C9D20(u8);
extern u8 D_807444EC;
extern s16 D_807FC624;

void func_8068BBF8(void) {
    void *sp54;
    s16 sp52;
    s16 pad50[1];
    s16 sp4E;
    f32 sp48;
    f32 pad44[1];
    f32 sp40;
    f32 sp3C;
    s16 sp3A;
    void *sp34;
    s32 pad30[1];
    f32 temp_fa0;
    f32 temp_fa1;
    f32 temp_fv0;
    f32 temp_fv1;
    f32 var_fv1;
    Actor *temp_a0_2;
    s16 temp_v0;
    s32 temp_v0_2;
    s16 temp_v1_3;
    s32 var_v1;
    u8 temp_v1_2;
    sp54 = D_807FBB40->unk174;
    sp4E = 0;
    sp3A = 0x1E;
    sp40 = 0.08f;
    sp3C = 8.0f;
    sp34 = (void *)((*(u8 *)((u8 *)sp54 + 0xFB) * 0x2F0) + (u8 *)D_807FC924);
    *(s16 *)((u8 *)sp34 + 0x2CC) = ((KaN6_ActorE4 *)D_807FBB40)->unkEC;
    ((KaN6_ActorE4 *)D_807FBB40)->unkEC = ((KaN6_ActorE4 *)D_807FBB40)->unkE4;
    *(s16 *)((u8 *)sp34 + 0x2CA) = (s16)(s32)*(f32 *)((u8 *)sp34 + 0x214);
    sp48 = mathAngleBetweenPointsRad(*(f32 *)((u8 *)sp34 + 0x218), *(f32 *)((u8 *)sp34 + 0x210), *(f32 *)((u8 *)sp34 + 0x230), *(f32 *)((u8 *)sp34 + 0x228));
    temp_fv1 = *(f32 *)((u8 *)sp34 + 0x230) - *(f32 *)((u8 *)sp34 + 0x218);
    temp_fa1 = *(f32 *)((u8 *)sp34 + 0x228) - *(f32 *)((u8 *)sp34 + 0x210);
    temp_fa0 = mathAngleBetweenPointsRad(0.0f, *(f32 *)((u8 *)sp34 + 0x214), sqrtf((temp_fv1 * temp_fv1) + (temp_fa1 * temp_fa1)), *(f32 *)((u8 *)sp34 + 0x22C)) + 3.1415927f;
    var_fv1 = temp_fa0;
    if (temp_fa0 > 6.2831855f) {
        var_fv1 = temp_fa0 - 6.2831855f;
    }
    if (var_fv1 > 3.1415927f) {
        var_fv1 = 3.1415927f - (var_fv1 - 3.1415927f);
    }
    *(f32 *)((u8 *)sp34 + 0x2D4) = 6.2831855f - sp48;
    *(f32 *)((u8 *)sp34 + 0x2D8) = 6.2831855f - var_fv1;
    func_806C9D20(*(u8 *)((u8 *)sp54 + 0xFB));
    sp52 = mathAngleBetweenPoints2D(*(f32 *)((u8 *)sp34 + 0x210), *(f32 *)((u8 *)sp34 + 0x218), *(f32 *)((u8 *)sp34 + 0x228), *(f32 *)((u8 *)sp34 + 0x230));
    camUpdate(D_807FBB40, (u8 *)sp34 + 0x210, (u8 *)sp34 + 0x214, (u8 *)sp34 + 0x218, (u8 *)sp34 + 0x228, (u8 *)sp34 + 0x22C, (u8 *)sp34 + 0x230, (u8 *)sp34 + 0x240, (u8 *)sp34 + 0x244, (u8 *)sp34 + 0x248);
    temp_v0 = mathAngleBetweenPoints2D(*(f32 *)((u8 *)sp34 + 0x210), *(f32 *)((u8 *)sp34 + 0x218), *(f32 *)((u8 *)sp34 + 0x228), *(f32 *)((u8 *)sp34 + 0x230));
    temp_a0_2 = *(Actor **)sp54;
    if (D_807FBB4C != temp_a0_2) {
        return;
    }
    if ((D_8076A0A8 == 0x1F) || (D_8076A0A8 == 0x33)) {
        if (D_807FC624 && D_807FC624) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
        ((KaN6_ActorE4 *)D_807FBB40)->unkE4 = (s16)(s32)(func_80612794(D_807FC624) * 100.0f);
        if (D_8076A0A8 == 0x1F) {
            if (D_807FC624 < 0x1E) {
                func_80609140(0x15, 0x7FFF, 64.0f, 1.0f, 10, 128);
            }
            if ((D_807FC624 >= 0x800) && (D_807FC624 < 0x81E)) {
                func_80609140(0x14, 0x7FFF, 64.0f, 1.0f, 10, 128);
            }
        }
        if (D_807444EC && D_807444EC) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
        D_807FC624 = (D_807FC624 + 0x1E) & 0xFFF;
        return;
    }
    if (D_807444EC != 1) {
            temp_v1_2 = temp_a0_2->unk154;
            if (D_8076A0A8 && D_8076A0A8) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
            switch ((s32)temp_v1_2) {
            case 0x63:
                sp40 = 0.02f;
                sp3C = 15.0f;
                goto calc_angle;
            case 0x7:
            case 0x8:
            case 0x9:
            case 0xA:
            case 0xB:
            case 0xF:
            case 0x10:
            case 0x11:
            case 0x12:
            case 0x13:
            case 0x14:
                sp3A = 0x64;
                sp40 = 0.1f;
            case 0x4F:
            case 0x69:
            case 0x6D:
calc_angle:
                temp_v1_3 = sp52 - temp_v0;
                if (temp_v1_3 >= 0x801) {
                    sp4E = temp_v1_3 - 0x1000;
                } else if (temp_v1_3 < -0x800) {
                    sp4E = temp_v1_3 + 0x1000;
                } else {
                    sp4E = temp_v1_3;
                }
                break;
            }
            temp_v0_2 = -sp3A;
            var_v1 = (temp_v0_2 < sp4E) ? sp4E : temp_v0_2;
            var_v1 = (var_v1 < sp3A) ? ((temp_v0_2 < sp4E) ? sp4E : temp_v0_2) : sp3A;
            temp_fv0 = (f32)((KaN6_ActorE4 *)D_807FBB40)->unkE4;
            ((KaN6_ActorE4 *)D_807FBB40)->unkE4 = (s16)(s32)(((((f32)var_v1 * sp3C) - temp_fv0) * sp40) + temp_fv0);
    }
}
#else

#pragma GLOBAL_ASM("asm/global/nonmatchings/8F4B0/func_8068BBF8.s")
#endif
