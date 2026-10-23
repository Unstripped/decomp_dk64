// func_8064F450 (src/global/54150.c): stage 5: code structurally identical (frame/offsets/regs match); only IDO loop-unroll factor differs (target 2x prologue + 2 iters of 4 records; ours 5 iters of 2) plus s3/s4 swap and branch-likely form on the NULL early path
#include "common.h"

typedef struct M54AVtx {
    u32 unk0;
    f32 unk4;
    u16 unk8;
    u16 unkA;
    u16 unkC;
    u8 unkE;
    u8 unkF;
    u8 unk10;
    u8 unk11;
    u8 unk12;
    u8 unk13;
} M54AVtx; /* 0x14 */

typedef struct M54AModel {
    u8 *unk0;
    u8 *unk4;
    M54AVtx unk8[10];
} M54AModel; /* 0xD0 */

void *func_80610FE8(s32);
void *memcpy(void *, const void *, unsigned int);

void func_8064F450(M54AModel **arg0, u8 *arg1) {
    M54AModel *m;
    u8 *src;
    u32 size;
    u32 n;
    u32 i;
    u8 *p1;
    u8 *p2;

    if (*(u32 *)(arg1 + 0x68) == *(u32 *)(arg1 + 0x64)) {
        *arg0 = NULL;
    } else {
    m = func_80610FE8(0xD0);
    *arg0 = m;
    n = *(u32 *)(arg1 + *(u32 *)(arg1 + 0x68));
    m->unk0 = func_80610FE8(n);
    m->unk4 = func_80610FE8(n);
    src = arg1 + *(u32 *)(arg1 + 0x68);
    size = *(u32 *)(src + 4);
    memcpy(m->unk0, src + 8, size);
    memcpy(m->unk4, src + 8, size);
    p1 = m->unk0 + size;
    p2 = m->unk4 + size;
    for (i = (n - size) >> 6; i != 0; i--) {
        guMtxIdent((Mtx *)p1);
        guMtxIdent((Mtx *)p2);
        p1 += 0x40;
        p2 += 0x40;
    }
    src = arg1 + *(u32 *)(arg1 + 0x64);
    for (i = 0; i < 10; i++) {
        m->unk8[i].unk0 = (u32)src + *(u32 *)(src + i * 4);
        m->unk8[i].unk4 = 0.0f;
        m->unk8[i].unk8 = 0;
        m->unk8[i].unkA = 0;
        m->unk8[i].unkC = 1;
        m->unk8[i].unkE = 0;
        m->unk8[i].unkF = 0;
        m->unk8[i].unk10 = 0;
        m->unk8[i].unk11 = 0;
        m->unk8[i].unk12 = 0;
        m->unk8[i].unk13 = 0;
    }
    }
}
