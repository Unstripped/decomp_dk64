// func_8069B010 (src/global/9DD70.c): m2c stage-1 C only; many untyped call prototypes (lightAdd/actorAppend*/func_8065D254) need real signatures
? actorAppendCallback(void *, void *, ?, u8, s32, s32); /* extern */
? actorAppendModelNode(void *, ?, ?, ?, f32, s32);  /* extern */
? actorAppendModelSubNode(void *, ?, ?, ?, s32);    /* extern */
? actorDespawn(void *);                             /* extern */
? collisionCheckActorFloor(void *, f32, s32, f32, void *); /* extern */
? func_8065D254(void *, ?, ?, ?, s32, s32, s32, s32, s32, s32, f32); /* extern */
? func_8066EB40(void *, ?);                         /* extern */
? func_8067ACB4(void *);                            /* extern */
? func_8071498C(? *);                               /* extern */
? func_807149B8(?);                                 /* extern */
? func_807149FC(?);                                 /* extern */
? func_80714C08(? *, ?, void *, ?, s32);            /* extern */
? func_80714CC0(? *, ?, f32, s32, f32);             /* extern */
? lightAdd(f32, f32, f32, ?, f32, f32, f32, s32, s32, s32, s32); /* extern */
f32 mathAngleBetweenPointsDeg(f32, f32, s32, s32, s32, s32); /* extern */
? sfxPlayFromActorWithAltitudeCheck(void *, ?, ?, ?, s32); /* extern */
extern ? D_8071FE08;
extern ? D_80720E14;
extern s16 D_80750378;
extern u32 D_8076A068;
extern s32 D_8076A0A8;
extern void *D_807FBB40;
extern void *D_807FBB4C;
extern u8 D_807FBD70;
extern void *D_807FC924;
extern ? func_8071EEE0;

void func_8069B010(void) {
    u32 *sp4C;
    f32 sp44;
    f32 temp_fa1;
    f32 temp_ft5;
    f32 temp_fv0;
    f32 temp_fv1;
    f32 var_fa0;
    f32 var_ft4;
    u8 temp_v1;
    void *temp_s0;
    void *temp_s0_2;
    void *temp_v0;

    temp_s0 = D_807FBB40;
    sp4C = temp_s0->unk174;
    if (!(temp_s0->unk60 & 0x10)) {
        temp_s0->unk6A = (u16) (temp_s0->unk6A & 0xFFFE);
        D_807FBB40->unk144 = 2;
        func_8066EB40(D_807FBB40, 0x42700000);
        actorAppendModelNode(D_807FBB40, 0, 0, 0, 60.0f, -1);
        actorAppendModelSubNode(D_807FBB40, 0, 0, 0, -1);
        func_807149FC(-1);
        func_807149B8(1);
        func_8071498C(&func_8071EEE0);
        func_80714C08(&D_80720E14, 0x3F666666, D_807FBB40, 1, 2);
        *sp4C = D_8076A068;
        D_807FBB40->unk60 = (s32) (D_807FBB40->unk60 | 0x80000);
        collisionCheckActorFloor(D_807FBB40, D_807FBB40->unk7C, D_807FBB40->unk80, D_807FBB40->unk84, D_807FBB40 + 0xA4);
    }
    func_8067ACB4(temp_s0);
    func_8065D254(D_807FBB40, 0x3C8, 0x40, 0x40, 0x1E, 0x1E, 1, 0x4B, 0x78, 0, 1.0f);
    temp_s0_2 = D_807FBB40;
    temp_v0 = temp_s0_2->unk11C;
    if (temp_v0 != NULL) {
        temp_v1 = temp_v0->unk154;
        if ((temp_v1 != 2) && (temp_v1 != 0x26)) {
            actorDespawn(temp_s0_2);
            return;
        }
        if (temp_v0->unk15F == temp_s0_2->unk15F) {
            var_fa0 = temp_s0_2->unk7C;
            var_ft4 = temp_s0_2->unk84;
            temp_fa1 = D_807FBB4C->unk7C;
            temp_ft5 = D_807FBB4C->unk84;
            temp_fv0 = var_fa0 - temp_fa1;
            temp_fv1 = var_ft4 - temp_ft5;
            if (((temp_fv0 * temp_fv0) + (temp_fv1 * temp_fv1)) > 900.0f) {
                sp44 = mathAngleBetweenPointsDeg(var_fa0, temp_fa1, (s32) var_fa0, (s32) var_ft4, (s32) temp_fa1, (s32) temp_ft5);
                D_807FBB40->unk11C->unkEC = (s16) (s32) (sp44 - mathAngleBetweenPointsDeg((bitwise f32) (s32) D_807FC924->unk228, (bitwise f32) (s32) D_807FC924->unk230, (s32) D_807FC924->unk210, (s32) D_807FC924->unk218));
                var_fa0 = D_807FBB40->unk7C;
                var_ft4 = D_807FBB40->unk84;
            }
            lightAdd(var_fa0, temp_s0_2->unk80, var_ft4, 0, 0.0f, 0.0f, 100.0f, 0, 0xFF, 0xFF, 0);
        }
        if (D_807FBD70 == 9) {
            sfxPlayFromActorWithAltitudeCheck(D_807FBB40, 0x1CE, 0xFF, 0x7F, 0x1E);
            func_80714CC0(&D_8071FE08, 0x3F800000, D_807FBB40->unk7C, D_807FBB40->unk80, D_807FBB40->unk84);
            actorAppendCallback(D_807FBB40->unk11C, D_807FBB40, 0x02000000, D_807FBB40->unk15F, 0, 0);
            actorDespawn(D_807FBB40);
        }
        if ((D_8076A0A8 != 0x48) && (D_8076A0A8 != 0x11) && ((u32) (*sp4C + D_80750378) < (u32) D_8076A068)) {
            actorAppendCallback(D_807FBB40->unk11C, D_807FBB40, 0x02000000, 0xFFU, 0, 0);
            actorDespawn(D_807FBB40);
        }
    } else {
        actorDespawn(temp_s0_2);
    }
}
