// spawnFlagLookup (src/global/135D30.c): spawnFlagLookup (src/global/135D30.c): stage 6, 30 insns, diff 6/30 (park 8 -> 6 with 's32 i;' + 'for (i = 0; ...)'): only i+1 in a1 (uopt candidate sharing e's a1) vs ring temp t3 in target. Tried: i/i+1 spellings (++i, i=*arg2=i+1, k=i+1 copy, i+=1, i=i+1U), u8/s16/u32 i, decl order, dead-test sweep + hill-climb (e/i/val/arg tests, x=x defs): none beat 6
extern FlagTableEntry D_80755DA8[];

s32 spawnFlagLookup(s16 arg0, s16 arg1, s32 *arg2) {
    FlagTableEntry *e; s32 n = 0x1F; s32 i; s16 val = arg0;
    *arg2 = 0; for (i = 0; i < n; ) {
        e = D_80755DA8 + i;
        if (val == e->unk0 && arg1 == e->unk2) {
            return e->unk4;
        }
        *arg2 = i + 1;
        i++;
    }
    return -1;
}
