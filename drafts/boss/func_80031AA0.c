// func_80031AA0 (src/boss/C920.c): stage 4: compiles, parked NON_MATCHING in src. 1050 insns expected vs ~1062; frame 128 and slots i@0x70, flags 0x67-0x6B, sp5C@0x5C, j@0x52 match only with 3 unused s32 before 'i' and 2 before 'j' (original has 5 more 4-byte named locals; temps land 0x40/0x44 not 0x44/0x48). Remaining diffs: scheduling in spawn loop (0.1f lwc1 + D_807FBB44 addr hoisted after the call in expected; unk174 ptr as named local st), 1.0f/62.0f f32 args to func_80609140 get CSE'd into $f2 (expected plain lui a3; int-literal args fix that but conflicts with the f32 prototype at C920.c:195), actorSpawn is 2-arg (a2/a3 are leftover regs), lightAdd(x,400.0f,z,x,300.0f,z,200.0f,0,c,c,c). Switch2 case 1 uses nested switch(unk12){2,3,default} for the cmp chain.
#include "common.h"

struct BossD_Actor;
extern struct BossD_Actor *D_807FBB40;
extern struct BossD_Actor *D_807FBB4C;
f32 func_80612794(s16);
s32 camIsCutsceneActive(void);

typedef struct BsA2_Sub4 {
    u8 pad0[0x34];
    f32 unk34;
    f32 unk38;
    f32 unk3C;
} BsA2_Sub4;

typedef struct BsA2_SpawnState {
    void *unk0;
    s8 unk4;
    s8 unk5;
} BsA2_SpawnState;

typedef struct BsA2_State {
    f32 unk0;
    f32 unk4;
    f32 unk8;
    s16 unkC;
    s16 unkE;
    s16 unk10;
    s8 unk12;
    s8 unk13;
    s8 unk14;
    s8 unk15;
    s8 unk16;
    s8 unk17;
} BsA2_State;

typedef struct BsA2_Actor {
    u8 pad0[4];
    BsA2_Sub4 *unk4;
    u8 pad8[0x60 - 8];
    s32 unk60;
    u8 pad64[0x7C - 0x64];
    f32 unk7C;
    f32 unk80;
    f32 unk84;
    u8 pad88[0xA4 - 0x88];
    u8 unkA4;
    u8 padA5[0xE6 - 0xA5];
    s16 unkE6;
    u8 padE8[0x128 - 0xE8];
    s16 unk128;
    s16 unk12A;
    u8 pad12C[0x144 - 0x12C];
    u8 unk144;
    u8 pad145;
    s16 unk146;
    u8 pad148[0x154 - 0x148];
    u8 unk154;
    u8 unk155;
    u8 pad156[0x174 - 0x156];
    BsA2_State *unk174;
} BsA2_Actor;

typedef struct BsA2_Spawn {
    u8 pad0[4];
    BsA2_Sub4 *unk4;
    u8 pad8[0x60 - 8];
    s32 unk60;
    u8 pad64[0x80 - 0x64];
    f32 unk80;
    u8 pad84[0x174 - 0x84];
    BsA2_SpawnState *unk174;
} BsA2_Spawn;

extern BsA2_Spawn *D_807FBB44;
extern u8 D_807FBDC4;
extern s16 D_80035B00[];
extern s16 D_80035B08[];
extern s8 D_80035B28;
extern s16 D_80035B2C;
extern s8 D_80035B30[];
extern s8 D_80035B34;
extern u8 D_80035B38;
extern f32 D_80035B3C;
extern s8 D_80035B40;
extern s8 D_80035B44[];
extern s16 D_80035B4C[];
extern u8 D_80035B58[];
extern s16 D_80035B60[];
extern s8 D_80035B68;
extern s8 D_80035B6C;
extern s16 D_80035B70;
extern s8 D_80036DC0;
extern f32 D_80036DC4;

s32 actorSpawn(s32, s32);
void *actorListFindActorById(s16);
void actorDespawn(void *);
s32 camStartPath(void *, s32, s32);
void func_805FF378(s32, s32);
void collisionCheckActorFloor(void *, f32, f32, f32, void *);
void func_8068A764(void *, u8);
void func_806C8E58(s16);
void func_806F09F0(void *, u16);
void func_8067AAB8(void *, void *, s32, f32, s32);
void func_80609140(s32, s32, f32, f32, s32, s32);
void camPausePath(void);
void camResumePath(void);
void func_80724994(s32, s32, s32, s32, s32);
s32 func_806119A0(void);
f32 func_806119FC(void);
void sfxAllocateChannel(s32, f32);
void bossSpawnParticleRing(s32, s16, s16, s16, s32, s32);
void lightAdd(f32, f32, f32, f32, f32, f32, f32, s32, s32, s32, s32);
void lightSetColor(f32, f32, f32, s32);
void func_8068B80C(void);
void actorUpdateModelMatrix(void *, s32);

#define BsA2_A ((BsA2_Actor *)D_807FBB40)
#define BsA2_P ((BsA2_Actor *)D_807FBB4C)

void func_80031AA0(void) {
    s32 padA0;
    s32 padA1;
    s32 padA2;
    s32 i;
    BsA2_State *s;
    s8 sp6B;
    s8 sp6A;
    s8 sp69;
    s8 sp68;
    s8 sp67;
    BsA2_SpawnState *st;
    s32 sp5C;
    s32 padY0;
    s32 padY1;
    s16 j;

    s = BsA2_A->unk174;
    sp67 = 0;
    sp68 = 0;
    sp6A = 0;
    if (!(BsA2_A->unk60 & 0x10)) {
        D_80035B28 = 0xF;
        D_80035B34 = 0;
        D_80035B3C = 0.0f;
        s->unkC = 0x1E;
        s->unkE = 1;
        s->unk14 = 0;
        s->unk0 = BsA2_A->unk80;
        D_80035B6C = 0;
        s->unk12 = 0;
        D_80035B70 = 5;
        for (i = 0; i != 8; i++) {
            if (actorSpawn(0xA6, D_80035B60[i >> 1]) != 0) {
                st = D_807FBB44->unk174;
                st->unk0 = BsA2_A;
                st->unk4 = i >> 1;
                st->unk5 = i & 1;
                D_807FBB44->unk80 = BsA2_A->unk80 + 50.0f;
                D_807FBB44->unk4->unk34 = 0.1f;
                D_807FBB44->unk4->unk38 = 0.1f;
                D_807FBB44->unk4->unk3C = 0.1f;
                D_807FBB44->unk60 |= 0x400;
            }
        }
        D_80036DC4 = 160000.0f;
        D_80036DC0 = 0;
        if (D_807FBB4C != NULL) {
            BsA2_P->unk154 = 0x77;
            BsA2_P->unk155 = 0;
        }
        BsA2_A->unk12A = 0x7D0;
        collisionCheckActorFloor(BsA2_A, BsA2_A->unk7C, BsA2_A->unk80, BsA2_A->unk84, &BsA2_A->unkA4);
        BsA2_A->unk154 = 2;
        camStartPath(0, 3, 1);
    }
    switch (BsA2_A->unk154) {
    case 0:
        BsA2_P->unk7C = BsA2_A->unk7C;
        BsA2_P->unk80 = BsA2_A->unk80;
        BsA2_P->unk84 = BsA2_A->unk84;
        if (D_80035B38 == 0xFF) {
            D_80035B38 = BsA2_P->unk144;
        }
        BsA2_P->unk60 &= ~4;
        BsA2_P->unk144 = 1;
        if (D_807FBDC4 != 0) {
            sp5C = D_80035B44[D_80036DC0];
            BsA2_A->unk146 = 0;
            for (i = 4; D_80036DC0 < i; i--) {
                func_8068A764(D_807FBB40, D_80035B58[D_80035B44[i]]);
            }
            D_80036DC0++;
            sp5C = D_80035B4C[sp5C];
            func_806C8E58(sp5C);
            func_806F09F0(D_807FBB4C, sp5C);
            BsA2_P->unk154 = 0xC;
            BsA2_P->unk155 = 0;
            func_8067AAB8(D_807FBB40, D_807FBB4C, 0, 180.0f, 0x46);
            BsA2_A->unk154 = 1;
            BsA2_P->unk144 = D_80035B38;
        }
        break;
    case 1:
        BsA2_P->unk60 |= 4;
        if (BsA2_P->unk7C - BsA2_A->unk7C > 700.0 || BsA2_P->unk7C - BsA2_A->unk7C < -700.0 ||
            BsA2_P->unk84 - BsA2_A->unk84 > 700.0 || BsA2_P->unk84 - BsA2_A->unk84 < -700.0) {
            if (D_80036DC0 < 5) {
                BsA2_A->unk154 = 0;
                camStartPath(0, 2, 1);
            } else {
                func_805FF378(0x2A, 2);
                BsA2_A->unk154 = 3;
            }
        }
        break;
    case 2:
        s->unkE--;
        if (s->unkE < 0) {
            BsA2_A->unk154 = 0;
            func_806C8E58(4);
            func_806F09F0(D_807FBB4C, 4);
            s->unk13 = 1;
        }
        break;
    case 3:
        break;
    }
    BsA2_A->unkE6 += 0x32;
    BsA2_A->unkE6 &= 0xFFF;
    BsA2_A->unk80 = func_80612794(BsA2_A->unkE6) * 5.0 + s->unk0;
    if (BsA2_P->unk154 == 0x45 && BsA2_P->unk155 >= 2 && D_80036DC4 < 10000.0) {
        sp6A = 1;
    }
    sp69 = 0;
    s->unk4 += s->unk8;
    if (s->unk4 > 1.0f) {
        s->unk4 = 1.0f;
        sp69 = 1;
    }
    if (s->unk4 < 0.0f) {
        s->unk4 = 0.0f;
        sp69 = -1;
    }
    if (sp69 != 0 && camIsCutsceneActive() == 0) {
        s->unk10++;
    }
    s->unk17 = 0;
    sp6B = s->unk13;
    switch (sp6B) {
    case 0:
        i = 5;
        if (s->unk12 == 2) {
            j = 0xC;
            s->unk8 = -0.2f;
        } else {
            i = 0x3C;
            j = 4;
            s->unk8 = -0.1f;
        }
        if (i < s->unk10) {
            s->unk15++;
            if (s->unk15 < j) {
                s->unk13 = 1;
                func_80609140(0x37D, 0x7D00, 62.0f, 1.0f, 0, 0);
                if (s->unk12 == 2) {
                    func_80609140(0x381, 0x7D00, 62.0f, 1.0f, 0, 0);
                } else {
                    func_80609140(0x37F, 0x7D00, 62.0f, 1.0f, 0, 0);
                }
            } else {
                s->unk13 = 2;
                s->unk15 = 0;
            }
        }
        if (sp69 != 0 && D_80035B40 == 0) {
            sp68 = 1;
            D_80035B2C = 0;
        }
        break;
    case 1:
        switch (s->unk12) {
        case 2:
            i = 0xA;
            s->unk8 = 0.2f;
            break;
        case 3:
            i = 0x3C;
            s->unk8 = 0.1f;
            break;
        default:
            i = 0xB4;
            s->unk8 = 0.1f;
            break;
        }
        if (sp69 == 1) {
            sp67 = 1;
            if (i < s->unk10) {
                s->unk13 = 0;
                s->unk15++;
                func_80609140(0x17D, 0x3E80, 62.0f, 1.0f, 0, 0);
            }
            if (sp6A != 0) {
                func_80609140(0x97, 0x7D00, 62.0f, 1.0f, 0, 0);
                s->unk16++;
                s->unk15 = 0;
                s->unk13 = 2;
                if (s->unk16 == 3) {
                    func_80609140(0x385, 0x7D00, 62.0f, 1.0f, 0, 0);
                    s->unk16 = 0;
                    camPausePath();
                    s->unk13 = 4;
                } else {
                    func_80609140(0x38E, 0x7D00, 62.0f, 1.0f, 0, 0);
                    func_80609140(0x383, 0x7D00, 62.0f, 1.0f, 0, 0);
                }
            }
        }
        break;
    case 2:
        s->unk8 = -0.1f;
        if (s->unk10 >= 0x5B) {
            s->unk15++;
            if (s->unk15 < 3) {
                s->unk13 = 3;
                func_80609140(0x37D, 0x7D00, 62.0f, 1.0f, 0, 0);
                func_80609140(0x380, 0x7D00, 62.0f, 1.0f, 0, 0);
            } else {
                s->unk13 = 0;
                s->unk15 = 0;
            }
        }
        if (sp69 != 0 && D_80035B40 == 0) {
            sp68 = 1;
        }
        break;
    case 3:
        s->unk8 = 0.1f;
        if (s->unk10 >= 0x1F) {
            s->unk13 = 2;
            func_80609140(0x17D, 0x3E80, 62.0f, 1.0f, 0, 0);
        }
        if (sp69 != 0) {
            s->unk17 = 1;
        }
        break;
    case 4:
        D_80035B3C += 1.0;
        if (D_80035B3C > 24.0) {
            D_80035B3C = 24.0f;
            s->unk10++;
            D_80035B2C = func_80612794(s->unk10 << 5) * 200.0f;
            if (s->unk10 == 0x3F) {
                D_80035B3C = 0.0f;
                D_80035B2C = 0;
                D_80035B28 = D_80035B30[D_80035B34];
                D_80035B34 += 1;
                s->unk13 = 5;
            }
        }
        break;
    case 5:
        s->unk10++;
        if (s->unk10 >= 0x3D) {
            s->unk8 = -0.1f;
            camResumePath();
            s->unk13 = 0;
            s->unk12++;
            if (s->unk12 == 1) {
                func_80724994(1, 7, 0, 0, 0);
            }
            if (s->unk12 == 3) {
                s->unk13 = 7;
            }
        }
        break;
    case 6:
        s->unk8 = -0.1f;
        if (sp69 == -1) {
            sp67 = 1;
            if (D_80035B70 < s->unk10) {
                func_80609140(0x17D, 0x3E80, 62.0f, 1.0f, 0, 0);
                s->unk10 = 0;
                j = D_80035B70 + 1;
                if (j >= 0x10) {
                    j += 1;
                }
                D_80035B70 = j;
                if (j >= 0x1A) {
                    s->unk13 = 1;
                    s->unk15++;
                    D_80035B70 = (func_806119A0() & 3) + 4;
                    func_80609140(0x37F, 0x7D00, 62.0f, 1.0f, 0, 0);
                    func_80609140(0x381, 0x7D00, 62.0f, 1.0f, 0, 0);
                }
                sp68 = 1;
            }
            D_80035B68 = 0x1E;
        }
        break;
    case 7:
        s->unk10++;
        s->unk8 = -0.1f;
        if (s->unk10 >= 0x10) {
            for (j = 0; j < 4; j++) {
                actorDespawn(actorListFindActorById(j));
            }
            BsA2_A->unk60 &= ~0x8000;
            BsA2_A->unk128 = 0;
            camStartPath(0, 4, 1);
            s->unk13 = 8;
        }
        break;
    case 8:
        s->unk8 = -0.1f;
        if (D_807FBDC4 != 0) {
            sfxAllocateChannel(0x35, 1.0f);
            bossSpawnParticleRing(0x13D, BsA2_A->unk7C, BsA2_A->unk80 + 200.0f, BsA2_A->unk84 + 40.0f, 0x800, 1);
            s->unk13 = 9;
        }
        break;
    }
    if (s->unk12 == 3 && s->unk13 == 0) {
        if (s->unk15 < 2) {
            s->unk13 = 6;
        } else {
            s->unk15 = 0x14;
        }
    }
    if (sp6B != s->unk13) {
        s->unk10 = 0;
    }
    if (sp68 != 0) {
        if (s->unk12 == 2 || s->unk12 == 3) {
            s->unk14++;
        } else {
            s->unk14 += (s32)(func_806119FC() * 2.99f) + 1;
        }
        if (s->unk14 >= 4) {
            s->unk14 -= 4;
        }
    }
    D_80035B68++;
    if (sp67 != 0) {
        i = (D_80035B68 & 0x1F) - 0x10;
        if (i < 0) {
            i = -i;
        }
        if (i >= 0x10) {
            i = 0xF;
        }
        sp5C = (i * 0x10) & 0xFF;
        lightAdd((f32)((f64)D_80035B00[s->unk14] * 0.33 + (f64)BsA2_A->unk7C), 400.0f,
                 (f32)((f64)D_80035B08[s->unk14] * 0.33 + (f64)BsA2_A->unk84),
                 (f32)((f64)D_80035B00[s->unk14] * 0.33 + (f64)BsA2_A->unk7C), 300.0f,
                 (f32)((f64)D_80035B08[s->unk14] * 0.33 + (f64)BsA2_A->unk84), 200.0f, 0, sp5C, sp5C, sp5C);
        if (s->unk12 == 1) {
            j = s->unk14 + 2;
            if (j >= 4) {
                j -= 4;
            }
            lightAdd((f32)((f64)D_80035B00[j] * 0.33 + (f64)BsA2_A->unk7C), 400.0f,
                     (f32)((f64)D_80035B08[j] * 0.33 + (f64)BsA2_A->unk84),
                     (f32)((f64)D_80035B00[j] * 0.33 + (f64)BsA2_A->unk7C), 300.0f,
                     (f32)((f64)D_80035B08[j] * 0.33 + (f64)BsA2_A->unk84), 200.0f, 0, sp5C, sp5C, sp5C);
        }
    }
    s->unkC--;
    if (s->unkC < 0) {
        s->unkC = (func_806119A0() & 0x7F) + 0x5A;
        lightSetColor(0.5f, 0.5f, 0.5f, -1);
        func_8068B80C();
    }
    D_80035B40 = sp69;
    actorUpdateModelMatrix(D_807FBB40, 0);
}
