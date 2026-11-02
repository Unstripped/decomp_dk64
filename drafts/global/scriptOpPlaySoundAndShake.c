// scriptOpPlaySoundAndShake (src/global/19A00.c): UNPARKED 2026-11-02: park was 204 insns vs target 206 (count-inexact parks stay drafts); stage 4, still 16 diff lines (as1 only; regs match): target has bne v1,2; nop; lh t2 (no hoist of lh t2/li at,1/li a1,10/li a2,8 into the entry stall/delay slot) and bnezl v1 + copied lw t8,88(s0) at the else-if with lbu t6 kept in the block (so mtc1 zero,f8 hoists into the lbu gap); ours hoists all of them. as1probe: dup of the first bne record + swapping the lbu v1,72(sp)/b records gives 7; deleting the first load of the ==0 arm gives bnezl; no C spelling found. Tried (all unchanged 16): x = x/| 0/& MASK/dead tests on every local at every boundary up to depth 3, all single/pair LINE-JOINs, wrapper blocks (do-while/if(1)/for/switch) per arm, switch(selector) (111), mode local (u8/s32/u32, pad as mode), statement order permutations per arm, FP spellings, var_v1 types, cond spellings (|| && ! cast), arm-1 if forms, permuter (junk baseline).
s32 scriptOpPlaySoundAndShake(Actor *arg0) {
    s16 sp4E;
    u8 sp4D;
    s16 sp4A;
    u8 sp49;
    u8 var_v1;
    u8 pad;

    D_807F5AF0++;
    scriptReadU16((u8 *)&sp4E);
    scriptReadU8(&sp4D);
    scriptReadU16((u8 *)&sp4A);
    scriptReadU8(&sp49);
    if (((PlayerSoundView *)gPlayerSlots)[((GlobalSoundState *)gActivePlayerState)->unk1A4].unk2C0 == 2) {
        var_v1 = 0xA;
        if (sp4E == 1) {
            sp4D = (u32)((f64)(u32)sp4D * 0.5);
        }
        camStartShakeFromPoint(((GlobalSoundState *)gActivePlayerState)->unk104, 0xA, 8, ((ActorSoundPosView *)arg0)->unk7C, ((ActorSoundPosView *)arg0)->unk80, ((ActorSoundPosView *)arg0)->unk84, 100.0f, 800.0f);
    } else if (((PlayerSoundView *)gPlayerSlots)[((GlobalSoundState *)gActivePlayerState)->unk1A4].unk2C0 == 0) {
        var_v1 = 0xFF;
        sp4D = (u32)((f64)(u32)sp4D * 0.5);
    } else {
        switch (arg0->unk58) {
        case 6:
        case 7:
            var_v1 = 0x46;
            break;
        case 8:
            var_v1 = 0x5A;
            break;
        case 2:
        case 4:
            var_v1 = 0x32;
            break;
        default:
            var_v1 = 0x50;
            break;
        }
    }
    sp4E = mapActionLookupEntry(sp4E, arg0, ((ActorSoundPosView *)arg0)->unk78);
    if ((sp4E == 2) || (sp4E == 8)) {
        sp49 = 0xA;
    }
    sfxPlayAtPositionPooled(arg0->unk7C, arg0->unk80, arg0->unk84, sp4E, (s32)sp4D, (s32)sp4A, (s32)sp49, (s32)var_v1, 0.3f, 0);
    return 1;
}
