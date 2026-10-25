// func_806ED5C0 (src/global/EFDC0.c): stage 1: m2c reconstruction of actor-map event routing; stack-local source at 0x1A remains unresolved
s32 actorListFindIdByActor();                       /* extern */
? func_8061CC40(?, ?, ?);                           /* extern */
s32 func_8073110C(s16, ?);                          /* extern */
? func_8073129C(s16, ?, ?);                         /* extern */
extern s32 D_8076A0A8;

void func_806ED5C0(void *arg0) {
    u16 sp24;
    s32 sp18;
    s16 var_v0;
    s32 temp_v0;

    sp24 = (u16) arg0->unk58;
    temp_v0 = actorListFindIdByActor();
    switch (D_8076A0A8) {                           /* switch 1; irregular */
    case 26:                                        /* switch 1 */
        if (temp_v0 == 0x11) {
            return;
        }
    default:                                        /* switch 1 */
block_6:
        switch (sp24) {                             /* switch 2; irregular */
        case 0x19:                                  /* switch 2 */
            var_v0 = 0x169;
block_15:
            sp18 = (s32) var_v0;
            if (func_8073110C(var_v0, 0) == 0) {
                func_8061CC40(0, 0x16, 5);
                func_8073129C(unksp1A, 1, 0);
            }
            return;
        case 0x28:                                  /* switch 2 */
            var_v0 = 0x168;
            goto block_15;
        case 0x39:                                  /* switch 2 */
            var_v0 = 0x16B;
            goto block_15;
        case 0x38:                                  /* switch 2 */
            var_v0 = 0x16A;
            goto block_15;
        }
        break;
    case 48:                                        /* switch 1 */
        if (temp_v0 != 0x17) {
            goto block_6;
        }
        break;
    }
}
