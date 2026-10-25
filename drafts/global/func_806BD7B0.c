// func_806BD7B0 (src/global/C1E70.c): Parked under NON_MATCHING in src. Only t-reg naming differs (2 groups, 4 lines): equal-branch sll t3/li t5 vs mine t4/t6 in case 4. Needs s32 func_80614EBC, case 0 break, locals order st,sp48,sp44,sp40,p,limit,sp30(+unused 4-byte slot); if ((limit == st->unk0) != 0) from permuter.
extern s8 D_807506A4;
extern f32 D_807FC8D4;

typedef struct R1C0C1Sub174 {
    /* 0x00 */ s16 unk0;
    /* 0x02 */ s8 unk2;
    /* 0x04 */ Actor *unk4;
} R1C0C1Sub174;

typedef struct R1C0C1Spawned {
    /* 0x000 */ u8 pad0[0x146];
    /* 0x146 */ s16 unk146;
} R1C0C1Spawned;

s32 func_806BDD2C(void);
s32 func_80614EBC(void *, s32);
void func_806319C4(void *, s32);
s32 func_8061CC40(void *, s32, s32);
s32 func_8061CB50(void);
s32 sfxAllocateChannel(s32, f32);
s16 func_80609140(s16, s32, f32, f32, u8, u8);
void func_8073129C(s16, s32, s32);

typedef struct R1C0C1Ptr178 {
    /* 0x00 */ Actor *unk0;
} R1C0C1Ptr178;

typedef struct R1C0C1Act178 {
    /* 0x000 */ u8 pad0[0x178];
    /* 0x178 */ R1C0C1Ptr178 *unk178;
} R1C0C1Act178;

typedef struct R1C0C1Pair {
    /* 0x00 */ s16 a;
    /* 0x02 */ s16 b;
} R1C0C1Pair;

typedef struct R1C0C1Blob8 {
    /* 0x00 */ s8 b[8];
} R1C0C1Blob8;

extern R1C0C1Pair D_80750664[];
extern s16 D_80750684[];
extern R1C0C1Blob8 D_807506B8;
extern u8 D_80720A7C;

void sfxStopChannel(s32, s32);
void func_8063DA40(s32, s32);
void func_8061CB08(void);
void func_80712524(s32, s32);
void func_80714950(s32);
void func_8071498C(void (*)(void));
void func_8071AADC(void);
void func_807149C8(s32, s32, s32, s32);
void func_80714CC0(void *, f32, f32, f32, f32);
f32 func_806119FC(void);

void func_806BD7B0(void) {
    R1C0C1Sub174 *st = D_807FBB40->unk174;
    f32 sp48;
    f32 sp44;
    f32 sp40;
    R1C0C1Ptr178 *p;
    s32 limit;
    R1C0C1Blob8 sp30;

    switch (D_807FBB40->unk154) {
        case 5:
            if (D_807506A4 != 0 && func_8061CB50() == 0) {
                st->unk0++;
                if (st->unk0 >= 0x29) {
                    D_807506A4 = 0;
                    D_807FBB40->unk154 = 1;
                }
            } else {
                st->unk0 = 0;
            }
            break;
        case 1:
            st->unk0 = 0;
            D_807FBB40->unk154 = 2;
            break;
        case 2:
            if (D_807FC8D4 < 160000.0) {
                D_807FBB40->unk154 = 3;
                st->unk0 = 0;
                sfxAllocateChannel(0x3B, 1.0f);
                func_80609140(0x258, 0x7FFF, 63.0f, 1.0f, 5, 0);
                func_8061CC40(D_807FBB40, 0, 1);
                func_80614EBC(D_807FBB40, 0x291);
                D_807FBB40->unk155[0] = 0;
                ((R1C0C1Spawned *)D_807FBB40)->unk146 = 1;
            }
            break;
        case 3:
            if (D_807FBB40->unk155[0] == 1) {
                D_807FBB40->unk155[0]++;
            } else if (D_807FBB40->unk155[0] == 2) {
                sfxStopChannel(0x3B, 1);
                D_807FBB40->unk128 -= 8;
                if (D_807FBB40->unk128 <= 0) {
                    D_807FBB40->unk128 = 0;
                    st->unk0++;
                    if (st->unk0 == 1) {
                        func_80609140(0x1F6, 0x7FFF, 63.0f, 1.0f, 5, 0);
                    }
                    if (st->unk0 >= 0xB) {
                        sp30 = D_807506B8;
                        D_807FBB40->unk154 = 4;
                        sfxAllocateChannel(0x7D, 1.0f);
                        func_80614EBC(st->unk4, D_80750684[st->unk2]);
                        st->unk0 = 0;
                        st->unk4->unk154 = 3;
                        st->unk4->unk155[0] = 0;
                        func_8061CC40(0, 1, 1);
                        func_8063DA40(sp30.b[st->unk2], 2);
                    }
                }
                if (D_807FBB40->unk128 < 0x80) {
                    D_807FBB40->unk80 -= 6.0;
                }
            } else {
                func_80714950(0x10064);
                func_8071498C(func_8071AADC);
                func_807149C8(0xFF, 0xFF, 0xFF, 0xFF);
                sp48 = func_806119FC() * 30.0 + D_807FBB40->unk7C;
                sp44 = func_806119FC() * 30.0 + (D_807FBB40->unk80 + 20.0);
                sp40 = func_806119FC() * 30.0 + D_807FBB40->unk84;
                func_80714CC0(&D_80720A7C, 1.2f, sp48, sp44, sp40);
            }
            break;
        case 4:
            if (func_806BDD2C() != 0) {
                p = ((R1C0C1Act178 *)st->unk4)->unk178;
                p->unk0->unk80 += 5.0;
                if (st->unk0 == 0x10E) {
                    func_8073129C(0x315, 1, 0);
                    func_80712524(D_80750664[7].a, D_80750664[7].b);
                }
            }
            limit = 0xB4;
            if (st->unk2 == 2 || st->unk2 == 7) {
                if (func_806BDD2C() == 0) {
                    limit = 0x5A;
                }
            }
            st->unk0++;
            if ((limit == st->unk0) != 0) {
                if (st->unk2 == 2 || st->unk2 == 7) {
                    func_8073129C(st->unk2 + 0x1BC, 1, 0);
                    if (func_806BDD2C() == 0) {
                        func_8061CB08();
                        sfxStopChannel(0x7D, 1);
                        D_807506A4 = 1;
                    }
                } else {
                    func_80712524(D_80750664[st->unk2].a, D_80750664[st->unk2].b);
                }
            }
            break;
        case 0:
            break;
    }
    D_807FBB40->unk15E = 0x28;
    func_806319C4(D_807FBB40, 0);
}
