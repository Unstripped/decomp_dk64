// func_800288A8 (src/critter/4840.c): C1 stage 3: frame 0xB8 needed; ours 0xC0/0xC8: locals region only 12 bytes in target (<=4 bytes of scalars: var_s1 u8 + v1 s16 named; step must be an unnamed CSE temp in t9, not a named local which lands in a2). arg2 reused as var_s0, arg1 as token, s16 v1 loop var (s32 gets unrolled).
s16 func_800288A8(TextData *arg0, char *arg1, s16 arg2) {
    s16 sp94[18];
    s16 sp70[18];
    char sp4C[36];
    u8 var_s1;
    s32 step;
    s16 v1;

    _strcpy(sp4C, arg1);
    step = (s32)(func_806FBD5C(6, (s32)_strtok(sp4C, " ")) * 0.5 * 4.0);
    sp70[0] = arg2;
    var_s1 = 1;
    sp94[0] = arg2 + step;
    arg2 = arg2 + step * 2 + 0x14;
    while ((arg1 = _strtok(NULL, " ")) != NULL) {
        step = (s32)(func_806FBD5C(6, (s32)arg1) * 0.5 * 4.0);
        sp70[var_s1] = arg2;
        sp94[var_s1] = arg2 + step;
        arg2 = arg2 + step * 2 + 0x14;
        var_s1++;
    }
    arg0->unk2 = var_s1;
    arg0->unk8 = (s16 *)func_80610FE8(var_s1 * 2);
    arg0->unk4 = (s16 *)func_80610FE8(var_s1 * 2);
    for (v1 = 0; v1 < var_s1; v1++) {
        arg0->unk4[v1] = sp70[v1];
        arg0->unk8[v1] = sp94[v1];
    }
    return sp94[0];
}
