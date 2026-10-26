// func_806175C4 (src/global/19A00.c): stage 2: m2c behavioural reconstruction; exact local allocation and f64 expression/register scheduling remain.
typedef struct P19eActorSub4View { u8 pad0[0x34]; f32 unk34; } P19eActorSub4View;
void func_806086CC(f32, f32, f32, s16, s32, s32, s32, s32, f32, s32);

s32 func_806175C4(Actor *arg0) {
    s16 command;
    u8 factor, a, b, c;
    f32 value;
    f64 result;
    D_807F5AF0++;
    func_80614F4C((u8 *)&command);
    func_80614F28(&factor); func_80614F28(&a); func_80614F28(&b); func_80614F28(&c);
    result = (((((f64)((P19eActorSub4View *)arg0->unk4)->unk34 / 0.4381361) * 200.0) + 55.0) * (f64)factor) / 255.0;
    if (result > 255.0) value = 255.0f; else value = (f32)result;
    func_806086CC(arg0->unk7C, arg0->unk80, arg0->unk84, command, (u32)value, a, b, c, 0.3f, 0);
    return 1;
}
