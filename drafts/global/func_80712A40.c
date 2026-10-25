// func_80712A40 (src/global/117190.c): Stage 2: state reset, mode-dependent timer seed, and carry-aware timer accumulation recovered; stack/register allocation differs.
typedef struct R117dTimePair {
    s32 unk0;
    u32 unk4;
} R117dTimePair;

typedef struct R117dTimedState {
    s32 unk0;
    u32 unk4;
    u8 unk8[8];
    u8 unk10;
} R117dTimedState;

extern R117dTimePair D_807445B8;
extern s32 D_807445C0;
extern u32 D_807445C4;
extern s8 D_80746B60;
extern s8 D_8075530C;
extern s8 D_80755310;
extern s32 D_80755320;
extern s8 D_80755324;
extern R117dTimedState D_80755340;
extern s32 D_807FBB60;
void func_8060B6CC(void);
void func_806119F0(u32);

void func_80712A40(void) {
    u32 sp1C;
    s32 sp18;
    s32 temp_t2;
    u32 temp_t3;
    u32 temp_t7;
    u32 temp_t9;
    u32 temp_v1;
    u64 temp_ret;

    func_8060B6CC();
    if ((D_80755318 == 3) || (D_80755318 == 4)) {
        func_806119F0(0x8E32B6F7U);
        D_80746B60 = 1;
    } else {
        func_806119F0((u32) osGetTime());
        D_80746B60 = 0;
    }
    D_8075530C = 0;
    D_80755310 = 0;
    D_80755314 = D_80755318;
    D_80755324 = 0;
    D_80755320 = 0;
    if (D_807FBB60 & 2) {
        temp_ret = osGetTime();
        temp_v1 = (u32) temp_ret;
        temp_t3 = temp_v1 - D_807445C4;
        temp_t2 = (temp_ret - D_807445C0) - (temp_v1 < (u32) D_807445C4);
        temp_t9 = D_807445B8.unk4 + temp_t3;
        sp18 = temp_t2;
        sp1C = temp_t3;
        D_807445B8.unk0 = (s32) ((temp_t9 < temp_t3) + D_807445B8.unk0 + temp_t2);
        D_807445B8.unk4 = temp_t9;
        if (D_80755340.unk10 != 0) {
            temp_t7 = D_80755340.unk4 + sp1C;
            D_80755340.unk0 = (s32) ((temp_t7 < sp1C) + D_80755340.unk0 + sp18);
            D_80755340.unk4 = temp_t7;
        }
    }
}
