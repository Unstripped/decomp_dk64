// func_80721814 (src/global/126260.c): stage 3: exact 6304 bytes text and 64 bytes rodata match; 9 u32 float-to-int FCSR conversions and math reconstructed; remaining diff frame size (0x28 vs 0x38)
typedef struct {
    u8 unk0, unk1, unk2, unk3;
    u8 unk4, unk5, unk6, unk7;
    s8 unk8, unk9, unkA, padB[5];
} L126a_Light;

s32 func_80721814(s32 arg0, Command *arg1, f32 arg2, f32 arg3, f32 arg4) {
    L126a_Light *lights;
    L126a_Light *ambient;
    L126a_Light *slot_light;
    f32 dist;
    f32 intensity;
    f64 dist_d;
    f64 clamped;
    f64 dy_d;
    u32 c;

    lights = (L126a_Light *)((u8 *)D_8076A048 + (D_807FDB75 * 0x78) + 0x278);
    ambient = (L126a_Light *)((u8 *)D_8076A048 + (D_807FDB75 * 0x78) + 0x270);
    slot_light = (L126a_Light *)((u8 *)D_8076A048 + (D_807FDB75 * 0x78) + ((arg0 & 0xFF) * 0x10) + 0x278);

    if ((arg0 & 0xFF) >= 7) {
        return 0;
    }

    if (arg1->unkE == 5) {
        dist_d = sqrtf((arg2 - (f32)arg1->unk4) * (arg2 - (f32)arg1->unk4) + (arg4 - (f32)arg1->unk8) * (arg4 - (f32)arg1->unk8));
        dist = (dist_d > 0.001) ? dist_d : 0.001;
        clamped = (f64)(dist - (f32)((s32)arg1->unkA / 2));
        clamped = (f32)(clamped < 1.0 ? 1.0 : clamped);
        clamped = (f64)(u32)arg1->unkA / (0.5 * clamped * clamped);
        intensity = (clamped > 1.0) ? 1.0 : clamped;
        if ((f32)(arg1->unk6 + 50) < arg3) {
            dy_d = (arg3 - (f32)arg1->unk6) - 50.0f;
            dy_d = (dy_d > 20.0) ? 20.0 : dy_d;
            intensity = (f64)intensity * (1.0 - (dy_d / 20.0));
        }
    } else {
        dist_d = sqrtf((arg2 - (f32)arg1->unk4) * (arg2 - (f32)arg1->unk4) + (arg3 - (f32)arg1->unk6) * (arg3 - (f32)arg1->unk6) + (arg4 - (f32)arg1->unk8) * (arg4 - (f32)arg1->unk8));
        dist = (dist_d > 0.001) ? dist_d : 0.001;
        intensity = 1.0f;
    }

    if (arg1->unkE == 5) {
        if ((f64)intensity > 0.1) {
            c = (u32)(((f32)(arg1->unkB - lights->unk0) * intensity) + (f32)(u32)lights->unk0);
            lights->unk4 = (s8)c;
            lights->unk0 = (u8)c;

            c = (u32)(((f32)(arg1->unkC - lights->unk1) * intensity) + (f32)(u32)lights->unk1);
            lights->unk5 = (s8)c;
            lights->unk1 = (u8)c;

            c = (u32)(((f32)(arg1->unkD - lights->unk2) * intensity) + (f32)(u32)lights->unk2);
            lights->unk6 = (s8)c;
            lights->unk2 = (u8)c;

            c = (u32)(((((f64)(u32)ambient->unk0 * 0.5) - (f64)(u32)ambient->unk0) * (f64)intensity) + (f64)(u32)ambient->unk0);
            ambient->unk4 = (s8)c;
            ambient->unk0 = (u8)c;

            c = (u32)(((((f64)(u32)ambient->unk1 * 0.5) - (f64)(u32)ambient->unk1) * (f64)intensity) + (f64)(u32)ambient->unk1);
            ambient->unk5 = (s8)c;
            ambient->unk1 = (u8)c;

            c = (u32)(((((f64)(u32)ambient->unk2 * 0.5) - (f64)(u32)ambient->unk2) * (f64)intensity) + (f64)(u32)ambient->unk2);
            ambient->unk6 = (s8)c;
            ambient->unk2 = (u8)c;
        }
        return 0;
    }

    if ((f64)intensity > 0.02) {
        c = (u32)((f32)(u32)arg1->unkB * intensity);
        slot_light->unk4 = (s8)c;
        slot_light->unk0 = (u8)c;

        c = (u32)((f32)(u32)arg1->unkC * intensity);
        slot_light->unk5 = (s8)c;
        slot_light->unk1 = (u8)c;

        c = (u32)((f32)(u32)arg1->unkD * intensity);
        slot_light->unk6 = (s8)c;
        slot_light->unk2 = (u8)c;

        slot_light->unk8 = (s8)(s32)(((f32)arg1->unk4 - arg2) * (127.0f / dist));
        slot_light->unk9 = (s8)(s32)(((f32)arg1->unk6 - arg3) * (127.0f / dist));
        slot_light->unkA = (s8)(s32)(((f32)arg1->unk8 - arg4) * (127.0f / dist));
        return 1;
    }

    return 0;
}
