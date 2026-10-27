// func_80027BE8 (src/jetpac/3480.c): stage 4->5, parked NON_MATCHING: frame 0x68 and sp58 at 0x58 right (decl order x,y,inner,sp58,i,p; sp58 init before inner; sp58 must be struct field J3Color.g so sb is a direct frame store). Only diff: arg1(fp) spills because uopt allocates const-8/2 + hi(D_8002F3C0) lui-hoist before arg1 (adjsave -0.5); target keeps arg1 in fp and no hoist.
typedef struct {
    void *frame;
    s32 unk4;
    s32 unk8;
    s32 unkC;
    s32 unk10;
    s32 unk14;
} JetpacSprite;

typedef struct {
    JetpacSprite *sprites[2];
    f32 unk8;
    f32 unkC;
    u8 pad10[0x1C - 0x10];
    s32 unk1C;
    u8 pad20[4];
    s32 unk24;
    s32 unk28;
    s32 unk2C;
    s32 unk30;
    u8 pad34[4];
    s32 unk38;
    u8 pad3C[4];
    s32 unk40;
    u8 pad44[4];
    void (*unk48)(void *, s32);
} JetpacItem;

typedef struct {
    u8 pad0[0xC];
    s32 unkC;
    u8 pad10[0x14 - 0x10];
    JetpacItem items[4];
    u8 pad144[4];
    u8 unk148;
    u8 pad149[0x190 - 0x149];
    void (*unk190)(void *, s32);
} JetpacInner;

void func_80025700(void *, s32, s32, void *, s32);

typedef struct {
    u8 pad0[0x344];
    s32 unk344;
} JetpacGlobal;

extern JetpacGlobal D_8002EC30;

typedef struct {
    u8 r;
    u8 g;
    u8 b;
    u8 a;
} J3Color;

extern s32 D_8002DCE8;
extern s32 D_8002F3C0;
f32 jetpacRoundFloat(f32);

void func_80027BE8(JetpacItem *arg0, s32 arg1) {
    s32 x;
    s32 y;
    JetpacInner *inner;
    J3Color sp58;
    s32 i;
    JetpacSprite **p;

    *(s32 *)&sp58 = D_8002DCE8;
    inner = (JetpacInner *)((u8 *)&D_8002EC30 + D_8002EC30.unk344 * 0x194 + 0x1C);
    if (arg0->unk1C >= 2) {
        x = (s32)arg0->unk8;
        y = (s32)jetpacRoundFloat(arg0->unkC);
        if (arg1 < 3) {
            p = arg0->sprites;
            for (i = 0; i != 2; i++, p++, y += 8) {
                if ((inner->unkC < 8 && inner->unkC + arg1 * 2 + i >= 8) || (inner->unkC == 8 && (D_8002F3C0 & 0x10))) {
                    sp58.g = 0;
                }
                if (*p != NULL) {
                    func_80025700(*p, x, y, &sp58, *(s32 *)((u8 *)arg0 + 0x20));
                }
            }
        } else {
            func_80025700(arg0->sprites[0], x, y, (u8 *)arg0 + 0x18, *(s32 *)((u8 *)arg0 + 0x20));
        }
    }
}
