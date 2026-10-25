// func_806E7DF4 (src/global/E4090.c): text identical except t0/t1 swap: uopt colours D_807FD610 base (adjsave 0.75) before const -1 (0.5); target has -1 in t0, base in t1. Tried: dead tests, locals, register, compound ops, permuter 25k iters x3. Needs: -1 priority above base. Key tricks: nested ternary call arg for 2nd func_80614EBC, 'st->unk3F == 1' re-read after store (not (u8)(cnt-1)), direct D_807FD580 reads (no player local), plain 'if (unk1F0 & mask)' twice (no sel var).
// and the hoisted -1 constant (mine t1, target t0). Needs G21Table/D_807FD610/G24_SCHED280/gScheduler from E4090.c.
typedef struct G28State {
    /* 0x00 */ s16 unk0;
    /* 0x02 */ s16 unk2;
    /* 0x04 */ u8 pad4[0x28];
    /* 0x2C */ f32 unk2C;
    /* 0x30 */ u8 pad30[4];
    /* 0x34 */ u8 *unk34;
    /* 0x38 */ u8 pad38[6];
    /* 0x3E */ u8 unk3E;
    /* 0x3F */ u8 unk3F;
    /* 0x40 */ u8 unk40;
    /* 0x41 */ u8 pad41;
    /* 0x42 */ u8 unk42;
} G28State;

typedef struct G28Anim0 {
    /* 0x00 */ u8 pad0[0x10];
    /* 0x10 */ s16 unk10;
} G28Anim0;

typedef struct G28Anim {
    /* 0x00 */ G28Anim0 *unk0;
} G28Anim;

typedef struct G28Actor {
    /* 0x000 */ u8 pad0[4];
    /* 0x004 */ G28Anim *unk4;
    /* 0x008 */ u8 pad8[0xAC];
    /* 0x0B4 */ f32 unkB4;
    /* 0x0B8 */ f32 unkB8;
    /* 0x0BC */ u8 padBC[4];
    /* 0x0C0 */ f32 unkC0;
    /* 0x0C4 */ u8 padC4[0x22];
    /* 0x0E6 */ s16 unkE6;
    /* 0x0E8 */ s16 unkE8;
    /* 0x0EA */ u8 padEA[0x6A];
    /* 0x154 */ u8 unk154;
    /* 0x155 */ u8 unk155;
    /* 0x156 */ u8 pad156[0x1E];
    /* 0x174 */ G28State *unk174;
} G28Actor;

typedef struct G28Player {
    /* 0x00 */ u8 pad0[0x10];
    /* 0x10 */ s16 unk10;
    /* 0x12 */ s16 unk12;
    /* 0x14 */ s16 unk14;
    /* 0x16 */ u8 pad16[0x1A];
    /* 0x30 */ f32 unk30;
    /* 0x34 */ u8 pad34[4];
    /* 0x38 */ f32 unk38;
    /* 0x3C */ u8 pad3C[0x1C];
    /* 0x58 */ u32 unk58;
    /* 0x5C */ u32 unk5C;
    /* 0x60 */ u8 pad60[0x28];
    /* 0x88 */ G28Actor *unk88;
    /* 0x8C */ u8 pad8C[0x164];
    /* 0x1F0 */ s32 unk1F0;
} G28Player;

#define G28_P ((G28Player *)D_807FD580)
#define G28_A ((G28Actor *)D_807FBB40)
#define G28_PAD(sym, T) (*(T *)((u8 *)&(sym) + D_807FC929 * 0x34))
#define G28_PADS ((G21Table *)((u8 *)D_807FD610 + D_807FC929 * 0x34))

extern s16 D_80750338;

void func_806E7DF4(void) {
    G28State *st;
    u8 flag;
    s32 a1;
    u8 cnt;

    st = G28_P->unk88->unk174;
    if (st->unk0 != 0) {
        G28_PAD(D_807FD63E, s8) = 0;
    } else {
        flag = 0;
        a1 = 3;
        if (G28_P->unk88->unk154 == 5) {
            flag = 1;
        }
        if (*st->unk34 & 0x80) {
            a1 = 1;
        }
        if (flag) {
            G28_PADS->unk2E = G28_PADS->unk2E * -1;
        }
        if (G28_P->unk1F0 & 0x10000002) {
            G28_PADS->unk2E = G28_PADS->unk2E * -1;
        }
        if (G28_P->unk1F0 & 0x10000002) {
            G28_PADS->unk2F = G28_PADS->unk2F * -1;
        }
        if ((*st->unk34 & 0xC0) &&
            ((G28_PADS->unk2E >= 0x1F && st->unk3F > 0) || (G28_PADS->unk2E < -0x1E && st->unk3F < a1))) {
            G28_P->unk58 = G24_SCHED280;
            G28_P->unk88->unkC0 = D_80750338;
            G28_P->unk58 = G24_SCHED280 - 0x1E;
            cnt = st->unk3F;
            st->unk2C = 1.0f;
            st->unk40 = cnt;
            if (G28_PADS->unk2E >= 0x1F) {
                st->unk3F = cnt - 1;
                if (st->unk3F == 1) {
                    st->unk3F = 0;
                }
                a1 = flag ? 0x81 : 0x7D;
                func_80614E78(D_807FBB40, a1);
                func_80614EBC(G28_P->unk88, flag ? 0x295 : 0x296);
            } else {
                st->unk3F = cnt + 1;
                if (st->unk3F == 1 && (*st->unk34 & 0x40)) {
                    st->unk3F = 2;
                }
                a1 = flag ? 0x7D : 0x81;
                func_80614E78(D_807FBB40, a1);
                func_80614EBC(G28_P->unk88, flag ? 0x296 : 0x295);
            }
        }
    }
    if (G28_P->unk1F0 & 8) {
        st->unk3E = 3;
        G28_P->unk88->unkB8 = 3.0f;
        return;
    }
    st->unk3E = (G28_PAD(D_807FD63F, s8) / 1.5) + 80.0;
}
