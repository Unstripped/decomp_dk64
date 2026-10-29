// func_80717B64 (src/global/11BC10.c): stage 4-5: structure+dataflow complete; remaining diff is register allocation only
typedef struct {
    u8 pad0[0x210];
    f32 unk210;
    f32 unk214;
    f32 unk218;
} Fx11BAPlayerView;

typedef struct {
    s16 unk0;
    s16 unk2;
    s16 unk4;
} Fx11BAFalloffState;

extern void *D_807FC924;

void func_80717B64(TimedEffectActorView *arg0, s8 *arg1) {
    Fx11BAFalloffState *var_v1;
    f32 scale;
    f32 dz;
    f32 dx;
    f32 dy;
    f32 dist;
    s32 temp_v0;
    s32 value;

    var_v1 = arg0->unk384;
    scale = (f32) ((s32) (arg0->unk34C * 3) / 4);
    if (var_v1 == NULL) {
        arg0->unk384 = func_80610FE8(6);
        var_v1 = arg0->unk384;
        var_v1->unk0 = 0;
        var_v1->unk2 = *(s16 *) ((u8 *) arg0->unk330 + 0x16) * arg0->unk350;
        var_v1->unk4 = arg0->unk36D;
        var_v1 = arg0->unk384;
    }
    temp_v0 = var_v1->unk0;
    if (temp_v0 == var_v1->unk2) {
        *arg1 = 1;
    } else {
        var_v1->unk0 = temp_v0 + 1;
    }
    dz = ((Fx11BAPlayerView *) D_807FC924)->unk218 - arg0->unk348;
    dx = ((Fx11BAPlayerView *) D_807FC924)->unk210 - arg0->unk340;
    dy = ((Fx11BAPlayerView *) D_807FC924)->unk214 - arg0->unk344;
    dist = sqrtf((dz * dz) + ((dx * dx) + (dy * dy)));
    if (dist < scale) {
        arg0->unk36D = var_v1->unk4;
        return;
    }
    value = (s32) ((f32) var_v1->unk4 * ((dist - scale) / ((f32) arg0->unk34C - scale)));
    if (var_v1->unk4 < value) {
        value = (s32) var_v1->unk4;
    }
    arg0->unk36D = var_v1->unk4 - value;
}
