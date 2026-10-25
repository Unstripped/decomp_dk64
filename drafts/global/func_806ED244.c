// func_806ED244 (src/global/EFDC0.c): stage 3: correct control flow and 0x18 frame; global-load/register allocation remains
typedef struct EfN5Target { u8 pad0[0xB8]; f32 unkB8; } EfN5Target;
typedef struct EfN5Player { u8 pad0[0x88]; void *unk88; } EfN5Player;
typedef struct EfN5Camera { u8 pad0[0x2A0]; void *unk2A0; u8 pad2A4[0x4C]; } EfN5Camera;

void func_806ED244(void) {
    EfN5Target *target;
    EfN5Target *cameraTarget;
    f32 absoluteVelocity;

    target = (EfN5Target *)((EfN5Player *)D_807FD580)->unk88;
    if (target->unkB8 >= 0.0f) {
        func_8072DB68(3);
        target = (EfN5Target *)((EfN5Player *)D_807FD580)->unk88;
    }
    cameraTarget = ((EfN5Camera *)D_807FC924)[D_807FC929].unk2A0;
    if (cameraTarget != NULL) {
        if (cameraTarget->unkB8 != 0.0f) {
            absoluteVelocity = cameraTarget->unkB8 > 0.0f ? cameraTarget->unkB8 : -cameraTarget->unkB8;
            target->unkB8 = (f32)(2.0 * (f64)absoluteVelocity);
        } else {
            absoluteVelocity = target->unkB8 > 0.0f ? target->unkB8 : -target->unkB8;
            target->unkB8 = absoluteVelocity < 50.0f ? -50.0f : -absoluteVelocity;
        }
    } else {
        absoluteVelocity = target->unkB8 > 0.0f ? target->unkB8 : -target->unkB8;
        target->unkB8 = absoluteVelocity < 50.0f ? -50.0f : -absoluteVelocity;
    }
    func_80614EBC((Actor *)((EfN5Player *)D_807FD580)->unk88, 0x292);
    if (D_807FBB48->unk154 != 9) {
        func_80614E78(D_807FBB48, 0x83);
    }
}
