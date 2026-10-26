// func_806136B4 (src/global/17B90.c): stage 1: m2c starter; needs concrete allocation-state structs and exact free-call types
? animListFree(void *);                             /* extern */
? func_80613794(void *, ?);                         /* extern */
? func_80613944(void *, s32);                       /* extern */
? heapFreeDeferred(void *, void *);                 /* extern */

void func_806136B4(void *arg0) {
    void *temp_a1;
    void *temp_a1_2;
    void *temp_a1_3;

    func_80613794(NULL);
    func_80613794(arg0, 1);
    func_80613794(arg0, 2);
    animListFree(arg0 + 0x158);
    func_80613944(arg0, arg0->unk4->unk0);
    func_80613944(arg0, arg0->unk4->unk4);
    func_80613944(arg0, arg0->unk4->unk8);
    func_80613944(arg0, arg0->unk4->unkC);
    temp_a1 = arg0->unk4->unk1C;
    if (temp_a1 != NULL) {
        heapFreeDeferred(temp_a1, temp_a1);
    }
    temp_a1_2 = arg0->unk4->unk20;
    if (temp_a1_2 != NULL) {
        heapFreeDeferred(temp_a1_2, temp_a1_2);
    }
    temp_a1_3 = arg0->unk4->unk24;
    if (temp_a1_3 != NULL) {
        heapFreeDeferred(temp_a1_3, temp_a1_3);
    }
    heapFreeDeferred(arg0->unk4);
}
