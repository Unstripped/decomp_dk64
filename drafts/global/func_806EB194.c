// func_806EB194 (src/global/EFDC0.c): Callback dispatcher reconstruction: behavior recovered; stack/register allocation differs.
s32 actorTableContains(Actor *);

void func_806EB194(void) {
    EfAQueuedCall *entry;

    entry = &EfA_Q[D_807FC929];
    if (entry->unk29C >= 0) {
        if (entry->unk2A0 != NULL) {
            if ((actorTableContains(entry->unk2A0) == 0) ||
                (((EfAActor *)entry->unk2A0)->unk54 != entry->unk2A4)) {
                EfA_Q[D_807FC929].unk2A0 = NULL;
                entry = &EfA_Q[D_807FC929];
            }
        }
        D_80752C70[entry->unk29C]();
        entry = &EfA_Q[D_807FC929];
    }
    entry->unk29C = -1;
}
