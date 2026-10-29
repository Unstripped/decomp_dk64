// func_8071ABDC (src/global/11BC10.c): stage 3: frame 0xC0 matches with unused 128-byte matrix buffer; sh at 0x2C, swc1 at 0x38 and 0x30 match, sp24 sits at 0x28 vs target 0x24
typedef struct {
    f32 unk0;
    f32 unk4;
    f32 unk8;
    f32 unkC;
} Fx11BE2_AbdcMotion;

typedef struct {
    u8 pad0[0x340];
    f32 unk340;
    f32 unk344;
    f32 unk348;
    u8 pad34C[2];
    s16 unk34E;
    u8 pad350[0xC];
    s32 unk35C;
    u8 pad360[0xD];
    u8 unk36D;
    u8 pad36E[0x16];
    Fx11BE2_AbdcMotion *unk384;
} Fx11BE2_ActorABDC;

s32 collisionCheckGroundAtPoint(f32, f32, f32 *);
f32 sinApprox(f32);
f32 cosApprox(f32);
u32 func_806119A0(void);
void *func_80610FE8(s32);

void func_8071ABDC(Fx11BE2_ActorABDC *arg0, s8 *arg1) {
    f32 sp80[4][4];
    f32 sp40[4][4];
    f32 pad3C;
    f32 sp38;
    f32 pad34;
    f32 sp30;
    s16 pad_s, sp2C;
    f32 sp24;

    if (arg0->unk384 == NULL) {
        arg0->unk384 = func_80610FE8(0x10);
        sp2C = (s16) ((arg0->unk35C >> 16) & 0xFF);
        if (sp2C == 0) {
            arg0->unk384->unk0 = (f32) (((f64) (f32) ((func_806119A0() / 10000U) % 100U) / 20.0) - 2.5);
        } else {
            arg0->unk384->unk0 = (f32) (((f64) (f32) ((func_806119A0() / 10000U) % 100U) / 10.0) - 2.5);
        }
        sp24 = (f32) ((arg0->unk35C & 0xFFFF) * 30) * 0.017453292f;
        sp38 = (f32) ((f64) sinApprox(sp24) * 2.5);
        arg0->unk384->unk8 = (f32) ((f64) cosApprox(sp24) * 2.5);
        arg0->unk384->unk4 = sp38;
        if (sp2C == 1) {
            arg0->unk384->unk4 *= 2.0f;
            arg0->unk384->unk8 *= 2.0f;
        } else if (sp2C == 2) {
            arg0->unk384->unk4 *= 4.0f;
            arg0->unk384->unk8 *= 4.0f;
        }
        sp30 = arg0->unk344;
        if (collisionCheckGroundAtPoint(arg0->unk340, arg0->unk348, &sp30) != 0) {
            arg0->unk384->unkC = sp30;
        } else {
            arg0->unk384->unkC = 0.0f;
        }
    }
    if (arg0->unk34E >= 9) {
        arg0->unk384->unk0 = (f32) ((f64) arg0->unk384->unk0 - 0.63);
        arg0->unk384->unk4 = (f32) ((f64) arg0->unk384->unk4 * 0.9);
        arg0->unk384->unk8 = (f32) ((f64) arg0->unk384->unk8 * 0.9);
    }
    if (arg0->unk34E >= (s16) ((arg0->unk35C >> 24) & 0xFF)) {
        if (arg0->unk36D >= 0x3C) {
            arg0->unk36D -= 0x3C;
        } else {
            arg0->unk36D = 0;
        }
    }
    arg0->unk340 += arg0->unk384->unk4;
    arg0->unk348 += arg0->unk384->unk8;
    arg0->unk344 += arg0->unk384->unk0;
    if (arg0->unk344 < arg0->unk384->unkC) {
        *arg1 = 1;
    }
}
