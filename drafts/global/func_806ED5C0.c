// func_806ED5C0 (src/global/EFDC0.c): from .scratch/EfN9/func_806ED5C0_best.c
typedef struct EfN9Actor58 {
    u8 pad0[0x58];
    s32 unk58;
} EfN9Actor58;

s32 func_8073110C(s16, s32);
void func_8073129C(s32, s32, s32);

void func_806ED5C0(Actor *arg0) {
    u16 sp24;
    s32 sp18;
    s32 var_v0;
    s32 temp_v0;

    sp24 = *(volatile s32 *)&((EfN9Actor58 *)arg0)->unk58;
    temp_v0 = actorListFindIdByActor(arg0);
    switch (D_8076A0A8) {
    case 26:
        if (temp_v0 == 0x11) {
            return;
        }
        break;
    case 48:
        if (temp_v0 == 0x17) {
            return;
        }
        break;
    }
    switch (sp24) {
    case 0x19:
        var_v0 = 0x169;
        break;
    case 0x28:
        var_v0 = 0x168;
        break;
    case 0x39:
        var_v0 = 0x16B;
        break;
    case 0x38:
        var_v0 = 0x16A;
        break;
    default:
        return;
    }
    sp18 = (s32)var_v0;
    if (func_8073110C((s16)sp18, 0) == 0) {
        func_8061CC40(NULL, 0x16, 5);
        func_8073129C((s16)sp18, 1, 0);
    }
}
