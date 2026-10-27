// func_80025168 (src/jetpac/0.c): stage 5-6: 12 -> 7 diff lines (frame/size/regs identical). Remaining: target p=v0 (lui v0..addiu v0 for D_8002BA6C), x%60 in ring temp t1; ours p=a0, rem=v0 (uopt candidate 1243 adjsave 3.0 colours before p adjsave 2.0). Found by permuter: 'if ((zero = D_807ECDE8->unk2) >= 0x1F)' (reuse of dead local) puts unk2 in a0. Kept (s64) cast on first store and 'if (0) {}'. Tried: local sec/rem of every int width, rem via zero/flag/arg0, no-op casts on 60/30 expressions (192 combos), if(!p){} dummies, p position, p cast; permuter 4x270s
typedef struct {
    u16 unk0;
    s8 unk2;
    s8 unk3;
} J0bPad;

extern u8 D_8002BA70;
extern J0bPad *D_807ECDE8;
void func_8002466C(s32);
void func_800248E8(s32);

void func_80025168(s32 arg0) {
    u8 flag;
    s32 zero;
    volatile s32 *p;

    zero = 0;
    if (D_8002BA70 != 0) {
        D_8002EC30.unk78C = 0;
        D_8002EC30.unk790 = 0;
        D_8002EC30.unk794 = 3;
        D_8002EC30.num_players = 1;
        D_8002EC30.unk34C = 0;
        D_8002BA70 = zero;
        D_8002EC30.high_score = func_8060C6B8(0x11, zero, zero, zero);
        flag = flagGet(0x61, 2);
        D_8002EC30.unk798 = flag;
        if (flag != zero) {
            D_8002EC30.unk799 = 0;
        }
    }
    p = &D_8002BA6C;
    *p = (s64)D_8002EC30.unk790;
    *p = D_8002EC30.unk790 % 60;
    *p = D_8002EC30.unk790 % 60 / 30;
    D_8002EC30.unk4 = D_8002EC30.unk0;
    D_8002EC30.unk0 = D_807ECDE8->unk0;
    if (0) {
    }
    if ((zero = D_807ECDE8->unk2) >= 0x1F) {
        D_8002EC30.unk0 |= 0x100;
    }
    if (D_807ECDE8->unk2 < -0x1E) {
        D_8002EC30.unk0 |= 0x200;
    }
    if (D_807ECDE8->unk3 >= 0x1F) {
        D_8002EC30.unk0 |= 0x800;
    }
    if (D_807ECDE8->unk3 < -0x1E) {
        D_8002EC30.unk0 |= 0x400;
    }
    D_8002EC30.unk8 = (D_8002EC30.unk0 ^ D_8002EC30.unk4) & D_8002EC30.unk0;
    if ((u32)D_8002EC30.unk794 < 3) {
        D_8002EC30.unk794++;
        return;
    }
    switch (D_8002EC30.unk78C) {
    case 0:
        func_8002466C(arg0);
        break;
    case 1:
        func_800248A0(arg0);
        break;
    case 2:
        func_800248E8(arg0);
        break;
    case 3:
        func_80024A8C(arg0);
        break;
    case 4:
        func_80024C90(arg0);
        break;
    case 5:
        func_80024D48(arg0);
        break;
    }
    D_8002EC30.unk790 = D_8002EC30.unk790 + 1;
}
