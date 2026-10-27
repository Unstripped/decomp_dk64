// func_806358E8 (src/global/36880.c): stage 3 (NM36A2, no progress to stage 4): frame 0x80 matches; callee-saved still s0-s6 vs target s0-s4 (target: s0=const 1 then loop i, s1=arg9 then &D_807FC924, s2=arg0*0x90 offset, s3=flag, s4=&D_807F6000). Tried: s32 i + (u8*)D_807FC924 + i*0x2F0 / array form (both strength-reduce i*752 into an s-reg pointer instead of target's per-iteration sll/subu chain, product CSE'd across the call); direct macro instead of v1 slot var after the first blocks; dead &argN aliases; toggling x vs x != 0 on all arg9-12 tests (64 combos): always 7 s-regs. Needs prototype s32 func_8062D2AC(s32, s16*, u8) (currently void) and s32 func_80635EF0 proto before use. Idea left: target hoists off=arg0*0x90 into s2 after the first (arg12) block and keeps arg0 memory-resident (lw s2,0x80(sp)).
// Draft context (same file 36880.c): ModelSlot *D_807F6000, extern void *D_807FC924, s32 hashTableLookup(s32),
// s32 func_8062D2AC(s32, s16 *, u8) [needs s32 return], s32 func_806303C4(s32, u8, void *, f32, f32, f32, s32 x5),
// func_806333F8/func_8063373C(s32, R36880bVertTable *, f32 x7, u8) from earlier in the file.
typedef struct R36880dVec {
    /* 0x00 */ f32 unk0;
    /* 0x04 */ f32 unk4;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ f32 unk10;
    /* 0x14 */ f32 unk14;
    /* 0x18 */ f32 unk18;
    /* 0x1C */ f32 unk1C;
} R36880dVec;

typedef struct R36880dTgt {
    /* 0x00 */ u8 pad0[0x7C];
    /* 0x7C */ f32 unk7C;
    /* 0x80 */ f32 unk80;
    /* 0x84 */ f32 unk84;
} R36880dTgt;

typedef struct R36880dPlayer {
    /* 0x00 */ u8 unk0;
    /* 0x01 */ u8 pad1[3];
    /* 0x04 */ R36880dTgt *unk4;
    /* 0x08 */ u8 pad8[0x2E8];
} R36880dPlayer;

typedef struct R36880dKind {
    /* 0x00 */ u8 pad0[0x67];
    /* 0x67 */ u8 unk67;
    /* 0x68 */ s16 unk68;
    /* 0x6A */ s16 unk6A;
    /* 0x6C */ s16 unk6C;
} R36880dKind;

typedef struct R36880dMeta {
    /* 0x00 */ u8 pad0[0x1E];
    /* 0x1E */ s16 unk1E;
} R36880dMeta;

typedef struct R36880dSlotG {
    /* 0x00 */ f32 unk0;
    /* 0x04 */ f32 unk4;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ f32 unk10;
    /* 0x14 */ f32 unk14;
    /* 0x18 */ f32 unk18;
    /* 0x1C */ f32 unk1C;
    /* 0x20 */ R36880dVec *unk20;
    /* 0x24 */ R36880dMeta *unk24;
    /* 0x28 */ u8 pad28[0x54];
    /* 0x7C */ R36880dKind *unk7C;
    /* 0x80 */ u8 pad80[6];
    /* 0x86 */ s16 unk86;
    /* 0x88 */ s16 unk88;
    /* 0x8A */ s16 unk8A;
    /* 0x8C */ u8 pad8C[4];
} R36880dSlotG;

extern u8 D_807FC928;
s32 func_80635EF0(f32, f32, f32, s16, s16, s16, u16);
s32 collisionCheckBoundingBoxXZ(void *, f32, f32);
s32 collisionCheckBoundingBoxY(void *, f32);
void collisionTransformNode(s32, void *, f32, f32, f32, f32, f32, f32, f32);
void func_80634908(s32, void *, f32, f32, f32, f32, f32, f32, f32);
void actorUpdateEntryCoordinates(s16, f32, f32, f32, f32, f32);

#define R36880D_G ((R36880dSlotG *)((u8 *)D_807F6000 + arg0 * 0x90))
#define R36880D_GO ((R36880dSlotG *)((u8 *)D_807F6000 + off))


void func_806358E8(s32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6, f32 arg7, f32 arg8, u8 arg9, u8 arg10, u8 arg11, u8 arg12, u8 arg13) {
    R36880dSlotG *v1;
    s16 sp76;
    u8 flag;
    u8 i;
    flag = 0;
    if (arg13 == 1) {
        arg0 = hashTableLookup(arg0);
    }
    if (arg12) {
        R36880D_G->unk1C = arg8;
        v1 = R36880D_G;
        switch (v1->unk86) {
            case 2:
                v1->unk20->unk10 = arg8;
                break;
            case 1:
                v1->unk20->unk1C = arg8;
                break;
        }
    }
    if (arg9 != 0) {
        R36880D_G->unk0 = arg1;
        R36880D_G->unk4 = arg2;
        R36880D_G->unk8 = arg3;
        v1 = R36880D_G;
        switch (v1->unk86) {
            case 2:
                v1->unk20->unk0 = arg1;
                v1->unk20->unk4 = arg2;
                v1->unk20->unk8 = arg3;
                break;
            case 1:
                v1->unk20->unk0 = arg1;
                v1->unk20->unk4 = arg2;
                v1->unk20->unk8 = arg3;
                break;
        }
    }
    if (arg10) {
        R36880D_G->unk10 = arg4;
        R36880D_G->unk14 = arg5;
        R36880D_G->unk18 = arg6;
        v1 = R36880D_G;
        if (v1->unk86 == 1) {
            v1->unk20->unk10 = arg4;
            v1->unk20->unk14 = arg5;
            v1->unk20->unk18 = arg6;
        }
    }
    if (arg11) {
        R36880D_G->unkC = arg7;
        v1 = R36880D_G;
        switch (v1->unk86) {
            case 2:
                v1->unk20->unkC = arg7;
                break;
            case 1:
                v1->unk20->unkC = arg7;
                break;
        }
    }
    if ((arg9 != 0 || arg12) && func_8062D2AC((s32)R36880D_G->unk20, &sp76, 0) != 0) {
        v1 = R36880D_G;
        func_806303C4(0, ((u8 *)v1)[0x87], v1->unk20, v1->unk0, v1->unk4, v1->unk8, v1->unk24->unk1E, v1->unk88, 0, sp76, 2);
    }
    v1 = R36880D_G;
    if (arg9 != 0 || arg12 || arg10) {
        actorUpdateEntryCoordinates(v1->unk88, v1->unk0, v1->unk4, v1->unk8, v1->unkC, v1->unk14);
        v1 = R36880D_G;
    }
    if (v1->unk7C != NULL) {
        switch (v1->unk7C->unk67) {
            case 0:
                flag = 1;
                break;
            case 2:
                if (D_807FC924 != 0) {
                    i = 0;
                    if (D_807FC928 > 0) {
                        do {
                            if ((((R36880dPlayer *)D_807FC924)[i]).unk0 != 0) {
                                s32 hit = collisionCheckBoundingBoxY((u8 *)&D_807F6000[arg0] + 0x54, (((R36880dPlayer *)D_807FC924)[i]).unk4->unk80) != 0;
                                if (hit != 0) {
                                    hit = collisionCheckBoundingBoxXZ((u8 *)&D_807F6000[arg0] + 0x54, (((R36880dPlayer *)D_807FC924)[i]).unk4->unk7C, (((R36880dPlayer *)D_807FC924)[i]).unk4->unk84) != 0;
                                }
                                flag |= hit;
                            }
                            i++;
                        } while (i < D_807FC928);
                        v1 = R36880D_G;
                    }
                }
                break;
            case 1:
                if (D_807FC924 != 0) {
                    i = 0;
                    if (D_807FC928 > 0) {
                        do {
                            if ((((R36880dPlayer *)D_807FC924)[i]).unk0 != 0) {
                                flag |= collisionCheckBoundingBoxXZ((u8 *)&D_807F6000[arg0] + 0x54, (((R36880dPlayer *)D_807FC924)[i]).unk4->unk7C, (((R36880dPlayer *)D_807FC924)[i]).unk4->unk84);
                            }
                            i++;
                        } while (i < D_807FC928);
                        v1 = R36880D_G;
                    }
                }
                break;
            case 3:
            case 4:
                if (D_807FC924 != 0) {
                    flag = func_80635EF0(v1->unk0, v1->unk4, v1->unk8, v1->unk7C->unk68, v1->unk7C->unk6A, v1->unk7C->unk6C, v1->unk7C->unk67 == 3 ? 0xEF : 1);
                    v1 = R36880D_G;
                }
                break;
        }
    }
    if (flag != 0) {
        collisionTransformNode(arg0, v1->unk24, v1->unk0, v1->unk4, v1->unk8, v1->unk10, v1->unk14, v1->unk18, v1->unkC);
        v1 = R36880D_G;
        func_80634908(arg0, v1->unk24, v1->unk0, v1->unk4, v1->unk8, v1->unk10, v1->unk14, v1->unk18, v1->unkC);
        v1 = R36880D_G;
    }
    func_806333F8(arg0, (R36880bVertTable *)v1->unk24, v1->unk0, v1->unk4, v1->unk8, v1->unk10, v1->unk14, v1->unk18, v1->unkC, 1);
    v1 = R36880D_G;
    func_8063373C(arg0, (R36880bVertTable *)v1->unk24, v1->unk0, v1->unk4, v1->unk8, v1->unk10, v1->unk14, v1->unk18, v1->unkC, 1);
}
