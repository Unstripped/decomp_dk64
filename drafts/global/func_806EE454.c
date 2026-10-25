// func_806EE454 (src/global/EFDC0.c): stage 4: recovered both branches, state update, conditional lookup, and notify call; untested register/frame matching
extern void func_806CA2AC(void);
extern s32 func_806EB400(Actor *);
extern s32 func_806C9974(u8, s16);
extern void func_80614E78(Actor *, s32);
extern s32 sfxPlayFromActorWithAltitudeCheck(Actor *, s32, s32, s32, s32);
extern void func_8061F0B0(void *, s32);

void func_806EE454(void) {
    s32 shouldNotify = 1;

    func_806CA2AC();
    if ((func_806EB400(D_807FBB48) != 0) && (func_806C9974(D_807FC929, -1) != 0)) {
        shouldNotify = 0;
        if ((D_807FBB48->unk6A & 4) != 0) {
            func_80614E78(D_807FBB48, 0x29);
        } else {
            func_80614E78(D_807FBB48, 0x27);
        }
        D_807FBB48->unk154 = 0x36;
        D_807FBB48->unk155[0] = 0;
    } else {
        sfxPlayFromActorWithAltitudeCheck(D_807FBB40, 0x16, 0xFF, 0x7F, 0);
        func_80614E78(D_807FBB40, 0x1E);
        D_807FBB40->unk154 = 0x20;
        D_807FBB40->unk155[0] = 1;
    }
    if ((((s16 *)D_807FD580)[0x6A] == 0) && (D_807FC928 < 2)) {
        ((s16 *)D_807FD580)[0x6A] = ((s16 *)D_807530B0)[D_807FD584];
    }
    if (shouldNotify != 0) {
        func_8061F0B0(((void **)D_807FD580)[0x41], 0x14);
    }
}
