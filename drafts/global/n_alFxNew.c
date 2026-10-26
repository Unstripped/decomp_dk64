// n_alFxNew (src/global/140600.c): stage 5: all allocation/init blocks and target-size core shape recovered; remaining branch layout, loop compare, temporary register, and own-data relocation differences
void n_alFxNew(void **arg0, void *arg1, s16 arg2, ALHeap *arg3) {
    u16 sp36;
    u16 sp34;
    u16 sp32;
    s32 *sp2C;
    LpfNMFx *sp28;
    LpfNMFxState *sp24;

    sp2C = NULL;
    sp24 = alHeapDBAlloc(NULL, 0, arg3, 1, 0x30);
    *arg0 = sp24;
    if (((u8 *)arg1 + arg2)[0x1C] == 6) {
        sp2C = *(s32 **)((u8 *)arg1 + (arg2 * 4) + 0x20);
    } else {
        sp2C = D_80756458;
    }
    sp34 = 0;
    sp24->unk8 = (u8)sp2C[sp34];
    sp34 += 1;
    sp24->unk0 = sp2C[sp34];
    sp34 += 1;
    sp24->unk4 = alHeapDBAlloc(NULL, 0, arg3, sp24->unk8, 0x28);
    sp24->unk20 = alHeapDBAlloc(NULL, 0, arg3, sp24->unk0, 2);
    sp24->unk28 = sp24->unk20;
    sp24->unk24 = alHeapDBAlloc(NULL, 0, arg3, sp24->unk0, 2);
    sp24->unk2C = sp24->unk24;
    sp32 = 0;
    if (sp24->unk0 != 0) {
        do {
            sp24->unk24[sp32] = 0;
            sp24->unk20[sp32] = sp24->unk24[sp32];
        } while ((u32)((sp32 += 1) & 0xFFFF) < (u32)sp24->unk0);
    }
    sp36 = 0;
    if ((s32)sp24->unk8 > 0) {
        do {
            sp28 = &sp24->unk4[sp36];
            sp28->unk0 = sp2C[sp34];
            sp34 += 1;
            sp28->unk4 = sp2C[sp34];
            sp34 += 1;
            sp28->unkA = (s16)sp2C[sp34];
            sp34 += 1;
            sp28->unk8 = (s16)sp2C[sp34];
            sp34 += 1;
            sp28->unkC = (s16)sp2C[sp34];
            sp34 += 1;
            if (sp2C[sp34] != 0) {
                sp28->unk10 = ((f32)sp2C[sp34] / 1000.0f * 2.0f) / (f32)*(s32 *)((u8 *)arg1 + 0x18);
                sp34 += 1;
                sp28->unk1C = ((f32)sp2C[sp34] / 173123.4062f) * (f32)(u32)(sp28->unk4 - sp28->unk0);
                sp34 += 1;
                sp28->unk14 = 1.0f;
                sp28->unk18 = 0;
                sp28->unk24 = alHeapDBAlloc(NULL, 0, arg3, 1, 0x38);
                sp28->unk24->unk14 = alHeapDBAlloc(NULL, 0, arg3, 1, 0x20);
                sp28->unk24->unk18 = alHeapDBAlloc(NULL, 0, arg3, 1, 0x20);
                sp28->unk24->unk24 = 0.0f;
                sp28->unk24->unk28 = 1;
            } else {
                sp28->unk24 = NULL;
                sp34 += 1;
                sp34 += 1;
            }
            if (sp2C[sp34] != 0) {
                sp28->unk20 = alHeapDBAlloc(NULL, 0, arg3, 1, 0x38);
                sp28->unk20->unk2C = alHeapDBAlloc(NULL, 0, arg3, 1, 8);
                sp28->unk20->unk30 = alHeapDBAlloc(NULL, 0, arg3, 1, 8);
                sp28->unk20->base.unk0 = (s16)sp2C[sp34];
                sp34 += 1;
                _init_lpfilter((SynLPFilter *)sp28->unk20);
            } else {
                sp28->unk20 = NULL;
                sp34 += 1;
            }
            sp36 += 1;
        } while (sp36 < (s32)sp24->unk8);
    }
}
