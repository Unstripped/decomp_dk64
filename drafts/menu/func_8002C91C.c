// func_8002C91C (src/menu/3E10.c): stage 5 (parked NON_MATCHING): same frame 0x50 and s0-s7 saved set; remaining diff: loop-1 hoisted lui order (target hoists D_8003387C first into a0, mine last into a2; a0 stays unused in mine and 'move s7,a0' is scheduled after the luis instead of first), then temp numbering. Variants tried: pointer loop, for loop (best, 1030), s8/s32 counter, named temp t, explicit call args (worse).
extern u8 D_80033878;
extern u8 D_80033F20[];
extern s16 D_80744524[];
extern s8 D_8076A105;
extern u8 D_8003387C[];
extern u8 D_80033F24[];

void func_8002C91C(void *arg0, s32 arg1) {
    Menu3A_Struct174 *sp4C = *(Menu3A_Struct174 **)((u8 *)arg0 + 0x174);
    s32 i;
    s8 t;
    Menu6_Sub174 *sub;

    for (i = 0; i < 4; i++) {
        t = D_8076A0E4[i];
        if (!(t & 0x80)) {
            D_8003387C[D_80033878] = t & 0x7F;
            D_80033F20[D_80033878] = i;
            D_80033F24[i] = D_80033878;
            if (D_8076A105 == D_80033878) {
                D_80744524[i] += 1;
            }
            D_80033878 += 1;
        }
    }
    menuUpdateCameraPositions();
    sp4C->unk17 = 0;
    i = 0;
    if (D_80033878 > 0) {
        do {
            actorSpawn(0x151, D_8003386C[D_8003387C[i]]);
            {
                s16 *q = Menu6_A->unk17C;
                *q = D_8003386C[D_8003387C[i]];
            }
            Menu6_A->unk154 = D_80033F20[i] | 0x80;
            Menu6_A->unk155 = D_8003387C[i];
            sub = Menu6_A->unk174;
            sub->unk0 = arg0;
            sub->unk8 = (i == D_8076A105) + 1;
            i += 1;
        } while (i < D_80033878);
    }
    func_80030894(sp4C, &D_80720CF0, 0x122, 0xD2, 0.75f, 2, 0);
}
