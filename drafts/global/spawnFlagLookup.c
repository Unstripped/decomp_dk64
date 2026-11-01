// func_80731784 (src/global/135D30.c): stage 6: 30 insns, diff 6/30 (score full=6 text=6): resolved a0..a3 regalloc (a0=arg0, a1=e, a3=arg1); only i+1 in t3 vs a1 remains
extern FlagTableEntry D_80755DA8[];

s32 func_80731784(s16 arg0, s16 arg1, s32 *arg2) {
    FlagTableEntry *e; s32 n = 0x1F; s32 i = 0; s16 val = arg0;
    *arg2 = 0; for (; i < n; ) {
        e = D_80755DA8 + i;
        if (val == e->unk0 && arg1 == e->unk2) {
            return e->unk4;
        }
        *arg2 = i + 1;
        i++;
    }
    return -1;
}
