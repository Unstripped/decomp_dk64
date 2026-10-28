// func_800313B8 (src/arcade/0.c): Stage 4: same frame/insn flow, only D_8004BCD0 address CSE differs: target (2) idx ptr = lui/addiu t8 + addu index-first, player load D_8004BCD0[D_8004C71F].unk0 folded as lui at/addu/lwc1 lo(at); mine hoists one base (lui a1/addiu before the r>=4 branch) shared by both (-3 insns). Tried: ptr local, f32 temp for player x, cast/alias forms, (s32)&sym, u8* arithmetic, block extern, clamp forms, permuter 4 min.
extern ArcadeEntity D_8004A3D8;
extern s32 D_8004A318[][2];

void func_800313B8(void) {
    u8 idx;
    u8 r;

    if (D_8004C6DC % 200 == 0 && arcadeCountEntitiesByType(2) < 5) {
        idx = arcadeFindFreeEntityAfterPlayer();
        D_8004BCD0[idx] = D_8004A3D8;
        D_8004BCD0[idx].unk1A = 0;
        D_8004BCD0[idx].unk8 = -0.5f;
        D_8004BCD0[idx].unk0 = 244.0f;
        r = arcadeRand() & 7;
        if (r >= 4) {
            r = 1;
        }
        D_8004BCD0[idx].unk0 = D_8004A318[r][0];
        D_8004BCD0[idx].unk4 = D_8004A318[r][1];
        if (160.0f < D_8004BCD0[D_8004C71F].unk0) {
            D_8004BCD0[idx].unk0 = 320.0f - D_8004BCD0[idx].unk0;
            D_8004BCD0[idx].unk1A = 1 - D_8004BCD0[idx].unk1A;
            D_8004BCD0[idx].unk8 = -D_8004BCD0[idx].unk8;
        }
    }
    if (D_8004C718 == 0) {
        arcadeStopSound(0);
        D_8004C718 = 1;
        D_8004C708 = 1;
        D_8004C71D = 2;
        D_8004BCE9[arcadeFindEntityByType(0x17) << 5] = 8;
    }
}
