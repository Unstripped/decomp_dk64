// func_8071D0F0 (src/global/11BC10.c): stage 5: frame 0x38 and s0 saved reached; direct state reload matches allocation path, but stack local, global materialization, and argument register allocation remain.
typedef struct { f32 timer; f32 x; f32 y; f32 z; } NM1bD0Motion;
typedef struct { u8 pad0[0x7C]; f32 x; f32 y; f32 z; } NM1bD0Actor;
typedef struct { u8 pad0[0x1F0]; s32 flags; } NM1bD0Flags;
extern u8 D_8076A0AB;
extern u16 D_807FC930[];
extern NM1bD0Flags *D_807FD580;
void actorGetNodePos(s32, u8, f32 *, f32 *, f32 *);
s32 func_805FF030(u8, s32, f32, f32);
void func_8071D0F0(TimedEffectActorView *arg0, s8 *arg1) {
    f64 pad;
    NM1bD0Motion *motion;
    s32 node;
    f32 factor;
    node = arg0->unk35C;
    motion = arg0->unk384;
    if (motion == NULL) { motion = func_80610FE8(0x10); arg0->unk384 = motion; motion->timer = 30.0f; }
    actorGetNodePos(node, 1, &motion->x, &motion->y, &motion->z);
    factor = (f32)((f64)motion->timer / 30.0);
    arg0->unk340 = (f32)(((NM1bD0Actor *)D_807FBB4C)->x - motion->x) * factor + motion->x;
    arg0->unk344 = (f32)(((NM1bD0Actor *)D_807FBB4C)->y - motion->y) * factor + motion->y;
    arg0->unk348 = (f32)(((NM1bD0Actor *)D_807FBB4C)->z - motion->z) * factor + motion->z;
    motion->timer -= 1.0f;
    if (motion->timer == 0.0f) { D_807FD580->flags |= 0x20000; D_807FC930[func_805FF030(D_8076A0AB, 0, motion->y, motion->z)]++; *arg1 = 1; }
}
