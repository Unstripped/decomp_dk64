// func_80652BC8 (src/global/55B20.c): stage 5: full logic matches; frame 0x80 vs 0x78, mode u8 slot 0x6F vs 0x6E, ptr slot 0x68 vs 0x74, setup insn order; args f32 in a1/a2/a3 confirmed (slot>=1 int regs here)
typedef struct M55P3Node {
    /* 0x00 */ u8 pad0[0x14];
    /* 0x14 */ struct M55P3Node *unk14;
    /* 0x18 */ u8 pad18[6];
    /* 0x1E */ s16 unk1E;
    /* 0x20 */ u8 pad20[4];
    /* 0x24 */ u8 unk24;
} M55P3Node;

extern u16 func_80630324(s32, s32);
extern s32 func_80668E9C(s32, s16, f32, f32, f32, s32);

s32 func_80652BC8(s32 arg0, f32 arg1, f32 arg2, f32 arg3, s32 arg4) {
    s32 result;
    s32 count;
    s32 off;
    s16 x;
    s16 y;
    u8 mode;
    void *ptr;
    M55P3Node *node;
    M55P3EffectBuf *eff;

    result = 0;
    mode = func_80630324(1, 0);
    count = 0;
    if (D_807F6C28 > 0) {
        off = 0;
        x = (s16)(s32)(arg1 * 6.0f);
        node = ptr;
        do {
            eff = (M55P3EffectBuf *)((u8 *)D_807F6C18 + off);
            if ((x >= eff->unk80 - 0x32) &&
                ((y = (s16)(s32)(arg2 * 6.0f)) >= eff->unk82 - 0x32) &&
                (eff->unk84 + 0x32 >= x) &&
                (eff->unk86 + 0x32 >= y)) {
                switch (mode) {
                case 0:
                    node = (M55P3Node *)eff->unk14;
                    break;
                case 1:
                    node = (M55P3Node *)eff->unk1C;
                    break;
                }
                if (node != NULL) {
                    do {
                        if (node->unk24 == 1) {
                            result = (result | func_80668E9C(arg0, node->unk1E, arg1, arg2, arg3, arg4)) & 0xFF;
                        }
                        node = node->unk14;
                    } while (node != NULL);
                }
            }
            count++;
            off += 0x1C8;
        } while (count < D_807F6C28);
        ptr = node;
    }
    return result;
}
