// func_806AB4EC (src/global/ACDC0.c): stage 6: one instruction differs: jal func_806119FC delay slot is 'move a0,a2' vs expected nop (expected keeps the switch-variable copy in a0 from before the switch; any explicit var copy gets coalesced into a2). Dead param arg1 reused as scratch for the alloc size (a declared local n shifts spill slots 4 bytes). Parked NON_MATCHING
typedef struct M1HudEntry {
    /* 0x00 */ u8 pad0[8];
    /* 0x08 */ s16 unk8[2];
    /* 0x0C */ s16 unkC[2];
    /* 0x10 */ u8 pad10[2];
    /* 0x12 */ s8 unk12;
    /* 0x13 */ u8 pad13;
    /* 0x14 */ s8 unk14;
    /* 0x15 */ s8 unk15;
} M1HudEntry;

void *func_80610FE8(s32);

typedef struct M1TextObj {
    /* 0x000 */ u8 pad0[0x340];
    /* 0x340 */ f32 unk340;
    /* 0x344 */ f32 unk344;
    /* 0x348 */ u8 pad348[0x18];
    /* 0x360 */ f32 unk360;
    /* 0x364 */ f32 unk364;
    /* 0x368 */ u8 pad368[2];
    /* 0x36A */ u8 unk36A;
    /* 0x36B */ u8 unk36B;
    /* 0x36C */ u8 unk36C;
    /* 0x36D */ u8 pad36D[0x17];
    /* 0x384 */ f32 *unk384;
} M1TextObj;

extern s8 D_807FC80F;
void func_806AC07C();
void func_80714998(u8);
void func_8071495C(void);
void func_807149FC(s32);
void func_80714950(void *);
void func_8071498C(void (*)());
void func_80714A28(s32);
M1TextObj *func_80714CC0(s32, f32, f32, f32, f32);
s32 func_806FACE8(s32);
f32 func_806119FC(s32);
f32 sqrtf(f32);

void func_806AB4EC(M1HudEntry *arg0, s32 arg1, s32 arg2, s32 arg3, f32 arg4, u8 arg5, s32 arg6) {
    M1TextObj *obj;
    f32 *buf;
    f32 dx;
    f32 dy;
    f32 len;
    f32 fy;

    func_80714998(arg5);
    func_8071495C();
    func_807149FC(-1);
    func_80714950(arg0);
    func_8071498C(func_806AC07C);
    func_80714A28(0x101);
    if (arg1 < 0) {
        fy = arg2;
        obj = func_80714CC0(arg1, arg4, fy, (f32)arg3, -10.0f);
    } else {
        fy = arg2;
        obj = func_80714CC0(func_806FACE8(arg1), arg4, fy, (f32)arg3, -10.0f);
    }
    arg1 = 7;
    if (arg6 == 6) {
        arg1 = 10;
    }
    buf = func_80610FE8(arg1 * 4);
    obj->unk384 = buf;
    if (arg6 == 9) {
        arg6 = 7;
        obj->unk360 = -obj->unk360;
    }
    arg6 = arg6;
    buf[0] = arg6;
    buf[1] = arg0->unk15;
    buf[2] = obj->unk340;
    buf[3] = obj->unk344;
    switch (arg6) {
    case 1:
    case 2:
    case 7:
    case 13:
        dx = 640.0f - buf[2];
        dy = 480.0f - buf[3];
        len = sqrtf(dx * dx + dy * dy);
        buf[4] = -(dx / len) * (1040.0f - len);
        buf[5] = -(dy / len) * (1040.0f - len);
        buf[6] = obj->unk364;
        if (arg6 == 13) {
            buf[0] = 2.0f;
            obj->unk36C = 0;
            obj->unk36B = 0;
            obj->unk36A = 0xFF;
        }
        break;
    case 6:
        buf[4] = 0.0f;
        buf[5] = 0.0f;
        buf[6] = 0.0f;
        buf[7] = 0.0f;
        buf[8] = func_806119FC(arg6) * 4096.0f;
        if (arg2 < 0xA0) {
            obj->unk360 = -obj->unk360;
        }
        buf[9] = 0.0f;
        break;
    case 10:
        buf[2] = fy;
        break;
    case 14:
        buf[0] = 3.0f;
        obj->unk36C = 0;
        obj->unk36B = 0;
        obj->unk36A = 0xFF;
    default:
        buf[4] = arg4;
        buf[5] = 0.0f;
        break;
    }
    if (D_807FC80F == 0) {
        obj->unk36A = 0x64;
        obj->unk36B = 0x64;
        obj->unk36C = 0x64;
    }
    D_807FC80F = 1;
}
