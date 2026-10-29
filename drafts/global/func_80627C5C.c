// func_80627C5C (src/global/2C910.c): stage 5 (6 diff lines: only the two uopt spill slots 0x38/0x34 sit at 0x34/0x30; text size 5504 = target, all regs/insns identical, frame 0xD8, callee-saved {s0}). Cause: cfe temp var created by 'idx = X' assignment-as-arg (needed for the target's double sll/sra narrowing) and by 's += strlen()' (needed for addu s0,s0,v0) takes one extra home word above the spills; target has only idx+s homes (+pad at 0x30). Key finds: real boot/3630.c prototypes (u8 *_strncpy(u8*,u8*,u32), u32 _strcspn(u8*,char*), u8 *_strchr, u32 strlen with (s32)strlen(s)/2); one s16 var idx for both blocks. Tried: n/len s16/s32 user vars, comma exprs, block-scoped s/idx, register s, arg0 reuse, decl orders: none removes the temp word without losing the narrowing shape.
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
