// func_8070DA74 (src/global/112080.c): stage 2: queue removal candidate compiled; initial global-load and traversal shape differ
// func_8070DA74: stage-2 m2c reconstruction; typed private-copy attempt compiled.
void func_8070DA74(void *arg0) {
    void *sp2C;
    void *sp28;
    void **var_v1;
    void *temp_a0_2;
    void *temp_v0;
    void *var_s0;
    void *var_s2;
    void *var_v0;
    void *temp_a0;
    void *temp_v0_2;

    var_v1 = &D_807550C4;
    var_s2 = NULL;
    if ((D_807550C4 != NULL) && (arg0 != *D_807550C4)) {
        var_v0 = D_807550C4;
        do {
            var_v1 = &*(var_v0 + 0xC);
            var_v0 = *(var_v0 + 0xC);
        } while ((var_v0 != NULL) && (arg0 != *var_v0));
    }
    temp_v0 = *var_v1;
    if (temp_v0 != NULL) {
        var_s2 = temp_v0;
        *var_v1 = temp_v0->unkC;
    }
    if (var_s2 != NULL) {
        temp_v0_2 = var_s2->unk4;
        temp_a0 = temp_v0_2->unk174;
        sp2C = temp_v0_2;
        sp28 = temp_a0;
        func_8070DA28(temp_a0);
        func_8070D970(sp28->unk8);
        var_s0 = var_s2->unk8;
        if (var_s0 != NULL) {
            do {
                temp_a0_2 = var_s0;
                var_s0 = var_s0->unk4;
                heapFreeDeferred(temp_a0_2);
            } while (var_s0 != NULL);
        }
        heapFreeDeferred(var_s2);
        heapFreeDeferred(sp28->unk34);
        actorDespawn(sp2C);
        arg0->unk60 &= 0xFDFFFFFF;
    }
}
