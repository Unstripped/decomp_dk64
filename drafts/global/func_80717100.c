// func_80717100 (src/global/11BC10.c): stage 5: target 0x20 frame and s1 actor/s0 motion reached; direct actor guard fixes saves, remaining temporary/register allocation in angle update and arithmetic
typedef struct {
    s16 unk0;
    s16 unk2;
    s16 unk4;
    s16 unk6;
    s16 unk8;
} NM1bMotion10;

void func_80717100(Ub1ActorView *arg0, void *arg1) {
    Ub1ActorView *actor;
    NM1bMotion10 *motion;
    s16 angle_delta;

    actor = arg0;
    if (actor->unk384 == NULL) {
        actor->unk384 = func_80610FE8(0xA);
        motion = actor->unk384;
        motion->unk0 = (func_80611A44() >> 15) % 4095;
        motion->unk2 = actor->unk35C;
        motion->unk4 = actor->unk35C >> 16;
        motion->unk6 = actor->unk340;
        motion->unk8 = actor->unk348;
    }
    motion = actor->unk384;
    angle_delta = motion->unk4;
    motion->unk0 += angle_delta;
    actor->unk340 = func_80612794(motion->unk0) * motion->unk2 + motion->unk6;
    actor->unk348 = func_80612790(motion->unk0) * motion->unk2 + motion->unk8;
}
