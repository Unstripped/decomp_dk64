// func_806C850C (src/global/CC800.c): func_806C850C stage 6 (Nm3CC800): regalloc only, ~88 diff lines. u32 sel = arg1 gives single 'andi sel,a1,0xff' reg (no param copy), -new_var keeps -1 from folding to 255; extern volatile G00Slot34 D_807FD610[] + array accesses reproduce uncached slot loads. Remaining: uopt colors &D_807FBB48 const (adjsave 2.25=9/4) before sel (8/7 per use, +1/7 per extra use) so sel=s3/D=s2 vs target sel=s2/D=s3; -1 stores share li a1 (s8 unk247 + literal -1: shared li but in a1 not v1); slot load temps f8/f10/f16..f18 vs target f10,f16,f18..f8. Tried: s8/u8/s16/u16/register sel types, K&R, direct param use (param uncolored, lbu from home), dead if(sel){}, sel^=0, dead tests of D, two slot pointers (CSE'd), permuter 600s (no gain).
typedef struct G00Sub4 {
    /* 0x00 */ u8 pad0[0x1C];
    /* 0x1C */ u8 *unk1C;
    /* 0x20 */ u8 *unk20;
    /* 0x24 */ u8 *unk24;
} G00Sub4;

typedef struct G00ActorView {
    /* 0x000 */ u8 pad0[0xC4];
    /* 0x0C4 */ f32 unkC4;
    /* 0x0C8 */ f32 unkC8;
    /* 0x0CC */ u8 padCC[0x12];
    /* 0x0DE */ s16 unkDE;
    /* 0x0E0 */ u8 padE0[0x66];
    /* 0x146 */ s16 unk146;
    /* 0x148 */ u8 pad148[0x30];
    /* 0x178 */ G00Out *unk178;
} G00ActorView;

typedef struct G00Player {
    /* 0x000 */ u8 pad0[0x16];
    /* 0x016 */ s16 unk16;
    /* 0x018 */ u8 pad18[0xE];
    /* 0x026 */ s16 unk26;
    /* 0x028 */ u8 pad28[0xA0];
    /* 0x0C8 */ s16 unkC8;
    /* 0x0CA */ u8 unkCA;
    /* 0x0CB */ u8 padCB[9];
    /* 0x0D4 */ s16 unkD4;
    /* 0x0D6 */ u8 padD6[2];
    /* 0x0D8 */ u8 unkD8;
    /* 0x0D9 */ u8 padD9[3];
    /* 0x0DC */ u8 padDC[0x20];
    /* 0x0FC */ s32 unkFC;
    /* 0x100 */ s32 unk100;
    /* 0x104 */ Actor *unk104;
    /* 0x108 */ u8 pad108[4];
    /* 0x10C */ u8 unk10C;
    /* 0x10D */ u8 pad10D[0x11];
    /* 0x11E */ s16 unk11E;
    /* 0x120 */ s32 unk120;
    /* 0x124 */ u8 pad124[0x7C];
    /* 0x1A0 */ s16 unk1A0;
    /* 0x1A2 */ u8 pad1A2[2];
    /* 0x1A4 */ u8 unk1A4;
    /* 0x1A5 */ u8 pad1A5[7];
    /* 0x1AC */ s32 unk1AC;
    /* 0x1B0 */ s32 unk1B0;
    /* 0x1B4 */ u8 pad1B4[0xC];
    /* 0x1C0 */ f32 unk1C0;
    /* 0x1C4 */ f32 unk1C4;
    /* 0x1C8 */ f32 unk1C8;
    /* 0x1CC */ f32 unk1CC;
    /* 0x1D0 */ f32 unk1D0;
    /* 0x1D4 */ f32 unk1D4;
    /* 0x1D8 */ u8 pad1D8[0x16];
    /* 0x1EE */ s16 unk1EE;
    /* 0x1F0 */ s32 unk1F0;
    /* 0x1F4 */ u8 pad1F4[0x2A];
    /* 0x21E */ s16 unk21E;
    /* 0x220 */ u8 pad220[0x24];
    /* 0x244 */ u8 unk244;
    /* 0x245 */ u8 unk245;
    /* 0x246 */ u8 pad246;
    /* 0x247 */ u8 unk247;
    /* 0x248 */ u8 pad248[8];
    /* 0x250 */ s32 unk250;
    /* 0x254 */ u8 pad254[4];
    /* 0x258 */ f32 unk258;
    /* 0x25C */ f32 unk25C;
    /* 0x260 */ u8 pad260[4];
    /* 0x264 */ s32 unk264;
} G00Player;

typedef struct G00Slot34 {
    /* 0x00 */ u8 pad0[4];
    /* 0x04 */ f32 unk4;
    /* 0x08 */ u8 pad8[8];
    /* 0x10 */ f32 unk10;
    /* 0x14 */ f32 unk14;
    /* 0x18 */ f32 unk18;
    /* 0x1C */ f32 unk1C;
    /* 0x20 */ s16 unk20;
    /* 0x22 */ s16 unk22;
    /* 0x24 */ s16 unk24;
    /* 0x26 */ s16 unk26;
    /* 0x28 */ s16 unk28;
    /* 0x2A */ u8 pad2A[0xA];
} G00Slot34;

#define G00_P ((G00Player *)D_807FD580)
#define G00_A48 ((G00ActorView *)D_807FBB48)

extern s32 controllerGetPort(s32);
extern s32 D_8076A0A8;
extern f32 D_8075C4B0;
extern Actor *D_807F5D10;
extern f32 D_80753578[];
extern f32 D_807535E8[];
extern volatile G00Slot34 D_807FD610[];
void func_806E2C74(Actor *);
s32 flagGet(s32, s32);
void func_806F09F0(Actor *, u16);
void func_806CFF9C(Actor *);
void func_806C90C4(s32);
void func_806C8984(void);
void func_806C8D20(Actor *);

/* Parked (stage 6, regalloc only): `u32 sel = arg1` gives the single `andi sel,a1,0xff` register, but uopt colors the
 * &D_807FBB48 constant (adjsave 2.25) before sel (1.14), so ours has sel=s3/D=s2 where the target has sel=s2/D=s3.
 * Volatile slot reads stand in for the target's uncached loads; `-new_var` keeps the -1 stores from folding to 255. */
void func_806C850C(s32 arg0, u8 arg1) {
    G00Row *row;
    f32 flt;
    u32 sel;
    s32 new_var;

    sel = arg1;
    if (D_807FC928 >= 2) {
        D_8074E77C[sel] = D_8074E77C[controllerGetPort(sel)];
    }
    if (sel == 0 && D_8076A0A8 == 0x50) {
        D_8074E77C[0] = 0;
    }
    row = &D_8075C410[D_8074E77C[sel]];
    actorSpawn(row->unk0, row->unk8);
    D_807FBB44->unk60 &= ~0x1000;
    D_807FBB44->unk60 |= row->unkC;
    D_807FBB44->unk16E[0] = 0x42;
    D_807FBB44->unk16E[1] = 0x42;
    D_807FBB44->unk60 |= 0x01000000;
    if (D_807FC928 >= 2) {
        D_807FBB44->unk64 |= 0x200;
    }
    D_807FBB44->unk68 |= 0xC0;
    ((G00Sub4 *)D_807FBB44->unk4)->unk1C = heapAlloc(0x100);
    *((G00Sub4 *)D_807FBB44->unk4)->unk1C = 0;
    ((G00Sub4 *)D_807FBB44->unk4)->unk20 = heapAlloc(0x200);
    *((G00Sub4 *)D_807FBB44->unk4)->unk20 = 0xFF;
    ((G00Sub4 *)D_807FBB44->unk4)->unk24 = heapAlloc(0x200);
    new_var = 1;
    *((G00Sub4 *)D_807FBB44->unk4)->unk24 = 0xFF;
    D_807FBB48 = D_807FBB44;
    D_807FD580 = D_807FBB44->unk174;
    G00_P->unk247 = -new_var;
    G00_P->unk1A4 = sel;
    G00_P->unk11E = -new_var;
    G00_P->unk244 = 0;
    G00_P->unk120 = -0x64;
    D_807FD584 = row->unk4;
    G00_P->unk1EE = D_807FBB44->unk58;
    func_806E2C74(D_807FBB48);
    actorSpawn(0xBC, 0);
    G00_P->unk104 = D_807FBB44;
    if (sel == 0) {
        D_807F5D10 = D_807FBB44;
    }
    D_807FBB44->unk60 |= 0x100000;
    func_806C8D20(D_807FBB48);
    flt = D_8075C4B0;
    G00_P->unk26 = 0x64;
    G00_A48->unkC4 = D_80753578[D_807FD584];
    G00_A48->unkC8 = D_807535E8[D_807FD584];
    G00_P->unk250 = 0x78;
    G00_P->unkD4 = 0;
    G00_P->unkD8 = 0;
    G00_P->unkFC = 0;
    G00_P->unk100 = 0;
    G00_P->unk16 = 0;
    G00_P->unk10C = 0;
    G00_P->unk1A0 = 0;
    G00_P->unk1C0 = flt;
    G00_P->unk1C4 = flt;
    G00_P->unk1C8 = flt;
    G00_P->unk1CC = flt;
    G00_P->unk1D0 = flt;
    G00_P->unk1D4 = flt;
    G00_P->unk245 = 0;
    G00_P->unk21E = 0x1E;
    G00_P->unkC8 = -1;
    G00_P->unkCA = 0;
    G00_P->unkC8 = -1;
    G00_P->unk264 = -new_var;
    G00_P->unk258 = 1.0f;
    G00_P->unk25C = 1.0f;
    if (flagGet(0xCE, 0) != 0) {
        G00_P->unk1F0 |= 0x100000;
    }
    func_806C8220(1, G00_A48->unk178, D_807FBB48->unk58);
    G00_A48->unk146 = 0;
    func_806F09F0(D_807FBB48, *(u16 *)((u8 *)D_807FBB48 + 0x5A));
    G00_A48->unkDE = 0x400;
    G00_P->unk1B0 = 0;
    G00_P->unk1AC = 0;
    D_807FD610[sel].unk14 = D_807FD610[sel].unk4;
    D_807FD610[sel].unk18 = D_807FD610[sel].unk4;
    D_807FD610[sel].unk1C = D_807FD610[sel].unk4;
    D_807FD610[sel].unk22 = D_807FD610[sel].unk28;
    D_807FD610[sel].unk24 = D_807FD610[sel].unk28;
    D_807FD610[sel].unk26 = D_807FD610[sel].unk28;
    D_807FD610[sel].unk20 = D_807FD610[sel].unk28;
    D_807FD610[sel].unk10 = D_807FD610[sel].unk4;
    func_806CFF9C(D_807FBB48);
    func_806C90C4(arg0);
    func_806C8984();
}
