// func_80675AFC (src/global/7A510.c): stage 5: matches control flow and frame 0x38, remaining diff regalloc and D_807FBB70 inner loop
typedef struct KaC1_ActorAFC {
    u8 pad0[0x5A];
    s16 unk5A;
    s16 unk5C;
} KaC1_ActorAFC;

typedef struct KaC1_InteractionEntry {
    s16 unk0;
    s16 unk2;
    s8 unk4;
    s8 unk5;
    void (*unk8)(KaC1_ActorAFC *, KaC1_ActorAFC *, s32, s32);
    u8 unkC;
} KaC1_InteractionEntry;

extern ActorGlobalState D_807FBB70;
extern KaC1_InteractionEntry D_8074ABCC[];
s32 func_80675C70(s16, s16, s16);

void func_80675AFC(KaC1_ActorAFC *arg0, KaC1_ActorAFC *arg1) {
    ActorGlobalState *state;
    KaC1_InteractionEntry *entry;
    s32 done;
    s32 found;
    s32 j;
    s8 temp_t1;
    s8 temp_t0;

    state = &D_807FBB70;
    entry = D_8074ABCC;
    done = 0;
    do {
        if (func_80675C70(arg0->unk5A, arg0->unk5C, entry->unk0) &&
            func_80675C70(arg1->unk5A, arg1->unk5C, entry->unk2) &&
            ((temp_t1 = entry->unk4) == -1 || state->unk200 == temp_t1)) {
            temp_t0 = entry->unk5;
            found = 1;
            if (temp_t0 != -1) {
                found = 0;
                for (j = 0; j < state->unk201; j++) {
                    if (arg1 != (KaC1_ActorAFC *)state->unk204[j]) {
                        continue;
                    }
                    if (state->unk244[j] != temp_t0) {
                        continue;
                    }
                    found = 1;
                    break;
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
