// func_8063B4C0 (src/global/36880.c): stage 5 (parked NON_MATCHING in src copy; was stage 4): 18 hunks, frame/callee-saved/ra-allow match, idx via sll/addu/sll matches. Permuter hints applied: (0, best) in compare, newv temp for pz (+0x84), 'if (!arg0) {}' in else of obj[0x54]==6, e->key store before e->done, joined prologue statements ('if (0) {..} allow = 1; if (arg0->unk24 == 1) { idx=..; tbl=..; obj=..; nv = 0; if (obj != NULL) {' on ONE line) with 'int nv' = 0 used for case 2, i = i + 1 form. Remaining: loop prologue i narrowing (target addiu t0; andi t6; slt uses t6; move t0,t6 at bottom vs mine andi t9; move t0,t9 and v0 copy of i), px/py/pz regs (target v1/a0/a1, mine a1/a2/a3), addu base/offset order at first slot access (addu t9,t8,t7 vs t7,t8), flag/allow temp t6 vs t9 (v0).
typedef struct R36880fSrc {
    /* 0x00 */ u8 pad0[4];
    /* 0x04 */ f32 unk4;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ u8 pad10[0xE];
    /* 0x1E */ s16 unk1E;
    /* 0x20 */ u8 pad20[4];
    /* 0x24 */ u8 unk24;
} R36880fSrc;

extern u8 D_807F7140;

void func_8063B4C0(R36880fSrc *arg0, u8 arg1) {
    u8 *obj;
    u8 allow;
    s32 pad1;
    s32 pad2;
    s16 idx;
    s32 pad3;
    s32 pad4;
    s32 pad5;
    u8 *tbl;
    u8 *newv;
    u8 i;
    ModelPendingQueueEntry *e;
    int nv;
    u8 *p;
    u8 flag;
    f32 *px;
    f32 *py;
    f32 *pz;
    f32 best;

    if (0) { func_8063E078((s32)&idx); func_8063E078((s32)&tbl); } allow = 1; if (arg0->unk24 == 1) { idx = hashTableLookup(arg0->unk1E); tbl = (u8 *)D_807F6000; obj = ((ModelSlot *)(tbl + idx * 0x90))->unk7C; nv = 0; if (obj != NULL) {
            switch (obj[0x54]) {
            case 2:
                allow = nv;
                break;
            case 0:
                allow = arg1;
                break;
            case 4:
                allow = arg1;
            case 3:
            case 6:
                best = 1e8f;
                for (i = 0; i < D_80750AB4;) {
                    p = (u8 *)D_807FC924 + i * 0x2F0;
                    i++;
                    if (*p != 0) {
                        if (obj[0x54] == 6) {
                            px = (f32 *)(*(u8 **)(p + 4) + 0x7C);
                            py = (f32 *)(*(u8 **)(p + 4) + 0x80);
                            newv = *(u8 **)(p + 4) + 0x84;
                            pz = (f32 *)newv;
                        } else {
                            px = (f32 *)(p + 0x21C);
                            if (!arg0) {
                            }
                            py = (f32 *)(p + 0x220);
                            pz = (f32 *)(p + 0x224);
                        }
                        if ((*pz - arg0->unkC) * (*pz - arg0->unkC) + ((*px - arg0->unk4) * (*px - arg0->unk4) + (*py - arg0->unk8) * (*py - arg0->unk8)) < (0, best)) {
                            best = (*pz - arg0->unkC) * (*pz - arg0->unkC) + ((*px - arg0->unk4) * (*px - arg0->unk4) + (*py - arg0->unk8) * (*py - arg0->unk8));
                        }
                    }
                }
                flag = 0;
                if (best < (f32)*(s32 *)(obj + 0x58)) {
                    flag = 1;
                }
                allow = allow & flag;
                break;
            case 5:
                if (D_807F6028 == 0x14) {
                    return;
                }
                allow = 0;
                e = &D_807F6030[D_807F6028];
                e->id = arg0->unk1E;
                D_807F6028++;
                e->key = *(s32 *)(obj + 0x58);
                e->done = 0;
                break;
            }
            if (allow != 0) {
                D_807F7140++;
                if (D_807F60A8 != 0x46) {
                    D_807F60B0[D_807F60A8] = *(s16 *)(tbl + idx * 0x90 + 0x8A);
                    D_807F60A8++;
                    func_8063E078((s32)obj);
                    func_8063E0D4((s32)obj, arg0->unk1E);
                }
            }
        }
    }
}
