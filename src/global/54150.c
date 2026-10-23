#include "common.h"
#include "actor.h"

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

#ifdef NON_MATCHING
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
#else

#pragma GLOBAL_ASM("asm/global/nonmatchings/54150/func_8064F450.s")
#endif

typedef struct M54ASlot {
    u8 pad0[0x24];
    u8 *unk24;
    u8 pad28[0x50];
    u8 *unk78;
    u8 pad7C[0x14];
} M54ASlot; /* 0x90 */

typedef struct M54AOwner {
    u8 *unk0;
    u32 unk4;
    u8 pad8[6];
    u8 unkE;
    u8 padF[2];
    u8 unk11;
    u8 pad12;
    u8 unk13;
} M54AOwner;

extern M54ASlot *D_807F6000;

u32 func_8064F6C0(arg0)
s16 arg0;
{
    u8 *p = D_807F6000[arg0].unk24;

    return *(u32 *)(p + *(s32 *)(p + 0x68));
}

typedef struct M54ABuf {
    u32 unk0;
    u32 unk4;
} M54ABuf;

void func_806357F8();
void func_806358E8(s16, s32, s32, s32, f32, f32, f32, f32, f32, s32, s32, s32, s32, s32);

void func_8064F6F8(arg0, arg1)
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
    func_806357F8(arg1, &x, &y, &z, &a, &b, &c, &d, &e, 0);
    func_806358E8(arg1, x, y, z, a, b, c, d, e, 0, 0, 0, 0, 1);
}

void heapFreeDeferred(void *);
void heapFree(void *);
void func_80650684();

void func_8064F804(u8 **arg0) {
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
void func_8064F954(void *);

u8 func_8064F84C(arg0)
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
                func_8064F954(p + 8);
                D_807F6BEC = 1;
            }
            p += 0x14;
        }
        func_806506E8(base);
    }
    return D_807F6BEC;
}

void func_806500E0(void *);
void func_8064F97C(M54AOwner *);

void func_8064F954(void *arg0) {
    func_806500E0(arg0);
    func_8064F97C(arg0);
}

void func_8064FB64();
void func_8065054C();
void func_806505F0();

#ifdef NON_MATCHING
void func_8064F97C(M54AOwner *arg0) {
    u8 *node;
    s16 stride;
    s32 i;
    u8 *p;
    u32 a;
    u32 b;

    node = arg0->unk0;
    stride = *(u8 *)node * 0x24 + 8;
    a = D_807F6BE0;
    b = D_807F6BE4;
    i = 0;
    p = node + 0x3C;
    while (i < *(u8 *)(node + 0x39)) {
        u32 v;

        func_8064FB64(arg0->unk11, arg0->unk4, p, p + 8, arg0->unk13);
        v = *(u32 *)p;
        if (arg0->unkE == 0) {
            func_8065054C(D_807F6BE8, v + a, v + b);
        } else {
            func_806505F0(v + b);
        }
        i++;
        p += stride;
    }
}
#else

#pragma GLOBAL_ASM("asm/global/nonmatchings/54150/func_8064F97C.s")
#endif

#ifdef NON_MATCHING
void func_8064FA7C(u32 *arg0, u32 *arg1) {
    u8 *node;
    s16 stride;
    s32 i;
    u8 *p;
    u32 a;
    u32 b;

    node = (u8 *)*arg1;
    stride = *(u8 *)node * 0x24 + 8;
    a = arg0[D_807444FC ^ 1];
    *(volatile u32 *)&D_807F6BE0 = a;
    b = arg0[D_807444FC];
    *(volatile u32 *)&D_807F6BE4 = b;
    p = node + 0x3C;
    i = 0;
    while (i < *(u8 *)(node + 0x39)) {
        func_8065054C(arg0, *(u32 *)p + a, *(u32 *)p + b);
        i++;
        p += stride;
    }
}
#else

#pragma GLOBAL_ASM("asm/global/nonmatchings/54150/func_8064FA7C.s")
#endif

#pragma GLOBAL_ASM("asm/global/nonmatchings/54150/func_8064FB64.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/54150/func_806500E0.s")


typedef struct M54B_ClearGroup {
    s32 unk0;
    u8 pad04[0xC];
    s32 unk10;
    u8 pad14[0xC];
    s32 unk20;
    u8 pad24[0xC];
    s32 unk30;
    u8 pad34[0xC];
} M54B_ClearGroup;

typedef struct M54B_Slot {
    s32 unk0;
    s32 unk4;
    s32 unk8;
    u8 unkC;
    u8 padD[3];
} M54B_Slot;

typedef struct M54B_HashEntry {
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
} M54B_HashEntry;

typedef struct M54B_HashGroup {
    u8 *unk0;
    u8 *unk4;
    M54B_HashEntry entries[1];
} M54B_HashGroup;

extern M54B_Slot D_807F6960[];
void func_80732354(s32, s32, s32, s32);
void func_8064FA7C();

#ifdef NON_MATCHING
void func_8065051C(void) {
    M54B_ClearGroup *group = (M54B_ClearGroup *)D_807F6960;

    for (;;) {
        group->unk10 = 0;
        group->unk20 = 0;
        group->unk30 = 0;
        group->unk0 = 0;
        group++;
        if (group == (M54B_ClearGroup *)&D_807F6BE0) {
            break;
        }
    }
}
#else

#pragma GLOBAL_ASM("asm/global/nonmatchings/54150/func_8065051C.s")
#endif

#ifdef NON_MATCHING
void func_8065054C(s32 arg0, s32 arg1, s32 arg2) {
    s32 found;
    s32 i;
    M54B_Slot *slot;

    found = 0;
    i = 0;
    slot = &D_807F6960[0];
    do {
        if (slot->unk0 == 0) {
            found = 1;
        } else {
            i++;
            slot++;
        }
    } while (found == 0 && i < 0x28);

    if (found != 0) {
        slot = &D_807F6960[i];
        slot->unk0 = arg0;
        slot->unk4 = arg1;
        slot->unk8 = arg2;
        slot->unkC = D_807444FC ^ 1;
        return;
    }
    func_80732354(0xB, 0, 0, 0);
}
#else

#pragma GLOBAL_ASM("asm/global/nonmatchings/54150/func_8065054C.s")
#endif

#ifdef NON_MATCHING
void func_806505F0(s32 arg0) {
    M54B_Slot *slot = D_807F6960;

    for (;;) {
        if (slot->unk0 != 0 && slot->unk8 == arg0) {
            slot->unk0 = 0;
        }
        if (slot[1].unk0 != 0 && slot[1].unk8 == arg0) {
            slot[1].unk0 = 0;
        }
        if (slot[2].unk0 != 0 && slot[2].unk8 == arg0) {
            slot[2].unk0 = 0;
        }
        if (slot[3].unk0 != 0 && slot[3].unk8 == arg0) {
            slot[3].unk0 = 0;
        }
        slot += 4;
        if (slot == (M54B_Slot *)&D_807F6BE0) {
            break;
        }
    }
}
#else

#pragma GLOBAL_ASM("asm/global/nonmatchings/54150/func_806505F0.s")
#endif

#ifdef NON_MATCHING
void func_80650684(s32 arg0) {
    M54B_Slot *slot = D_807F6960;

    for (;;) {
        if (slot->unk0 == arg0) {
            slot->unk0 = 0;
        }
        if (slot[1].unk0 == arg0) {
            slot[1].unk0 = 0;
        }
        if (slot[2].unk0 == arg0) {
            slot[2].unk0 = 0;
        }
        if (slot[3].unk0 == arg0) {
            slot[3].unk0 = 0;
        }
        slot += 4;
        if (slot == (M54B_Slot *)&D_807F6BE0) {
            break;
        }
    }
}
#else

#pragma GLOBAL_ASM("asm/global/nonmatchings/54150/func_80650684.s")
#endif

#ifdef NON_MATCHING
void func_806506E8(s32 arg0) {
    M54B_Slot *slot = D_807F6960;

    do {
        if (slot->unk0 == arg0 && slot->unkC == D_807444FC) {
            memcpy((void *)slot->unk8, (void *)slot->unk4, 0x40);
            slot->unk0 = 0;
            D_807F6BEC = 1;
        }
        slot++;
    } while (slot != (M54B_Slot *)&D_807F6BE0);
}
#else

#pragma GLOBAL_ASM("asm/global/nonmatchings/54150/func_806506E8.s")
#endif

#ifdef NON_MATCHING
void func_80650794(s16 arg0, s16 arg1, u8 arg2, f32 arg3) {
    M54B_HashGroup *group;
    M54B_HashEntry *entry;
    u32 value;
    u32 level;

    group = (M54B_HashGroup *)D_807F6000[hashTableLookup(arg0)].unk78;
    if (group != NULL) {
        entry = &group->entries[arg1];
        value = (u32)(8.0f * arg3);
        level = (value & 0xFF) < 0x10 ? (value & 0xFF) : 0xF;
        entry->unk13 = (level << 4) + arg2;
    }
}
#else

#pragma GLOBAL_ASM("asm/global/nonmatchings/54150/func_80650794.s")
#endif

void func_806508B4(s16 arg0, s16 arg1, s16 arg2) {
    M54B_HashGroup *group;
    M54B_HashEntry *entry;

    group = (M54B_HashGroup *)D_807F6000[hashTableLookup(arg0)].unk78;
    if (group != NULL) {
        entry = &group->entries[arg1];
        entry->unkA = arg2;
        entry->unkE = 1;
        entry->unk8 = 0;
    }
}

void func_8065092C(s16 arg0, s16 arg1) {
    M54B_HashGroup *group;
    M54B_HashEntry *entry;

    group = (M54B_HashGroup *)D_807F6000[hashTableLookup(arg0)].unk78;
    if (group != NULL) {
        entry = &group->entries[arg1];
        entry->unkE = 0;
        func_8064FA7C(group, entry);
    }
}

void func_80650998(s16 arg0, s16 arg1) {
    M54B_HashGroup *group;
    M54B_HashEntry *entry;

    group = (M54B_HashGroup *)D_807F6000[hashTableLookup(arg0)].unk78;
    if (group != NULL) {
        entry = &group->entries[arg1];
        entry->unk11 = 0;
        entry->unk4 = 0.0f;
    }
}

void func_80650A04(s16 arg0, s16 arg1, s16 arg2) {
    M54B_HashGroup *group;
    M54B_HashEntry *entry;

    group = (M54B_HashGroup *)D_807F6000[hashTableLookup(arg0)].unk78;
    if (group != NULL) {
        entry = &group->entries[arg1];
        entry->unkC = arg2;
    }
}

#ifdef NON_MATCHING
s16 func_80650A70(s16 arg0, s16 arg1) {
    M54B_HashGroup *group;
    s16 value;

    group = (M54B_HashGroup *)D_807F6000[hashTableLookup(arg0)].unk78;
    value = 0;
    if (group != NULL) {
        value = group->entries[arg1].unkC;
    }
    return value;
}
#else

#pragma GLOBAL_ASM("asm/global/nonmatchings/54150/func_80650A70.s")
#endif

void func_80650AD8(s16 arg0, s16 arg1, s16 arg2, f32 arg3) {
    M54B_HashGroup *group;
    M54B_HashEntry *entry;

    group = (M54B_HashGroup *)D_807F6000[hashTableLookup(arg0)].unk78;
    if (group != NULL) {
        entry = &group->entries[arg1];
        entry->unk4 = arg3;
        entry->unk11 = arg2;
    }
}

void func_80650B50(s16 arg0, s16 arg1, s16 arg2) {
    M54B_HashGroup *group;
    M54B_HashEntry *entry;

    group = (M54B_HashGroup *)D_807F6000[hashTableLookup(arg0)].unk78;
    if (group != NULL) {
        entry = &group->entries[arg1];
        entry->unkF = arg2;
    }
}

void func_80650BBC(s16 arg0, s16 arg1, s16 arg2) {
    M54B_HashGroup *group;
    M54B_HashEntry *entry;

    group = (M54B_HashGroup *)D_807F6000[hashTableLookup(arg0)].unk78;
    if (group != NULL) {
        entry = &group->entries[arg1];
        entry->unk10 = arg2;
    }
}

void func_80650C28(s16 arg0, s16 arg1, s16 arg2) {
    M54B_HashGroup *group;
    M54B_HashEntry *entry;

    group = (M54B_HashGroup *)D_807F6000[hashTableLookup(arg0)].unk78;
    if (group != NULL) {
        entry = &group->entries[arg1];
        entry->unk8 = 0;
        entry->unkA = arg2;
    }
}

void func_80650C98(s16 arg0, s16 arg1, s16 arg2) {
    M54B_HashGroup *group;
    M54B_HashEntry *entry;

    group = (M54B_HashGroup *)D_807F6000[hashTableLookup(arg0)].unk78;
    if (group != NULL) {
        entry = &group->entries[arg1];
        entry->unk12 = arg2;
    }
}

u8 func_80650D04(s16 arg0, s16 arg1) {
    M54B_HashGroup *group;
    s32 flag;
    u8 result;

    result = 0;
    group = (M54B_HashGroup *)D_807F6000[hashTableLookup(arg0)].unk78;
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

void func_80650D8C(s16 arg0, s16 arg1, s16 *arg2, f32 *arg3, u8 *arg4) {
    M54B_HashGroup *group;
    M54B_HashEntry *entry;

    group = (M54B_HashGroup *)D_807F6000[hashTableLookup(arg0)].unk78;
    if (group != NULL) {
        entry = &group->entries[arg1];
        *arg3 = entry->unk4;
        *arg2 = entry->unk11;
        *arg4 = entry->unkF;
    }
}
