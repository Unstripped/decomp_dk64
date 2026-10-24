// func_8069D424 (src/global/9DD70.c): stage 3-4: same size (322 vs 323 insns), frame 0x60, Gfx writes match. Declarations cleaned: reuses the file's existing func_8069D358/M2_Pos/func_806FBD5C(s32) prototypes (cast at call sites) and a local M2_GfxWord pair type. Remaining: branch/switch dispatch order for the unk155 if/else-if chain (~19 extra insns around the func_807040D0 calls), Gfx cursor s1 vs s0, the unk15F*0.0078125 double block, state/mode bytes at 0x5A/0x5B vs 0x56/0x57.
extern Actor *D_807FBB40;
extern s16 D_80744490;

typedef struct M2_GfxWord {
    s32 w0;
    s32 w1;
} M2_GfxWord;

extern Gfx D_1000118;
extern s32 D_8074E880[];
extern s8 func_80717404;
s32 func_80611A44(void);
s16 func_806FBD5C(s16, s32);
void func_807040D0(s16);
void func_807149B8(s32);
void func_8071495C(void);
void func_8071498C(void *);
void func_80714950(s32);
void func_80714CC0(s32, f32, f32, f32, f32);


#define M2_WRITE_GFX(pkt, _w0, _w1) { Gfx *_g = (Gfx *)(pkt); _g->words.w0 = (_w0); _g->words.w1 = (u32)(_w1); }
void func_8069D424(Gfx *gfx, Actor *actor) {
    s32 *sub;
    u8 state;
    u8 mode;
    s16 sp54;
    s16 a2;
    s16 a3;
    f64 min;

    sub = actor->unk174;
    state = 3;
    mode = (u8)(u32)actor->unk84;
    M2_WRITE_GFX(gfx++, 0xDE000000, &D_1000118);
    M2_WRITE_GFX(gfx++, 0xFC119623, 0xFF2FFFFF);

    if (((u8 *)actor)[0x155] == 0) {
        if (actor->unk84 == 1.0f) {
            min = (f64)actor->unk15F * 0.0078125;
            if (min > 1.0) {
                min = 1.0;
            }
            sp54 = (s16)(s32)((f64)func_806FBD5C((s16)(s32)actor->unk84, *(s32 *)sub) * (min * 0.9) + (f64)actor->unk7C * 0.25);
            func_807149B8(1);
            func_8071498C(&func_80717404);
            func_80714950(0xA);
            func_8071495C();
            func_80714CC0(D_8074E880[((func_80611A44() >> 0xF) % 1000) % 3], 1.0f,
                          (f32)sp54, (f32)((f64)actor->unk80 * 0.25 + 12.0), -5.0f);
        }
        func_807040D0((s16)(actor->unk15F * 3));
    } else if (((u8 *)actor)[0x155] == 2) {
        func_807040D0((s16)(actor->unk15F * 3 + 0x4000));
    } else {
        func_807040D0((s16)(actor->unk15F * 3));
    }

    a2 = (s16)(s32)actor->unk7C;
    a3 = (s16)(s32)actor->unk80;
    switch (mode) {
    case 1:
        sp54 = func_806FBD5C((s16)(s32)actor->unk84, *(s32 *)sub);
        state = 0x13;
        gfx = func_8069D358(gfx, (M2_Pos *)actor, sp54, 0.8f);
        state &= 0xFFFE;
        a2 = sp54 * -2;
        a3 = 0;
        break;
    case 6:
        state = 0x23;
        M2_WRITE_GFX(gfx++, 0xE3000A01, 0x100000);
        M2_WRITE_GFX(gfx++, 0xE200001C, 0x0C184240);
        break;
    case 0:
        mode = 6;
        sp54 = func_806FBD5C(6, *(s32 *)sub);
        actor->unk7C = (f32)((D_80744490 - sp54) * 2);
        gfx = func_8069D358(gfx, (M2_Pos *)actor, sp54, 0.8f);
        state = 0;
        a2 = sp54 * -2;
        a3 = 0;
        mode = 6;
        break;
    case 10:
        mode = 6;
        gfx = func_8069D358(gfx, (M2_Pos *)actor, 0, 0.8f);
        state = 0;
        a2 = 0;
        a3 = 0;
        mode = 6;
        break;
    }

    M2_WRITE_GFX(gfx++, 0xFA000000, (actor->unk16A << 24) | (actor->unk16B << 16) | (actor->unk16C << 8) | actor->unk15F);
    func_806FC530((M2_GfxWord *)gfx, (s16)mode, a2, a3, *(s32 *)sub, state);
}
