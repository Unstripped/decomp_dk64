// func_806F2C48 (src/global/F56F0.c): Stage 4: all target blocks/calls/entry stores recovered, including sin/cos decomposition. Checked candidate is 16 bytes long: target frame 0x30, draft frame 0x38; remaining differences are local spill placement and register allocation.
typedef struct F5CState16 { u8 pad0[0x16]; s16 unk16; } F5CState16;
typedef struct F5CTurnActor { u8 pad0[0x6A]; u16 unk6A; u8 pad6C[0xDC - 0x6C]; s16 unkDC; s16 unkDE; u8 padE0[6]; s16 unkE6; } F5CTurnActor;
typedef struct F5CTurnEntry { s8 unk0; u8 unk1; s16 unk2; s16 unk4; s16 unk6; } F5CTurnEntry;
#define F5C_S16 ((F5CState16 *)D_807FD580)
extern s16 func_806CC10C(s16, s16);
extern f32 func_80612790(s16);
extern f32 func_80612794(s16);
void func_806F2C48(F5CTurnActor *arg0, F5CTurnEntry *arg1, s32 *arg2) {
    s32 entry_index;
    s16 angle;
    s16 magnitude;
    u16 scaled;
    s32 v;
    f32 sine;
    f32 amplitude;
    f32 factor;
    f32 cosine;
    entry_index = *arg2;
    if (arg0->unk6A & 1) {
        F5C_S16->unk16 += 2;
        if (F5C_S16->unk16 >= 0x80) F5C_S16->unk16 = 0x7F;
    } else {
        F5C_S16->unk16 -= 2;
        if (F5C_S16->unk16 < 0) F5C_S16->unk16 = 0;
    }
    if (F5C_S16->unk16 != 0) {
        magnitude = (0x400 - arg0->unkDE) & 0xFFF;
        if (magnitude >= 0x156) magnitude = 0x155;
        scaled = magnitude * 0x10;
        angle = func_806CC10C(arg0->unkE6, (arg0->unkDC - 0x800) & 0xFFF);
        sine = func_80612790(angle);
        factor = (f32)scaled;
        amplitude = sine * factor;
        cosine = func_80612794(angle);
        v = (s8)((F5C_S16->unk16 * 6) / 10);
        if (v != 0) {
            arg1[entry_index].unk1 = 1;
            arg1[entry_index].unk4 = 0;
            arg1[entry_index].unk0 = v;
            arg1[entry_index].unk2 = (s16)amplitude;
            arg1[entry_index].unk6 = (s16)((-cosine) * factor);
            entry_index += 1;
        }
        v = (s8)((F5C_S16->unk16 * 3) / 10);
        if (v != 0) {
            arg1[entry_index].unk1 = 2;
            arg1[entry_index].unk4 = 0;
            arg1[entry_index].unk0 = v;
            arg1[entry_index].unk2 = (s16)amplitude;
            arg1[entry_index].unk6 = (s16)((-cosine) * factor);
            entry_index += 1;
        }
    }
    *arg2 = entry_index;
}
