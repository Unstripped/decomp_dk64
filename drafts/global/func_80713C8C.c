// func_80713C8C (src/global/117190.c): Stage 2: countdown state update and timed completion logic recovered; 64-bit expression shape and frame differ.
typedef struct R117d2TimedState { s32 unk0; u32 unk4; s32 unk8; s32 unkC; u8 unk10; u8 unk11; } R117d2TimedState;
extern s32 D_807445B0;
extern u32 D_807445B4;
extern R117d2TimedState D_80755340;
extern u16 D_80755358[];
extern s32 D_807FBB60;
s32 func_8073110C(s32, s32);
void sfxAllocateChannel(s32, f32);
void func_80609140(s32, s32, f32, f32, s32, s32);

void func_80713C8C(void) {
    s32 temp_t0;
    u32 temp_t3;
    u64 temp_ret;
    u64 elapsed;
    D_8075531C = 1;
    if (D_80755340.unk10 != 0) {
        if (func_8073110C(0x302, 0) != 0) { func_8071261C(); sfxAllocateChannel(0x74, 1.0f); return; }
        temp_t3 = D_80755340.unk4 + D_807445B4;
        D_80755340.unk0 = (s32)((temp_t3 < D_807445B4) + D_80755340.unk0 + D_807445B0);
        D_80755340.unk4 = temp_t3;
        if (!(D_807FBB60 & 2)) {
            temp_ret = osGetTime();
            elapsed = (temp_ret - ((u64)D_80755340.unk0 << 32 | D_80755340.unk4)) * 64;
            temp_t0 = D_80755340.unkC - (u32)(elapsed / 3000 / 1000000);
            D_80755340.unk8 = temp_t0;
            if ((D_80755340.unk11 < 0xA) && (temp_t0 == D_80755358[D_80755340.unk11])) { func_80609140(0x2D4, 0x7FFF, 63.0f, 1.0f, 0, 0); D_80755340.unk11++; }
            if (D_80755340.unk8 <= 0) func_807127B4();
        }
    }
}
