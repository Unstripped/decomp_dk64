// _decodeChunk (src/global/144E00.c): matched: loop product must evaluate loop[1] before (loop[0] << 1); exact 0x28 frame, outer-switch s0, zero-fill reuse, RAW type-1 restart reload, and control flow
void _decodeChunk(DecodeFilter *filter, s32 paramID, DecodeWave *wave) {
    DecodeFilter *temp;

    temp = filter;
    switch (paramID) {
    case 5:
        temp->wave = wave;
        temp->unk3C = temp->wave->unk0;
        temp->unk30 = 0;
        switch (temp->wave->pad8[0]) {
        case 0:
            temp->wave->unk4 = (temp->wave->unk4 / 9) * 9;
            temp->unk24 = (temp->wave->loop[1] * (temp->wave->loop[0] << 1)) * 8;
            if (temp->wave->book != NULL) {
                temp->unk14 = temp->wave->book->unk0;
                temp->unk18 = temp->wave->book->unk4;
                temp->unk1C = temp->wave->book->unk8;
                bcopy((u8 *)temp->wave->book + 0xC, temp->out, 0x20);
            } else {
                temp->unk14 = temp->unk18 = temp->unk1C = 0;
            }
            break;
        case 1:
            if (temp->wave->book != NULL) {
                temp->unk14 = temp->wave->book->unk0;
                temp->unk18 = temp->wave->book->unk4;
                temp->unk1C = temp->wave->book->unk8;
            } else {
                temp->unk14 = temp->unk18 = temp->unk1C = 0;
            }
            break;
        default:
            break;
        }
        break;
    case 4:
        temp->unk34 = 0;
        temp->unk38 = 1;
        temp->unk30 = 0;
        if (temp->wave != NULL) {
            temp->unk3C = temp->wave->unk0;
            if (temp->wave->pad8[0] == 0) {
                if (temp->wave->book != NULL) {
                    temp->unk1C = temp->wave->book->unk8;
                }
            } else if (temp->wave->pad8[0] == 1) {
                if (temp->wave->book != NULL) {
                    temp->unk1C = temp->wave->book->unk8;
                }
            }
        }
        break;
    default:
        break;
    }
}
