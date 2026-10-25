// func_806BD3E4 (src/global/C1E70.c): Stage 6, 13 insn diffs (26 diff lines): uopt gives &D_807FBB40 (bb4) v0 not a2 (target lui a2 sits in the beqz delay slot; as1 can't hoist lui v0 since v0 is the branch reg), sh zero,0x26(sp) lands in jal actorSpawn delay slot instead of sb D_807506B4, li 40/15 (sp28/sp2B) t6/t7 swapped, li -1 is t9 not v0. Fixed vs old draft: 's8 *cnt = &D_807506B4;' + 'n = *cnt;' (local pointer to the counter stops uopt caching &D_807506B4 in t1: an if(D_807506B4){} read before the switch has same effect), sp28 = 0 after dx/dz (lwc1 order A7c,A84,B7c,B84), 'if (sp28)' instead of '!= 0' (lhu t1; move a2,t1). Parked NON_MATCHING in private copy. Tried: array/char/s32/u8 forms of D_807506B4, decl order, dead reads of D_807FBB40/4C/44 anywhere, if/else/goto variants of the early return, local ptr to &D_807FBB40, ptrs to other globals, v3=0 position, 'n=-1; D_807506B4=n', callee proto variants, permuter ~600s.
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
void func_8073129C(s16, s32, s32);

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
        D_807506B4 = 0;
        actorSpawn(0x73, 0xC4);
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
        if (func_8073110C(0x1BB, 0) == 0) {
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
                sp28 = 0x28;
                sp2B = 0xF;
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
                func_8073129C(0x28, 1, 1);
                func_8073129C(0x26, 1, 1);
                D_807506B4 = -1;
            }
        } else {
            D_807506B4 = 0;
        }
    }
    D_8076A0A6 = 0;
    func_806319C4(D_807FBB40, 0);
}
