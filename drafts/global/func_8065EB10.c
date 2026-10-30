// func_8065EB10 (src/global/63810.c): stage 5, NO FAKEs: frame -8, s0 accum, lbu 0xB(sp) arg0, all integer regs and loop shapes match; 329 vs 328 insns (full diff ~82 lines, all FP). Recipe: arg0 modified in place (arg0 = arg0 - 1, no idx local); u8 count + one s32 i for loops 1-3; loop2 'for (i=0; sub[i].unkA!=0; count++, i++)'; loop3 'i = 1; while (temp_hi >= accum) { accum += sub[i].unkA; i++; }'; NO cur/nxt locals (index D_80748430[arg0].sub[i]/[next] directly); 'accum -= sub[i].unkA; temp_hi -= accum; t = (f32)temp_hi / (f32)sub[i].unkA' right after i--, before next; D_807F9070 stores reordered by hill-climb with D_80748A84++ last. Remaining: FP candidate coloring: arg2 not promoted to f12 (sw a2,16(sp)); factor takes f12, 0.8 const candidate takes f16 (target: arg2 f12, arg3 f14, factor f16, 0.8 as temp f18); arg6 load temp f18 vs f4. uopt: FP candidate regs are f0,f2,f12,f14,f16 only
typedef struct RenderB63810_LightEntry {
    s16 unk0;
    u8 pad2[2];
    f32 unk4;
    f32 unk8;
    f32 unkC;
    s16 unk10;
    s16 unk12;
    s16 unk14;
    u8 unk16;
    u8 unk17;
    u8 unk18;
    u8 pad19[3];
} RenderB63810_LightEntry;

extern s16 D_80748A84;
extern RenderB63810_LightEntry D_807F9070[];

typedef struct RenderB63810_KeyFrame {
    f32 unk0;
    u8 r;
    u8 g;
    u8 b;
    u8 pad7;
    s16 unk8;
    s16 unkA;
} RenderB63810_KeyFrame;

typedef struct RenderB63810_KeyFrameSet {
    RenderB63810_KeyFrame sub[5];
} RenderB63810_KeyFrameSet;

extern RenderB63810_KeyFrameSet D_80748430[];
extern s32 D_8076A064;

void func_8065EB10(u8 arg0, s16 arg1, f32 arg2, f32 arg3, f32 arg4, s16 arg5, f32 arg6, s16 arg7) {
    u8 count;
    s32 i;
    s32 total;
    s32 temp_hi;
    s32 accum;
    s32 next;
    f32 t;
    f32 factor;
    f32 base;
    f64 d6;

    arg0 = arg0 - 1;
    if (D_80748A84 != 0x1E) {
        for (i = 0; i < D_80748A84; i++) {
            if (arg1 == D_807F9070[i].unk0) {
                return;
            }
        }

        total = 0;
        count = 0;
        for (i = 0; D_80748430[arg0].sub[i].unkA != 0; count++, i++) {
            total += D_80748430[arg0].sub[i].unkA;
        }

        temp_hi = (arg1 + D_8076A064) % total;
        accum = D_80748430[arg0].sub[0].unkA;
        i = 1;
        while (temp_hi >= accum) {
            accum += D_80748430[arg0].sub[i].unkA;
            i++;
        }

        i--;
        accum -= D_80748430[arg0].sub[i].unkA;
        temp_hi -= accum;
        t = (f32)temp_hi / (f32)D_80748430[arg0].sub[i].unkA;
        next = i + 1;
        if (next == count) {
            next = 0;
        }


        d6 = arg6;
        if (d6 < 0.8) {
            factor = 1.0f;
        } else {
            factor = 1.0 - ((d6 - 0.8) / 0.19999999999999996);
        }

        base = D_80748430[arg0].sub[i].unk0;
        base = (base + (D_80748430[arg0].sub[next].unk0 - base) * t) * factor;

        D_807F9070[D_80748A84].unk8 = arg3;
        D_807F9070[D_80748A84].unk16 = (u32)(((f32)(u32)D_80748430[arg0].sub[i].r + (f32)(D_80748430[arg0].sub[next].r - D_80748430[arg0].sub[i].r) * t) * base);
        D_807F9070[D_80748A84].unk4 = arg2;

        D_807F9070[D_80748A84].unk17 = (u32)(((f32)(u32)D_80748430[arg0].sub[i].g + (f32)(D_80748430[arg0].sub[next].g - D_80748430[arg0].sub[i].g) * t) * base);
        D_807F9070[D_80748A84].unk0 = arg1;
        D_807F9070[D_80748A84].unk18 = (u32)(((f32)(u32)D_80748430[arg0].sub[i].b + (f32)(D_80748430[arg0].sub[next].b - D_80748430[arg0].sub[i].b) * t) * base);
        D_807F9070[D_80748A84].unkC = arg4;
        D_807F9070[D_80748A84].unk10 = (s32)((f32)D_80748430[arg0].sub[i].unk8 + (f32)(D_80748430[arg0].sub[next].unk8 - D_80748430[arg0].sub[i].unk8) * t);
        D_807F9070[D_80748A84].unk12 = arg7;
        D_807F9070[D_80748A84].unk14 = arg5;
        D_80748A84++;
    }
}
