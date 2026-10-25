// func_806C8E58 (src/global/CC800.c): stage 6, only regs (8 rows): target i=v0 ptr=v1 found=a1 row=a2; ours i=v1 ptr=a3 (ghost CSE cand for (u8)((i+1)&255), adjsave 30 > i 16, takes v0 first; target colors i then ptr before found/row). Tried (this + earlier runs): s32/u8 i/found, while(!found), if-order, explicit row var, flag ptr local (any decl order), dead loads/ifs of i and flag, unchained stores (worse), K&R s16 param, 2 permuter runs 480s+900s (28k its) no gain
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
