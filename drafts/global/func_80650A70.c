// func_80650A70 (src/global/54150.c): M54B:  func_80650A70 (src/global/54150.c) — closest diff: same 27 insns, but the  * s16 result lives in a0 and is copied to v0 at the end; expected keeps it in  * v0 (`lh v0,20(t3)` with no copy). Every declaration/return-type/if-else 
/* func_80650A70 (src/global/54150.c) — closest diff: same 27 insns, but the
 * s16 result lives in a0 and is copied to v0 at the end; expected keeps it in
 * v0 (`lh v0,20(t3)` with no copy). Every declaration/return-type/if-else
 * variation tried still colours it to a0. */
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

s16 func_80650A70(s16 arg0, s16 arg1) {
    M54B_HashGroup *group;
    s16 value;

    group = (M54B_HashGroup *)D_807F6000[hashTableLookup(arg0)].unk78;
    value = 0;
    if (group != NULL) {
        value = group->entries[arg1].unkC;
    }
    return value;
}
