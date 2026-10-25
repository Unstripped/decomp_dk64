// func_806F9B64 (src/global/FCCD0.c): stage 3: `s4 = slot + 0x28` setup matches; frame 0x80 vs 0x78 and swapped loop array registers (removing the payload temp fixed the frame but broadened the diff)
typedef struct R1FCCD0bSlot {
    u8 pad0[8];
    s32 unk8;
    s32 unkC;
    u8 pad10[0x18];
    R1FCCD0bAllocRecord *unk28;
    u8 pad2C[4];
} R1FCCD0bSlot;

typedef struct R1FCCD0bMatrixPayload {
    s32 unk0;
    s32 unk4;
} R1FCCD0bMatrixPayload;

extern R1FCCD0bSlot *D_80754280;
extern void *D_80750518[];
extern f32 D_807FD7A0[];

void func_806F9AF0(void *, s8 *);

void func_806F9B64(s32 arg0) {
    s32 sp64;
    f32 *var_s1;
    void **var_s2;
    s32 var_s0;
    R1FCCD0bSlot *temp_s4;
    R1FCCD0bMatrixPayload *temp_v0;

    temp_s4 = &D_80754280[arg0];
    sp64 = arg0 * 0x30;
    func_806F966C(&temp_s4->unk28);
    func_806F96CC((R1FCCD0bEffect *)temp_s4->unk28, 0);
    *(s16 *)((u8 *)temp_s4->unk28 + 0x10) = 0;
    temp_v0 = temp_s4->unk28->unk14;
    temp_v0->unk0 = ((R1FCCD0bSlot *)((u8 *)D_80754280 + sp64))->unk8 + 0x14;
    temp_v0->unk4 = ((R1FCCD0bSlot *)((u8 *)D_80754280 + sp64))->unkC - 0x14;
    var_s2 = D_80750518;
    var_s1 = D_807FD7A0;
    var_s0 = 0;
    do {
        func_8071495C();
        func_807149FC(-1);
        func_8071498C((void (*)(void))func_806F9AF0);
        func_80714950((void *)var_s0);
        *var_s1 = -100.0f;
        func_80714CC0((s32)*var_s2, 1.0f, -200.0f, 0.0f, -10.0f);
        var_s0++;
        var_s1++;
        var_s2++;
    } while (var_s0 != 5);
}
