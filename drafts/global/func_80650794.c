// func_80650794 (src/global/54150.c): M54B:  func_80650794 (src/global/54150.c) — closest diff: the float->u32 clamp tail  * differs by 2 insns. Expected: andi t2,v0,0xff / ctc1 / slti / bnez / (delay)  * andi a0,v0,0xff / li a0,15 / sll — i.e. a signed `& 0xFF` compare plus a 
/* func_80650794 (src/global/54150.c) — closest diff: the float->u32 clamp tail
 * differs by 2 insns. Expected: andi t2,v0,0xff / ctc1 / slti / bnez / (delay)
 * andi a0,v0,0xff / li a0,15 / sll — i.e. a signed `& 0xFF` compare plus a
 * *second, non-CSE'd* andi for the selected value. Every form tried collapses
 * them into one andi + move. */
typedef struct M54A_HashSlot {
    u8 pad0[0x24];
    u8 *unk24;
    u8 pad28[0x50];
    u8 *unk78;
    u8 pad7C[0x14];
} M54A_HashSlot;

typedef struct M54B_HashEntry {
    u8 *unk0;
    f32 unk4;
    s16 unk8;
    s16 unkA;
    s16 unkC;
    u8 unkE;
    u8 unkF;
    u8 unk10;
    s8 unk11;
    u8 unk12;
    u8 unk13;
} M54B_HashEntry;

typedef struct M54B_HashGroup {
    u8 *unk0;
    u8 *unk4;
    M54B_HashEntry entries[1];
} M54B_HashGroup;

extern M54A_HashSlot *D_807F6000;
s32 hashTableLookup();

void func_80650794(s16 arg0, s16 arg1, u8 arg2, f32 arg3) {
    M54B_HashGroup *group;
    M54B_HashEntry *entry;
    u32 value;
    u32 level;

    group = (M54B_HashGroup *)D_807F6000[hashTableLookup(arg0)].unk78;
    if (group != NULL) {
        entry = &group->entries[arg1];
        value = (u32)(8.0f * arg3);
        level = (value & 0xFF) < 0x10 ? (value & 0xFF) : 0xF;
        entry->unk13 = (level << 4) + arg2;
    }
}
