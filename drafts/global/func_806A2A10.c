// func_806A2A10 (src/global/A7710.c): stage 6: missing only 'or t6,a0; sh t6,0x1A' narrow home of the s16 first param (plus its scheduling knock-on); ANSI/K&R/u16/s32+s16-local/volatile variants all omit it
/* func_806A2A10 (src/global/A7710.c) - stage 6, 2 instructions short.
 * Target prologue: sw a0,0x18; sw a1,0x1C; sw a2,0x20; `move t6,a0; sh t6,0x1A`;
 * addiu a0,0xB0; `sb a2,0x23`; jal actorSpawn (a1=0 in delay slot). The s16 first
 * parameter gets BOTH a word home (0x18) and a narrow halfword home (0x1A, the low
 * half of the same slot) and is later reloaded with `lh a3,0x1A`; the u8 third
 * parameter likewise gets `sb a2,0x23`. This source emits every instruction of the
 * body identically but only the u8 narrow home.
 * Probed without producing the `or t6,a0; sh t6,0x1A` pair: ANSI (s16,s16,u8),
 * K&R definition, u16 first param, u16/s16 with casts, s32 first param + s16 local,
 * `id` local declared/folded, `(s16)` casts, address-taken/volatile locals.
 * Nothing needs a local slot (frame is only 0x18, ra at 0x14), so 0x1A can only be
 * arg0's own home; IDO simply does not narrow-home an s16 param here.
 */
extern Actor *D_807FBB40;
extern Actor *D_807FBB44;
extern void *D_807FD580;
s32 actorSpawn(s32, s32);

void func_806A2A10(s16 arg0, s16 arg1, u8 arg2) {
    s16 id;

    id = arg0;
    actorSpawn(0xB0, 0);
    if (id & 0x8000) {
        D_807FBB44->unk15F = 0xB;
        arg2--;
    } else {
        D_807FBB44->unk15F = 6;
    }
    D_807FBB40->unk11C = (void *)D_807FBB44;
    *(s32 *)((u8 *)D_807FD580 + 0x1A8) = (s32)D_807FBB44;
    *(s32 *)((u8 *)D_807FBB44->unk174 + 0xC) = arg2;
    D_807FBB44->unk7C = (f32)(s16)(id & 0x7FFF);
    D_807FBB44->unk80 = (f32)arg1;
    D_807FBB44->unk154 = 1;
    D_807FBB44->unk128 = 0;
}
