// func_806A2E30 (src/global/A7710.c): stage 1-2: complete C transcription (timer countdown display: 3-way switch on unk154, sprintf %.2d formats, rotation ramp). Compiles to 2160 of 3312 bytes; block order/regalloc and the sprintf buffer/stack layout still differ. func_806A36F4 (empty) included after it.
/* func_806A2E30 (src/global/A7710.c): stage 1 - structurally complete C transcribed
   from the asm/m2c (three-way switch on actor->unk154, countdown timer formatting,
   rotation ramp). Not yet block-ordered/regalloc-matched; saved as the starting point.
   func_806A36F4 (the empty function at 0x806A36F4) follows this function. */
typedef struct A7R2TimerState {
    /* 0x00 */ s32 unk0;      /* timer, high word */
    /* 0x04 */ u32 unk4;      /* timer, low word */
    /* 0x08 */ u32 unk8;
    /* 0x0C */ s32 unkC;
    /* 0x10 */ u8 unk10;
} A7R2TimerState;

extern Actor *D_807FBB40;
extern s32 D_807445B0;
extern u32 D_807445B4;
extern s32 D_807476C8;
extern u32 D_807476CC;
extern s32 D_8076A0A8;
extern s32 D_807FC7D0;
extern u32 D_807FC7D4;
extern u8 D_807FC7D8;

u64 __ll_mul(u64, u64);
u64 __ull_div(u64, u64);
u64 __ull_rem(u64, u64);
f64 __ull_to_d(u64);
s32 _sprintf(char *, char *, ...);
void func_80609140(s32, s32, f32, f32, s32, s32);
s32 func_80611A44(void);
f32 func_806FDA8C(s32);
void func_806FDAB8(s32, f32);
u8 func_806FDB8C(s16, char *, u8, s32, f32, f32);
void func_806FDF1C(s32, char *);
void renderCallbacksRegister(void *, Actor *, s32);
s32 strlen(char *);
void func_806A2B90(Gfx *, Actor *);

void func_806A2E30(void) {
    A7R2TimerState *sub;
    char text[0x24];
    f32 sp84;
    f32 sp80;
    f32 ang;
    s32 sp4C;
    u32 elapsedHi;
    u32 elapsedLo;
    u64 now;
    u64 ticks;
    u64 secs;
    u8 mode;
    u8 cnt;
    s32 lim;

    sub = D_807FBB40->unk174;
    if (!(D_807FBB40->unk60 & 0x10)) {
        if (D_807FBB40->unk15F == 6) {
            _sprintf(text, "%.2d", sub->unkC);
        } else {
            _sprintf(text, "%.2d:%.2d:00", (u32)sub->unkC / 60U, (u32)sub->unkC % 60U);
        }
        mode = D_807FBB40->unk15F;
        sub->unk10 = func_806FDB8C(mode == 0xB ? 6 : 3, text, mode, 0, 0.0f, 0.0f);
    }
    if (D_807FBB40->unk154 == 3) {
        now = osGetTime();
        sub->unk4 = (u32)now - D_807FC7D4;
        sub->unk0 = (s32)(now >> 32) - D_807FC7D0 - ((u32)now < D_807FC7D4);
        D_807FBB40->unk154 = 2;
        D_807FBB40->unk155[0] = 1;
    }
    elapsedLo = sub->unk4 + D_807445B4;
    elapsedHi = (elapsedLo < D_807445B4) + sub->unk0 + D_807445B0;
    sub->unk0 = elapsedHi;
    sub->unk4 = elapsedLo;
    if (D_807FBB40->unk15F == 0xB) {
        u32 t = elapsedLo + D_807476CC;
        sub->unk0 = (t < D_807476CC) + elapsedHi + D_807476C8;
        sub->unk4 = t;
    }
    now = osGetTime();
    ticks = __ll_mul(now - *(u64 *)&sub->unk0, 0x40);
    secs = __ull_div(ticks, 0xBB8);
    sub->unk8 = __ull_div(secs, 0xF4240);
    if (D_807476C8 == 0 && D_807476CC == 0) {
        D_807FC7D8 = __ull_rem(__ull_div(secs, 0x2710), 0x64);
    }
    sp84 = ((f32)(s32)((func_806FDA8C(sub->unk10) - 1.5707964f) / 3.1415927f) * 3.1415927f) + 3.1415927f + 1.5707964f;
    ang = (f32)((((f64)__ull_to_d(secs) / 10000.0) / 100.0) * 3.1415927410125732 + 1.5707963705062866);
    sp80 = ang;
    func_806FDAB8(sub->unk10, 0.0f);
    sp4C = sub->unkC - sub->unk8;
    switch (D_807FBB40->unk154) {
    case 1:
        if (D_807FBB40->unk128 < 0xFF) {
            if (D_807FBB40->unk128 + 3 >= 0x100) {
                D_807FBB40->unk128 = 0xFF;
            } else {
                D_807FBB40->unk128 = D_807FBB40->unk128 + 3;
            }
        }
        func_806FDAB8(sub->unk10, 1.5707964f);
        D_807FBB40->unk168 = 0;
        break;
    case 4:
        D_807FBB40->unk154 = 2;
        D_807FBB40->unk155[0] = 0xFF;
        /* fallthrough */
    case 2:
        if (D_807FBB40->unk155[0] == 0) {
            D_807FBB40->unk155[0] = D_807FBB40->unk155[0] + 1;
            now = osGetTime();
            sub->unk0 = (s32)(now >> 32);
            sub->unk4 = (u32)now;
            sub->unk8 = 0;
            ang = 1.5707964f;
        }
        lim = sub->unkC - sub->unk8;
        if (lim >= 0) {
            sp80 = ang;
            sp4C = lim;
            func_806FDAB8(sub->unk10, ang < 0.0f ? 0.0f : ang);
            *(f64 *)D_807FBB40->unk160 = ang < 0.0f ? 0.0 : (f64)ang;
            if (sp84 <= ang) {
                if ((s32)sub->unk8 >= sub->unkC
                    && (D_807FBB40->unk15F == 6 || sub->unkC < (s32)sub->unk8 || D_807FC7D8 >= 0x5B)) {
                    D_807FBB40->unk154 = 5;
                    D_807FBB40->unk155[0] = 0;
                } else if (D_807FBB40->unk15F == 6) {
                    if ((s32)(sp84 / 3.1415927f) & 1) {
                        func_80609140(0x8E, 0x58EF, 40.0f, 1.0f, 5, 0);
                    } else {
                        func_80609140(0x8F, 0x58EF, 40.0f, 1.0f, 5, 0);
                    }
                }
                if (sp4C == 0xA) {
                    D_807FBB40->unk154 = 4;
                }
            }
            if (D_807FBB40->unk15F == 6) {
                _sprintf(text, "%.2d", sp4C);
            } else if (D_807FBB40->unk154 != 5) {
                _sprintf(text, "%.2d:%.2d:%.2d", (u32)(sp4C / 60), (u32)(sp4C % 60), 0x63 - D_807FC7D8);
            } else {
                _sprintf(text, "00:00:00");
            }
            D_807FBB40->unk168 = strlen(text);
            func_806FDF1C(sub->unk10, text);
        } else {
            D_807FBB40->unk154 = 5;
            D_807FBB40->unk155[0] = 0;
            func_806FDF1C(sub->unk10, "00:00:00");
        }
        break;
    case 5:
        switch (D_8076A0A8) {
        case 0x35: case 0x49: case 0x9B: case 0x9C: case 0x9D:
        case 0x9E: case 0x9F: case 0xA0: case 0xA1: case 0xA2:
            cnt = D_807FBB40->unk155[0];
            switch (cnt) {
            case 0: case 7: case 14: case 21: case 28: case 35: case 42:
                func_80609140(0x3BD, 0x7FFF, 40.0f, 1.15f, 1, 0x80);
                cnt = D_807FBB40->unk155[0];
                break;
            }
            D_807FBB40->unk155[0] = cnt + 1;
            break;
        default:
            if (D_807FBB40->unk155[0] == 0) {
                func_80609140(0x1BB, 0x7FFF, 40.0f, 1.0f, 0, 0);
                D_807FBB40->unk155[0] = D_807FBB40->unk155[0] + 1;
            }
            break;
        }
        D_807FBB40->unk168 = 0;
        if (sp4C <= 0 && sp4C >= -2) {
            func_806FDAB8(sub->unk10,
                          (f32)(((f64)((func_80611A44() >> 0xF) % 180) / 180.0) * 3.1415927410125732
                                + 1.5707963705062866));
        }
        break;
    }
    renderCallbacksRegister((void *)func_806A2B90, D_807FBB40, 7);
}

void func_806A36F4(void) {
}
