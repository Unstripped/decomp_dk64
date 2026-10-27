// func_806264DC (src/global/201B0.c): CamF2: stage 5, same callee-saved set + frame 0xB8 + instruction stream; only regalloc/scheduling diffs: temps v1/a1, part-2 cursor s1 vs s0 (target s0, copy s0, li s1,28), part-3 lw/multu order, part-4 pt/u (target addu t9 store addr + separate addu s2,v1,v0;addiu s2,4; mine s2 direct), jtbl reloc naming. Needs volatile u8 arg2 (K&R) to keep arg2 unpromoted (lbu 0xC3(sp)); unsigned multiplies (cnt*0x12U) give shift expansion; hdr read as *hdr++ twice in part 3.
typedef struct CamF2Seg {
    /* 0x00 */ s16 a[3];
    /* 0x06 */ s16 b[3];
    /* 0x0C */ s16 c[3];
} CamF2Seg; // size = 0x12

typedef struct CamF2Bnd {
    /* 0x00 */ s16 v[14];
} CamF2Bnd; // size = 0x1C

typedef struct CamF2E {
    /* 0x00 */ s16 v[7];
} CamF2E; // size = 0xE

typedef struct CamF2Q {
    /* 0x00 */ s16 v[4];
} CamF2Q; // size = 0x8

typedef struct CamF2Head {
    /* 0x00 */ s16 unk0;
    /* 0x02 */ s16 pad2;
    /* 0x04 */ CamF2Seg *unk4;
} CamF2Head; // size = 0x8

typedef struct CamF2List {
    /* 0x0 */ s16 unk0;
    /* 0x2 */ s16 pad2;
    /* 0x4 */ s16 *unk4;
    /* 0x8 */ s16 *unk8;
} CamF2List; // size = 0xC

typedef struct CamF2Path {
    /* 0x00 */ CamF2Head heads[24];
    /* 0xC0 */ s16 unkC0;
    /* 0xC2 */ s16 padC2;
    /* 0xC4 */ CamF2Bnd *unkC4;
    /* 0xC8 */ s8 *unkC8;
    /* 0xCC */ s16 unkCC;
    /* 0xCE */ s16 padCE;
    /* 0xD0 */ CamF2List *unkD0;
    /* 0xD4 */ s16 unkD4;
    /* 0xD6 */ s16 padD6;
    /* 0xD8 */ CamPathPoint *unkD8;
} CamF2Path;

void *func_80610FE8(s32);
void heapClearBlock(void *);
void func_80626478(s16 *, s16 *);
u8 *func_8062649C(u8 *, void *, u16);

void func_806264DC(arg0, arg1, arg2) s16 *arg0; CamF2Path *arg1; volatile u8 arg2; {
    s16 i;
    s16 j;
    s16 cnt;
    s16 *hdr;
    u8 *data;
    CamF2Head *h;
    CamF2Seg *dst;
    CamPathPoint *pt;
    s16 *s;
    u8 *rd;
    s32 padf1;
    s32 padf2;
    s32 padf3;
    s32 padf4;
    s32 padf5;
    CamF2Seg buf;
    CamPathSpline *u;
    s16 m;
    s16 k;
    s32 padg1;
    s32 padg2;
    s32 padg3;
    s32 skip;

    hdr = arg0;
    data = arg0 != NULL ? (u8 *)arg0 + 0x30 : NULL;
    for (i = 0; i < 0x18; i++) {
        h = &arg1->heads[i];
        cnt = h->unk0 = hdr != NULL ? *hdr++ : 0;
        if (arg2 != 0) {
            h->unk4 = func_80610FE8(cnt * 0x12U);
            for (j = 0; j < cnt; j++) {
                dst = &h->unk4[j];
                buf = *(CamF2Seg *)data;
                data += 0x12;
                func_80626478(dst->a, buf.a);
                func_80626478(dst->c, buf.c);
                func_80626478(dst->b, buf.b);
            }
        }
    }
    hdr = (s16 *)data;
    cnt = arg1->unkC0 = hdr != NULL ? *hdr++ : 0;
    if (arg2 != 0) {
        arg1->unkC8 = func_80610FE8(cnt);
        arg1->unkC4 = func_80610FE8(cnt * 0x1CU);
        s = hdr;
        for (i = 0; i < cnt; i++) {
            arg1->unkC8[i] = func_806531B8(s[8], s[9], s[10], 0);
            s += 0xE;
            arg1->unkC4[i] = *(CamF2Bnd *)(s - 0xE);
        }
        hdr = s;
    }
    i = 0;
    cnt = arg1->unkCC = hdr != NULL ? *hdr++ : 0;
    arg1->unkD0 = func_80610FE8(cnt * 0xCU);
    for (i = 0; i < cnt; i++) {
        m = *hdr++;
        k = m;

        arg1->unkD0[i].unk0 = m;
        arg1->unkD0[i].unk4 = func_80610FE8(m * 2);
        arg1->unkD0[i].unk8 = func_80610FE8(m * 2);
        for (j = 0; j < k; j++) {
            arg1->unkD0[i].unk4[j] = *hdr++;
            arg1->unkD0[i].unk8[j] = *hdr++;
        }
    }
    i = 0;
    cnt = arg1->unkD4 = hdr != NULL ? *hdr++ : 0;
    arg1->unkD8 = func_80610FE8(0x6400);
    heapClearBlock(arg1->unkD8);
    rd = (u8 *)hdr;
    if (cnt != 0) {
        do {
            skip = 0;
            pt = &arg1->unkD8[i];
            pt->unk1 = rd[1];
            arg1->unkD8[i].unk0 = rd[0];
            pt = (CamPathPoint *)&pt->u.spline;
            u = (CamPathSpline *)pt;
            switch (arg1->unkD8[i].unk1) {
                case 13:
                    rd = func_8062649C(rd, u, 0xC);
                    break;
                case 12:
                    rd = func_8062649C(rd, u, 2);
                    break;
                case 10:
                case 15:
                case 16:
                    rd = func_8062649C(rd, u, 0xE);
                    break;
                case 1:
                    rd = func_8062649C(rd, u, 6);
                    break;
                case 2:
                    rd = func_8062649C(rd, u, 8);
                    break;
                case 3:
                    rd = func_8062649C(rd, u, 0xC);
                    break;
                case 4:
                    s = (s16 *)(rd + 0x20);
                    j = 0;
                    u->unk0 = *(s16 *)(rd + 4);
                    u->unk4 = func_80610FE8(u->unk0 * 0xEU);
                    for (; j < u->unk0; j++) {
                        ((CamF2E *)u->unk4)[j] = *(CamF2E *)s;
                        s += 7;
                    }
                    rd = (u8 *)s;
                    break;
                case 5:
                    s = (s16 *)(rd + 0x14);
                    j = 0;
                    u->unk0 = *(s16 *)(rd + 4);
                    u->unk4 = func_80610FE8(u->unk0 * 8U);
                    for (; j < u->unk0; j++) {
                        ((CamF2Q *)u->unk4)[j] = *(CamF2Q *)s;
                        s += 4;
                    }
                    rd = (u8 *)s;
                    break;
                default:
                    rd = func_8062649C(rd, u, 0);
                    skip = 1;
                    break;
            }
            if (skip == 0) {
                cnt--;
            }
            i++;
        } while (cnt != 0);
    }
}
