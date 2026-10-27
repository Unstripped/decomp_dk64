// func_80025168 (src/jetpac/0.c): stage 5-6: frame 0x20 + s0 match; first 44 insns now match (a local 'zero' used for the 0 stores/args stops IDO CSEing &D_8002BA70 into v0; volatile s32 *p keeps the 3 stores to D_8002BA6C). Remaining diff is regalloc only: target value=a1, mfhi=t1, p=v0, pad ptr=v1/lb a0; mine value=v1, mfhi=v0, p=a2, pad ptr=a0/lb a1. Permuter hint: '(x) & 0xFFFFFFFFFFFFFFFF' on the first D_8002BA6C store gets 62 diff lines (vs 114) but is a hack, not used.
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
    *p = D_8002EC30.unk790;
    *p = D_8002EC30.unk790 % 60;
    *p = D_8002EC30.unk790 % 60 / 30;
    D_8002EC30.unk4 = D_8002EC30.unk0;
    D_8002EC30.unk0 = D_807ECDE8->unk0;
    if (D_807ECDE8->unk2 >= 0x1F) {
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
