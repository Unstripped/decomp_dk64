// func_8072D714 (src/global/12E800.c): stage 3: all opcodes/branches match except frame 0x20 vs target 0x28 (extra 8 unused local bytes), f64 spill regs (target raw f0 -> clamped f2, constant 2.0 in f12) and rodata reloc. Tried f/raw split, f32 x local, permuter 300s best 995.
extern u16 D_80744508;
extern s32 D_8076A0A8;
s32 mathAngleDistance(s16, s16);
void func_8072B59C(u8, s16, s32);
void func_8072D9D4(void);
void func_8002D7E8(s16);

typedef struct D1ActorViewI {
    /* 0x000 */ u8 pad0[4];
    /* 0x004 */ ActorSub4 *unk4;
    /* 0x008 */ u8 pad8[0x50];
    /* 0x058 */ s32 unk58;
    /* 0x05C */ u8 pad5C[2];
    /* 0x05E */ u8 pad5E[0xC];
    /* 0x06A */ u8 pad6A[0x4E];
    /* 0x0B8 */ f32 unkB8;
    /* 0x0BC */ u8 padBC[0x2A];
    /* 0x0E6 */ s16 unkE6;
    /* 0x0E8 */ u8 padE8[6];
    /* 0x0EE */ s16 unkEE;
    /* 0x0F0 */ u8 padF0[0x44];
    /* 0x134 */ s16 unk134;
    /* 0x136 */ u8 pad136[2];
    /* 0x138 */ u32 unk138;
} D1ActorViewI;

#define D1AI ((D1ActorViewI *)D_807FBB40)

s32 mathAngleDistance(s16, s16);
void func_8072B59C(u8, s16, s32);
void func_8072D9D4(void);
void func_8002D7E8(s16);

void func_8072D714(D1ActorViewI *arg0, s32 arg1) {
    f64 f;
    f64 raw;
    f32 x;

    if (arg0 != NULL) {
        raw = (D1AI->unk134 - 1) * -0.6;
        f = (2.0 < raw) ? 2.0 : raw;
        D1AI->unkEE = (arg0->unkEE + 0x800) & 0xFFF;
        if ((Actor *)arg0 == D_807FDC94) {
            if (mathAngleDistance(arg0->unkEE, arg0->unkE6) > 0x400) {
                D1AI->unkEE += 0x800;
            }
        }
        func_8072B59C(0x37, 0, arg1);
        x = 66.0f * (f32)(f + 0.5);
        if ((x < arg0->unkB8 ? arg0->unkB8 : x) < 150.0f) {
            D1AI->unkB8 = -(x < arg0->unkB8 ? arg0->unkB8 : x);
        } else {
            D1AI->unkB8 = -150.0f;
        }
        if (arg0->unk4 != NULL) {
            D1AI->unkB8 = D1AI->unkB8 * (arg0->unk4->unk38 / 0.15);
        }
    } else {
        func_8072B59C(0x37, 0, arg1);
        D1AI->unkB8 = -60.0f;
    }
    D1AI->unk138 &= 0xFFFF7FFF;
    D_807FBB40->unk60 &= 0xFFFF7FFF;
    if (arg0 == NULL || (Actor *)arg0 == D_807FDC94 || arg0->unk58 == 0x2B) {
        func_8072D9D4();
    }
    D_80744508++;
    if (D_8076A0A8 == 0xBF) {
        func_8002D7E8(*(s16 *)((u8 *)D_807FBB40 + 0x5A));
    }
}
