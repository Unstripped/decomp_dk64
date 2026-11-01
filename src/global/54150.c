#include "common.h"
#include "actor.h"

typedef struct ModelVertex {
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
} ModelVertex; /* 0x14 */

typedef struct ModelData {
    u8 *unk0;
    u8 *unk4;
    ModelVertex unk8[10];
} ModelData; /* 0xD0 */

void *heapAlloc(s32);
void *memcpy(void *, const void *, unsigned int);

void func_8064F450(ModelData **arg0, u8 *arg1) {
    u8 *p2;
    u32 n;
    u8 *p1;
    u8 *src;
    u32 size;
    ModelData *m;
    u32 i;

    if (*(u32 *)(arg1 + 0x68) != *(u32 *)(arg1 + 0x64)) {
        m = heapAlloc(0xD0);
        *arg0 = m;
        n = *(u32 *)(arg1 + *(u32 *)(arg1 + 0x68));
        m->unk0 = heapAlloc(n);
        m->unk4 = heapAlloc(n);
        src = arg1 + *(u32 *)(arg1 + 0x68);
        size = *(u32 *)(src + 4);
        memcpy(m->unk0, src + 8, size);
        memcpy(m->unk4, src + 8, size);
        i = (n - size) >> 6;
        p1 = m->unk0 + size;
        p2 = m->unk4 + size;
        for (; i != 0; i--) {
            guMtxIdent((Mtx *)p1);
            guMtxIdent((Mtx *)p2);
            p1 += 0x40;
            p2 += 0x40;
        }
        {
            u8 *q = arg1 + *(u32 *)(arg1 + 0x64);
            s32 j;

            for (j = 0; j < 10; j++) {
                ModelVertex *v = &m->unk8[j];
                v->unk0 = (u32)q + *(u32 *)(q + j * 4);
                v->unk4 = 0.0f;
                v->unk8 = 0;
                v->unkA = 0;
                v->unkE = 0;
                v->unkF = 0;
                v->unk10 = 0;
                v->unk11 = 0;
                v->unkC = 1;
                v->unk12 = 0;
                v->unk13 = 0;
            }
        }
    } else {
        *arg0 = NULL;
    }
}

typedef struct ModelSlot {
    u8 pad0[0x24];
    u8 *unk24;
    u8 pad28[0x50];
    u8 *unk78;
    u8 pad7C[0x14];
} ModelSlot; /* 0x90 */

typedef struct ModelAnimEntryRaw {
    u8 *unk0;
    u32 unk4;
    u8 pad8[6];
    u8 unkE;
    u8 padF[2];
    u8 unk11;
    u8 pad12;
    u8 unk13;
} ModelAnimEntryRaw;

extern ModelSlot *D_807F6000;

u32 modelSlotDataSize(arg0)
s16 arg0;
{
    u8 *p = D_807F6000[arg0].unk24;

    return *(u32 *)(p + *(s32 *)(p + 0x68));
}

typedef struct ModelSlotBuf {
    u32 unk0;
    u32 unk4;
} ModelSlotBuf;

void modelSlotGetTransformVectors();
void func_806358E8(s16, s32, s32, s32, f32, f32, f32, f32, f32, s32, s32, s32, s32, s32);

void modelSlotCopyData(arg0, arg1)
s16 arg1;
u8 *arg0;
{
    u8 *obj;
    u8 **dst;
    s32 n;
    s32 x;
    s32 y;
    s32 z;
    f32 a;
    f32 b;
    f32 c;
    f32 d;
    f32 e;

    obj = D_807F6000[arg1].unk24;
    dst = (u8 **)D_807F6000[arg1].unk78;
    n = *(s32 *)(obj + *(s32 *)(obj + 0x68));
    memcpy(dst[0], arg0, n);
    memcpy(dst[1], arg0, n);
    modelSlotGetTransformVectors(arg1, &x, &y, &z, &a, &b, &c, &d, &e, 0);
    func_806358E8(arg1, x, y, z, a, b, c, d, e, 0, 0, 0, 0, 1);
}

void heapFreeDeferred(void *);
void heapFree(void *);
void mtxCopyQueueCancelGroup();

void modelSlotFree(u8 **arg0) {
    if (arg0 != NULL) {
        heapFreeDeferred(arg0[0]);
        heapFreeDeferred(arg0[1]);
        mtxCopyQueueCancelGroup(arg0);
        heapFree(arg0);
    }
}

extern u32 D_807F6BE0;
extern u32 D_807F6BE4;
extern u32 D_807F6BE8;
extern u8 D_807F6BEC;
extern u8 D_807444FC;
s32 hashTableLookup();
void mtxCopyQueueFlush();
void modelAnimEntryStep(void *);

u8 modelSlotStepAnimations(arg0)
s16 arg0;
{
    u32 *base;
    u8 *p;
    s32 i;

    base = (u32 *)D_807F6000[hashTableLookup(arg0)].unk78;
    D_807F6BEC = 0;
    if (base != NULL) {
        D_807F6BE0 = base[D_807444FC];
        D_807F6BE4 = base[D_807444FC ^ 1];
        D_807F6BE8 = (u32)base;
        i = 0;
        p = (u8 *)base;
        for (; i != 0xC8; i += 0x14) {
            if (p[0x16] == 1) {
                modelAnimEntryStep(p + 8);
                D_807F6BEC = 1;
            }
            p += 0x14;
        }
        mtxCopyQueueFlush(base);
    }
    return D_807F6BEC;
}

void modelAnimEntryAdvance();
void func_8064F97C(ModelAnimEntryRaw *);

void modelAnimEntryStep(void *arg0) {
    modelAnimEntryAdvance(arg0);
    func_8064F97C(arg0);
}

void modelAnimEntryBuildKeyMatrix();
void mtxCopyQueuePush();
void mtxCopyQueueCancelDest();

void func_8064F97C(ModelAnimEntryRaw *arg0) {
    u8 *node;
    s16 stride;
    s32 i;
    u8 *p;
    u32 a;
    u32 b;
    u32 c;
    u32 d;

    node = arg0->unk0;
    stride = *(u8 *)node * 0x24 + 8;
    a = D_807F6BE0;
    b = D_807F6BE4;
    i = 0;
    p = node + 0x3C;
    while (i < *(u8 *)(node + 0x39)) {
        modelAnimEntryBuildKeyMatrix(arg0->unk11, arg0->unk4, p, p + 8, arg0->unk13);
        c = *(u32 *)p + b;
        if (arg0->unkE == 0) {
            d = *(u32 *)p + a;
            mtxCopyQueuePush(D_807F6BE8, d, c);
        } else {
            mtxCopyQueueCancelDest(c);
        }
        i++;
        p += stride;
    }
}

void func_8064FA7C(u32 *arg0, u32 *arg1) {
    u8 *node;
    s16 stride;
    s32 i;
    u8 *p;
    u32 a;
    u32 b;
    u32 c;

    node = (u8 *)*arg1;
    stride = *(u8 *)node * 0x24 + 8;
    a = D_807F6BE0 = arg0[D_807444FC ^ 1];
    b = D_807F6BE4 = arg0[D_807444FC];
    if (D_807444FC == 0) {}  // FAKE: deadsweep dead statement (extends D_807444FC live range: v1 not v0, address temps a2/a3)
    p = node + 0x3C;
    i = 0;
    while (i < *(u8 *)(node + 0x39)) {
        c = *(u32 *)p + b;
        mtxCopyQueuePush(arg0, *(u32 *)p + a, c);
        i++;
        p += stride;
    }
    if (D_807444FC && D_807444FC) {}  // FAKE: deadsweep dead statement (extends D_807444FC live range: v1 not v0, address temps a2/a3)
}

#ifdef NON_MATCHING
typedef struct ModelBTrack {
    u8 *unk0;
    u8 *unk4;
} ModelBTrack;

typedef struct ModelBKey {
    f32 unk0;
    f32 unk4;
    f32 unk8;
    f32 unkC;
    f32 unk10;
    f32 unk14;
    f32 unk18;
    f32 unk1C;
    f32 unk20;
} ModelBKey; /* 0x24 */

void matrixMakeRotationX(f32 (*)[4], f32);
void matrixMakeRotationY(f32 (*)[4], f32);
void matrixMakeRotationZ(f32 (*)[4], f32);

void modelAnimEntryBuildKeyMatrix(arg0, arg1, arg2, arg3, arg4)
u8 arg0;
u32 arg1;
ModelBTrack *arg2;
u8 *arg3;
u8 arg4;
{
    u32 off;
    f32 x;
    f32 y;
    f32 z;
    f32 c6;
    f32 c7;
    f32 c8;
    f32 c0;
    f32 c1;
    f32 c2;
    float work[4][4];
    float mtx[4][4];
    s32 padB[5];

    off = D_807F6BE0;
    x = ((ModelBKey *)arg3)[arg0 + 1].unkC - ((ModelBKey *)arg3)[arg0].unkC;
    if (x < -180.0) {
        x += 360.0;
    } else if (x > 180.0) {
        x -= 360.0;
    }
    x *= (*(f32 *)&arg1);
    x += ((ModelBKey *)arg3)[arg0].unkC;
    y = ((ModelBKey *)arg3)[arg0 + 1].unk10 - ((ModelBKey *)arg3)[arg0].unk10;
    if (y < -180.0) {
        y += 360.0;
    } else if (y > 180.0) {
        y -= 360.0;
    }
    if (off == 0) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
    y *= (*(f32 *)&arg1);
    y += ((ModelBKey *)arg3)[arg0].unk10;
    z = ((ModelBKey *)arg3)[arg0 + 1].unk14 - ((ModelBKey *)arg3)[arg0].unk14;
    if (z < -180.0) {
        z += 360.0;
    } else if (z > 180.0) {
        z -= 360.0;
    }
    z *= (*(f32 *)&arg1);
    z += ((ModelBKey *)arg3)[arg0].unk14;
    c6 = ((ModelBKey *)arg3)[arg0 + 1].unk18 - ((ModelBKey *)arg3)[arg0].unk18;
    c6 *= (*(f32 *)&arg1);
    c6 += ((ModelBKey *)arg3)[arg0].unk18;
    if (arg0 != 0) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
    c7 = ((ModelBKey *)arg3)[arg0 + 1].unk1C - ((ModelBKey *)arg3)[arg0].unk1C;
    c7 *= (*(f32 *)&arg1);
    c7 += ((ModelBKey *)arg3)[arg0].unk1C;
    c8 = ((ModelBKey *)arg3)[arg0 + 1].unk20 - ((ModelBKey *)arg3)[arg0].unk20;
    c8 *= (*(f32 *)&arg1);
    c8 += ((ModelBKey *)arg3)[arg0].unk20;
    c0 = (((ModelBKey *)arg3)[arg0 + 1].unk0 - ((ModelBKey *)arg3)[arg0].unk0) * (*(f32 *)&arg1) + ((ModelBKey *)arg3)[arg0].unk0;
    c1 = (((ModelBKey *)arg3)[arg0 + 1].unk4 - ((ModelBKey *)arg3)[arg0].unk4) * (*(f32 *)&arg1) + ((ModelBKey *)arg3)[arg0].unk4;
    if (work && work) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
    if (arg4 == 0) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
    c2 = (((ModelBKey *)arg3)[arg0 + 1].unk8 - ((ModelBKey *)arg3)[arg0].unk8) * (*(f32 *)&arg1) + ((ModelBKey *)arg3)[arg0].unk8;
    if (x && x) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
    switch (arg4 & 0xF) {
    case 0:
        break;
    case 1:
        c6 *= (f32)(((arg4 >> 4) & 0xF) * 0.125);
        break;
        if (off) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
    case 2:
        c7 *= (f32)(((arg4 >> 4) & 0xF) * 0.125);
        if (work == 0) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
        break;
    case 3:
        c8 *= (f32)(((arg4 >> 4) & 0xF) * 0.125);
        break;
    case 4:
        if (c7) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
        if (work && work) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
        x *= (f32)(((arg4 >> 4) & 0xF) * 0.125);
        break;
    case 5:
        y *= (f32)(((arg4 >> 4) & 0xF) * 0.125);
        break;
    case 6:
        z *= (f32)(((arg4 >> 4) & 0xF) * 0.125);
        break;
    case 7:
        if (c6 == 0) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
        c0 *= (f32)(((arg4 >> 4) & 0xF) * 0.125);
        break;
    case 8:
        c1 *= (f32)(((arg4 >> 4) & 0xF) * 0.125);
        break;
    case 9:
        c2 *= (f32)(((arg4 >> 4) & 0xF) * 0.125);
        break;
    }
    memcpy(work, arg2->unk4 + off, 0x40);
    guScaleF(mtx, c0, c1, c2);
    guMtxCatF(work, mtx, work);
    matrixMakeRotationZ(mtx, z);
    guMtxCatF(work, mtx, work);
    matrixMakeRotationY(mtx, y);
    guMtxCatF(work, mtx, work);
    matrixMakeRotationX(mtx, x);
    guMtxCatF(work, mtx, work);
    guTranslateF(mtx, c6, c7, c8);
    guMtxCatF(work, mtx, work);
    memcpy(mtx, arg2->unk4 + off + 0x40, 0x40);
    guMtxCatF(work, mtx, work);
    guMtxF2L(work, (Mtx *)(arg2->unk0 + off));
    if (c2 != 0) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
}
#else

#pragma GLOBAL_ASM("asm/global/nonmatchings/54150/modelAnimEntryBuildKeyMatrix.s")
#endif

typedef struct ModelAnimEntryView {
    u8 *unk0;
    f32 unk4;
    s16 unk8;
    s16 unkA;
    s16 unkC;
    u8 unkE;
    u8 unkF;
    u8 unk10;
    s8 unk11;
    u8 unk12;
    u8 unk13;
} ModelAnimEntryView;

extern u32 D_80744478;

void modelAnimEntryAdvance(ModelAnimEntryView *arg0) {
    u8 *node;
    u8 *p;
    u32 limit;
    f32 qq;
    f32 out;
    s32 i;
    s32 q;

    node = arg0->unk0;
    if (arg0->unk11) {} // FAKE: raises the arg0->unk11 candidate priority (v1 vs a1 swap)
    p = (u8 *)((u32)node + arg0->unk11); // FAKE: u32 cast flips the addu operand order (node, idx)
    qq = (f32)((f64)((f32)(p[2] - p[1]) * arg0->unk4 + (f32)(u32)p[1]) / 300.0);
    out = (f32)arg0->unkC * qq;
    if (D_80744478 < 4) {
        limit = D_80744478;
    } else {
        limit = 4;
    }
    if (arg0->unk12 & 1) {
        out = (f64)out * ((f64)limit * 0.5);
    }
    switch (arg0->unkF) {
    case 0:
        arg0->unk4 += out;
        i = arg0->unk4;
        arg0->unk11 += i;
        arg0->unk4 -= (f32)i;
        if (arg0->unk11 < *(u8 *)node - 1) {
            return;
        }
        arg0->unk8 += arg0->unk11 / (*(u8 *)node - 1);
        if (arg0->unk8 >= arg0->unkA && arg0->unkA != -1) {
            arg0->unk4 = 1.0f;
            arg0->unk11 = *(u8 *)node - 2;
            arg0->unkE = 0;
            if (arg0->unk10 == 1) {
                arg0->unkF = 1;
            }
        } else {
            switch (arg0->unk10) {
            case 0:
                arg0->unk11 = arg0->unk11 % (*(u8 *)node - 1);
                break;
            case 1:
                q = arg0->unk11 / (*(u8 *)node - 1);
                if (q != 0) {
                    arg0->unkF = 1;
                    arg0->unk11 = *(u8 *)node - 2;
                    arg0->unk4 = 1.0f;
                }
                break;
            }
        }
        break;
    case 1:
        arg0->unk4 -= out;
        if (arg0->unk4 < 0.0) {
            i = (s32)arg0->unk4 - 1;
            arg0->unk11 += i;
            arg0->unk4 -= (f32)i;
        }
        if (arg0->unk11 < 0) {
            arg0->unk8 += (-arg0->unk11) / *(u8 *)node + 1;
            if (arg0->unk8 >= arg0->unkA && arg0->unkA != -1) {
                if (arg0->unk10 == 1) {
                    arg0->unkF = 0;
                }
                arg0->unk4 = 0.0f;
                arg0->unk11 = 0;
                arg0->unkE = 0;
            } else {
                switch (arg0->unk10) {
                case 0:
                    arg0->unk11 = (-arg0->unk11) % (*(u8 *)node - 1);
                    if (arg0->unk11 != 0) {
                        arg0->unk11 = *(u8 *)node - arg0->unk11 - 1;
                    }
                    break;
                case 1:
                    q = (-arg0->unk11) / *(u8 *)node + 1;
                    if (q) {
                        arg0->unkF = 0;
                        arg0->unk11 = 0;
                        arg0->unk4 = 0.0f;
                    }
                    break;
                }
            }
        }
        break;
    }
}


typedef struct MtxCopyRequest {
    s32 unk0;
    s32 unk4;
    s32 unk8;
    u8 unkC;
    u8 padD[3];
} MtxCopyRequest;

typedef struct ModelAnimEntry {
    u8 *unk0;
    f32 unk4;
    s16 unk8;
    s16 unkA;
    s16 unkC;
    u8 unkE;
    u8 unkF;
    u8 unk10;
    s8 unk11;
    u8 unk12;
    u8 unk13;
} ModelAnimEntry;

typedef struct ModelAnimGroup {
    u8 *unk0;
    u8 *unk4;
    ModelAnimEntry entries[1];
} ModelAnimGroup;

extern MtxCopyRequest D_807F6960[];
void faultSetMessage(s32, s32, s32, s32);
void func_8064FA7C();

void func_8065051C(void) {
    s32 i;

    for (i = 0; i < 0x28; i++) {
        D_807F6960[i].unk0 = 0;
    }
}

void mtxCopyQueuePush(s32 arg0, s32 arg1, s32 arg2) {
    s32 found;
    s32 i;

    found = 0;
    i = 0;
    while (found == 0 && i < 0x28) {
        if (D_807F6960[i].unk0 == 0) {
            found = 1;
        } else {
            i++;
        }
    }

    if (found != 0) {
        D_807F6960[i].unk0 = arg0;
        D_807F6960[i].unk4 = arg1;
        D_807F6960[i].unk8 = arg2;
        D_807F6960[i].unkC = D_807444FC ^ 1;
        return;
    }
    faultSetMessage(0xB, 0, 0, 0);
}


void mtxCopyQueueCancelDest(s32 arg0) {
    s32 i;
    for (i = 0; i < 0x28; i++) {
        if (D_807F6960[i].unk0 != 0 && D_807F6960[i].unk8 == arg0) {
            D_807F6960[i].unk0 = 0;
        }
    }
}


void mtxCopyQueueCancelGroup(s32 arg0) {
    s32 i;
    for (i = 0; i < 0x28; i++) {
        if (D_807F6960[i].unk0 == arg0) {
            D_807F6960[i].unk0 = 0;
        }
    }
}



void mtxCopyQueueFlush(s32 arg0) {
    s32 i;
    for (i = 0; i < 0x28; i++) {
        if (D_807F6960[i].unk0 == arg0 && D_807F6960[i].unkC == D_807444FC) {
            memcpy((void *)D_807F6960[i].unk8, (void *)D_807F6960[i].unk4, 0x40);
            D_807F6960[i].unk0 = 0;
            D_807F6BEC = 1;
        }
    }
}

void modelAnimEntrySetUnk13(s16 arg0, s16 arg1, u8 arg2, f32 arg3) {
    ModelAnimGroup *group;
    ModelAnimEntry *entry;
    u32 value;
    s32 level;

    group = (ModelAnimGroup *)D_807F6000[hashTableLookup(arg0)].unk78;
    if (group != NULL) {
        entry = &group->entries[arg1];
        value = (u32)(8.0f * arg3);
        level = value & 0xFF;
        if ((u8)value >= 0x10) {
            level = 0xF;
        }
        entry->unk13 = (level << 4) + arg2;
    }
}

void modelAnimEntryStart(s16 arg0, s16 arg1, s16 arg2) {
    ModelAnimGroup *group;
    ModelAnimEntry *entry;

    group = (ModelAnimGroup *)D_807F6000[hashTableLookup(arg0)].unk78;
    if (group != NULL) {
        entry = &group->entries[arg1];
        entry->unkA = arg2;
        entry->unkE = 1;
        entry->unk8 = 0;
    }
}

void modelAnimEntryStop(s16 arg0, s16 arg1) {
    ModelAnimGroup *group;
    ModelAnimEntry *entry;

    group = (ModelAnimGroup *)D_807F6000[hashTableLookup(arg0)].unk78;
    if (group != NULL) {
        entry = &group->entries[arg1];
        entry->unkE = 0;
        func_8064FA7C(group, entry);
    }
}

void modelAnimEntryClearTime(s16 arg0, s16 arg1) {
    ModelAnimGroup *group;
    ModelAnimEntry *entry;

    group = (ModelAnimGroup *)D_807F6000[hashTableLookup(arg0)].unk78;
    if (group != NULL) {
        entry = &group->entries[arg1];
        entry->unk11 = 0;
        entry->unk4 = 0.0f;
    }
}

void modelAnimEntrySetUnkC(s16 arg0, s16 arg1, s16 arg2) {
    ModelAnimGroup *group;
    ModelAnimEntry *entry;

    group = (ModelAnimGroup *)D_807F6000[hashTableLookup(arg0)].unk78;
    if (group != NULL) {
        entry = &group->entries[arg1];
        entry->unkC = arg2;
    }
}

s16 modelAnimEntryGetUnkC(s16 arg0, s16 arg1) {
    ModelAnimGroup *group;

    group = (ModelAnimGroup *)D_807F6000[hashTableLookup(arg0)].unk78;
    if (group != NULL) {
        return group->entries[arg1].unkC;
    }
    return 0;
}

void modelAnimEntrySetTime(s16 arg0, s16 arg1, s16 arg2, f32 arg3) {
    ModelAnimGroup *group;
    ModelAnimEntry *entry;

    group = (ModelAnimGroup *)D_807F6000[hashTableLookup(arg0)].unk78;
    if (group != NULL) {
        entry = &group->entries[arg1];
        entry->unk4 = arg3;
        entry->unk11 = arg2;
    }
}

void modelAnimEntrySetUnkF(s16 arg0, s16 arg1, s16 arg2) {
    ModelAnimGroup *group;
    ModelAnimEntry *entry;

    group = (ModelAnimGroup *)D_807F6000[hashTableLookup(arg0)].unk78;
    if (group != NULL) {
        entry = &group->entries[arg1];
        entry->unkF = arg2;
    }
}

void modelAnimEntrySetUnk10(s16 arg0, s16 arg1, s16 arg2) {
    ModelAnimGroup *group;
    ModelAnimEntry *entry;

    group = (ModelAnimGroup *)D_807F6000[hashTableLookup(arg0)].unk78;
    if (group != NULL) {
        entry = &group->entries[arg1];
        entry->unk10 = arg2;
    }
}

void modelAnimEntryResetFrame(s16 arg0, s16 arg1, s16 arg2) {
    ModelAnimGroup *group;
    ModelAnimEntry *entry;

    group = (ModelAnimGroup *)D_807F6000[hashTableLookup(arg0)].unk78;
    if (group != NULL) {
        entry = &group->entries[arg1];
        entry->unk8 = 0;
        entry->unkA = arg2;
    }
}

void modelAnimEntrySetUnk12(s16 arg0, s16 arg1, s16 arg2) {
    ModelAnimGroup *group;
    ModelAnimEntry *entry;

    group = (ModelAnimGroup *)D_807F6000[hashTableLookup(arg0)].unk78;
    if (group != NULL) {
        entry = &group->entries[arg1];
        entry->unk12 = arg2;
    }
}

u8 modelAnimEntryIsActive(s16 arg0, s16 arg1) {
    ModelAnimGroup *group;
    s32 flag;
    u8 result;

    result = 0;
    group = (ModelAnimGroup *)D_807F6000[hashTableLookup(arg0)].unk78;
    if (group != NULL) {
        flag = 0;
        if (group->entries[arg1].unkE == 1) {
            flag = 1;
        } else {
            flag = 0;
        }
        return flag;
    } else {
        return result;
    }
}

void modelAnimEntryGetState(s16 arg0, s16 arg1, s16 *arg2, f32 *arg3, u8 *arg4) {
    ModelAnimGroup *group;
    ModelAnimEntry *entry;

    group = (ModelAnimGroup *)D_807F6000[hashTableLookup(arg0)].unk78;
    if (group != NULL) {
        entry = &group->entries[arg1];
        *arg3 = entry->unk4;
        *arg2 = entry->unk11;
        *arg4 = entry->unkF;
    }
}
