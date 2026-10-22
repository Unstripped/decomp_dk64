// func_80689DD4 (src/global/8D3E0.c): logic matches, frame 0x18 vs 0x20 due to callee-saved float reg allocation for args
typedef struct {
    u8 unk0;
    char pad1[0x210 - 1];
    f32 unk210;
    f32 unk214;
    f32 unk218;
    char pad21C[0x2F0 - 0x21C];
} R2D3B_PlayerEntry;

extern R2D3B_PlayerEntry *D_807FC924;
extern u8 D_807FC928;

f32 func_80689DD4(f32 arg0, f32 arg1, f32 arg2) {
    f32 minDist = 100000000.0f;
    f32 z = arg2;
    f32 x = arg0;
    f32 y = arg1;
    s32 i;

    for (i = 0; i < D_807FC928; i++) {
        if (D_807FC924[i].unk0 != 0) {
            f32 dy;
            f32 dist;

            arg1 = x - D_807FC924[i].unk210;
            dy = y - D_807FC924[i].unk214;
            arg0 = z - D_807FC924[i].unk218;
            dist = (arg0 * arg0) + ((arg1 * arg1) + (dy * dy));
            if (dist < minDist) {
                minDist = dist;
            }
        }
    }
    return minDist;
}
