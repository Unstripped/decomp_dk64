// func_806AA304 (src/global/ACDC0.c): same size, ~35 diff lines (k-loop slti/bne, sum addu order, spill slots, s0 &D_807210EC CSE, case3 tail sched)
typedef struct {
    /* 0x00 */ u8 pad0[2];
    /* 0x02 */ u8 unk2;
    /* 0x03 */ u8 pad3;
    /* 0x04 */ u8 unk4;
    /* 0x05 */ u8 pad5;
    /* 0x06 */ u16 unk6;
    /* 0x08 */ u16 unk8;
    /* 0x0A */ u16 unkA[14];
    /* 0x26 */ u16 unk26[14];
    /* 0x42 */ u16 unk42[14];
} L9HudEntry;

typedef struct {
    /* 0x00 */ u8 pad0[4];
    /* 0x04 */ f32 unk4;
    /* 0x08 */ s16 unk8[4];
    /* 0x10 */ s16 unk10;
    /* 0x12 */ s8 unk12;
    /* 0x13 */ u8 pad13;
    /* 0x14 */ s8 unk14;
    /* 0x15 */ s8 unk15;
} L9Hud;

typedef struct {
    /* 0x00 */ u8 unk0;
    /* 0x01 */ u8 pad1[3];
    /* 0x04 */ s16 unk4;
    /* 0x06 */ u8 pad6[2];
} L9Entry8;

extern u8 D_8074E77C;
extern u8 D_8076A0AB;
extern u8 D_807FC950[];
#define L9ENT(i) ((L9HudEntry *)(D_807FC950 + (i) * 0x5E))
extern L9Entry8 D_80755DA8[];
extern s8 D_80750560[];
extern s8 D_807FC7F8[];
extern s8 D_807FC800;
extern f32 D_807FC804;
extern s8 D_807FC80C;
extern s8 D_807FC80D;
extern s8 D_807FC80F;
extern s8 D_807FC818[];
extern s16 D_807FC828[];
extern s16 D_807FC82A;
extern s16 D_807FC82E;
extern s16 D_807FC838;
extern s16 D_807FC83A;
extern s8 D_807FC83C;
extern u16 D_807FCC40;
extern u16 D_807FCC44;
extern u16 D_807FCC46;
extern u16 D_807FCC48;
extern s8 D_80750530[];
extern void *D_80750518[];
extern s16 D_807505A4[];
extern s16 D_807505B8[];
extern s16 D_807505CA;
extern s8 D_807505D0;
extern void *D_807505D8[];
extern s32 D_80720C34;
extern s32 D_80720D38;
extern s32 D_80720D5C;
extern s32 D_80720D80;
extern s32 D_8072104C;
extern s32 D_80721094;
extern s32 D_807210EC;
extern s32 D_807211D0;
extern s32 D_80721474;
extern s32 D_80721518;

s32 func_805FF030(s32, s32);
f32 func_80612E40(f32);
s32 func_806C8DE0(s32);
s32 func_806F6E58(s32);
s32 func_806FA7A4(s32);
s32 func_8073110C(s16, s32);
s32 func_807319D8(s32, s32, s32);
s32 func_80731A04(s32, s32, s32, s32);
void func_806AB4EC(void *, void *, s32, s32, f32, s32, s32);
void func_806AB808(void *, s32, s32, s32, s32, s32, s32, s32);

void func_806AA304(L9Hud *arg0, s32 arg1) {
    s32 saved;
    s32 idx;
    L9HudEntry *e2;
    L9HudEntry *ent;
    s32 j;
    s32 i;
    s8 cnt8;
    s16 xs;
    s8 *fp;
    s32 sum;
    s32 sum3;
    s32 cnt;
    s8 found[4];
    s16 *p;
    L9Entry8 *q;
    s32 x;
    f32 f;
    s32 flag;

    saved = D_8074E77C;
    e2 = L9ENT(func_806C8DE0(0));
    D_8074E77C = arg0->unk14;
    ent = L9ENT(arg0->unk14);
    idx = arg0->unk8[arg0->unk15];
    D_807FC7F8[arg0->unk15] = 0;
    idx = D_80750560[idx];
    if (arg1 == 0) {
        D_807FC800 = arg0->unk14;
        D_807FC80D = D_807FC80C;
        arg0->unk10 = 0;
        arg0->unk4 = 0.0f;
        D_807FC804 = 0.0f;
    }
    D_807FC80F = 1;
    switch (arg0->unk12) {
    case 0:
        D_8074E77C = saved;
        idx = func_805FF030(D_8076A0AB, 1);
        if (idx >= 9) {
            idx = 7;
        }
        if (idx != 7 && func_8073110C(0x18B, 0)) {
            func_806AB808(arg0, 0x1E, 0x1E, 0xC, -0xA, e2->unkA[idx], 1, 0);
            func_806AB4EC(arg0, 0, 0x1E, 0x1E, 0.75f, 2, 1);
        }
        if (func_8073110C(0x184, 0)) {
            func_806AB808(arg0, 0x1E, 0x5A, 0xC, -0xA, D_807FCC44, 1, 1);
            func_806AB4EC(arg0, (void *)4, 0x1E, 0x5A, 0.75f, 2, 1);
        }
        if (e2->unk2 != 0) {
            func_806AB808(arg0, 0x1E, 0x7D, 0xC, -0xA, D_807FCC40, 1, 1);
            func_806AB4EC(arg0, (void *)2, 0x1E, 0x7D, 0.65f, 2, 1);
        }
        if (func_806F6E58(D_8074E77C)) {
            f = func_806FA7A4(5);
            func_806AB808(arg0, 0x1E, 0xA0, 0xC, -0xA, (s32)func_80612E40((f32)(u32)D_807FCC46 / f), 1, 1);
            func_806AB4EC(arg0, (void *)5, 0x1E, 0xA0, 0.65f, 2, 1);
        }
        if (func_8073110C(0x18C, 0)) {
            func_806AB808(arg0, 0x122, 0x5A, -0xF, -0xA, e2->unk6, 1, 0x80);
            func_806AB4EC(arg0, (void *)1, 0x122, 0x5A, 0.75f, 2, 1);
        }
        if (ent->unk4 & 1) {
            func_806AB808(arg0, 0x122, 0x7D, -0xC, -0xA, ent->unk8, 2, 0x81);
            func_806AB4EC(arg0, (void *)7, 0x122, 0x7D, 0.75f, 2, 7);
        }
        if (func_8073110C(0x179, 0)) {
            func_806AB808(arg0, 0x122, 0xA0, -0xC, -0xA, D_807FCC48, 1, 0x81);
            func_806AB4EC(arg0, (void *)6, 0x122, 0xA0, 0.65f, 2, 1);
        }
        if (D_807FC828[0] > 0) {
            func_806AB808(arg0, 0x91, 0xBE, 0xF, -0xA, D_807FC828[0], 1, 0);
            func_806AB4EC(arg0, (void *)9, 0x91, 0xBE, 1.0f, 2, 1);
        }
        D_8074E77C = arg0->unk14;
        break;
    case 1:
        if (idx != 7) {
            i = idx;
            if (idx != 8) {
                func_806AB808(arg0, 0x1E, 0x2A, 0xC, -0xA, ent->unkA[idx] + ent->unk26[idx], 2, 0);
                func_806AB4EC(arg0, (void *)0, 0x1E, 0x2A, 0.75f, 2, 2);
            } else {
                i = 7;
            }
            if (D_807FC82E > 0) {
                if (idx != 8) {
                    D_807FC80F = (L9ENT(D_8074E77C)->unkA[idx] + L9ENT(D_8074E77C)->unk26[idx]) >= 0x4B;
                } else {
                    D_807FC80F = func_80731A04(0x225, i, i, D_8074E77C);
                }
                func_806AB4EC(arg0, (void *)0xA, 0x113, 0x7D, 0.75f, 2, 2);
                if (func_80731A04(0x225, i, i, D_8074E77C)) {
                    func_806AB4EC(arg0, &D_80721518, 0x113, 0x7D, 0.35f, 2, 0xD);
                }
            }
        }
        if (arg1 == 0) {
            for (i = 0; i < 5; i++) {
                void *s;
                if (D_80750530[i]) {
                    s = D_80750518[i];
                } else {
                    s = &D_807211D0;
                }
                func_806AB4EC(arg0, s, i, i, 0.75f, 2, 0xA);
                func_806AB4EC(arg0, s, i + 5, i + 5, 0.75f, 2, 0xA);
            }
        }
        if (idx != 8) {
            func_806AB4EC(arg0, (void *)9, 0x91, 0xCB, 1.0f, 2, 2);
            sum = 0;
            for (i = 0; i < 5; i++) {
                if (func_80731A04(0x1D5, 0, 7, i)) {
                    sum = 1;
                }
            }
            if (sum) {
                D_807FC80F = func_8073110C(func_807319D8(0x1D5, idx, D_8074E77C), 0);
                func_806AB4EC(arg0, (void *)0xC, 0x26, 0x7D, 0.75f, 2, 2);
                if (func_8073110C(func_807319D8(0x1FD, idx, D_8074E77C), 0)) {
                    func_806AB4EC(arg0, &D_80721518, 0x26, 0x7D, 0.35f, 2, 0xD);
                }
            }
        }
        if (arg1 == 0) {
            arg0->unk10 = D_807505A4[arg0->unk14];
            func_806AB4EC(arg0, &D_80720C34, 0xA0, 0x78, 0.75f, 2, 0);
            if (D_807505D0 > 0) {
                func_806AB4EC(arg0, &D_80720D80, 0xA0, 0x19, 0.5f, 2, 0xB);
                func_806AB4EC(arg0, &D_80720D5C, 0xA0, 0x19, 0.5f, 2, 0xC);
            }
        }
        break;
    case 2:
        sum = 0;
        sum3 = 0;
        for (i = 0; i < 5; i++) {
            sum = sum + L9ENT(i)->unk26[idx] + L9ENT(i)->unkA[idx];
            sum3 += L9ENT(i)->unk42[idx];
        }
        cnt8 = 0;
        for (i = 0; i < 4; i++) {
            found[i] = 0;
        }
        for (i = 0; D_80755DA8[i].unk0 != 0xFF; i++) {
            if (func_805FF030(D_80755DA8[i].unk0, 1) == idx) {
                xs = D_80755DA8[i].unk4;
                if (xs >= 0x24D && xs < 0x261 && cnt8 < 4) {
                    found[cnt8] = func_8073110C(xs, 0);
                    cnt8++;
                }
            }
        }
        if (idx != 7) {
            j = idx;
            if (idx != 8) {
                func_806AB808(arg0, 0x24, 0x2A, 0xC, -0xA, sum, 1, 0);
                func_806AB4EC(arg0, &D_80721474, 0x24, 0x2A, 0.75f, 2, 1);
            } else {
                j = 7;
            }
            i = 0;
            do {
                if (idx != 8) {
                    D_807FC80F = (L9ENT(i)->unkA[idx] + L9ENT(i)->unk26[idx]) >= 0x4B;
                } else {
                    D_807FC80F = func_80731A04(0x225, j, j, i);
                }
                func_806AB4EC(arg0, (void *)0xA, D_807505A4[i], 0, 0.75f, 2, 3);
                if (func_80731A04(0x225, j, j, i)) {
                    func_806AB4EC(arg0, &D_80721518, D_807505A4[i], 0, 0.35f, 2, 0xE);
                }
                i++;
            } while (i != 5);
            if (D_807FC82A > 0) {
                D_807FC80F = func_8073110C(D_807505B8[idx], 0);
                func_806AB4EC(arg0, &D_807210EC, 0xA0, 0x78, 1.0f, 2, 4);
            }
            if (func_8073110C(0x179, 0)) {
                D_807FC80F = found[0];
                func_806AB4EC(arg0, &D_80721094, 0x3C, 0x78, 1.0f, 2, 6);
                D_807FC80F = found[1];
                func_806AB4EC(arg0, &D_80721094, 0x104, 0x78, 1.0f, 2, 6);
            }
        } else {
            if (D_807FC82A > 0) {
                D_807FC80F = func_8073110C(D_807505B8[idx], 0);
                func_806AB4EC(arg0, &D_807210EC, 0xA0, 0x55, 1.0f, 2, 4);
                D_807FC80F = func_8073110C(D_807505CA, 0);
                func_806AB4EC(arg0, &D_807210EC, 0xA0, 0x91, 1.0f, 2, 4);
            }
            if (func_8073110C(0x179, 0)) {
                D_807FC80F = found[0];
                func_806AB4EC(arg0, &D_80721094, 0x3C, 0x5A, 1.0f, 2, 6);
                D_807FC80F = found[1];
                func_806AB4EC(arg0, &D_80721094, 0x46, 0x96, 1.0f, 2, 6);
                D_807FC80F = found[2];
                func_806AB4EC(arg0, &D_80721094, 0x104, 0x5A, 1.0f, 2, 6);
                D_807FC80F = found[3];
                func_806AB4EC(arg0, &D_80721094, 0xFA, 0x96, 1.0f, 2, 6);
            }
        }
        if (idx != 8) {
            func_806AB4EC(arg0, (void *)9, 0x91, 0xCB, 1.0f, 2, 2);
        }
        if (arg1 == 0 && D_807505D0 > 0) {
            func_806AB4EC(arg0, &D_80720D80, 0xA0, 0x19, 0.5f, 2, 0xB);
            func_806AB4EC(arg0, &D_80720D5C, 0xA0, 0x19, 0.5f, 2, 0xC);
        }
        break;
    case 3:
        p = D_807FC828;
        D_807FC83C = 0;
        do {
            if (*p > 0) {
                D_807FC83C++;
            }
            p++;
        } while (p < &D_807FC838);
        D_807FC83A = 0x1000 / D_807FC83C;
        x = 0;
        cnt = 0;
        p = D_807FC828;
        for (i = 0; i < 8; i++, p++) {
            if (*p > 0) {
                if (i != 5) {
                    f = 0.75f;
                    flag = 5;
                } else {
                    f = 1.0f;
                    flag = 8;
                }
                func_806AB4EC(arg0, D_807505D8[i], x, 0, f, 2, flag);
                D_807FC818[cnt] = i;
                cnt++;
                x += D_807FC83A;
            }
        }
        arg0->unk10 = D_807FC83A * D_807FC80C;
        func_806AB4EC(arg0, &D_80720C34, 0xA0, 0x78, 0.75f, 2, 0);
        break;
    }
    if (arg1 == 0 && D_807FC828[0] > 0) {
        func_806AB4EC(arg0, &D_80720D38, 0x2D, 0xC8, 1.0f, 2, 1);
        func_806AB4EC(arg0, &D_8072104C, 0x113, 0xC8, 1.0f, 2, 1);
    }
    D_8074E77C = saved;
}
