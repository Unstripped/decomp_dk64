// func_8065D1AC (src/global/61AA0.c): 3 insns diff: s3,s2,s0 addiu setup order
typedef struct {
    s32 unk0;
    s16 unk4;
    s16 unk6;
    void *unk8;
} R1A_Struct807F8E90;

extern R1A_Struct807F8E90 D_807F8E90[4];
extern s8 D_807F8E88;
extern s32 D_8076A064;
extern s32 D_807F8EC0;

void assetFreeBuffer(void *, s32, s32);

void func_8065D1AC(void) {
    R1A_Struct807F8E90 *var_s0;

    D_807F8E88 = 0;
    var_s0 = D_807F8E90;
    do {
        if (var_s0->unk0 != -1 && (u32)(D_8076A064 - var_s0->unk0) >= 21) {
            assetFreeBuffer(var_s0->unk8, 0x65, 0x4D);
            var_s0->unk0 = -1;
        }
    } while (++var_s0 != (R1A_Struct807F8E90 *)&D_807F8EC0);
}
