// func_8068A858 (src/global/8F4B0.c): 200/226 insns matched; head 140 and tail 60 exact match; diff in middle D_807FC621 load/store scheduling and pointer representation
typedef struct {
    /* 0x00 */ u8 unk0;
    /* 0x01 */ u8 unk1;
    /* 0x02 */ s16 unk2;
    /* 0x04 */ s16 unk4;
    /* 0x06 */ s16 unk6;
    /* 0x08 */ s16 unk8;
    /* 0x0A */ s16 unkA;
    /* 0x0C */ s16 unkC;
} Act8F4_Entry0E;

extern s32 D_8076A064;
extern Actor *D_807FBB40;
extern u8 D_807FC621;
extern u8 D_807FC622;
extern u8 D_807501C0[][3];
extern Act8F4_Entry0E D_80750194[];

f32 func_80612790(s16);
f32 func_80612794(s16);
void func_8065A660(f32, f32);
void func_8065A708(f32, f32, f32, f32, f32, f32, f32, s32, s32, s32, s32);

void func_8068A858(u8 *arg0, u8 *arg1, u8 *arg2) {
    f32 pad;
    f32 sp40;
    f32 sp3C;
    f32 sp38;
    u8 temp_v1;
    u8 idx;
    Act8F4_Entry0E *entry;

    if (D_807FBB40->unk60 & 4) {
        switch (D_807FC622) {
        case 0:
            *arg0 = 0xFF;
            *arg1 = 0xFF;
            *arg2 = 0xFF;
            break;
        case 1:
            if (!(D_8076A064 & 0xF)) {
                goto set_color;
            }
            break;
        case 2:
            if (!(D_8076A064 & 3)) {
set_color:
                idx = (u32)(func_80612790(D_8076A064 * 200) * 4.0f + 4.0f);
                *arg0 = D_807501C0[idx][0];
                *arg1 = D_807501C0[idx][1];
                *arg2 = D_807501C0[idx][2];
            }
            break;
        }

        if ((D_807FC621 & 0x80) && (temp_v1 = D_807FC621 & 0x7F)) {
            entry = &D_80750194[temp_v1];
            D_807FC621 = temp_v1;
            sp40 = (f32)(entry - 1)->unk8;
            sp3C = (f32)(entry - 1)->unkA;
            sp38 = (f32)(entry - 1)->unkC;
            if (D_807FC622 != 0) {
                sp40 += 80.0f * func_80612794(D_8076A064 * 400);
                sp38 += 80.0f * func_80612790(D_8076A064 * 200);
                entry = &D_80750194[D_807FC621];
            }
            func_8065A660((f32)(u32)(entry - 1)->unk0, (f32)(u32)(entry - 1)->unk1);
            entry = &D_80750194[D_807FC621];
            func_8065A708((f32)(entry - 1)->unk2, (f32)(entry - 1)->unk4, (f32)(entry - 1)->unk6, sp40, sp3C, sp38, 0.0f, 1, *arg0, *arg1, *arg2);
        }
    }
}
