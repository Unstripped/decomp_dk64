// func_8069A614 (src/global/9DD70.c): parked NON_MATCHING: missing dead 'sw a1,4(sp)' home-slot store (79 vs 78 insns)
typedef struct {
    u8 pad0[0x98];
    f32 unk98[4];
    f32 unkA8[4];
    u8 unkB8[4];
} M1ActorSlots;

void func_8069A614(f32 arg0, s32 arg1) {
    M1ActorSlots *slots = (M1ActorSlots *)D_807FBB40->unk174;
    s16 i;
    s32 found;
    f64 temp;

    arg1 &= 0xFF;
    found = 0;
    i = 0;
    do {
        if (slots->unkB8[i] == 0) {
            found = 1;
        } else {
            i++;
        }
    } while (i < 4 && found == 0);
    if (found != 0) {
        slots->unkB8[i] = 1;
        switch (arg1) {
        case 0:
            slots->unkA8[i] = 10.0f;
            temp = (f64)arg0 / 843.0;
            if (temp > 0.0) {
                slots->unk98[i] = (f32)temp;
                return;
            }
            slots->unk98[i] = (f32)-temp;
            return;
        case 1:
            slots->unkA8[i] = 12.0f;
            temp = (f64)arg0 / 480.0;
            if (temp > 0.0) {
                slots->unk98[i] = (f32)temp;
                return;
            }
            slots->unk98[i] = (f32)-temp;
            break;
        }
    }
}
