// func_806F5270 (src/global/F9450.c): stage 3: recovered cleanup lists and frame; first-list pointer lifetime differs
? func_806F95C8();                                  /* extern */
? heapFree(void *);                                 /* extern */
extern void *D_80754244;
extern s16 D_807FD720;
extern void *D_807FD72C;
extern void *D_807FD730;

void func_806F5270(void) {
    s32 var_s2;
    s32 var_s3;
    void *temp_a0;
    void *temp_s0;
    void *temp_s0_2;
    void *temp_s1;
    void *var_s0;
    void *var_s1;
    void *var_s1_2;

    temp_a0 = D_80754244;
    if (temp_a0 != NULL) {
        var_s2 = 0;
        var_s3 = 0;
        if (D_807FD720 > 0) {
            do {
                var_s1 = *(temp_a0 + var_s3);
                if (var_s1 != NULL) {
                    do {
                        temp_s0 = var_s1->unk18;
                        heapFree(var_s1);
                        var_s1 = temp_s0;
                    } while (temp_s0 != NULL);
                }
                var_s2 += 1;
                var_s3 += 4;
            } while (var_s2 < D_807FD720);
        }
        heapFree(temp_a0);
        D_80754244 = NULL;
    }
    var_s1_2 = D_807FD72C;
    if (var_s1_2 != NULL) {
        do {
            temp_s0_2 = var_s1_2->unk18;
            heapFree(var_s1_2);
            var_s1_2 = temp_s0_2;
        } while (temp_s0_2 != NULL);
    }
    if (D_807FD730 != NULL) {
        var_s0 = D_807FD730;
        if (D_807FD730 != NULL) {
            do {
                temp_s1 = var_s0->unk1C;
                heapFree(var_s0);
                var_s0 = temp_s1;
            } while (temp_s1 != NULL);
        }
        D_807FD730 = NULL;
    }
    func_806F95C8();
}
