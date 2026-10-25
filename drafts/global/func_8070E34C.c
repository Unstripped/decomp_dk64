// func_8070E34C (src/global/112080.c): stage 3: resource-group construction compiled; frame and register allocation remain different
extern void *func_80610FE8(s32);
extern void heapClearBlock(void *);
extern f64 D_8075E4A8;
extern void *D_80755390[];
void effectGridGetScaledDimensions(void *, s16 *, s16 *);
typedef struct R112eE34cEntry { s16 unk0; u8 pad2[0xE]; u16 unk10; u8 unk12; } R112eE34cEntry;
typedef struct R112eE34cGroup { u8 unk0; u8 pad1[0xB]; R112eE34cEntry *entries; u8 pad10[4]; f32 unk14; f32 unk18; struct R112eE34cGroup *next; } R112eE34cGroup;
typedef struct R112eE34cContainer { u8 pad0[0xC]; R112eE34cGroup *groups; } R112eE34cContainer;
typedef struct R112eE34cSourceEntry { u16 unk0; u8 unk2; u8 pad3; } R112eE34cSourceEntry;
typedef struct R112eE34cSource { u8 count; u8 pad1[3]; R112eE34cSourceEntry *entries; } R112eE34cSource;
void func_8070E34C(R112eE34cContainer *arg0, R112eE34cSource *arg1, void *arg2) {
    s16 sp56; s16 sp54; f32 temp_fv0; f32 temp_fv1; s32 var_s3; R112eE34cGroup **var_s1;
    R112eE34cGroup *temp_v0; R112eE34cGroup *temp_v0_2; R112eE34cGroup *temp_v0_3;
    R112eE34cEntry *temp_v0_4; R112eE34cGroup *temp_v0_5; R112eE34cGroup *temp_v0_6;
    R112eE34cEntry **var_s0; R112eE34cSourceEntry *temp_s2; R112eE34cGroup *var_v0;
    var_s1 = &arg0->groups;
    if (arg0->groups != NULL) { var_v0 = arg0->groups; do { var_s1 = &var_v0->next; var_v0 = var_v0->next; } while (var_v0 != NULL); }
    temp_v0 = func_80610FE8(0x20); *var_s1 = temp_v0; heapClearBlock(temp_v0); var_s3 = 0; (*var_s1)->unk0 = 2; var_s0 = &(*var_s1)->entries;
    if (arg1->count > 0) { do {
        temp_s2 = &arg1->entries[var_s3]; effectGridGetScaledDimensions(D_80755390[temp_s2->unk0], &sp56, &sp54); temp_v0_2 = *var_s1;
        if ((f64)(temp_v0_2->unk14 + (f32)sp56) >= D_8075E4A8) { var_s1 = &temp_v0_2->next; temp_v0_3 = func_80610FE8(0x20); temp_v0_2->next = temp_v0_3; heapClearBlock(temp_v0_3); temp_v0_2->next->unk0 = 2; var_s0 = &temp_v0_2->next->entries; }
        temp_v0_4 = func_80610FE8(0xA8); *var_s0 = temp_v0_4; heapClearBlock(temp_v0_4); (*var_s0)->unk0 = sp56; (*var_s0)->unk10 = temp_s2->unk0; (*var_s0)->unk12 = temp_s2->unk2;
        temp_v0_5 = *var_s1; temp_v0_5->unk14 += (f32)(*var_s0)->unk0; temp_v0_6 = *var_s1; temp_fv1 = temp_v0_6->unk18; temp_fv0 = (f32)sp54;
        if (temp_fv0 < temp_fv1) { temp_v0_6->unk18 = temp_fv1; } else { temp_v0_6->unk18 = temp_fv0; }
        var_s3 += 1; var_s0 = (R112eE34cEntry **)((u8 *)*var_s0 + 0xA0);
    } while (var_s3 < arg1->count); }
}
