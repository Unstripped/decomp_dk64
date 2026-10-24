// func_8069D424 (src/global/9DD70.c): stage 2: m2c-guided first cut, same .text size as target; prologue ordering (sub/state/mode) and register allocation differ (target keeps gfx ptr in s0, Actor* in s1, defers (u8)(u32)unk84 conversion until after the two GPLoad commands)
extern Actor *D_807FBB40;

typedef struct M2_Pos {
    u8 pad0[0x7C];
    f32 unk7C;
    f32 unk80;
} M2_Pos;

extern s16 D_80744490;
void *func_8069D358(void *, M2_Pos *, s16, f32);

typedef struct M2_Gfx {
    s32 w0;
    s32 w1;
} M2_Gfx;

extern u32 D_1000118;
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
void func_806FC530(M2_Gfx *, s16, s16, s16, s32, s32);

void func_8069D424(M2_Gfx *arg0, Actor *arg1) {
    M2_Gfx *p;
    s32 *sub;
    u8 state;
    u8 mode;
    s16 tmp;
    s16 sp54;
    s16 a2;
    s16 a3;
    f64 min;
    f64 v;
    s16 y;

    sub = arg1->unk174;
    state = 3;
    mode = (u8)(u32)arg1->unk84;
    arg0->w0 = 0xDE000000;
    arg0->w1 = (s32)&D_1000118;
    p = arg0 + 1;
    p->w0 = 0xFC119623;
    p->w1 = 0xFF2FFFFF;
    p++;

    if (((u8 *)arg1)[0x155] == 0) {
        if (arg1->unk84 == 1.0f) {
            v = (f64)arg1->unk15F * 0.0078125;
            if (v > 1.0) {
                min = 1.0;
            } else {
                min = v;
            }
            sp54 = (s16)(s32)((f64)func_806FBD5C((s16)(s32)arg1->unk84, *(s32 *)sub) * (min * 0.9) + (f64)arg1->unk7C * 0.25);
            func_807149B8(1);
            func_8071498C(&func_80717404);
            func_80714950(0xA);
            func_8071495C();
            func_80714CC0(D_8074E880[((func_80611A44() >> 0xF) % 1000) % 3], 1.0f,
                          (f32)sp54, (f32)((f64)arg1->unk80 * 0.25 + 12.0), -5.0f);
        }
        func_807040D0((s16)(arg1->unk15F * 3));
    } else if (((u8 *)arg1)[0x155] == 2) {
        func_807040D0((s16)(arg1->unk15F * 3 + 0x4000));
    } else {
        func_807040D0((s16)(arg1->unk15F * 3));
    }

    a2 = (s16)(s32)arg1->unk7C;
    a3 = (s16)(s32)arg1->unk80;
    switch (mode) {
    case 1:
        sp54 = func_806FBD5C((s16)(s32)arg1->unk84, *(s32 *)sub);
        state = 0x13;
        p = func_8069D358(p, (M2_Pos *)arg1, sp54, 0.8f);
        state &= 0xFFFE;
        a2 = sp54 * -2;
        a3 = 0;
        break;
    case 6:
        state = 0x23;
        p->w0 = 0xE3000A01;
        p->w1 = 0x100000;
        p++;
        p->w0 = 0xE200001C;
        p->w1 = 0x0C184240;
        p++;
        break;
    case 0:
        mode = 6;
        sp54 = func_806FBD5C(6, *(s32 *)sub);
        arg1->unk7C = (f32)((D_80744490 - sp54) * 2);
        p = func_8069D358(p, (M2_Pos *)arg1, sp54, 0.8f);
        state = 0;
        a2 = sp54 * -2;
        a3 = 0;
        mode = 6;
        break;
    case 10:
        mode = 6;
        p = func_8069D358(p, (M2_Pos *)arg1, 0, 0.8f);
        state = 0;
        a2 = 0;
        a3 = 0;
        mode = 6;
        break;
    }

    p->w0 = 0xFA000000;
    p->w1 = (arg1->unk16A << 24) | (arg1->unk16B << 16) | (arg1->unk16C << 8) | arg1->unk15F;
    func_806FC530(p + 1, (s16)mode, a2, a3, *(s32 *)sub, state);
}
