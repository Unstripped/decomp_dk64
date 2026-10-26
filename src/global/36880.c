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
s16 func_80632860(s32, s32, f32, f32, f32, f32, f32, f32, f32, f32, s32, s32, s32 *);
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
    s32 found;

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

#pragma GLOBAL_ASM("asm/global/nonmatchings/36880/func_80632860.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/36880/func_80632E10.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/36880/func_80632E74.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/36880/func_80632F20.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/36880/func_80632F74.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/36880/func_80632FCC.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/36880/func_806330C4.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/36880/func_806333F8.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/36880/func_80633570.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/36880/func_806335B0.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/36880/func_8063367C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/36880/func_8063373C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/36880/func_806338B4.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/36880/func_806338F4.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/36880/func_8063393C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/36880/func_80633A1C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/36880/func_80633D30.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/36880/func_80633DC0.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/36880/func_80634768.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/36880/func_806348B4.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/36880/func_80634908.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/36880/func_8063495C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/36880/func_806349FC.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/36880/func_80634CC8.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/36880/func_80634D14.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/36880/func_80634D64.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/36880/func_80634E10.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/36880/func_80634EA4.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/36880/func_80634EDC.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/36880/func_80634F14.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/36880/func_80634FA0.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/36880/func_80635018.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/36880/func_80635098.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/36880/func_80635114.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/36880/func_80635214.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/36880/func_8063524C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/36880/func_80635468.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/36880/func_80635548.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/36880/func_80635588.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/36880/func_806355DC.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/36880/func_806357F8.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/36880/func_806358E8.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/36880/func_80635EF0.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/36880/func_80636014.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/36880/func_80636074.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/36880/func_80636164.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/36880/func_80636210.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/36880/func_806362C4.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/36880/func_80636380.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/36880/func_8063643C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/36880/func_80636448.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/36880/func_806364C4.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/36880/func_806365D0.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/36880/func_80636784.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/36880/func_806368F0.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/36880/func_80636A44.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/36880/func_80636A8C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/36880/func_80636AE8.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/36880/func_80636B50.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/36880/func_80636C00.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/36880/func_80636D38.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/36880/func_80636EFC.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/36880/func_80636FFC.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/36880/func_80637B6C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/36880/func_806392BC.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/36880/func_806398E4.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/36880/func_80639968.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/36880/func_80639C04.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/36880/func_80639CD0.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/36880/func_80639F1C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/36880/func_80639FC0.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/36880/func_8063A38C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/36880/func_8063A848.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/36880/func_8063A8C4.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/36880/func_8063A968.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/36880/func_8063B4A4.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/36880/func_8063B4C0.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/36880/func_8063B758.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/36880/func_8063B8D8.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/36880/func_8063BBB0.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/36880/func_8063BEC0.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/36880/func_8063BF34.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/36880/func_8063C1EC.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/36880/func_8063C248.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/36880/func_8063C2A8.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/36880/func_8063C328.s")
