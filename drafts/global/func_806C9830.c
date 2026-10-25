// func_806C9830 (src/global/CC800.c): K&R s8 arg0 + 's8 v = arg0; arg0 = 0;' (v declared before p) matches entry sll/sra+move, home store, frame 0x20, spill 0x1f; only diff v in a3 vs a2 and p in v0 vs a0+move v0,a0. Tried proto/K&R s8/s32/char params, dead uses, q copy, inline p, call protos, permuter (semantics-breaking only)
typedef struct G01Ctl {
    /* 0x000 */ u8 pad0[0x1A4];
    /* 0x1A4 */ u8 unk1A4;
} G01Ctl;

typedef struct G01Act {
    /* 0x000 */ u8 pad0[0x174];
    /* 0x174 */ G01Ctl *unk174;
} G01Act;

typedef struct G01Player {
    /* 0x000 */ u8 pad0[0x2A0];
    /* 0x2A0 */ Actor *unk2A0;
    /* 0x2A4 */ u8 pad2A4[0x4C];
} G01Player;

extern G01Player *D_807FC924;
extern s32 D_807FBB64;
void func_800268C0();

/* stage 6: K&R `s8 arg0` + local `s8 v = arg0; arg0 = 0;` gives the target's single entry conversion (sll/sra, move) and the
 * dead home store sw a0,0x20(sp), frame 0x20 and the 0x1f(sp) spill slot (v declared before p). Remaining diff: v lands in a3
 * (target a2, so the call-arg `li a2` merges with the spill) and p in v0 (target a0 plus `move v0,a0`). */
s8 func_806C9830(arg0, arg1)
    s8 arg0;
    Actor *arg1;
{
    s8 v;
    Actor *p;

    v = arg0;
    arg0 = 0;

    if (D_807FC928 >= 2) {
        p = D_807FC924[((G01Act *)arg1)->unk174->unk1A4].unk2A0;
        if (p != NULL) {
            if (p->unk5C & 1) {
                v = -1;
                if (D_807FBB64 & 0x04000000) {
                    func_800268C0(1, arg1, v);
                }
            } else if (p->unk5C & 4) {
                if (p->unk58 == 0x29 || p->unk58 == 0xAB) {
                    v = -3;
                    if (D_807FBB64 & 0x04000000) {
                        func_800268C0(2, arg1, v);
                    }
                } else {
                    v = -2;
                    if (D_807FBB64 & 0x04000000) {
                        func_800268C0(1, arg1, v);
                    }
                }
            } else if (D_807FBB64 & 0x04000000) {
                func_800268C0(1, arg1, v);
            }
        }
    }
    return v;
}
