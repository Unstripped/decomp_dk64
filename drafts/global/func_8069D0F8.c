// func_8069D0F8 (src/global/9DD70.c): stage 6: instruction-for-instruction identical except the float temp is spilled at 0x28 instead of 0x2C (one stack slot); everything else matches
extern Actor *D_807FBB40;
extern Actor *D_807FBB44;

typedef struct M2_Sub {
    void *unk0;
    u16 unk4;
    u16 unk6;
    u8 unk8;
    u8 unk9;
    u8 unkA;
} M2_Sub;

s32 actorSpawn(s32, s32);
s32 func_806FDB8C(s16, s32, s32, f32, f32, f32);
s32 func_806FBD5C(s16, s32);
Mtx *func_80610FE8(s32);
extern s16 D_80744490;
extern Actor *D_807FBB44;

void func_8069D0F8(u8 arg0, s16 arg1, s16 arg2, s32 arg3, u16 arg4, u16 arg5, u8 arg6, u8 arg7) {
    s32 len;
    M2_Sub *sub;

    if (actorSpawn(0xE8, 0) != 0) {
        sub = D_807FBB44->unk174;
        if (arg0 & 0x80) {
            f32 f = (f32)arg2;
            sub->unkA = func_806FDB8C((s16)(arg0 & 0xFF7F), arg3, 2, 160.0f, f, 0.0f);
            *(s16 *)((u8 *)D_807FBB44 + 0xEE) = 1;
            D_807FBB44->unk80 = f;
            return;
        }
        if (arg1 == 0) {
            D_807FBB44->unk7C = (f32)((D_80744490 - func_806FBD5C((s16)arg0, arg3)) * 2);
        } else {
            D_807FBB44->unk7C = (f32)(arg1 * 4);
        }
        D_807FBB44->unk80 = (f32)(arg2 * 4);
        D_807FBB44->unk84 = (f32)arg0;
        D_807FBB44->unk16A = 0xFF;
        D_807FBB44->unk16B = 0xFF;
        D_807FBB44->unk16C = 0xFF;
        len = strlen((char *)arg3) + 1;
        sub->unk0 = func_80610FE8(len);
        _strcpy((char *)sub->unk0, (char *)arg3);
        sub->unk4 = arg4;
        sub->unk6 = arg5;
        sub->unk8 = arg6;
        sub->unk9 = arg7;
    }
}
