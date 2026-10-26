// func_806FA1A4 (src/global/FCCD0.c): Stage 1 behavioural five-player display-list loop compiles; target saves s0-s7/f20-f30 in a 0x90 frame, drafted block order/register allocation remains far from target.
// Behavioural stage-1 reconstruction; batched five-player display-list layout.
typedef struct R3FCCD0fBatchArg { u8 pad0[4]; f32 unk4; f32 unk8; s16 unk10; u8 pad12[2]; s32 *unk14; } R3FCCD0fBatchArg;
typedef struct R3FCCD0fBatchSlot { u8 pad0[4]; u16 unk4; } R3FCCD0fBatchSlot;
extern s16 D_807505AE[];
extern u8 D_807FC992[];
extern u8 D_807FD7E4;
extern void *D_2000180;
extern s8 flagGet(s16, s32);
extern Gfx *func_806F9D8C(s32, R3FCCD0fBatchArg *, Gfx *);

Gfx *func_806FA1A4(s32 arg0, R3FCCD0fBatchArg *arg1, Gfx *arg2) {
    s32 player = func_805FF030(D_8076A0AB, 1);
    s32 active_player = func_806C8DE0(0);
    s32 i;
    s32 *cursor = arg1->unk14;
    R3FCCD0fBatchSlot *slot = (R3FCCD0fBatchSlot *)((u8 *)D_80754280 + (arg0 * 0x30));
    s32 saved_value = slot->unk4;
    s32 saved_cursor = cursor[1];
    f32 x = (f32)((f64)cursor[0] * 4.0);
    f32 draw_y = (f32)((f64)((f32)((f64)cursor[1] * 4.0)) + 92.0);

    x = (f32)((f64)x - (4.0 * (6.0 - ((1.0 - (f64)func_80612794(arg1->unk10)) * (f64)arg1->unk4))));
    for (i = 0; i < 5; i++) {
        s32 valid = (i == 0) || flagGet(D_807505AE[i], 0);
        if (valid != 0) {
            f32 scale = (i == active_player) ? 2.0f : 1.5f;
            if (i == active_player) {
                slot->unk4 = saved_value;
            } else {
                slot->unk4 = ((u16 *)D_807FC992)[i * 0x5E + player];
            }
            arg2 = func_806F9D8C(arg0, arg1, arg2);
            if (i != active_player) {
                arg2->words.w0 = 0xFA000000;
                arg2->words.w1 = D_807FD7E4 >> 1;
                arg2++;
            }
            ((f32 *)&D_807FD7A0)[i] = (f32)((f64)x - (10.0 * (f64)scale));
            ((f32 *)&D_807FD7B8)[i] = (f32)((f64)draw_y - (30.0 * (f64)scale));
            ((f32 *)&D_807FD7D0)[i] = (f32)((f64)scale * 1.15);
            draw_y = (f32)((f64)draw_y + 136.0);
            cursor[1] += 0x22;
        }
    }
    slot->unk4 = saved_value;
    cursor[1] = saved_cursor;
    arg2->words.w0 = 0xDA380003;
    arg2->words.w1 = (u32)D_2000180;
    return arg2 + 1;
}
