// actorGlobalCallbacksReset (src/global/7CA80.c): text matches IDO byte-exact (0 diff lines) ONLY when the TU defines 'ActorCallbackNode *D_807FBFE0[4];' (.bss carve 0x807FBFE0-0x807FBFF0 in dk64.global.us.yaml; as extern uopt hoists the base, target shares one lui at per pair). Needs yaml carve; parked under NON_MATCHING in src copy
void actorUpdateActiveList(u8);
void actorGlobalCallbacksDispatchAndFree();
void func_80678B04(void);
void actorDelayedCallbacksTick(void);

ActorCallbackNode *D_807FBFE0[4];
void actorGlobalCallbacksReset(void) {
    s32 i;

    D_807FBE09 = 1;
    D_807FBF10 = 0;
    for (i = 0; i < 4; i++) {
        D_807FBFE0[i] = NULL;
    }
    actorUpdateActiveList(1);
    actorUpdateActiveList(2);
    actorGlobalCallbacksDispatchAndFree(1);
    func_80678B04();
    D_807FBE09 = 0;
    actorFlushDespawnQueue();
    actorDelayedCallbacksTick();
}
