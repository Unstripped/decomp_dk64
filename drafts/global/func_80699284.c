// func_80699284 (src/global/9DD70.c): Stage 4-5: identical blocks, frame 0xF0, callee-saved {s0,ra} and all stack offsets match; 406 vs 403 insns, 21 normalized diff lines. Remaining: assetFreeBuffer/heapFreeDeferred arg-materialisation order, 2 extra spEC loads in the despawn region, .late_rodata label offsets. spEC must stay a spilled pointer (orig had no s-register for it); used spEC[1] array hack. 63.0f (not 60.0f) is func_80609140's 3rd arg.
typedef struct L1_PlayerState {
    /* 0x000 */ u8 pad0[0x88];
    /* 0x088 */ s32 unk88;
    /* 0x08C */ u8 pad8C[0x1A4 - 0x8C];
    /* 0x1A4 */ u8 unk1A4;
    /* 0x1A5 */ u8 pad1A5[0x1EC - 0x1A5];
    /* 0x1EC */ u8 unk1EC;
    /* 0x1ED */ u8 pad1ED[0x1F0 - 0x1ED];
    /* 0x1F0 */ u32 unk1F0;
} L1_PlayerState;

typedef struct L1_Sub174 {
    /* 0x00 */ L1_PlayerState *unk0;
    /* 0x04 */ s16 *unk4;
    /* 0x08 */ s32 unk8;
    /* 0x0C */ s32 unkC;
    /* 0x10 */ u16 unk10;
} L1_Sub174;

typedef struct L1_CamState {
    /* 0x000 */ u8 pad0[0x210];
    /* 0x210 */ f32 unk210;
    /* 0x214 */ f32 unk214;
    /* 0x218 */ f32 unk218;
    /* 0x21C */ u8 pad21C[0xC];
    /* 0x228 */ f32 unk228;
    /* 0x22C */ f32 unk22C;
    /* 0x230 */ f32 unk230;
} L1_CamState;

#define L1_MIN(a, b) (((a) < (b)) ? (a) : (b))

extern Actor *D_807FBB40;
extern s32 D_807FC924;
extern u8 D_807444FC;
extern L1_PlayerState *D_807FD580;

s32 func_806FFF88(void);
void func_80613C48(Actor *, s16, f32, f32);
void func_80614D00(Actor *, f32, f32);
void sfxPlayActorSound(void *, s32, s32, s32, s32, s32, f32, s32);
void sfxStopSlotSound(Actor *, s32);
void func_807002AC(s16 *, s32 *, f32);
void animSetNodeItem(void *, s32, s16, s32);
void func_806F91B4(s32, u8, s32);
void sfxAllocateChannel(s32, f32);
void func_80609140(s32, s32, f32, f32, s32, s32);
void renderCallbacksRegister(void *, void *, s32);
void func_80699070(s16 *, s16 *, f32, f32, f32, f32, f32, f32);
s32 playerStateQueueCallback(s32, s32, s32, void *);
void assetFreeBuffer(s32, s32, s32);
void heapFreeDeferred(Mtx *);
void actorDespawn(Actor *);
void func_806319C4(Actor *, s32);
void func_80699128(Gfx *, Actor *);
void func_806FF628(void);

void func_80699284(void) {
    /* 1-element array: forces the target's spilled-pointer codegen (loads from
       0xEC(sp) with per-block reuse) instead of a callee-saved s1. */
    L1_Sub174 *spEC[1];
    s16 spEA;
    s16 spE8;
    f32 mtx1[4][4];
    f32 mtx2[4][4];
    s16 sp66;
    s16 l1Angle;
    s32 *l1Dest;
    u8 sp5F;
    f32 t;

    sp5F = 0;
    spEC[0] = D_807FBB40->unk174;
    if (!(D_807FBB40->unk60 & 0x10)) {
        spEC[0]->unk10 = 0x5A;
        D_807FBB40->unk60 |= 0x400;
        D_807FBB40->unk12A = 0x3E8;
        spEC[0]->unk4 = (s16 *)func_806FFF88();
        func_80613C48(D_807FBB40, 0x40B, 0, 0);
        func_80614D00(D_807FBB40, 0.15f, 0);
    }
    D_807FBB40->unk60 &= ~4;
    sp66 = 0x5A - spEC[0]->unk10;
    if (sp66 == 0xD) {
        sfxPlayActorSound(D_807FBB40, 0x222, 0, 0, 0, 0xFF, 1.0f, -1);
    }
    if (sp66 == 0x1B) {
        sfxStopSlotSound(D_807FBB40, 0);
    }
    t = L1_MIN(1.0, ((sp66 - 0x1E) < 0 ? 0 : (sp66 - 0x1E)) / 60.0f * 5.0);
    if (t < 1.0 && D_807FBB40->unk58 != 0xD9) {
        l1Dest = &(&spEC[0]->unk8)[D_807444FC];
        func_807002AC((s16 *)spEC[0]->unk4, l1Dest, t);
        animSetNodeItem(D_807FBB40, 0, 0, (&spEC[0]->unk8)[D_807444FC]);
    } else {
        animSetNodeItem(D_807FBB40, 0, 0, (s32)spEC[0]->unk4);
        if (D_807FBB40->unk155[0] == 0) {
            if (D_807FD580->unk1EC == 1) {
                func_806F91B4(0xC, D_807FD580->unk1A4, 1);
                sfxAllocateChannel(0x2E, 1.0f);
            } else if (D_807FD580->unk1EC == 2) {
                func_80609140(0x98, 0x7FFF, 63.0f, 1.0f, 0, 0x80);
            }
            D_807FBB40->unk155[0]++;
        }
        if (D_807FD580->unk1EC != 0xFF && spEC[0]->unk10 != 0) {
            renderCallbacksRegister(&func_806FF628, D_807FBB40, 3);
        }
    }
    func_80699070(&spE8, &spEA, ((L1_CamState *)D_807FC924)->unk210, ((L1_CamState *)D_807FC924)->unk214, ((L1_CamState *)D_807FC924)->unk218, ((L1_CamState *)D_807FC924)->unk228, ((L1_CamState *)D_807FC924)->unk22C, ((L1_CamState *)D_807FC924)->unk230);
    t = L1_MIN(30.0, sp66) / 30.0;
    D_807FBB40->unkE6 = spEA;
    l1Angle = (f32)spE8 - (2048.0f + -2048.0f * t);
    *(s16 *)D_807FBB40->unkE8 = l1Angle;
    guRotateF(mtx1, spE8 / 4095.0 * 360.0, 1.0f, 0.0f, 0.0f);
    guRotateF(mtx2, spEA / 4095.0 * 360.0, 0.0f, 1.0f, 0.0f);
    guMtxCatF(mtx1, mtx2, mtx1);
    guTranslateF(mtx2, ((L1_CamState *)D_807FC924)->unk210, ((L1_CamState *)D_807FC924)->unk214, ((L1_CamState *)D_807FC924)->unk218);
    guMtxCatF(mtx1, mtx2, mtx1);
    guMtxXFMF(mtx1, 0.0f, 0.0f, -30.0f * t, &D_807FBB40->unk7C, &D_807FBB40->unk80, &D_807FBB40->unk84);
    if (spEC[0]->unk10 != 0) {
        spEC[0]->unk10--;
    } else {
        D_807FBB40->unk60 &= ~0x8000;
        D_807FBB40->unk128 -= 0xA;
        if (D_807FBB40->unk128 <= 0) {
            sp5F = 1;
        }
    }
    if (sp5F || !(spEC[0]->unk0->unk1F0 & 0x8000)) {
        if (spEC[0]->unk0->unk1EC == 1) {
            playerStateQueueCallback(0x58, 0, 0, (void *)spEC[0]);
        }
        sfxStopSlotSound(D_807FBB40, 0);
        spEC[0]->unk0->unk1F0 &= ~0x8000;
        spEC[0]->unk0->unk1EC = 0xFF;
        if (D_807FBB40->unk58 == 0xD9) {
            assetFreeBuffer((s32)spEC[0]->unk4, 0xF6, 0x45);
        } else {
            heapFreeDeferred((Mtx *)spEC[0]->unk4);
        }
        spEC[0]->unk0->unk88 = 0;
        actorDespawn(D_807FBB40);
    } else {
        guTranslateF((f32 (*)[4])((u8 *)D_807FBB40 + 0xC), 0.0f, -70.0f, 0.0f);
        func_806319C4(D_807FBB40, 1);
        renderCallbacksRegister(&func_80699128, D_807FBB40, 3);
    }
}
