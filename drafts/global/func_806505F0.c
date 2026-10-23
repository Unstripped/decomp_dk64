// func_806505F0 (src/global/54150.c): M54B:  func_806505F0 (src/global/54150.c) — closest diff: identical instruction  * sequence and count (38 lines, 0x94); only the slot pointer / end pointer  * registers are swapped (expected slot=v1, end=v0; this gives slot=v0, 
/* func_806505F0 (src/global/54150.c) — closest diff: identical instruction
 * sequence and count (38 lines, 0x94); only the slot pointer / end pointer
 * registers are swapped (expected slot=v1, end=v0; this gives slot=v0,
 * end=v1). `for (;;) ... break` is required to stop IDO's 8x loop unroller. */
typedef struct M54B_Slot {
    s32 unk0;
    s32 unk4;
    s32 unk8;
    u8 unkC;
    u8 padD[3];
} M54B_Slot;

extern M54B_Slot D_807F6960[];
extern u32 D_807F6BE0;

void func_806505F0(s32 arg0) {
    M54B_Slot *slot = D_807F6960;

    for (;;) {
        if (slot->unk0 != 0 && slot->unk8 == arg0) {
            slot->unk0 = 0;
        }
        if (slot[1].unk0 != 0 && slot[1].unk8 == arg0) {
            slot[1].unk0 = 0;
        }
        if (slot[2].unk0 != 0 && slot[2].unk8 == arg0) {
            slot[2].unk0 = 0;
        }
        if (slot[3].unk0 != 0 && slot[3].unk8 == arg0) {
            slot[3].unk0 = 0;
        }
        slot += 4;
        if (slot == (M54B_Slot *)&D_807F6BE0) {
            break;
        }
    }
}
