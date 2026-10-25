// func_806D0DE4 (src/global/CEAE0.c): G07 stage 4-5: behaviourally equivalent; only regalloc differs: target keeps arg1 in a3 (move a3,a1 at entry), arg0 in a0, flags0 in a1, var_a2 in a2; ours puts arg0 in a3 and spills arg1 (sw a1,4(sp)). Direct arg->unk5C reads (no flag temps) fix the arg regs but lose hoisted andi; dead 'if(!arg1){}' flips priority wrongly; decl order and s32 temps no effect.
typedef struct G07PlayerSlot {
    /* 0x000 */ u8 pad0[4];
    /* 0x004 */ void *unk4;
    /* 0x008 */ u8 pad8[0x2B8];
    /* 0x2C0 */ u8 unk2C0;
    /* 0x2C1 */ u8 pad2C1[0x2F];
} G07PlayerSlot;

typedef struct G07StateView {
    /* 0x000 */ u8 pad0[0x1A4];
    /* 0x1A4 */ u8 unk1A4;
} G07StateView;

u8 func_806D0DE4(Actor *arg0, Actor *arg1) {
    s32 var_a0;
    s32 var_a2;
    u16 temp_a1;
    u16 temp_t0;
    u8 var_v0;
    u8 var_v1;

    var_v0 = 1;
    var_v1 = 1;
    var_a2 = 1;
    if ((D_807FC928 < 2) || (temp_a1 = arg0->unk5C, ((temp_a1 & 4) != 0)) || (temp_t0 = arg1->unk5C, ((temp_t0 & 4) != 0))) {
        return 0;
    }
    if (temp_a1 & 1) {
        var_v0 = ((G07PlayerSlot *)D_807FC924)[((G07StateView *)arg0->unk174)->unk1A4].unk2C0;
    }
    if (temp_t0 & 1) {
        var_v1 = ((G07PlayerSlot *)D_807FC924)[((G07StateView *)arg1->unk174)->unk1A4].unk2C0;
        var_a2 = arg1->unk154 != 0x7C;
    }
    var_a0 = var_v0 < var_v1;
    if (var_a0 != 0) {
        var_a0 = var_a2 != 0;
    }
    return var_a0 & 0xFF;
}
