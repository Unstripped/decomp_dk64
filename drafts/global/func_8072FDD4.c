// func_8072FDD4 (src/global/133A90.c): stage 6: ptr form (no sub local) fixes lw order; only swap left: 0.0 double const in f12 vs prev in f2 (target const f2, prev f12). uopt colours f-candidates by index order: prev (M var, idx14) before the 0.0 constant (idx45); dead ifs/locals/orderings/types did not move it.
typedef struct H1ProxSub {
    u8 pad0[4];
    f32 unk4;
    u8 pad8[0x14];
} H1ProxSub;

typedef struct H1ProxNode {
    u8 pad0[7];
    u8 unk7;
    u8 pad8[0x2C];
    H1ProxSub *unk34;
} H1ProxNode;

void func_8072FDD4(H1ProxNode *arg0, f32 arg1, u8 *arg2, f32 *arg3) {
    u8 i;
    f32 rem;
    f32 prev;

    rem = arg1;
    i = 0;
    do {
        prev = rem;
        rem -= arg0->unk34[i++].unk4;
    } while (rem > 0.0 && i < arg0->unk7);
    i--;
    *arg2 = i;
    *arg3 = prev / arg0->unk34[i].unk4;
}
