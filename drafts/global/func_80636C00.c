// func_80636C00 (src/global/36880.c): func_80636C00: stage 5. 3-arg calls (no callee change). if(unk3C!=0) flag=0 else flag=1 fixes branch shape; (u8*)D_807F6000 + idx*0x90 (both uses) fixes t2/t3. Remaining ~13 rows: head/tail temp regs (target diffs v0/t0, B0 t5, head t6, tail t8; ours t0/t8, t6, t5, t7) and 2nd call a0 (target lw a0,0xA8(a3) direct, ours v0 + move a0,v0).
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

typedef struct R36880eSegOwner {
    /* 0x00 */ u8 pad0[0x20];
    /* 0x20 */ R36880eSeg *unk20;
} R36880eSegOwner;

typedef struct R36880eObjHdr {
    /* 0x00 */ u32 unk0;
    /* 0x04 */ u8 pad4[4];
    /* 0x08 */ s32 unk8;
    /* 0x0C */ u8 padC[0x10];
    /* 0x1C */ u8 unk1C;
    /* 0x1D */ u8 pad1D[0x1F];
    /* 0x3C */ s16 unk3C;
} R36880eObjHdr;

extern s16 D_80747D74;
void func_80636B50(R36880eCmd *, R36880eCmd *, u8);

void func_80636C00(void) {
    u32 mid;
    R36880eSeg *seg;
    u32 head;
    u32 tail;
    u8 flag;
    R36880eObjHdr *obj;
    ModelSlot *slot;

    if (D_80747D70 != 0) {
        D_80747D74 += 1;
        if (D_80747D74 >= D_80747D70) {
            D_80747D74 = 0;
        }
        slot = (ModelSlot *)((u8 *)D_807F6000 + D_80747D74 * 0x90);
        obj = (R36880eObjHdr *)slot->unk24;
        if (obj->unk0 & 0x10) {
            if ((slot->unk8C & 0x20) && D_8076A064 != obj->unk8) {
                slot->unk8C &= ~0x20;
                obj->unk3C -= 1;
                if (obj->unk3C != 0) {
                    flag = 0;
                } else {
                    flag = 1;
                }
                seg = ((ModelSlot *)((u8 *)D_807F6000 + D_80747D74 * 0x90))->unk20;
                mid = seg->unkA8;
                head = (mid - seg->unkA0) >> 3;
                tail = (seg->unkB0 - mid) >> 3;
                func_80636B50((R36880eCmd *)seg->unkA0, (R36880eCmd *)(seg->unkA0 + head * 8), flag);
                func_80636B50((R36880eCmd *)seg->unkA8, (R36880eCmd *)(seg->unkA8 + tail * 8), flag);
            }
        }
    }
}
