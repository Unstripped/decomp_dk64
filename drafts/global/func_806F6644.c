// func_806F6644 (src/global/F9450.c): Stage 1 m2c starter; reviewed 217-instruction target control flow.
s32 hashTableLookup(s16, u8 *);                     /* extern */
extern ? D_8074E77C;
extern s32 D_807F6000;
extern s32 D_807FC924;
extern u8 D_807FC929;
extern ? D_807FC952;

s32 func_806F6644(s16 arg0, ? arg1, s32 arg2) {
    s32 temp_t6;
    s32 var_v0;
    u8 temp_a0;

    temp_t6 = arg2 & 0xFFFF;
    switch (temp_t6) {                              /* irregular */
    case 0x11:
        if ((*(&D_807FC952 + ((D_807FC929 * 0x306) + (*(&D_8074E77C + D_807FC929) * 0x5E))) & 3) != 3) {
            return 0;
        }
    default:
block_18:
        temp_a0 = (D_807F6000 + (hashTableLookup(arg0) * 0x90))->unk8C;
        if ((temp_a0 & 8) && ((D_807FC924 + (D_807FC929 * 0x2F0))->unk4->unk58 != 2)) {
            return 0;
        }
        if ((temp_a0 & 2) && ((D_807FC924 + (D_807FC929 * 0x2F0))->unk4->unk58 != 3)) {
            return 0;
        }
        if ((temp_a0 & 4) && ((D_807FC924 + (D_807FC929 * 0x2F0))->unk4->unk58 != 5)) {
            return 0;
        }
        if ((temp_a0 & 0x10) && ((D_807FC924 + (D_807FC929 * 0x2F0))->unk4->unk58 != 4)) {
            return 0;
        }
        var_v0 = 1;
        if ((temp_a0 & 1) && ((D_807FC924 + (D_807FC929 * 0x2F0))->unk4->unk58 != 6)) {
            var_v0 = 0;
        }
        return var_v0;
    case 0x8F:
        if (!(*(&D_807FC952 + ((D_807FC929 * 0x306) + (*(&D_8074E77C + D_807FC929) * 0x5E))) & 1)) {
            return 0;
        }
        goto block_18;
    case 0x98:
        if (!((D_807FC924 + (D_807FC929 * 0x2F0))->unk4->unk174->unk1F4 & 1)) {
            return 0;
        }
        goto block_18;
    case 0x8E:
        if (!((D_807FC924 + (D_807FC929 * 0x2F0))->unk4->unk174->unk1F4 & 2)) {
            return 0;
        }
        goto block_18;
    case 0x90:
        if (((hashTableLookup(arg0, &D_807FC929) * 0x90) + D_807F6000)->unk7C->unk64 != 0xFF) {
            return 0;
        }
        goto block_18;
    }
}
