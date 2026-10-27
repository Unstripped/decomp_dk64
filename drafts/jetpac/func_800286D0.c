// func_800286D0 (src/jetpac/3480.c): stage 5, parked NON_MATCHING: frame 0x30 ok (needs 6 locals: i,item,spd,y,t,pad); remaining FP register numbering: target keeps y in f12, t in f0, 0.0 in f2, 1.0 in f14; mine f0/f2/f14/f16. D_80770DF8[1] vs D_80770DFC is reloc only.
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

typedef struct {
    u8 pad0[0x344];
    s32 unk344;
} JetpacGlobal;

extern JetpacGlobal D_8002EC30;

extern s32 D_80770DF8[];
void func_80024E70(s32);
void func_80024F24(s32, f32);
void func_80024F64(s32);
void func_80024F9C(s32);
void func_800250A0(void);

void func_800286D0(void) {
    s32 i;
    JetpacItem *item;
    f32 spd;
    f32 y;
    f32 t;
    s32 pad;

    item = (JetpacItem *)((u8 *)&D_8002EC30 + D_8002EC30.unk344 * 0x194 + 0x30);

    y = item->unkC;
    t = (y - -8.0f) / 144.0f;
    t = (t < 0.0f) ? 0.0f : ((t > 1.0f) ? 1.0f : t);

    if (*(s32 *)((u8 *)&D_8002EC30 + 0x78C) == 1) {
        if (D_80770DF8[1] == 0) {
            func_80024E70(1);
        }
        func_80024F24(1, 1.0f - t * 0.059466f);
        y = item->unkC;
        if (y >= 136.0f) {
            for (i = 0; i < 3; i++) {
                item[i].unk8 = 168.0f;
                item[i].unkC = (f32)(i * 16) + 136.0f;
            }
            func_80024F64(1);
            func_80024F9C(2);
            return;
        }
        spd = 0.4f;
    } else if (*(s32 *)((u8 *)&D_8002EC30 + 0x78C) == 4) {
        if (D_80770DF8[0] == 0) {
            func_80024E70(0);
        }
        t = 1.0f - t;
        func_80024F24(0, t * 0.059466f + 1.0f);
        y = item->unkC;
        if (y < -8.0f) {
            func_80024F64(0);
            func_800250A0();
            return;
        }
        spd = -0.4f;
    }

    t = y + spd;
    for (i = 0; i < 3; i++) {
        item[i].unkC = t;
        t += 16.0f;
    }
}
