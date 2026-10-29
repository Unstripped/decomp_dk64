// func_8071D784 (src/global/11BC10.c): Fx11BG copy C (agent stopped: subagent credits ran out), deadsweep score full=6 vs expected; earlier note: Stage 3: compiled velocity/matrix behavior; target frame is 0xD0 and preserves fs0, while draft local/matrix allocation differs.
void func_8071D784(TimedEffectActorView *arg0, s8 *arg1) {
    f32 sp90[4][4];
    f32 sp50[4][4];
    f32 sp48;
    f32 sp44;
    f32 sp40;

    if (arg0->unk384 == NULL) {
        arg0->unk384 = func_80610FE8(0xC);
        guRotateF(sp90, -(f32) ((func_806119A0() % 36000U) / 1000U), 1.0f, 0.0f, 0.0f);
        guRotateF(sp50, (f32) ((arg0->unk35C * 360) / 4096), 0.0f, 1.0f, 0.0f);
        guMtxCatF(sp90, sp50, sp90);
        guMtxXFMF(sp90, 0.0f, 0.0f, D_80755678, &sp48, &sp44, &sp40);
        ((Fx11BGVelocityState *) arg0->unk384)->unk0 = sp48;
        ((Fx11BGVelocityState *) arg0->unk384)->unk4 = sp44;
        ((Fx11BGVelocityState *) arg0->unk384)->unk8 = sp40;
    }
    arg0->unk340 = arg0->unk340 + ((Fx11BGVelocityState *) arg0->unk384)->unk0;
    arg0->unk344 = arg0->unk344 + ((Fx11BGVelocityState *) arg0->unk384)->unk4;
    ((Fx11BGVelocityState *) arg0->unk384)->unk4 = ((Fx11BGVelocityState *) arg0->unk384)->unk4 + D_80755674;
    arg0->unk348 = arg0->unk348 + ((Fx11BGVelocityState *) arg0->unk384)->unk8;
    if (arg0->unk344 <= ((Fx11BGPlayerView *) D_807FBB4C)->unk80) {
        *arg1 = 1;
    }
}
