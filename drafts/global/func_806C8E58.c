// func_806C8E58 (src/global/CC800.c): G00 stage 6: only regs differ (8 rows): target i=v0, &D_8074E77C[idx]=v1, found a1, row ptr a2; ours i=v1, ptr a3 (uopt trace -l 5: a ghost CSE candidate for (u8)((i+1)&255), adjsave 30, takes v0 first, pushes i to v1 and ptr to a3). Tried: s32/int/u8 callee return, s32/u32 i, u8* local for the flag ptr, i^=0 / found^=0 / dead ptr uses, while/for forms, decl order, unchained store (worse), 480s permuter (no gain, base 40).
void func_806C8F8C(void *);

void func_806C8E58(s16 arg0) {
    s32 found;
    u8 i;

    found = 0;
    i = D_8074E77C[D_807FC929] = 0;
    do {
        if (arg0 == D_8075C410[i].unk0) {
            found = 1;
        } else {
            i = D_8074E77C[D_807FC929] = (i + 1) & 0xFF;
        }
    } while (found == 0);
    func_806C8F8C(&D_8075C410[i]);
}
