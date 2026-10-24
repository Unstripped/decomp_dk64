// func_806AB808 (src/global/ACDC0.c): stage 4: frame 0x58 and buf/flag slots match, but expected keeps idx/list in a2/a3 (spilled) and recomputes list+idx*0x18 three times; ours caches it in t-regs and spill slots shift. Permuter 420s no gain. Parked NON_MATCHING
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

typedef struct M1TextEntry {
    /* 0x00 */ f32 unk0;
    /* 0x04 */ f32 unk4;
    /* 0x08 */ s16 unk8;
    /* 0x0A */ s16 unkA;
    /* 0x0C */ s16 unkC;
    /* 0x0E */ s16 unkE;
    /* 0x10 */ u8 unk10;
    /* 0x11 */ char unk11[7];
} M1TextEntry; // size = 0x18

extern M1TextEntry *D_807FC7F0[2];
extern s8 D_807FC7F8[2];
void _sprintf(char *, const char *, ...);
s32 func_806FBD5C(s32, void *);
extern u8 D_807FC810;
f32 sqrtf(f32);

void func_806AB808(M1HudEntry *arg0, s16 arg1, s16 arg2, s16 arg3, s16 arg4, s32 arg5, s32 arg6, s32 arg7) {
    s32 pad;
    s32 idx;
    u8 *src;
    u8 *dst;
    s32 i;
    f32 len;
    M1TextEntry *list;
    s8 flag;
    u8 buf[11];

    flag = 0;
    if (arg7 & 0x80) {
        flag = 1;
        arg7 &= ~0x80;
    }
    switch (arg7) {
    case 1:
        _sprintf((char *)buf, "%02d", arg5);
        break;
    case 2:
        _sprintf((char *)buf, "%d", arg5);
        arg3 -= func_806FBD5C(1, buf) >> 1;
        break;
    default:
        _sprintf((char *)buf, "%d", arg5);
        break;
    }
    if (flag != 0) {
        arg3 -= func_806FBD5C(1, buf);
    }
    D_807FC810 = func_806FBD5C(1, buf);
    idx = D_807FC7F8[arg0->unk15];
    list = D_807FC7F0[arg0->unk15];
    len = sqrtf((640.0f - (f32)(arg1 * 4)) * (640.0f - (f32)(arg1 * 4)) + (480.0f - (f32)(arg2 * 4)) * (480.0f - (f32)(arg2 * 4)));
    list[idx].unk0 = -((640.0f - (f32)(arg1 * 4)) / len) * (1040.0f - len);
    list[idx].unk4 = -((480.0f - (f32)(arg2 * 4)) / len) * (1040.0f - len);
    list[idx].unk8 = arg1;
    list[idx].unkA = arg2;
    list[idx].unkC = arg3;
    list[idx].unkE = arg4;
    list[idx].unk10 = arg6;
    i = 0;
    src = buf;
    dst = (u8 *)&list[idx];
    if (buf[0] != 0) {
        do {
            dst[0x11] = src[0];
            i++;
            dst++;
            src++;
        } while (src[0] != 0);
    }
    ((u8 *)&list[idx])[0x11 + i] = 0;
    D_807FC7F8[arg0->unk15]++;
}
