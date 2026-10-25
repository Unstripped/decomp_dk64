// func_80717930 (src/global/11BC10.c): stage 7: instruction stream is exact (fdiff score 0; permuter baseline and iteration score 0). Function-owned literals still report as local-rodata relocation differences.
typedef struct {
    s16 unk0;
    s16 unk2;
    s16 unk4;
    s16 unk6;
    s16 unk8;
} NM2Motion10;

typedef struct {
    u8 pad0[4];
    ActorSub4 *unk4;
} NM2ScaleHolder;

typedef struct {
    u8 pad0[0x32C];
    u8 unk32C;
    u8 pad32D[0xB];
    NM2ScaleHolder *unk338;
    u8 pad33C[4];
    f32 unk340;
    f32 unk344;
    f32 unk348;
    u8 pad34C[0x10];
    s32 unk35C;
    f32 unk360;
    f32 unk364;
    u8 pad368[0x1C];
    NM2Motion10 *unk384;
    u8 pad388[4];
    u16 unk38C;
} NM2MotionActor;

void func_80717930(NM2MotionActor *arg0, void *arg1) {
    f32 temp_fv0;
    f32 call_result;
    s32 temp_v1;
    NM2Motion10 *temp_s1;
    void *temp_v0;
    NM2ScaleHolder *temp_v0_2;

    if (arg0->unk384 == NULL) {
        arg0->unk384 = func_80610FE8(0xA);
        temp_v0 = arg0->unk384;
        ((NM2Motion10 *)temp_v0)->unk0 = (func_80611A44() >> 0xF) % 4095;
        ((NM2Motion10 *)temp_v0)->unk2 = arg0->unk340;
        ((NM2Motion10 *)temp_v0)->unk4 = arg0->unk348;
        temp_v1 = arg0->unk35C;
        if (temp_v1 & 0x8000) {
            arg0->unk35C = temp_v1 & 0xFFFF7FFF;
            ((NM2Motion10 *)temp_v0)->unk6 = 0xC8;
            ((NM2Motion10 *)temp_v0)->unk8 = 0xA;
        } else {
            ((NM2Motion10 *)temp_v0)->unk6 = 0x46;
            ((NM2Motion10 *)temp_v0)->unk8 = 0xF;
        }
        temp_v0_2 = arg0->unk338;
        if (temp_v0_2 != NULL) {
            temp_fv0 = temp_v0_2->unk4->unk38 / 0.15;
            ((NM2Motion10 *)temp_v0)->unk8 = ((NM2Motion10 *)temp_v0)->unk8 * temp_fv0;
            arg0->unk35C = arg0->unk35C * temp_fv0;
        }
    }
    temp_s1 = arg0->unk384;
    if (arg0->unk38C & 2) {
        arg0->unk340 = func_80612794(temp_s1->unk0) * arg0->unk35C + D_807FBB4C->unk7C;
        arg0->unk348 = func_80612790(temp_s1->unk0) * arg0->unk35C + D_807FBB4C->unk84;
    } else {
        arg0->unk340 = func_80612794(temp_s1->unk0) * arg0->unk35C + temp_s1->unk2;
        arg0->unk348 = func_80612790(temp_s1->unk0) * arg0->unk35C + temp_s1->unk4;
    }
    arg0->unk344 += temp_s1->unk8 * 0.1;
    temp_s1->unk0 += temp_s1->unk6;
}
