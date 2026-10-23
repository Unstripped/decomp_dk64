// func_806524A0 (src/global/55B20.c): stage 6, regalloc only: target keeps arg1 masked once in s3 and re-masks with andi a3,s3,0xff at each call; draft CSEs the u8 conversion into s2 and emits move a3,s2 (1 instruction shorter, s2/s3 roles swapped). Tried: u8/s32/s8 arg1, explicit (u8)/&0xFF casts, K&R definition, local copies, permuter 560s
typedef struct M55P3EffectBuf {
    /* 0x000 */ u8 unk0;
    /* 0x001 */ u8 unk1;
    /* 0x002 */ u8 unk2;
    /* 0x003 */ u8 unk3;
    /* 0x004 */ u8 unk4;
    /* 0x005 */ u8 pad5[0x1];
    /* 0x006 */ u8 unk6;
    /* 0x007 */ u8 unk7;
    /* 0x008 */ u8 pad8[0xC];
    /* 0x014 */ s32 unk14;
    /* 0x018 */ u8 pad18[0x4];
    /* 0x01C */ s32 unk1C;
    /* 0x020 */ u8 pad20[0x4];
    /* 0x024 */ s32 unk24;
    /* 0x028 */ u8 pad28[0x40];
    /* 0x068 */ s32 unk68;
    /* 0x06C */ s32 unk6C;
    /* 0x070 */ s32 unk70;
    /* 0x074 */ s32 unk74;
    /* 0x078 */ u32 unk78;
    /* 0x07C */ u32 unk7C;
    /* 0x080 */ s16 unk80;
    /* 0x082 */ s16 unk82;
    /* 0x084 */ s16 unk84;
    /* 0x086 */ s16 unk86;
    /* 0x088 */ u8 pad88[0x140];
} M55P3EffectBuf;

extern s32 D_807F6C28;
extern M55P3EffectBuf *D_807F6C18;
void func_806307CC(s32, s32, s32, s32, u8 *);

void func_806524A0(s32 arg0, u8 arg1) {
    u8 flag;
    s32 i;

    flag = 0;
    for (i = 0; i < D_807F6C28 && !flag; i++) {
        func_806307CC(D_807F6C18[i].unk14, arg0, 0, arg1, &flag);
        if (!flag) {
            func_806307CC(D_807F6C18[i].unk1C, arg0, 0, arg1, &flag);
        }
    }
}
