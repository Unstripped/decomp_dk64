// schedHandleRSP (src/global/131B0.c): text-identical, reloc only (D_807F04C4/D_807F050C alias relocs vs D_807F04C0+4/D_807F0508+4). Needs u64 D_807F04C8, D_807F0500, D_807F0510 and u32 D_807F04E8 bss types
void schedHandleRSP(SchedStruct *sc) {
    TaskNode *task = sc->curRSPTask;

    sc->curRSPTask = NULL;
    if (task->state == 3) {
        D_807F04D0 = osGetTime() - D_807F04C0;
        if (D_807F04C8 < D_807F04D0) {
            D_807F04C8 = D_807F04D0;
        }
        if (osSpTaskYielded(&task->task) == 0) {
            task->state = 2;
            task->flags |= 4;
            schedTaskDone(sc, task);
        }
        schedStartTask(sc, 0);
    } else {
        if (task->flags & 0x40) {
            D_807F04E8 = __ull_div(osGetTime() - sc->unk290, 0x1E91);
            D_80746828 = 1;
        } else if (task->task.t.type == 2) {
            D_807F0510 = osGetTime();
            D_807F0500 = D_807F0508;
        }
        task->state = 2;
        task->flags |= 4;
        if (schedTaskDone(sc, task) != 0) {
            if (sc->gfxListHead != NULL && sc->gfxListHead->flags != 0x47) {
                schedStartTask(sc, 1);
            }
        }
    }
}
