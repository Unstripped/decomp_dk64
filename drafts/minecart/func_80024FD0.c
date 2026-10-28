// func_80024FD0 (src/minecart/0.c): stage 5: frame/regs/FP all match, 3-line diff: expected shares one hoisted 'li a1,0x14' between func_800240DC(1,0x14) and func_80726EE0(0,0x14) (second call only 'move a0,zero' in jal delay); ours re-emits li a1,20 and hoists move a0,zero above bne. Needs McA_Cart174 from func_80024B00 decls; func_806A2A10 third param must be u8 (andi a2,v0,0xff). Tried: u8/s32 proto variants, named local for 0x14, if/else/goto shapes, permuter (no gain).
extern s32 D_80028C20;
void actorScriptStart(void *, s32);
void actorSetStateTwo(void *);
void func_806A2A10(s32, s32, u8);
void func_80726EE0(s32, s32);
void camSetFixedView(void *, f32, f32, f32, f32, f32, f32, s32);

void func_80024FD0(void) {
    McA_Cart174 *sp44;
    Struct_807FC924_4_174 *sp40;
    f32 diff;
    f32 sp28;

    sp44 = (McA_Cart174 *)D_807FBB40->unk174;
    sp40 = D_807FBB4C->unk174;
    if (!(D_807FBB40->unk60 & 0x10)) {
        sp44->unk30 = func_80610FE8(3);
        sp44->unk30[0] = 0x10;
        sp44->unk30[1] = 0xFF;
        sp44->unk24 = 3.0f;
        sp44->unk28 = 12.0f;
        D_807FBB40->unk168 = 3;
        sp40->unk1F0 |= 8;
        camStartPath(D_807FBB40, 0, 1, sp44);
        actorScriptStart(D_807FBB40, 0);
    }
    if (D_807FBB40->unk154 != 5 && D_807FBB40->unk154 != 6) {
        diff = (D_807FC924->unk214 - D_807FBB40->unk80) - 100.0f;
        sp28 = (f32)(((f64)diff / 650.0 * 0.15) + .15);
        actorSetUniformScale(D_807FBB40, sp28);
        actorSetUniformScale(D_807FBB4C, sp28);
    }
    if (sp40->unk1F0 & 8) {
        sp44->unk3E = 3;
    }
    if (D_807FBB40->unk154 < 5) {
        func_8002430C(0x16, (s32)sp44->unk30, 0, 0x19);
    }
    if (camIsCutsceneActive() == 0) {
        camSetFixedView(sp40->unk104, 322.0f, 900.0f, 268.0f, 325.0f, -9000.0f, 500.0f, 0);
    }
    switch (D_807FBB40->unk154) {
    case 1:
    case 2:
    case 3:
        if (D_807FBB40->unk4->unk64 == 0x292) {
            func_800240DC(1, 0x14);
            D_807FBB40->unk154 = 5;
        } else if (D_807FBB40->unk11C != NULL && D_807FBB40->unk11C->unk154 == 5) {
            func_80726EE0(0, 0x14);
            func_80024000(1, 0xE);
            D_807FBB40->unk154 = 5;
            break;
        }
        func_80024E78((MinecartStruct_E78 *)sp44, (MinecartElem **)&D_80028C20, 0x10, 0x13);
        actorGetNodePos(D_807FBB40, 9, &sp44->unk4->unk7C, &sp44->unk4->unk80, &sp44->unk4->unk84);
        return;
    case 4:
        D_807FBB40->unk154 = 3;
        sp44->unk34--;
        break;
    case 5:
        actorSetUniformScale(D_807FBB40, 0.15f);
        actorSetUniformScale(D_807FBB4C, 0.225f);
        D_807FBB40->unkE4 = 0;
        D_807FBB40->unk154++;
        break;
    case 10:
        sfxAllocateChannel(0x5A, 1.0f);
        func_806A2A10(0x78, 0x78, (D_8076A0A8 == 0x4D) ? 0x1E : (D_8076A0A8 == 0x81) ? 0x2D : 0x3C);
        actorSetStateTwo(D_807FBB40->unk11C);
        sp40->unk1F0 &= ~8;
        D_807FBB40->unk154 = 3;
        break;
    }
}
