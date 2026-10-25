// func_806F54E0 (src/global/F9450.c): Stage 3 semantic reconstruction: K&R s32 middle parameter and nested 0x306/0x5E action layout yield exact 0x30 frame/prologue and near-exact 0xB7 block; switch layout, call argument ordering, and signed return remain.
s32 func_805FF030(u8, s32);
s16 func_807319D8(s32, s32, u8);
s32 func_806C9974(u8, s8);
void func_8060DEC8(void);
void func_806F91B4(s32, u8, s32);
void func_80609140(s32, s32, f32, f32, s32, s32);
extern s8 D_80029FA0;
extern s8 D_80753EF2[];
extern u8 D_8076A0AB;
extern s32 D_807FBB64;

typedef struct {
    u8 pad0[6];
    u16 unk6;
    u8 pad8[0x56];
} F9L3_Action;

typedef struct {
    F9L3_Action actions[4];
    u8 pad178[0x18E];
} F9L3_PlayerData;

extern F9L3_PlayerData D_807FC950[];

void func_806F54E0(arg0, arg1, arg2)
s32 arg0;
s32 arg1;
u8 arg2;
{
    s32 pad;
    s32 temp_v0;
    u8 shouldComplete;

    shouldComplete = 0;
    if ((D_807FBB64 & 0x10000000) && (arg1 != 0x56)) {
        D_80029FA0--;
        return;
    }
    if (D_8076A0A8 != 0xF) {
        temp_v0 = func_806F544C(D_80753EF2[func_806F4E74(arg1) * 0x14], arg1, arg2);
        switch (arg1) {
        case 0xDD: case 0xDE: case 0xDF: case 0xE0: case 0xE1:
            func_8073129C(func_807319D8(0x1D5, func_805FF030(D_8076A0AB, 1), D_8074E77C[(u8)arg0]), 1, 0);
        case 0x74: case 0x288:
            func_806F91B4(temp_v0, arg0, 1);
            shouldComplete = 1;
            break;
        case 0x91: case 0x15D: case 0x15E: case 0x15F: case 0x160:
            if (D_807FC928 == 1) {
                func_80609140(0x331, 0x7FFF, 63.0f, 1.0f, 5, 0);
            }
        case 0xA: case 0xD: case 0x16: case 0x1E: case 0x1F:
            func_8073129C(0x18B, 1, 0);
            func_806F91B4(temp_v0, arg0, 1);
            break;
        case 0x1C: case 0x1D: case 0x23: case 0x24: case 0x27:
            func_8073129C(0x18C, 1, 0);
        case 0x98: case 0xEC: case 0x1D2:
            func_806F91B4(temp_v0, arg0, 1);
            break;
        case 0x56:
            func_8073129C(0x173, 1, 0);
            func_806F91B4(temp_v0, arg0, 1);
            break;
        case 0xB7:
            D_807FC950[(u8)arg0].actions[0].unk6 += 5;
            D_807FC950[(u8)arg0].actions[1].unk6 += 5;
            D_807FC950[(u8)arg0].actions[2].unk6 += 5;
            D_807FC950[(u8)arg0].actions[3].unk6 += 5;
            func_806F5498();
            break;
        case 0x8E:
            func_806F91B4(temp_v0, arg0, 0x96);
            break;
        case 0x57:
            func_806C9974(arg0, 1);
            break;
        case 0x13C: case 0x18D:
            shouldComplete = 1;
            break;
        }
        if (shouldComplete != 0) {
            func_8060DEC8();
        }
    }
}
