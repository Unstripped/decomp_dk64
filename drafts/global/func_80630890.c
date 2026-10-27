// func_80630890 (src/global/35000.c): func_80630890 (src/global/35000.c): stage 5, parked NON_MATCHING: frame/regs/f-regs/v0-v1 all match (separate cmpB local for inner compare; ins loaded after dz ternary; node reused as cur->unk14 temp in inner swap block raises node priority so node=v0, ins=v1). Remaining diff: last block (inserted==0) temps t6,t7,t8 vs expected t7,t8,t9 (one hidden temp consumed after the inner swap block); rodata symbol reloc names only.
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

extern R35000aNode *D_807F5FF0;
extern R35000aNode *D_807F5FF4;
extern R35000aNode *D_807F5FF8;
extern R35000aNode *D_807F5FFC;

void func_80630300(void) {
    D_807F5FF0 = 0;
    D_807F5FF4 = 0;
    D_807F5FF8 = 0;
    D_807F5FFC = 0;
}

s32 func_80630324(u8 arg0, u8 *arg1) {
    if (arg0 == 2) {
        if (arg1[0x4E] & 2) {
            return 0;
        }
        if (arg1[0x4E] & 1) {
            return 1;
        }
        return 0;
    }
    switch (arg0) {
    case 0:
    case 1:
        return 0;
    case 5:
        return 1;
    default:
        return 0;
    }
}

void func_806306D0(R35000aNode *);

void func_8063039C(void) {
    func_806306D0(D_807F5FF4);
    D_807F5FF4 = 0;
}

void *func_80610FE8(s32);

R35000aNode *func_806303C4(R35000aNode *arg0, u8 arg1, s32 arg2, f32 arg3, f32 arg4, f32 arg5, s16 arg6, s16 arg7, u8 arg8, s16 arg9, u8 arg10) {
    s32 found;
    R35000aNode *prev;
    R35000aNode *node;
    R35000aNode *head;

    found = 0;
    prev = NULL;
    if (arg10 == 1) {
        arg0 = D_807F5FF0;
    }
    if (arg10 == 2) {
        arg0 = D_807F5FF4;
    }
    if (arg10 == 3) {
        arg0 = D_807F5FF8;
    }
    if (arg10 == 4) {
        arg0 = D_807F5FFC;
    }
    head = arg0;
    if (arg0 != NULL) {
        do {
            if (arg2 == arg0->unk0) {
                found = 1;
            } else {
                prev = arg0;
                arg0 = arg0->unk14;
            }
        } while (arg0 != NULL && found == 0);
    }
    if (found != 0) {
        arg0->unk4 = arg3;
        arg0->unk8 = arg4;
        arg0->unkC = arg5;
        arg0->unk1C = arg6;
        if (arg9 != -1) {
            arg0->unk20 = arg9;
        }
        arg0->unk23 = 1;
    } else {
        node = func_80610FE8(0x28);
        node->unk24 = arg1;
        node->unk0 = arg2;
        node->unk4 = arg3;
        node->unk8 = arg4;
        node->unkC = arg5;
        node->unk1C = arg6;
        node->unk1E = arg7;
        node->unk22 = arg8;
        node->unk23 = 1;
        node->unk20 = 0;
        node->unk14 = NULL;
        node->unk10 = 0.0f;
        if (prev != NULL) {
            prev->unk14 = node;
            node->unk18 = prev;
        } else {
            head = node;
            node->unk18 = NULL;
        }
    }
    if (arg10 == 1) {
        D_807F5FF0 = head;
    }
    if (arg10 == 2) {
        D_807F5FF4 = head;
    }
    if (arg10 == 3) {
        D_807F5FF8 = head;
    }
    if (arg10 == 4) {
        D_807F5FFC = head;
    }
    return head;
}

void heapFree(void *);

R35000aNode *func_80630588(R35000aNode *arg0, s32 arg1, u8 arg2, u8 *arg3) {
    u8 found;
    R35000aNode *prev;
    R35000aNode *head;

    found = 0;
    prev = NULL;
    if (arg2 == 1) {
        arg0 = D_807F5FF0;
    }
    if (arg2 == 2) {
        arg0 = D_807F5FF4;
    }
    if (arg2 == 3) {
        arg0 = D_807F5FF8;
    }
    if (arg2 == 4) {
        arg0 = D_807F5FFC;
    }
    head = arg0;
    if (arg0 != NULL) {
        do {
            if (arg1 == arg0->unk0) {
                found = 1;
            } else {
                prev = arg0;
                arg0 = arg0->unk14;
            }
        } while (arg0 != NULL && found == 0);
    }
    if (found != 0) {
        if (prev != NULL) {
            prev->unk14 = arg0->unk14;
        } else {
            head = arg0->unk14;
        }
        if (arg0->unk14 != NULL) {
            arg0->unk14->unk18 = prev;
        }
        heapFree(arg0);
    }
    *arg3 = found;
    if (arg2 == 1) {
        D_807F5FF0 = head;
    }
    if (arg2 == 2) {
        D_807F5FF4 = head;
    }
    if (arg2 == 3) {
        D_807F5FF8 = head;
    }
    if (arg2 == 4) {
        D_807F5FFC = head;
    }
    return head;
}

void func_806306D0(R35000aNode *arg0) {
    R35000aNode *cur;

    if (arg0 != NULL) {
        do {
            cur = arg0;
            arg0 = arg0->unk14;
            heapFree(cur);
        } while (arg0 != NULL);
    }
}

R35000aNode *func_8063070C(R35000aNode *arg0) {
    R35000aNode *head;

    head = arg0;
    if (arg0 != NULL) {
        do {
            if (arg0->unk22 == 1 && arg0->unk23 == 0) {
                if (arg0->unk18 != NULL) {
                    arg0->unk18->unk14 = arg0->unk14;
                } else {
                    head = arg0->unk14;
                }
                if (arg0->unk14 != NULL) {
                    arg0->unk14->unk18 = arg0->unk18;
                }
                heapFree(arg0);
            }
            arg0 = arg0->unk14;
        } while (arg0 != NULL);
    }
    return head;
}

void func_806307AC(R35000aNode *arg0) {
    if (arg0 != NULL) {
        do {
            arg0->unk23 = 0;
            arg0 = arg0->unk14;
        } while (arg0 != NULL);
    }
}

void func_806307CC(R35000aNode *arg0, s32 arg1, u8 arg2, u8 arg3, s8 *arg4) {
    s8 found;

    found = 0;
    if (arg2 == 1) {
        arg0 = D_807F5FF0;
    }
    if (arg2 == 2) {
        arg0 = D_807F5FF4;
    }
    if (arg2 == 3) {
        arg0 = D_807F5FF8;
    }
    if (arg2 == 4) {
        arg0 = D_807F5FFC;
    }
    if (arg0 != NULL) {
        do {
            if (arg1 == arg0->unk0) {
                found = 1;
            } else {
                arg0 = arg0->unk14;
            }
        } while (arg0 != NULL && found == 0);
    }
    if (found != 0) {
        if (arg3) {
            arg0->unk10 = -1.0f;
        } else {
            arg0->unk1C = -2;
        }
    }
    *arg4 = found;
}

#ifdef NON_MATCHING
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
    f32 cmpB;

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
                dz = (f32)((cur->unk1C < cur->unk10) ? 9999.0 : cur->unk10);
                ins = cur->unk18;
                if (ins != NULL) {
                    do {
                        cmpB = (f32)((ins->unk1C < ins->unk10) ? 9999.0 : ins->unk10);
                        if (dz <= cmpB || cur->unk1C == -2) {
                            inserted = 1;
                            if (ins != cur->unk18) {
                                cur->unk18->unk14 = cur->unk14;
                                node = cur->unk14;
                                if (node != NULL) {
                                    node->unk18 = cur->unk18;
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
