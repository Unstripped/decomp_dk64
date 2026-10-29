// func_80723428 (src/global/127B00.c): Fx127A copy C (agent stopped: subagent credits ran out), deadsweep score full=2 vs expected; earlier note: stage 4: 0x20 frame conflicts with required sp+0x1C pointer home slot
void heapFree(void *);

void func_80723428(s32 arg0) {
    PathPlayback **temp_v0;
    s32 pad;

    if ((arg0 == -1) || (D_807FDBF8[arg0] != NULL)) {
        temp_v0 = &D_807FDBF8[arg0];
        heapFree(*temp_v0);
        *temp_v0 = NULL;
    }
}
