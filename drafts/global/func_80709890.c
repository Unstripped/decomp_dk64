// func_80709890 (src/global/10E1D0.c): no note
typedef struct R1F10E1D0a_AllocView { s32 unk0, unk4; void *unk8, *unkC, *unk10, *unk14; s32 *unk18; void *unk1C, *unk20; } R1F10E1D0a_AllocView;
extern s32 D_807FD9B4;
s32 func_80610FE8(s32);
s32 func_80709890(R1F10E1D0a_AllocView *arg0, void **arg1, void **arg2, void **arg3) {
    s32 *list, *cursor, count;
    if (!arg0 || !arg1) return 0;
    D_807FD9B4 = func_80610FE8(0x708);
    arg0->unk10 = (void *)func_80610FE8(arg0->unk0 * 0x10);
    arg0->unk14 = (void *)func_80610FE8(arg0->unk0 * 0x10);
    arg0->unk8 = (u8 *)arg0 + 0x2C;
    arg0->unkC = (u8 *)arg0->unk8 + arg0->unk0 * 0xC;
    list = (s32 *)((u8 *)arg0->unkC + arg0->unk4 * 0x1C); arg0->unk18 = list;
    count = 1; cursor = list; while (*cursor) { count++; cursor++; }
    arg0->unk20 = (u8 *)list + count * 4; arg0->unk1C = (u8 *)arg0->unk20 + count * 4;
    *arg1 = arg0; if (arg2) *arg2 = arg0->unk1C; if (arg3) *arg3 = (u8 *)arg0->unk1C + count * 4;
    return 1;
}
