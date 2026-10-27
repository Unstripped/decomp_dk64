// func_8063A38C (src/global/36880.c): func_8063A38C: TEXT-IDENTICAL, reloc only (stage 6). Fix: 'u32 found' (s32/u8/s16 gave move v0,s6 / extra sll-sra). Only fdiff diff is the function-owned 360.0 literal relocating as .rodata+0x2a8 vs splat D_807584A8 (.rodata section itself matches). Paste into src replacing GLOBAL_ASM; add forward decl 'R36880fNode *func_8063A848(R36880fNode *, R36880fNode *);' above it (R36880fNode already typedef'd in 36880.c).
typedef struct R36880fLink {
    /* 0x00 */ u8 pad0[0x4C];
    /* 0x4C */ s32 unk4C;
    /* 0x50 */ s32 unk50;
    /* 0x54 */ s32 unk54;
    /* 0x58 */ s32 unk58;
    /* 0x5C */ s32 unk5C;
    /* 0x60 */ u8 pad60[0x74];
    /* 0xD4 */ struct R36880fLink *unkD4;
} R36880fLink;

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

typedef struct R36880fSrcA {
    /* 0x00 */ f32 unk0;
    /* 0x04 */ f32 unk4;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ f32 unk10;
    /* 0x14 */ f32 unk14;
    /* 0x18 */ u8 pad18[4];
    /* 0x1C */ f32 unk1C;
    /* 0x20 */ u8 pad20[0x2E];
    /* 0x4E */ u8 unk4E;
    /* 0x4F */ u8 pad4F;
    /* 0x50 */ R36880fLink *unk50;
    /* 0x54 */ R36880fNode *unk54;
    /* 0x58 */ u8 pad58[0x60];
    /* 0xB8 */ R36880fLink *unkB8;
    /* 0xBC */ R36880fNode *unkBC;
} R36880fSrcA;

typedef struct R36880fList {
    /* 0x00 */ R36880fSrcA *data;
    /* 0x04 */ u8 pad4[0x10];
    /* 0x14 */ struct R36880fList *next;
    /* 0x18 */ u8 pad18[0xC];
    /* 0x24 */ u8 unk24;
} R36880fList;

R36880fNode *func_8063A848(R36880fNode *, R36880fNode *);
void func_80639FC0(f32, f32, f32, f32, f32, f32, f32 *, f32 *, f32 *, u8);


R36880fNode *func_8063A38C(R36880fList *arg0, R36880fList *arg1, f32 arg2, f32 arg3, f32 arg4) {
    R36880fNode *result;
    u8 second;
    f32 x;
    f32 y;
    f32 z;
    f32 d2;
    u32 found;
    f32 scale;
    f32 base;
    R36880fNode *tgt;
    R36880fSrcA *d;
    R36880fSrcA *d1;
    R36880fLink *link;
    s16 idx;
    s16 r;
    f32 sp9C;
    f32 sp98;
    f32 sp94;
    s16 r2;

    result = NULL;
    second = 0;
    if (arg0 == NULL) {
        arg0 = arg1;
        second = 1;
    }
    if (arg0 != NULL) {
        do {
            switch (arg0->unk24) {
            case 2:
                d = arg0->data;
                if (d->unk4E & 0x10) {
                    tgt = NULL;
                } else {
                    x = d->unk0;
                    y = d->unk4 - d->unk10;
                    z = d->unk8;
                    tgt = d->unk54;
                    link = d->unk50;
                    func_80639FC0(x, y, z, arg2, arg3, arg4, &sp9C, &sp98, &sp94, 0);
                    scale = d->unkC;
                }
                break;
            case 1:
                d1 = arg0->data;
                tgt = d1->unkBC;
                link = d1->unkB8;
                x = d1->unk0;
                z = d1->unk8;
                y = d1->unk4 - d1->unk1C;
                sp98 = d1->unk14;
                scale = d1->unkC;
                break;
            default:
                tgt = NULL;
                break;
            }
            if (tgt != NULL) {
                r = tgt->unk2C;
                d2 = (arg2 - x) * (arg2 - x) + (arg3 - y) * (arg3 - y) + (arg4 - z) * (arg4 - z);
                if (d2 < (f32)(r * r)) {
                    r2 = tgt->unk2A;
                    if (d2 < (f32)(r2 * r2)) {
                        tgt->unk2F = tgt->unk2E;
                    } else {
                        d2 = sqrtf(d2);
                        tgt->unk2F = (u32)((f32)(u32)tgt->unk2E - ((f32)(u32)tgt->unk2E * (d2 - (f32)tgt->unk2A)) / (f32)(tgt->unk2C - tgt->unk2A));
                    }
                    if (tgt->unk24 != -1) {
                        found = 0;
                        if (link != NULL) {
                            do {
                                if (link->unk5C == tgt->unk24) {
                                    found = 1;
                                } else {
                                    link = link->unkD4;
                                }
                            } while (found == 0 && link != NULL);
                        }
                        tgt->unk26 = (s16)(s32)sp98;
                        tgt->unk26 = (s16)(s32)((f64)tgt->unk26 + ((f64)(link->unk54 * 0x168 / link->unk58) + ((f64)link->unk50 * 360.0 / (f64)link->unk58) / (f64)link->unk4C));
                    } else {
                        tgt->unk26 = (s16)(s32)sp98;
                    }
                    tgt->unk14 = x;
                    tgt->unk26 = tgt->unk26 + tgt->unk28;
                    tgt->unk18 = y;
                    tgt->unk1C = z;
                    tgt->next = NULL;
                    tgt->unk10 = (s16)(s32)((f32)tgt->unkC * scale);
                    tgt->unk12 = (s16)(s32)((f32)tgt->unkE * scale);
                    result = func_8063A848(result, tgt);
                }
            }
            arg0 = arg0->next;
            if (arg0 == NULL && second == 0) {
                arg0 = arg1;
                second = 1;
            }
        } while (arg0 != NULL);
    }
    return result;
}
