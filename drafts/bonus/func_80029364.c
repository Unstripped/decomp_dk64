// func_80029364 (src/bonus/2690.c): stage 5: frame 0x58 + callee-saved set match; code identical except 3 v0/v1-vs-ring temp sites in the D_8002D8F8/FC arms (chain1 lh v1, andi v1, else-arm li v0/v1 consts). D_8002D8F8/FC stores via ((s16*)&D_8002D8F4)[2/4] (splits lda CSE), do-while(++i<6) unroll loop, 6x & 0xFFu ring-burn on r
typedef struct {
    s16 unk0;
    char pad2[2];
    f32 unk4;
    s8 unk8[6];
    s16 unkE;
    char pad10;
    u8 unk11;
    u8 unk12;
    char pad13;
    s16 unk14;
    s16 unk16;
} LargeB2_Sub178;

typedef struct LargeB2_Actor {
    char pad0[0x60];
    s32 unk60;
    char pad64[0x84];
    s16 unkE8;
    char padEA[0x11C - 0xEA];
    struct LargeB2_Actor *unk11C;
    char pad120[0x154 - 0x120];
    u8 unk154;
    char pad155[0x16A - 0x155];
    u8 unk16A;
    u8 unk16B;
    u8 unk16C;
    char pad16D[0x174 - 0x16D];
    BonusB2_Sub174 *unk174;
    LargeB2_Sub178 *unk178;
} LargeB2_Actor;

#define LB2 ((LargeB2_Actor *)D_807FBB40)

extern s8 D_8002D8F4;
extern s16 D_8002D8F8;
extern s16 D_8002D8FC;
extern s16 D_8002D8EC[];
void lightSetColor(f32, f32, f32, s32);
void func_80029E54(void *);
Gfx *func_80029B9C(Gfx *, Actor_BB44 *);

void func_80029364(void) {
    BonusB2_Sub174 *t1 = LB2->unk174;
    LargeB2_Sub178 *t0 = LB2->unk178;
    Point3f *p;
    f32 y;
    f32 z;
    s32 pad;
    s32 i;
    s32 j;
    s32 r;
    u8 c;
    s16 d;

    if (!(LB2->unk60 & 0x10)) {
        t1->unk23 = 5;
        t1->unk0 = -2;
        switch (D_8076A0A8) {
        case 0x65:
            t0->unk16 = 0xA;
            D_8002D8F4 = 0x30;
            break;
        case 0x8D:
            t0->unk16 = 0xF;
            D_8002D8F4 = 0x30;
            break;
        case 0x8E:
            t0->unk16 = 5;
            D_8002D8F4 = 0x1E;
            break;
        case 0x8F:
            t0->unk16 = 0xA;
            D_8002D8F4 = 0x1E;
            break;
        }
        t0->unk14 = t0->unk16;
        t0->unkE = 0x3C;
        t0->unk12 = 0;
        c = func_806FDB8C(1, func_8070E750(0x1A, 2, 1), 8, 0.0f, 0.0f, 0.0f);
        t0->unk11 = c;
        func_806FDAB8(c, 0.0f);
        t0->unk0 = 0x3C;
        t0->unk4 = 1.0f;
        playerStateQueueCallback(0x48, 0, 0);
        camSetTarget(*(void **)((u8 *)D_807FD580 + 0x104), D_807FBB40, 4, 0x800, 0x1A, 0, 0x1F, 0x15, 0x10, 0, 0.05f);
        camStartPath(0, 0, 1);
        LB2->unkE8 = 0x9A;
        LB2->unk60 |= 0x800000;
        LB2->unk16A = 0xFF;
        LB2->unk16B = 0xFF;
        LB2->unk16C = 0xFF;
        i = 0;
        do {
            t0->unk8[i] = i | 0x80;
        } while (++i < 6);
        func_80029E54(D_807FBB40);
    }
    if (t1->unk0 > 0) {
        if (LB2->unk154 == 0) {
            t0->unk0 -= 1;
        } else {
            t0->unk0 = 0x3C;
        }
        if (t0->unk0 > 0) {
            t0->unk4 = t0->unk4 + 0.2f;
        } else {
            t0->unk4 = t0->unk4 - 0.2f;
        }
        if (t0->unk4 > 1.0) {
            t0->unk4 = 1.0f;
        }
        if (t0->unk4 < 0.0) {
            t0->unk4 = 0.0f;
        }
        lightSetColor(t0->unk4, t0->unk4, t0->unk4, 0);
        if (t0->unk4 == 0.0f) {
            d = D_8002D8F8 - 1;
            ((s16 *)&D_8002D8F4)[2] = d;
            if (d <= 0) {
                func_80609140(0x1A1, 0x7FFF, 63.0f, 1.0f, 0x50, 0);
                D_8002D8F8 = (func_806119A0() & 3) + 2;
            }
            d = D_8002D8FC + 1;
            ((s16 *)&D_8002D8F4)[4] = d;
            if (d == 0xE) {
                func_80609140(D_8002D8EC[func_806119A0() & 3], 0x7FFF, 63.0f, 1.0f, 0x14, 0);
            }
        } else {
            if (func_806119FC() < 0.5f) {
                D_8002D8FC = 0;
            } else {
                D_8002D8FC = -0x64;
            }
            D_8002D8F8 = 1;
        }
        if (t0->unk0 < -0x1E) {
            t0->unk0 = D_8002D8F4;
            i = 0;
            do {
                t0->unk8[i] = -1;
                i++;
            } while (i < 6);
            for (i = 0; i != 6; i++) {
                j = i;
                r = ((((((func_806119A0() & 0xFFu) & 0xFFu) & 0xFFu) & 0xFFu) & 0xFFu) & 0xFFu) & 7;
                while (r >= 0) {
                    if (t0->unk8[j] == -1) {
                        r -= 1;
                        if (r >= 0) {
                            j += 1;
                        }
                    } else {
                        j += 1;
                    }
                    if (j >= 6) {
                        j = 0;
                    }
                }
                t0->unk8[j] = i | 0x80;
            }
        }
        t1->unk22 = 0;
        if (LB2->unk154 == 0 && (D_807FD610.unk30 >= 0x1F || D_807FD610.unk31 >= 0x1F)) {
            if (D_807FD610.unk2F > 0) {
                if (D_807FD610.unk2E < -0x28) {
                    t1->unk22 = 1;
                } else if (D_807FD610.unk2E >= 0x29) {
                    t1->unk22 = 3;
                } else {
                    t1->unk22 = 2;
                }
            } else if (D_807FD610.unk2E < -0x28) {
                t1->unk22 = 4;
            } else if (D_807FD610.unk2E >= 0x29) {
                t1->unk22 = 5;
            } else {
                t1->unk22 = 6;
            }
        }
        p = *D_807F5FD4 + t1->unk22;
        y = p->y;
        z = p->z;
        if (t1->unk22 != 0) {
            y += 27.0f;
            z -= 8.0f;
        }
        switch (func_80027548(p->x, y, z)) {
        case 1:
            break;
        case 2:
            t1->unk25 = 0xFF;
            func_80609140(0x3BC, 0x7FFF, 63.0f, 1.0f, 0, 0);
            break;
        }
        switch (LB2->unk154) {
        case 0:
            if (t0->unk14 == 0) {
                LB2->unk154 = 2;
            }
            if (LB2->unk11C->unk154 == 5) {
                LB2->unk154 = 1;
            }
            break;
        case 1:
            func_800265C0(0, 1);
            camStartPath(0, 1, 0x11);
            LB2->unk154 = 3;
            break;
        case 2:
            func_800264E0(0, 0);
            camStartPath(0, 1, 0x11);
            LB2->unk154 = 3;
            break;
        }
    } else {
        switch (t1->unk0) {
        case -2:
            if (D_807444EC != 1) {
                t1->unk0++;
                func_806A2A10(0xDC, 0x2A, ((u8 *)t0)[0xF]);
                func_8070D8C0(D_807FBB40, 0, 9);
            }
            break;
        case -1:
            if (!(LB2->unk60 & 0x2000000)) {
                t1->unk0 = 1;
                actorSetStateTwo(LB2->unk11C);
                func_8002733C(t1);
                sfxAllocateChannel(8, 1.0f);
            }
            break;
        }
    }
    renderCallbacksRegister(func_80029B9C, D_807FBB40, 3);
    actorUpdateModelMatrix(D_807FBB40, 0);
}
