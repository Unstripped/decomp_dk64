// func_806524A0 (src/global/55B20.c): stage6: target masks arg1 once into s3 and re-masks andi a3,s3,0xff per call; C hoists the u8->s32 widening into s2 and emits move a3,s2. u8/s32/u32/K&R/unprototyped/local-copy variants all hoist
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
    /* 0x020 */ u8 pad20[0x68];
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
