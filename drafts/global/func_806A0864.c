// func_806A0864 (src/global/A2F10.c): stage 6: 198/198 insns, matrix stack layout matched (mtxL,mtx1,mtx3,mtx2); only temp-register naming differs (t0<->t9)
typedef struct {
    f32 unk0;
    f32 unk4;
    f32 unk8;
    f32 unkC;
} M5_A2F10Quad;

typedef struct {
    f32 unk0;
    f32 unk4;
    f32 unk8;
} M5_A2F10Vec3;

typedef struct {
    s32 unk0;
    s32 unk4;
    s32 unk8;
    /* 0x00C */ s16 unkC;
    /* 0x00E */ u8 unkE;
    /* 0x00F */ u8 unkF;
    u8 pad10[0x1F0];
    s16 unk200;
} M5_A2F10Sub;

typedef struct {
    /* 0x000 */ struct M5_A2F10Model *unk0;
    /* 0x004 */ struct M5_A2F10Sub4 *unk4;
    /* 0x008 */ void *unk8;
    /* 0x00C */ u8 padC[0x50];
    /* 0x05C */ u16 unk5C;
    /* 0x05E */ u8 pad5E[2];
    /* 0x060 */ u32 unk60;
    /* 0x064 */ u8 pad64[0x6];
    /* 0x06A */ u16 unk6A;
    /* 0x06C */ u16 unk6C;
    /* 0x06E */ u8 pad6E[0xE];
    /* 0x07C */ f32 unk7C;
    /* 0x080 */ f32 unk80;
    /* 0x084 */ f32 unk84;
    /* 0x088 */ u8 pad88[0x1C];
    /* 0x0A4 */ f32 unkA4;
    /* 0x0A8 */ f32 unkA8;
    /* 0x0AC */ u8 padAC[0xC];
    /* 0x0B8 */ f32 unkB8;
    /* 0x0BC */ f32 unkBC;
    /* 0x0C0 */ f32 unkC0;
    /* 0x0C4 */ u8 padC4[0x20];
    /* 0x0E4 */ s16 unkE4;
    /* 0x0E6 */ u8 padE6[2];
    /* 0x0E8 */ s16 unkE8;
    /* 0x0EA */ u8 padEA[4];
    /* 0x0EE */ s16 unkEE;
    /* 0x0F0 */ u8 padF0[0xC];
    /* 0x0FC */ u8 unkFC;
    /* 0x0FD */ u8 padFD[0x1F];
    /* 0x11C */ struct M5_A2F10SpActor *unk11C;
    /* 0x120 */ u8 pad120[4];
    /* 0x124 */ M5_A2F10Vec3 *unk124;
    /* 0x128 */ s16 unk128;
    /* 0x12A */ s16 unk12A;
    /* 0x12C */ u8 pad12C[6];
    /* 0x132 */ s16 unk132;
    /* 0x134 */ u8 pad134[0x10];
    /* 0x144 */ u8 unk144;
    /* 0x145 */ u8 pad145[1];
    /* 0x146 */ s16 unk146;
    /* 0x148 */ u8 pad148[0x18];
    /* 0x160 */ f64 unk160;
    /* 0x168 */ s16 unk168;
    /* 0x16A */ u8 unk16A;
    /* 0x16B */ u8 unk16B;
    /* 0x16C */ u8 unk16C;
    /* 0x16D */ u8 pad16D[7];
    /* 0x174 */ M5_A2F10Sub *unk174;
} M5_A2F10Actor;

typedef struct M5_A2F10Sub4 {
    /* 0x000 */ u8 pad0[0x24];
    /* 0x024 */ M5_A2F10Quad *unk24;
    /* 0x028 */ u8 pad28[0xC];
    /* 0x034 */ f32 unk34;
    /* 0x038 */ f32 unk38;
    /* 0x03C */ f32 unk3C;
} M5_A2F10Sub4;

typedef struct M5_A2F10Model {
    /* 0x000 */ u8 pad0[0x20];
    /* 0x020 */ u8 unk20;
} M5_A2F10Model;

typedef struct {
    /* 0x000 */ u8 pad0[0x58];
    /* 0x058 */ s32 unk58;
    /* 0x05C */ u8 pad5C[0xC];
    /* 0x068 */ u16 unk68;
    /* 0x06A */ u16 unk6A;
    /* 0x06C */ u8 pad6C[0x10];
    /* 0x07C */ f32 unk7C;
    /* 0x080 */ f32 unk80;
    /* 0x084 */ f32 unk84;
    /* 0x088 */ u8 pad88[0x20];
    /* 0x0A8 */ f32 unkA8;
    /* 0x0AC */ u8 padAC[0x9A];
    /* 0x146 */ s16 unk146;
    /* 0x148 */ u8 pad148[0xE];
    /* 0x156 */ u8 unk156;
} M5_A2F10Target;

typedef struct M5_A2F10SpActor {
    /* 0x000 */ u8 pad0[8];
    /* 0x008 */ void *unk8;
    /* 0x00C */ u8 padC[0x48];
    /* 0x054 */ s32 unk54;
    /* 0x058 */ s32 unk58;
    /* 0x05C */ u8 pad5C[0x20];
    /* 0x07C */ f32 unk7C;
    /* 0x080 */ f32 unk80;
    /* 0x084 */ f32 unk84;
    /* 0x088 */ u8 pad88[0x20];
    /* 0x0A8 */ f32 unkA8;
    /* 0x0AC */ u8 padAC[0x9A];
    /* 0x146 */ s16 unk146;
    /* 0x148 */ u8 pad148[0xC];
    /* 0x154 */ u8 unk154;
    /* 0x155 */ u8 pad155[9];
    /* 0x15E */ u8 unk15E;
    /* 0x15F */ u8 unk15F;
    /* 0x160 */ u8 pad160[0x14];
    /* 0x174 */ void *unk174;
    /* 0x178 */ u8 pad178[0x88];
    /* 0x200 */ s16 unk200;
} M5_A2F10SpActor;

extern Actor *D_807FBB40;
s32 func_80611A44(void);
void func_806319C4(void *, s32);
void func_80665564(Actor *, f32);
void func_8067ACB4(Actor *);
void actorApplyVelocity(Actor *);
void actorDespawn(Actor *);
extern f32 D_80750394;

#define M5_A2F10_ACTOR ((M5_A2F10Actor *) D_807FBB40)

s32 func_80611A44(void);
void func_806319C4(void *, s32);
void func_80665564(Actor *, f32);
void func_8067ACB4(Actor *);
void actorApplyVelocity(Actor *);
void actorDespawn(Actor *);
extern f32 D_80750394;
extern Actor *D_807FBB44;
s32 func_80613448(Actor *);
s32 actorSpawn(s32, s32);
extern void *D_807FBB40;

void func_806A0864(void) {
    Mtx mtxL;
    float mtx1[4][4];
    float mtx3[4][4];
    float mtx2[4][4];
    M5_A2F10Sub *sub;
    Mtx *dst;
    s32 i;

    sub = M5_A2F10_ACTOR->unk174;
    if (!(M5_A2F10_ACTOR->unk60 & 0x10)) {
        M5_A2F10_ACTOR->unk60 |= 0x8100000;
        M5_A2F10_ACTOR->unk60 &= 0xFFFF7FFF;
        func_806131D4(D_807FBB40, func_80613448(D_807FBB40));
        sub->unk4 = M5_A2F10_ACTOR->unk11C->unk54;
        sub->unk0 = (s32) M5_A2F10_ACTOR->unk11C;
        sub->unk8 = M5_A2F10_ACTOR->unk11C->unk58;
    }
    if (!actorTableContains((Actor *) sub->unk0) || M5_A2F10_ACTOR->unk11C->unk54 != sub->unk4) {
        actorDespawn(D_807FBB40);
        return;
    }
    if (!(func_80665AAC((Actor *) sub->unk0) && M5_A2F10_ACTOR->unk11C->unk58 == sub->unk8
          && actorIsActive((Actor *) sub->unk0) && (((M5_A2F10Target *) sub->unk0)->unk68 & 0x40))) {
        actorDespawn(D_807FBB40);
        ((M5_A2F10Target *) sub->unk0)->unk6A &= 0xF7FF;
        return;
    }
    {
        M5_A2F10_ACTOR->unk128 = 0xFF;
        M5_A2F10_ACTOR->unk146 = ((M5_A2F10Target *) sub->unk0)->unk146;
        M5_A2F10_ACTOR->unk7C = ((M5_A2F10Target *) sub->unk0)->unk7C;
        M5_A2F10_ACTOR->unk80 = ((M5_A2F10Target *) sub->unk0)->unk80;
        M5_A2F10_ACTOR->unkA8 = ((M5_A2F10Target *) sub->unk0)->unkA8;
        M5_A2F10_ACTOR->unk84 = ((M5_A2F10Target *) sub->unk0)->unk84;
        M5_A2F10_ACTOR->unk60 |= 0x200;
        M5_A2F10_ACTOR->unk8 = ((void **) ((u8 *) M5_A2F10_ACTOR->unk4 + 0x14))[D_807444FC];
        memcpy(M5_A2F10_ACTOR->unk8, M5_A2F10_ACTOR->unk11C->unk8, M5_A2F10_ACTOR->unk0->unk20 << 6);
        guMtxIdentF(mtx1);
        mtx1[1][1] = -1.0f;
        guTranslateF(mtx2, -M5_A2F10_ACTOR->unk7C, -M5_A2F10_ACTOR->unkA8, -M5_A2F10_ACTOR->unk84);
        guMtxCatF(mtx2, mtx1, mtx1);
        guMtxF2L(mtx1, &mtxL);
        guTranslateF(mtx2, M5_A2F10_ACTOR->unk7C, M5_A2F10_ACTOR->unkA8, M5_A2F10_ACTOR->unk84);
        dst = M5_A2F10_ACTOR->unk8;
        for (i = 0; i < M5_A2F10_ACTOR->unk0->unk20; i++) {
            guMtxL2F(mtx3, dst);
            guMtxCatF(mtx3, mtx1, mtx3);
            guMtxCatF(mtx3, mtx2, mtx3);
            guMtxF2L(mtx3, dst);
            dst++;
        }
    }
}
