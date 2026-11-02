// modelPendingQueueInsert (src/global/36880.c): R5 W4Mid: stage 5, deadsweep 26 -> 3 (189/189 insns, parked in 36880.c copy). Levers: px/py/pz as i*0x2F0+(u8*)gPlayerSlots+off; player slot fields via struct view ((W4Slot*)gPlayerSlots)[i].u0/u4 (not raw p/ *(u8**)(p+4)); NO p local; 'allow &= best < (f32)*(s32*)(obj+0x58)' (no flag local); tail '*(s16 *)(tbl + 0x8A + idx * 0x90)' (operand order fixed the t-ring, 16 -> 6); dead tests found by annealing (anneal.py, ~11 FAKEs, none greedy-removable); case-4 'newv = (u8*)gPlayerSlots' legalises the newv dead tests. Remaining 3 lines: offset cand i*0x2F0 gets a0 (target a2) in 'mflo/addu v0,off,t1'.
typedef struct ModelPendingEntry {
    /* 0x00 */ u8 pad0[4];
    /* 0x04 */ f32 unk4;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ u8 pad10[0xE];
    /* 0x1E */ s16 unk1E;
    /* 0x20 */ u8 pad20[4];
    /* 0x24 */ u8 unk24;
} ModelPendingEntry;

extern u8 D_807F7140;

typedef struct W4M_Slot { u8 u0; u8 pad1[3]; u8 *u4; u8 pad8[0x21C-8]; f32 x; f32 y; f32 z; u8 padE[0x2F0-0x228]; } W4M_Slot;
void modelPendingQueueInsert(ModelPendingEntry *arg0, u8 arg1) {
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
    s32 i;
    ModelPendingQueueEntry *e;
    int nv;
    u8 *p;
    u8 flag;
    f32 *px;
    f32 *py;
    f32 *pz;
    f32 best;

    if (0) { csStateTickTimers((s32)&idx); csStateTickTimers((s32)&tbl); } allow = 1; if (arg0->unk24 == 1) { idx = hashTableLookup(arg0->unk1E); tbl = (u8 *)D_807F6000; obj = ((ModelSlot *)tbl)[idx].unk7C; if (obj != NULL) {
            switch (obj[0x54]) {
            case 2:
                allow = 0;
                break;
            case 0:
                allow = arg1;
                break;
            case 4:
                newv = (u8 *)gPlayerSlots;  // FAKE: defines newv so the dead tests below read an assigned local
                if (newv && newv) {}  // FAKE: fk
                if (newv == 0) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
                if (newv != 0) {}  // FAKE: fk
                allow = arg1;
            case 3:
            case 6:
                best = 1e8f;
                for (i = 0; i < D_80750AB4; i = (u8)(i + 1)) {
                    
                    if (tbl && tbl) {}  // FAKE: fk
                    if (((W4M_Slot *)gPlayerSlots)[i].u0 != 0) {
                        if (obj == 0) {}  // FAKE: fk
                        if (arg0 && arg0) {}  // FAKE: fk
                        if (arg0 != 0) {}  // FAKE: fk
                        if (obj[0x54] == 6) {
                            px = (f32 *)(((W4M_Slot *)gPlayerSlots)[i].u4 + 0x7C);
                            py = (f32 *)(((W4M_Slot *)gPlayerSlots)[i].u4 + 0x80);
                            newv = ((W4M_Slot *)gPlayerSlots)[i].u4 + 0x84;
                            pz = (f32 *)newv;
                        } else {
                            px = (f32 *)(i * 0x2F0 + (u8 *)gPlayerSlots + 0x21C);
                            if (!arg0) {
                            }
                            if (tbl && tbl) {}  // FAKE: fk
                            if (i && i) {}  // FAKE: fk
                            py = (f32 *)(i * 0x2F0 + (u8 *)gPlayerSlots + 0x220);
                            pz = (f32 *)(i * 0x2F0 + (u8 *)gPlayerSlots + 0x224);
                        }
        if (px) {} // FAKE: x
                        if (gPlayerSlots != 0) {}  // FAKE: fk
                        if ((*pz - arg0->unkC) * (*pz - arg0->unkC) + ((*px - arg0->unk4) * (*px - arg0->unk4) + (*py - arg0->unk8) * (*py - arg0->unk8)) < (0, best)) {
                            if (((W4M_Slot *)gPlayerSlots)[i].u4 != 0) {}  // FAKE: fk
                            if (px && px) {}  // FAKE: fk
                            best = (*pz - arg0->unkC) * (*pz - arg0->unkC) + ((*px - arg0->unk4) * (*px - arg0->unk4) + (*py - arg0->unk8) * (*py - arg0->unk8));
                        }
                        if (py && py) {}  // FAKE: fk
                        if (tbl && tbl) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
                    }
                    
                }
                allow &= best < (f32)*(s32 *)(obj + 0x58);
                break;
            case 5:
                if (D_807F6028 == 0x14) return;
                allow = 0;
                D_807F6030[D_807F6028].id = arg0->unk1E;
                D_807F6030[D_807F6028].key = *(s32 *)(obj + 0x58);
                D_807F6030[D_807F6028++].done = 0;
                break;
            }
            if (allow != 0) {
                D_807F7140++;
                if (D_807F60A8 != 0x46) {
                    D_807F60B0[D_807F60A8] = *(s16 *)(tbl + 0x8A + idx * 0x90);
                    D_807F60A8++;
                    csStateTickTimers((s32)obj);
                    csStateUpdate((s32)obj, arg0->unk1E);
                }
            }
        }
    }
}
