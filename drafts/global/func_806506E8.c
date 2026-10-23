// func_806506E8 (src/global/54150.c): M54B:  func_806506E8 (src/global/54150.c) — closest diff: same 44 insns and frame;  * only the position of the last of the four hoisted global-address `addiu`s  * differs (expected hoists &D_807F6BE0, &D_807F6BEC, &D_807444FC, &D_807F6960 
/* func_806506E8 (src/global/54150.c) — closest diff: same 44 insns and frame;
 * only the position of the last of the four hoisted global-address `addiu`s
 * differs (expected hoists &D_807F6BE0, &D_807F6BEC, &D_807444FC, &D_807F6960
 * in that order, i.e. reverse first-use; this emits &D_807F6960 first). */
typedef struct M54B_Slot {
    s32 unk0;
    s32 unk4;
    s32 unk8;
    u8 unkC;
    u8 padD[3];
} M54B_Slot;

extern M54B_Slot D_807F6960[];
extern u32 D_807F6BE0;
extern u8 D_807F6BEC;
extern u8 D_807444FC;
void *memcpy(void *, const void *, unsigned int);

void func_806506E8(s32 arg0) {
    M54B_Slot *slot = D_807F6960;

    do {
        if (slot->unk0 == arg0 && slot->unkC == D_807444FC) {
            memcpy((void *)slot->unk8, (void *)slot->unk4, 0x40);
            slot->unk0 = 0;
            D_807F6BEC = 1;
        }
        slot++;
    } while (slot != (M54B_Slot *)&D_807F6BE0);
}
