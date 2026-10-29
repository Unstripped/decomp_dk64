// func_806776A0 (src/global/7BBD0.c): stage 4: frame size 0x138 matched, all 8 callee-saved regs matched, remaining regalloc and loop schedule
typedef struct KaS2_ActorSub140 {
    s32 unk0;
    s32 unk4;
    s32 unk8;
    s32 unkC;
    u8 pad10[0x48];
    s32 unk58;
    u8 pad5C[0xC];
    s32 unk68;
    u8 pad6C[0x20];
    CollisionNode *unk8C;
    u8 pad90[0x14];
    s32 unkA4;
    s32 unkA8;
    u8 unkAC;
} KaS2_ActorSub140;

extern u8 D_807FD614;

extern u8 D_807FB603;
extern u8 D_807FB547;
extern s32 D_807FB5D0;
extern void *D_807FC924;
extern u8 D_807FC929;
extern s16 D_80753D50[];
extern s16 D_80753D60[];
extern s32 D_807FD584;

void func_80672E90(s32, s32, s32);
void actorSetCameraBoundaryMode(u32);
void actorSetTargetAngleBounds(void *);
u8 func_806738D0(s32, s32, s32, s32, s32, s32);
s32 func_8067B1E0(Actor *);
void func_8067A99C(f32, f32, Actor *, Actor *, s32);
void func_8067A69C(Actor *, Actor *, f32, f32, s32, s32);

void func_806776A0(Actor *arg0, Actor *arg1, f32 *arg2, void *arg3, s8 arg4, s32 arg5, s32 arg6, u8 arg7) {
    Beh7BB_MtxF spEC;
    f32 spE8;
    f32 spE4;
    f32 spE0;
    f32 spDC;
    f32 spD8;
    f32 spD4;
    f32 spD0;
    f32 spCC;
    f32 spC8;
    f32 spC4;
    f32 spC0;
    f32 spBC;
    f32 spB8;
    f32 spB4;
    f32 spB0;
    f32 spAC;
    f32 spA8;
    f32 spA4;
    f32 spA0;
    f32 sp9C;
    f32 sp98;
    f32 sp94;
    f32 sp90;
    f32 sp8C;
    f32 sp78;
    f32 sp74;
    f32 sp70;
    f32 sp68;
    f32 sp64;
    f32 *var_s2;
    f32 *var_s3;
    s32 var_s0;
    KaS2_ActorSub140 *temp_s5;
    KaS2_ActorSub140 *temp_s6;

    temp_s5 = (KaS2_ActorSub140 *)arg0->unk140;
    temp_s6 = (KaS2_ActorSub140 *)arg1->unk140;
    D_807FB603 = temp_s5->unkAC;
    D_807FB5FD = 1;
    D_807FB600 = 1;
    D_807FB547 = 0;
    func_80672E90(temp_s6->unk0, temp_s6->unk4, temp_s6->unk8);
    actorSetCameraBoundaryMode(arg1->unk58);
    if (arg7 != 0) {
        var_s0 = func_80673708(temp_s6->unk0, temp_s6->unk4, temp_s6->unk8, arg5, temp_s5->unkA4, temp_s5->unkA8, (s32)((u8 *)arg1 + 0xF4), (s32)((u8 *)arg1 + 0xF6));
    } else {
        actorSetTargetAngleBounds((void *)(temp_s5->unkA4 + (temp_s6->unk58 * 0x58)));
        if (!(*(u32 *)&arg0->unk64 & 0x10)) {
            var_s0 = func_806738D0(temp_s6->unk0, temp_s6->unk4, temp_s6->unk8, arg5, temp_s5->unkA4, temp_s5->unkA8);
        } else {
            var_s0 = func_80673708(temp_s6->unk0, temp_s6->unk4, temp_s6->unk8, arg5, temp_s5->unkA4, temp_s5->unkA8, (s32)((u8 *)arg1 + 0xF4), (s32)((u8 *)arg1 + 0xF6));
        }
    }
    if ((arg7 != 0) && ((f64)*(f32 *)(&D_807FD614 + (func_8067B1E0(arg1) * 0x34)) > 30.0)) {
        var_s0 = 1;
    }
    if (var_s0 != 0) {
        actorGetMatrix((Beh7BB_Struct_760C *)temp_s5, spEC, arg4);
        guMtxXFMF(spEC, *(f32 *)arg2, *((f32 *)arg2 + 1), *((f32 *)arg2 + 2), &spE8, &spE4, &spE0);
        var_s2 = &spD4;
        var_s3 = &spC8;
        arg2 = &spBC;
        if (*(u32 *)&arg0->unk64 & 0x10) {
            sp68 = spE8;
            sp64 = spE0;
        } else {
            do {
                guMtxXFMF(spEC, *(f32 *)arg3, *((f32 *)arg3 + 1), *((f32 *)arg3 + 2), var_s2, var_s3, arg2);
                arg2 += 4;
                arg3 = (u8 *)arg3 + 0xC;
                var_s2 += 4;
                var_s3 += 4;
            } while (arg2 != &spC8);
            spB0 = spDC - spD4;
            spB4 = spD0 - spC8;
            spB8 = spC4 - spBC;
            spA4 = spD8 - spD4;
            spA8 = spCC - spC8;
            spAC = spC0 - spBC;
            sp98 = (spB4 * spAC) - (spA8 * spB8);
            sp9C = (spB8 * spA4) - (spAC * spB0);
            spA0 = (spB0 * spA8) - (spA4 * spB4);
            sp64 = sqrtf((spA0 * spA0) + (sp98 * sp98) + (sp9C * sp9C));
            sp8C = sp98 / sp64;
            sp90 = sp9C / sp64;
            sp94 = spA0 / sp64;
            if (arg1->unk5C & 1) {
                if (*(u8 *)(*(s32 *)&D_807FC924 + (D_807FC929 * 0x2F0) + 0x2C0) == 1) {
                    sp68 = (f32)D_80753D50[D_807FD584] / 8.0f;
                } else {
                    sp68 = (f32)D_80753D60[D_807FD584] / 8.0f;
                }
                sp70 = sp8C * sp68;
                sp74 = sp90 * sp68;
                sp78 = sp94 * sp68;
                *(f32 *)((u8 *)arg1->unk174 + 0xE0) = spE8 - sp70;
                *(f32 *)((u8 *)arg1->unk174 + 0xE4) = spE0 - sp78;
            }
            if (temp_s6->unk68 != 0) {
                arg5 = temp_s6->unk68 + 5;
                D_807FB5D0 = arg5;
                if (arg6 < arg5) {
                    D_807FB5D0 = arg6;
                    arg5 = arg6;
                }
            } else {
                D_807FB5D0 = arg5;
                if (arg5 < 0xF) {
                    arg5 = 0xF;
                    D_807FB5D0 = 0xF;
                }
                if (arg6 < arg5) {
                    D_807FB5D0 = arg6;
                    arg5 = arg6;
                }
            }
            sp68 = (f32)arg5 / 8.0f;
            sp8C *= sp68;
            sp94 *= sp68;
            sp90 *= sp68;
            sp68 = spE8 - sp8C;
            sp64 = spE0 - sp94;
            func_8067A99C(sp8C, sp94, arg0, arg1, arg5);
        }
        func_8067A69C(arg0, arg1, sp68, sp64, 1, 1);
    }
    for (var_s0 = (s32)temp_s6->unk8C; var_s0 != 0; var_s0 = (s32)((CollisionNode *)var_s0)->next) {
        if (((CollisionNode *)var_s0)->unk26 != 0) {
            arg1->unkFC |= func_80673708(((CollisionNode *)var_s0)->unk10, ((CollisionNode *)var_s0)->unk14, ((CollisionNode *)var_s0)->unk18, ((CollisionNode *)var_s0)->unk1C, temp_s5->unkA4, temp_s5->unkA8, (s32)((u8 *)arg1 + 0xF4), (s32)((u8 *)arg1 + 0xF6));
        }
    }
    *(u8 *)((u8 *)arg1 + 0xFD) = D_807FB547;
}
