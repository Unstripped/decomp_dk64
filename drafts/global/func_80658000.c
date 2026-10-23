// func_80658000 (src/global/55B20.c): stage 4: 4x __ll_to_f + div.s by unk20, fabs via 0.0-x, returns v<=(f32)arg4; call order matches; remaining: frame 0x40 vs 0x38 and arg reload shape
typedef struct R2P6aXform {
    /* 0x00 */ long long unk0;
    /* 0x08 */ long long unk8;
    /* 0x10 */ long long unk10;
    /* 0x18 */ long long unk18;
    /* 0x20 */ f32 unk20;
    /* 0x24 */ f32 unk24;
    /* 0x28 */ u8 pad28[8];
} R2P6aXform;

extern R2P6aXform *D_807F6C24;

s32 func_80658000();

s32 func_80658000(arg0, arg1, arg2, arg3, arg4)
s32 arg0;
f32 arg1;
f32 arg2;
f32 arg3;
s16 arg4;
{
    f32 v;

    v = ((f32)D_807F6C24[arg0].unk18 + ((f32)D_807F6C24[arg0].unk0 * arg1 + (f32)D_807F6C24[arg0].unk8 * arg2 + (f32)D_807F6C24[arg0].unk10 * arg3)) / D_807F6C24[arg0].unk20;
    if (v < 0.0) {
        v = 0.0 - v;
    }
    return v <= (f32)arg4;
}
