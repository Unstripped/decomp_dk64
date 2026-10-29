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

void *func_80610FE8(s32);
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
        m = func_80610FE8(0xD0);
        *arg0 = m;
        n = *(u32 *)(arg1 + *(u32 *)(arg1 + 0x68));
        m->unk0 = func_80610FE8(n);
        m->unk4 = func_80610FE8(n);
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
void func_80650684();

void modelSlotFree(u8 **arg0) {
    if (arg0 != NULL) {
        heapFreeDeferred(arg0[0]);
        heapFreeDeferred(arg0[1]);
        func_80650684(arg0);
        heapFree(arg0);
    }
}

extern u32 D_807F6BE0;
extern u32 D_807F6BE4;
extern u32 D_807F6BE8;
extern u8 D_807F6BEC;
extern u8 D_807444FC;
s32 hashTableLookup();
void func_806506E8();
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
        func_806506E8(base);
    }
    return D_807F6BEC;
}

void func_806500E0(void *);
void func_8064F97C(ModelAnimEntryRaw *);

void modelAnimEntryStep(void *arg0) {
    func_806500E0(arg0);
    func_8064F97C(arg0);
}

void func_8064FB64();
void func_8065054C();
void func_806505F0();

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
        func_8064FB64(arg0->unk11, arg0->unk4, p, p + 8, arg0->unk13);
        c = *(u32 *)p + b;
        if (arg0->unkE == 0) {
            d = *(u32 *)p + a;
            func_8065054C(D_807F6BE8, d, c);
        } else {
            func_806505F0(c);
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
        func_8065054C(arg0, *(u32 *)p + a, c);
        i++;
        p += stride;
    }
    if (D_807444FC && D_807444FC) {}  // FAKE: deadsweep dead statement (extends D_807444FC live range: v1 not v0, address temps a2/a3)
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/54150/func_8064FB64.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/54150/func_806500E0.s")


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

void func_8065054C(s32 arg0, s32 arg1, s32 arg2) {
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

#ifdef NON_MATCHING
void func_806505F0(s32 arg0) {
    s32 i;
    for (i = 0; i < 0x28; i++) {
        if (D_807F6960[i].unk0 != 0 && D_807F6960[i].unk8 == arg0) {
            D_807F6960[i].unk0 = 0;
        }
    }
}
#else

#pragma GLOBAL_ASM("asm/global/nonmatchings/54150/func_806505F0.s")
#endif

#ifdef NON_MATCHING
void func_80650684(s32 arg0) {
    s32 i;
    for (i = 0; i < 0x28; i++) {
        if (D_807F6960[i].unk0 == arg0) {
            D_807F6960[i].unk0 = 0;
        }
    }
}
#else

#pragma GLOBAL_ASM("asm/global/nonmatchings/54150/func_80650684.s")
#endif

#ifdef NON_MATCHING
void func_806506E8(s32 arg0) {
    s32 i;
    for (i = 0; i < 0x28; i++) {
        if (D_807F6960[i].unk0 == arg0 && D_807F6960[i].unkC == D_807444FC) {
            memcpy((void *)D_807F6960[i].unk8, (void *)D_807F6960[i].unk4, 0x40);
            D_807F6960[i].unk0 = 0;
            D_807F6BEC = 1;
        }
    }
}
#else

#pragma GLOBAL_ASM("asm/global/nonmatchings/54150/func_806506E8.s")
#endif

void func_80650794(s16 arg0, s16 arg1, u8 arg2, f32 arg3) {
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

s16 func_80650A70(s16 arg0, s16 arg1) {
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
