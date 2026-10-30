// func_80616850 (src/global/19A00.c): stage 4: clean ScriptJumpState; only 14 insns regalloc diff (a1/v0 vs v0/v1)
s32 func_80616850(Actor *arg0) {
    s32 sp24;
    u16 sp22;
    ScriptJumpState *sp1C;

    sp1C = (ScriptJumpState *)arg0->unk4;
    sp24 = sp1C->unk88;
    D_807F5AF0++;
    scriptReadU16((u8 *)&sp22);
    sp1C->unk5C = sp1C->unk64;
    sp1C->unk60 = D_807F5AF0 - sp1C->unk68;
    actorScriptStart(arg0, sp22);
    D_807F5AF0 = sp1C->unk6C;
    sp1C->unk88 = sp24;
    return D_807F5AF4;
}
