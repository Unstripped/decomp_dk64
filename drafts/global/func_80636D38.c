// func_80636D38 (src/global/36880.c): stage 4 (NM36A2): frame 0x48, callee-saved ra/s0/s1 match (159 diff lines). K&R def (u8 arg1/arg2): prototype must become void func_80636D38(); needs s32 func_80636EFC(R36880eCmd*,R36880eCmd*,R36880eNode*,u8) proto above, casts (u8*)obj,(R36880dAsset*)seg for func_80635468. Dead if(0){f(&sp24,&sp20,&sp3C)} stops sp2C/sp3C promotion (single &sp20 also gives stage 4; subsets swept) but kills CSE of A0/A8 loads (target loads A8/A0/B0 once, mine reloads). Remaining: arg2 promoted to a3 (target lbu 0x53(sp) each use; &arg2 alias fixes it, 163 lines), obj temp v0->s1 copy (target uses v0 for obj->unk8 store then or s1,v0), flags var v1 vs a3, reload of A0/A8.
typedef struct R36880eCmd {
    /* 0x0 */ u32 unk0;
    /* 0x4 */ s32 unk4;
} R36880eCmd;

typedef struct R36880eLink {
    /* 0x00 */ void *unk0;
    /* 0x04 */ void *unk4;
    /* 0x08 */ u8 pad8[4];
    /* 0x0C */ void *unkC;
    /* 0x10 */ void *unk10;
    /* 0x14 */ u8 pad14[4];
    /* 0x18 */ void *unk18;
    /* 0x1C */ void *unk1C;
    /* 0x20 */ u8 pad20[4];
    /* 0x24 */ void *unk24;
    /* 0x28 */ void *unk28;
    /* 0x2C */ u8 pad2C[0xA8];
    /* 0xD4 */ struct R36880eLink *unkD4;
} R36880eLink;

typedef struct R36880eSeg {
    /* 0x00 */ u8 pad0[0xA0];
    /* 0xA0 */ u32 unkA0;
    /* 0xA4 */ u32 unkA4;
    /* 0xA8 */ u32 unkA8;
    /* 0xAC */ u32 unkAC;
    /* 0xB0 */ u32 unkB0;
    /* 0xB4 */ s16 unkB4;
    /* 0xB6 */ s16 unkB6;
    /* 0xB8 */ R36880eLink *unkB8;
    /* 0xBC */ s32 unkBC;
    /* 0xC0 */ u8 padC0[3];
    /* 0xC3 */ u8 unkC3;
} R36880eSeg;

typedef struct R36880eDLObj {
    /* 0x00 */ u8 pad0[4];
    /* 0x04 */ s32 unk4;
    /* 0x08 */ u8 pad8[0x28];
    /* 0x30 */ s32 unk30;
} R36880eDLObj;

typedef struct R36880ePtrSet {
    /* 0x0 */ R36880eDLObj *unk0;
    /* 0x4 */ R36880eDLObj *unk4;
    /* 0x8 */ s32 *unk8;
} R36880ePtrSet;

typedef struct R36880eNode {
    /* 0x00 */ R36880ePtrSet unk0[2];
    /* 0x18 */ R36880ePtrSet unk18[2];
    /* 0x30 */ s32 unk30;
    /* 0x34 */ s16 unk34;
    /* 0x36 */ s16 unk36;
    /* 0x38 */ s16 unk38;
    /* 0x3A */ s16 unk3A;
    /* 0x3C */ s32 unk3C;
    /* 0x40 */ s32 unk40;
    /* 0x44 */ s32 unk44;
    /* 0x48 */ u8 unk48;
    /* 0x49 */ u8 unk49;
    /* 0x4A */ u8 unk4A;
    /* 0x4B */ u8 pad4B;
    /* 0x4C */ s32 unk4C;
    /* 0x50 */ s32 unk50;
    /* 0x54 */ s32 unk54;
    /* 0x58 */ s32 unk58;
    /* 0x5C */ s32 unk5C[29];
    /* 0xD0 */ u8 unkD0;
    /* 0xD1 */ u8 padD1[3];
    /* 0xD4 */ struct R36880eNode *unkD4;
} R36880eNode;

typedef struct R36880eObjHdr {
    /* 0x00 */ u32 unk0;
    /* 0x04 */ u8 pad4[4];
    /* 0x08 */ s32 unk8;
    /* 0x0C */ u8 padC[0x10];
    /* 0x1C */ u8 unk1C;
    /* 0x1D */ u8 pad1D[0x1F];
    /* 0x3C */ s16 unk3C;
} R36880eObjHdr;

typedef struct R36880eObj60 {
    /* 0x00 */ u8 pad0[0x14];
    /* 0x14 */ void *unk14;
    /* 0x18 */ void *unk18;
    /* 0x1C */ u8 pad1C[0x2E];
    /* 0x4A */ s16 unk4A;
    /* 0x4C */ s16 unk4C;
    /* 0x4E */ u8 unk4E;
    /* 0x4F */ u8 pad4F;
    /* 0x50 */ s32 unk50;
    /* 0x54 */ s32 unk54;
    /* 0x58 */ u8 pad58[3];
    /* 0x5B */ u8 unk5B;
} R36880eObj60;

typedef struct R36880dAsset {
    u8 pad[0x10];
} R36880dAsset;
void func_80635468(u8 *, R36880dAsset *);
void func_80635548(s32, u8 *);
s32 func_80636EFC(R36880eCmd *, R36880eCmd *, R36880eNode *, u8);

typedef struct R36880fObjHdr {
    /* 0x00 */ u32 unk0;
    /* 0x04 */ u8 pad4[4];
    /* 0x08 */ s32 unk8;
    /* 0x0C */ u8 padC[0x10];
    /* 0x1C */ u8 unk1C;
    /* 0x1D */ u8 pad1D[0x1F];
    /* 0x3C */ s16 unk3C;
} R36880fObjHdr;

#define SEG ((R36880eSeg *)arg0->unk20)
void func_80636D38(arg0, arg1, arg2)
ModelSlot *arg0;
u8 arg1;
u8 arg2;
{
    R36880eSeg *seg;
    R36880fObjHdr *obj;
    void *sp3C;
    u8 flags;
    u32 sp30;
    R36880eNode *sp2C;
    u8 sp2B;
    s32 sp24;
    s32 sp20;
    u8 var_v1;

    if (0) {
        func_80635548((s32)&sp24, 0);
        func_80635548((s32)&sp20, 0);
        func_80635548((s32)&sp3C, 0);
    }
    seg = arg0->unk20;
    obj = (R36880fObjHdr *)arg0->unk24;
    sp3C = seg;
    obj->unk8 = D_8076A064;
    flags = arg0->unk8C;
    if (!(flags & 0x20) && (!(obj->unk0 & 0x10) || arg2 != 0)) {
        arg0->unk8C = flags | 0x20;
        obj->unk3C += 1;
        if (obj->unk1C == 1) {
            sp2C = (R36880eNode *)((R36880eSeg *)arg0->unk20)->unkB8;
            sp24 = ((seg->unkA8 - seg->unkA0) >> 3) * 8;
            sp30 = (seg->unkB0 - seg->unkA8) >> 3;
            sp2B = func_80636EFC((R36880eCmd *)seg->unkA0, (R36880eCmd *)(seg->unkA0 + sp24), sp2C, arg2);
            sp20 = sp30 * 8;
            var_v1 = (sp2B | func_80636EFC((R36880eCmd *)seg->unkA8, (R36880eCmd *)(seg->unkA8 + sp20), sp2C, arg2)) & 0xFF;
            if (sp2C != NULL) {
                sp2B = var_v1;
                sp2B |= func_80636EFC((R36880eCmd *)seg->unkA4, (R36880eCmd *)(seg->unkA4 + sp24), sp2C, arg2);
                var_v1 = (sp2B | func_80636EFC((R36880eCmd *)seg->unkAC, (R36880eCmd *)(seg->unkAC + sp20), sp2C, arg2)) & 0xFF;
            }
            if (var_v1 != 0) {
                obj->unk0 &= ~0x10;
            }
        } else {
            if (((R36880eObj60 *)sp3C)->unk50 != 0 || arg1 != 0) {
                func_80635468((u8 *)obj, (R36880dAsset *)sp3C);
                return;
            }
            func_80635548((s32)obj, sp3C);
        }
    }
}
