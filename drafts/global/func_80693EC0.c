// func_80693EC0 (src/global/936B0.c): stage 4 (frame 0x50, s0/s1 set, all blocks equal; uses ProjectileBeam* types of 936B0.c): 2 insns differ at angle wrap: target 'lh v1; addiu v1,v1,2048; andi t5,v1,0xfff' vs ours 'addiu t3,v1,2048; andi t5,t3,..' (angle s16 var; s32 angle gives in-place addiu but temp-reg rotation -3: andi t2 vs t5). Needs 2 hidden t-temps (t2,t3) before andi with in-place add. Tried: angle/diff/temp_v0 types grid, pad48/pad40 as angle/diff, m2c inline form, dead stmts (deadsweep), permuter 2x300s.
extern u8 D_80720268;
extern s16 func_80672A70(s16, s16);

void func_80693EC0(void) {
    ProjectileBeamActorExtra *sp4C;
    s32 pad48;
    u8 sp47;
    s32 pad40;
    s16 temp_v0;
    f32 temp_fv0;

    sp4C = (ProjectileBeamActorExtra *)G_PROJECTILE_BEAM_ACTOR->unk174;
    sp47 = 0;
    if (!(G_PROJECTILE_BEAM_ACTOR->unk60 & 0x10)) {
        sfxPlayFromActorWithAltitudeCheck(D_807FBB40, 0xF4, 0xFF, 0x7F, 5);
        G_PROJECTILE_BEAM_ACTOR->unk6A &= 0xFFFE;
        G_PROJECTILE_BEAM_ACTOR->unkEE = (s16)((G_PROJECTILE_BEAM_ACTOR->unk124->unk0 / 6.2831855f) * 4095.0f);
        G_PROJECTILE_BEAM_ACTOR->unkB8 = (f32)((f64)(G_PROJECTILE_BEAM_ACTOR->unk124->unk4 / (f32)4) * 2.6);
        G_PROJECTILE_BEAM_ACTOR->unkC0 = G_PROJECTILE_BEAM_ACTOR->unk124->unk8;
        G_PROJECTILE_BEAM_ACTOR->unk144 = 0x3C;
        func_8066EB40(D_807FBB40, 60.0f);
        actorAppendModelNode(D_807FBB40, 0.0f, 0.0f, 0.0f, 50.0f, -1);
        actorAppendModelSubNode(D_807FBB40, 0.0f, 0.0f, 0.0f, -1);
        func_807149FC(-1);
        func_807149B8(1);
        func_807149C8(0, 0xFF, 0, 0xFF);
        func_80714C08(&D_80720268, G_PROJECTILE_BEAM_ACTOR->unk124->unkC, D_807FBB40, 1, 2);
        sp4C->unk0 = D_8076A068;
        sp4C->unk4 = 0;
        G_PROJECTILE_BEAM_ACTOR->unk60 |= 0x80000;
        G_PROJECTILE_BEAM_ACTOR->unkFA = 0x2328;
        sp4C->unk13 = (u8)(u32)G_PROJECTILE_BEAM_ACTOR->unk124->unk10;
        if (sp4C->unk13 == 0x63) {
            sp4C->unk4 = 2;
        }
        sp4C->unk1C = 0;
    }
    if ((u32)(sp4C->unk0 + 10) < D_8076A068) {
        G_PROJECTILE_BEAM_ACTOR->unk60 &= 0xFFF7FFFF;
    }
    func_80690C60(1, D_807FBB40, 0, 1);
    func_8067ACB4(D_807FBB40);
    if (G_PROJECTILE_BEAM_ACTOR->unkFC != 0 && func_806725A0(D_807FBB40, G_PROJECTILE_BEAM_ACTOR->unkEE) == 0) {
        s16 angle;
        s16 diff;
        sfxPlayFromActorWithAltitudeCheck(D_807FBB40, 0xF5, 0xFF, 0x7F, 0x1E);
        temp_v0 = func_80672A70(G_PROJECTILE_BEAM_ACTOR->unkF4, G_PROJECTILE_BEAM_ACTOR->unkF6);
        angle = G_PROJECTILE_BEAM_ACTOR->unkEE;
        angle += 0x800;
        diff = temp_v0 - (angle & 0xFFF);
        G_PROJECTILE_BEAM_ACTOR->unkEE = temp_v0 + diff;
        if (G_PROJECTILE_BEAM_ACTOR->unkEE < 0) {
            G_PROJECTILE_BEAM_ACTOR->unkEE += 0xFFF;
        }
        if (G_PROJECTILE_BEAM_ACTOR->unkEE >= 0x1000) {
            G_PROJECTILE_BEAM_ACTOR->unkEE -= 0xFFF;
        }
        if (func_806725A0(D_807FBB40, G_PROJECTILE_BEAM_ACTOR->unkEE) == 0) {
            sp47 = 1;
        }
    }
    actorApplyVelocity(D_807FBB40);
    func_80665564(D_807FBB40, 0.0f);
    func_8065D254(D_807FBB40, 0x3C8, 0x40, 0x40, 10, 10, 1, 0x4B, 0x78, 0, 1.0f);
    G_PROJECTILE_BEAM_ACTOR->unkC0 += D_807502E4;
    temp_fv0 = (f32)D_807502D0;
    if (G_PROJECTILE_BEAM_ACTOR->unkC0 < temp_fv0) {
        G_PROJECTILE_BEAM_ACTOR->unkC0 = temp_fv0;
    }
    if ((G_PROJECTILE_BEAM_ACTOR->unk6A & 1) && !(G_PROJECTILE_BEAM_ACTOR->unk6C & 1)) {
        switch (sp4C->unk4) {
            case 0:
                G_PROJECTILE_BEAM_ACTOR->unkC0 = 200.0f;
                break;
            case 1:
                G_PROJECTILE_BEAM_ACTOR->unkC0 = 150.0f;
                break;
            case 2:
                G_PROJECTILE_BEAM_ACTOR->unkC0 = 100.0f;
                func_8066EB40(D_807FBB40, 200.0f);
                actorAppendModelNode(D_807FBB40, 0.0f, 0.0f, 0.0f, 180.0f, -1);
                break;
            case 3:
                G_PROJECTILE_BEAM_ACTOR->unkC0 = 80.0f;
                break;
        }
        sfxPlayFromActorWithAltitudeCheck(D_807FBB40, 0xF5, 0xFF, 0x7F, 0x1E);
        sp4C->unk4++;
        G_PROJECTILE_BEAM_ACTOR->unkB8 = (f32)(((f64)G_PROJECTILE_BEAM_ACTOR->unkB8 / 3.0) * 2.5);
    }
    if ((G_PROJECTILE_BEAM_ACTOR->unk64 & 0x100) || sp47 != 0) {
        D_807FBB85 = 1;
    }
    if (((G_PROJECTILE_BEAM_ACTOR->unk6A & 1) && sp4C->unk4 == 4) || D_807FBB85 != 0) {
        projectileSpawnExplosion();
        actorDespawn(D_807FBB40);
    }
    if ((u32)(sp4C->unk0 + D_80750344) < D_8076A068) {
        actorDespawn(D_807FBB40);
    }
}
