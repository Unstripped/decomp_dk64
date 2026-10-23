// func_80662B90 (src/global/67890.c): 284/300 insns: prologue/epilogue/setup match; loop has quad-vertex indexing and centroid calculations
#include "common.h"
#include "actor.h"

typedef struct R2G67890_Entry40 {
    f32 unk0[8];
    s16 unk20;
    s16 unk22;
    s16 unk24;
    s16 unk26;
    s16 unk28;
    s16 unk2A;
    s16 unk2C;
    s16 unk2E;
    s16 unk30;
    s16 unk32;
    s16 unk34;
    s16 unk36;
    s16 unk38;
    s16 unk3A;
    s16 unk3C;
    u8 unk3E;
    u8 unk3F;
} R2G67890_Entry40;

typedef struct R2G67890_Entry14 {
    f32 unk0;
    f32 unk4;
    f32 unk8;
    f32 unkC;
    u8 unk10;
    u8 unk11;
    s8 unk12;
    s8 unk13;
} R2G67890_Entry14;

typedef struct R2G67890_Vtx {
    s16 ob[3];
    s16 flag;
    s16 tc[2];
    u8 cn[4];
} R2G67890_Vtx;

extern R2G67890_Entry40 *D_807F93F0;
extern R2G67890_Entry14 *D_807F93F4;
extern s32 D_807F93F8;
extern R2G67890_Vtx *D_807F93FC;
extern s32 D_807F9400;

void *func_80610FE8(s32);
s32 func_8066B0F8(s32, s32, s32, s32);
#define E(i) ((R2G67890_Entry40 *)((u8 *)D_807F93F0 + ((i) << 6)))
#define V(off) ((R2G67890_Vtx *)((u8 *)D_807F93FC + (off)))

void func_80662B90(void *arg0) {
    s32 count;
    s32 sp[3];
    s32 i;
    s32 vtx_off;
    s32 entry_off;
    s32 entry14_off;

    sp[0] = 0;
    count = *(s32 *)((u8 *)arg0 + *(s32 *)((u8 *)arg0 + 0x50));
    D_807F93F8 = count;
    if (count != 0) {
        D_807F93F0 = (R2G67890_Entry40 *)((u8 *)arg0 + *(s32 *)((u8 *)arg0 + 0x50) + 4);
        D_807F93F4 = func_80610FE8(count * sizeof(R2G67890_Entry14));
        D_807F93FC = func_80610FE8(D_807F93F8 << 6);
        if (D_807F93F8 > 0) {
            vtx_off = sp[0] * 0x10;
            entry14_off = 0;
            entry_off = 0;
            i = 0;
            do {
                V(vtx_off)->ob[0] = E(i)->unk20;
                V(vtx_off)->ob[1] = E(i)->unk28;
                V(vtx_off)->ob[2] = E(i)->unk30;
                V(vtx_off)->tc[0] = (s16)((s32)(E(i)->unk0[0] * 50.0f) << 5);
                V(vtx_off)->tc[1] = (s16)((s32)(E(i)->unk0[1] * 50.0f) << 5);
                vtx_off += 0x10;

                V(vtx_off)->ob[0] = E(i)->unk22;
                V(vtx_off)->ob[1] = E(i)->unk2A;
                V(vtx_off)->ob[2] = E(i)->unk32;
                V(vtx_off)->tc[0] = (s16)((s32)(E(i)->unk0[2] * 50.0f) << 5);
                V(vtx_off)->tc[1] = (s16)((s32)(E(i)->unk0[3] * 50.0f) << 5);
                vtx_off += 0x10;

                V(vtx_off)->ob[0] = E(i)->unk24;
                V(vtx_off)->ob[1] = E(i)->unk2C;
                V(vtx_off)->ob[2] = E(i)->unk34;
                V(vtx_off)->tc[0] = (s16)((s32)(E(i)->unk0[4] * 50.0f) << 5);
                V(vtx_off)->tc[1] = (s16)((s32)(E(i)->unk0[5] * 50.0f) << 5);
                vtx_off += 0x10;

                V(vtx_off)->ob[0] = E(i)->unk26;
                V(vtx_off)->ob[1] = E(i)->unk2E;
                V(vtx_off)->ob[2] = E(i)->unk36;
                V(vtx_off)->tc[0] = (s16)((s32)(E(i)->unk0[6] * 50.0f) << 5);
                V(vtx_off)->tc[1] = (s16)((s32)(E(i)->unk0[7] * 50.0f) << 5);
                vtx_off += 0x10;

                ((R2G67890_Entry14 *)((u8 *)D_807F93F4 + entry14_off))->unk4 = (f32)((f64)(((R2G67890_Entry40 *)((u8 *)D_807F93F0 + entry_off))->unk26 + ((R2G67890_Entry40 *)((u8 *)D_807F93F0 + entry_off))->unk20 + ((R2G67890_Entry40 *)((u8 *)D_807F93F0 + entry_off))->unk22 + ((R2G67890_Entry40 *)((u8 *)D_807F93F0 + entry_off))->unk24) * 0.25);
                ((R2G67890_Entry14 *)((u8 *)D_807F93F4 + entry14_off))->unk8 = (f32)((f64)(((R2G67890_Entry40 *)((u8 *)D_807F93F0 + entry_off))->unk2E + ((R2G67890_Entry40 *)((u8 *)D_807F93F0 + entry_off))->unk28 + ((R2G67890_Entry40 *)((u8 *)D_807F93F0 + entry_off))->unk2A + ((R2G67890_Entry40 *)((u8 *)D_807F93F0 + entry_off))->unk2C) * 0.25);
                entry_off += 0x40;
                ((R2G67890_Entry14 *)((u8 *)D_807F93F4 + entry14_off))->unkC = (f32)((f64)(((R2G67890_Entry40 *)((u8 *)D_807F93F0 + entry_off - 0x40))->unk36 + ((R2G67890_Entry40 *)((u8 *)D_807F93F0 + entry_off - 0x40))->unk30 + ((R2G67890_Entry40 *)((u8 *)D_807F93F0 + entry_off - 0x40))->unk32 + ((R2G67890_Entry40 *)((u8 *)D_807F93F0 + entry_off - 0x40))->unk34) * 0.25);
                entry14_off += 0x14;
                i++;
            } while (i < D_807F93F8);
        }
        D_807F9400 = func_8066B0F8(7, 0x3C7, 1, 0);
    }
}
