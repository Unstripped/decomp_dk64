// playerHandleDamageReaction (src/global/7CA80.c): stage 5: frame 0x40 ok, same size. LgDisp2: phantom 3rd arg of func_806D0DE4 removed (it takes 2 args, u8 return; var_a2 no longer folded to li a2,1), u8 param, var_a2=1 moved after the arg2 test -> var_a2 a2 like target. Remaining: target narrows arg2 straight into a3 (andi a3,a2,0xff at entry, var_a2 in a2 live across it, li a2,1 hoisted before bne); mine does andi t6; move a2,t6 (param candidate adjsave 0.5 coloured a2 before var_a2 0.4 when their ranges overlap; with var_a2 set at top it takes a3 instead). 1800+ spelling/type/dead-test variants no gain. Needs var_a2 priority > 0.5 or param forbidden a2.
extern u8 D_807FBB85;
extern s32 D_80720E2C;
void func_80686CF8(Actor *);
s32 func_80714608(s32);
u8 func_806D0DE4(Actor *, Actor *);
void func_807149FC(s32);
void func_807149B8(s32);
void func_8071498C(void *);
void func_80714C08(void *, s32, Actor *, s32, s32);
void effectPulseSpinUpdate(void);
void playerHandleDamageReaction(Actor *arg0, Actor *arg1, u8 arg2) {
    s32 sp3C;
    s32 var_a2;
    void *sp24;
    s32 temp_a3;
    s32 var_v0;

    temp_a3 = arg2 & 0xFF;  // FAKE: unused local keeps the 8-byte frame slot (target frame 0x40)
    D_807FBB85 = 1;
    if (arg0 == D_807FBB48) {
        if (((DamageReactionPlayerEntry *)D_807FC924)[D_807FD580->unk1A4].unk2C0 == 2 && arg1 != NULL && (arg1->unk5C & 2)) {
            return;
        }
        sp3C = 0x2E;
        if (arg2 != 0) {
            sp3C = 0x30;
        }
        var_a2 = 1;
        if (arg1 != NULL && arg1->unk58 == 0x116) {
            func_80686CF8(arg0);
            switch (arg1->unk155[0]) {
            case 1:
                var_a2 = 0;
                D_807FD580->unk1F0 ^= 0x80;
                break;
            case 2:
                sp3C = 0x27;
                break;
            case 3:
                func_807149FC(0xF0);
                func_807149B8(1);
                sp24 = &effectPulseSpinUpdate;
                func_8071498C(&effectPulseSpinUpdate);
                func_80714C08(&D_80720E2C, 0x3ECCCCCD, arg0, 1, 2);
                func_807149FC(0xF0);
                func_807149B8(1);
                func_8071498C(sp24);
                func_80714C08(&D_80720E2C, 0x3EC28F5C, arg0, 5, 2);
                func_807149FC(0xF0);
                func_807149B8(1);
                func_8071498C(sp24);
                func_80714C08(&D_80720E2C, 0x3E99999A, arg0, 6, 2);
                var_a2 = 0;
                D_807FD580->unk1F0 |= 0x08000000;
                break;
            }
            D_807FD580->unk200 = 0xF0;
        } else if (arg1 != NULL && ((arg1->unk5C & 1) || (arg1->unk5C & 4) || (arg1->unk5C & 2))) {
            if (D_807FD580 == 0) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
            if (func_80714608(0) != 0) {
                if (func_806D0DE4(arg0, arg1) != 0) {
                    sp3C = 0x31;
                } else {
                    var_v0 = 1;
                    if (arg1->unk5C & 4) {
                        var_v0 = 3;
                    }
                    if (arg1->unk154 != 0x28 && var_v0 < 3) {
                        sp3C = 0x2B;
                    } else {
                        sp3C = 0xE;
                    }
                }
            }
        }
        if (var_a2 != 0) {
            playerStateQueueCallback((s16)sp3C, (s32)arg1, D_807FC929);
        }
    }
}
