// func_80721814 (src/global/126260.c): stage 5 (parked NON_MATCHING): text 6304 bytes, frame 0x38 and same insn count; arg0 must be u8 (prototype in 126b NON_MATCHING block needs u8 first param); remaining ~79 reg-only lines: uopt phantom t2 candidate from FAKE dead-uses (unkE web t3 not t2, t-ring +1), f12/f0 and f14/f2 FP webs in the intensity block, and target's 'move t8,v0' before the 3rd slot_light color stores (div.s hoist) not reproduced; also u8 'if(arg0>=7)' with (u32) cast gave pointer regs right but sltiu
s32 func_80721814(u8 arg0, Command *arg1, f32 arg2, f32 arg3, f32 arg4, s16 arg5) {
    f32 dist;
    f64 dist_d;
    Light *lights;
    Ambient *ambient;
    Light *slot_light;
    f32 intensity;
    f64 clamped;
    f64 dy_d;
    u32 c;

    lights = (Light *)((u8 *)D_8076A048 + (D_807FDB75 * 0x78) + 0x278);
    ambient = (Ambient *)((u8 *)D_8076A048 + (D_807FDB75 * 0x78) + 0x270);
    slot_light = (Light *)((u8 *)D_8076A048 + (D_807FDB75 * 0x78) + (arg0 * 0x10) + 0x278);
    if (lights && lights) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)

    if (D_8076A048 == 0) {} // FAKE: makes the base load a uopt candidate (v1)
    if (arg0 >= 7) {
        return 0;
    }

    if (arg1->unkE == 5) {
        dist_d = sqrtf((arg2 - (f32)arg1->unk4) * (arg2 - (f32)arg1->unk4) + (arg4 - (f32)arg1->unk8) * (arg4 - (f32)arg1->unk8));
        dist = (dist_d > 0.001) ? dist_d : 0.001;
        intensity = (dist - (f32)((s32)arg1->unkA / 2) < 1.0) ? 1.0 : dist - (f32)((s32)arg1->unkA / 2);
        clamped = (f64)(f32)(u32)arg1->unkA / (0.5 * intensity * intensity);
        intensity = (clamped > 1.0) ? 1.0 : clamped;
        if ((f32)(arg1->unk6 + 50) < arg3) {
            dy_d = ((arg3 - (f32)arg1->unk6) - 50.0f > 20.0) ? 20.0 : (arg3 - (f32)arg1->unk6) - 50.0f;
            intensity = (f64)intensity * (1.0 - (dy_d / 20.0));
        }
    } else {
        dist_d = sqrtf((arg2 - (f32)arg1->unk4) * (arg2 - (f32)arg1->unk4) + (arg3 - (f32)arg1->unk6) * (arg3 - (f32)arg1->unk6) + (arg4 - (f32)arg1->unk8) * (arg4 - (f32)arg1->unk8));
        dist = (dist_d > 0.001) ? dist_d : 0.001;
        intensity = 1.0f;
    }

    if (arg1->unkE == 5) {
        if ((f64)intensity > 0.1) {
            if (ambient && ambient) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
            c = (u32)((f32)(u32)lights->l.col[0] + ((f32)(arg1->unkB - lights->l.col[0]) * intensity));
            lights->l.colc[0] = (s8)c;
            lights->l.col[0] = (u8)c;

            c = (u32)((f32)(u32)lights->l.col[1] + ((f32)(arg1->unkC - lights->l.col[1]) * intensity));
            lights->l.colc[1] = (s8)c;
            lights->l.col[1] = (u8)c;

            c = (u32)((f32)(u32)lights->l.col[2] + ((f32)(arg1->unkD - lights->l.col[2]) * intensity));
            lights->l.colc[2] = (s8)c;
            lights->l.col[2] = (u8)c;

            c = (u32)(((((f64)(u32)ambient->l.col[0] * 0.5) - (f64)(u32)ambient->l.col[0]) * (f64)intensity) + (f64)(u32)ambient->l.col[0]);
            ambient->l.colc[0] = (s8)c;
            ambient->l.col[0] = (u8)c;

            c = (u32)(((((f64)(u32)ambient->l.col[1] * 0.5) - (f64)(u32)ambient->l.col[1]) * (f64)intensity) + (f64)(u32)ambient->l.col[1]);
            ambient->l.colc[1] = (s8)c;
            ambient->l.col[1] = (u8)c;

            c = (u32)(((((f64)(u32)ambient->l.col[2] * 0.5) - (f64)(u32)ambient->l.col[2]) * (f64)intensity) + (f64)(u32)ambient->l.col[2]);
            ambient->l.colc[2] = (s8)c;
            ambient->l.col[2] = (u8)c;
        }
        return 0;
    }

    if ((f64)intensity > 0.02) {
        c = (u32)((f32)(u32)arg1->unkB * intensity);
        slot_light->l.colc[0] = (s8)c;
        slot_light->l.col[0] = (u8)c;

        c = (u32)((f32)(u32)arg1->unkC * intensity);
        slot_light->l.colc[1] = (s8)c;
        slot_light->l.col[1] = (u8)c;

        c = (u32)((f32)(u32)arg1->unkD * intensity);
        slot_light->l.colc[2] = (s8)c;
        slot_light->l.col[2] = (u8)c;

        slot_light->l.dir[0] = (s8)(s32)(((f32)arg1->unk4 - arg2) * (127.0f / dist));
        slot_light->l.dir[1] = (s8)(s32)(((f32)arg1->unk6 - arg3) * (127.0f / dist));
        slot_light->l.dir[2] = (s8)(s32)(((f32)arg1->unk8 - arg4) * (127.0f / dist));
        return 1;
    }

    return 0;
}
