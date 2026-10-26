// func_80627C5C (src/global/2C910.c): stage 3 (best, norm diff 27 lines): K&R(u8,u16,u8) with (s16)arg1 in block1 -> (u16)arg1 spill at 0x34 now exists like target; two s16 vars len/idx (single var gets s1; two vars spill like target: callee-saved {s0}, frame 0xD8 match). Remaining: target uses one slot 0x42 for both idx vars (mine 0x42/0x40), spill temps at 0x34/0x38 vs mine 0x30/0x34 (target has an extra unused word at 0x30), block1 extra sll/sra/move narrowing in target; built 147 vs 148 insns.
s32 _strchr(u8 *, s32);
s32 _strcspn(u8 *, u8 *);
void _strncpy(u8 *, u8 *, s16);
s32 func_806FBD5C();
u8 *func_8070E750(s32, s32, s32);
void textSpawnMarkerChecked(s32, s32, s32, u8 *, s32, s32, s32, s32);
s32 strlen(u8 *);

void func_80627C5C(arg0, arg1, arg2)
u8 arg0;
u16 arg1;
u8 arg2;
{
    u8 sp98[0x40];
    u8 sp58[0x40];
    u8 sp44[0x14];
    s16 len;
    s16 idx;
    u8 *s;

    s = func_8070E750(1, arg0, 1);
    if (_strchr(s, 0x3A) != 0) {
        len = _strcspn(s, ":") + 1;
        _strncpy(sp44, s, len);
        sp44[len] = 0;
        textSpawnMarkerChecked(0xA, 0x14, 0x18, sp44, 0, (s16)arg1, 0x32, 0x32);
        func_80627C10(arg2);
        s += strlen(sp44);
    }
    if ((s16)func_806FBD5C(6, s) >= 0x12D) {
        idx = strlen(s) / 2;
        if (s[idx] != 0x20) {
            do {
                idx--;
            } while (s[idx] != 0x20);
        }
        _strncpy(sp98, s, idx);
        sp98[idx] = 0;
        _strncpy(sp58, s + idx + 1, 0xFF);
        textSpawnMarkerChecked(0, 0, 0xCD, sp98, 0, arg1, 0x32, 0x32);
        func_80627C10(arg2);
        textSpawnMarkerChecked(0, 0, 0xD7, sp58, 0, arg1, 0x32, 0x32);
        func_80627C10(arg2);
        return;
    }
    textSpawnMarkerChecked(0, 0, 0xCD, s, 0, arg1, 0x32, 0x32);
    func_80627C10(arg2);
}
