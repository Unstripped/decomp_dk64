#include "common.h"
#include "actor.h"

extern Actor *D_807FBB44;

typedef struct {
    u8 r;
    u8 g;
    u8 b;
} Rgb8;

const Rgb8 D_80757F70[8] = {
    { 0xFF, 0xFF, 0xFF },
    { 0xC8, 0x00, 0x32 },
    { 0xDC, 0xC8, 0x00 },
    { 0x32, 0xC8, 0x00 },
    { 0xCA, 0x5B, 0xFF },
    { 0x00, 0x96, 0xFF },
    { 0x32, 0x32, 0xFA },
    { 0x00, 0x00, 0x00 },
};

void actorSetTintFromPalette(u8 arg0) {
    D_807FBB44->unk16A = D_80757F70[arg0].r;
    D_807FBB44->unk16B = D_80757F70[arg0].g;
    D_807FBB44->unk16C = D_80757F70[arg0].b;
}

#ifdef NON_MATCHING
u8 *_strchr(u8 *, s32);
u32 _strcspn(u8 *, char *);
u8 *_strncpy(u8 *, u8 *, u32);
s32 textGetStringWidth();
u8 *func_8070E750(s32, s32, s32);
void textSpawnMarkerChecked(s32, s32, s32, u8 *, s32, s32, s32, s32);
u32 strlen(u8 *);

void func_80627C5C(arg0, arg1, arg2)
u8 arg0;
u16 arg1;
u8 arg2;
{
    u8 sp98[0x40];
    u8 sp58[0x40];
    u8 sp44[0x14];
    s16 idx;
    u8 *s;

    s = func_8070E750(1, arg0, 1);
    if (_strchr(s, 0x3A) != 0) {
        _strncpy(sp44, s, idx = _strcspn(s, ":") + 1);
        sp44[idx] = 0;
        textSpawnMarkerChecked(0xA, 0x14, 0x18, sp44, 0, (s16)arg1, 0x32, 0x32);
        actorSetTintFromPalette(arg2);
        s += strlen(sp44);
    }
    if ((s16)textGetStringWidth(6, s) >= 0x12D) {
        idx = (s32)strlen(s) / 2;
        if (s[idx] != 0x20) {
            do {
                idx--;
            } while (s[idx] != 0x20);
        }
        _strncpy(sp98, s, idx);
        sp98[idx] = 0;
        _strncpy(sp58, s + idx + 1, 0xFF);
        textSpawnMarkerChecked(0, 0, 0xCD, sp98, 0, arg1, 0x32, 0x32);
        actorSetTintFromPalette(arg2);
        textSpawnMarkerChecked(0, 0, 0xD7, sp58, 0, arg1, 0x32, 0x32);
        actorSetTintFromPalette(arg2);
        return;
    }
    textSpawnMarkerChecked(0, 0, 0xCD, s, 0, arg1, 0x32, 0x32);
    actorSetTintFromPalette(arg2);
}
#else

#pragma GLOBAL_ASM("asm/global/nonmatchings/2C910/func_80627C5C.s")
#endif

extern Actor *D_807FBB4C;
Actor *spawnNodeActivate(s16, s32);

Actor *actorFromSpawnNodeOrDefault(s16 arg0) {
    Actor *v;

    if (arg0 != 0) {
        v = spawnNodeActivate(arg0, 0);
    }
    if ((arg0 == 0) || (v == 0)) {
        v = D_807FBB4C;
    }
    return v;
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/2C910/func_80627F04.s")

extern Actor *D_807FBB40;

s32 currentActorTestClearFlag(void) {
    s32 r = 0;

    if (D_807FBB40->unk6A & 0x100) {
        D_807FBB40->unk6A &= 0xFEFF;
        r = 1;
    }
    return r;
}

void currentActorClearFlag(void) {
    D_807FBB40->unk6A &= 0xFEFF;
}
