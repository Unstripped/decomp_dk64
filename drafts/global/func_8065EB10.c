// func_8065EB10 (src/global/63810.c): near-miss: leaf stack frame $s0 save and regalloc differences
typedef struct R1B63810_SubEntry_EB10 {
    f32 unk0;
    u8 r;
    u8 g;
    u8 b;
    u8 pad7;
    s16 unk8;
    s16 unkA;
} R1B63810_SubEntry_EB10;

typedef struct R1B63810_Entry_EB10 {
    R1B63810_SubEntry_EB10 sub[5];
} R1B63810_Entry_EB10;

typedef struct R1B63810_Struct_9070 {
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
} R1B63810_Struct_9070;

extern R1B63810_Entry_EB10 D_80748430[];
extern s16 D_80748A84;
extern s32 D_8076A064;
extern R1B63810_Struct_9070 D_807F9070[];

void func_8065EB10(u8 arg0, s16 arg1, f32 arg2, f32 arg3, f32 arg4, s16 arg5, f32 arg6, s16 arg7) {
    s32 idx = (u8)(arg0 - 1);
    s32 i;
    R1B63810_SubEntry_EB10 *sub;
    R1B63810_SubEntry_EB10 *curr;
    R1B63810_SubEntry_EB10 *curr2;
    R1B63810_Struct_9070 *out;
    s32 total;
    u8 count;
    s32 temp_hi;
    s16 accum;
    s32 k;
    s32 sub_idx;
    s32 next_idx;
    f32 t;
    f64 d6;
    f32 factor;
    f32 fv1;
    f32 ft5;

    if (D_80748A84 != 0x1E) {
        for (i = 0; i < D_80748A84; i++) {
            if (arg1 == D_807F9070[i].unk0) {
                return;
            }
        }

        sub = D_80748430[idx].sub;
        total = 0;
        count = 0;
        if (sub[0].unkA != 0) {
            curr = sub;
            do {
                total += curr->unkA;
                count++;
                curr++;
            } while (curr->unkA != 0);
        }

        temp_hi = (s32)(arg1 + D_8076A064) % total;
        accum = sub[0].unkA;
        k = 1;
        if (temp_hi >= accum) {
            curr = &sub[1];
            do {
                k++;
                accum += curr->unkA;
                curr++;
            } while (temp_hi >= accum);
        }

        sub_idx = k - 1;
        curr = &sub[sub_idx];
        next_idx = sub_idx + 1;
        if (next_idx == count) {
            next_idx = 0;
        }
        curr2 = &sub[next_idx];

        t = (f32)(temp_hi - (accum - curr->unkA)) / (f32)curr->unkA;

        d6 = arg6;
        if (d6 < 0.8) {
            factor = 1.0f;
        } else {
            factor = 1.0 - ((d6 - 0.8) / 0.19999999999999996);
        }

        ft5 = curr->unk0;
        fv1 = (ft5 + (curr2->unk0 - ft5) * t) * factor;

        out = &D_807F9070[D_80748A84];
        out->unk16 = (u32)(((f32)(u32)curr->r + (f32)(curr2->r - curr->r) * t) * fv1);
        out->unk17 = (u32)(((f32)(u32)curr->g + (f32)(curr2->g - curr->g) * t) * fv1);
        out->unk18 = (u32)(((f32)(u32)curr->b + (f32)(curr2->b - curr->b) * t) * fv1);

        out->unk4 = arg2;
        out->unk8 = arg3;
        out->unkC = arg4;
        out->unk0 = arg1;
        out->unk12 = arg7;
        out->unk14 = arg5;
        out->unk10 = (s32)((f32)curr->unk8 + (f32)(curr2->unk8 - curr->unk8) * t);
        D_80748A84++;
    }
}
