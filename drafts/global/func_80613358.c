// func_80613358 (src/global/17B90.c): stage 1: m2c starter; attempted concrete types, but pointer expression/register allocation differs
? memcpy(void *, void *, ?, void *);                /* extern */

void func_80613358(void *arg0, s32 arg1, void *arg2) {
    void *temp_a0;

    if (!(arg0->unk60 & 0x10) && ((temp_a0 = (arg1 * 8) + *arg0->unk0->unk4, (temp_a0->unk0 != arg2->unk0)) || (temp_a0->unk4 != arg2->unk4))) {
        memcpy(temp_a0, arg2, 8, arg2);
    }
}
