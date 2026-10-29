// func_80678824 (src/global/7CA80.c): stage 4: frame 0x18, ra saved at 0x14, extra lui at for scalar D_807FBFE0-C stores
void func_8067889C(s32);
void func_806790F4(s32);
void func_80678B04(void);
void func_80679334(void);
extern ActorCallbackNode *D_807FBFE4;
extern ActorCallbackNode *D_807FBFE8;
extern ActorCallbackNode *D_807FBFEC;

void func_80678824(void) {
    D_807FBE09 = 1;
    D_807FBF10 = 0;
    D_807FBFE4 = NULL;
    *D_807FBFE0 = NULL;
    D_807FBFE8 = NULL;
    D_807FBFEC = NULL;
    func_8067889C(1);
    func_8067889C(2);
    func_806790F4(1);
    func_80678B04();
    D_807FBE09 = 0;
    actorFlushDespawnQueue();
    func_80679334();
}
