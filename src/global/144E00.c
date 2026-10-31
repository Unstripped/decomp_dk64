#include "common.h"

struct AdpcmNMAcmd;
struct AdpcmNMLoadFilter;
typedef struct {
    u32 w0;
    u32 w1;
} AdpcmAcmd;

typedef struct {
    s32 unk0;
    s32 unk4;
    u8 pad8[8];
    s32 *loop;
} AdpcmWave;

typedef struct {
    u8 pad0[0xC];
    void *unkC;
    void *unk10;
    s32 unk14;
    s32 unk18;
    s32 unk1C;
    AdpcmWave *unk20;
    s32 unk24;
    s32 (*dma)(void *, s32, void *);
    void *unk2C;
    s32 unk30;
    s32 unk34;
    s32 unk38;
    s32 unk3C;
} AdpcmFilter;

struct AdpcmNMAcmd *alLoadParam(struct AdpcmNMAcmd *ptr, struct AdpcmNMLoadFilter *filter, s32 samples, s32 count, s16 out, s16 state, s32 flags);

struct AdpcmNMAcmd *n_alAdpcmPull(AdpcmFilter *arg0, s16 *arg1, s32 arg2, struct AdpcmNMAcmd *arg3) {
    AdpcmAcmd *sp7C;
    s16 sp7A;
    s32 sp74;
    s32 sp70;
    s32 sp6C;
    s32 sp68;
    s32 sp64;
    s32 sp60;
    s32 sp5C;
    s32 sp58;
    s32 sp54;
    s32 sp50;
    s32 sp4C;
    s32 sp48;
    AdpcmFilter *sp44;
    AdpcmAcmd *sp40;
    AdpcmAcmd *sp3C;
    AdpcmAcmd *sp38;

    sp7C = (AdpcmAcmd *)arg3;
    sp4C = 0;
    sp48 = 0;
    sp44 = arg0;
    if (arg2 == 0) {
        return (struct AdpcmNMAcmd *)sp7C;
    }
    sp7A = 0;
    sp40 = sp7C++;
    sp40->w0 = (sp44->unk24 & 0xFFFFFF) | 0x0B000000;
    sp40->w1 = ((u32)sp44->unk20->loop + 8) & 0x1FFFFFFF;
    sp48 = ((u32)(sp44->unk30 + arg2) > (u32)sp44->unk18) && sp44->unk1C;
    if (sp48 != 0) {
        sp5C = sp44->unk18 - sp44->unk30;
    } else {
        sp5C = arg2;
    }
    if (sp44->unk34 != 0) {
        sp54 = 0x10 - sp44->unk34;
    } else {
        sp54 = 0;
    }
    sp74 = sp5C - sp54;
    if (sp74 < 0) {
        sp74 = 0;
    }
    sp70 = (sp74 + 0xF) >> 4;
    sp6C = sp70 * 9;
    if (sp48 != 0) {
        sp7C = (AdpcmAcmd *)alLoadParam((struct AdpcmNMAcmd *)sp7C, (struct AdpcmNMLoadFilter *)sp44, sp74, sp6C, *arg1, sp7A, sp44->unk38);
        if (sp44->unk34 != 0) {
            *arg1 += sp44->unk34 * 2;
        } else {
            *arg1 += 0x20;
        }
        sp44->unk34 = sp44->unk14 & 0xF;
        sp44->unk3C = sp44->unk20->unk0 + ((u32)sp44->unk14 >> 4) * 9 + 9;
        sp44->unk30 = sp44->unk14;
        sp50 = *arg1;
        if (arg2 > sp5C) {
            do {
                arg2 -= sp5C;
                sp58 = (((sp70 + 1) << 5) + sp50 + 0x10) & ~0x1F;
                sp50 += sp5C * 2;
                if ((sp44->unk1C != -1) && (sp44->unk1C != 0)) {
                    sp44->unk1C = sp44->unk1C - 1;
                }
                sp5C = ((u32)arg2 < (u32)(sp44->unk18 - sp44->unk14)) ? arg2 : sp44->unk18 - sp44->unk14;
                sp74 = (sp5C - 0x10) + sp44->unk34;
                if (sp74 < 0) {
                    sp74 = 0;
                }
                sp70 = (sp74 + 0xF) >> 4;
                sp6C = sp70 * 9;
                sp7C = (AdpcmAcmd *)alLoadParam((struct AdpcmNMAcmd *)sp7C, (struct AdpcmNMLoadFilter *)sp44, sp74, sp6C, sp58, sp7A, sp44->unk38 | 2);
                sp3C = sp7C++;
                sp3C->w0 = (((sp44->unk34 * 2) + sp58) & 0xFFFFFF) | 0x0A000000;
                sp3C->w1 = ((sp50 & 0xFFFF) << 0x10) | ((sp5C * 2) & 0xFFFF);
            } while (arg2 > sp5C);
        }
        sp44->unk34 = (sp44->unk34 + arg2) & 0xF;
        sp44->unk30 = sp44->unk30 + arg2;
        sp44->unk3C = sp44->unk3C + (sp70 * 9);
        return (struct AdpcmNMAcmd *)sp7C;
    }
    sp5C = sp70 << 4;
    sp68 = (sp44->unk3C + sp6C) - (sp44->unk20->unk0 + sp44->unk20->unk4);
    if (sp68 < 0) {
        sp68 = 0;
    }
    sp60 = (sp68 / 9) * 0x10;
    if (sp60 > (sp5C + sp54)) {
        sp60 = sp5C + sp54;
    }
    sp6C -= sp68;
    if ((sp60 - (sp60 & 0xF)) < arg2) {
        sp4C = 1;
        sp7C = (AdpcmAcmd *)alLoadParam((struct AdpcmNMAcmd *)sp7C, (struct AdpcmNMLoadFilter *)sp44, sp5C - sp60, sp6C, *arg1, sp7A, sp44->unk38);
        if (sp44->unk34 != 0) {
            *arg1 += sp44->unk34 * 2;
        } else {
            *arg1 += 0x20;
        }
        sp44->unk34 = (sp44->unk34 + arg2) & 0xF;
        sp44->unk30 = sp44->unk30 + arg2;
        sp44->unk3C = sp44->unk3C + (sp70 * 9);
    } else {
        sp44->unk34 = 0;
        sp44->unk3C = sp44->unk3C + (sp70 * 9);
    }
    if (sp60 != 0) {
        sp44->unk34 = 0;
        if (sp4C != 0) {
            sp64 = ((sp54 + sp5C) - sp60) * 2;
        } else {
            sp64 = 0;
        }
        sp38 = sp7C++;
        sp38->w0 = ((*arg1 + sp64) & 0xFFFFFF) | 0x02000000;
        sp38->w1 = sp60 * 2;
    }
    return (struct AdpcmNMAcmd *)sp7C;
}

typedef struct DecodeBook {
    s32 unk0;
    s32 unk4;
    s32 unk8;
} DecodeBook;

typedef struct DecodeWave {
    s32 unk0;
    s32 unk4;
    u8 pad8[4];
    DecodeBook *book;
    s32 *loop;
} DecodeWave;

typedef struct DecodeFilter {
    u8 pad0[0x10];
    void *out;
    s32 unk14;
    s32 unk18;
    s32 unk1C;
    DecodeWave *wave;
    s32 unk24;
    u8 pad28[8];
    s32 unk30;
    s32 unk34;
    s32 unk38;
    s32 unk3C;
} DecodeFilter;

void _decodeChunk(DecodeFilter *filter, s32 paramID, DecodeWave *wave) {
    DecodeFilter *temp;

    temp = filter;
    switch (paramID) {
    case 5:
        temp->wave = wave;
        temp->unk3C = temp->wave->unk0;
        temp->unk30 = 0;
        switch (temp->wave->pad8[0]) {
        case 0:
            temp->wave->unk4 = (temp->wave->unk4 / 9) * 9;
            temp->unk24 = (temp->wave->loop[1] * (temp->wave->loop[0] << 1)) * 8;
            if (temp->wave->book != NULL) {
                temp->unk14 = temp->wave->book->unk0;
                temp->unk18 = temp->wave->book->unk4;
                temp->unk1C = temp->wave->book->unk8;
                bcopy((u8 *)temp->wave->book + 0xC, temp->out, 0x20);
            } else {
                temp->unk14 = temp->unk18 = temp->unk1C = 0;
            }
            break;
        case 1:
            if (temp->wave->book != NULL) {
                temp->unk14 = temp->wave->book->unk0;
                temp->unk18 = temp->wave->book->unk4;
                temp->unk1C = temp->wave->book->unk8;
            } else {
                temp->unk14 = temp->unk18 = temp->unk1C = 0;
            }
            break;
        default:
            break;
        }
        break;
    case 4:
        temp->unk34 = 0;
        temp->unk38 = 1;
        temp->unk30 = 0;
        if (temp->wave != NULL) {
            temp->unk3C = temp->wave->unk0;
            if (temp->wave->pad8[0] == 0) {
                if (temp->wave->book != NULL) {
                    temp->unk1C = temp->wave->book->unk8;
                }
            } else if (temp->wave->pad8[0] == 1) {
                if (temp->wave->book != NULL) {
                    temp->unk1C = temp->wave->book->unk8;
                }
            }
        }
        break;
    default:
        break;
    }
}

typedef struct AdpcmNMAcmd {
    u32 w0;
    u32 w1;
} AdpcmNMAcmd;

typedef struct AdpcmNMLoadFilter {
    u8 pad0[0xC];
    void *unkC;
    void *unk10;
    u8 pad14[0x14];
    s32 (*dma)(void *, s32, void *);
    void *unk2C;
    u8 pad30[8];
    s32 unk38;
    void *unk3C;
} AdpcmNMLoadFilter;

AdpcmNMAcmd *alLoadParam(AdpcmNMAcmd *ptr, AdpcmNMLoadFilter *filter, s32 samples, s32 count, s16 out, s16 state, s32 flags) {
    s32 offset;
    s32 dmaAddr;

    if (count > 0) {
        AdpcmNMAcmd *cmd;

        dmaAddr = filter->dma(filter->unk3C, count, filter->unk2C);
        offset = dmaAddr & 7;
        count += offset;
        cmd = ptr++;
        cmd->w0 = 0x04000000 | ((((count - (count & 7)) + 8) & 0xFFF) << 12) | (state & 0xFFF);
        cmd->w1 = (s32)(dmaAddr - offset);
    } else {
        offset = 0;
    }
    if (flags & 2) {
        AdpcmNMAcmd *cmd;

        cmd = ptr++;
        cmd->w0 = 0x0F000000;
        cmd->w1 = (u32)filter->unk10 & 0x1FFFFFFF;
    }
    {
        AdpcmNMAcmd *cmd;

        cmd = ptr++;
        cmd->w0 = ((u32)filter->unkC & 0x1FFFFFFF & 0xFFFFFF) | 0x01000000;
        cmd->w1 = ((flags & 0xF) << 28) | (((samples * 2) & 0xFFF) << 16) | ((offset & 0xF) << 12) | (out & 0xFFF);
    }
    filter->unk38 = 0;
    return ptr;
}
