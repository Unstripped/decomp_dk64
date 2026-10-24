// func_8069A7C8 (src/global/9DD70.c): stage 5 (parked, same blocks/frame/saved regs; 235 vs ~235+pad). Fixed: final node->unk8 store must be '0.0 - (float_sum)' (double literal forces cvt.d.s/sub.d/cvt.s.d after a float mul.s+add.s). Remaining: s0/s1/s2 role swap (original: s2 = globals+4i, s0 = globals+12i re-derived via 'move s0,s2' in the preheader), sqrt term load order (original loads entries[i].unk8 (68) before unk0 (60) although the C has unk8 first -> needs a scheduling nudge, e.g. splitting the terms into temps), FP temp allocation in the unk8 decay block (f19/f18/f10 vs f7/f6/...) and the .rodata literal order (lwc1 0(at) vs 8(at)).
extern Actor *D_807FBB40;
extern ActorGlobalState D_807FBB70;
/* Behaviourally equivalent, same blocks/frame/saved regs; remaining diff is FP
   temporary allocation (and one insn): 235 vs 236 insns. */
typedef struct {
    u8 unk0;
    u8 unk1;
    u8 pad2[2];
    f32 unk4;
    f32 unk8;
    f32 unkC;
    u8 unk10;
    u8 pad11[3];
} M1Sub4Node;

typedef struct {
    u8 pad0[0x24];
    M1Sub4Node *unk24;
} M1Sub4;

typedef struct {
    f32 unk0;
    u8 unk4;
    u8 pad5[3];
    f32 unk8;
    s32 unkC;
} M1ProximityState;

typedef struct {
    f32 unk0;
    f32 unk4;
    f32 unk8;
} M1ProximityEntry;

typedef struct {
    u8 pad0[0xB8];
    f32 unkB8;
} M1ProximityNode;

typedef struct {
    u8 pad0[0x3C];
    M1ProximityEntry entries[4];
    u8 pad6C[0x10];
    M1ProximityNode *nodes[4];
} M1ProximityGlobal;

s32 func_80610FE8(s32);
f32 func_80612D1C(f32);
void func_806319C4(Actor *, s32);

void func_8069A7C8(void) {
    M1ProximityGlobal *globals;
    M1ProximityState *state;
    f32 acc;
    f32 dist;
    f32 limit;
    f32 value;
    s32 flags;
    s32 i;

    flags = D_807FBB40->unk60;
    acc = 0.0f;
    state = (M1ProximityState *)D_807FBB40->unk174;
    if (!(flags & 0x10)) {
        D_807FBB40->unk60 = flags | 0x400;
        ((M1Sub4 *)D_807FBB40->unk4)->unk24 = (M1Sub4Node *)func_80610FE8(0x20);
        ((M1Sub4 *)D_807FBB40->unk4)->unk24->unk0 = 1;
        ((M1Sub4 *)D_807FBB40->unk4)->unk24->unk1 = 0xFF;
        ((M1Sub4 *)D_807FBB40->unk4)->unk24->unk4 = 0.0f;
        ((M1Sub4 *)D_807FBB40->unk4)->unk24->unkC = 0.0f;
        ((M1Sub4 *)D_807FBB40->unk4)->unk24->unk8 = 0.0f;
        ((M1Sub4 *)D_807FBB40->unk4)->unk24->unk10 = 0xFF;
        D_807FBB40->unk12A = 0x3E8;
        state->unk4 = 0;
        state->unkC = 0;
        state->unk0 = 0.0f;
        state->unk8 = 0.0f;
    }
    globals = (M1ProximityGlobal *)&D_807FBB70;
    i = 0;
    if ((s32)D_807FBB70.unk39 > 0) {
        do {
            dist = sqrtf((globals->entries[i].unk8 * globals->entries[i].unk8) + (globals->entries[i].unk0 * globals->entries[i].unk0));
            if (dist > 1347.0f) {
                dist = 1347.0f;
            }
            acc += 1347.0f - dist;
            value = (f32)((f64)globals->nodes[i]->unkB8 * 0.1);
            if (state->unk8 < value) {
                state->unk8 = value;
            }
            i++;
        } while (i < (s32)D_807FBB70.unk39);
    }
    if (acc > 1347.0f) {
        acc = 1347.0f;
    }
    limit = (f32)((f64)acc / 10.0);
    if (state->unk0 < limit) {
        state->unk0 = (f32)((f64)state->unk0 + ((f64)(limit - state->unk0) * 0.25));
        if (limit < state->unk0) {
            state->unk0 = limit;
        }
    }
    if (limit < state->unk0) {
        state->unk0 = (f32)((f64)state->unk0 - ((f64)(state->unk0 - limit) * 0.5));
        if (state->unk0 < limit) {
            state->unk0 = limit;
        }
    }
    state->unkC++;
    if ((f64)state->unk8 == 0.0) {
        state->unkC = 0;
    }
    if (D_807FBB70.unk39 != state->unk4) {
        state->unk8 = 12.0f;
    }
    state->unk8 = (f32)((f64)state->unk8 - ((f64)state->unk8 / 40.0));
    if ((f64)state->unk8 < 0.5) {
        state->unk8 = 0.0f;
    }
    ((M1Sub4 *)D_807FBB40->unk4)->unk24->unk8 = 0.0 - (func_80612D1C((f32)((f64)state->unkC * 0.5)) * state->unk8 + state->unk0);
    state->unk4 = D_807FBB70.unk39;
    func_806319C4(D_807FBB40, 0);
}
