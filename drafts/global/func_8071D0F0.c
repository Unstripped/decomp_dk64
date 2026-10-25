// func_8071D0F0 (src/global/11BC10.c): stage 4: behavior compiled; f64 padding produces target 0x38 frame and saved register set, remaining register allocation/call argument and u16 indexing differences
typedef struct { f32 timer; f32 x; f32 y; f32 z; } Ua2cD0Motion;
typedef struct { u8 pad0[0x7C]; f32 x; f32 y; f32 z; } Ua2cD0Actor;
typedef struct { u8 pad0[0x1F0]; s32 flags; } Ua2cD0Flags;
extern u8 D_8076A0AB;
extern u16 D_807FC930[];
extern Ua2cD0Flags *D_807FD580;
void actorGetNodePos(s32, u8, f32 *, f32 *, f32 *);
s32 func_805FF030(f32, f32, u8, s32);
void func_8071D0F0(Ub2ActorView *arg0, s8 *arg1) {
    f64 pad; Ua2cD0Motion *motion; s32 node; f32 factor;
    node = arg0->unk35C; motion = arg0->unk384;
    if (motion == NULL) { motion = func_80610FE8(0x10); arg0->unk384 = motion; motion->timer = 30.0f; }
    actorGetNodePos(node, 1, &motion->x, &motion->y, &motion->z);
    factor = (f32)((f64)motion->timer / 30.0);
    arg0->unk340 = (f32)(((Ua2cD0Actor *)D_807FBB4C)->x - motion->x) * factor + motion->x;
    arg0->unk344 = (f32)(((Ua2cD0Actor *)D_807FBB4C)->y - motion->y) * factor + motion->y;
    arg0->unk348 = (f32)(((Ua2cD0Actor *)D_807FBB4C)->z - motion->z) * factor + motion->z;
    motion->timer -= 1.0f;
    if (motion->timer == 0.0f) { D_807FD580->flags |= 0x20000; D_807FC930[func_805FF030(motion->y, motion->z, D_8076A0AB, 0) * 2]++; *arg1 = 1; }
}
