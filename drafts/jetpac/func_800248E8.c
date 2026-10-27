// func_800248E8 (src/jetpac/0.c): Stage 6 (parked NON_MATCHING in J0a2/0.c): frame/size/no-s0 now match; only diff: p in v1/score in v0 (target p=v0,score=v1) and target re-stores p (sw v0,0x1C(sp)) in the delay slot of jetpacPlayerStateUpdate. Key fixes: final-block accesses through a block-local JetpacGlobalView *g = J0aG (fewer &D_8002EC30 uses stops s0 promotion). Permuter hint: a dead 'if (!sp1C->unk10 && !sp1C->unk10){}' after func_80024408 reproduces the double store (score 612->320) but adds insns.
typedef struct {
    u8 pad0[8];
    s32 unk8;
    u8 unkC;
    u8 padD[0x348 - 0xD];
    s32 unk348;
    s32 unk34C;
    u8 pad350[0x44C - 0x350];
    s32 unk44C;
    u8 pad450[0x78C - 0x450];
    s32 unk78C;
    u8 pad790[0x798 - 0x790];
    u8 unk798;
    u8 unk799;
} J0aGlobalView;
#define J0aG ((J0aGlobalView *)&D_8002EC30)

s32 func_80026FE0(void);
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
