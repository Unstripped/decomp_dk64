// modelPendingQueueInsert (src/global/36880.c): stage 5: 33 diff lines (down from 48). Frame 0x58, callee-saved, relocations match 100%. Remaining: loop index narrowing (v0 vs t0), else base address (a2 vs v0), case 5 sb/sh store order
typedef struct ModelA_PendingSrc {
    /* 0x00 */ u8 pad0[4];
    /* 0x04 */ f32 unk4;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ u8 pad10[0xE];
    /* 0x1E */ s16 unk1E;
    /* 0x20 */ u8 pad20[4];
    /* 0x24 */ u8 unk24;
} ModelA_PendingSrc;

extern u8 D_807F7140;

void modelPendingQueueInsert(ModelA_PendingSrc *arg0, u8 arg1) {
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

    if (0) { csStateTickTimers((s32)&idx); csStateTickTimers((s32)&tbl); } allow = 1; if (arg0->unk24 == 1) { idx = hashTableLookup(arg0->unk1E); tbl = (u8 *)D_807F6000; obj = ((ModelSlot *)tbl)[idx].unk7C; if (obj != NULL) {
            switch (obj[0x54]) {
            case 2:
                allow = 0;
                break;
            case 0:
                allow = arg1;
                break;
            case 4:
                if (newv == 0) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
                allow = arg1;
            case 3:
            case 6:
                best = 1e8f;
                for (i = 0; i < D_80750AB4;) {
                    p = (u8 *)gPlayerSlots + i * 0x2F0;
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
                            if (arg0) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
                            best = (*pz - arg0->unkC) * (*pz - arg0->unkC) + ((*px - arg0->unk4) * (*px - arg0->unk4) + (*py - arg0->unk8) * (*py - arg0->unk8));
                        }
                        if (tbl && tbl) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
                    }
                    if (p) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
                }
                flag = 0;
                if (best < (f32)*(s32 *)(obj + 0x58)) {
                    flag = 1;
                }
                allow = allow & flag;
                break;
            case 5:
                if (D_807F6028 == 0x14) return;
                allow = 0;
                D_807F6030[D_807F6028].id = arg0->unk1E;
                D_807F6030[D_807F6028].key = *(s32 *)(obj + 0x58);
                D_807F6030[D_807F6028].done = 0;
                D_807F6028++;
                break;
            }
            if (allow != 0) {
                D_807F7140++;
                if (D_807F60A8 != 0x46) {
                    D_807F60B0[D_807F60A8] = *(s16 *)(tbl + idx * 0x90 + 0x8A);
                    D_807F60A8++;
                    csStateTickTimers((s32)obj);
                    csStateUpdate((s32)obj, arg0->unk1E);
                }
            }
        }
    }
}
