// func_80713C8C (src/global/117190.c): Matched TEXT OK: model timestamp as u64 time and accumulate the u64 global directly; relocation is D_807445B0+4 versus D_807445B4.
typedef struct {
    u64 time;
    s32 unk8;
    s32 duration;
    u8 active;
    u8 index;
} R117hTimedState;

extern u64 D_807445B0;
extern R117hTimedState D_80755340;
extern u16 D_80755358[];
extern u32 D_807FBB60;
s32 func_8073110C(s32, s32);
void sfxAllocateChannel(s32, f32);
void func_80609140(s32, s32, f32, f32, s32, s32);

void func_80713C8C(void) {
    u64 elapsed;

    D_8075531C = 1;
    if (D_80755340.active != 0) {
        if (func_8073110C(0x302, 0) != 0) {
            func_8071261C();
            sfxAllocateChannel(0x74, 1.0f);
            return;
        }
        D_80755340.time += D_807445B0;
        if (!(D_807FBB60 & 2)) {
            elapsed = (osGetTime() - D_80755340.time) * 64;
            D_80755340.unk8 = D_80755340.duration - (u32)(elapsed / 3000 / 1000000);
            if (((u32)D_80755340.index < 0xA) && (D_80755340.unk8 == D_80755358[D_80755340.index])) {
                func_80609140(0x2D4, 0x7FFF, 63.0f, 1.0f, 0, 0);
                D_80755340.index++;
            }
            if (D_80755340.unk8 <= 0) {
                func_807127B4();
            }
        }
    }
}
