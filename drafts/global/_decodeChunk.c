// _decodeChunk (src/global/144E00.c): stage 4: decoder layout correct through ADPCM init; remaining zero-copy local and RAW restart control-flow shape
void _decodeChunk(void *arg0, s32 arg1, s32 *arg2) {
    void *sp24;
    s32 *temp_t6;
    s32 temp_s0_2;
    s32 temp_s0_3;
    u8 temp_s0;
    void *temp_t2;

    sp24 = arg0;
    switch (arg1) {                                 /* switch 1; irregular */
    case 5:                                         /* switch 1 */
        sp24->unk20 = arg2;
        sp24->unk3C = (s32) *sp24->unk20;
        sp24->unk30 = 0;
        temp_s0 = sp24->unk20->unk8;
        switch (temp_s0) {                          /* switch 2; irregular */
        case 0:                                     /* switch 2 */
            temp_t6 = sp24->unk20;
            temp_t6->unk4 = (s32) (((s32) temp_t6->unk4 / 9) * 9);
            temp_t2 = sp24->unk20->unk10;
            sp24->unk24 = (s32) (temp_t2->unk0 * 2 * temp_t2->unk4 * 8);
            if (sp24->unk20->unkC != 0) {
                sp24->unk14 = (s32) *sp24->unk20->unkC;
                sp24->unk18 = (s32) sp24->unk20->unkC->unk4;
                sp24->unk1C = (s32) sp24->unk20->unkC->unk8;
                bcopy(sp24->unk20->unkC + 0xC, sp24->unk10, 0x20);
            } else {
                sp24->unk1C = 0;
                temp_s0_2 = sp24->unk1C;
                sp24->unk18 = temp_s0_2;
                sp24->unk14 = temp_s0_2;
            }
            break;
        case 1:                                     /* switch 2 */
            if (sp24->unk20->unkC != 0) {
                sp24->unk14 = (s32) *sp24->unk20->unkC;
                sp24->unk18 = (s32) sp24->unk20->unkC->unk4;
                sp24->unk1C = (s32) sp24->unk20->unkC->unk8;
            } else {
                sp24->unk1C = 0;
                temp_s0_3 = sp24->unk1C;
                sp24->unk18 = temp_s0_3;
                sp24->unk14 = temp_s0_3;
            }
            break;
        }
        break;
    case 4:                                         /* switch 1 */
        sp24->unk34 = 0;
        sp24->unk38 = 1;
        sp24->unk30 = 0;
        if (sp24->unk20 != NULL) {
            sp24->unk3C = (s32) *sp24->unk20;
            if (sp24->unk20->unk8 == 0) {
                if (sp24->unk20->unkC != 0) {
                    sp24->unk1C = (s32) sp24->unk20->unkC->unk8;
                }
            } else if ((sp24->unk20->unk8 == 1) && (sp24->unk20->unkC != 0)) {
                sp24->unk1C = (s32) sp24->unk20->unkC->unk8;
            }
        }
        break;
    }
}
