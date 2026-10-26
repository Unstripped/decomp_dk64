// func_80613448 (src/global/17B90.c): stage 4; permuter best 140; remaining state-table loop register allocation and scheduling
typedef struct { u16 unk0; u16 unk2; s32 unk4; s32 unk8; } Perm3StateEntry;
extern Perm3StateEntry D_807FB630[];
extern s16 D_807FBB30;

u16 func_80613448(u32 *arg0) {
    u16 var_v1;
    Perm3StateEntry *var_a0;

    var_v1 = (u16)D_807FBB30;
    if ((s32)var_v1 >= 0) {
        var_a0 = &D_807FB630[var_v1];
        do {
            if (*arg0 == (u32)var_a0->unk4) {
                break;
            }
            var_v1--;
            var_a0--;
        } while ((s32)var_v1 >= 0);
    }
    if ((s32)var_v1 >= 0) {
        return D_807FB630[var_v1].unk0;
    }
    return 0;
}
