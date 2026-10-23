// func_80650E20 (src/global/55B20.c): near miss; regalloc/scheduling stage
typedef struct M55P1_Unk80650E20 {
    /* 0x000 */ u8 pad0[0x64];
    /* 0x064 */ s32 unk64;
} M55P1_Unk80650E20;

s32 func_80610FE8(s32);
extern s32 D_807F6C28;
extern s32 D_8076A0B4;
extern s32 D_8076A0B8;
extern s32 D_8076A0BC;
extern s32 D_8076A0C0;
extern s32 D_8076A0C4;
extern s32 D_8076A0C8;

void func_80650E20(M55P1_Unk80650E20 *arg0) {
    s32 temp;
    s32 count;
    s32 size;

    temp = *(s32 *)(arg0->unk64 + (u8 *)arg0);
    D_807F6C28 = temp;
    if (temp >= 2) {
        count = temp & 0xFF;
    } else {
        count = 1;
    }
    size = count * 4;
    D_8076A0B4 = func_80610FE8(size);
    D_8076A0B8 = func_80610FE8(size);
    D_8076A0BC = func_80610FE8(size);
    D_8076A0C0 = func_80610FE8(size);
    D_8076A0C4 = func_80610FE8(size);
    D_8076A0C8 = func_80610FE8(size);
}
