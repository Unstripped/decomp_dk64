// func_80675AFC (src/global/7A510.c): stage 5: frame 0x38, s0-s6/ra match, control flow matches; remaining diff inner loop unk204 indexing and delay-slot branch-likely filling (score 28)
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
    s32 found;
    s32 j;
    s8 temp_t1;
    s8 temp_t0;

    entry = D_8074ABCC;
    done = 0;
    do {
        if (func_80675C70(arg0->unk5A, arg0->unk5C, entry->unk0) &&
            func_80675C70(arg1->unk5A, arg1->unk5C, entry->unk2) &&
            ((-1 == (temp_t1 = entry->unk4)) || D_807FBB70.unk200 == temp_t1)) {
            found = 1;
            if (-1 != (temp_t0 = entry->unk5)) {
                found = 0;
                for (j = 0; !found && j < D_807FBB70.unk201; j++) {
                    if (arg1 == (KaP2_ActorAFC *)D_807FBB70.unk204[j] && D_807FBB70.unk244[j] == temp_t0) {
                        found = 1;
                    }
                }
            }
            if (found) {
                entry->unk8(arg0, arg1, temp_t1 & 0xFF, temp_t0 & 0xFF);
                if (entry->unkC == 0 || entry->unkC == 2) {
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
