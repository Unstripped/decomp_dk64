// func_80678824 (src/global/7CA80.c): from .scratch/R3A/func_80678824_best.c
void func_8067889C(s32);
void func_806790F4(s32);
void func_80678B04(void);
void func_80679334(void);
extern u8 D_807FBE09;
extern s16 D_807FBF10;
extern ActorCallbackNode *D_807FBFE4;
extern ActorCallbackNode *D_807FBFE0[];
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
    func_806783BC();
    func_80679334();
}
