// func_80700BF4 (src/global/103AB0.c): stage 6 near-miss (parked NON_MATCHING): identical insns/frame/callee-saved; only saved-reg numbering differs: target y=s3,w-copy=s2 vs ours y=s2,w-copy=s3. Needs p=&D_807FD610[i] ptr var (early li 40/cvt.d.w), int base=0x28 outside loop, r/flag/bad locals for xor order; tried decl order, register kw, dead ifs, permuter.
typedef struct {
    u8 pad0[0x270];
    s16 unk270;
    s16 unk272;
    s16 unk274;
    s16 unk276;
    s16 unk278;
    s16 unk27A;
    u8 pad27C[4];
    f32 unk280;
} AdViewport;

#define ADVP ((AdViewport *)D_807FC924)

extern u8 D_80754BC0;
extern s32 D_807FBB60;
extern s16 D_807FD800;
extern s16 D_807FD802;
extern s16 D_807FD804;
extern s16 D_807FD806;

typedef struct {
    f32 unk0;
    f32 unk4;
    f32 unk8;
} AdPoint;

extern u8 D_807FD838[2][3];
extern AdPoint D_807FD840[2][3];

typedef struct {
    u8 pad0[0x2E];
    s8 unk2E;
    u8 pad2F;
    u8 unk30;
    u8 pad31[3];
} AdD610;

extern AdD610 D_807FD610[];

typedef struct {
    u8 pad0[0x10E];
    s16 unk10E;
    s16 unk110;
    s16 unk112;
    s16 unk114;
    s16 unk116;
    s16 unk118;
    s16 unk11A;
} AdPlayerState;

typedef struct {
    u8 unk0;
    u8 pad1[3];
    Actor *unk4;
    u8 pad8[0x2F0 - 8];
} AdView2F0;

typedef struct {
    u8 pad0[0x174];
    AdPlayerState *unk174;
} AdActor174;

s32 func_80700AE4(s16, s16);
s32 func_807009F4(s16);

void func_80700BF4(void) {
    u8 i;
    AdPlayerState *st;
    s16 x;
    s16 y;
    u16 w;
    s32 base;
    AdD610 *p;
    s32 r;
    s32 flag;
    s32 bad = 0x7FFF;

    if (D_80754BC0 != 0) {
        do {
            D_80754BC0--;
            if ((f32)ADVP->unk270 < D_807FD840[D_807444FC][D_80754BC0].unk0 &&
                D_807FD840[D_807444FC][D_80754BC0].unk0 < (f32)ADVP->unk274 &&
                (f32)ADVP->unk272 < D_807FD840[D_807444FC][D_80754BC0].unk4 &&
                D_807FD840[D_807444FC][D_80754BC0].unk4 < (f32)ADVP->unk276 &&
                !(D_807FBB60 & 2)) {
                if (D_807FD840[D_807444FC][D_80754BC0].unk8 <
                    (f32)func_807009F4(func_80700AE4((s16)D_807FD840[D_807444FC][D_80754BC0].unk0,
                                                     (s16)D_807FD840[D_807444FC][D_80754BC0].unk4))) {
                    D_807FD838[D_807444FC][D_80754BC0] = 5;
                }
            }
        } while (D_80754BC0 != 0);
    }
    r = func_80700AE4(0xA0, 0xDC);
    flag = bad == r;
    if (flag == 0) {
        r = func_80700AE4(0xC, 0x78);
        flag = bad == r;
        if (flag == 0) {
            r = func_80700AE4(0x134, 0x78);
            flag = bad == r;
        }
    }
    D_807FD800 = flag;
    D_807FD802 = func_807009F4(func_80700AE4(D_807FD804, D_807FD806));
    base = 0x28;
    for (i = 0; i < D_807FC928; i++) {
        if (((AdView2F0 *)D_807FC924)[i].unk0 != 0) {
            st = ((AdActor174 *)((AdView2F0 *)D_807FC924)[i].unk4)->unk174;
            p = &D_807FD610[i];
            x = st->unk10E;
            y = st->unk110;
            x += p->unk2E;
            y -= 0x14;
            w = (u32)(base + p->unk30 / 1.5);
            st->unk114 = func_807009F4(func_80700AE4(x, y));
            st->unk116 = func_807009F4(func_80700AE4(x, st->unk112));
            st->unk118 = func_807009F4(func_80700AE4(x - w, y));
            st->unk11A = func_807009F4(func_80700AE4(x + w, y));
        }
    }
}
