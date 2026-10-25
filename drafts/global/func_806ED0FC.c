// func_806ED0FC (src/global/EFDC0.c): stage 1: m2c reconstruction of actor target setup; needs camera-block and player-state views
s16 actorListFindIdByActor(s32, u8 *, ?);           /* extern */
? func_80614E78(void *, ?);                         /* extern */
? func_806CA2AC();                                  /* extern */
? func_806CF398(void *);                            /* extern */
? func_806F0C18(void *);                            /* extern */
? sfxStopSlotSound(void *, ?);                      /* extern */
extern void *D_807FBB40;
extern void *D_807FBB48;
extern s32 D_807FC924;
extern u8 D_807FC929;
extern void *D_807FD580;

void func_806ED0FC(void) {
    void *temp_v0;

    func_806CA2AC();
    func_806CF398(D_807FBB48);
    D_807FD580->unk8C = 0;
    func_806F0C18(D_807FBB40);
    sfxStopSlotSound(D_807FBB40, 0);
    sfxStopSlotSound(D_807FBB40, 1);
    func_80614E78(D_807FBB48, 0x21);
    temp_v0 = (D_807FC924 + (D_807FC929 * 0x2F0))->unk2A0;
    if (temp_v0 != NULL) {
        D_807FD580->unkBC = (s16) temp_v0->unk58;
        D_807FD580->unkBE = actorListFindIdByActor((D_807FC924 + (D_807FC929 * 0x2F0))->unk2A0, &D_807FC929, 0x2F0);
    } else {
        D_807FD580->unkBC = 0;
        D_807FD580->unkBE = -1;
    }
    if (D_807FBB40->unk6A & 4) {
        D_807FBB48->unk154 = 0x43;
        D_807FBB48->unk155 = 0;
        return;
    }
    D_807FBB48->unk154 = 0x42;
    D_807FBB48->unk155 = 0;
}
