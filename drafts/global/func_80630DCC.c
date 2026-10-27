// func_80630DCC (src/global/35000.c): func_80630DCC (src/global/35000.c): stage 5, parked NON_MATCHING in NM35 copy: frame 0xE0, stack offsets, callee-saved set exact; whole function matches except (1) size block: expected computes add.s/trunc.w.s/mfc1 v1 (s32)(size*size+dz*dz) BEFORE the dy<0.01 branch (uopt sinks it in mine: toy tests show a single-def int var, a prior-def var, f64/s32/f32 locals, ternary clamp all sink; only a real pre-branch use pins it) which also changes lw t3,4(s0) delay-slot choice and f-regs (expected f16/f18/f4/f6/v1; mine t4 + 0.3 const in f12 early); (2) FIXED: 'if (node)' instead of 'node != 0' with s32 actorGetNodePos proto gives lbu v0 + move a1,v0; 4 insns (16 bytes) shorter than expected overall due to (1). Needs GfxWords + WRITE_GFX_WORDS from 35000.c; func_80630DCC proto 3rd param is GfxWords *.
typedef struct ModelInfo {
    /* 0x00 */ u8 pad0[0x38];
    /* 0x38 */ f32 unk38;
} ModelInfo;

typedef struct ActorCtl {
    /* 0x000 */ u8 pad0[0x1A4];
    /* 0x1A4 */ u8 unk1A4;
} ActorCtl;

typedef struct RenderActor {
    /* 0x000 */ u8 pad0[4];
    /* 0x004 */ ModelInfo *unk4;
    /* 0x008 */ u8 pad8[0x50];
    /* 0x058 */ s32 unk58;
    /* 0x05C */ u16 unk5C;
    /* 0x05E */ u8 pad5E[2];
    /* 0x060 */ u32 unk60;
    /* 0x064 */ u32 unk64;
    /* 0x068 */ u8 pad68[2];
    /* 0x06A */ u16 unk6A;
    /* 0x06C */ u8 pad6C[0x10];
    /* 0x07C */ f32 unk7C;
    /* 0x080 */ f32 unk80;
    /* 0x084 */ f32 unk84;
    /* 0x088 */ u8 pad88[0x45];
    /* 0x0CD */ u8 unkCD;
    /* 0x0CE */ s16 unkCE;
    /* 0x0D0 */ u8 padD0[0x58];
    /* 0x128 */ s16 unk128;
    /* 0x12A */ s16 unk12A;
    /* 0x12C */ s16 unk12C;
    /* 0x12E */ u8 pad12E[2];
    /* 0x130 */ u8 unk130;
    /* 0x131 */ u8 unk131;
    /* 0x132 */ u8 pad132[0x16];
    /* 0x148 */ void *unk148[2];
    /* 0x150 */ u8 pad150[0xE];
    /* 0x15E */ u8 unk15E;
    /* 0x15F */ u8 pad15F[0xB];
    /* 0x16A */ u8 unk16A;
    /* 0x16B */ u8 unk16B;
    /* 0x16C */ u8 unk16C;
    /* 0x16D */ u8 unk16D;
    /* 0x16E */ u8 pad16E[6];
    /* 0x174 */ ActorCtl *unk174;
} RenderActor;

typedef struct PlayerView {
    /* 0x000 */ u8 pad0[0x21C];
    /* 0x21C */ f32 unk21C;
    /* 0x220 */ f32 unk220;
    /* 0x224 */ f32 unk224;
    /* 0x228 */ u8 pad228[0x2F0 - 0x228];
} PlayerView;

extern u8 D_807444FC;
extern PlayerView *D_807FC924;
extern u8 D_807FC928;
extern u8 D_807FC929;

void func_80614A64(void *);
void *func_80614B34(void *, void *);
s32 func_80658E8C(f32, f32, f32, u8, s32);
void func_8065C334(f32, f32, f32, s16, u8 *, u8 *, u8 *, s16);
void *func_80722294(void *, void *, u8);
void actorGetNodePos(void *, s32, f32 *, f32 *, f32 *);
void renderCalcPlayerDistanceAlpha(f32, f32, f32, f32, s16, s16 *);
f32 renderScaleDistanceByFov(f32);
void *renderSetSegment6AndFog(void *, s16, u8);

#define RENDER_ACT ((RenderActor *)arg1)
#define CUR_PLAYER_VIEW ((PlayerView *)((u8 *)D_807FC924 + D_807FC929 * 0x2F0))

void *func_80630DCC(s32 arg0, void *arg1, GfxWords *arg2, u8 arg3) {
    ActorCtl *ctl;
    s32 flag;
    f32 dx;
    f32 dy;
    f32 dz;
    u8 spCB;
    u8 spCA;
    u8 spC9;
    f64 x;
    f32 size;
    f32 spB8;
    f64 d;

    spB8 = 1.0f;
    if (!(RENDER_ACT->unk60 & 4)) {
        flag = 0;
        if (D_807FC928 >= 2 && (RENDER_ACT->unk5C & 1) && (ctl = RENDER_ACT->unk174, D_807FC929 != ctl->unk1A4)) {
            flag = 1;
        }
        if (flag == 0) {
            return arg2;
        }
    }
    if (RENDER_ACT->unk58 != 0x1F && RENDER_ACT->unk58 != 0x27 && RENDER_ACT->unk58 != 0xAE && !(RENDER_ACT->unk60 & 0x400)) {
        dx = CUR_PLAYER_VIEW->unk21C - RENDER_ACT->unk7C;
        dy = CUR_PLAYER_VIEW->unk220 - RENDER_ACT->unk80;
        dz = CUR_PLAYER_VIEW->unk224 - RENDER_ACT->unk84;
        dx = dx * dx;
        dy = dy * dy;
        dz = dz * dz;
        if (sqrtf(dx + dy + dz) > renderScaleDistanceByFov(RENDER_ACT->unk12A)) {
            return arg2;
        }
        if (func_80658E8C(RENDER_ACT->unk7C, RENDER_ACT->unk80, RENDER_ACT->unk84, RENDER_ACT->unk130, RENDER_ACT->unk131)) {
            return arg2;
        }
    }
    RENDER_ACT->unk60 |= 0x100;
    if (!(RENDER_ACT->unk60 & 0x200)) {
        func_80614A64(arg1);
    }
    WRITE_GFX_WORDS(arg2++, 0xE7000000, 0);
    WRITE_GFX_WORDS(arg2++, 0xD9FFFFFF, 0x200001);
    WRITE_GFX_WORDS(arg2++, 0xD9FEF9FF, 0);
    if (RENDER_ACT->unk58 == 0x135) {
        WRITE_GFX_WORDS(arg2++, 0xD9FFFFFE, 0);
    }
    WRITE_GFX_WORDS(arg2++, 0xDB06003C, osVirtualToPhysical(RENDER_ACT->unk148[D_807444FC]));
    if (RENDER_ACT->unk60 & 0x1000) {
        arg2 = func_80722294(arg2, arg1, D_807FC929);
        WRITE_GFX_WORDS(arg2++, 0xD9FFFFFF, 0x20000);
        WRITE_GFX_WORDS(arg2++, 0xFA0000FF, 0xFFFFFFFF);
    } else {
        u8 node;
        s32 padE[1];
        f32 sp88;
        f32 sp84;
        f32 sp80;
        s32 padF[1];
        WRITE_GFX_WORDS(arg2++, 0xD9FDFFFF, 0);
        if (RENDER_ACT->unk60 & 0x800000) {
            spCB = RENDER_ACT->unk16A;
            spCA = RENDER_ACT->unk16B;
            spC9 = RENDER_ACT->unk16C;
        } else {
            node = RENDER_ACT->unkCD;
            if (node) {
                actorGetNodePos(arg1, node, &sp88, &sp84, &sp80);
            } else {
                sp88 = RENDER_ACT->unk7C;
                sp84 = RENDER_ACT->unk80;
                sp80 = RENDER_ACT->unk84;
            }
            func_8065C334(sp88, sp84, sp80, RENDER_ACT->unkCE, &spCB, &spCA, &spC9, RENDER_ACT->unk12C);
            if (!(RENDER_ACT->unk64 & 1)) {
                dx = RENDER_ACT->unk16D / 15.0f;
                spCB = spCB * dx;
                spCA = spCA * dx;
                spC9 = spC9 * dx;
            }
        }
        WRITE_GFX_WORDS(arg2++, 0xFA0000FF, (spCB << 24) | (spCA << 16) | (spC9 << 8) | 0xFF);
    }
    if (RENDER_ACT->unk60 & 0x8000) {
        renderCalcPlayerDistanceAlpha(RENDER_ACT->unk7C, RENDER_ACT->unk80, RENDER_ACT->unk84, RENDER_ACT->unk12A, -1, &RENDER_ACT->unk128);
    }
    if (RENDER_ACT->unk5C != 0x80 && RENDER_ACT->unk5C != 0x40 && RENDER_ACT->unk5C != 8) {
        if ((RENDER_ACT->unk80 - 5.0f < CUR_PLAYER_VIEW->unk220 && CUR_PLAYER_VIEW->unk220 < RENDER_ACT->unk80 + 2.0 * RENDER_ACT->unk15E) || (RENDER_ACT->unk6A & 0x2000)) {
            size = RENDER_ACT->unk84 - CUR_PLAYER_VIEW->unk224;
            dz = RENDER_ACT->unk7C - CUR_PLAYER_VIEW->unk21C;
            dy = RENDER_ACT->unk4->unk38;
            if (dy < 0.01) {
                dy = 0.01f;
            }
            spB8 = ((((f64)(s32)(size * size + dz * dz) / (dy / 0.15) / 400.0) > 0.3 ? ((f64)(s32)(size * size + dz * dz) / (dy / 0.15) / 400.0) - 0.3 : 0.0) < 1.0) ? (((f64)(s32)(size * size + dz * dz) / (dy / 0.15) / 400.0) > 0.3 ? ((f64)(s32)(size * size + dz * dz) / (dy / 0.15) / 400.0) - 0.3 : 0.0) : 1.0;
        }
    }
    dx = RENDER_ACT->unk128 * spB8;
    if (dx != 0.0f) {
        arg2 = func_80614B34(renderSetSegment6AndFog(arg2, dx, 1), arg1);
    }
    WRITE_GFX_WORDS(arg2++, 0xE7000000, 0);
    WRITE_GFX_WORDS(arg2++, 0xE3001001, 0);
    WRITE_GFX_WORDS(arg2++, 0xE7000000, 0);
    return arg2;
}
