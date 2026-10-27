// func_8062D620 (src/global/2F550.c): Stage 4 (NM2F). Stream+frame 0x68 identical; only s16 sp56 at 0x5E vs target 0x56 (sp58 0x58 ok). Layout study: locals are byte-packed top-down in declaration order inside a 16-byte area (0x58..0x68); 3 words -> frame 0x60, 5 words -> 0x70 (any extra/unused local grows the frame), so nothing can sit below 0x58; target puts the halfword at 0x56 below sp58, impossible with this frame. Tried all decl permutations, s32 sp54+(u8*)&sp54+2, s32 sp54[2], u8/s8/s16 arrays, block-scoped sp56, s16/u8 pads, register keyword, dead-alias pads, permuter 400s (22k iters, no gain).
typedef struct R2F550cEntry {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ f32 unk4;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ u8 pad10[4];
    /* 0x14 */ struct R2F550cEntry *unk14;
    /* 0x18 */ u8 pad18[4];
    /* 0x1C */ s16 unk1C;
    /* 0x1E */ s16 unk1E;
    /* 0x20 */ s16 unk20;
    /* 0x22 */ u8 unk22;
    /* 0x23 */ u8 pad23;
    /* 0x24 */ u8 unk24;
} R2F550cEntry;

s32 func_806303C4(s32, u8, s32, f32, f32, f32, s32, s32, s32, s32, s32);
u8 func_8062E898(void *, u8 *, f32, f32, f32);
void func_806306D0(s32);
void mapChunkUpdateEntryNode(R2F550cEntry *);
extern s32 D_807F5FFC;
s32 func_8062DAF4(R2F550bObj *, f32, f32, f32);
void mapChunkFrameUpdate(f32, f32, f32);
void mapChunkClearNodeFlags(u8);
void mapChunkFreeNodeLists(u8);
void mapChunkRebuildNodeLists(f32, f32, f32, u8);
void func_80652A08(f32, f32, f32, u8);
s32 func_80630890(s32, f32, f32, f32, void *);
void func_806307AC(s32);
s32 func_8063070C(s32);
s32 func_8063A38C(s32, s32, f32, f32, f32);

void func_8062D620(R2F550bObj *arg0, R2F550bTree *arg1, R2F550cEntry *arg2, f32 arg3, f32 arg4, f32 arg5, u8 arg6, u8 arg7, u8 arg8) {
    s32 listA;
    s32 listB;
    s16 sp56;
    s32 sp58;

    if (0) {
        mapChunkUpdateEntryNode((R2F550cEntry *)&arg6);
    }
    listA = 0;
    listB = 0;
    if (arg0 == NULL) {
        return;
    }
    if (arg6 == 0 && func_8062DAF4(arg0, arg3, arg4, arg5) == 0) {
        arg1->unk1 = 3;
        return;
    }
    switch (arg0->unkB8) {
        case 2:
            arg1->unk1 = 0;
            mapChunkFrameUpdate(arg3, arg4, arg5);
            if (arg7 == 0) {
                mapChunkClearNodeFlags(arg8);
                if (arg2 != NULL) {
                    do {
                        mapChunkUpdateEntryNode(arg2);
                        arg2 = arg2->unk14;
                    } while (arg2 != NULL);
                }
                mapChunkFreeNodeLists(arg8);
                mapChunkRebuildNodeLists(arg3, arg4, arg5, arg8);
                func_80652A08(arg3, arg4, arg5, arg8);
                D_807F5FFC = func_80630890(D_807F5FFC, arg3, arg4, arg5, &sp58);
            }
            break;
        case 1:
            arg1->unk1 = 0;
            if (arg7 == 0) {
                func_806307AC((s32)arg1->unk4);
                if (arg2 != NULL) {
                    do {
                        arg1->unk4 = (R2F550bObj *)func_806303C4((s32)arg1->unk4, arg2->unk24, arg2->unk0, arg2->unk4, arg2->unk8, arg2->unkC, arg2->unk1C, arg2->unk1E, arg2->unk22, arg2->unk20, 0);
                        arg2 = arg2->unk14;
                    } while (arg2 != NULL);
                }
                arg1->unk4 = (R2F550bObj *)func_8063070C((s32)arg1->unk4);
                arg1->unk4 = (R2F550bObj *)func_80630890((s32)arg1->unk4, arg3, arg4, arg5, &sp58);
                arg1->unk8 = func_8063A38C((s32)arg1->unk4, 0, arg3, arg4, arg5);
                D_807F5FFC = func_80630890(D_807F5FFC, arg3, arg4, arg5, &sp58);
            }
            break;
        case 0:
            if (arg2 != NULL) {
                do {
                    if (func_8062E898(arg0, (u8 *)&sp56, arg2->unk4, arg2->unk8, arg2->unkC) != 0) {
                        listB = func_806303C4(listB, arg2->unk24, arg2->unk0, arg2->unk4, arg2->unk8, arg2->unkC, arg2->unk1C, arg2->unk1E, arg2->unk22, arg2->unk20, 0);
                    } else {
                        listA = func_806303C4(listA, arg2->unk24, arg2->unk0, arg2->unk4, arg2->unk8, arg2->unkC, arg2->unk1C, arg2->unk1E, arg2->unk22, arg2->unk20, 0);
                    }
                    arg2 = arg2->unk14;
                } while (arg2 != NULL);
            }
            arg1->unk0 = func_8062E898(arg0, &arg1->unk1, arg3, arg4, arg5);
            if (arg6 != 0) {
                func_8062D620(arg0->unk0, arg1->unkC, (R2F550cEntry *)listA, arg3, arg4, arg5, arg6, arg7, arg8);
                func_8062D620(arg0->unk4, arg1->unk10, (R2F550cEntry *)listB, arg3, arg4, arg5, arg6, arg7, arg8);
            } else {
                if (arg1->unk1 != 0) {
                    if (arg1->unk1 == 1 || arg1->unk1 == 2) {
                        if (arg1->unk0 != 0) {
                            func_8062D620(arg0->unk4, arg1->unk10, (R2F550cEntry *)listB, arg3, arg4, arg5, arg6, arg7, arg8);
                        } else {
                            func_8062D620(arg0->unk0, arg1->unkC, (R2F550cEntry *)listA, arg3, arg4, arg5, arg6, arg7, arg8);
                        }
                    }
                } else {
                    func_8062D620(arg0->unk0, arg1->unkC, (R2F550cEntry *)listA, arg3, arg4, arg5, arg6, arg7, arg8);
                    func_8062D620(arg0->unk4, arg1->unk10, (R2F550cEntry *)listB, arg3, arg4, arg5, arg6, arg7, arg8);
                }
            }
            func_806306D0(listA);
            func_806306D0(listB);
            break;
    }
}
