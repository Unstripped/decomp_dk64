// func_8002597C (src/race/1770.c): stage 5 (parked NON_MATCHING in copy; frame 0x50, s0-s2 and stack homes match, 3 diff lines): only register swap left: target src2 (tbl[0] reload) in s2 and dst (tbl[2]) in t2, ours reversed, plus addu operand order a1=a2+s2 vs s2+a2. Found by partition search of variable sharing: one pointer var p0 reused for buf, memcpy dst args and mid; p1 for orig and dst; extra named temps for memcpy dst args (p0 = tbl[0]; memcpy(p0,...)); u32 sz = count * 12 gives single a2 spill.
typedef struct {
    f32 x, y, z;
} RaceAPoint3f;
extern s32 *D_807F5FD4;
extern s32 D_807F5FD0;
void *memcpy(void *, const void *, unsigned int);
void *func_80610FE8(s32);

void func_8002597C(void) {
    RaceAPoint3f *buf, *src, *lo;
    s32 i;
    RaceAPoint3f **tbl;
    s32 count;
    u32 sz;

    count = (D_807F5FD4[1] - D_807F5FD4[0]) / 12 / 2;
    buf = func_80610FE8(count * 0x24);
    tbl = func_80610FE8(0x10);
    for (i = 0; i < 4; i++) {
        tbl[i] = (RaceAPoint3f *)((u8 *)buf + i * count * 12);
    }
    src = (RaceAPoint3f *)D_807F5FD4[0];
    sz = count * 12;
    buf = tbl[0];
    memcpy(buf, src, sz);
    buf = tbl[2];
    memcpy(buf, (u8 *)src + sz, sz);
    buf = tbl[1];
    lo = tbl[0];
    src = tbl[2];
    for (i = 0; i < count; i++) {
        buf[i].x = (lo[i].x + src[i].x) * 0.5;
        buf[i].y = (lo[i].y + src[i].y) * 0.5;
        buf[i].z = (lo[i].z + src[i].z) * 0.5;
    }
    D_807F5FD0 = 3;
    D_807F5FD4 = (s32 *)tbl;
}
