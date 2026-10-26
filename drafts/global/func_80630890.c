// func_80630890 (src/global/35000.c): stage 5, parked NON_MATCHING: frame 0x40/regs match; remaining diff: lw v1,24(a1) (ins=cur->unk18) hoisted into mtc1 slot instead of after cmpA cvt; inner cmpB lands in f0 (expected f2) with ins->unk10 temp in f2; rodata D_807581D0/D4/D8 symbol vs .rodata+off only. Key: copy arg0 into 'base' for the 2nd half, reuse node as next, cmpA=dz cmpB=dx float temps (10 locals)
typedef struct R35000aNode R35000aNode;
struct R35000aNode {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ f32 unk4;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ f32 unk10;
    /* 0x14 */ R35000aNode *unk14;
    /* 0x18 */ R35000aNode *unk18;
    /* 0x1C */ s16 unk1C;
    /* 0x1E */ s16 unk1E;
    /* 0x20 */ s16 unk20;
    /* 0x22 */ u8 unk22;
    /* 0x23 */ u8 unk23;
    /* 0x24 */ u8 unk24;
    /* 0x25 */ u8 pad25[3];
};

R35000aNode *func_80630890(R35000aNode *arg0, f32 arg1, f32 arg2, f32 arg3, R35000aNode **arg4) {
    R35000aNode *node;
    f32 dx;
    f32 dy;
    f32 dz;
    R35000aNode *head;
    R35000aNode *cur;
    R35000aNode *ins;
    R35000aNode *base;
    s32 inserted;
    f32 dist;

    dist = 0.0f;
    node = arg0;
    head = arg0;
    *arg4 = NULL;
    base = arg0;
    if (base != NULL) {
        do {
            dx = node->unk4 - arg1;
            dy = node->unk8 - arg2;
            dz = node->unkC - arg3;
            if (node->unk10 != -1.0) {
                node->unk10 = sqrtf(dx * dx + dy * dy + dz * dz);
            }
            node = node->unk14;
        } while (node != NULL);
    }
    if (base != NULL) {
        if (base->unk10 < base->unk1C || base->unk1C == -2) {
            *arg4 = base;
            if (base->unk1C == -2) {
                dist = 9999.0f;
            } else {
                dist = base->unk10;
            }
        }
        cur = base->unk14;
        if (cur != NULL) {
            do {
                inserted = 0;
                if ((dist < cur->unk10 && cur->unk10 < cur->unk1C) || cur->unk1C == -2) {
                    *arg4 = cur;
                    if (cur->unk1C == -2) {
                        dist = 9999.0f;
                    } else {
                        dist = cur->unk10;
                    }
                }
                ins = cur->unk18;
                dz = (f32)((cur->unk1C < cur->unk10) ? 9999.0 : cur->unk10);
                if (ins != NULL) {
                    do {
                        dx = (f32)((ins->unk1C < ins->unk10) ? 9999.0 : ins->unk10);
                        if (dz <= dx || cur->unk1C == -2) {
                            inserted = 1;
                            if (ins != cur->unk18) {
                                cur->unk18->unk14 = cur->unk14;
                                if (cur->unk14 != NULL) {
                                    cur->unk14->unk18 = cur->unk18;
                                }
                                node = ins->unk14;
                                ins->unk14 = cur;
                                cur->unk14 = node;
                                if (node != NULL) {
                                    node->unk18 = cur;
                                }
                                cur->unk18 = ins;
                            }
                        }
                        ins = ins->unk18;
                    } while (ins != NULL && inserted == 0);
                }
                if (inserted == 0) {
                    cur->unk18->unk14 = cur->unk14;
                    if (cur->unk14 != NULL) {
                        cur->unk14->unk18 = cur->unk18;
                    }
                    cur->unk18 = NULL;
                    cur->unk14 = head;
                    head->unk18 = cur;
                    head = cur;
                }
                cur = cur->unk14;
            } while (cur != NULL);
        }
    }
    return head;
}
