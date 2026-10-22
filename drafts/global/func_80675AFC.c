// func_80675AFC (src/global/7A510.c): from .scratch/Beh7984B/func_80675AFC_best.c
typedef struct Beh7984B_ActorAFC {
    u8 pad0[0x5A];
    s16 unk5A;
    s16 unk5C;
} Beh7984B_ActorAFC;

typedef struct Beh7984B_InteractionEntry {
    s16 unk0;
    s16 unk2;
    s8 unk4;
    s8 unk5;
    void (*unk8)(Beh7984B_ActorAFC *, Beh7984B_ActorAFC *, s32, s32);
    u8 unkC;
} Beh7984B_InteractionEntry;

extern ActorGlobalState D_807FBB70;
extern Beh7984B_InteractionEntry D_8074ABCC[];
s32 func_80675C70(s16, s16, s16);

void func_80675AFC(Beh7984B_ActorAFC *arg0, Beh7984B_ActorAFC *arg1) {
    Beh7984B_InteractionEntry *entry;
    s32 done;
    s32 found;
    s32 j;
    s32 count;
    s8 temp_t1;
    s8 temp_t0;

    entry = D_8074ABCC;
    done = 0;
    do {
        if (func_80675C70(arg0->unk5A, arg0->unk5C, entry->unk0) &&
            func_80675C70(arg1->unk5A, arg1->unk5C, entry->unk2) &&
            ((temp_t1 = entry->unk4) == -1 || D_807FBB70.unk200 == temp_t1)) {
            temp_t0 = entry->unk5;
            found = 1;
            if (temp_t0 != -1) {
                found = 0;
                j = 0;
                count = D_807FBB70.unk201;
                while (j < count) {
                    if (arg1 == (Beh7984B_ActorAFC *)D_807FBB70.unk204[j] && D_807FBB70.unk244[j] == temp_t0) {
                        found = 1;
                    }
                    j++;
                    if (found) {
                        break;
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
