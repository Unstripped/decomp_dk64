// actorGlobalCallbacksReset (src/global/7CA80.c): stage 4: 30 insns, frame 0x18, ra saved at 0x14; uopt hoists base of D_807FBFE0 into v0 (12 insns) vs target 12 insns direct off at via %hi/%lo of D_807FBFE4/8
void actorUpdateActiveList(s32);
void actorGlobalCallbacksDispatchAndFree(s32);
void func_80678B04(void);
void actorDelayedCallbacksTick(void);

void actorGlobalCallbacksReset(void) {
    D_807FBE09 = 1;
    D_807FBF10 = 0;
    D_807FBFE0[1] = NULL;
    D_807FBFE0[0] = NULL;
    D_807FBFE0[2] = NULL;
    D_807FBFE0[3] = NULL;
    actorUpdateActiveList(1);
    actorUpdateActiveList(2);
    actorGlobalCallbacksDispatchAndFree(1);
    func_80678B04();
    D_807FBE09 = 0;
    actorFlushDespawnQueue();
    actorDelayedCallbacksTick();
}
