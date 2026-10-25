// func_806F12FC (src/global/F56F0.c): Behavioural draft; target hoists arg0->unk174 after testing unk58 and uses branch-likely delay load, while equivalent C retains an extra branch.
typedef struct F5AActorExtra {
    u8 pad0[0x1F0];
    s32 unk1F0;
} F5AActorExtra;

void func_80613214();
void sfxStopChannel(s32, s32);

void func_806F12FC(Actor *arg0) {
    F5AActorExtra *extra;

    if (arg0->unk58 == 6) {
        extra = arg0->unk174;
        func_80613214();
        sfxStopChannel(0x6C, 0);
    } else {
        extra = arg0->unk174;
    }
    extra->unk1F0 &= ~0x40;
}
