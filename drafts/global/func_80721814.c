// func_80721814 (src/global/126260.c): stage 5 (parked NON_MATCHING, R2Lru1): insn count/frame/t-regs now identical (diff 79 -> ~10 real lines, 4 more are .rodata-reloc ldc1 only); remaining: FP webs in the intensity block (target f2=first intensity web, f0=widen ring temp, f12=quotient web, f14=2nd intensity; mine merges to f14/f12/f0: a 2nd f32 local gives widen f0 but base f14, clamped f2 since clamped outranks base in adjsave; decl order/(0,X) wrappers/dead FP uses/permuter no help) and target keeps 'move t8,v0' value for BOTH 3rd slot_light colc/col stores (mine forwards v0 for the 2nd). Wins: (u32)arg0*0x10 kills phantom t2 candidate, (c & 0xFF) on every colc store restores the t-ring hidden touch, (f64)col + (...) operand order on ambient add.d
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
    slot_light = (Light *)((u8 *)D_8076A048 + (D_807FDB75 * 0x78) + ((u32)arg0 * 0x10) + 0x278); // FAKE: u32 cast splits the arg0 conversion candidate (no phantom t2)
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
            lights->l.colc[0] = (c & 0xFF); // FAKE: no-op mask touches one ring temp
            lights->l.col[0] = (u8)c;

            c = (u32)((f32)(u32)lights->l.col[1] + ((f32)(arg1->unkC - lights->l.col[1]) * intensity));
            lights->l.colc[1] = (c & 0xFF); // FAKE: no-op mask touches one ring temp
            lights->l.col[1] = (u8)c;

            c = (u32)((f32)(u32)lights->l.col[2] + ((f32)(arg1->unkD - lights->l.col[2]) * intensity));
            lights->l.colc[2] = (c & 0xFF); // FAKE: no-op mask touches one ring temp
            lights->l.col[2] = (u8)c;

            c = (u32)((f64)(u32)ambient->l.col[0] + ((((f64)(u32)ambient->l.col[0] * 0.5) - (f64)(u32)ambient->l.col[0]) * (f64)intensity));
            ambient->l.colc[0] = (c & 0xFF); // FAKE: no-op mask touches one ring temp
            ambient->l.col[0] = (u8)c;

            c = (u32)((f64)(u32)ambient->l.col[1] + ((((f64)(u32)ambient->l.col[1] * 0.5) - (f64)(u32)ambient->l.col[1]) * (f64)intensity));
            ambient->l.colc[1] = (c & 0xFF); // FAKE: no-op mask touches one ring temp
            ambient->l.col[1] = (u8)c;

            c = (u32)((f64)(u32)ambient->l.col[2] + ((((f64)(u32)ambient->l.col[2] * 0.5) - (f64)(u32)ambient->l.col[2]) * (f64)intensity));
            ambient->l.colc[2] = (c & 0xFF); // FAKE: no-op mask touches one ring temp
            ambient->l.col[2] = (u8)c;
        }
        return 0;
    }

    if ((f64)intensity > 0.02) {
        c = (u32)((f32)(u32)arg1->unkB * intensity);
        slot_light->l.colc[0] = (c & 0xFF); // FAKE: no-op mask touches one ring temp
        slot_light->l.col[0] = (u8)c;

        c = (u32)((f32)(u32)arg1->unkC * intensity);
        slot_light->l.colc[1] = (c & 0xFF); // FAKE: no-op mask touches one ring temp
        slot_light->l.col[1] = (u8)c;

        c = (u32)((f32)(u32)arg1->unkD * intensity);
        slot_light->l.colc[2] = (c & 0xFF); // FAKE: no-op mask touches one ring temp
        slot_light->l.col[2] = (u8)c;

        slot_light->l.dir[0] = (s8)(s32)(((f32)arg1->unk4 - arg2) * (127.0f / dist));
        slot_light->l.dir[1] = (s8)(s32)(((f32)arg1->unk6 - arg3) * (127.0f / dist));
        slot_light->l.dir[2] = (s8)(s32)(((f32)arg1->unk8 - arg4) * (127.0f / dist));
        return 1;
    }

    return 0;
}
