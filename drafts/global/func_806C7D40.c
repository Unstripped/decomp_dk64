// func_806C7D40 (src/global/CC800.c): G00: scheduling-only near miss; needs G00Block/G00Entry/G00Sub6 (CC800 copy). Diff: order of lh/sh in the 0x270..0x276 scale block and 0x27C/0x280/0x284 stores; everything else identical.
typedef struct G00Sub6 {
    /* 0x0 */ s16 unk0;
    /* 0x2 */ s16 unk2;
    /* 0x4 */ s16 unk4;
} G00Sub6;

typedef struct G00Block {
    /* 0x000 */ u8 unk0;
    /* 0x001 */ u8 pad1[3];
    /* 0x004 */ Actor *unk4;
    /* 0x008 */ u8 pad8[0x208];
    /* 0x210 */ f32 unk210;
    /* 0x214 */ f32 unk214;
    /* 0x218 */ f32 unk218;
    /* 0x21C */ f32 unk21C;
    /* 0x220 */ f32 unk220;
    /* 0x224 */ f32 unk224;
    /* 0x228 */ f32 unk228;
    /* 0x22C */ f32 unk22C;
    /* 0x230 */ f32 unk230;
    /* 0x234 */ u8 pad234[0xC];
    /* 0x240 */ f32 unk240;
    /* 0x244 */ f32 unk244;
    /* 0x248 */ f32 unk248;
    /* 0x24C */ u8 pad24C[0x24];
    /* 0x270 */ s16 unk270;
    /* 0x272 */ s16 unk272;
    /* 0x274 */ s16 unk274;
    /* 0x276 */ s16 unk276;
    /* 0x278 */ s16 unk278;
    /* 0x27A */ s16 unk27A;
    /* 0x27C */ f32 unk27C;
    /* 0x280 */ f32 unk280;
    /* 0x284 */ f32 unk284;
    /* 0x288 */ f32 unk288;
    /* 0x28C */ u8 pad28C[4];
    /* 0x290 */ s16 unk290;
    /* 0x292 */ u8 pad292[2];
    /* 0x294 */ G00Sub6 *unk294;
    /* 0x298 */ s16 *unk298;
    /* 0x29C */ s16 unk29C;
    /* 0x29E */ u8 pad29E[0x22];
    /* 0x2C0 */ u8 unk2C0;
    /* 0x2C1 */ u8 unk2C1;
    /* 0x2C2 */ u8 pad2C2[0x1A];
    /* 0x2DC */ u8 unk2DC[0xE];
    /* 0x2EA */ u8 unk2EA;
    /* 0x2EB */ u8 unk2EB;
    /* 0x2EC */ u8 pad2EC[4];
} G00Block; // size = 0x2F0

extern G00Block *D_807FC924;

typedef struct G00Entry {
    /* 0x0 */ u8 unk0;
    /* 0x1 */ u8 unk1;
    /* 0x2 */ u8 unk2;
    /* 0x3 */ u8 unk3;
    /* 0x4 */ s16 unk4;
    /* 0x6 */ s16 unk6;
    /* 0x8 */ s16 unk8;
    /* 0xA */ s16 unkA;
} G00Entry;

extern G00Entry D_80750948[];
extern u8 D_80750ABC;

typedef struct G00Player306 {
    /* 0x000 */ u8 pad0[0x2FB];
    /* 0x2FB */ s8 unk2FB;
    /* 0x2FC */ u8 pad2FC;
    /* 0x2FD */ s8 unk2FD;
    /* 0x2FE */ u8 pad2FE[8];
} G00Player306;

void *func_80610FE8(s32);
void heapClearBlock(void *);
void func_806C850C(s32, u8);
void func_80708BB8(void *);
void func_80709464(u8);
void func_806C80E4(void);
s32 actorSpawn(s32, s32);
extern G00Player306 D_807FC950[];
extern G00Sub6 D_807ECD10[];
extern s16 D_807ECD48[];
extern u32 D_8074458C[];
extern f32 D_807444C4;
extern u8 D_80750AD0;
extern u32 D_807FBB64;
extern u32 D_807FBB68;
extern u16 D_807FD570;

void func_806C7D40(s32 arg0) {
    G00Block *blk;
    s32 i;
    u8 sel;
    G00Entry *e;

    D_807FC924 = func_80610FE8(D_807FC928 * 0x2F0);
    heapClearBlock(D_807FC924);
    for (i = 0; i < D_807FC928; i++) {
        blk = &D_807FC924[i];
        blk->unk0 = 1;
        sel = i;
        D_807FC929 = i;
        func_806C850C(arg0++, sel);
        blk->unk4 = D_807FBB48;
        if (i == 0) {
            D_807FBB4C = D_807FBB48;
        }
        blk->unk218 = 100.0f;
        blk->unk214 = 100.0f;
        blk->unk210 = 100.0f;
        blk->unk224 = 100.0f;
        blk->unk220 = 100.0f;
        blk->unk21C = 100.0f;
        blk->unk230 = 0.0f;
        blk->unk22C = 0.0f;
        blk->unk228 = 0.0f;
        blk->unk248 = 0.0f;
        blk->unk240 = 0.0f;
        blk->unk244 = 1.0f;
        e = func_806C7C94(sel);
        blk->unk270 = e->unk4;
        blk->unk272 = e->unk6;
        blk->unk274 = e->unk8;
        blk->unk276 = e->unkA;
        if (osViGetCurrentMode() == D_8074458C[osTvType + osTvType]) {
            blk->unk270 *= 2;
            blk->unk274 += 1;
            blk->unk276 += 1;
            blk->unk272 *= 2;
            blk->unk274 *= 2;
            blk->unk276 *= 2;
            blk->unk274 -= 1;
            blk->unk276 -= 1;
        }
        blk->unk278 = blk->unk274 - blk->unk270;
        blk->unk27A = blk->unk276 - blk->unk272;
        blk->unk27C = 45.0f;
        blk->unk284 = 10.0f;
        blk->unk280 = (f32)blk->unk278 / (f32)blk->unk27A;
        blk->unk290 = 0;
        blk->unk294 = &D_807ECD10[i];
        blk->unk298 = &D_807ECD48[i];
        blk->unk29C = -1;
        blk->unk2C0 = 1;
        blk->unk2C1 = 1;
        blk->unk2EA = 0;
        blk->unk2EB = 0;
        blk->unk288 = D_807444C4;
        func_80708BB8(blk->unk2DC);
        if (((D_807FBB64 & 1) && !(D_807FBB68 & 2)) || (D_807FC950[i].unk2FB + D_807FC950[i].unk2FD <= 0)) {
            func_80709464(sel);
        }
    }
    if (D_807FD570 != 0) {
        func_806C80E4();
        D_807FD570 = 0;
    }
    if (D_807FC928 >= 2) {
        actorSpawn(0x13E, 0);
    }
    D_80750AD0 = (D_80750AB8 == 0) && (D_807FC928 >= 2);
}
