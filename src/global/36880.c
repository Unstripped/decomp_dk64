#include "common.h"
#include "actor.h"

typedef struct ModelSlot {
    /* 0x00 */ f32 unk0;
    /* 0x04 */ f32 unk4;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ u8 padC[0x14];
    /* 0x20 */ void *unk20;
    /* 0x24 */ u8 *unk24;
    /* 0x28 */ u8 pad28[0x4C];
    /* 0x74 */ void *unk74;
    /* 0x78 */ u8 *unk78;
    /* 0x7C */ void *unk7C;
    /* 0x80 */ u8 pad80[4];
    /* 0x84 */ s16 unk84;
    /* 0x86 */ s16 unk86;
    /* 0x88 */ u8 pad88[4];
    /* 0x8C */ u8 unk8C;
    /* 0x8D */ u8 pad8D[3];
} ModelSlot; /* 0x90, indexed by hashTableLookup() */

extern ModelSlot *D_807F6000;

extern void *D_807FC924;
extern u8 D_807FC929;
extern s32 D_8076A064;
extern s32 D_8076A0A8;
extern u8 D_807444FC;

s32 hashTableLookup(s32);
void heapFree(void *);
void *func_80610FE8(s32);
void assetFreeBuffer(void *, s32, s32);

extern u8 D_807F6148;

void func_80631B80(void) {
    D_807F6148 = 0;
}

extern s16 D_807F6140[];

void func_80631B8C(s16 arg0) {
    if (D_807F6148 != 4) {
        D_807F6140[D_807F6148++] = arg0;
    }
}

s32 func_80631BCC(s16 arg0) {
    s32 i;

    for (i = 0; i < D_807F6148; i++) {
        if (D_807F6140[i] == arg0) {
            return 1;
        }
    }
    return 0;
}

extern s16 D_807F6150[];

s16 func_80631C20(u8 arg0) {
    return D_807F6150[arg0];
}

u8 func_805FF030(u8, u8);
void *func_8066B0F8(s32, s32, s32, s32);
void func_80631F58(u8 *, u8 **, u8 **);
s32 func_80631EB8(u16);
void assetSetImmediateFree(void);

extern u8 D_80747D78;

void func_80631C3C(void) {
    s32 x;
    s32 i;
    void *asset;
    u8 *entries;
    u8 *sp54;
    u8 slot;
    s32 count;
    u8 *entry;
    s32 j;

    if (D_80747D78 == 0) {
        D_80747D78 = 1;
        for (i = 0; i < 8; i++) {
            D_807F6150[i] = 0;
        }
        for (i = 0; i != 0xDD; i++) {
            asset = func_8066B0F8(9, i, 1, 1);
            if (asset != NULL) {
                slot = func_805FF030(i, 1);
                func_80631F58(asset, &entries, &sp54);
                count = *(s32 *)entries;
                entry = entries + 4;
                for (j = 0; j < count; j++) {
                    if (func_80631EB8(*(u16 *)(entry + 0x28))) {
                        D_807F6150[slot]++;
                    }
                    entry += 0x30;
                }
                assetSetImmediateFree();
                assetFreeBuffer(asset, 0x10C, 7);
            }
        }
    }
}

u16 func_80631D8C(u8 arg0) {
    u16 total;
    u8 slot;
    s32 i;
    void *asset;
    s32 x1;
    u8 *entries;
    u8 *sp58;
    s32 j;
    s32 count;
    u8 *entry;

    slot = func_805FF030(arg0, 1);
    total = 0;
    for (i = 0; i < arg0; i++) {
        if (slot == func_805FF030(i, 1)) {
            asset = func_8066B0F8(9, i, 1, 1);
            if (asset != NULL) {
                func_80631F58(asset, &entries, &sp58);
                count = *(s32 *)entries;
                entry = entries + 4;
                for (j = 0; j < count; j++) {
                    if (func_80631EB8(*(u16 *)(entry + 0x28))) {
                        total++;
                    }
                    entry += 0x30;
                }
                assetSetImmediateFree();
                assetFreeBuffer(asset, 0x13A, 7);
            }
        }
    }
    return total;
}

s32 func_80631EB8(u16 arg0) {
    switch (arg0) {
        case 0xA:
        case 0xD:
        case 0x16:
        case 0x1C:
        case 0x1D:
        case 0x1E:
        case 0x1F:
        case 0x23:
        case 0x24:
        case 0x27:
        case 0x2B:
        case 0x205:
        case 0x206:
        case 0x207:
        case 0x208:
            return 1;
        default:
            return 0;
    }
}

void func_80631F58(u8 *arg0, u8 **arg1, u8 **arg2) {
    s32 n;
    u8 *r;

    if (arg0 == NULL) {
        *arg1 = NULL;
        *arg2 = NULL;
        return;
    }
    *arg1 = arg0;
    n = *(s32 *)arg0;
    arg0 += n * 0x30;
    arg0 += 4;
    r = arg0;
    r += *(s32 *)arg0 * 0x24;
    r += 4;
    *arg2 = r;
}

extern s16 D_807F614A;
void heapClearBlock(void *);

s16 func_80631FAC(s32 arg0, u8 arg1) {
    switch (arg0) {
        case 48:
            D_807F614A = 0x212;
            break;
        case 26:
            D_807F614A = 0x1F4;
            break;
        case 38:
            D_807F614A = 0x1F4;
            break;
        case 30:
            D_807F614A = 0x1E5;
            break;
        case 7:
            D_807F614A = 0x1D1;
            break;
        default:
            D_807F614A = 0x1C2;
            break;
    }
    if (arg1 != 0) {
        D_807F6000 = func_80610FE8(D_807F614A * 0x90);
        heapClearBlock(D_807F6000);
    }
    return D_807F614A;
}

typedef struct {
    /* 0x00 */ f32 unk0;
    /* 0x04 */ f32 unk4;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ f32 unk10;
    /* 0x14 */ f32 unk14;
    /* 0x18 */ f32 unk18;
    /* 0x1C */ f32 unk1C;
    /* 0x20 */ f32 unk20;
    /* 0x24 */ f32 unk24;
    /* 0x28 */ s16 unk28;
    /* 0x2A */ s16 unk2A;
    /* 0x2C */ u8 pad2C[2];
    /* 0x2E */ u8 unk2E;
    /* 0x2F */ u8 unk2F;
} R36880aEntry; /* 0x30 */

typedef struct {
    /* 0x00 */ f32 unk0;
    /* 0x04 */ f32 unk4;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ f32 unk10;
    /* 0x14 */ f32 unk14;
    /* 0x18 */ f32 unk18;
    /* 0x1C */ f32 unk1C;
    /* 0x20 */ u8 pad20[0x64];
    /* 0x84 */ s16 unk84;
    /* 0x86 */ s16 pad86;
    /* 0x88 */ s16 unk88;
    /* 0x8A */ s16 unk8A;
    /* 0x8C */ u8 unk8C;
    /* 0x8D */ u8 pad8D[3];
} R36880aSlot; /* 0x90 */

extern s32 D_80747D70;
extern s16 D_807F6240[];
extern s32 D_807F6004;
void hashTableInit(void);
void func_8063D930(void);
void func_8065051C(void);
u8 func_8060E3B0(u16, u8);
s32 func_80631BCC(s16);
s32 func_807315D4(s16, s16);
s32 func_8063253C(s16, s32);
s16 func_80632860(s32, s32, f32, f32, f32, f32, f32, f32, f32, f32, u8, u8, s32 *);
void func_80632E74(s16, s16, u8 *);
void func_8062D3E4(s32);
void func_806306D0(s32);
void func_8062D1A8(void);
void func_8063DC58(void *);
void func_8063DFEC(s32, u8 *);
void func_80631B80(void);

void func_80632084(u8 *arg0, s32 arg1, u8 arg2, u16 arg3, u8 arg4) {
    s32 sp94;
    s32 sp90;
    u8 *sp8C;
    R36880aEntry *entry;
    s32 i;
    s32 n;
    u8 *rec;
    s32 outCount;
    u16 counter;
    s16 result;
    u8 found;
    u8 used;

    sp94 = 0;
    outCount = 0;
    i = 0;
    counter = 0;
    D_80747D70 = 0;
    if (arg0 == NULL) {
        sp90 = 0;
        entry = (R36880aEntry *)sp8C;
    } else {
        entry = (R36880aEntry *)(arg0 + 4);
        sp90 = *(s32 *)arg0;
    }
    D_807F6004 = 0;
    hashTableInit();
    func_8063D930();
    func_8065051C();
    if (arg0 != NULL) {
        if (sp90 > 0) {
            do {
                found = 0;
                used = 0;
                if (arg2 && func_80631EB8(entry->unk28)) {
                    found = func_8060E3B0(arg3 + counter, arg4);
                    used = 1;
                }
                if (found == 0 && func_80631BCC(entry->unk28) == 0 &&
                    func_807315D4(*(s16 *)((u8 *)&D_8076A0A8 + 2), entry->unk2A) == 0 &&
                    func_8063253C(entry->unk28, arg1) != 0) {
                    ((R36880aSlot *)D_807F6000)[outCount].unk0 = entry->unk0;
                    ((R36880aSlot *)D_807F6000)[outCount].unk4 = entry->unk4;
                    ((R36880aSlot *)D_807F6000)[outCount].unk8 = entry->unk8;
                    ((R36880aSlot *)D_807F6000)[outCount].unkC = entry->unkC;
                    ((R36880aSlot *)D_807F6000)[outCount].unk10 = entry->unk18;
                    ((R36880aSlot *)D_807F6000)[outCount].unk14 = entry->unk1C;
                    ((R36880aSlot *)D_807F6000)[outCount].unk18 = entry->unk20;
                    ((R36880aSlot *)D_807F6000)[outCount].unk1C = entry->unk24;
                    ((R36880aSlot *)D_807F6000)[outCount].unk8A = entry->unk2A;
                    result = func_80632860(outCount, entry->unk28, entry->unk0, entry->unk4, entry->unk8,
                                           entry->unk18, entry->unk1C, entry->unk20, entry->unkC, entry->unk24,
                                           entry->unk2F, entry->unk2E, &sp94);
                    func_80632E74(*(s16 *)((u8 *)&D_8076A0A8 + 2), ((R36880aSlot *)D_807F6000)[outCount].unk8A,
                                  (u8 *)(outCount * 0x90 + (s32)D_807F6000 + 0x8C));
                    D_807F6240[entry->unk2A] = result;
                    D_80747D70++;
                    outCount++;
                }
                if (used != 0) {
                    counter++;
                }
                i++;
                entry++;
            } while (i < sp90);
        }
        func_8062D3E4(sp94);
        func_806306D0(sp94);
        func_8062D1A8();
        func_8063DC58(func_8066B0F8(0xA, D_8076A0A8, 1, 0));
        n = *(s32 *)entry;
        rec = (u8 *)entry + 4;
        while (n--) {
            func_8063DFEC(*(s32 *)rec, rec + 4);
            rec += 0x24;
        }
        func_80631B80();
    }
}

typedef struct R36880aFlagObj {
    /* 0x00 */ u8 pad0[0x4A];
    /* 0x4A */ s16 unk4A;
    /* 0x4C */ u8 pad4C[2];
    /* 0x4E */ u8 unk4E;
} R36880aFlagObj;

typedef struct R36880aFlagNode {
    /* 0x00 */ R36880aFlagObj *unk0;
    /* 0x04 */ u8 pad4[0x10];
    /* 0x14 */ struct R36880aFlagNode *unk14;
    /* 0x18 */ u8 pad18[0xC];
    /* 0x24 */ u8 unk24;
} R36880aFlagNode;

s32 flagGet(s32, s32);

void func_806323C0(R36880aFlagNode *arg0) {
    R36880aFlagObj *obj;
    s16 flag;

    if (arg0 != NULL) {
        do {
            if (arg0->unk24 == 2) {
                obj = arg0->unk0;
                switch (obj->unk4A) {
                    case 0xA:
                    case 0x24:
                    case 0x208:
                        flag = 6;
                        break;
                    case 0x1F:
                    case 0x27:
                    case 0x206:
                        flag = 0x75;
                        break;
                    case 0x16:
                    case 0x1C:
                    case 0x207:
                        flag = 0x42;
                        break;
                    case 0x1E:
                    case 0x23:
                    case 0x205:
                        flag = 0x46;
                        break;
                    default:
                        flag = -1;
                        break;
                }
                if (flag != -1) {
                    if (flagGet(flag, 0) == 0) {
                        obj->unk4E |= 0x10;
                    } else {
                        obj->unk4E &= ~0x10;
                    }
                }
            }
            arg0 = arg0->unk14;
        } while (arg0 != NULL);
    }
}

s32 func_8063253C(s16 arg0, s32 arg1) {
    return 1;
}

s32 func_8063254C(s32 arg0, s32 *arg1, f32 *arg2, f32 *arg3, f32 *arg4, s16 *arg5, s16 *arg6) {
    s32 i;
    u8 found;

    found = 0;
    i = *arg1;
    do {
    } while (0);
    if (i < D_80747D70) {
        do {
            if (((R36880aSlot *)D_807F6000)[i].unk84 == arg0) {
                found = 1;
                *arg5 = ((R36880aSlot *)D_807F6000)[i].unk88;
                *arg6 = ((R36880aSlot *)D_807F6000)[i].unk8A;
                *arg2 = ((R36880aSlot *)D_807F6000)[i].unk0;
                *arg3 = ((R36880aSlot *)D_807F6000)[i].unk4;
                *arg4 = ((R36880aSlot *)D_807F6000)[i].unk8;
            }
            i++;
        } while (found == 0 && i < D_80747D70);
    }
    *arg1 = i;
    return found;
}

extern u8 D_807F6008;
void faultSetMessage(s32, s32, s32, s32);
f32 func_80636A44(s32);
s16 func_8063D9D0(s16, u8);

s16 func_80632630(s32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, u8 arg5) {
    s32 sp5C;
    s16 sp5A;
    f32 temp;

    sp5C = 0;
    if (D_80747D70 >= D_807F614A) {
        faultSetMessage(8, 0, 0, 0);
    }
    if (arg5 == 0 && D_807F6008 != 0) {
        return -1;
    }
    temp = func_80636A44(arg0);
    ((R36880aSlot *)D_807F6000)[D_80747D70].unk0 = arg1;
    ((R36880aSlot *)D_807F6000)[D_80747D70].unk4 = arg2;
    ((R36880aSlot *)D_807F6000)[D_80747D70].unk8 = arg3;
    ((R36880aSlot *)D_807F6000)[D_80747D70].unkC = temp;
    ((R36880aSlot *)D_807F6000)[D_80747D70].unk10 = 0.0f;
    ((R36880aSlot *)D_807F6000)[D_80747D70].unk14 = 0.0f;
    ((R36880aSlot *)D_807F6000)[D_80747D70].unk18 = 0.0f;
    ((R36880aSlot *)D_807F6000)[D_80747D70].unk1C = arg2 - arg4;
    ((R36880aSlot *)D_807F6000)[D_80747D70].unk8C = 0;
    sp5A = func_80632860(D_80747D70, arg0, arg1, arg2, arg3, 0.0f, 0.0f, 0.0f, temp, arg2 - arg4, 1, 0, &sp5C);
    func_8062D3E4(sp5C);
    func_806306D0(sp5C);
    ((R36880aSlot *)D_807F6000)[D_80747D70].unk8A = func_8063D9D0(sp5A, arg5);
    D_80747D70++;
    return sp5A;
}

typedef struct R36880bSub24 {
    /* 0x00 */ u32 unk0;
    /* 0x04 */ u8 pad4[0x18];
    /* 0x1C */ u8 unk1C;
    /* 0x1D */ u8 unk1D;
    /* 0x1E */ s16 unk1E;
    /* 0x20 */ u8 pad20[8];
    /* 0x28 */ s16 unk28;
    /* 0x2A */ s16 unk2A;
    /* 0x2C */ s16 unk2C;
    /* 0x2E */ s16 unk2E;
    /* 0x30 */ s16 unk30;
    /* 0x32 */ u8 unk32;
    /* 0x33 */ u8 unk33;
    /* 0x34 */ u8 unk34;
    /* 0x35 */ u8 unk35;
    /* 0x36 */ u8 unk36;
    /* 0x37 */ u8 unk37;
    /* 0x38 */ u8 unk38;
    /* 0x39 */ u8 unk39;
} R36880bSub24;

typedef struct R36880bSlot {
    /* 0x00 */ u8 pad0[0x20];
    /* 0x20 */ void *unk20;
    /* 0x24 */ R36880bSub24 *unk24;
    /* 0x28 */ u8 unk28[0x14];
    /* 0x3C */ u8 unk3C;
    /* 0x3D */ u8 unk3D;
    /* 0x3E */ u8 pad3E[0xA];
    /* 0x48 */ u8 unk48[0x24];
    /* 0x6C */ u8 unk6C;
    /* 0x6D */ u8 pad6D[0xB];
    /* 0x78 */ u8 unk78[4];
    /* 0x7C */ void *unk7C;
    /* 0x80 */ u8 pad80[4];
    /* 0x84 */ s16 unk84;
    /* 0x86 */ s16 unk86;
    /* 0x88 */ s16 unk88;
    /* 0x8A */ u8 pad8A[6];
} R36880bSlot;

typedef struct R36880bObj1 {
    /* 0x00 */ f32 unk0;
    /* 0x04 */ f32 unk4;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ f32 unk10;
    /* 0x14 */ f32 unk14;
    /* 0x18 */ f32 unk18;
    /* 0x1C */ f32 unk1C;
    /* 0x20 */ u8 pad20[0x96];
    /* 0xB6 */ s16 unkB6;
    /* 0xB8 */ u8 padB8[4];
    /* 0xBC */ void *unkBC;
    /* 0xC0 */ s16 unkC0;
    /* 0xC2 */ u8 unkC2;
    /* 0xC3 */ u8 unkC3;
    /* 0xC4 */ u8 unkC4;
    /* 0xC5 */ u8 unkC5;
} R36880bObj1;

typedef struct R36880bObj2 {
    /* 0x00 */ u8 pad0[0x4C];
    /* 0x4C */ s16 unk4C;
    /* 0x4E */ u8 unk4E;
    /* 0x4F */ u8 pad4F[5];
    /* 0x54 */ void *unk54;
    /* 0x58 */ s16 unk58;
    /* 0x5A */ u8 unk5A;
    /* 0x5B */ u8 unk5B;
    /* 0x5C */ u8 unk5C;
} R36880bObj2;

typedef struct R36880bNode38 {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ f32 unk4;
    /* 0x08 */ u8 unk8;
    /* 0x09 */ u8 unk9;
    /* 0x0A */ u8 unkA;
    /* 0x0B */ u8 unkB;
    /* 0x0C */ s16 unkC;
    /* 0x0E */ s16 unkE;
    /* 0x10 */ u8 pad10[0x14];
    /* 0x24 */ s16 unk24;
    /* 0x26 */ u8 pad26[2];
    /* 0x28 */ s16 unk28;
    /* 0x2A */ s16 unk2A;
    /* 0x2C */ s16 unk2C;
    /* 0x2E */ u8 unk2E;
    /* 0x2F */ u8 pad2F;
    /* 0x30 */ u8 unk30;
    /* 0x31 */ u8 pad31[3];
    /* 0x34 */ s32 unk34;
} R36880bNode38;

extern s32 D_807FBB64;
extern s32 D_807FBB68;

void func_806368F0();
void func_80636AE8(void *);
void func_80636D38(void *, s32, s32);
struct R36880bParent;
void func_8063524C(struct R36880bParent *, f32, f32, f32, f32, f32, f32, f32, f32);
void func_8063495C(u8 *, ModelSlot *);
void func_806349FC(u8 *, ModelSlot *, s32);
void func_8064F450(void *, void *);
void func_8066C2D0(s32, void *, f32, f32, f32, f32, f32, f32, f32);
struct R36880bModelData;
void func_80633A1C(s32, struct R36880bModelData *, f32, f32, f32, f32, f32, f32, f32);
struct R36880bBuf;
void func_806348B4(struct R36880bBuf *);
void dynamicBufferFree(void *);
void hashTableInsert(s32, s32);
s32 func_806303C4(s32, u8, void *, f32, f32, f32, s32, s32, s32, s32, s32);
void func_80632E10(s16, u8 *);
void func_80632F20(s32, u8 *);
s32 func_80632F74(f32, f32, f32);
void func_80632FCC(s16, u8);
struct R36880bPathTable;
void func_806330C4(s16, struct R36880bPathTable *, f32);
struct R36880bVertTable;
void func_806333F8(s32, struct R36880bVertTable *, f32, f32, f32, f32, f32, f32, f32, u8);
void func_8063373C(s32, struct R36880bVertTable *, f32, f32, f32, f32, f32, f32, f32, u8);
void func_806338F4(s32);

#define R36880B_SLOT ((R36880bSlot *)((u8 *)D_807F6000 + arg0 * 0x90))
#define R36880B_SLOTP ((R36880bSlot *)&D_807F6000[arg0])

s16 func_80632860(s32 arg0, s32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6, f32 arg7, f32 arg8, f32 arg9, u8 arg10, u8 arg11, s32 *arg12) {
    s32 padA[1];
    s32 sp68;
    s32 padB[1];
    R36880bObj1 *obj1;
    R36880bObj2 *obj2;
    R36880bSub24 *s0;
    s32 type;
    R36880bNode38 *node;
    void **sp4C;

    sp68 = *arg12;
    func_806368F0(R36880B_SLOTP);
    R36880B_SLOT->unk88 = D_807F6004;
    hashTableInsert(R36880B_SLOT->unk88, arg0);
    s0 = R36880B_SLOT->unk24;
    type = s0->unk1C;
    if (D_807FBB68 & 0x100) {
        s0->unk0 &= ~0x10;
    }
    func_80632F20(arg1, (u8 *)s0);
    if (D_807FBB64 & 0x100) {
        s0->unk1E = 0x7D0;
    } else if (D_807FBB64 & 0x400000) {
        s0->unk1E = 0x1F4;
    }
    func_8064F450(R36880B_SLOTP->unk78, s0);
    R36880B_SLOT->unk3C = 0;
    R36880B_SLOT->unk3D = 0;
    func_8066C2D0(arg0, s0, arg2, arg3, arg4, arg5, arg6, arg7, arg8);
    dynamicBufferFree(R36880B_SLOTP->unk28);
    func_806338F4(arg0);
    R36880B_SLOT->unk6C = 0;
    func_80633A1C(arg0, s0, arg2, arg3, arg4, arg5, arg6, arg7, arg8);
    func_806348B4(R36880B_SLOTP->unk48);
    func_806333F8(arg0, (struct R36880bVertTable *)s0, arg2, arg3, arg4, arg5, arg6, arg7, arg8, 0);
    func_8063373C(arg0, (struct R36880bVertTable *)s0, arg2, arg3, arg4, arg5, arg6, arg7, arg8, 0);
    func_806330C4(R36880B_SLOT->unk88, (struct R36880bPathTable *)s0, arg8);
    if (type == 1) {
        func_80636AE8(R36880B_SLOTP);
    }
    if (type != 1) {
        if (type == 2) {
            func_8063524C(R36880B_SLOTP, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9);
            func_806349FC(s0, R36880B_SLOTP, type);
            obj2 = R36880B_SLOT->unk20;
            sp4C = &obj2->unk54;
            obj2->unk4C = D_807F6004;
            obj2->unk4E = arg10;
            obj2->unk5B = arg11;
            obj2->unk58 = s0->unk1E;
            obj2->unk5A = s0->unk1D;
            obj2->unk5C = func_80632F74(arg2, arg3, arg4);
        }
    } else {
        obj1 = R36880B_SLOT->unk20;
        obj1->unk0 = arg2;
        obj1->unk4 = arg3;
        obj1->unk8 = arg4;
        obj1->unkC = arg8;
        obj1->unk10 = arg5;
        obj1->unk14 = arg6;
        obj1->unk18 = arg7;
        obj1->unk1C = arg9;
        obj1->unkB6 = D_807F6004;
        obj1->unkC0 = s0->unk1E;
        obj1->unkC2 = s0->unk1D;
        obj1->unkC3 = arg11;
        obj1->unkC4 = func_80632F74(arg2, arg3, arg4);
        obj1->unkC5 = 0;
        func_80632E10(arg1, &obj1->unkC5);
        func_806349FC(s0, R36880B_SLOTP, type);
        sp4C = &obj1->unkBC;
    }
    func_80636D38(R36880B_SLOTP, 0, 0);
    if (type == 2) {
        func_8063495C(s0, R36880B_SLOTP);
    }
    R36880B_SLOT->unk84 = arg1;
    R36880B_SLOT->unk86 = type;
    R36880B_SLOT->unk7C = NULL;
    if (s0->unk28 != -1) {
        node = func_80610FE8(0x38);
        *sp4C = node;
        node->unk34 = 0;
        node->unk4 = 1.0f;
        node->unkC = s0->unk2E;
        node->unkE = s0->unk30;
        node->unkA = s0->unk34;
        node->unkB = s0->unk35;
        node->unk8 = s0->unk32;
        node->unk9 = s0->unk33;
        node->unk24 = s0->unk2A;
        node->unk28 = s0->unk2C;
        node->unk2A = s0->unk36 * 10;
        node->unk2C = s0->unk37 * 10;
        node->unk2E = s0->unk38;
        node->unk30 = s0->unk39;
        node->unk0 = (s32)func_8066B0F8(0x19, s0->unk28, 1, 0);
        func_80632FCC(arg0, 0);
    }
    *arg12 = func_806303C4(sp68, type, R36880B_SLOT->unk20, arg2, arg3, arg4, s0->unk1E, D_807F6004, 0, 0, 0);
    D_807F6004 += 1;
    return D_807F6004 - 1;
}


typedef struct R36880bMapPair {
    /* 0x0 */ u16 map;
    /* 0x2 */ u16 id;
} R36880bMapPair;

extern R36880bMapPair D_80747D50[];

void func_80632E10(s16 arg0, u8 *arg1) {
    s32 i;
    s32 n;
    i = 0;
    n = 8;
    for (; i < n; i++) {
        if (D_8076A0A8 == D_80747D50[i].map && arg0 == D_80747D50[i].id) {
            *arg1 |= 1;
            return;
        }
    }
}

s32 func_80731654(s16, s16);

void func_80632E74(s16 arg0, s16 arg1, u8 *arg2) {
    switch (func_80731654(arg0, arg1)) {
        case 2:
            *arg2 |= 8;
            break;
        case 5:
            *arg2 |= 4;
            break;
        case 6:
            *arg2 |= 1;
            break;
        case 3:
            *arg2 |= 2;
            break;
        case 4:
            *arg2 |= 0x10;
            break;
    }
}

typedef struct R36880bMapTriple {
    /* 0x0 */ u16 map;
    /* 0x2 */ u16 id;
    /* 0x4 */ u16 val;
} R36880bMapTriple;

extern R36880bMapTriple D_80747D30[];

void func_80632F20(s32 arg0, u8 *arg1) {
    s32 i;
    s32 n;

    n = 5;
    for (i = 0; i < n; i++) {
        if (D_8076A0A8 == D_80747D30[i].map && arg0 == D_80747D30[i].id) {
            *(u16 *)(arg1 + 0x1E) = D_80747D30[i].val;
            return;
        }
    }
}

s32 collisionCheckGroundAtPoint(f32, f32, f32 *);
u8 func_80667174(void);

s32 func_80632F74(f32 x, f32 y, f32 z) {
    f32 sp1C;

    sp1C = y + 10.0f;
    if (collisionCheckGroundAtPoint(x, z, &sp1C) != 0) {
        return func_80667174();
    }
    return 0xF;
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/36880/func_80632FCC.s")

typedef struct R36880bPathSeg {
    /* 0x00 */ f32 unk0;
    /* 0x04 */ f32 unk4;
    /* 0x08 */ s16 unk8;
    /* 0x0A */ s16 unkA;
    /* 0x0C */ s16 unkC;
    /* 0x0E */ s16 unkE;
    /* 0x10 */ u8 unk10;
    /* 0x11 */ u8 unk11;
    /* 0x12 */ u8 unk12;
    /* 0x13 */ u8 pad13;
} R36880bPathSeg;

typedef struct R36880bPathEntry {
    /* 0x00 */ f32 unk0;
    /* 0x04 */ f32 unk4;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ f32 unk10;
    /* 0x14 */ u8 unk14;
    /* 0x15 */ u8 unk15;
    /* 0x16 */ u8 segCount;
    /* 0x17 */ u8 pad17;
    /* 0x18 */ R36880bPathSeg segs[8];
} R36880bPathEntry;

typedef struct R36880bPathTable {
    /* 0x00 */ u8 pad0[0x5C];
    /* 0x5C */ s32 unk5C;
} R36880bPathTable;

void func_806335B0(s32, u8, s32, f32 *, f32 *, f32 *);
void proxPathAdd(Actor *, u8, u8, u8, u8, f32, f32, f32, f32, f32, f32, u8, f32, f32, u8);
void proxPathSetSegment(Actor *, u8, u8, u8, u8, f32, f32, f32, u8, s16, s16, s16, s16);

void func_806330C4(s16 arg0, R36880bPathTable *arg1, f32 arg2) {
    s32 j;
    R36880bPathEntry *tbl;
    s32 i;
    s32 count;
    f32 spC4;
    f32 spC0;
    f32 spBC;
    f32 spB8;
    f32 spB4;
    f32 spB0;
    f32 len;

    count = *(s32 *)(arg1->unk5C + (s32)arg1);
    tbl = (R36880bPathEntry *)((u8 *)(arg1->unk5C + (s32)arg1) + 4);
    for (i = 1; i <= count; i++) {
        len = 0.0f;
        for (j = 0; j < tbl[i - 1].segCount; j++) {
            func_806335B0(arg0, 1, tbl[i - 1].segs[j].unk10, &spC0, &spB8, &spB0);
            func_806335B0(arg0, 1, tbl[i - 1].segs[j].unk11, &spC4, &spBC, &spB4);
            len += sqrtf((spB0 - spB4) * (spB0 - spB4) + ((spC0 - spC4) * (spC0 - spC4) + (spB8 - spBC) * (spB8 - spBC)));
        }
        proxPathAdd((Actor *)arg0, 1, i, 1, tbl[i - 1].segCount, 0.0f, len, tbl[i - 1].unk0 * arg2, tbl[i - 1].unkC * arg2, tbl[i - 1].unk10 * arg2, tbl[i - 1].unk10 * arg2, tbl[i - 1].unk14, tbl[i - 1].unk4, tbl[i - 1].unk8, tbl[i - 1].unk15);
        for (j = 0; j < tbl[i - 1].segCount; j++) {
            func_806335B0(arg0, 1, tbl[i - 1].segs[j].unk10, &spC0, &spB8, &spB0);
            func_806335B0(arg0, 1, tbl[i - 1].segs[j].unk11, &spC4, &spBC, &spB4);
            proxPathSetSegment((Actor *)arg0, i, j, tbl[i - 1].segs[j].unk10, tbl[i - 1].segs[j].unk11, sqrtf((spB0 - spB4) * (spB0 - spB4) + ((spC0 - spC4) * (spC0 - spC4) + (spB8 - spBC) * (spB8 - spBC))), tbl[i - 1].segs[j].unk0 * arg2, tbl[i - 1].segs[j].unk4 * arg2, tbl[i - 1].segs[j].unk12, tbl[i - 1].segs[j].unk8, tbl[i - 1].segs[j].unkC, tbl[i - 1].segs[j].unkA, tbl[i - 1].segs[j].unkE);
        }
    }
}


void func_8066C610(s16, s8, f32 (*)[4]);

typedef struct R36880bPosNode {
    /* 0x0 */ f32 x;
    /* 0x4 */ f32 y;
    /* 0x8 */ f32 z;
    /* 0xC */ struct R36880bPosNode *next;
} R36880bPosNode;

typedef struct R36880bVertTable {
    /* 0x00 */ u8 pad0[0x54];
    /* 0x54 */ s32 unk54;
    /* 0x58 */ s32 unk58;
} R36880bVertTable;

typedef struct R36880bVert {
    /* 0x0 */ s16 x;
    /* 0x2 */ s16 y;
    /* 0x4 */ s16 z;
    /* 0x6 */ s8 unk6;
} R36880bVert;

void func_806333F8(s32 arg0, R36880bVertTable *arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6, f32 arg7, f32 arg8, u8 arg9) {
    R36880bPosNode *node;
    R36880bPosNode **tail;
    f32 *pz;
    f32 sp6C[4][4];
    f32 *py;
    R36880bVert *vert;
    s32 *tbl;
    s32 count;

    node = NULL;
    tail = (R36880bPosNode **)((u8 *)&D_807F6000[arg0] + 0x70);
    if (arg9 == 0) {
        *tail = NULL;
    }
    tbl = (s32 *)(arg1->unk54 + (s32)arg1);
    count = *tbl;
    vert = (R36880bVert *)((u8 *)tbl + 4);
    if (count != 0) {
        do {
            switch (arg9) {
                case 0:
                    node = func_80610FE8(0x10);
                    *tail = node;
                    tail = &node->next;
                    node->next = NULL;
                    py = &node->y;
                    pz = &node->z;
                    break;
                case 1:
                    if (node == NULL) {
                        node = *tail;
                    } else {
                        node = node->next;
                    }
                    py = &node->y;
                    pz = &node->z;
                    break;
                default:
                    py = &node->y;
                    pz = &node->z;
                    break;
            }
            func_8066C610(arg0, vert->unk6, sp6C);
            guMtxXFMF(sp6C, vert->x, vert->y, vert->z, &node->x, py, pz);
            count--;
            vert++;
        } while (count != 0);
    }
}

typedef struct R36880bListNode {
    /* 0x0 */ u8 pad0[0xC];
    /* 0xC */ struct R36880bListNode *next;
} R36880bListNode;

void func_80633570(R36880bListNode *arg0) {
    R36880bListNode *next;

    while (arg0 != NULL) {
        next = arg0->next;
        heapFree(arg0);
        arg0 = next;
    }
}

void func_806335B0(s32 arg0, u8 arg1, s32 arg2, f32 *arg3, f32 *arg4, f32 *arg5) {
    R36880bPosNode *node;
    s32 n;

    if (arg1 == 1) {
        arg0 = hashTableLookup(arg0);
    }
    node = D_807F6000[arg0].unk74;
    for (n = arg2 - 1; node != NULL && n != 0; n--) {
        node = node->next;
    }
    if (node != NULL) {
        *arg3 = node->x;
        *arg4 = node->y;
        *arg5 = node->z;
    } else {
        *arg5 = 0.0f;
        *arg4 = 0.0f;
        *arg3 = 0.0f;
    }
}

Mtx *func_8063367C(s32 arg0, u8 arg1, s32 arg2) {
    s32 idx;
    f32 sp24[4][4];
    Mtx *sp20;
    u8 *base;
    s8 *p;

    idx = arg0;
    if (arg1 == 1) {
        idx = hashTableLookup(arg0);
    }
    base = D_807F6000[idx].unk24;
    p = (s8 *)(base + *(s32 *)(base + 0x58)) + 4;
    for (arg2--; p != NULL && arg2 != 0; arg2--) {
        p += 8;
    }
    func_8066C610(idx, p[6], sp24);
    sp20 = func_80610FE8(0x40);
    guMtxF2L(sp24, sp20);
    return sp20;
}

void func_8063373C(s32 arg0, R36880bVertTable *arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6, f32 arg7, f32 arg8, u8 arg9) {
    R36880bPosNode *node;
    R36880bPosNode **tail;
    f32 *pz;
    f32 spAC[4][4];
    f32 sp6C[4][4];
    f32 *py;
    R36880bVert *vert;
    s32 *tbl;
    s32 count;

    node = NULL;
    tail = (R36880bPosNode **)((u8 *)&D_807F6000[arg0] + 0x74);
    if (arg9 == 0) {
        *tail = NULL;
    }
    tbl = (s32 *)(arg1->unk58 + (s32)arg1);
    count = *tbl;
    vert = (R36880bVert *)((u8 *)tbl + 4);
    if (count != 0) {
        do {
            switch (arg9) {
                case 0:
                    node = func_80610FE8(0x10);
                    *tail = node;
                    tail = &node->next;
                    node->next = NULL;
                    py = &node->y;
                    pz = &node->z;
                    break;
                case 1:
                    if (node == NULL) {
                        node = *tail;
                    } else {
                        node = node->next;
                    }
                    py = &node->y;
                    pz = &node->z;
                    break;
                default:
                    py = &node->y;
                    pz = &node->z;
                    break;
            }
            func_8066C610(arg0, vert->unk6, spAC);
            guMtxXFMF(spAC, vert->x, vert->y, vert->z, &node->x, py, pz);
            count--;
            vert++;
        } while (count != 0);
    }
}

void func_806338B4(R36880bListNode *arg0) {
    R36880bListNode *next;

    while (arg0 != NULL) {
        next = arg0->next;
        heapFree(arg0);
        arg0 = next;
    }
}

typedef struct R36880bSlotTail {
    /* 0x00 */ u8 pad0[0x24];
    /* 0x24 */ u8 unk24;
    /* 0x25 */ u8 unk25[2];
} R36880bSlotTail;

void func_806338F4(s32 arg0) {
    R36880bSlotTail *p = (R36880bSlotTail *)((u8 *)&D_807F6000[arg0] + 0x48);
    u8 i;

    for (i = 0; i < 2; i++) {
        p->unk25[i] = 0xFF;
    }
    p->unk24 = 0;
}

void func_8063393C(s32 arg0, u8 arg1, u8 arg2, u8 arg3) {
    s32 i = 0;
    u8 found = 0;
    u8 key;
    u8 *p;

    if (arg1 == 1) {
        arg0 = hashTableLookup(arg0);
    }
    p = (u8 *)D_807F6000 + arg0 * 0x90 + 0x6D;
    key = arg3 ? arg2 : 0xFF;
    while (i < 2 && found == 0) {
        if (key == p[i]) {
            found = 1;
        } else {
            i++;
        }
    }
    p[i] = arg3 ? 0xFF : arg2;
}

typedef struct R36880bBuf {
    /* 0x00 */ u8 *unk0;
    /* 0x04 */ u8 *unk4;
    /* 0x08 */ s32 unk8;
    /* 0x0C */ f32 unkC[6];
    /* 0x24 */ u8 unk24;
} R36880bBuf;

typedef struct R36880bModelData {
    /* 0x00 */ u32 unk0;
    /* 0x04 */ u8 pad4[0x4C];
    /* 0x50 */ s32 unk50;
    /* 0x54 */ u8 pad54[0xC];
    /* 0x60 */ s32 unk60;
} R36880bModelData;

void func_80633D30(f32 *, f32 *);
void func_80633DC0(f32 (*)[4], void *, void *);
s32 func_80634768(void *, void *, f32 (*)[4]);
void func_8066C7F4(void *, void *, f32 (*)[4]);

void func_80633A1C(s32 arg0, R36880bModelData *arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6, f32 arg7, f32 arg8) {
    s32 count;
    u8 *anim;
    f32 sp138[4][4];
    f32 spF8[4][4];
    f32 spB8[4][4];
    f32 sp78[4][4];
    R36880bBuf *buf;
    u8 *entry;
    u8 *out;
    s32 i;
    void *sp64;
    u8 *sp60;
    s8 bone;
    s8 lastBone;
    s32 off;
    s32 pad2;
    s32 pad3;

    off = arg0 * 0x90;
    anim = ((ModelSlot *)((u8 *)D_807F6000 + off))->unk78;
    buf = (R36880bBuf *)((0, off) + (s32)D_807F6000);
    lastBone = -1;
    buf = (R36880bBuf *)((u8 *)buf + 0x48);
    if (anim != NULL) {
        sp64 = ((void **)anim)[D_807444FC];
    } else {
        sp64 = NULL;
    }
    sp60 = (u8 *)(arg1->unk60 + (s32)arg1);
    if (arg1->unk0 & 4) {
        buf->unk24 |= 2;
    } else {
        buf->unk24 &= ~2;
    }
    count = *(s32 *)(arg1->unk50 + (s32)arg1);
    if (count == 0) {
        buf->unk0 = NULL;
        buf->unk4 = NULL;
        buf->unk24 |= 1;
        buf->unk8 = D_8076A064;
        return;
    }
    if (!(buf->unk24 & 1)) {
        buf->unk0 = func_80610FE8(count * 0x28);
    }
    buf->unk24 |= 4;
    entry = (u8 *)(arg1->unk50 + (s32)arg1) + 0x10;
    out = buf->unk0;
    guScaleF(sp138, arg8, arg8, arg8);
    guRotateF(spF8, arg5, 1.0f, 0.0f, 0.0f);
    guMtxCatF(sp138, spF8, sp138);
    guRotateF(spF8, arg6, 0.0f, 1.0f, 0.0f);
    guMtxCatF(sp138, spF8, sp138);
    guRotateF(spF8, arg7, 0.0f, 0.0f, 1.0f);
    guMtxCatF(sp138, spF8, sp138);
    guTranslateF(spF8, arg2, arg3, arg4);
    guMtxCatF(sp138, spF8, sp138);
    func_80633DC0(sp138, (u8 *)(arg1->unk50 + (s32)arg1) + 4, buf);
    for (i = 0; i < count; i++) {
        bone = entry[0x13];
        if ((bone ^ 0) == -1) {
            if (func_80634768(entry, out, sp138) != 0) {
                out += 0x28;
            }
        } else {
            if (lastBone != bone) {
                func_8066C7F4(sp60 + (bone << 5), sp64, spB8);
                guMtxCatF(spB8, sp138, sp78);
                lastBone = entry[0x13];
            }
            if (func_80634768(entry, out, sp78) != 0) {
                func_80633D30((f32 *)out, buf->unkC);
                out += 0x28;
            }
        }
        entry += 0x18;
    }
    buf->unk4 = out;
    buf->unk24 |= 1;
    buf->unk8 = D_8076A064;
}


void func_80633D30(f32 *arg0, f32 *arg1) {
    s32 i;

    for (i = 0; i < 3; i++) {
        if (arg0[i] < arg1[0]) {
            arg1[0] = arg0[i];
        }
        if (arg0[i + 6] < arg1[2]) {
            arg1[2] = arg0[i + 6];
        }
        if (arg1[3] < arg0[i]) {
            arg1[3] = arg0[i];
        }
        if (arg1[5] < arg0[i + 6]) {
            arg1[5] = arg0[i + 6];
        }
    }
}


typedef struct {
    /* 0x00 */ u8 padL80633DC0[0xC];
    /* 0x0C */ f32 minX;
    /* 0x10 */ f32 minY;
    /* 0x14 */ f32 minZ;
    /* 0x18 */ f32 maxX;
    /* 0x1C */ f32 maxY;
    /* 0x20 */ f32 maxZ;
} L80633DC0Box;

#define L80633DC0_OUT ((L80633DC0Box *)arg2)
#define L80633DC0_ACC(x, y, z) \
    guMtxXFMF(arg0, (f32)((s16 *)arg1)[x], (f32)((s16 *)arg1)[y], (f32)((s16 *)arg1)[z], &sp3C, &sp38, &sp34); \
    if (L80633DC0_OUT->minX < sp3C) { L80633DC0_OUT->minX = L80633DC0_OUT->minX; } else { L80633DC0_OUT->minX = sp3C; } \
    if (L80633DC0_OUT->minY < sp38) { L80633DC0_OUT->minY = L80633DC0_OUT->minY; } else { L80633DC0_OUT->minY = sp38; } \
    if (L80633DC0_OUT->minZ < sp34) { L80633DC0_OUT->minZ = L80633DC0_OUT->minZ; } else { L80633DC0_OUT->minZ = sp34; } \
    if (sp3C < L80633DC0_OUT->maxX) { L80633DC0_OUT->maxX = L80633DC0_OUT->maxX; } else { L80633DC0_OUT->maxX = sp3C; } \
    if (sp38 < L80633DC0_OUT->maxY) { L80633DC0_OUT->maxY = L80633DC0_OUT->maxY; } else { L80633DC0_OUT->maxY = sp38; } \
    if (sp34 < L80633DC0_OUT->maxZ) { L80633DC0_OUT->maxZ = L80633DC0_OUT->maxZ; } else { L80633DC0_OUT->maxZ = sp34; }

void func_80633DC0(f32 (*arg0)[4], void *arg1, void *arg2) {
    f32 sp3C;
    f32 sp38;
    f32 sp34;

    guMtxXFMF(arg0, (f32)((s16 *)arg1)[0], (f32)((s16 *)arg1)[1], (f32)((s16 *)arg1)[2], &sp3C, &sp38, &sp34);
    L80633DC0_OUT->minX = sp3C;
    L80633DC0_OUT->minY = sp38;
    L80633DC0_OUT->minZ = sp34;
    L80633DC0_OUT->maxX = sp3C;
    L80633DC0_OUT->maxY = sp38;
    L80633DC0_OUT->maxZ = sp34;
    L80633DC0_ACC(3, 1, 2)
    L80633DC0_ACC(0, 1, 5)
    L80633DC0_ACC(3, 1, 5)
    L80633DC0_ACC(0, 4, 2)
    L80633DC0_ACC(3, 4, 2)
    L80633DC0_ACC(0, 4, 5)
    L80633DC0_ACC(3, 4, 5)
}

s32 func_80634768(void *arg0, void *arg1, f32 (*arg2)[4]) {
    s16 *in = arg0;
    f32 *out = arg1;

    guMtxXFMF(arg2, in[0], in[1], in[2], &out[0], &out[3], &out[6]);
    guMtxXFMF(arg2, in[3], in[4], in[5], &out[1], &out[4], &out[7]);
    guMtxXFMF(arg2, in[6], in[7], in[8], &out[2], &out[5], &out[8]);
    ((u8 *)arg1)[0x24] = ((u8 *)arg0)[0x12];
    ((u8 *)arg1)[0x25] = ((u8 *)arg0)[0x14];
    ((s8 *)arg1)[0x26] = ((s8 *)arg0)[0x13];
    ((u8 *)arg1)[0x27] = ((u8 *)arg0)[0x15];
    return 1;
}


void func_806348B4(R36880bBuf *arg0) {
    if (arg0->unk0 != NULL && (arg0->unk24 & 1)) {
        heapFree(arg0->unk0);
    }
    arg0->unk24 &= ~1;
}


void func_80634908(s32 arg0, void *arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6, f32 arg7, f32 arg8) {
    func_80633A1C(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8);
}

typedef struct R36880bNode {
    /* 0x00 */ u32 *unk0[12];
    /* 0x30 */ s32 unk30;
    /* 0x34 */ s16 unk34;
    /* 0x36 */ s16 unk36;
    /* 0x38 */ s16 unk38;
    /* 0x3A */ s16 unk3A;
    /* 0x3C */ s32 unk3C;
    /* 0x40 */ s32 unk40;
    /* 0x44 */ void *unk44;
    /* 0x48 */ u8 unk48;
    /* 0x49 */ u8 unk49;
    /* 0x4A */ u8 unk4A;
    /* 0x4B */ u8 pad4B;
    /* 0x4C */ s32 unk4C;
    /* 0x50 */ s32 unk50;
    /* 0x54 */ s32 unk54;
    /* 0x58 */ s32 unk58;
    /* 0x5C */ s32 unk5C;
    /* 0x60 */ s32 unk60[28];
    /* 0xD0 */ u8 unkD0;
    /* 0xD1 */ u8 padD1[3];
    /* 0xD4 */ struct R36880bNode *unkD4;
} R36880bNode;

typedef struct R36880bObj {
    /* 0x00 */ u8 pad0[0x24];
    /* 0x24 */ void *unk24[11];
    /* 0x50 */ R36880bNode *unk50;
    /* 0x54 */ u8 pad54[0x4C];
    /* 0xA0 */ u32 *unkA0;
    /* 0xA4 */ u32 *unkA4;
    /* 0xA8 */ u32 *unkA8;
    /* 0xAC */ u32 *unkAC;
    /* 0xB0 */ u8 padB0[8];
    /* 0xB8 */ R36880bNode *unkB8;
} R36880bObj;

void func_8063495C(u8 *arg0, ModelSlot *arg1) {
    R36880bNode *node;
    s16 *p;
    s32 n;
    s32 idx;
    s32 found;
    s32 key;

    node = ((R36880bObj *)arg1->unk20)->unk50;
    if (node != NULL) {
        do {
            key = node->unk5C;
            n = *(s32 *)(arg0 + *(s32 *)(arg0 + 0x70));
            p = (s16 *)(arg0 + *(s32 *)(arg0 + 0x70) + 4);
            found = 0;
            idx = 0;
            if (n != 0) {
                do {
                    if (key == *p) {
                        found = 1;
                    } else {
                        n--;
                        p = (s16 *)((u8 *)p + 0x30);
                        idx++;
                    }
                } while (n != 0 && found == 0);
            }
            if (found != 0) {
                node->unk44 = ((R36880bObj *)arg1->unk20)->unk24[idx];
            } else {
                node->unk44 = NULL;
            }
            node = node->unkD4;
        } while (node != NULL);
    }
}


void *memcpy(void *, const void *, unsigned int);
s32 func_80635214(u32 *);
void func_80635114(u32 *, s32, s32, s32, u32 **, u32 **, u32 **);

void func_806349FC(u8 *arg0, ModelSlot *arg1, s32 arg2) {
    s32 count;
    s32 *entry;
    s32 i;
    R36880bNode *node;
    s32 j;
    R36880bNode **tail;
    R36880bObj *obj;
    s32 len1;
    s32 len2;
    s32 *tbl;

    tbl = (s32 *)(arg0 + *(s32 *)(arg0 + 0x6C));
    count = *tbl;
    entry = tbl + 1;
    switch (arg2) {
        case 1:
            tail = &((R36880bObj *)arg1->unk20)->unkB8;
            if (count != 0) {
                obj = arg1->unk20;
                len1 = func_80635214(obj->unkA0);
                obj->unkA4 = func_80610FE8(len1);
                memcpy(obj->unkA4, obj->unkA0, len1);
                len2 = func_80635214(obj->unkA8);
                obj->unkAC = func_80610FE8(len2);
                memcpy(obj->unkAC, obj->unkA8, len2);
            }
            break;
        case 2:
            tail = &((R36880bObj *)arg1->unk20)->unk50;
            break;
    }
    for (i = 0; i < count; i++) {
        node = func_80610FE8(0xD8);
        node->unk48 = 1;
        node->unk49 = 0;
        node->unk4A = entry[1];
        node->unk4C = entry[2];
        node->unk50 = 0;
        node->unk54 = 0;
        node->unk58 = entry[3];
        node->unk5C = entry[0];
        for (j = 0; j < node->unk58 - 1; j++) {
            node->unk60[j] = entry[4 + j];
        }
        node->unkD0 = entry[0x20];
        if (D_807FBB64 & 0x2000000) {
            node->unkD0 = 0;
        }
        node->unk3C = 0;
        node->unk40 = 0;
        node->unk34 = 0;
        node->unk36 = 0;
        node->unk38 = 0;
        node->unk3A = 0;
        node->unk30 = -1;
        if (arg2 == 1) {
            func_80635114(obj->unkA0, len1, entry[0], entry[1], &node->unk0[0], &node->unk0[1], &node->unk0[2]);
            func_80635114(obj->unkA4, len1, entry[0], entry[1], &node->unk0[3], &node->unk0[4], &node->unk0[5]);
            func_80635114(obj->unkA8, len2, entry[0], entry[1], &node->unk0[6], &node->unk0[7], &node->unk0[8]);
            func_80635114(obj->unkAC, len2, entry[0], entry[1], &node->unk0[9], &node->unk0[10], &node->unk0[11]);
        }
        *tail = node;
        tail = &node->unkD4;
        entry += 0x21;
    }
    *tail = NULL;
}


void func_80634D64(s32, s16, s16, s16, s16 *, s16 *, u8);
void func_80634F14(s32, s16, u8, u8 *, u8);
void func_80635018(s32, s16, s32, s32);

void func_80634CC8(s32 arg0, s16 arg1, s16 arg2, s16 arg3) {
    func_80634D64(arg0, arg1, arg2, arg3, &arg2, &arg3, 0);
}

void func_80634D14(s32 arg0, s16 arg1, s16 *arg2, s16 *arg3) {
    s16 sp2E;
    s16 sp2C;

    func_80634D64(arg0, arg1, sp2E, sp2C, arg2, arg3, 1);
}

void func_80634E10(R36880bNode *, s16, s16, s16, s16 *, s16 *, u8);

void func_80634D64(s32 arg0, s16 arg1, s16 arg2, s16 arg3, s16 *arg4, s16 *arg5, u8 arg6) {
    ModelSlot *slot;
    R36880bObj *obj;

    slot = hashTableLookup(arg0) + ((0, D_807F6000));
    obj = slot->unk20;
    if (slot->unk86 != 1) {
        if (slot->unk86 == 2) {
            func_80634E10(obj->unk50, arg1, arg2, arg3, arg4, arg5, arg6);
        }
    } else {
        func_80634E10(obj->unkB8, arg1, arg2, arg3, arg4, arg5, arg6);
    }
}

void func_80634E10(R36880bNode *arg0, s16 arg1, s16 arg2, s16 arg3, s16 *arg4, s16 *arg5, u8 arg6) {
    arg1--;
    while (arg0 != NULL && arg1 != 0) {
        arg0 = arg0->unkD4;
        arg1--;
    }
    if (arg0 != NULL) {
        if (arg6 != 0) {
            *arg4 = arg0->unk38;
            *arg5 = arg0->unk3A;
        } else {
            arg0->unk38 = arg2;
            arg0->unk3A = arg3;
        }
    }
}

void func_80634EA4(s32 arg0, s16 arg1, u8 arg2) {
    func_80634F14(arg0, arg1, arg2, &arg2, 0);
}

void func_80634EDC(s32 arg0, s16 arg1, u8 *arg2) {
    u8 sp27;

    func_80634F14(arg0, arg1, sp27, arg2, 1);
}

void func_80634FA0(R36880bNode *, s16, u8, u8 *, u8);

void func_80634F14(s32 arg0, s16 arg1, u8 arg2, u8 *arg3, u8 arg4) {
    ModelSlot *slot;
    R36880bObj *obj;

    slot = hashTableLookup(arg0) + ((0, D_807F6000));
    obj = slot->unk20;
    if (slot->unk86 != 1) {
        if (slot->unk86 == 2) {
            func_80634FA0(obj->unk50, arg1, arg2, arg3, arg4);
        }
    } else {
        func_80634FA0(obj->unkB8, arg1, arg2, arg3, arg4);
    }
}

void func_80634FA0(R36880bNode *arg0, s16 arg1, u8 arg2, u8 *arg3, u8 arg4) {
    arg1--;
    while (arg0 != NULL && arg1 != 0) {
        arg0 = arg0->unkD4;
        arg1--;
    }
    if (arg0 != NULL) {
        if (arg4 != 0) {
            *arg3 = arg0->unk48;
        } else {
            arg0->unk48 = arg2;
        }
    }
}

void func_80635098(R36880bNode *, s16, s32, s32);

void func_80635018(s32 arg0, s16 arg1, s32 arg2, s32 arg3) {
    ModelSlot *slot;
    R36880bObj *obj;

    slot = hashTableLookup(arg0) + ((0, D_807F6000));
    obj = slot->unk20;
    if (slot->unk86 != 1) {
        if (slot->unk86 == 2) {
            func_80635098(obj->unk50, arg1, arg2, arg3);
        }
    } else {
        func_80635098(obj->unkB8, arg1, arg2, arg3);
    }
}

void func_80635098(R36880bNode *arg0, s16 arg1, s32 arg2, s32 arg3) {
    arg1--;
    while (arg0 != NULL && arg1 != 0) {
        arg0 = arg0->unkD4;
        arg1--;
    }
    if (arg0 != NULL) {
        if (arg2 != arg0->unk54 || arg3 != arg0->unk50) {
            arg0->unk49 = 1;
        }
        arg0->unk54 = arg2;
        arg0->unk50 = arg3;
    }
}

void func_80635114(u32 *arg0, s32 arg1, s32 arg2, s32 arg3, u32 **arg4, u32 **arg5, u32 **arg6) {
    s32 found;
    u32 cmd;

    *arg4 = NULL;
    *arg5 = NULL;
    *arg6 = NULL;
    found = 0;
    if (arg1 != 0) {
        do {
            cmd = *arg0;
            arg1 -= 8;
            if ((cmd >> 24) == ((0, 0xFD)) && arg2 == arg0[1]) {
                *arg4 = arg0;
                found = 1;
            }
            arg0 += 2;
        } while (found == 0 && arg1 != 0);
    }
    if (arg3 != 0) {
        found = 0;
        if (arg1 != 0) {
            do {
                cmd = *arg0;
                arg1 -= 8;
                if ((cmd >> 24) == ((0, 0xFD)) && arg2 == arg0[1]) {
                    *arg5 = arg0;
                    found = 1;
                }
                arg0 += 2;
            } while (found == 0 && arg1 != 0);
        }
        if (arg1 != 0) {
            found = 0;
            do {
                cmd = *arg0;
                arg1 -= 8;
                if ((cmd >> 24) == ((0, 0xFA))) {
                    *arg6 = arg0;
                    found = 1;
                }
                arg0 += 2;
            } while (found == 0 && arg1 != 0);
        }
    }
}


s32 func_80635214(u32 *arg0) {
    s32 len;
    s32 found;
    u32 cmd;

    len = 0;
    found = 0;
    do {
        cmd = *arg0;
        len += 8;
        if ((cmd >> 24) == ((0, 0xDF))) {
            found = 1;
        }
        arg0 += 2;
    } while (found == 0);
    return len;
}


#ifdef NON_MATCHING
typedef struct R36880bVtx {
    /* 0x00 */ s16 x;
    /* 0x02 */ s16 y;
    /* 0x04 */ s16 z;
    /* 0x06 */ s16 pad6;
    /* 0x08 */ s16 s;
    /* 0x0A */ s16 t;
    /* 0x0C */ u8 pad[4];
} R36880bVtx;

typedef struct R36880bQuad {
    /* 0x00 */ u8 pad0[4];
    /* 0x04 */ s16 x[4];
    /* 0x0C */ s16 y[4];
    /* 0x14 */ s16 z[4];
    /* 0x1C */ s16 uv[4][2];
    /* 0x2C */ u8 rgba[4];
} R36880bQuad;

typedef struct R36880bOut {
    /* 0x00 */ f32 unk0;
    /* 0x04 */ f32 unk4;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ f32 unk10;
    /* 0x14 */ u8 pad14[8];
    /* 0x1C */ R36880bVtx *unk1C;
    /* 0x20 */ u8 unk20;
    /* 0x21 */ u8 pad21[0x23];
    /* 0x44 */ u8 rgba[4];
    /* 0x48 */ s16 unk48;
} R36880bOut;

typedef struct R36880bParent {
    /* 0x00 */ u8 pad0[0x20];
    /* 0x20 */ R36880bOut *unk20;
    /* 0x24 */ u8 *unk24;
} R36880bParent;

void func_8063524C(R36880bParent *arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6, f32 arg7, f32 arg8) {
    R36880bOut *out;
    R36880bQuad *q;
    u8 *data;
    s32 i;
    s32 j;
    s16 sum;

    data = arg0->unk24;
    out = arg0->unk20;
    out->unk0 = arg1;
    out->unk4 = arg2;
    q = (R36880bQuad *)(*(s32 *)(data + 0x70) + (s32)data + 4);
    out->unk8 = arg3;
    out->unkC = arg7;
    out->unk10 = arg8;
    out->unk20 = *(s32 *)(*(s32 *)(data + 0x70) + (s32)data);
    sum = 0;
    out->unk1C = func_80610FE8(out->unk20 << 6);
    for (i = 0; i < out->unk20; i++) {
        out->rgba[0] = q->rgba[0];
        out->rgba[1] = q->rgba[1];
        out->rgba[2] = q->rgba[2];
        out->rgba[3] = q->rgba[3];
        for (j = 0; j != 4; j += 2) {
            out->unk1C[i * 4 + j].x = q->x[j];
            out->unk1C[i * 4 + j].y = q->y[j];
            out->unk1C[i * 4 + j].z = q->z[j];
            out->unk1C[i * 4 + j].s = q->uv[j][0];
            out->unk1C[i * 4 + j].t = q->uv[j][1];
            sum += q->y[j];
            out->unk1C[i * 4 + j + 1].x = q->x[j + 1];
            out->unk1C[i * 4 + j + 1].y = q->y[j + 1];
            out->unk1C[i * 4 + j + 1].z = q->z[j + 1];
            out->unk1C[i * 4 + j + 1].s = q->uv[j + 1][0];
            out->unk1C[i * 4 + j + 1].t = q->uv[j + 1][1];
            sum += q->y[j + 1];
        }
        q++;
    }
    out->unk48 = sum / (out->unk20 * 4);
}
#else

#pragma GLOBAL_ASM("asm/global/nonmatchings/36880/func_8063524C.s")
#endif



typedef struct R36880dAsset {
    /* 0x00 */ u8 pad0[0x14];
    /* 0x14 */ void *unk14;
    /* 0x18 */ void *unk18;
    /* 0x1C */ void *unk1C;
    /* 0x20 */ u8 unk20;
    /* 0x21 */ u8 pad21[3];
    /* 0x24 */ void *unk24[4];
    /* 0x34 */ void *unk34[4];
} R36880dAsset;

void func_80635468(u8 *arg0, R36880dAsset *arg1) {
    u8 type;
    s32 i;
    R36880dAsset *p;
    s16 *src;

    src = (s16 *)(arg0 + *(s32 *)(arg0 + 0x70) + 4);
    if (*(s32 *)(arg0 + *(s32 *)(arg0 + 0x6C)) != 0) {
        type = 7;
    } else {
        type = 0x19;
    }
    i = 0;
    if (arg1->unk20 > (type * 0)) {
        p = arg1;
        do {
            *(s32 *)((u8 *)p + 0x24) = (s32)func_8066B0F8(type, src[0], 1, 0);
            if (src[1] != -1) {
                *(s32 *)((u8 *)p + 0x34) = (s32)func_8066B0F8(type, src[1], 1, 0);
            } else {
                *(s32 *)((u8 *)p + 0x34) = 0;
            }
            i++;
            p = (R36880dAsset *)((u8 *)p + 4);
            src = (s16 *)((u8 *)src + 0x30);
        } while (i < arg1->unk20);
    }
}

void func_80635548(s32 arg0, u8 *arg1) {
    s32 *p;
    s32 i;

    i = 0;
    p = (s32 *)arg1;
    for (; i < arg1[0x20]; i++) {
        p[9] = 0;
        p[13] = 0;
        p++;
    }
}

void func_806355DC();
void hashTableClear(void);

void func_80635588(void) {
    s32 i;
    s32 n;

    n = D_80747D70;
    for (i = 0; i < n; i++) {
        func_806355DC(0, 0);
    }
    hashTableClear();
}

typedef struct R36880dSlotF {
    /* 0x00 */ u8 pad0[0x20];
    /* 0x20 */ s32 unk20;
    /* 0x24 */ u8 pad24[0x4C];
    /* 0x70 */ R36880bListNode *unk70;
    /* 0x74 */ R36880bListNode *unk74;
    /* 0x78 */ u8 **unk78;
    /* 0x7C */ u8 *unk7C;
    /* 0x80 */ u8 pad80[8];
    /* 0x88 */ s16 unk88;
    /* 0x8A */ s16 unk8A;
    /* 0x8C */ u8 pad8C[4];
} R36880dSlotF;

void actorClearEntrySlot(s16);
void hashTableRemove(s32);
void proxPathRemoveActor(s16);
void func_80605380(s16);
void func_8062D2AC(s32, s16 *, u8);
void func_80630588(s32, s32, s32, u8 *);
void func_8063DE68(void *);
void modelSlotFree(u8 **);
void func_80636074(ModelSlot *);

void func_806355DC(arg0, arg1)
s32 arg0;
u8 arg1;
{
    s16 sp36;
    s16 sp34;
    u8 sp33;

    if (arg1 == 1) {
        arg0 = hashTableLookup(arg0);
    }
    func_8062D2AC(((R36880dSlotF *)((u8 *)D_807F6000 + arg0 * 0x90))->unk20, &sp34, 0);
    func_80630588(0, ((R36880dSlotF *)((u8 *)D_807F6000 + arg0 * 0x90))->unk20, 2, &sp33);
    dynamicBufferFree((u8 *)&D_807F6000[arg0] + 0x28);
    func_806348B4((u8 *)&D_807F6000[arg0] + 0x48);
    func_80633570(((R36880dSlotF *)((u8 *)D_807F6000 + arg0 * 0x90))->unk70);
    func_806338B4(((R36880dSlotF *)((u8 *)D_807F6000 + arg0 * 0x90))->unk74);
    modelSlotFree(((R36880dSlotF *)((u8 *)D_807F6000 + arg0 * 0x90))->unk78);
    func_80636074(&D_807F6000[arg0]);
    if (((R36880dSlotF *)((u8 *)D_807F6000 + arg0 * 0x90))->unk7C != NULL) {
        func_8063DE68(((R36880dSlotF *)((u8 *)D_807F6000 + arg0 * 0x90))->unk7C);
    }
    D_807F6240[((R36880dSlotF *)((u8 *)D_807F6000 + arg0 * 0x90))->unk8A] = -1;
    actorClearEntrySlot(((R36880dSlotF *)((u8 *)D_807F6000 + arg0 * 0x90))->unk88);
    sp36 = ((R36880dSlotF *)((u8 *)D_807F6000 + arg0 * 0x90))->unk88;
    hashTableRemove(sp36);
    proxPathRemoveActor(sp36);
    if (((R36880dSlotF *)((u8 *)D_807F6000 + arg0 * 0x90))->unk7C != NULL) {
        if (*(s16 *)(((R36880dSlotF *)((u8 *)D_807F6000 + arg0 * 0x90))->unk7C + 0x10) != -1) {
            func_80605380(*(s16 *)(((R36880dSlotF *)((u8 *)D_807F6000 + arg0 * 0x90))->unk7C + 0x10));
        }
        if (*(s16 *)(((R36880dSlotF *)((u8 *)D_807F6000 + arg0 * 0x90))->unk7C + 0x12) != -1) {
            func_80605380(*(s16 *)(((R36880dSlotF *)((u8 *)D_807F6000 + arg0 * 0x90))->unk7C + 0x12));
        }
    }
    if (arg0 + 1 != D_80747D70) {
        hashTableInsert(((R36880dSlotF *)((u8 *)D_807F6000 + D_80747D70 * 0x90 - 0x90))->unk88, arg0);
    }
    memcpy(&D_807F6000[arg0], &D_807F6000[D_80747D70] - 1, 0x90);
    D_80747D70 -= 1;
}

typedef struct R36880dVec {
    /* 0x00 */ f32 unk0;
    /* 0x04 */ f32 unk4;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ f32 unk10;
    /* 0x14 */ f32 unk14;
    /* 0x18 */ f32 unk18;
    /* 0x1C */ f32 unk1C;
} R36880dVec;

#define R36880D_VEC(i) ((R36880dVec *)((u8 *)D_807F6000 + (i) * 0x90))

void func_806357F8(s32 arg0, f32 *arg1, f32 *arg2, f32 *arg3, f32 *arg4, f32 *arg5, f32 *arg6, f32 *arg7, f32 *arg8, u8 arg9) {
    if (arg9 == 1) {
        arg0 = hashTableLookup(arg0);
    }
    *arg1 = R36880D_VEC(arg0)->unk0;
    *arg2 = R36880D_VEC(arg0)->unk4;
    *arg3 = R36880D_VEC(arg0)->unk8;
    *arg4 = R36880D_VEC(arg0)->unk10;
    *arg5 = R36880D_VEC(arg0)->unk14;
    *arg6 = R36880D_VEC(arg0)->unk18;
    *arg7 = R36880D_VEC(arg0)->unkC;
    *arg8 = R36880D_VEC(arg0)->unk1C;
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/36880/func_806358E8.s")

typedef struct R36880dActorBox {
    /* 0x00 */ u8 pad0[0x5C];
    /* 0x5C */ u16 unk5C;
    /* 0x5E */ u8 pad5E[0x1E];
    /* 0x7C */ f32 unk7C;
    /* 0x80 */ f32 unk80;
    /* 0x84 */ f32 unk84;
} R36880dActorBox;

typedef struct R36880dActorRef {
    /* 0x0 */ R36880dActorBox *actor;
    /* 0x4 */ s32 unk4;
} R36880dActorRef;

extern R36880dActorRef gActiveActors[];
extern u16 gActiveActorCount;

s32 func_80635EF0(f32 arg0, f32 arg1, f32 arg2, s16 arg3, s16 arg4, s16 arg5, u16 arg6) {
    s32 i;
    R36880dActorBox *b;
    R36880dActorBox *a;
    s16 rx;
    s16 ry;
    s16 rz;

    rx = arg3;
    ry = arg4;
    rz = arg5;
    for (i = 0; i < gActiveActorCount; i++) {
        a = gActiveActors[i].actor;
        b = a;
        if (b->unk5C & arg6) {
            if (arg0 - arg3 <= b->unk7C && arg1 - arg4 <= b->unk80 && arg2 - arg5 <= b->unk84 &&
                a->unk7C <= arg3 + arg0 && a->unk80 <= arg4 + arg1 && a->unk84 <= arg5 + arg2) {
                return 1;
            }
        }
    }
    return 0;
}

void func_8062D094(void *, u8);

void func_80636014(s32 arg0, u8 arg1, u8 arg2) {
    if (arg1 == 1) {
        arg0 = hashTableLookup(arg0);
    }
    func_8062D094(D_807F6000[arg0].unk20, arg2);
}

typedef struct R36880dChain {
    /* 0x00 */ u8 pad0[0x3C];
    /* 0x3C */ void *unk3C;
    /* 0x40 */ void *unk40;
    /* 0x44 */ u8 pad44[0x90];
    /* 0xD4 */ struct R36880dChain *unkD4;
} R36880dChain;

typedef struct R36880dOwner {
    /* 0x00 */ u8 pad0[0x50];
    /* 0x50 */ R36880dChain *unk50;
    /* 0x54 */ s32 *unk54;
    /* 0x58 */ u8 pad58[0x60];
    /* 0xB8 */ R36880dChain *unkB8;
    /* 0xBC */ s32 *unkBC;
} R36880dOwner;

void func_806365D0(ModelSlot *, void *, R36880dOwner *);
void func_80636380(void *, R36880dAsset *);

void func_80636074(ModelSlot *arg0) {
    R36880dChain *node;
    R36880dOwner *ownerA;
    s32 *sp24;
    R36880dOwner *ownerB;
    R36880dChain *cur;

    switch (arg0->unk86) {
        case 2:
            ownerA = arg0->unk20;
            node = ownerA->unk50;
            sp24 = ownerA->unk54;
            func_80636380(arg0->unk24, (R36880dAsset *)ownerA);
            break;
        case 1:
            ownerB = arg0->unk20;
            node = ownerB->unkB8;
            sp24 = ownerB->unkBC;
            func_806365D0(arg0, arg0->unk24, ownerB);
            break;
    }
    if (node != NULL) {
        do {
            if (node->unk3C != NULL) {
                assetFreeBuffer(node->unk3C, 0x9DB, 7);
            }
            if (node->unk40 != NULL) {
                assetFreeBuffer(node->unk40, 0x9DC, 7);
            }
            cur = node;
            node = node->unkD4;
            heapFree(cur);
        } while (node != NULL);
    }
    if (sp24 != NULL) {
        assetFreeBuffer((void *)*sp24, 0x9E5, 7);
        heapFree(sp24);
    }
}

typedef struct R36880b2Chain {
    /* 0x00 */ u8 pad0[0x3C];
    /* 0x3C */ void *unk3C;
    /* 0x40 */ void *unk40;
    /* 0x44 */ u8 pad44[0x8C];
    /* 0xD0 */ u8 unkD0;
    /* 0xD4 */ struct R36880b2Chain *unkD4;
} R36880b2Chain;

typedef struct R36880b2Owner {
    /* 0x00 */ u8 pad0[0x50];
    /* 0x50 */ R36880b2Chain *unk50;
    /* 0x54 */ u8 pad54[0x64];
    /* 0xB8 */ R36880b2Chain *unkB8;
} R36880b2Owner;

void func_80636164(R36880b2Owner *arg0, u8 arg1) {
    R36880b2Chain *node;

    if (arg1 != 1) {
        if (arg1 == 2) {
            node = arg0->unk50;
            goto walk;
        }
    } else {
        node = arg0->unkB8;
walk:
        if (node != NULL) {
            do {
                if (node->unk3C != NULL && node->unkD0 == 0) {
                    assetFreeBuffer(node->unk3C, 0xA09, 7);
                    node->unk3C = NULL;
                }
                if (node->unk40 != NULL && node->unkD0 == 0) {
                    assetFreeBuffer(node->unk40, 0xA0E, 7);
                    node->unk40 = NULL;
                }
                node = node->unkD4;
            } while (node != NULL);
        }
    }
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/36880/func_80636210.s")

void func_806362C4(s32 arg0, u8 arg1) {
    s32 *sp1C;
    s32 **sp18;
    ModelSlot *slot;
    s32 ***pp;

    if (arg1 == 1) {
        arg0 = hashTableLookup(arg0);
    }
    slot = &D_807F6000[arg0];
    if (slot->unk86 != 1) {
        if (slot->unk86 == 2) {
            sp18 = (s32 **)((u8 *)slot->unk20 + 0x54);
        }
    } else {
        sp18 = (s32 **)((u8 *)slot->unk20 + 0xBC);
    }
    pp = &sp18;
    if (*pp != NULL) {
        sp1C = **pp;
        if (sp1C != NULL) {
            assetFreeBuffer((void *)*sp1C, 0xA56, 7);
            heapFree(sp1C);
            **pp = NULL;
        }
    }
}

void heapFreeDeferred(void *);

void func_80636380(void *arg0, R36880dAsset *arg1) {
    s32 i;
    void **p;

    p = (void **)arg1;
    i = 0;
    if (arg1->unk20 > 0) {
        do {
            if (p[9] != NULL) {
                assetFreeBuffer(p[9], 0xA69, 7);
            }
            if (p[13] != NULL) {
                assetFreeBuffer(p[13], 0xA6A, 7);
            }
            i++;
            p++;
        } while (i < arg1->unk20);
    }
    assetFreeBuffer(arg0, 0xA6E, 7);
    heapFreeDeferred(arg1->unk1C);
    heapFreeDeferred(arg1);
    heapFreeDeferred(arg1->unk14);
    heapFreeDeferred(arg1->unk18);
}

typedef struct R36880b2Rec {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ s32 unk8;
    /* 0x0C */ s32 unkC;
    /* 0x10 */ s32 unk10;
    /* 0x14 */ s32 unk14;
    /* 0x18 */ struct R36880b2Rec *unk18;
} R36880b2Rec;

extern R36880b2Rec *D_807F6160;

void func_8063643C(void) {
    D_807F6160 = 0;
}

void func_80636448(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    R36880b2Rec *rec;
    R36880b2Rec *old;

    rec = func_80610FE8(0x1C);
    old = D_807F6160;
    D_807F6160 = rec;
    rec->unk18 = old;
    rec->unk0 = arg0;
    rec->unk4 = arg1;
    rec->unk8 = arg2;
    rec->unkC = arg3;
    rec->unk14 = D_8076A064 + 2;
    rec->unk10 = arg4;
}

typedef struct R36880dCount {
    /* 0x00 */ u8 pad0[0x3C];
    /* 0x3C */ s16 unk3C;
} R36880dCount;

void func_80636784(s32, s32, s32, s32, s32);

void func_806364C4(void) {
    R36880b2Rec *cur;
    R36880b2Rec *prev;
    R36880b2Rec *next;

    cur = D_807F6160;
    prev = NULL;
    if (cur != NULL) {
        do {
            next = cur->unk18;
            if (D_8076A064 == cur->unk14) {
                ((R36880dCount *)cur->unk10)->unk3C -= 1;
                func_80636784(cur->unk0, cur->unk4, 0, 0, ((R36880dCount *)cur->unk10)->unk3C == 0);
                func_80636784(cur->unk8, cur->unkC, 0, 1, ((R36880dCount *)cur->unk10)->unk3C == 0);
                assetFreeBuffer((void *)cur->unk10, 0xAB1, 7);
                if (prev == NULL) {
                    D_807F6160 = cur->unk18;
                } else {
                    prev->unk18 = cur->unk18;
                }
                heapFree(cur);
            } else {
                prev = cur;
            }
            cur = next;
        } while (next != NULL);
    }
}

typedef struct R36880eCmd {
    /* 0x0 */ u32 unk0;
    /* 0x4 */ s32 unk4;
} R36880eCmd;

typedef struct R36880eLink {
    /* 0x00 */ void *unk0;
    /* 0x04 */ void *unk4;
    /* 0x08 */ u8 pad8[4];
    /* 0x0C */ void *unkC;
    /* 0x10 */ void *unk10;
    /* 0x14 */ u8 pad14[4];
    /* 0x18 */ void *unk18;
    /* 0x1C */ void *unk1C;
    /* 0x20 */ u8 pad20[4];
    /* 0x24 */ void *unk24;
    /* 0x28 */ void *unk28;
    /* 0x2C */ u8 pad2C[0xA8];
    /* 0xD4 */ struct R36880eLink *unkD4;
} R36880eLink;

typedef struct R36880eSeg {
    /* 0x00 */ u8 pad0[0xA0];
    /* 0xA0 */ u32 unkA0;
    /* 0xA4 */ u32 unkA4;
    /* 0xA8 */ u32 unkA8;
    /* 0xAC */ u32 unkAC;
    /* 0xB0 */ u32 unkB0;
    /* 0xB4 */ s16 unkB4;
    /* 0xB6 */ s16 unkB6;
    /* 0xB8 */ R36880eLink *unkB8;
    /* 0xBC */ s32 unkBC;
    /* 0xC0 */ u8 padC0[3];
    /* 0xC3 */ u8 unkC3;
} R36880eSeg;

typedef struct R36880eDLObj {
    /* 0x00 */ u8 pad0[4];
    /* 0x04 */ s32 unk4;
    /* 0x08 */ u8 pad8[0x28];
    /* 0x30 */ s32 unk30;
} R36880eDLObj;

typedef struct R36880ePtrSet {
    /* 0x0 */ R36880eDLObj *unk0;
    /* 0x4 */ R36880eDLObj *unk4;
    /* 0x8 */ s32 *unk8;
} R36880ePtrSet;

typedef struct R36880eNode {
    /* 0x00 */ R36880ePtrSet unk0[2];
    /* 0x18 */ R36880ePtrSet unk18[2];
    /* 0x30 */ s32 unk30;
    /* 0x34 */ s16 unk34;
    /* 0x36 */ s16 unk36;
    /* 0x38 */ s16 unk38;
    /* 0x3A */ s16 unk3A;
    /* 0x3C */ s32 unk3C;
    /* 0x40 */ s32 unk40;
    /* 0x44 */ s32 unk44;
    /* 0x48 */ u8 unk48;
    /* 0x49 */ u8 unk49;
    /* 0x4A */ u8 unk4A;
    /* 0x4B */ u8 pad4B;
    /* 0x4C */ s32 unk4C;
    /* 0x50 */ s32 unk50;
    /* 0x54 */ s32 unk54;
    /* 0x58 */ s32 unk58;
    /* 0x5C */ s32 unk5C[29];
    /* 0xD0 */ u8 unkD0;
    /* 0xD1 */ u8 padD1[3];
    /* 0xD4 */ struct R36880eNode *unkD4;
} R36880eNode;

typedef struct R36880eOwner {
    /* 0x00 */ u8 pad0[0x24];
    /* 0x24 */ s32 unk24[8];
    /* 0x44 */ u8 pad44[0xC];
    /* 0x50 */ R36880eNode *unk50;
} R36880eOwner;

void func_80639CD0(R36880eNode *, s32 *, s32 *, u8 *, s16 *);
void collisionBstLookupByHash(s32, s32 *, s32 *);

#pragma GLOBAL_ASM("asm/global/nonmatchings/36880/func_806365D0.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/36880/func_80636784.s")

typedef struct R36880eAssetHdr {
    /* 0x00 */ u8 pad0[0x1C];
    /* 0x1C */ u8 unk1C;
    /* 0x1D */ u8 pad1D[0x23];
    /* 0x40 */ s32 unk40;
    /* 0x44 */ s32 unk44;
    /* 0x48 */ s32 unk48;
} R36880eAssetHdr;

typedef struct R36880eObj60 {
    /* 0x00 */ u8 pad0[0x14];
    /* 0x14 */ void *unk14;
    /* 0x18 */ void *unk18;
    /* 0x1C */ u8 pad1C[0x2E];
    /* 0x4A */ s16 unk4A;
    /* 0x4C */ s16 unk4C;
    /* 0x4E */ u8 unk4E;
    /* 0x4F */ u8 pad4F;
    /* 0x50 */ s32 unk50;
    /* 0x54 */ s32 unk54;
    /* 0x58 */ u8 pad58[3];
    /* 0x5B */ u8 unk5B;
} R36880eObj60;

extern u8 D_80750AB4;
u8 func_80636A8C(s32);

void func_806368F0(ModelSlot *arg0, s32 arg1) {
    R36880eAssetHdr *hdr;
    R36880eSeg *seg;
    s32 pad;
    void *sp28;
    R36880eObj60 *obj;

    if (func_80636A8C(arg1) != 0) {
        arg0->unk24 = func_8066B0F8(4, arg1, 1, 1);
    } else {
        arg0->unk24 = func_8066B0F8(4, arg1, 1, 0);
    }
    hdr = (R36880eAssetHdr *)arg0->unk24;
    arg0->unk8C = 0;
    arg0->unk86 = hdr->unk1C;
    arg0->unk84 = arg1;
    if (hdr->unk1C != 1) {
        if (hdr->unk1C == 2) {
            obj = func_80610FE8(0x60);
            sp28 = obj;
            obj->unk4A = arg1;
            obj->unk50 = 0;
            obj->unk54 = 0;
            obj->unk4C = -1;
            obj->unk4E = 0;
            obj->unk5B = 0;
            obj->unk14 = func_80610FE8(D_80750AB4 << 6);
            obj->unk18 = func_80610FE8(D_80750AB4 << 6);
        }
    } else {
        seg = func_80610FE8(0xC8);
        sp28 = seg;
        seg->unkB4 = arg1;
        seg->unkB8 = 0;
        seg->unkA0 = hdr->unk40 + (u32)hdr;
        seg->unkA8 = hdr->unk44 + (u32)hdr;
        seg->unkB0 = hdr->unk48 + (u32)hdr;
        seg->unkBC = 0;
        seg->unkB6 = -1;
        seg->unkC3 = 0;
    }
    arg0->unk20 = sp28;
}

f32 func_80636A44(s32 arg0) {
    s32 pad;
    s32 *asset;
    f32 result;

    asset = func_8066B0F8(4, arg0, 1, 0);
    result = ((f32 *)asset)[1];
    assetFreeBuffer(asset, 0xB87, 7);
    return result;
}

u8 func_80636A8C(s32 arg0) {
    s32 pad;
    s32 *asset;
    s32 result;

    asset = func_8066B0F8(4, arg0, 1, 0);
    if (*asset & 8) {
        result = 1;
    } else {
        result = 0;
    }
    assetFreeBuffer(asset, 0xBA3, 7);
    return result;
}

#ifdef NON_MATCHING
typedef struct R36880eSegOwner {
    /* 0x00 */ u8 pad0[0x20];
    /* 0x20 */ R36880eSeg *unk20;
} R36880eSegOwner;

void renderReplaceSegment6Commands();

void func_80636AE8(void *arg0) {
    u32 head;
    R36880eSeg *seg;
    u32 mid;
    u32 count;

    seg = ((R36880eSegOwner *)arg0)->unk20;
    mid = seg->unkA8;
    head = seg->unkA0;
    head = (mid - head) >> 3;
    count = (seg->unkB0 - mid) >> 3;
    renderReplaceSegment6Commands(seg->unkA0, seg->unkA0 + head * 8, seg, seg->unkB0 - mid);
    renderReplaceSegment6Commands(seg->unkA8, seg->unkA8 + count * 8, seg, count);
}
#else

#pragma GLOBAL_ASM("asm/global/nonmatchings/36880/func_80636AE8.s")
#endif

void func_80636B50(R36880eCmd *arg0, R36880eCmd *arg1, u8 arg2) {
    u32 w;
    u32 tag;
    s32 sp34;
    s32 sp30;

    if (arg0 != arg1) {
        do {
            w = arg0->unk0;
            tag = w >> 24;
            if (0xFD == tag) {
                if (arg2) {
                    collisionBstLookupByHash(arg0->unk4, &sp34, &sp30);
                }
                assetFreeBuffer((void *)arg0->unk4, 0xBCD, 7);
                if (arg2) {
                    arg0->unk4 = sp30;
                }
            }
            arg0++;
        } while (arg0 != arg1);
    }
}


#ifdef NON_MATCHING
typedef struct R36880eObjHdr {
    /* 0x00 */ u32 unk0;
    /* 0x04 */ u8 pad4[4];
    /* 0x08 */ s32 unk8;
    /* 0x0C */ u8 padC[0x10];
    /* 0x1C */ u8 unk1C;
    /* 0x1D */ u8 pad1D[0x1F];
    /* 0x3C */ s16 unk3C;
} R36880eObjHdr;

extern s16 D_80747D74;

void func_80636C00(void) {
    u32 mid;
    R36880eSeg *seg;
    u32 head;
    u32 tail;
    u8 flag;
    R36880eObjHdr *obj;
    ModelSlot *slot;
    u32 start;

    if (D_80747D70 != 0) {
        D_80747D74 += 1;
        if (D_80747D74 >= D_80747D70) {
            D_80747D74 = 0;
        }
        slot = (ModelSlot *)((u8 *)D_807F6000 + D_80747D74 * 0x90);
        obj = (R36880eObjHdr *)slot->unk24;
        if (obj->unk0 & 0x10) {
            if ((slot->unk8C & 0x20) && D_8076A064 != obj->unk8) {
                slot->unk8C &= ~0x20;
                obj->unk3C -= 1;
                if (obj->unk3C != 0) {
                    flag = 0;
                } else {
                    flag = 1;
                }
                seg = ((ModelSlot *)((u8 *)D_807F6000 + D_80747D74 * 0x90))->unk20;
                mid = seg->unkA8;
                start = seg->unkA0;
                head = (mid - start) >> 3;
                tail = (seg->unkB0 - mid) >> 3;
                func_80636B50((R36880eCmd *)seg->unkA0, (R36880eCmd *)(seg->unkA0 + head * 8), flag);
                func_80636B50((R36880eCmd *)seg->unkA8, (0, (R36880eCmd *)(seg->unkA8 + tail * 8)), flag);
            }
        }
    }
}
#else

#pragma GLOBAL_ASM("asm/global/nonmatchings/36880/func_80636C00.s")
#endif



#pragma GLOBAL_ASM("asm/global/nonmatchings/36880/func_80636D38.s")


s32 func_80636EFC(R36880eCmd *arg0, R36880eCmd *arg1, R36880eNode *arg2, u8 arg3) {
    u32 w;
    u32 tag;
    s32 result;
    s32 found;
    R36880eNode *node;

    result = 0;
    if (arg0 != arg1) {
        do {
            w = arg0->unk0;
            found = 0;
            tag = w >> 24;
            if (0xFD == tag) {
                node = arg2;
                if (node != NULL) {
                    do {
                        if (arg0->unk4 == node->unk5C[0]) {
                            found = 1;
                        } else {
                            node = node->unkD4;
                        }
                    } while (found == 0 && node != NULL);
                }
                if (found == 0) {
                    arg0->unk4 = (s32)func_8066B0F8(0x19, arg0->unk4, (u8)(arg3 == 0), 0);
                    if (arg0->unk4 & 7) {
                        arg0->unk4 &= ~0xF;
                        result = 1;
                    }
                }
            }
            arg0++;
        } while (arg0 != arg1);
    }
    return result;
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/36880/func_80636FFC.s")

typedef struct L80637B6CObj {
    /* 0x00 */ f32 unk0;
    /* 0x04 */ f32 unk4;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ u8 pad10[4];
    /* 0x14 */ Mtx *unk14;
    /* 0x18 */ Mtx *unk18;
    /* 0x1C */ Vtx *unk1C;
    /* 0x20 */ u8 unk20;
    /* 0x21 */ u8 pad21[3];
    /* 0x24 */ s32 unk24;
    /* 0x28 */ u8 pad28[0xC];
    /* 0x34 */ s32 unk34[4];
    /* 0x44 */ u8 unk44;
    /* 0x45 */ u8 unk45;
    /* 0x46 */ u8 unk46;
    /* 0x47 */ u8 unk47;
    /* 0x48 */ s16 unk48;
    /* 0x4A */ s16 unk4A;
    /* 0x4C */ s16 unk4C;
    /* 0x4E */ u8 unk4E;
    /* 0x4F */ u8 pad4F;
    /* 0x50 */ u8 pad50[8];
    /* 0x58 */ s16 unk58;
    /* 0x5A */ u8 unk5A;
    /* 0x5B */ u8 unk5B;
    /* 0x5C */ u8 unk5C;
} L80637B6CObj;

#define L80637B6C_GFX(a, b) { Gfx *_g = (Gfx *)(arg1++); _g->words.w0 = (a); _g->words.w1 = (b); }

extern u8 D_807F6009;
extern s32 D_807F600C;
extern s32 D_807F5FD8;

f32 renderScaleDistanceByFov(f32);
void func_8065EB10(u8, s16, f32, f32, f32, s32, f32, s32);
s32 func_80658E8C(f32, f32, f32, s32, s32);
void func_80626F8C(f32, f32, f32, f32 *, f32 *, s32, f32, s32);
void func_80658C10(void *, s16, s16, s16);
u8 mapSearchTableGetValue(void *);
void func_8065C334(f32, f32, f32, s16, u8 *, u8 *, u8 *, s16);
void func_806392BC(s16, u8 *, s16 *);
void func_80639C04(R36880eOwner *, s32, s32 *, s32 *, u8 *, s16 *);
void func_80639FC0(f32, f32, f32, f32, f32, f32, f32 *, f32 *, f32 *, u8);

Gfx *func_80637B6C(L80637B6CObj *arg0, Gfx *arg1, f32 arg2, f32 arg3, f32 arg4, u8 arg5, s16 arg6) {
    f32 sp238[4][4];
    f32 sp1F8[4][4];
    f32 sp1F4;
    f32 sp1F0;
    f32 sp1EC;
    s32 sp1E8;
    s32 sp1E4;
    u8 sp1E3;
    s16 sp1E0;
    f32 dx;
    f32 sp1D8;
    f32 sp1D4;
    f32 sp1D0;
    f32 dy;
    f32 dz;
    s32 pad0;
    f32 scale;
    s16 limit;
    s32 i;
    s32 sp1B4;
    s16 pad16;
    s16 sp1B0;
    u8 sp1AF;
    u8 sp1AE;
    u8 sp1AD;
    u8 sp1AC;
    u8 sp1AB;
    Mtx *mtx;
    s32 pad[1];

    if (0) {
        func_806392BC(0, &arg5, 0);
    }
    sp1B4 = 0;
    sp1AF = 0;
    if (arg5 != 0) {
        dx = arg2 - arg0->unk0;
        dy = arg3 - arg0->unk4;
        dz = arg4 - arg0->unk8;
        dx *= dx;
        dy *= dy;
        dz *= dz;
        sp1D0 = sqrtf(dx + dy + dz);
        limit = renderScaleDistanceByFov((f32)arg0->unk58);
        if ((f32)limit < sp1D0) {
            return arg1;
        }
    }
    if (arg0->unk5B != 0) {
        func_8065EB10(arg0->unk5B, arg0->unk4C, arg0->unk0, arg0->unk4, arg0->unk8, arg0->unk58, sp1D0 / (f32)limit, arg6);
    }
    if (arg5 != 0) {
        if (func_80658E8C(arg0->unk0, arg0->unk4, arg0->unk8, 0, 0) != 0) {
            return arg1;
        }
    } else {
        limit = -0x8000;
        sp1D0 = 1.0f;
    }
    if (arg0->unk4E & 0x10) {
        return arg1;
    }
    if (arg0->unk4E & 8) {
        func_80626F8C(arg0->unk0, arg0->unk4, arg0->unk8, &sp1D8, &sp1D4, 0, 1.0f, D_807FC929);
        func_80658C10(arg0, sp1D8, sp1D4, sp1D0);
        if (mapSearchTableGetValue(arg0) != 0) {
            return arg1;
        }
    }
    D_807F5FD8 += 1;
    if (arg0->unk24 == 0) {
        func_80635468(D_807F6000[(s16)hashTableLookup(arg0->unk4C)].unk24, (R36880dAsset *)arg0);
    }
    func_80639FC0(arg0->unk0, arg0->unk4, arg0->unk8, arg2, arg3, arg4, &sp1F4, &sp1F0, &sp1EC, arg0->unk4E & 4);
    guTranslateF(sp238, 0.0f, -arg0->unk48, 0.0f);
    if (sp1F4 != 0.0) {
        guRotateF(sp1F8, sp1F4, 1.0f, 0.0f, 0.0f);
        guMtxCatF(sp238, sp1F8, sp238);
    }
    if (sp1F0 != 0.0) {
        guRotateF(sp1F8, sp1F0, 0.0f, 1.0f, 0.0f);
        guMtxCatF(sp238, sp1F8, sp238);
    }
    if (arg0->unkC != 1.0) {
        guScaleF(sp1F8, arg0->unkC, arg0->unkC, arg0->unkC);
        guMtxCatF(sp238, sp1F8, sp238);
    }
    guTranslateF(sp1F8, arg0->unk0, arg0->unk4 + arg0->unk48 * arg0->unkC, arg0->unk8);
    guMtxCatF(sp238, sp1F8, sp238);
    switch (D_807444FC) {
    case 0:
        mtx = arg0->unk14 + D_807FC929;
        break;
    case 1:
        mtx = arg0->unk18 + D_807FC929;
        break;
    }
    guMtxF2L(sp238, mtx);
    L80637B6C_GFX(0xE7000000, 0);
    L80637B6C_GFX(0xD9000000, 0);
    L80637B6C_GFX(0xDA380000, osVirtualToPhysical(mtx));
    if (sp1D0 < (f32)((limit * 3) / 4)) {
        sp1AE = 1;
        sp1B0 = 0xFF;
    } else {
        sp1AE = 0;
        sp1B0 = ((sp1D0 - (f32)((limit * 3) / 4)) / ((f32)limit - (f32)((limit * 3) / 4))) * 255.0f;
        if (sp1B0 >= 0x100) {
            sp1B0 = 0xFF;
        }
        sp1B0 = 0xFF - sp1B0;
    }
    func_806392BC(arg0->unk4A, &sp1AE, &sp1B0);
    if (arg5 != 0 && arg0->unk5A == 0) {
        func_8065C334(arg0->unk0, arg0->unk4, arg0->unk8, 0, &sp1AD, &sp1AC, &sp1AB, arg6);
        scale = (f32)(u32)arg0->unk5C / 15.0f;
        sp1AD = (f32)(u32)sp1AD * scale;
        sp1AC = (f32)(u32)sp1AC * scale;
        sp1AB = (f32)(u32)sp1AB * scale;
    } else {
        sp1AD = sp1AC = sp1AB = 0xFF;
    }
    for (i = 0; i < arg0->unk20; i++) {
        func_80639C04((R36880eOwner *)arg0, i, &sp1E8, &sp1E4, &sp1E3, &sp1E0);
        L80637B6C_GFX(0xE7000000, 0);
        if (arg0->unk4E & 2) {
            if (sp1AE != 0) {
                gSPSetOtherMode(arg1++, G_SETOTHERMODE_L, 3, 29, 0x0C193078);
            } else {
                gSPSetOtherMode(arg1++, G_SETOTHERMODE_L, 3, 29, 0x0C184A50);
            }
        } else if (arg0->unk4E & 1) {
            gSPSetOtherMode(arg1++, G_SETOTHERMODE_L, 3, 29, 0x0C184A50);
        } else {
            gSPSetOtherMode(arg1++, G_SETOTHERMODE_L, 3, 29, 0x0C184240);
        }
        gSPSetOtherMode(arg1++, G_SETOTHERMODE_H, 20, 2, 0x100000);
        if ((arg0->unk4E & 1) || (arg0->unk4E & 2)) {
            L80637B6C_GFX(0xD9FFFFFF, 0x210005);
        } else {
            L80637B6C_GFX(0xD9FFFFFF, 0x210004);
        }
        gDPSetPrimColor(arg1++, 0, sp1E0, sp1AD, sp1AC, sp1AB, sp1B0);
        switch (sp1E3) {
        case 0:
            L80637B6C_GFX(0xFC1197FF, 0xFFFFFE38);
            L80637B6C_GFX(0xD7000002, 0xFFFFFFFF);
            if (D_807F6009 != 2 || sp1E8 != D_807F600C) {
                switch (arg0->unk46) {
                case 0:
                    gDPLoadTextureBlock_4b(arg1++, sp1E8 + 0x80000000, arg0->unk47, arg0->unk44, arg0->unk45, 0, G_TX_CLAMP, G_TX_CLAMP, 0, 0, 0, 0);
                    if (arg0->unk47 == 2) {
                        gDPSetTextureImage(arg1++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, arg0->unk34[i]);
                        gDPTileSync(arg1++); gDPSetTile(arg1++, G_IM_FMT_RGBA, G_IM_SIZ_4b, 0, 0x100, G_TX_LOADTILE, 0, 0, 0, 0, 0, 0, 0);
                        gDPLoadSync(arg1++);
                        gDPLoadTLUTCmd(arg1++, G_TX_LOADTILE, 15); gDPPipeSync(arg1++);
                        gDPSetTextureLUT(arg1++, G_TT_RGBA16);
                        sp1AF = 1;
                    }
                    break;
                case 1:
                    gDPLoadTextureBlock(arg1++, sp1E8 + 0x80000000, arg0->unk47, G_IM_SIZ_8b, arg0->unk44, arg0->unk45, 0, G_TX_CLAMP, G_TX_CLAMP, 0, 0, 0, 0);
                    if (arg0->unk47 == 2) {
                        gDPSetTextureImage(arg1++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, arg0->unk34[i]);
                        gDPTileSync(arg1++); gDPSetTile(arg1++, G_IM_FMT_RGBA, G_IM_SIZ_4b, 0, 0x100, G_TX_LOADTILE, 0, 0, 0, 0, 0, 0, 0);
                        gDPLoadSync(arg1++);
                        gDPLoadTLUTCmd(arg1++, G_TX_LOADTILE, 255); gDPPipeSync(arg1++);
                        gDPSetTextureLUT(arg1++, G_TT_RGBA16);
                        sp1AF = 1;
                    }
                    break;
                case 2:
                    gDPLoadTextureBlock(arg1++, sp1E8 + 0x80000000, arg0->unk47, G_IM_SIZ_16b, arg0->unk44, arg0->unk45, 0, G_TX_CLAMP, G_TX_CLAMP, 0, 0, 0, 0);
                    break;
                case 3:
                    gDPLoadTextureBlock(arg1++, sp1E8 + 0x80000000, arg0->unk47, G_IM_SIZ_32b, arg0->unk44, arg0->unk45, 0, G_TX_CLAMP, G_TX_CLAMP, 0, 0, 0, 0);
                    break;
                }
            }
            D_807F600C = sp1E8;
            break;
        case 1:
            L80637B6C_GFX(0xFC272C03, 0x1F1C93F8);
            L80637B6C_GFX(0xD7000002, 0xFFFFFFFF);
            gSPSetOtherMode(arg1++, G_SETOTHERMODE_H, 16, 1, 0);
            gDPSetTextureImage(arg1++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, sp1E8);
            gDPSetTile(arg1++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, 0, 0, 0, 0, 0, 0);
            gDPLoadSync(arg1++);
            gDPLoadBlock(arg1++, G_TX_LOADTILE, 0, 0, ((arg0->unk44 * arg0->unk45 * 2) >> 1) - 1, CALC_DXT(arg0->unk44, 2));
            gDPSetTextureImage(arg1++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, sp1E4);
            gDPTileSync(arg1++);
            gDPSetTile(arg1++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0x100, G_TX_LOADTILE, 0, 0, 0, 0, 0, 0, 0);
            gDPLoadSync(arg1++);
            gDPLoadBlock(arg1++, G_TX_LOADTILE, 0, 0, ((arg0->unk44 * arg0->unk45 * 2) >> 1) - 1, CALC_DXT(arg0->unk44, 2));
            gDPSetTile(arg1++, G_IM_FMT_RGBA, G_IM_SIZ_16b, arg0->unk44 / 4, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 0, 0, G_TX_CLAMP, 0, 0);
            gDPSetTileSize(arg1++, G_TX_RENDERTILE, 2, 2, ((arg0->unk44 - 1) << 2) + 2, ((arg0->unk45 - 1) << 2) + 2);
            gDPSetTile(arg1++, G_IM_FMT_RGBA, G_IM_SIZ_16b, arg0->unk44 / 4, 0x100, 1, 0, G_TX_CLAMP, 0, 0, G_TX_CLAMP, 0, 0);
            gDPSetTileSize(arg1++, 1, 2, 2, ((arg0->unk44 - 1) << 2) + 2, ((arg0->unk45 - 1) << 2) + 2);
            D_807F600C = 0;
            break;
        }
        L80637B6C_GFX(0x01004008, osVirtualToPhysical(arg0->unk1C + sp1B4));
        L80637B6C_GFX(0x06000204, 0x406);
        sp1B4 += 4;
        D_807F6009 = 2;
    }
    L80637B6C_GFX(0xD8380002, 0x40);
    L80637B6C_GFX(0xE7000000, 0);
    gSPSetOtherMode(arg1++, G_SETOTHERMODE_H, 20, 2, 0);
    gSPSetOtherMode(arg1++, G_SETOTHERMODE_H, 16, 1, 0x10000);
    if (sp1AF != 0) {
        gSPSetOtherMode(arg1++, G_SETOTHERMODE_H, 14, 2, 0);
    }
    gSPSetOtherMode(arg1++, G_SETOTHERMODE_L, 2, 1, 0);
    return arg1;
}

typedef struct R36880hCtl {
    /* 0x000 */ u8 pad0[0x174];
    /* 0x174 */ struct R36880hCtl2 *unk174;
} R36880hCtl;

typedef struct R36880hCtl2 {
    /* 0x000 */ u8 pad0[0x1F4];
    /* 0x1F4 */ s32 unk1F4;
} R36880hCtl2;

typedef struct R36880hObj {
    /* 0x00 */ u8 pad0[0x58];
    /* 0x58 */ s32 unk58;
} R36880hObj;

typedef struct R36880hPlayer {
    /* 0x000 */ u8 pad0[4];
    /* 0x004 */ R36880hObj *unk4;
    /* 0x008 */ u8 pad8[0x2E8];
} R36880hPlayer; /* 0x2F0 */

extern u8 D_8074E77C[];
typedef struct R36880hKong {
    /* 0x00 */ u8 unk0;
    /* 0x01 */ u8 pad1[0x5D];
} R36880hKong; /* 0x5E */

typedef struct R36880hPl {
    /* 0x000 */ R36880hKong kong[8];
    /* 0x2F0 */ u8 pad2F0[0x16];
} R36880hPl; /* 0x306 */

extern R36880hPl D_807FC952[];

#define R36880H_CUR ((R36880hPlayer *)D_807FC924)[D_807FC929].unk4

void func_806392BC(s16 arg0, u8 *arg1, s16 *arg2) {
    s32 hit = 0;
    R36880hCtl2 *ctl;

    switch (arg0) {
    case 0x24:
        if (R36880H_CUR->unk58 != 3) {
            hit = 1;
        }
        break;
    case 0x1D:
        if (R36880H_CUR->unk58 != 2) {
            hit = 1;
        }
        break;
    case 0x1C:
        if (R36880H_CUR->unk58 != 5) {
            hit = 1;
        }
        break;
    case 0x23:
        if (R36880H_CUR->unk58 != 4) {
            hit = 1;
        }
        break;
    case 0x27:
        if (R36880H_CUR->unk58 != 6) {
            hit = 1;
        }
        break;
    case 0xD:
        if (R36880H_CUR->unk58 != 2) {
            hit = 1;
        }
        break;
    case 0xA:
        if (R36880H_CUR->unk58 != 3) {
            hit = 1;
        }
        break;
    case 0x16:
        if (R36880H_CUR->unk58 != 5) {
            hit = 1;
        }
        break;
    case 0x1E:
        if (R36880H_CUR->unk58 != 4) {
            hit = 1;
        }
        break;
    case 0x1F:
        if (R36880H_CUR->unk58 != 6) {
            hit = 1;
        }
        break;
    case 0x2B:
        if (R36880H_CUR->unk58 != 2) {
            hit = 1;
        }
        break;
    case 0x208:
        if (R36880H_CUR->unk58 != 3) {
            hit = 1;
        }
        break;
    case 0x207:
        if (R36880H_CUR->unk58 != 5) {
            hit = 1;
        }
        break;
    case 0x205:
        if (R36880H_CUR->unk58 != 4) {
            hit = 1;
        }
        break;
    case 0x206:
        if (R36880H_CUR->unk58 != 6) {
            hit = 1;
        }
        break;
    case 0x11:
        if ((D_807FC952[D_807FC929].kong[D_8074E77C[D_807FC929]].unk0 & 3) != 3) {
            hit = 1;
        }
        break;
    case 0x8F:
        if (!(D_807FC952[D_807FC929].kong[D_8074E77C[D_807FC929]].unk0 & 1)) {
            hit = 1;
        }
        break;
    case 0x98:
        ctl = ((R36880hCtl *)R36880H_CUR)->unk174;
        if (!(ctl->unk1F4 & 1)) {
            hit = 1;
        }
        break;
    case 0x8E:
        ctl = ((R36880hCtl *)R36880H_CUR)->unk174;
        if (!(ctl->unk1F4 & 2)) {
            hit = 1;
        }
        break;
    }
    if (hit != 0) {
        *arg1 = 0;
        if (*arg2 > 0x64) {
            *arg2 = 0x64;
        }
    }
}

typedef struct R36880eFlags {
    /* 0x00 */ u8 pad0[0x4E];
    /* 0x4E */ u8 unk4E;
} R36880eFlags;

void func_806398E4(s32 arg0, u8 arg1, u8 arg2) {
    R36880eFlags *obj;

    if (arg1 == 1) {
        arg0 = hashTableLookup(arg0);
    }
    obj = D_807F6000[arg0].unk20;
    if (arg2 != 0) {
        obj->unk4E |= 1;
    } else {
        obj->unk4E &= ~1;
    }
    obj->unk4E &= ~2;
}

void func_80639968(R36880eSeg *arg0) {
    s32 pad;
    s32 sp60;
    s32 sp5C;
    u8 sp5B;
    s16 sp58;
    R36880eNode *node;
    s32 *dst;

    node = (R36880eNode *)arg0->unkB8;
    if (node != NULL) {
        do {
            func_80639CD0(node, &sp60, &sp5C, &sp5B, &sp58);
            if (node->unk0[D_807444FC].unk0 != NULL) {
                node->unk0[D_807444FC].unk0->unk4 = sp60;
                if (sp5B == 0) {
                    dst = &node->unk0[D_807444FC].unk0->unk30;
                    *dst = (node->unk34 << 12) | 0xF2000000 | node->unk36;
                }
            }
            if (node->unk18[D_807444FC].unk0 != NULL) {
                node->unk18[D_807444FC].unk0->unk4 = sp60;
                if (sp5B == 0) {
                    dst = &node->unk18[D_807444FC].unk0->unk30;
                    *dst = (node->unk34 << 12) | 0xF2000000 | node->unk36;
                }
            }
            if (D_8076A064 != node->unk30) {
                node->unk34 += node->unk38;
                if (node->unk34 >= 0x1000) {
                    node->unk34 = 0;
                }
                if (node->unk34 < 0) {
                    node->unk34 = 0xFFF;
                }
                node->unk36 += node->unk3A;
                if (node->unk36 >= 0x1000) {
                    node->unk36 = 0;
                }
                if (node->unk36 < 0) {
                    node->unk36 = 0xFFF;
                }
            }
            if (sp5B != 0) {
                if (node->unk0[D_807444FC].unk4 != NULL) {
                    node->unk0[D_807444FC].unk4->unk4 = sp5C;
                }
                if (node->unk18[D_807444FC].unk4 != NULL) {
                    node->unk18[D_807444FC].unk4->unk4 = sp5C;
                }
                if (node->unk0[D_807444FC].unk8 != NULL) {
                    *node->unk0[D_807444FC].unk8 = sp58 + 0xFA000000;
                }
                if (node->unk18[D_807444FC].unk8 != NULL) {
                    *node->unk18[D_807444FC].unk8 = sp58 + 0xFA000000;
                }
            }
            node->unk30 = D_8076A064;
            node = node->unkD4;
        } while (node != NULL);
    }
}

void func_8066B0DC(void);

void func_80639C04(R36880eOwner *arg0, s32 arg1, s32 *arg2, s32 *arg3, u8 *arg4, s16 *arg5) {
    R36880eNode *node;
    s32 key;
    s32 found;

    node = arg0->unk50;
    if (node != NULL) {
        key = arg0->unk24[arg1];
        found = 0;
        if (node != NULL) {
            do {
                if (key == node->unk44) {
                    found = 1;
                } else {
                    node = node->unkD4;
                }
            } while (node != NULL && found == 0);
        }
        if (found != 0) {
            func_80639CD0(node, arg2, arg3, arg4, arg5);
            node->unk30 = D_8076A064;
            return;
        }
        *arg4 = 0;
        *arg2 = key;
        return;
    }
    *arg4 = 0;
    *arg2 = arg0->unk24[arg1];
}


s32 func_80639F1C(R36880eNode *, s32 *, s32 *);

void func_80639CD0(R36880eNode *arg0, s32 *arg1, s32 *arg2, u8 *arg3, s16 *arg4) {
    s32 var_v1;
    s32 sp30;
    s32 sp2C;
    s32 temp_a3;
    s32 temp_a0;

    if (D_8076A064 == arg0->unk30) {
        var_v1 = 0;
    } else {
        var_v1 = (u8)func_80639F1C(arg0, &sp30, &sp2C);
    }
    if (var_v1 != 0 || arg0->unk3C == 0) {
        temp_a3 = arg0->unk3C;
        if (arg0->unk4A != 0) {
            temp_a0 = arg0->unk40;
            if (temp_a0 == 0 || arg0->unk49 != 0) {
                if (temp_a3 != 0) {
                    assetFreeBuffer((void *)temp_a3, 0xFCB, 7);
                }
                if (arg0->unkD0 != 0) {
                    func_8066B0DC();
                }
                arg0->unk3C = (s32)func_8066B0F8(7, arg0->unk5C[sp30], 0, 0);
                temp_a0 = arg0->unk40;
                if (temp_a0 != 0) {
                    assetFreeBuffer((void *)temp_a0, 0xFCE, 7);
                }
                if (arg0->unkD0 != 0) {
                    func_8066B0DC();
                }
                arg0->unk40 = (s32)func_8066B0F8(7, arg0->unk5C[sp2C], 0, 0);
            } else {
                if (temp_a3 != 0) {
                    assetFreeBuffer((void *)temp_a3, 0xFD5, 7);
                }
                temp_a0 = arg0->unk40;
                arg0->unk3C = temp_a0;
                if (arg0->unkD0 != 0) {
                    func_8066B0DC();
                }
                arg0->unk40 = (s32)func_8066B0F8(7, arg0->unk5C[sp2C], 0, 0);
            }
        } else {
            if (temp_a3 != 0) {
                assetFreeBuffer((void *)temp_a3, 0xFDF, 7);
            }
            if (arg0->unkD0 != 0) {
                func_8066B0DC();
            }
            arg0->unk3C = (s32)func_8066B0F8(7, arg0->unk5C[sp30], 0, 0);
        }
    }
    arg0->unk49 = 0;
    *arg3 = arg0->unk4A;
    if (arg0->unk4A != 0) {
        *arg4 = (s16)(((f32)arg0->unk50 / (f32)arg0->unk4C) * 255.0f);
    }
    *arg1 = arg0->unk3C;
    *arg2 = arg0->unk40;
}

s32 func_80639F1C(R36880eNode *arg0, s32 *arg1, s32 *arg2) {
    s32 result;

    result = 0;
    switch (arg0->unk48) {
        case 1:
            arg0->unk50 += 1;
            if (arg0->unk50 == arg0->unk4C) {
                arg0->unk50 = 0;
                arg0->unk54 += 1;
                if (arg0->unk54 == arg0->unk58) {
                    arg0->unk54 = 0;
                }
                result = 1;
            }
            break;
        case 0:
            if (arg0->unk49 != 0) {
                result = 1;
            }
            break;
        default:
            break;
    }
    *arg1 = arg0->unk54;
    if (arg0->unk54 + 1 == arg0->unk58) {
        *arg2 = 0;
    } else {
        *arg2 = arg0->unk54 + 1U;
    }
    return result;
}

typedef struct R36880fNode {
    /* 0x00 */ u32 key;
    /* 0x04 */ u8 pad4[8];
    /* 0x0C */ s16 unkC;
    /* 0x0E */ s16 unkE;
    /* 0x10 */ s16 unk10;
    /* 0x12 */ s16 unk12;
    /* 0x14 */ f32 unk14;
    /* 0x18 */ f32 unk18;
    /* 0x1C */ f32 unk1C;
    /* 0x20 */ u8 pad20[4];
    /* 0x24 */ s16 unk24;
    /* 0x26 */ s16 unk26;
    /* 0x28 */ s16 unk28;
    /* 0x2A */ s16 unk2A;
    /* 0x2C */ s16 unk2C;
    /* 0x2E */ u8 unk2E;
    /* 0x2F */ u8 unk2F;
    /* 0x30 */ u8 pad30[4];
    /* 0x34 */ struct R36880fNode *next;
} R36880fNode;

s32 func_80611E60(s32);
f32 distance3D(f32, f32, f32, f32, f32, f32);
f32 mathAngleBetweenPointsRad(f32, f32, f32, f32);

void func_80639FC0(f32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 *arg6, f32 *arg7, f32 *arg8, u8 arg9) {
    f32 len;
    s16 angle;
    f32 dx;
    f32 dz;
    s32 pad1;
    s32 pad2;
    s32 pad3;
    s16 angle2;
    s32 t;

    if (arg9 == 0) {
        dx = arg3 - arg0;
        dz = arg5 - arg2;
        len = sqrtf(dx * dx + dz * dz);
        if ((f64)len < 1.0) {
            len = 1.0f;
        }
        if (arg0 <= arg3 && arg2 <= arg5) {
            angle = (s16)(func_80611E60((s32)(((f64)dx * 65535.9) / (f64)len)) >> 4);
        }
        if (arg0 <= arg3 && arg5 < arg2) {
            angle = (s16)((func_80611E60((s32)(((f64)(arg2 - arg5) * 65535.9) / (f64)len)) >> 4) + 0x400);
        }
        if (arg3 < arg0 && arg5 < arg2) {
            angle = (s16)((func_80611E60((s32)(((f64)(arg0 - arg3) * 65535.9) / (f64)len)) >> 4) + 0x800);
        }
        if (arg3 < arg0 && arg2 <= arg5) {
            angle = (s16)((func_80611E60((s32)(((f64)dz * 65535.9) / (f64)len)) >> 4) + 0xC00);
        }
        *arg8 = 0.0f;
        *arg6 = 0.0f;
        *arg7 = (f32)(((f64)angle / 4095.0) * 360.0);
    } else {
        len = distance3D(arg3, arg4, arg5, arg0, arg1, arg2);
        if ((f64)len < 0.1) {
            len = 1.0f;
        }
        dz = (arg4 - arg1) / len;
        if (dz > 0.0f) {
            dx = dz;
        } else {
            dx = -dz;
        }
        t = func_80611E60((s32)(f32)(s32)((f64)dx * 65536.0)) >> 4;
        angle2 = t;
        if (dz >= 0.0f) {
            angle2 = 0xFFF - angle2;
        }
        *arg6 = (f32)(((f64)angle2 / 4095.0) * 360.0);
        *arg7 = mathAngleBetweenPointsRad(arg3, arg5, arg0, arg2) * 57.295776f;
        *arg8 = 0.0f;
    }
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/36880/func_8063A38C.s")

R36880fNode *func_8063A848(R36880fNode *head, R36880fNode *node) {
    R36880fNode *prev;
    R36880fNode *ret;
    s32 inserted;

    prev = NULL;
    ret = head;
    inserted = 0;
    if (head != NULL) {
        do {
            if (head->key >= node->key) {
                inserted = 1;
                node->next = head;
                if (prev != NULL) {
                    prev->next = node;
                } else {
                    ret = node;
                }
            }
            prev = head;
            if (inserted == 0) {
                head = head->next;
            }
        } while (head != NULL && inserted == 0);
    }
    if (inserted == 0) {
        if (prev == NULL) {
            ret = node;
        } else {
            prev->next = node;
        }
    }
    return ret;
}

void func_8063A8C4(s16 arg0, u8 arg1, f32 arg2) {
    u8 *obj;
    f32 *p;

    if (arg1 == 1) {
        arg0 = hashTableLookup(arg0);
    }
    obj = D_807F6000[arg0].unk20;
    switch (D_807F6000[arg0].unk86) {
    case 2:
        p = *(f32 **)(obj + 0x54);
        break;
    case 1:
        p = *(f32 **)(obj + 0xBC);
        break;
    }
    if (p != NULL) {
        p[1] = arg2;
    }
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/36880/func_8063A968.s")

extern s16 D_807F6028;
extern s16 D_807F60A8;
extern u8 D_807F6938;

void func_8063B4A4(void) {
    D_807F6028 = 0;
    D_807F60A8 = 0;
    D_807F6938 = 0;
}

typedef struct R36880fEntry {
    /* 0x0 */ s16 id;
    /* 0x2 */ s16 key;
    /* 0x4 */ u8 done;
    /* 0x5 */ u8 pad5;
} R36880fEntry;

extern R36880fEntry D_807F6030[];
extern s16 D_807F60B0[];
void func_8063E078(s32);
void func_8063E0D4(s32, s16);

#pragma GLOBAL_ASM("asm/global/nonmatchings/36880/func_8063B4C0.s")

void func_8063B758(void) {
    u8 found;
    s32 i;
    s32 slot;
    s32 obj;
    u8 any;
    s32 j;

    do {
        any = 0;
        for (i = 0; i < D_807F6028; i++) {
            if (D_807F6030[i].done == 0) {
                found = 0;
                for (j = 0; found == 0 && j < D_807F60A8; j++) {
                    if (D_807F60B0[j] == D_807F6030[i].key) {
                        found = 1;
                        any = 1;
                        D_807F6030[i].done = 1;
                        slot = hashTableLookup(D_807F6030[i].id);
                        obj = (s32)D_807F6000[slot].unk7C;
                        if (D_807F60A8 == 0x46) {
                            return;
                        }
                        D_807F60B0[D_807F60A8] = *(s16 *)((u8 *)D_807F6000 + slot * 0x90 + 0x8A);
                        D_807F60A8++;
                        func_8063E078(obj);
                        func_8063E0D4(obj, D_807F6030[i].id);
                    }
                }
            }
        }
    } while (any == 1);
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/36880/func_8063B8D8.s")

typedef struct R36880gSlot {
    /* 0x00 */ u8 pad0[0x24];
    /* 0x24 */ u8 *unk24;
    /* 0x28 */ u8 pad28[0x50];
    /* 0x78 */ u8 **unk78;
    /* 0x7C */ u8 *unk7C;
    /* 0x80 */ u8 pad80[8];
    /* 0x88 */ s16 unk88;
    /* 0x8A */ s16 unk8A;
    /* 0x8C */ u8 pad8C[4];
} R36880gSlot; /* 0x90 */

u32 modelSlotDataSize(s16);
void func_80634D14(s32, s16, s16 *, s16 *);
void func_80634EDC(s32, s16, u8 *);
void func_8062B8E4(f32 *);
void effectNodeCopyValues(f32 *);

#define R36880G_SLOT(i) ((R36880gSlot *)((u8 *)D_807F6000 + (i) * 0x90))

void func_8063BBB0(u8 **arg0, s32 *arg1) {
    s32 count = 0;
    s32 i;
    s32 pad;
    u8 *buf = NULL;
    u8 *rec;
    u8 *cur;
    s32 size = 0;
    u8 *p;
    s32 j;

    for (i = 0; i < D_80747D70; i++) {
        if (R36880G_SLOT(i)->unk7C != NULL) {
            if ((R36880G_SLOT(i)->unk24[0x3A] != 0 || (R36880G_SLOT(i)->unk7C[0x9B] & 1)) && !(R36880G_SLOT(i)->unk7C[0x9B] & 2)) {
                count++;
                if (R36880G_SLOT(i)->unk78 != NULL) {
                    size += modelSlotDataSize(i);
                }
            }
        }
    }
    if (count != 0) {
        buf = func_80610FE8(count * 0x254 + size);
        cur = buf;
        for (i = 0; i < D_80747D70; i++) {
            if (R36880G_SLOT(i)->unk7C != NULL) {
                if ((R36880G_SLOT(i)->unk24[0x3A] != 0 || (R36880G_SLOT(i)->unk7C[0x9B] & 1)) && !(R36880G_SLOT(i)->unk7C[0x9B] & 2)) {
                    rec = cur;
                    p = cur;
                    *(s16 *)p = R36880G_SLOT(i)->unk8A;
                    memcpy(p + 0xCC, R36880G_SLOT(i)->unk7C, 0x9C);
                    if (R36880G_SLOT(i)->unk78 != NULL) {
                        memcpy(p + 4, (u8 *)R36880G_SLOT(i)->unk78 + 8, 0xC8);
                        cur[0x250] = modelSlotDataSize(i) >> 6;
                        memcpy(p + 0x254, *R36880G_SLOT(i)->unk78, modelSlotDataSize(i));
                    } else {
                        cur[0x250] = 0;
                    }
                    for (j = 1; j != 5; j++) {
                        func_80634D14(R36880G_SLOT(i)->unk88, j, (s16 *)(p + 0x232 + j * 6), (s16 *)(p + 0x234 + j * 6));
                        func_80634EDC(R36880G_SLOT(i)->unk88, j, p + 0x236 + j * 6);
                    }
                    func_8062B8E4((f32 *)(p + 0x168));
                    effectNodeCopyValues((f32 *)(p + 0x1B8));
                    cur += rec[0x250] * 0x40;
                    cur += 0x254;
                }
            }
        }
    }
    *arg1 = count;
    *arg0 = buf;
}

void func_8063BEC0(u8 *arg0, s32 arg1, s16 arg2, s16 arg3) {
    s32 found = 0;
    s32 i = 0;

    if (arg1 > 0) {
        do {
            if (*(s16 *)arg0 == arg2) {
                found = 1;
            } else {
                i++;
                arg0 += 0x254 + arg0[0x250] * 0x40;
            }
        } while (found == 0 && i < arg1);
    }
    if (found != 0) {
        arg0[0x117] = arg3;
        arg0[0x120] = 1;
    }
}

typedef struct R36880gSnap {
    /* 0x00 */ u32 unk0;
    /* 0x04 */ u8 pad4[0xC];
    /* 0x10 */ s16 unk10;
    /* 0x12 */ s16 unk12;
    /* 0x14 */ u8 pad14[0x80];
    /* 0x94 */ u32 unk94;
    /* 0x98 */ u8 pad98[4];
} R36880gSnap; /* 0x9C */

void func_8062BA0C(f32 *);
void effectNodeSetValues(f32 *);

void func_8063BF34(u8 *arg0, s32 arg1) {
    s32 k;
    s32 off;
    s32 j;
    s16 id;
    s16 idx;
    u8 tmp[0x14];
    R36880gSnap snap;
    s32 pad[2];

    for (k = 0; k < arg1; k++) {
        id = D_807F6240[*(s16 *)arg0];
        idx = hashTableLookup(id);
        memcpy(&snap, R36880G_SLOT(idx)->unk7C, 0x9C);
        memcpy(R36880G_SLOT(idx)->unk7C, arg0 + 0xCC, 0x9C);
        *(u32 *)R36880G_SLOT(idx)->unk7C = snap.unk0;
        *(s16 *)(R36880G_SLOT(idx)->unk7C + 0x10) = snap.unk10;
        *(s16 *)(R36880G_SLOT(idx)->unk7C + 0x12) = snap.unk12;
        *(u32 *)(R36880G_SLOT(idx)->unk7C + 0x94) = snap.unk94;
        R36880G_SLOT(idx)->unk7C[0x48] = R36880G_SLOT(idx)->unk7C[0x4B];
        R36880G_SLOT(idx)->unk7C[0x49] = R36880G_SLOT(idx)->unk7C[0x4C];
        R36880G_SLOT(idx)->unk7C[0x4A] = R36880G_SLOT(idx)->unk7C[0x4D];
        R36880G_SLOT(idx)->unk7C[0x9A] = 0;
        *(s32 *)(R36880G_SLOT(idx)->unk7C + 0x38) = -1;
        if (R36880G_SLOT(idx)->unk78 != NULL) {
            for (off = 0; off != 0xC8; off += 0x14) {
                memcpy(tmp, (u8 *)R36880G_SLOT(idx)->unk78 + off + 8, 0x14);
                memcpy((u8 *)R36880G_SLOT(idx)->unk78 + off + 8, arg0 + 4 + off, 0x14);
                *(u32 *)((u8 *)R36880G_SLOT(idx)->unk78 + off + 8) = *(u32 *)tmp;
            }
            modelSlotCopyData(arg0 + 0x254, idx);
        }
        for (j = 1; j != 5; j++) {
            func_80634CC8(id, j, *(s16 *)(arg0 + 0x232 + j * 6), *(s16 *)(arg0 + 0x234 + j * 6));
            func_80634EA4(id, j, arg0[0x236 + j * 6]);
        }
        func_8062BA0C((f32 *)(arg0 + 0x168));
        effectNodeSetValues((f32 *)(arg0 + 0x1B8));
        arg0 += arg0[0x250] * 0x40;
        arg0 += 0x254;
    }
}

void func_8063C1EC(s32 arg0, u8 arg1) {
    ((u8 *)D_807F6000[hashTableLookup(D_807F6240[arg0])].unk20)[0x4E] |= arg1;
}

void func_8063C248(s32 arg0, u8 arg1) {
    ((u8 *)D_807F6000[hashTableLookup(D_807F6240[arg0])].unk20)[0x4E] &= ~arg1;
}

typedef struct R36880gSub {
    /* 0x00 */ u8 pad0[0x60];
    /* 0x60 */ u8 unk60;
    /* 0x61 */ u8 pad61[3];
    /* 0x64 */ s16 unk64;
} R36880gSub;

s32 func_8063C2A8(s16 arg0) {
    s16 idx = hashTableLookup(arg0);
    R36880gSub *sub = D_807F6000[idx].unk7C;

    if (sub != 0) {
        if (sub->unk60 == 1 && sub->unk64 == 0) {
            return 0;
        }
        return 1;
    }
    return 1;
}

s16 func_8063C328(s16 arg0) {
    s16 idx = hashTableLookup(arg0);

    if (idx == -1) {
        return -1;
    }
    return D_807F6000[idx].unk84;
}

