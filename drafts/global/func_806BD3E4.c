// func_806BD3E4 (src/global/C1E70.c): Stage 6, 2 insn diffs left (li v0,-1 / sb v0,D_807506B4 use t9 not v0 in the -1 store). Fixed vs old draft: (1) actorSpawn(0x73,0xC4,&D_807FBB40) with K&R 's32 actorSpawn();' - 3rd arg gives the else-block &D_807FBB40 range lu->reg=a2, so uopt picks a2 not v0 (preference, not forbidden set); (2) 'D_807506B4 = 0; actorSpawn(...)' on ONE source line fixes sh zero,0x26(sp)/sb zero delay-slot order (as1 does not reorder across .loc lines); (3) 'sp2B = 0xF; sp28 = 0x28;' on ONE line fixes li t6/t7 order AND sh/sb store order (separate lines gave li or store order wrong, never both). Tried for -1: n=-1 local, idx/v3/sp28 locals, ~0, 0xFF, (s8), *cnt=-1, duplicate stores, same-line with calls, s32 returns on flagSet/func_80609140, 10 min permuter (-j2): none changes t9 (copy-prop folds the constant; target v0 = bottom-pool temp, not top-down store-constant temp).
/* NOTE: needs line 14 of C1E70.c changed from 's32 actorSpawn(s32, s32);' to 's32 actorSpawn();' (3rd arg &D_807FBB40 pins the else-block &D_807FBB40 into a2). */
extern s16 D_8076A0A6;
extern s8 D_807506B4;
extern s8 D_807506A8[];
extern f32 D_807FC8D4;
extern s32 D_807F5D10;

s32 func_806BDD2C(void);
void func_8067B238(void *, void *, f32);
s32 func_80614EBC(void *, s32);
void func_806319C4(void *, s32);
s32 func_8061CC40(void *, s32, s32);
s32 func_80629148();
s32 func_8061CB50(void);
void func_8061F0B0(s32, s32, s32);
s32 sfxAllocateChannel(s32, f32);
s16 func_80609140(s16, s32, f32, f32, u8, u8);
void flagSet(s16, s32, s32);

typedef struct NmBD3E4Ptr178 {
    /* 0x00 */ Actor *unk0;
} NmBD3E4Ptr178;

typedef struct NmBD3E4Sub4 {
    /* 0x00 */ u8 pad0[0x64];
    /* 0x64 */ u16 unk64;
} NmBD3E4Sub4;

typedef struct NmBD3E4Act178 {
    /* 0x000 */ u8 pad0[0x178];
    /* 0x178 */ NmBD3E4Ptr178 *unk178;
} NmBD3E4Act178;

void func_806BD3E4(void) {
    NmBD3E4Ptr178 *sp34 = ((NmBD3E4Act178 *)D_807FBB40)->unk178;
    f32 dx;
    f32 dz;
    u8 sp2B;
    u16 sp28;
    s16 v3 = D_8076A0A6;
    s16 idx;
    s8 *cnt = &D_807506B4;
    s8 n;

    if (!(D_807FBB40->unk60 & 0x10)) {
        if (func_806BDD2C() != 0) {
            D_807FBB40->unk154 = 0x40;
            return;
        }
        D_807FBB40->unk12A = 0x7D0;
        D_807FBB40->unk60 |= 0x400;
        v3 = 0;
        D_807506B4 = 0; actorSpawn(0x73, 0xC4, &D_807FBB40);
        func_8067B238(D_807FBB44, D_807FBB40, D_807FBB40->unk4->unk38);
        D_807FBB44->unk64 |= 0x20;
        D_807FBB44->unk60 |= 0x400;
        D_807FBB44->unk12A = 0x7D0;
        sp34->unk0 = D_807FBB44;
        D_807FC8D4 = 1000.0f;
        func_806BD170();
        D_807FBB40->unk154 = 0;
        if (D_80750660 != 0) {
            D_80750660 = 0;
        }
        if (flagGet(0x1BB, 0) == 0) {
            D_807FBB40->unk154 = 1;
        }
    }
    idx = -1;
    if (v3 != 0) {
        idx = 0;
        while (!(v3 & 1)) {
            v3 >>= 1;
            idx++;
        }
    }
    dx = D_807FBB40->unk7C - D_807FBB4C->unk7C;
    dz = D_807FBB40->unk84 - D_807FBB4C->unk84;
    sp28 = 0;
    D_807FC8D4 = dx * dx + dz * dz;
    switch (D_807FBB40->unk154) {
        case 1:
            func_80614EBC(D_807FBB40, 0x2EF);
            D_807FBB40->unk154 = 2;
            func_8061CC40(D_807FBB4C, 2, 1);
            break;
        case 2:
            if (func_80629148() != 0) {
                sfxAllocateChannel(0x7D, 1.0f);
                func_80614EBC(D_807FBB40, 0x2F1);
                D_807FBB40->unk154 = 3;
                D_807FBB40->unk155[0] = 0;
            }
            break;
        case 3:
            if (D_807FBB40->unk155[0] & 1) {
                D_807FBB40->unk155[0]++;
                sp2B = 0xF; sp28 = 0x28;
            }
            break;
    }
    if (func_8061CB50() == 0) {
        if (((NmBD3E4Sub4 *)D_807FBB40->unk4)->unk64 != 0x2F0) {
            func_80614EBC(D_807FBB40, 0x2F0);
        }
    }
    if (sp28) {
        func_8061F0B0(D_807F5D10, sp2B, sp28);
    }
    if (idx >= 0) {
        n = *cnt;
        if (idx == D_807506A8[n]) {
            n++;
            D_807506B4 = n;
            if (D_807506A8[n] == -1) {
                func_80609140(0x1DA, 0x7FFF, 63.0f, 1.0f, 5, 0);
                flagSet(0x28, 1, 1);
                flagSet(0x26, 1, 1);
                D_807506B4 = -1;
            }
        } else {
            D_807506B4 = 0;
        }
    }
    D_8076A0A6 = 0;
    func_806319C4(D_807FBB40, 0);
}
