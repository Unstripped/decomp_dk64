// func_807063B8 (src/global/109660.c): stage 1 typed 0x18-byte temp-copy reconstruction; compiles, but source/output layout and frame differ
typedef struct {
    f32 unk0;
    u32 unk4;
    f32 unk8;
    u32 unkC;
    f32 unk10;
    u32 unk14;
} R2F109660cRect;

void func_807063B8(R2F109660cRect *arg0, u8 *arg1, s32 arg2, f32 arg3) {
    R2F109660cRect temp[4];
    R2F109660cRect *src;
    R2F109660cRect *current;
    R2F109660cRect *other;
    s32 i;
    u8 output;
    s32 selected;

    selected = arg2 & 0xFF;
    output = 0;
    if (*arg1 > 0) {
        for (i = 0, src = arg0; i < *arg1; i++, src++) {
            R2F109660cRect tmp = *src;
            temp[i] = tmp;
        }
    }
    if (*arg1 > 0) {
        for (i = 0; i < *arg1; i++) {
            current = &temp[i];
            if ((current->unk0 < 0.0f) || (arg3 < current->unk8)) {
                other = &temp[selected ^ 1];
                arg0[output].unk0 = (current->unk0 < 0.0f) ? current->unk0 + arg3 : current->unk0;
                arg0[output ^ selected].unk0 = other->unk0;
                arg0[output].unk8 = arg3;
                arg0[output ^ selected].unk8 = other->unk8;
                arg0[output].unk10 = current->unk10;
                arg0[output ^ selected].unk10 = other->unk10;
                output = (output + 1) & 0xFF;
                arg0[output].unk0 = 0.0f;
                arg0[output ^ selected].unk0 = other->unk0;
                arg0[output].unk8 = (current->unk0 < 0.0f) ? current->unk8 : current->unk8 - arg3;
                arg0[output ^ selected].unk8 = other->unk8;
                arg0[output].unk10 = arg0[output - 1].unk10 + (arg3 - arg0[output - 1].unk0);
                arg0[output ^ selected].unk10 = other->unk10;
                output = (output + 1) & 0xFF;
            } else {
                R2F109660cRect tmp = temp[i];
                arg0[output] = tmp;
                output = (output + 1) & 0xFF;
            }
        }
    }
    *arg1 = output;
}
