// func_806F8278 (src/global/FCCD0.c): stage 5: exact size; IDO lacks row0 pointer IV (addu t9,t0,a3 vs addiu t2,t2,2), uses bne not slt, regs differ; slot[arg0*15+9].unk4 tail matches
typedef struct FcASlot30 {
    u8 pad0[4];
    s16 unk4;
    u8 pad6[0x2A];
} FcASlot30;

void func_806F8278(u8 arg0) {
    s32 sum;
    u16 (*p)[0x2F];
    s32 i;
    s32 j;

    sum = 0;
    p = (u16 (*)[0x2F])((u8 *)D_807FC950 + arg0 * 0x306);
    for (i = 0; i < 14; i++) {
        for (j = 0; j < 5; j++) {
            sum += p[j][i + 0x21];
        }
    }
    ((FcASlot30 *)D_80754280)[arg0 * 15 + 9].unk4 = sum;
}
