// func_806FDB8C (src/global/1025E0.c): m2c-guided allocation/list implementation compiles with target frame but diverges in callee-saved register allocation and entry-count multiplication; stage 3.
typedef struct R1F1025E0Entry {
    f32 unk0;
    f32 unk4;
    f32 unk8;
    f32 unkC;
    f32 unk10;
    f32 unk14;
    f32 unk18;
    f32 unk1C;
    f32 unk20;
    f32 unk24;
    f32 unk28;
    f32 unk2C;
    f32 unk30;
    f32 unk34;
} R1F1025E0Entry;

typedef struct R1F1025E0Node {
    struct R1F1025E0Node *next;
    void *unk4;
    R1F1025E0Entry *unk8;
    s8 unkC;
    u8 unkD;
    u8 unkE[6];
    f32 unk14;
    f32 unk18;
    s16 unk1C;
} R1F1025E0Node;

extern R1F1025E0Node *D_80754AD0;
extern s16 D_80754AD4;
extern s16 D_80744490;
extern u8 D_8074450C;
extern s32 func_806FBD5C(s16, s32);
extern void *func_80610FE8(s32);
extern s32 func_80611A44(void);
extern u8 func_806FBEAC(char *);
extern void heapClearBlock(void *);
extern s32 strlen(char *);
void _strcpy(s32, s32);

s16 func_806FDB8C(s16 arg0, char *arg1, s32 arg2, f32 arg3, f32 arg4, f32 arg5) {
    R1F1025E0Node *temp_v0;
    void *temp_v0_2;
    void *temp_v0_4;
    R1F1025E0Node *var_v0;
    R1F1025E0Node *var_v1;
    s16 var_s2;
    s32 temp_lo;
    s32 temp_lo_2;
    u8 temp_v0_3;

    func_806FBD5C(arg0, (s32) arg1);
    temp_v0 = func_80610FE8(0x20);
    heapClearBlock(temp_v0);
    if (D_80754AD0 == NULL) {
        D_80754AD0 = temp_v0;
        temp_v0->next = NULL;
        D_80754AD4 = 0;
    } else {
        var_v0 = D_80754AD0->next;
        var_v1 = D_80754AD0;
        if (var_v0 != NULL) {
            do {
                var_v1 = var_v0;
                var_v0 = var_v0->next;
            } while (var_v0 != NULL);
        }
        var_v1->next = temp_v0;
        temp_v0->next = NULL;
    }
    temp_v0->unk1C = D_80754AD4;
    D_80754AD4 += 1;
    temp_v0_2 = func_80610FE8(strlen(arg1) + 1);
    temp_v0->unk4 = temp_v0_2;
    _strcpy((s32) temp_v0_2, (s32) arg1);
    temp_v0_3 = func_806FBEAC(arg1);
    temp_v0->unkD = temp_v0_3;
    temp_v0_4 = func_80610FE8((temp_v0_3 & 0xFF) * 0x38);
    temp_v0->unk8 = temp_v0_4;
    heapClearBlock(temp_v0_4);
    temp_v0->unkC = arg0;
    var_s2 = 0;
    if (temp_v0->unkD > 0) {
        do {
            if ((arg2 & 0xFF) == 3) {
                temp_lo = var_s2;
                temp_v0->unk8[temp_lo].unk0 = ((func_80611A44() >> 0xF) % 1440) - 0x50;
                temp_v0->unk8[temp_lo].unk4 = ((func_80611A44() >> 0xF) % 1120) - 0x50;
                temp_v0->unk8[temp_lo].unk20 = (f32) ((f64) ((func_80611A44() >> 0xF) % 6283) / 1000.0);
                temp_v0->unk14 = 0.1f;
            } else {
                temp_lo_2 = var_s2;
                temp_v0->unk8[temp_lo_2].unk0 = arg3 * 4.0f;
                temp_v0->unk8[temp_lo_2].unk4 = arg4 * 4.0f;
                temp_v0->unk8[temp_lo_2].unk8 = arg5 * 4.0f;
                if (D_8074450C == 2) {
                    temp_v0->unk8[temp_lo_2].unk30 = 1.0f;
                } else {
                    temp_v0->unk8[temp_lo_2].unk30 = 0.1f;
                }
                temp_v0->unk14 = 0.2f;
            }
            var_s2 += 1;
        } while (var_s2 < temp_v0->unkD);
    }
    return temp_v0->unk1C;
}
