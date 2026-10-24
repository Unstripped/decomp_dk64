#include "common.h"
#include "actor.h"

extern Actor *D_807FBB40;
extern Actor *D_807FBB4C;
extern ActorGlobalState D_807FBB70;
extern u8 D_807FBD70;

#pragma GLOBAL_ASM("asm/global/nonmatchings/BC3B0/func_806B76B0.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/BC3B0/func_806B7830.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/BC3B0/func_806B7BB8.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/BC3B0/func_806B7C74.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/BC3B0/func_806B7EA0.s")

typedef struct R1CView {
    /* 0x000 */ u8 pad0[0x178];
    /* 0x178 */ s16 *unk178;
    /* 0x17C */ s16 *unk17C;
} R1CView;

typedef struct R1CS90 {
    /* 0x00 */ u8 pad0[0x2C];
    /* 0x2C */ s16 unk2C;
    /* 0x2E */ s16 unk2E;
    /* 0x30 */ f32 unk30;
} R1CS90;

typedef struct R1CS98 {
    /* 0x00 */ u8 pad0[0xA];
    /* 0x0A */ u8 unkA;
    /* 0x0B */ u8 unkB;
} R1CS98;

typedef struct R1CS9C {
    /* 0x00 */ u8 pad0[0xA];
    /* 0x0A */ u8 unkA;
    /* 0x0B */ u8 unkB;
    /* 0x0C */ u8 unkC;
    /* 0x0D */ u8 unkD;
    /* 0x0E */ u8 padE;
    /* 0x0F */ u8 unkF;
} R1CS9C;

#define R1CA ((R1CView *)D_807FBB40)
#define R1C90 ((R1CS90 *)D_807FDC90)
#define R1C98 ((R1CS98 *)D_807FDC98)
#define R1C9C ((R1CS9C *)D_807FDC9C)

extern u32 D_8076A064;
extern u8 D_807201D4[];
extern void func_80717D4C(void);

void func_80729B00(void);
void func_8066EB40(Actor *, f32);
void actorAppendModelNode(Actor *, f32, f32, f32, f32, s32);
void actorAppendModelSubNode(Actor *, f32, f32, f32, s32);
void actorSetNodeFlag(Actor *, s32);
void actorClearNodeFlag(Actor *, s32);
void sfxPlayFromActorWithAltitudeCheck(void *, s32, s32, s32, s32);
void func_807149FC(s32);
void func_807149B8(s32);
void func_80714950(s32);
void func_8071498C(void *);
void func_80714CC0(void *, f32, f32, f32, f32);
void lightAdd(f32, f32, f32, f32, f32, f32, f32, s32, s32, s32, s32);
void projectileSetTargetCoords(f32, f32, f32);
void projectileAimAndSpawn(s32, s32, f32, f32, f32, f32, f32, void *);
void projectileSpawnNodeEntry(s32, s32, f32, s32, f32, f32, void *);
void func_806B88B8(void);

void func_806B83E4(void) {
    func_80729B00();
    if (!(D_807FBB40->unk60 & 0x10)) {
        R1C90->unk30 = R1C9C->unkB;
        func_8066EB40(D_807FBB40, 300.0f);
        actorAppendModelNode(D_807FBB40, 0.0f, 0.0f, 0.0f, 280.0f, -1);
        actorAppendModelSubNode(D_807FBB40, 0.0f, 0.0f, 0.0f, -1);
    }
    if (R1C90->unk30 <= 0.001) {
        R1C90->unk2C = R1C9C->unkA;
        R1C90->unk30 = R1C9C->unkB;
        actorSetNodeFlag(D_807FBB40, 1);
        sfxPlayFromActorWithAltitudeCheck(D_807FBB40, 0x182, 0xFF, 0x7F, 0x1E);
    }
    R1C90->unk30 = R1C90->unk30 - 1.0;
    if (R1C90->unk2C != 0 && D_8076A064 % 5 == 0) {
        func_807149FC(3);
        func_807149B8(1);
        func_80714950(-0x1C2);
        func_8071498C(func_80717D4C);
        func_80714CC0(D_807201D4, 1.2f, D_807FBB40->unk7C, D_807FBB40->unk80 + 7.0, D_807FBB40->unk84);
    }
    if (R1C90->unk2C != 0) {
        lightAdd(D_807FBB40->unk7C, D_807FBB40->unk80 + 7.0, D_807FBB40->unk84, 0.0f, 0.0f, 0.0f, 200.0f, 0, 0xFF, 0xC8, 0);
        R1C90->unk2C--;
        if (R1C90->unk2C == 0) {
            actorClearNodeFlag(D_807FBB40, 1);
        }
    }
}

void func_806B86AC(void) {
    func_80729B00();
    if (!(D_807FBB40->unk60 & 0x10)) {
        R1C90->unk2E = R1C98->unkB;
    }
    if (R1C90->unk2E == 0) {
        R1C90->unk2C = R1C98->unkA;
        R1C90->unk2E = R1C98->unkB;
        sfxPlayFromActorWithAltitudeCheck(D_807FBB40, 0x182, 0xFF, 0x7F, 0x1E);
    }
    R1C90->unk2E--;
    if (R1C90->unk2C != 0 && D_8076A064 % 5 == 0) {
        projectileSetTargetCoords(D_807FBB40->unk7C, D_807FBB40->unk80, D_807FBB40->unk84);
        projectileAimAndSpawn(0x51, 1, 0.3f, D_807FDC94->unk7C, D_807FDC94->unk80, D_807FDC94->unk84, 80.0f, D_807FBB40);
    }
    if (R1C90->unk2C != 0) {
        lightAdd(D_807FBB40->unk7C, D_807FBB40->unk80, D_807FBB40->unk84, 0.0f, 0.0f, 0.0f, 200.0f, 0, 0xFF, 0xC8, 0);
        R1C90->unk2C--;
    }
}

void func_806B8878(void) {
    func_806B88B8();
}

void func_806B8898(void) {
    func_806B88B8();
}

void func_806B88B8(void) {
    s16 *a = R1CA->unk178;
    s16 *b = R1CA->unk17C;
    s16 kind;

    func_80729B00();
    if (!(D_807FBB40->unk60 & 0x10)) {
        R1C90->unk30 = R1C9C->unkB;
        *a = R1C9C->unkD;
    }
    if (*a != 0) {
        *a = *a - 1;
        return;
    }
    if (R1C90->unk30 <= 0.001) {
        R1C90->unk2C = R1C9C->unkA;
        R1C90->unk30 = R1C9C->unkB;
        *b = 0;
        sfxPlayFromActorWithAltitudeCheck(D_807FBB40, 0x17, 0xFF, 0x7F, 0x19);
    }
    R1C90->unk30 = R1C90->unk30 - 1.0;
    if (R1C90->unk2C != 0 && *b == 0) {
        projectileSetTargetCoords(D_807FBB40->unk7C, D_807FBB40->unk80, D_807FBB40->unk84);
        switch (D_807FBB40->unk58) {
            case 0xDC:
                kind = 0x37;
                break;
            case 0xDF:
                kind = 0x1E;
                break;
        }
        projectileSpawnNodeEntry(kind, 0, 0.6f, D_807FBB40->unkE6, R1C9C->unkC * 10, 0.0f, 0);
        R1C90->unk2C--;
        *b = R1C9C->unkF;
    }
    if (*b != 0) {
        *b = *b - 1;
    }
}
