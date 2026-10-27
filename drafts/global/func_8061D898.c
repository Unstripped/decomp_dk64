// func_8061D898 (src/global/201B0.c): stage 6, regalloc only: text identical except idx=D_807F5CF0*2 CSE temp lands in a2 (target t9) so chain temps shift t9->t0; off=t8 ok; needs D_807F5D0C defined in TU (cam_defs). Tried locals off/idx, casts, <<1, K&R/varargs proto, permuter 400s (best 50).
void func_806F3DB0(u16, void *);

typedef struct CamDPathList {
    /* 0x0 */ u8 pad0[4];
    /* 0x4 */ s16 *unk4;
    /* 0x8 */ s16 *unk8;
} CamDPathList;

void func_8061D898(void) {
    ((CamActor *)D_807F5D0C)->unk168 = 0;
    ((CamActor *)D_807F5D0C)->unk160 = 0.0;
    D_807F5CF2 = D_807476FC->unkD0[D_807476F4].unk4[D_807F5CF0];
    D_807F5CEC = ((CamDPathList *)&D_807476FC->unkD0[D_807476F4])->unk8[D_807F5CF0];
    func_806F3DB0(D_807F5CF0, &D_807F5D0C);
}
