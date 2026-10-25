// func_806FAB20 (src/global/FCCD0.c): stage 4: semantic graphics-list draft; pointer initialization and s1 placement remain
? func_806F9518(s32);                               /* extern */
void *func_806FA5A4(s32, void *);                   /* extern */
void *func_806FA7BC(s32, void *);                   /* extern */
void *func_806FA9C0(s32, void *);                   /* extern */
extern ? D_2000180;
extern s32 D_80754280;
extern u8 D_807FC928;

void *func_806FAB20(void *arg0) {
    s32 temp_v0;
    s32 var_s0;
    s32 var_s2;
    void *temp_s1;
    void *var_s1;
    void *var_v0;

    if ((s32) D_807FC928 >= 2) {
        return arg0;
    }
    temp_s1 = arg0 + 8;
    arg0->unk0 = 0xE7000000;
    arg0->unk4 = 0;
    arg0->unk8 = 0xDA380003;
    temp_s1->unk4 = &D_2000180;
    var_s1 = temp_s1 + 8;
    var_s0 = 0;
    var_s2 = 0;
    do {
        temp_v0 = (D_80754280 + var_s2)->unk20;
        switch (temp_v0) {                          /* irregular */
        case 0:
            func_806F9518(var_s0);
            break;
        case 1:
            var_v0 = func_806FA5A4(var_s0, var_s1);
block_12:
            var_s1 = var_v0;
            break;
        case 2:
            var_v0 = func_806FA7BC(var_s0, var_s1);
            goto block_12;
        case 3:
            var_v0 = func_806FA9C0(var_s0, var_s1);
            goto block_12;
        }
        var_s0 += 1;
        var_s2 += 0x30;
    } while (var_s0 != 0xF);
    return var_s1;
}
