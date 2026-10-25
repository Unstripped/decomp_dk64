// func_806F54E0 (src/global/F9450.c): Stage 3: recovered both jump-table dispatches and B7 player-block increments; C trial compiles but has a 0x28 frame and premature s16 argument sign extension versus target 0x30/full a1 spill.
extern s32 func_805FF030(u8, s32);
extern void func_80609140(s32, s32, f32, f32, s32, s32);
extern void func_8060DEC8(void);
extern void func_806C9974(u8, s32);
extern s32 func_806F4E74(s16);
extern s32 func_806F544C(s8, s32, u8);
extern void func_806F5498(s32, s32);
extern void func_806F91B4(s32, u8, s32);
extern void func_8073129C(s16, s32, s32);
extern s16 func_807319D8(s32, s32, u8);
extern s8 D_80029FA0;
extern s8 D_80753EF2[];
extern u8 D_8076A0AB;
extern s32 D_807FBB64;

void func_806F54E0(u8 arg0, s16 arg1, u8 arg2) {
    s32 sp28;
    u8 sp27;
    sp27 = 0;
    if ((D_807FBB64 & 0x10000000) && (arg1 != 0x56)) { D_80029FA0--; return; }
    if (D_8076A0A8 != 0xF) {
        sp28 = func_806F544C(D_80753EF2[func_806F4E74(arg1) * 0x14], arg1, arg2);
        switch (arg1) {
        case 0xDD: case 0xDE: case 0xDF: case 0xE0: case 0xE1:
            func_8073129C(func_807319D8(0x1D5, func_805FF030(D_8076A0AB, 1), D_8074E77C[arg0]), 1, 0);
        case 0x74: case 0x288: func_806F91B4(sp28, arg0, 1); sp27 = 1; break;
        case 0x91: case 0x15D: case 0x15E: case 0x15F: case 0x160:
            if (D_807FC928 == 1) func_80609140(0x331, 0x7FFF, 63.0f, 1.0f, 5, 0);
        case 0xA: case 0xD: case 0x16: case 0x1E: case 0x1F:
            func_8073129C(0x18B, 1, 0); func_806F91B4(sp28, arg0, 1); break;
        case 0x1C: case 0x1D: case 0x23: case 0x24: case 0x27: func_8073129C(0x18C, 1, 0);
        case 0x98: case 0xEC: case 0x1D2: func_806F91B4(sp28, arg0, 1); break;
        case 0x56: func_8073129C(0x173, 1, 0); func_806F91B4(sp28, arg0, 1); break;
        case 0xB7: func_806F5498(1, arg1); break;
        case 0x8E: func_806F91B4(sp28, arg0, 0x96); break;
        case 0x57: func_806C9974(arg0, 1); break;
        case 0x13C: case 0x18D: sp27 = 1; break;
        }
        if (sp27 != 0) func_8060DEC8();
    }
}
