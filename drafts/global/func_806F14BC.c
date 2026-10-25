// func_806F14BC (src/global/F56F0.c): Stage 3 control-flow draft from FPU assembly; helper-result reuse and floating expression schedule remain unmatched.
typedef struct F5AActorMeta {
    f32 unk4;
    u8 pad8[0x1C];
    f32 unk24;
} F5AActorMeta;

typedef struct F5AActorSub14BC {
    F5AActorMeta *meta;
    u8 pad4[0x84];
    s32 status;
} F5AActorSub14BC;

void func_80614FD8(f32 *);
void func_80614F28(u8 *);
s32 func_806F1668(f32, f32, f32, f32);
void func_80614D00(Actor *, f32);

void func_806F14BC(Actor *arg0) {
    f32 limit;
    f32 value;
    u8 amount;
    F5AActorSub14BC *sub = arg0->unk4;

    func_80614FD8(&limit);
    func_80614F28(&amount);
    sub->status = 0;
    if (arg0->unk6A & 2) {
        value = arg0->unkAC - arg0->unkA4;
        if (value > 12.0f) {
            value = arg0->unkAC < arg0->unkA4 ? arg0->unkAC : arg0->unkA4;
        }
        if (arg0->unk80 - value < 0.0f) {
            value = 0.0f;
        }
    } else {
        value = arg0->unkB4;
    }
    if (func_806F1668(value * 40.0f, arg0->unkC0, arg0->unkC8, arg0->unkC4) == 0) {
        sub->status = 1;
        return;
    }
    value = ((f32)amount - sub->meta->unk4) / (f32)func_806F1668(value * 40.0f, arg0->unkC0, arg0->unkC8, arg0->unkC4);
    if (value < 0.0f) {
        value = 0.01f;
    }
    func_80614D00(arg0, value < limit ? value : limit);
}
