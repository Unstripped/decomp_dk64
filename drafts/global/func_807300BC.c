// func_807300BC (src/global/133A90.c): same frame 0x140/saved regs; only v0/v1 + t-reg numbering in guRotateF angle (target subu v0..sra v0; unk58 temp in v1; mine v1/t4 and v0); (s16)(0, x) comma trick from permuter; parked NON_MATCHING
typedef struct H1ProxSub {
    /* 0x00 */ u8 unk0;
    /* 0x01 */ u8 unk1;
    /* 0x02 */ u8 pad2[2];
    /* 0x04 */ f32 unk4;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ s16 unk10;
    /* 0x12 */ s16 unk12;
    /* 0x14 */ s16 unk14;
    /* 0x16 */ s16 unk16;
    /* 0x18 */ u8 unk18;
    /* 0x19 */ u8 pad19[3];
} H1ProxSub; // size = 0x1C

typedef struct H1ProxNode {
    /* 0x00 */ Actor *unk0;
    /* 0x04 */ u8 unk4;
    /* 0x05 */ u8 unk5;
    /* 0x06 */ u8 unk6;
    /* 0x07 */ u8 unk7;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ u8 pad10[4];
    /* 0x14 */ f32 unk14;
    /* 0x18 */ u8 unk18;
    /* 0x19 */ u8 pad19[3];
    /* 0x1C */ f32 unk1C;
    /* 0x20 */ f32 unk20;
    /* 0x24 */ f32 unk24;
    /* 0x28 */ f32 unk28;
    /* 0x2C */ f32 unk2C;
    /* 0x30 */ u8 unk30;
    /* 0x31 */ u8 unk31;
    /* 0x32 */ u8 pad32[2];
    /* 0x34 */ H1ProxSub *unk34;
    /* 0x38 */ struct H1ProxNode *next;
} H1ProxNode; // size = 0x3C

extern H1ProxNode *D_807FDCC0;

typedef struct H1ActorState {
    /* 0x000 */ u8 pad0[0x130];
    /* 0x130 */ Actor *unk130;
    /* 0x134 */ u8 unk134;
    /* 0x135 */ u8 pad135[3];
    /* 0x138 */ f32 unk138;
    /* 0x13C */ f32 unk13C;
    /* 0x140 */ f32 unk140;
    /* 0x144 */ f32 unk144;
    /* 0x148 */ f32 unk148;
    /* 0x14C */ u8 pad14C[0x10];
    /* 0x15C */ u8 unk15C[0x40];
    /* 0x19C */ s16 unk19C;
    /* 0x19E */ s16 unk19E;
    /* 0x1A0 */ u8 pad1A0[4];
    /* 0x1A4 */ u8 unk1A4;
} H1ActorState;

extern Actor *D_807FBB40;
void actorGetNodePos(void *, s32, f32 *, f32 *, f32 *);
f32 func_80611BB4(f32, f32);
f32 sqrtf(f32);

typedef struct H1ActorB {
    /* 0x000 */ u8 pad0[0xC];
    /* 0x00C */ f32 unkC[4][4];
    /* 0x04C */ u8 pad4C[0xC];
    /* 0x058 */ s32 unk58;
    /* 0x05C */ u8 pad5C[8];
    /* 0x064 */ u32 unk64;
    /* 0x068 */ u8 pad68[2];
    /* 0x06A */ u16 unk6A;
    /* 0x06C */ u8 pad6C[0x10];
    /* 0x07C */ f32 unk7C;
    /* 0x080 */ f32 unk80;
    /* 0x084 */ f32 unk84;
    /* 0x088 */ u8 pad88[0x5E];
    /* 0x0E6 */ s16 unkE6;
    /* 0x0E8 */ s16 unkE8;
    /* 0x0EA */ u8 padEA[0x8A];
    /* 0x174 */ H1ActorState *unk174;
} H1ActorB;

void func_8072FDD4(H1ProxNode *, f32, u8 *, f32 *);
void proxPathGetSegmentMatrices(Actor *, u8, u8, u8, void **, void **);
void mtxLerpL(Mtx *, Mtx *, f32, Mtx *);
void func_80730408(H1ActorB *, H1ActorState *, H1ProxNode *, u8, f32);

void func_807300BC(H1ActorB **arg0) {
    H1ActorB *actor;
    H1ActorState *state;
    u8 idx;
    f32 t;
    H1ProxNode *node;
    void *p128;
    void *p124;
    s32 found;
    Mtx mtx;
    f32 mA[4][4];
    f32 m6[4][4];
    u8 idA;
    u8 idB;
    s32 nodeId;
    f32 dx;
    f32 x;
    f32 y;
    f32 z;
    f32 dz;
    f32 dy;
    f32 dist;
    f32 ang;

    actor = *arg0;
    node = D_807FDCC0;
    state = actor->unk174;
    found = 0;
    while (node != NULL && !found) {
        if (node->unk0 == state->unk130 && node->unk5 == state->unk134) {
            found = 1;
        } else {
            node = node->next;
        }
    }
    if (!found || (actor->unk64 & 0x2000)) {
        actor->unk6A &= ~0x40;
        return;
    }
    func_8072FDD4(node, state->unk138, &idx, &t);
    idA = node->unk34[idx].unk0;
    idB = node->unk34[idx].unk1;
    switch (node->unk6) {
    case 0:
        proxPathGetSegmentMatrices(node->unk0, node->unk4, idA, idB, &p128, &p124);
        mtxLerpL(p128, p124, 1.0 - t, &mtx);
        guRotateF(m6, (s16)(0, (actor->unkE6 - state->unk130->unkE6) & 0xFFF) / 4095.0 * 360.0, 0.0f, 1.0f, 0.0f);
        guTranslateF(mA, 0.0f, state->unk138 + -80.0, 0.0f);
        guMtxCatF(m6, mA, mA);
        guMtxL2F(actor->unkC, &mtx);
        guMtxCatF(mA, actor->unkC, actor->unkC);
        actorGetNodePos(actor, 8, &actor->unk7C, &actor->unk80, &actor->unk84);
        state->unk19C = 0;
        state->unk19E = 0xFFF;
        if (D_807FBB40->unk6A & 0x40) {
            if (actor->unk58 != 2 && actor->unk58 != 5) {
                nodeId = 0xD;
            } else {
                nodeId = 0xF;
            }
            actorGetNodePos(actor, nodeId, &x, &y, &z);
            dy = y - actor->unk80;
            dx = x - actor->unk7C;
            dz = z - actor->unk84;
            dist = sqrtf(dx * dx + dz * dz);
            ang = func_80611BB4(dist, dy);
            actor->unkE8 = 0.0 - ang * 2048.0 / 3.1415927f;
        } else {
            actor->unkE8 = 0;
        }
        break;
    case 1:
        func_80730408(actor, state, node, idx, t);
        actorGetNodePos(actor, 1, &actor->unk7C, &actor->unk80, &actor->unk84);
        break;
    }
}
