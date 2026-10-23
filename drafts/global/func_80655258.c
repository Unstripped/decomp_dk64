// func_80655258 (src/global/55B20.c): stage6: instruction-identical; only 'move s0,zero' (off=0) lands one slot earlier (after lui chain, before addiu chain) in the preheader. guarded do-while form + box local gets closest
typedef struct M55P4Cell {
    /* 0x00 */ s16 unk0;
    /* 0x02 */ s16 unk2;
    /* 0x04 */ s16 unk4;
    /* 0x06 */ u8 pad6[0x12];
    /* 0x18 */ u8 unk18;
    /* 0x19 */ u8 unk19;
    /* 0x1A */ u8 pad1A[0x2];
} M55P4Cell;

typedef struct M55P2BoxEntry {
    /* 0x00 */ s16 unk0;
    /* 0x02 */ s16 unk2;
    /* 0x04 */ s16 unk4;
    /* 0x06 */ s16 unk6;
    /* 0x08 */ s16 unk8;
    /* 0x0A */ s16 unkA;
} M55P2BoxEntry;

extern s32 D_807F70AC;
extern struct M55P2SearchEntry *D_807F70B0;
extern struct M55P2BoxEntry *D_807F70B4;
extern M55P3EffectBuf *D_807F6C18;
extern f32 D_807F5FAC;

s32 func_8062DBDC(s16, s16, s16, s16, s16, s16, f32, f32, f32, f32, void *);

void func_80655258(f32 arg0, f32 arg1, f32 arg2, s32 arg3) {
    s32 i;
    M55P2BoxEntry *box;
    s32 off;

    i = 0;
    if (D_807F70AC > 0) {
        off = 0;
        do {
            if (arg3 == ((M55P4Cell *)((u8 *)D_807F70B0 + off))->unk4) {
                if (D_807F6C18[((M55P4Cell *)((u8 *)D_807F70B0 + off))->unk0].unk0 == 1) {
                    box = (M55P2BoxEntry *)D_807F70B4;
                    if (func_8062DBDC(box[((M55P4Cell *)((u8 *)D_807F70B0 + off))->unk2].unk0,
                                      box[((M55P4Cell *)((u8 *)D_807F70B0 + off))->unk2].unk2,
                                      box[((M55P4Cell *)((u8 *)D_807F70B0 + off))->unk2].unk4,
                                      box[((M55P4Cell *)((u8 *)D_807F70B0 + off))->unk2].unk6,
                                      box[((M55P4Cell *)((u8 *)D_807F70B0 + off))->unk2].unk8,
                                      box[((M55P4Cell *)((u8 *)D_807F70B0 + off))->unk2].unkA,
                                      arg0, arg1, arg2, D_807F5FAC,
                                      (u8 *)&D_807F6C18[((M55P4Cell *)((u8 *)D_807F70B0 + off))->unk0] + 0x88) != 0) {
                        ((M55P4Cell *)((u8 *)D_807F70B0 + off))->unk18 = 1;
                        ((M55P4Cell *)((u8 *)D_807F70B0 + off))->unk19 = 1;
                    }
                    if (((M55P4Cell *)((u8 *)D_807F70B0 + off))->unk18 != 0) {
                        func_80655258(arg0, arg1, arg2, ((M55P4Cell *)((u8 *)D_807F70B0 + off))->unk2);
                    }
                }
            }
            i++;
            off += 0x1C;
        } while (i < D_807F70AC);
    }
}
