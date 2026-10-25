// func_806CEB44 (src/global/CEAE0.c): G05 stage 6: selector/ret now in v1 (s32 ret = G05_P->unk4C; switch(ret); default ret=1; return ret) and all else matches (li v1,1 delay, layout); only diff: target has plain bc1t/bc1f with nop delays sharing 'jr ra; move v0,v1' while ours emits bc1tl/bc1fl with duplicated move and li v1,1 not in b delay slot. Variant with no trailing return and 'return ret;' at end of default gives plain bc1t + li in b delay (exact layout) but ret lands in v0 (no move tail). Tried: if-chain, goto end, per-case returns, ret/sel copy, s16/u32/s8 ret, int return, comma/dead returns.
typedef struct G05PlayerView {
    /* 0x000 */ s16 unk0;
    /* 0x002 */ u8 pad2[0x4C - 2];
    /* 0x04C */ s16 unk4C;
    /* 0x04E */ u8 pad4E[0x78 - 0x4E];
    /* 0x078 */ f32 unk78;
    /* 0x07C */ f32 unk7C;
    /* 0x080 */ s16 unk80;
    /* 0x082 */ u8 pad82[2];
    /* 0x084 */ u32 unk84;
    /* 0x088 */ u8 pad88[0xD0 - 0x88];
    /* 0x0D0 */ u32 unkD0;
    /* 0x0D4 */ u8 padD4[0x1AC - 0xD4];
    /* 0x1AC */ Actor *unk1AC;
    /* 0x1B0 */ Actor *unk1B0;
    /* 0x1B4 */ u8 pad1B4[4];
    /* 0x1B8 */ u16 unk1B8;
    /* 0x1BA */ u8 pad1BA[2];
    /* 0x1BC */ f32 unk1BC;
} G05PlayerView;

#define G05_P ((G05PlayerView *)D_807FD580)

extern f32 D_807532B8[];

s32 func_806CEB44(f32 arg0, f32 arg1) {
    s32 ret = G05_P->unk4C;

    switch (ret) {
        case 0:
            if (arg1 != 0.0f) {
                return 1;
            }
            break;
        case 1:
            if (arg1 == 0.0f && arg0 < D_807532B8[D_807FD584]) {
                return 0;
            }
            break;
        default:
            ret = 1;
            if (arg0 < D_807532B8[D_807FD584]) {
                return 0;
            }
            break;
    }
    return ret;
}
