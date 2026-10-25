// func_806C9830 (src/global/CC800.c): G01 stage 6 near-miss: s8 var kept in a3/memory instead of a2 + spill 0x1F(sp)
/* Needs (from the CC800 copy): G01Ctl (unk1A4 u8 at 0x1A4, unk174 pointer at Actor+0x174 via G01Act),
 * G01Player with `Actor *unk2A0` at 0x2A0 (0x2F0-byte stride), D_807FC924 array, D_807FC928 u8. */
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

/* stage 6: target keeps the s8 variable in $a2 (param converted once: sll/sra then move a2,t8; spill sb/lb at 0x1F(sp),
 * frame 0x20, home store sw a0,0x20(sp) never reloaded). Every C form tried puts the variable in $a3 (`lb a3,35(sp)`
 * from the param home) or keeps it memory-only in the param home byte (27(sp)); frame is 0x18 instead of 0x20. */
s8 func_806C9830(s32 arg0, Actor *arg1) {
    Actor *p;
    s8 v = arg0;

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
