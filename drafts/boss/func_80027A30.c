// func_80027A30 (src/boss/3840.c): from .scratch/Boss3C/func_80027A30_best.c
#include "common.h"

typedef struct {
    s16 unk0;
    s16 unk2;
    s16 unk4;
    s16 pad6[2];
} Boss3C_Point;

typedef struct {
    char pad[0x14];
    Boss3C_Point *unk14;
} Boss3C_Struct_DCA0;

typedef struct {
    char pad[0x20];
    u8 *unk20;
} Boss3C_Struct_DC98;

typedef struct {
    char pad[0x25];
    u8 unk25;
} Boss3C_Struct_DC90;

typedef struct {
    char pad0[0x7C];
    f32 unk7C;
    f32 unk80;
    f32 unk84;
} Boss3C_Actor;

typedef struct {
    char pad0[0x15];
    u8 unk15;
} Boss3C_Struct_80027950;

extern Boss3C_Struct_DC90 *D_807FDC90;
extern Boss3C_Struct_DC98 *D_807FDC98;
extern Boss3C_Struct_DCA0 *D_807FDCA0;
extern Boss3C_Actor *D_807FBB40;

void func_80027A30(Boss3C_Struct_80027950 *arg0, u8 *arg1) {
    s16 i = arg1[arg0->unk15];
    s32 max_dist = 0;
    u8 limit = arg1[arg0->unk15 + 1];

    if (i <= limit) {
        do {
            u8 *unk20 = D_807FDC98->unk20;
            Boss3C_Actor *actor = D_807FBB40;
            Boss3C_Point *points = D_807FDCA0->unk14;
            Boss3C_Point *pt = &points[unk20[i * 2]];
            f32 dz = actor->unk84 - (f32)pt->unk4;
            f32 dx = actor->unk7C - (f32)pt->unk0;
            f32 dy = actor->unk80 - (f32)pt->unk2;
            s32 dist = (s32)sqrtf((dx * dx) + (dy * dy) + (dz * dz));

            if (dist > max_dist) {
                max_dist = dist;
                D_807FDC90->unk25 = i;
            }
            i++;
        } while (i <= arg1[arg0->unk15 + 1]);
    }
    arg0->unk15 += 2;
}
