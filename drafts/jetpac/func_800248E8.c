// func_800248E8 (src/jetpac/0.c): Stage 6 (C1c re-check): only diff p in v1/score in v0 (target p=v0,score=v1) + target's extra sw v0,0x1C(sp) before jetpacPlayerStateUpdate. Tried (all identical 44-line diff): s32 return types on every callee (each and all), separate idx/score/pointer locals, register, pad local, pointer-from-offset forms, init-vs-assign, sc local, double read, &players[0]+i, pl base local, duplicated assignment (worse); permuter 240s -j2 best 592 (start 612), no hit. Earlier hint: dead 'if(!sp1C->unk10 && !sp1C->unk10){}' reproduces double store (612->320) but adds insns.
void jetpacPlayerStateUpdate(void);
void jetpacItemsUpdate(void);
void func_80026AB0(void);

typedef struct {
    u8 pad0[0x44];
    void (*unk44)(void *);
    u8 pad48[4];
} J0aItem;

void func_800248E8(s32 arg0) {
    JetpacPlayer *sp1C = &D_8002EC30.players[D_8002EC30.active_player];

    if (sp1C->score >= 1000000) {
        sp1C->score -= 1000000;
    }
    func_80024408(arg0);
    jetpacPlayerStateUpdate();
    func_80026CEC();
    sp1C->unk18C(&sp1C->unk148);
    ((J0aItem *)&sp1C->pad14[sp1C->unk10 * 0x4C])->unk44(&sp1C->pad14[sp1C->unk10 * 0x4C]);
    func_8002ABDC();
    jetpacInitRdp(arg0);
    func_80028E88();
    func_80026AB0();
    func_8002AD8C();
    jetpacItemsUpdate();
    func_800285DC();
    func_80026CA4();
    func_80025904(arg0);
    if (func_80026FE0() != 0) {
        J0aG->unk44C++;
    }
    {
        J0aGlobalView *g = J0aG;
        if (g->unk8 & 0x1000) {
            g->unk78C = 3;
            g->unkC = 1;
        }
    }
}
