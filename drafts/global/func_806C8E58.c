// func_806C8E58 (src/global/CC800.c): G00: only reg diff: i in v1/ptr a3 vs target v0/v1 (i = D_8074E77C[D_807FC929] = (i+1)&0xFF form from permuter fixes temp t3). 40 score permuter no better.

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
