// func_806C9830 (src/global/CC800.c): stage 6, regs only (fdiff score 130): K&R s8 arg0 + v=arg0; arg0=0 gives frame 0x20/spill 0x1f/dead home store. Named locals c=arg1->unk174, pl=c->unk1A4+(G01Player*)D_807FC924, p=pl->unk2A0, u16 f=p->unk5C give c=v0 pl=v1 p=a0 f=v1 (first blocks identical to target). 2-arg call func_800268C0(1,arg1) puts v in a2 (3-arg call forbids a2 via arg-setup regsused). Remaining: target copies p to v0 (move v0,a0 after lhu) and loads unk58 into v1 via lw v1,0x58(v0); ours lw v0,0x58(a0). Tried q=p copies (CP removes them), q types, reload q, dead if(p){} uses, k local for unk58, decl permutations, permuter 500s (no gain).
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

/* stage 6: K&R `s8 arg0` + `v = arg0; arg0 = 0;` gives the entry sll/sra/move, the dead home store, frame 0x20 and the
 * 0x1f(sp) spill. Named c/pl locals put c=v0, pl=v1, p=a0 in the first block. The call passes only (1, arg1): a third
 * `v` argument makes uopt forbid a2 for v (arg-setup block), so v stays in a2 only with the 2-arg call (callee reads a2).
 * Remaining diff: target keeps flags/unk58 in v1 and copies p to v0 (`move v0,a0`) for the unk58 load. */
s8 func_806C9830(arg0, arg1)
    s8 arg0;
    Actor *arg1;
{
    s8 v;
    G01Ctl *c;
    G01Player *pl;
    Actor *p;
    u16 f;

    v = arg0;
    arg0 = 0;

    if (D_807FC928 >= 2) {
        c = ((G01Act *)arg1)->unk174; pl = c->unk1A4 + (G01Player *)D_807FC924; p = pl->unk2A0;
        if (p != NULL) {
            f = p->unk5C;
            if (f & 1) {
                v = -1;
                if (D_807FBB64 & 0x04000000) {
                    func_800268C0(1, arg1);
                }
            } else if (f & 4) {
                if (p->unk58 == 0x29 || p->unk58 == 0xAB) {
                    v = -3;
                    if (D_807FBB64 & 0x04000000) {
                        func_800268C0(2, arg1);
                    }
                } else {
                    v = -2;
                    if (D_807FBB64 & 0x04000000) {
                        func_800268C0(1, arg1);
                    }
                }
            } else if (D_807FBB64 & 0x04000000) {
                func_800268C0(1, arg1);
            }
        }
    }
    return v;
}
