// func_8061D898 (src/global/201B0.c): stage 6, regalloc only: text identical except idx=D_807F5CF0*2 gets uopt reg a2 (target: ugen temp t9 computed BEFORE the unkD0 chain load; chain temps then start t0 instead of t9). Target = idx NOT a uopt candidate. Tried: s32/u32/s16 locals, path/i/j locals, <<1 / +self / *2 mixes (two sll), idx[ptr] forms, (*(u16*)&F0), K&R/varargs/4-arg proto, 800s permuter (best 35, semantic junk). func_80624978 matched this round with wrap = dist >= 0x801 ? 0x1000 - dist : dist.
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
