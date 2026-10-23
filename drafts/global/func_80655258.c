// func_80655258 (src/global/55B20.c): stage6: instruction sequence identical, temp-register numbering shifted (t2/t3..), 'sw s0' prologue slot + 'move s0,zero' placement differ; tried init/decl order variations
typedef struct M55P4Cell {
    s16 unk0;
    s16 unk2;
    s16 unk4;
    u8 pad6[0x12];
    u8 unk18;
    u8 unk19;
    u8 pad1A[2];
} M55P4Cell;

typedef struct M55P4Hit {
    s16 unk0;
    s16 unk2;
    s16 unk4;
    s16 unk6;
    s16 unk8;
    s16 unkA;
} M55P4Hit;

typedef struct M55P3EffectBuf {
    u8 unk0;
    u8 pad1[0x87];
} M55P3EffectBuf;

extern s32 D_807F70AC;
extern s32 D_807F70B0;
extern s32 D_807F70B4;
extern M55P3EffectBuf *D_807F6C18;
extern f32 D_807F5FAC;

s32 func_8062DBDC(s16, s16, s16, s16, s16, s16, f32, f32, f32, f32, void *);

void func_80655258(f32 arg0, f32 arg1, f32 arg2, s32 arg3) {
    s32 i;
    s32 off;

    i = 0;
    off = 0;
    while (i < D_807F70AC) {
        if (arg3 == ((M55P4Cell *)((u8 *)D_807F70B0 + off))->unk4) {
            if (D_807F6C18[((M55P4Cell *)((u8 *)D_807F70B0 + off))->unk0].unk0 == 1) {
                if (func_8062DBDC(((M55P4Hit *)D_807F70B4)[((M55P4Cell *)((u8 *)D_807F70B0 + off))->unk2].unk0,
                                  ((M55P4Hit *)D_807F70B4)[((M55P4Cell *)((u8 *)D_807F70B0 + off))->unk2].unk2,
                                  ((M55P4Hit *)D_807F70B4)[((M55P4Cell *)((u8 *)D_807F70B0 + off))->unk2].unk4,
                                  ((M55P4Hit *)D_807F70B4)[((M55P4Cell *)((u8 *)D_807F70B0 + off))->unk2].unk6,
                                  ((M55P4Hit *)D_807F70B4)[((M55P4Cell *)((u8 *)D_807F70B0 + off))->unk2].unk8,
                                  ((M55P4Hit *)D_807F70B4)[((M55P4Cell *)((u8 *)D_807F70B0 + off))->unk2].unkA,
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
    }
}
