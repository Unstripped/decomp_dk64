// func_806F14BC (src/global/F56F0.c): Stage 3 behavioral draft compiles; helper-result reuse, stack allocation, and floating-point scheduling remain unmatched.
typedef struct F5N3ActorMeta14BC {
    f32 unk4;
    u8 pad8[0x1C];
    f32 unk24;
} F5N3ActorMeta14BC;

typedef struct F5N3ActorSub14BC {
    F5N3ActorMeta14BC *meta;
    u8 pad4[0x84];
    s32 status;
} F5N3ActorSub14BC;

typedef struct F5N3Actor14BC {
    u8 pad0[0x6A];
    u16 unk6A;
    u8 pad6C[0x14];
    f32 unk80;
    u8 pad84[0x20];
    f32 unkA4;
    u8 padA8[4];
    f32 unkAC;
    u8 padB0[4];
    f32 unkB4;
    u8 padB8[8];
    f32 unkC0;
    f32 unkC4;
    f32 unkC8;
} F5N3Actor14BC;

s32 func_806F1668(f32, f32, f32, f32);
void func_80614D00(Actor *, f32);

void func_806F14BC(Actor *arg0) {
    F5N3Actor14BC *actor = (F5N3Actor14BC *) arg0;
    f32 limit;
    f32 value;
    u8 amount;
    F5N3ActorSub14BC *sub = (F5N3ActorSub14BC *) arg0->unk4;

    func_80614FD8(&limit);
    func_80614F28(&amount);
    sub->status = 0;
    if (actor->unk6A & 2) {
        value = actor->unkAC - actor->unkA4;
        if (value > 12.0f) {
            value = actor->unkAC < actor->unkA4 ? actor->unkAC : actor->unkA4;
        }
        if (actor->unk80 - value < 0.0f) {
            value = 0.0f;
        }
    } else {
        value = actor->unkB4;
    }
    if (func_806F1668(value * 40.0f, actor->unkC0, actor->unkC8, actor->unkC4) == 0) {
        sub->status = 1;
        return;
    }
    value = ((f32) amount - sub->meta->unk4) /
        (f32) func_806F1668(value * 40.0f, actor->unkC0, actor->unkC8, actor->unkC4);
    if (value < 0.0f) {
        value = 0.01f;
    }
    func_80614D00(arg0, value < limit ? value : limit);
}
