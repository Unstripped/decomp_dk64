// func_806ED244 (src/global/EFDC0.c): stage 4: local zero and separate branch locals preserved target control flow but global address CSE and register allocation still differ
void func_806ED244(void) {
    EfN9Target *cameraTarget;
    EfN9Target *target;
    f32 zero;

    target = (EfN9Target *)((EfN9Player *)D_807FD580)->unk88;
    zero = 0.0f;
    if (target->unkB8 >= zero) {
        func_8072DB68(3);
        target = (EfN9Target *)((EfN9Player *)D_807FD580)->unk88;
    }
    cameraTarget = ((EfN9Camera *)D_807FC924)[D_807FC929].unk2A0;
    if (cameraTarget != NULL) {
        if (cameraTarget->unkB8 != zero) {
            f32 absoluteVelocity;

            absoluteVelocity = cameraTarget->unkB8 > zero ? cameraTarget->unkB8 : -cameraTarget->unkB8;
            target->unkB8 = (f32)(2.0 * (f64)absoluteVelocity);
        } else {
            f32 absoluteVelocity;

            absoluteVelocity = target->unkB8 > zero ? target->unkB8 : -target->unkB8;
            target->unkB8 = absoluteVelocity < 50.0f ? -50.0f : -absoluteVelocity;
        }
    } else {
        f32 absoluteVelocity;

        absoluteVelocity = target->unkB8 > zero ? target->unkB8 : -target->unkB8;
        target->unkB8 = absoluteVelocity < 50.0f ? -50.0f : -absoluteVelocity;
    }
    func_80614EBC((Actor *)((EfN9Player *)D_807FD580)->unk88, 0x292);
    if (D_807FBB48->unk154 != 9) {
        func_80614E78(D_807FBB48, 0x83);
    }
}
