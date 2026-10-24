// func_8069A750 (src/global/9DD70.c): parked NON_MATCHING: two no-op beq tests (==2/==3 -> loop condition) folded away (30 vs 22)
extern u8 D_807FBBA9;

s32 func_8069A750(void) {
    Actor **list = (Actor **)((u8 *)&D_807FBB70 + 0x7C);
    s32 i;

    for (i = 0; i < D_807FBBA9; i++) {
        if (list[i]->unk58 != 2 && list[i]->unk58 != 3) {
            continue;
        }
    }
    if (D_807FBB40->unk58 == 0x1F) {
        return 0;
    }
    return 0;
}
