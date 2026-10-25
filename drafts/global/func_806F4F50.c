// func_806F4F50 (src/global/F9450.c): Stage 4: recovered unlink/relink and output coordinates; target frame and node-array register allocation remain different
typedef struct F9F1_Node {
    s16 unk0;
    s16 unk2;
    s16 unk4;
    s16 unk6;
    s16 unk8;
    s16 unkA;
    s16 unkC;
    u8 unkE;
    u8 padF;
    s16 unk10;
    u8 unk12;
    u8 unk13;
    u8 unk14;
    u8 pad15[3];
    struct F9F1_Node *next;
} F9F1_Node;

extern F9F1_Node **D_80754244;
extern s16 D_807FD720;
s32 func_806F4EBC(f32, f32);

void func_806F4F50(s16 arg0, f32 arg1, f32 arg2, f32 arg3) {
    F9F1_Node *sp1C;
    F9F1_Node **var_a1;
    F9F1_Node *var_v0;
    F9F1_Node *var_v1;
    s32 temp_a0;
    s32 temp_v0;
    s32 var_a2;
    s32 var_a3;
    s32 var_t0;

    var_a2 = 0;
    var_t0 = 0;
    if (D_807FD720 > 0) {
        var_a3 = 0;
        do {
            var_v0 = NULL;
            var_a2++;
            var_a1 = (F9F1_Node **)((u8 *)D_80754244 + var_a3);
            var_v1 = *var_a1;
            var_a3 += 4;
            if ((var_v1 != NULL) && (arg0 != var_v1->unk0)) {
                do {
                    var_v0 = var_v1;
                    var_v1 = var_v1->next;
                } while ((var_v1 != NULL) && (arg0 != var_v1->unk0));
            }
            if ((var_v1 != NULL) && (arg0 == var_v1->unk0)) {
                var_t0 = 1;
                if (var_v0 != NULL) {
                    var_v0->next = var_v1->next;
                } else {
                    *var_a1 = var_v1->next;
                }
            }
            sp1C = var_v1;
        } while ((var_t0 == 0) && (var_a2 < D_807FD720));
    }
    temp_v0 = func_806F4EBC(arg1, arg3);
    if ((D_807FD720 >= temp_v0) && (temp_v0 >= 0)) {
        temp_a0 = temp_v0 * 4;
        sp1C->next = *(F9F1_Node **)((u8 *)D_80754244 + temp_a0);
        *(F9F1_Node **)((u8 *)D_80754244 + temp_a0) = sp1C;
        sp1C->unk8 = (s16)arg1;
        sp1C->unkA = (s16)arg2;
        sp1C->unkC = (s16)arg3;
    }
}
