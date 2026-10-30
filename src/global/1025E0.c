#include "common.h"
#include "actor.h"

extern Actor *D_807FBB40;
extern Actor *D_807FBB44;
extern Actor *D_807FBB48;
extern Actor *D_807FBB4C;
extern void *D_807FC924;
extern u8 D_807FC928;
extern u8 D_807FC929;
extern u8 D_807FC950[][0x5E];
extern s32 D_8076A0A8;
extern u8 D_8076A0AB;
extern u8 D_8076A0B1;
extern s16 D_80744490;
extern s16 D_80744494;
extern u8 D_807444F8;
extern u8 D_807444FC;

extern s32 textGetStringWidth(s16, s32);
void textDrawStringVtx(s32, s16, s16, s16, s32, u8);

void textDrawStringCentered(s32 arg0, s16 arg1, s32 arg2, s16 arg3, u8 arg4) {
    s16 width;
    s16 height;

    width = (D_80744490 - textGetStringWidth(arg1, arg2)) * 2;
    height = arg3 * 4;
    textDrawStringVtx(arg0, arg1, width, height, arg2, arg4);
}

void func_806FD950(s32 arg0, s16 arg1, s32 arg2, s16 arg3) {
    textDrawStringVtx(arg0, arg1, 0x60, (s16)(arg3 * 4), arg2, 1);
}

typedef struct GfxResourceEntry {
    f32 unk0;
    f32 unk4;
    f32 unk8;
    f32 unkC;
    f32 unk10;
    f32 unk14;
    f32 unk18;
    f32 unk1C;
    f32 unk20;
    f32 unk24;
    f32 unk28;
    f32 unk2C;
    f32 unk30;
    f32 unk34;
} GfxResourceEntry;

typedef struct GfxResourceNode {
    struct GfxResourceNode *next;
    void *unk4;
    GfxResourceEntry *unk8;
    s8 unkC;
    u8 unkD;
    u8 unkE[6];
    f32 unk14;
    f32 unk18;
    s16 unk1C;
} GfxResourceNode;

extern GfxResourceNode *gGfxResourceList;
extern s16 gGfxResourceNextId;

void gfxResourceListReset(void) {
    gGfxResourceList = NULL;
    gGfxResourceNextId = 0;
}

GfxResourceNode *gfxResourceFindById(s16 arg0) {
    GfxResourceNode *var_v1;

    var_v1 = gGfxResourceList;
    if ((var_v1 != NULL) && (arg0 != var_v1->unk1C)) {
loop_2:
        var_v1 = var_v1->next;
        if ((var_v1 != NULL) && (arg0 != var_v1->unk1C)) {
            goto loop_2;
        }
    }
    return var_v1;
}

GfxResourceEntry *gfxResourceCopyEntry(GfxResourceEntry *arg0, s16 arg1, s16 arg2) {
    *arg0 = gfxResourceFindById(arg1)->unk8[arg2];
    return arg0;
}

f32 func_806FDA8C(s16 arg0) {
    return gfxResourceFindById(arg0)->unk18;
}

void func_806FDAB8(s16 arg0, f32 arg1) {
    gfxResourceFindById(arg0)->unk18 = arg1;
}

void heapFree(void *);

void gfxResourceFree(s16 arg0) {
    GfxResourceNode *var_a1;
    GfxResourceNode *var_v0;

    var_a1 = gGfxResourceList;
    var_v0 = NULL;
    if ((var_a1 != NULL) && (arg0 != var_a1->unk1C)) {
loop_2:
        var_v0 = var_a1;
        var_a1 = var_a1->next;
        if ((var_a1 != NULL) && (arg0 != var_a1->unk1C)) {
            goto loop_2;
        }
    }
    if (var_v0 != NULL) {
        var_v0->next = var_a1->next;
    } else {
        gGfxResourceList = var_a1->next;
    }
    heapFree(var_a1->unk4);
    heapFree(var_a1->unk8);
    heapFree(var_a1);
}

void _strcpy(s32, s32);
extern u8 D_8074450C;
s32 randomNonNegative();
s32 strlen(char *);
void *heapAlloc(s32);
void heapClearBlock(void *);
s16 textCountNonSpace(char *);

s16 gfxResourceCreate(s16 arg0, char *arg1, u8 arg2, f32 arg3, f32 arg4, f32 arg5) {
    GfxResourceNode *node;
    GfxResourceNode *tail;
    GfxResourceEntry *entries;
    void *name;
    u8 count;
    s16 i;

    textGetStringWidth(arg0, (s32)arg1);
    node = heapAlloc(0x20);
    heapClearBlock(node);
    if (gGfxResourceList == NULL) {
        gGfxResourceList = node;
        node->next = NULL;
        gGfxResourceNextId = 0;
    } else {
        tail = gGfxResourceList;
        while (tail->next != NULL) {
            tail = tail->next;
        }
        tail->next = node;
        node->next = NULL;
    }
    node->unk1C = (s16)(gGfxResourceNextId & 0xFFFF);
    gGfxResourceNextId++;
    if (gGfxResourceNextId && gGfxResourceNextId) {
    }
    name = heapAlloc(strlen(arg1) + 1);
    node->unk4 = name;
    _strcpy((s32)name, (s32)arg1);
    count = textCountNonSpace(arg1);
    node->unkD = count;
    entries = heapAlloc(count * sizeof(GfxResourceEntry));
    node->unk8 = entries;
    heapClearBlock(entries);
    node->unkC = arg0;
    i = 0;
    if (node->unkD > 0) {
        do {
            if (arg2 == 3) {
                node->unk8[i].unk0 = (randomNonNegative() >> 15) % 1440 - 0x50;
                node->unk8[i].unk4 = (randomNonNegative() >> 15) % 1120 - 0x50;
                node->unk8[i].unk20 = (randomNonNegative() >> 15) % 6283 / 1000.0;
                node->unk14 = 0.1f;
            } else {
                node->unk8[i].unk0 = arg3 * 4.0f;
                node->unk8[i].unk4 = arg4 * 4.0f;
                node->unk8[i].unk8 = arg5 * 4.0f;
                node->unk8[i].unk30 = (D_8074450C == 2) ? 1.0 : 0.1;
                node->unk14 = 0.2f;
            }
            i++;
        } while (i < node->unkD);
    }
    return node->unk1C;
}

void gfxResourceSetString(s16 arg0, s32 arg1) {
    _strcpy((s32)gfxResourceFindById(arg0)->unk4, arg1);
}

s16 func_806CC190(s16, s16, f32);

void func_806FDF54(f32 *arg0, f32 *arg1) {
    if (*arg1 < 0.0f) {
        do {
            *arg1 += 6.2831855f;
        } while (*arg1 < 0.0f);
    }
    if (*arg1 >= 6.2831855f) {
        do {
            *arg1 -= 6.2831855f;
        } while (*arg1 >= 6.2831855f);
    }
    *arg0 = (f32)((f64)((f32)func_806CC190((s16)(s32)(((f64)*arg0 * 2048.0) / 3.1415927410125732), (s16)(s32)(((f64)*arg1 * 2048.0) / 3.1415927410125732), 5.0f) * 3.1415927410125732f) * 0.00048828125);
}

typedef struct GfxResourceNodeView {
    struct GfxResourceNodeView *next;
    u8 *unk4;
    GfxResourceEntry *unk8;
    u8 unkC;
    u8 unkD;
    u8 padE[2];
    f32 unk10;
    f32 unk14;
    f32 unk18;
    s16 unk1C;
} GfxResourceNodeView;

extern u8 D_80754A37[];
extern s32 func_805FCA64();
extern s16 textGetCharAdvance(s16, s32);
extern Gfx *textObjectDrawFlat(Gfx *, GfxResourceNodeView *);
extern Gfx *textObjectDrawRotated(Gfx *, GfxResourceNodeView *);
f32 sinApprox(f32);
f32 cosApprox(f32);

Gfx *textDrawAnimated(Gfx *arg0, s16 arg1, s32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6) {
    GfxResourceNodeView *node;
    f32 var_fs2;
    f32 var_fs3;
    f32 var_fs4;
    f32 sp7C;
    s16 var_s3;
    s16 var_s5;
    s32 var_s6;
    f32 sp70;
    s32 var_s7;
    s32 var_a1;

    var_s5 = 0;
    var_fs3 = arg3;
    node = (GfxResourceNodeView *)gfxResourceFindById(arg1);
    var_s3 = 0;
    var_fs4 = ((f32)D_80744490 - ((f32)textGetStringWidth(node->unkC, (s32)node->unk4) * arg6)) / 2 + -3;
    sp7C = (f32)(D_80744490 >> 3);
    var_fs2 = node->unk10;
    sp70 = 6.2831855f / (f32)node->unkD;
    var_s6 = 1;
    var_s7 = 1;
    var_s5 = 1;
    var_a1 = node->unk4[0];
    while (var_a1 != 0) {
        if (var_a1 != 0x20) {
            u32 glyph;
            u8 temp_a1;
            u8 temp_s1;
            s32 temp_a2;
            u8 temp_a0;

            glyph = textGetCharAdvance(node->unkC, var_a1) * arg6;
            temp_a1 = glyph;
            temp_s1 = glyph;
            temp_a2 = temp_a1 / 2;
            temp_a0 = temp_a2;
            switch (arg2) {
                case 8:
                    node->unk8[var_s3].unkC = ((f32)temp_a0 + var_fs3) * 4.0f;
                    node->unk8[var_s3].unk10 = arg4 * 4.0f;
                    var_fs3 += (f32)temp_s1;
                    node->unk8[var_s3].unk34 = (f32)((f64)sinApprox(node->unk18) * 0.5 + arg6);
                    if (node->unk18 > 0.0f) {
                        node->unk18 = (f32)((f64)node->unk18 - 0.1);
                    } else {
                        node->unk18 = 0.0f;
                    }
                    break;
                case 6:
                    var_s6 = 0;
                    var_s7 = 0;
                    node->unk8[var_s3].unk0 = (var_fs3 + 20.0f) * 4.0f;
                    node->unk8[var_s3].unk4 = arg4 * 4.0f;
                    var_fs3 += 28.0f;
                    node->unk8[var_s3].unk20 = (f32)((f64)sinApprox(node->unk18) * 0.35);
                    node->unk8[var_s3].unk30 = 1.5f;
                    break;
                case 5:
                    var_s6 = 0;
                    var_s7 = 0;
                    node->unk8[var_s3].unk0 = ((f32)temp_a0 + var_fs4) * 4.0f;
                    node->unk8[var_s3].unk4 = arg4 * 4.0f;
                    var_fs4 += (f32)temp_s1;
                    node->unk8[var_s3].unk20 = 0.0f;
                    node->unk8[var_s3].unk30 = (f32)((f64)sinApprox(var_fs2) * 0.05 + 1.0);
                    var_fs2 += sp70;
                    node->unk10 = (f32)((f64)node->unk10 + 0.1);
                    break;
                case 4:
                    node->unk8[var_s3].unkC = ((f32)(u8)temp_a2 + var_fs4) * 4.0f;
                    node->unk8[var_s3].unk10 = arg4 * 4.0f;
                    var_fs4 += (f32)temp_a1;
                    node->unk8[var_s3].unk34 = 1.0f;
                    break;
                case 3:
                    node->unk8[var_s3].unkC = ((f32)temp_a0 + var_fs4) * 4.0f;
                    node->unk8[var_s3].unk10 = arg4 * 4.0f;
                    var_fs4 += (f32)temp_s1;
                    node->unk8[var_s3].unk2C = 0.0f;
                    node->unk8[var_s3].unk34 = (f32)((f64)sinApprox(var_fs2) * 0.3 + 1.2);
                    var_fs2 += sp70;
                    node->unk10 = (f32)((f64)node->unk10 + 0.04);
                    break;
                case 1:
                    var_fs2 -= (f32)temp_a0 * 0.013f;
                    node->unk8[var_s3].unkC = (sinApprox(var_fs2) * sp7C + var_fs3) * 4.0f;
                    node->unk8[var_s3].unk10 = (cosApprox(var_fs2) * sp7C + arg4) * 4.0f;
                    node->unk8[var_s3].unk2C = 3.1415927f - var_fs2;
                    var_fs2 -= (f32)temp_s1 * 0.013f;
                    break;
                case 2:
                    node->unk8[var_s3].unkC = ((f32)temp_a0 + var_fs4) * 4.0f;
                    node->unk8[var_s3].unk10 = (f32)(((f64)sinApprox(var_fs2 * 2) * 5.0 + arg4) * 4.0);
                    var_fs4 += (f32)temp_s1;
                    var_fs2 += sp70;
                    node->unk8[var_s3].unk20 = (f32)((f64)sinApprox(var_fs2 * 2) * 0.5);
                    node->unk10 = (f32)((f64)node->unk10 - 0.01);
                    node->unk8[var_s3].unk34 = arg6;
                    break;
                case 9:
                    node->unk8[var_s3].unkC = var_fs3 - (f32)(temp_a0 * 4);
                    node->unk8[var_s3].unk10 = arg4;
                    node->unk8[var_s3].unk14 = arg5;
                    var_fs3 -= (f32)(temp_s1 * 4);
                    var_fs2 += sp70;
                    node->unk8[var_s3].unk34 = (f32)((f64)sinApprox(var_fs2) * (0.2 * arg6) + arg6);
                    node->unk8[var_s3].unk2C = 3.1415927f;
                    node->unk10 = (f32)((f64)node->unk10 - 0.08);
                    break;
                case 10:
                    node->unk8[var_s3].unkC = var_fs3;
                    node->unk8[var_s3].unk10 = arg4;
                    node->unk8[var_s3].unk14 = (f32)temp_s1 + arg5;
                    arg5 += (f32)(temp_s1 * 4);
                    var_fs2 += sp70;
                    node->unk8[var_s3].unk34 = (f32)((f64)sinApprox(var_fs2) * (0.2 * arg6) + arg6);
                    node->unk8[var_s3].unk24 = 1.5707964f;
                    node->unk8[var_s3].unk28 = -1.5707964f;
                    node->unk8[var_s3].unk2C = 0.0f;
                    node->unk10 = (f32)((f64)node->unk10 - 0.08);
                    break;
            }
            if (var_s6 != 0) {
                node->unk8[var_s3].unk0 = node->unk8[var_s3].unk0 + (node->unk8[var_s3].unkC - node->unk8[var_s3].unk0) * node->unk14;
                node->unk8[var_s3].unk4 = node->unk8[var_s3].unk4 + (node->unk8[var_s3].unk10 - node->unk8[var_s3].unk4) * node->unk14;
                node->unk8[var_s3].unk8 = node->unk8[var_s3].unk8 + (node->unk8[var_s3].unk14 - node->unk8[var_s3].unk8) * node->unk14;
                func_806FDF54(&node->unk8[var_s3].unk18, &node->unk8[var_s3].unk24);
                func_806FDF54(&node->unk8[var_s3].unk1C, &node->unk8[var_s3].unk28);
                func_806FDF54(&node->unk8[var_s3].unk20, &node->unk8[var_s3].unk2C);
            }
            if (var_s7 != 0) {
                node->unk8[var_s3].unk30 = node->unk8[var_s3].unk30 + (node->unk8[var_s3].unk34 - node->unk8[var_s3].unk30) * node->unk14;
            }
            var_s3 += 1;
        } else {
            switch (arg2) {
                case 1:
                    var_fs2 -= (f32)D_80754A37[node->unkC * 6] * 0.013f;
                    break;
                case 2:
                case 3:
                case 4:
                case 5:
                case 8:
                    var_fs4 += (f32)D_80754A37[node->unkC * 6];
                    break;
                case 6:
                    var_fs3 += 32.0f;
                    break;
                case 10:
                    arg5 += (f32)D_80754A37[node->unkC * 6];
                    break;
                default:
                    var_fs3 += (f32)D_80754A37[node->unkC * 6];
                    break;
            }
            var_fs2 = (f32)((f64)var_fs2 - (f64)D_80754A37[node->unkC * 6] * 0.019);
        }
        if (var_fs2 < 0.0f) { var_fs2 += 6.2831855f; } var_a1 = *(u8 *)(var_s5 + node->unk4); var_s5 += 1;
    }
    gDPPipeSync(arg0++);
    gSPSetOtherMode(arg0++, G_SETOTHERMODE_L, G_MDSFT_RENDERMODE, 29, 0x00504240);
    switch (arg2) {
        case 9:
        case 10:
            return textObjectDrawRotated(arg0, node);
        case 0xFF:
            node->unk10 = (f32)((f64)node->unk10 + 0.04);
            return textObjectDrawRotated(arg0, node);
        case 8:
            if (func_805FCA64() == 0) {
                return arg0;
            }
            break;
        case 1:
            node->unk10 = (f32)((f64)node->unk10 + 0.02);
            break;
    }
    node->unk10 = (f32)((f64)node->unk10 + 0.04);
    return textObjectDrawFlat(arg0, node);
}
