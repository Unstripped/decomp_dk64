// func_8071CDE0 (src/global/11BC10.c): stage 1 behavior starter compiled; captures 8-byte orbit state, interpolation, lighting, and callback sequence; target still needs matrix tail and exact signed-byte height/load behavior
typedef struct { s16 angle; s16 y; s16 speed; s16 rotation; } Ua2cCde0State;
typedef struct { u8 pad0[0x7C]; f32 x; f32 y; f32 z; u8 pad88[0xD6]; s16 height; } Ua2cCde0Actor;
extern s32 D_8071FB08;
s16 func_806CC190(s16, s16, f32); s16 mathAngleBetweenPoints2D(f32, f32, f32, f32);
void lightSetFlags(s32); void lightAdd(f32, f32, f32, s32, f32, f32, f32, s32, s32, s32, s32);
void func_8071CDE0(Ub2ActorView *arg0, s8 *arg1) {
    Ua2cCde0State *state; Ua2cCde0Actor *actor; s16 angle; s16 y;
    state = arg0->unk384;
    if (state == NULL) { func_80611A44(); state = func_80610FE8(8); arg0->unk384 = state; state->angle = 0; state->y = (s16)arg0->unk344; state->speed = (func_80611A44() >> 0xF) % 5 + 0xA; state->rotation = 0; }
    actor = arg0->unk35C; angle = mathAngleBetweenPoints2D(actor->x, actor->z, arg0->unk340, arg0->unk348); state->angle = func_806CC190(state->angle, angle, (f32)((func_80611A44() >> 0xF) % 10 + 5));
    y = state->y; state->y = (s16)((f64)(actor->y + actor->height - y) * 0.1 + y); arg0->unk340 += state->speed * func_80612794(state->angle); arg0->unk348 += state->speed * func_80612790(state->angle); arg0->unk344 = (f32)((f64)func_80612794((state->speed + 0x32) * D_8076A064) * 40.0 + state->y + 0x28); lightSetFlags(1); lightAdd(arg0->unk340, arg0->unk344, arg0->unk348, 0, 0.0f, 0.0f, 150.0f, 0, 0x96, 0x96, 0xFF);
    if (!(D_8076A064 & 3)) { func_807149B8(1); func_8071498C(func_8071C818); func_80714CC0((s32)&D_8071FB08, 1.6f, arg0->unk340, arg0->unk344, arg0->unk348); } state->rotation += state->speed;
}
