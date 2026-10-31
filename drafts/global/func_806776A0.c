// func_806776A0 (src/global/7BBD0.c): stage 4+: frame 0x138, stack offsets, saved regs, FP regs, loop dup match; ~58 masked diff lines left: clamp region (arg6 v0 vs a0, D_807FB5D0 addr a0 vs v0, lui hoist) + int temp ring after. FAKEs: *(u8*)&arg7, do{}while(0)
typedef struct Col7B_ActorSub140 {
    s32 unk0;
    s32 unk4;
    s32 unk8;
    s32 unkC;
    u8 pad10[0x48];
    s16 unk58;
    u8 pad5A[0xE];
    s32 unk68;
    u8 pad6C[0x20];
    CollisionNode *unk8C;
    u8 pad90[0x14];
    s32 unkA4;
    s32 unkA8;
    u8 unkAC;
} Col7B_ActorSub140;

extern u8 D_807FD614[];
extern u8 D_807FB603;
extern u8 D_807FB547;
extern void *D_807FC924;
extern u8 D_807FC929;
extern s16 D_80753D50[];
extern s16 D_80753D60[];
extern s16 D_807FD584;

void func_80672E90(s32, s32, s32);
void actorSetCameraBoundaryMode(s32);
void actorSetTargetAngleBounds();
u8 func_806738D0(s32, s32, s32, s32, s32, s32);
u8 func_8067B1E0(Actor *);
void func_8067A99C(s32, Actor *, s32);
void func_8067A69C(s32, Actor *, f32, f32, u8, u8);

void func_806776A0(Actor *arg0, Actor *arg1, f32 *arg2, f32 *arg3, s8 arg4, s32 arg5, s32 arg6, u8 arg7) {
    Col7B_ActorSub140 *temp_s5;
    Col7B_ActorSub140 *temp_s6;
    CollisionNode *node;
    Beh7BB_MtxF spEC;
    f32 spE8;
    f32 spE4;
    f32 spE0;
    f32 spD4[3];
    f32 spC8[3];
    f32 spBC[3];
    f32 spB0[3];
    f32 spA4[3];
    f32 sp98[3];
    f32 sp8C[3];
    f32 scale;
    f32 norm;
    s32 clamp;
    u8 *p174;
    f32 sp70[3];
    f32 *ptr3;
    f32 sp68;
    f32 sp64;
    f32 *var_s2;
    f32 *var_s3;
    f32 *var_s0p;
    u8 var_s0;

    temp_s5 = (Col7B_ActorSub140 *)arg0->unk140;
    temp_s6 = (Col7B_ActorSub140 *)arg1->unk140;
    D_807FB603 = temp_s5->unkAC;
    D_807FB5FD = 1;
    D_807FB600 = 1;
    D_807FB547 = 0;
    func_80672E90(temp_s6->unk0, temp_s6->unk4, temp_s6->unk8);
    actorSetCameraBoundaryMode(arg1->unk58);
    if (*(u8 *)&arg7 != 0) { // FAKE: address-taken arg7 stops cvt CSE (arg7 reloaded)
        var_s0 = func_80673708(temp_s6->unk0, temp_s6->unk4, temp_s6->unk8, arg5, temp_s5->unkA4, temp_s5->unkA8, (s32)&arg1->unkF4, (s32)&arg1->unkF6);
    } else {
        actorSetTargetAngleBounds(temp_s5->unkA4 + temp_s6->unk58 * 0x58);
        if (!(arg0->unk64 & 0x10)) {
            var_s0 = func_806738D0(temp_s6->unk0, temp_s6->unk4, temp_s6->unk8, arg5, temp_s5->unkA4, temp_s5->unkA8);
        } else {
            var_s0 = func_80673708(temp_s6->unk0, temp_s6->unk4, temp_s6->unk8, arg5, temp_s5->unkA4, temp_s5->unkA8, (s32)&arg1->unkF4, (s32)&arg1->unkF6);
        }
    }
    if ((*(u8 *)&arg7 != 0) && ((f64)*(f32 *)(D_807FD614 + func_8067B1E0(arg1) * 0x34) > 30.0)) {
        var_s0 = 1;
    }
    if (var_s0 != 0) {
        actorGetMatrix((Beh7BB_Struct_760C *)temp_s5, spEC, arg4);
        guMtxXFMF(spEC, arg2[0], arg2[1], arg2[2], &spE8, &spE4, &spE0);
        sp68 = spE8;
        var_s0p = arg3;
        var_s2 = spD4;
        var_s3 = spC8;
        ptr3 = spBC;
        if (arg0->unk64 & 0x10) {
            sp64 = spE0;
        } else {
            do {
                guMtxXFMF(spEC, var_s0p[0], var_s0p[1], var_s0p[2], var_s2, var_s3, ptr3);
                ptr3 += 1;
                var_s0p += 3;
                var_s2 += 1;
                var_s3 += 1;
            } while (ptr3 != &spC8[0]);
            spB0[0] = spD4[2] - spD4[0];
            spB0[1] = spC8[2] - spC8[0];
            spB0[2] = spBC[2] - spBC[0];
            spA4[0] = spD4[1] - spD4[0];
            spA4[1] = spC8[1] - spC8[0];
            spA4[2] = spBC[1] - spBC[0];
            sp98[0] = (spB0[1] * spA4[2]) - (spB0[2] * spA4[1]);
            sp98[1] = (spB0[2] * spA4[0]) - (spB0[0] * spA4[2]);
            sp98[2] = (spB0[0] * spA4[1]) - (spB0[1] * spA4[0]);
            norm = sqrtf((sp98[0] * sp98[0]) + (sp98[1] * sp98[1]) + (sp98[2] * sp98[2]));
            sp8C[0] = sp98[0] / norm;
            sp8C[1] = sp98[1] / norm;
            sp8C[2] = sp98[2] / norm;
            if (arg1->unk5C & 1) {
                scale = (*(u8 *)(*(s32 *)&D_807FC924 + (D_807FC929 * 0x2F0) + 0x2C0) == 1 ? (f32)D_80753D50[D_807FD584] : (f32)D_80753D60[D_807FD584]) / 8;
                p174 = arg1->unk174;
                sp70[0] = sp8C[0] * scale;
                sp70[1] = sp8C[1] * scale;
                sp70[2] = sp8C[2] * scale;
                *(f32 *)(p174 + 0xE0) = spE8 - sp70[0];
                *(f32 *)(p174 + 0xE4) = spE0 - sp70[2];
            }
            if (temp_s6->unk68 != 0) {
                clamp = temp_s6->unk68 + 5;
                D_807FB5D0 = clamp;
                if (arg6 < clamp) {
                    D_807FB5D0 = arg6;
                    clamp = arg6;
                }
            } else {
                clamp = arg5;
                D_807FB5D0 = clamp;
                if (clamp < 0xF) {
                    clamp = 0xF;
                    D_807FB5D0 = 0xF;
                }
                if (arg6 < clamp) {
                    D_807FB5D0 = arg6;
                    clamp = arg6;
                }
            }
            sp8C[0] *= (f32)clamp / 8;
            sp8C[1] *= (f32)clamp / 8;
            sp8C[2] *= (f32)clamp / 8;
            do {} while (0); // FAKE: splits BB so sp68/sp64 can reuse $f0 after the CSE'd division
            sp68 = spE8 - sp8C[0];
            sp64 = spE0 - sp8C[2];
            func_8067A99C((s32)arg0, arg1, clamp);
        }
        func_8067A69C((s32)arg0, arg1, sp68, sp64, 1, 1);
        for (node = temp_s6->unk8C; node != 0; node = node->next) {
            if (node->unk26 != 0) {
                arg1->unkFC |= func_80673708(node->unk10, node->unk14, node->unk18, node->unk1C, temp_s5->unkA4, temp_s5->unkA8, (s32)&arg1->unkF4, (s32)&arg1->unkF6);
            }
        }
    } else {
        for (node = temp_s6->unk8C; node != 0; node = node->next) {
            if (node->unk26 != 0) {
                arg1->unkFC |= func_80673708(node->unk10, node->unk14, node->unk18, node->unk1C, temp_s5->unkA4, temp_s5->unkA8, (s32)&arg1->unkF4, (s32)&arg1->unkF6);
            }
        }
    }
    arg1->unkFD = D_807FB547;
}
