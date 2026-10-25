// func_8071CDE0 (src/global/11BC10.c): stage 4: frame and matrix tail match; state-pointer allocation and initial-register order differ
typedef struct { s16 angle; s16 y; s16 speed; s16 rotation; } M3Cde0State;
typedef struct { u8 pad0[0x7C]; f32 x; f32 y; f32 z; u8 pad88[0xD6]; u8 height; } M3Cde0Actor;
extern s32 D_8071FB08;
s16 func_806CC190(s16, s16, f32);
s16 mathAngleBetweenPoints2D(f32, f32, f32, f32);
void func_8071CDE0(TimedEffectActorView *arg0, s8 *arg1) {
 f32 sp98[4][4]; f32 sp58[4][4]; M3Cde0State *state; M3Cde0Actor *actor;
 state=arg0->unk384; if(state==NULL){func_80611A44();state=func_80610FE8(8);arg0->unk384=state;state->angle=0;state->y=(s16)arg0->unk344;state->speed=(func_80611A44()>>0xF)%5+10;state->rotation=0;} actor=(M3Cde0Actor *)(u32)arg0->unk35C;
 state->angle=func_806CC190(state->angle,mathAngleBetweenPoints2D(actor->x,actor->z,arg0->unk340,arg0->unk348),(f32)((func_80611A44()>>0xF)%10+5)); state->y=(s16)((f64)(actor->y+(f32)actor->height-state->y)*0.1+state->y); arg0->unk340+=state->speed*func_80612794(state->angle);arg0->unk348+=state->speed*func_80612790(state->angle);arg0->unk344=(f32)((f64)func_80612794((state->speed+0x32)*D_8076A064)*40.0+(state->y+0x28)); lightSetFlags(1);lightAdd(arg0->unk340,arg0->unk344,arg0->unk348,0.0f,0.0f,0.0f,150.0f,0,0x96,0x96,0xFF);if(!(D_8076A064&3)){func_807149B8(1);func_8071498C(func_8071C818);func_80714CC0((s32)&D_8071FB08,1.6f,arg0->unk340,arg0->unk344,arg0->unk348);}state->rotation+=state->speed;guScaleF(sp98,arg0->unk360,arg0->unk364,0.0f);guRotateF(sp58,(f32)state->rotation,0.0f,0.0f,1.0f);guMtxCatF(sp98,sp58,sp98);guMtxF2L(sp98,(Mtx *)((u8 *)arg0+(D_807444FC<<6)+0x128));arg0->pad0[0x32C]=2;
}
