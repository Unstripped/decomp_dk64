#include "common.h"
#include "actor.h"

extern Actor *D_807FBB40;
extern Actor *D_807FBB4C;
extern ActorGlobalState D_807FBB70;
extern u8 D_807FBD70;

typedef struct R1BQuad {
    /* 0x0 */ u8 unk0;
    /* 0x1 */ u8 unk1;
    /* 0x2 */ s16 unk2;
    /* 0x4 */ s16 unk4;
    /* 0x6 */ s16 unk6;
} R1BQuad;

typedef struct R1BSub4 {
    /* 0x00 */ u8 pad0[0x1C];
    /* 0x1C */ R1BQuad *unk1C;
} R1BSub4;

typedef struct R1BView {
    /* 0x000 */ u8 pad0[4];
    /* 0x004 */ R1BSub4 *unk4;
    /* 0x008 */ u8 pad8[0x9C];
    /* 0x0A4 */ f32 unkA4;
    /* 0x0A8 */ u8 padA8[0x10];
    /* 0x0B8 */ f32 unkB8;
    /* 0x0BC */ u8 padBC[8];
    /* 0x0C4 */ f32 unkC4;
    /* 0x0C8 */ f32 unkC8;
    /* 0x0CC */ u8 padCC[0x1A];
    /* 0x0E6 */ s16 unkE6;
    /* 0x0E8 */ u8 padE8[6];
    /* 0x0EE */ s16 unkEE;
    /* 0x0F0 */ u8 padF0[0x64];
    /* 0x154 */ u8 unk154;
    /* 0x155 */ u8 pad155[0x1F];
    /* 0x174 */ void *unk174;
    /* 0x178 */ u8 *unk178;
} R1BView;

#define R1B44 ((R1BView *)D_807FBB44)
#define R1B40 ((R1BView *)D_807FBB40)

extern Actor *D_807FBB44;
extern s16 D_807502E0;
extern f32 D_807502E8;

s32 actorSpawn(s32, s32);
void func_80614EBC(void *, s32);
void func_8067B238(void *, void *, f32);
void func_8072B324(void *, s32);
void *memcpy(void *, const void *, unsigned int);
void func_80729B00(void);
void func_80724C2C(s32);
void func_806B6DB0();
void sfxPlayFromActorWithAltitudeCheck(void *, s32, s32, s32, s32);

void func_806B6600(u8 arg0) {
    u8 *p = R1B40->unk178;
    s32 pad1;
    R1BQuad *q = R1B40->unk4->unk1C;
    s32 pad2;
    f32 f;
    f32 x;
    u32 a;

    if (!arg0) {
        p[0] = -p[0] * 0.2 + (u32)p[0];
        p[1] = 0;
    } else {
        switch (p[1]) {
            case 0:
                p[1] = 1;
                break;
            case 1:
                p[0] += 0x32;
                if (p[0] >= 0xCE) {
                    p[0] = 0xFF;
                    p[1] = 2;
                }
                break;
            case 2:
                p[0] -= 0x50;
                a = p[0];
                if (p[0] >= 0x64 && (s32)a < 0xB4) {
                    sfxPlayFromActorWithAltitudeCheck(D_807FBB40, 0x16C, 0xFF, 0xA0, 6);
                    a = p[0];
                }
                if ((s32)a < 0x50) {
                    p[0] = 0;
                    p[1] = 0;
                }
                break;
        }
    }
    x = (u32)p[0] / 255.0;
    f = 8000.0f * x;
    q->unk2 = (u32)-f;
    q[1].unk1 = 3;
    q++;
    q->unk0 = 0x7F;
    q->unk2 = (u32)f;
    q->unk4 = 0;
    q->unk6 = 0;
}

typedef struct R1B90View {
    /* 0x00 */ u8 pad0[0x1E];
    /* 0x1E */ u8 unk1E;
    /* 0x1F */ u8 unk1F;
    /* 0x20 */ u8 pad20[0xC];
    /* 0x2C */ s16 unk2C;
    /* 0x2E */ u8 pad2E[7];
    /* 0x35 */ u8 unk35;
} R1B90View;

#define R1B90 ((R1B90View *)D_807FDC90)

void effectSpawnRing();
void actorDespawn(Actor *);
void func_806319C4(void *, s32);
s32 func_8072AB74(s32, f32, f32, s32, f32);
void func_8072B7CC(s32);

void func_806B6958(void) {
    func_80729B00();
    if (!(D_807FBB40->unk60 & 0x10)) {
        R1B90->unk35 = R1B90->unk35 * 2;
        R1B90->unk2C = 0xD2;
        R1B90->unk1F = (u32)R1B90->unk1F * 1.5;
        R1B90->unk1E = (u32)R1B90->unk1E * 1.5;
    }
    if (R1B90->unk2C != 0) {
        R1B90->unk2C = R1B90->unk2C - 1;
    }
    if (R1B90->unk2C % 30 == 0) {
        R1B90->unk1F = R1B90->unk1F - 1;
        R1B90->unk1E = R1B90->unk1E - 1;
    }
    if (D_807FBB70.unk200 == 4) {
        func_80724C2C(-0x96);
    }
    if (R1B90->unk2C == 0 || D_807FBB70.unk200 == 9 || D_807FBB70.unk15 != 0) {
        sfxPlayFromActorWithAltitudeCheck(D_807FBB40, 0x3B2, 0xFF, 0x7F, 0x1E);
        sfxPlayFromActorWithAltitudeCheck(D_807FBB40, 0x3B7, 0xFF, 0x7F, 0x1E);
        effectSpawnRing();
        actorDespawn(D_807FBB40);
    }
    if (D_807FBB40->unk154 == 0x23) {
        func_8072AB74(0x23, D_807FDC94->unk7C, D_807FDC94->unk84, 0x200, 0.0f);
    } else {
        func_8072B7CC(0x237);
    }
    func_806319C4(D_807FBB40, 0);
}

void func_806B6C88(s16 arg0, s16 arg1) {
    if (actorSpawn(0xD3, 0x24) != 0) {
        R1B44->unk154 = 0x23;
        func_80614EBC(D_807FBB44, 0x237);
        R1B44->unkE6 = arg1;
        R1B44->unkEE = R1B44->unkE6;
        func_8067B238(D_807FBB44, D_807FBB40, D_807FBB40->unk4->unk38);
        R1B44->unkA4 = R1B40->unkA4;
        R1B44->unkC4 = D_807502E8;
        R1B44->unkC8 = D_807502E0;
        R1B44->unkB8 = 0.0f;
        func_8072B324(D_807FBB40, arg0 * 1.25);
        memcpy(R1B44->unk174, R1B40->unk174, 0x3C);
    }
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/BB300/func_806B6DB0.s")

void func_806B75F4(void) {
    func_80729B00();
    func_806B6DB0(0x2710);
}

void func_806B761C(void) {
    func_80729B00();
    if (D_807FBD70 == 4) {
        func_80724C2C(-0x64);
    }
    func_806B6DB0(0x2710);
}

void func_806B7660(void) {
    func_80729B00();
    if (D_807FBD70 == 4) {
        func_80724C2C(-0x64);
    }
    func_806B6DB0(0x2710);
}
