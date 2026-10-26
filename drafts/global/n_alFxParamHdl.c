// n_alFxParamHdl (src/global/141EF0.c): stage 6: correct 0x30 frame and 339-instruction size; unsigned float conversions added, remaining mismatch is GPR allocation across switch/shared paths
s32 n_alFxParamHdl(FxNMParamState *arg0, s32 arg1, s32 *arg2) {
    FxNMParamState *sp2C;
    u32 sp28;
    s32 sp24;
    s32 sp20;
    f32 sp1C;

    sp2C = arg0;
    sp28 = arg1 & 7;
    sp24 = arg1 >> 3;
    sp20 = *arg2;
    if (sp24 >= sp2C->unk8) {
        return 0;
    }
    switch (sp28) {
    case 0:
        sp2C->unk4[sp24].unk0 = ((sp20 * D_807563E4->unk40) / 1000) & ~7;
        break;
    case 1:
        sp2C->unk4[sp24].unk4 = ((sp20 * D_807563E4->unk40) / 1000) & ~7;
        break;
    case 2:
        sp2C->unk4[sp24].unkA = sp20;
        break;
    case 3:
        sp2C->unk4[sp24].unk8 = sp20;
        break;
    case 4:
        sp2C->unk4[sp24].unkC = sp20;
        break;
    case 5:
        sp2C->unk4[sp24].unk10 = (((f32)sp20 / 1000.0f) * 2.0f) / (f32)D_807563E4->unk40;
        break;
    case 6:
        sp1C = (f32)sp20;
        break;
    case 7:
        if (sp2C->unk4[sp24].unk20 != NULL) {
            *(s16 *)sp2C->unk4[sp24].unk20 = sp20;
            _init_lpfilter(sp2C->unk4[sp24].unk20);
        }
        break;
    }
    if ((u32)sp2C->unk4[sp24].unk0 >= (u32)(sp2C->unk0 - 0x10)) {
        sp2C->unk4[sp24].unk0 = sp2C->unk0 - 0x10;
    }
    if ((u32)sp2C->unk4[sp24].unk0 >= (u32)(sp2C->unk0 - 8)) {
        sp2C->unk4[sp24].unk0 = sp2C->unk0 - 8;
    }
    if ((u32)sp2C->unk4[sp24].unk0 >= (u32)sp2C->unk4[sp24].unk4) {
        sp2C->unk4[sp24].unk4 = sp2C->unk4[sp24].unk0 + 8;
    }
    if (sp2C->unk4[sp24].unk24 != NULL) {
        if (sp28 != 6) {
            if (sp2C->unk4[sp24].unk4 - sp2C->unk4[sp24].unk0 != 0) {
                sp1C = (sp2C->unk4[sp24].unk1C / (f32)(u32)(sp2C->unk4[sp24].unk4 - sp2C->unk4[sp24].unk0)) * 173123.4062f;
            } else {
                sp1C = 0.0f;
            }
        }
        sp2C->unk4[sp24].unk1C = (f32)(u32)(sp2C->unk4[sp24].unk4 - sp2C->unk4[sp24].unk0) * (sp1C / 173123.4062f);
    }
    return 0;
}
