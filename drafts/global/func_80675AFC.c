// func_80675AFC (src/global/7A510.c): func_80675AFC (src/global/7A510.c): stage 5, 1 insn diff: bnel operand order (t2,t0 vs t0,t2) on unk244[j]==entry->unk5 compare; needs 'if (1) found=0' and 'unkC==(two=2)' fakes + s16 two decl first; parked NON_MATCHING
typedef struct KaP2_ActorAFC {
    u8 pad0[0x5A];
    s16 unk5A;
    s16 unk5C;
} KaP2_ActorAFC;

typedef struct KaP2_InteractionEntry {
    s16 unk0;
    s16 unk2;
    s8 unk4;
    s8 unk5;
    void (*unk8)(KaP2_ActorAFC *, KaP2_ActorAFC *, s32, s32);
    u8 unkC;
} KaP2_InteractionEntry;

s32 func_80675C70(s16 arg0, s16 arg1, s16 arg2);
extern ActorGlobalState D_807FBB70;
extern KaP2_InteractionEntry D_8074ABCC[];

void func_80675AFC(KaP2_ActorAFC *arg0, KaP2_ActorAFC *arg1) {
    KaP2_InteractionEntry *entry;
    s32 done;
    s16 two;
    s32 found;
    s32 j;

    done = 0;
    entry = D_8074ABCC; do {
        if (func_80675C70(arg0->unk5A, arg0->unk5C, entry->unk0) &&
            func_80675C70(arg1->unk5A, arg1->unk5C, entry->unk2) &&
            ((entry->unk4 == -1) || entry->unk4 == D_807FBB70.unk200)) {
            if (entry->unk5 != -1) {
                if (1) {  // FAKE: extra block lowers D_807FBB70 const priority vs arg1 (s0/s1 swap)
                    found = 0;
                }
                for (j = 0; !found && j < D_807FBB70.unk201;) {
                    if (arg1 == (KaP2_ActorAFC *)D_807FBB70.unk204[j] && D_807FBB70.unk244[j] == entry->unk5) {
                        found = 1;
                    } else {
                        j++;
                    }
                }
            } else {
                found = 1;
            }
            if (found) {
                entry->unk8(arg0, arg1, entry->unk4 & 0xFF, entry->unk5 & 0xFF);
                if (entry->unkC == 0 || entry->unkC == (two = 2)) {  // FAKE: makes the constant 2 a register operand (bnel v0,s6 order)
                    done = 1;
                }
            }
        }
        if (entry->unkC == 0) {
            done = 1;
        }
        entry++;
    } while (!done);
}
