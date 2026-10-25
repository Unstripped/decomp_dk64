// func_806F6644 (src/global/F9450.c): Stage 6: branch and data access reconstruction; identical control flow with register-allocation differences.
s32 func_806F6644(s16 arg0, u8 arg1, u16 arg2) {
    u8 flags;

    switch (arg2) {
    case 0x11:
        if ((D_807FC952[D_807FC929 * 0x306 + D_8074E77C[D_807FC929] * 0x5E] & 3) != 3) {
            return 0;
        }
        break;
    case 0x8F:
        if ((D_807FC952[D_807FC929 * 0x306 + D_8074E77C[D_807FC929] * 0x5E] & 1) == 0) {
            return 0;
        }
        break;
    case 0x98:
        if ((F9F2_PLAYER[D_807FC929].unk4->unk174->unk1F4 & 1) == 0) {
            return 0;
        }
        break;
    case 0x8E:
        if ((F9F2_PLAYER[D_807FC929].unk4->unk174->unk1F4 & 2) == 0) {
            return 0;
        }
        break;
    case 0x90:
        if (*(s16 *)((u8 *)D_807F6000[hashTableLookup(arg0)].unk7C + 0x64) != 0xFF) {
            return 0;
        }
        break;
    }
    flags = D_807F6000[hashTableLookup(arg0)].unk8C;
    if ((flags & 8) && (F9F2_PLAYER[D_807FC929].unk4->unk58 != 2)) {
        return 0;
    }
    if ((flags & 2) && (F9F2_PLAYER[D_807FC929].unk4->unk58 != 3)) {
        return 0;
    }
    if ((flags & 4) && (F9F2_PLAYER[D_807FC929].unk4->unk58 != 5)) {
        return 0;
    }
    if ((flags & 0x10) && (F9F2_PLAYER[D_807FC929].unk4->unk58 != 4)) {
        return 0;
    }
    if ((flags & 1) && (F9F2_PLAYER[D_807FC929].unk4->unk58 != 6)) {
        return 0;
    }
    return 1;
}
