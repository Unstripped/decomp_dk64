// func_8065054C (src/global/54150.c): M54B:  func_8065054C (src/global/54150.c) — closest diff: 3 insns short (0x98 vs  * 0xa4). Expected computes the initial slot address with an *unfolded* index  * shift (sll t6,$zero,4; addu v0,t6,t7) and rematerialises the table base on 
/* func_8065054C (src/global/54150.c) — closest diff: 3 insns short (0x98 vs
 * 0xa4). Expected computes the initial slot address with an *unfolded* index
 * shift (sll t6,$zero,4; addu v0,t6,t7) and rematerialises the table base on
 * the store path (lui/addiu/addu) instead of keeping it live across the loop.
 * Permuter best 490 (baseline 681) by introducing a dummy non-constant index;
 * a semantics-preserving form was not found. Loop body/rotation and the two
 * duplicate `addiu v1,v1,1` (dead copy) already match exactly. */
typedef struct M54B_Slot {
    s32 unk0;
    s32 unk4;
    s32 unk8;
    u8 unkC;
    u8 padD[3];
} M54B_Slot;

extern M54B_Slot D_807F6960[];
extern u32 D_807F6BE0;
extern u8 D_807444FC;
void faultSetMessage(s32, s32, s32, s32);

void func_8065054C(s32 arg0, s32 arg1, s32 arg2) {
    s32 found;
    s32 i;
    M54B_Slot *slot;

    found = 0;
    i = 0;
    slot = &D_807F6960[0];
    do {
        if (slot->unk0 == 0) {
            found = 1;
        } else {
            i++;
            slot++;
        }
    } while (found == 0 && i < 0x28);

    if (found != 0) {
        slot = &D_807F6960[i];
        slot->unk0 = arg0;
        slot->unk4 = arg1;
        slot->unk8 = arg2;
        slot->unkC = D_807444FC ^ 1;
        return;
    }
    faultSetMessage(0xB, 0, 0, 0);
}
