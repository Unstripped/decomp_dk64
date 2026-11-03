// func_806C850C (src/global/CC800.c): Player rev8: re-derived: only diff is s2/s3 (sel vs &D_807FBB48 const). uopt numbers: sel P-web total 8 over 25 live units (bucket 7 -> 1.14), const total 10 over 15 units (bucket 5 -> 2.0): colour order is adjsave, const first. Tried new: `if (&D_807FBB48) {}`-type dead address refs at every boundary (no change), sel -> arg1 spellings per use site (1500 random subsets, none better), arg1 used directly / K&R / u8 / s32 sel (worse). Needs sel total >= 14 or const total <= 5 with identical code: no spelling found. PREVIOUS: W2Frame 2026-11-03 (revisit 7 wave 2): unchanged park (full=41 text=37 shape=6, count-exact 330/330). Re-derived: ONLY diff is s2/s3 (sel vs &D_807FBB48 const). uopt: 'sel' is the formal arg1 web (P, 8 loads, total 8, unk1C=((8+17)-2)/4+2=7 -> adjsave 1.14); const 174 has 11 loads -1 needreglod, unk1C=5 -> 2.0; colour order is by adjsave so const goes first (s2). Dead ifs cannot flip it (they add blocks to both ranges and sel's x is always larger); flipping needs sel total >= 15 or const total <= 5. Tried (new): 'register' on sel/flt/row (no change), all 6 local declaration orders (worse), 'u32 sel = arg1;'/(u8) cast/u8 temp (same), no-code defs 'sel = sel ^ 0 / | 0 / + 0 / * 1 / & 0xFFFFFFFF' 1-8 copies at 6 anchors (fold away; 6 copies right after sel=arg1 make the formal a separate web -> worse), 'if (0) { stores of sel }' blocks (cfe deletes them), tail dead ifs (real code once repeated). Untried: a source where arg1 is read through a struct/array so its web has 7 more loads.
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
    /* 0x247 */ s8 unk247;
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
    /* 0x04 */ volatile f32 unk4; // FAKE: volatile steers the pad-copy load order
    /* 0x08 */ u8 pad8[8];
    /* 0x10 */ f32 unk10;
    /* 0x14 */ f32 unk14;
    /* 0x18 */ f32 unk18;
    /* 0x1C */ f32 unk1C;
    /* 0x20 */ s16 unk20;
    /* 0x22 */ s16 unk22;
    /* 0x24 */ s16 unk24;
    /* 0x26 */ s16 unk26;
    /* 0x28 */ volatile s16 unk28; // FAKE: volatile steers the pad-copy load order
    /* 0x2A */ u8 pad2A[0xA];
} G00Slot34;

#define G00_P ((G00Player *)gActivePlayerState)
#define G00_A48 ((G00ActorView *)D_807FBB48)

extern s32 controllerGetPort(s32);
extern s32 gCurrentMap;
extern f32 D_8075C4B0;
extern Actor *gCamActor;
extern f32 D_80753578[];
extern f32 D_807535E8[];
extern G00Slot34 gPlayerPadState[];
void func_806E2C74(Actor *);
s32 flagGet(s32, s32);
void func_806F09F0(Actor *, u16);
void playerResumeLocomotion(Actor *);
void func_806C90C4(s32);
void func_806C8984(void);
void func_806C8D20(Actor *);

void func_806C850C(s32 arg0, u8 arg1) {
    G00Row *row;
    f32 flt;
    u32 sel;

    sel = arg1;
    if (gPlayerCount >= 2) {
        gPlayerCharacterId[sel] = gPlayerCharacterId[controllerGetPort(sel)];
    }
    if (sel == 0 && gCurrentMap == 0x50) {
        gPlayerCharacterId[0] = 0;
    }
    row = &D_8075C410[gPlayerCharacterId[sel]];
    actorSpawn(row->unk0, row->unk8);
    D_807FBB44->unk60 &= ~0x1000;
    D_807FBB44->unk60 |= row->unkC;
    D_807FBB44->unk16E[0] = 0x42;
    D_807FBB44->unk16E[1] = 0x42;
    D_807FBB44->unk60 |= 0x01000000;
    if (gPlayerCount >= 2) {
        D_807FBB44->unk64 |= 0x200;
    }
    D_807FBB44->unk68 |= 0xC0;
    ((G00Sub4 *)D_807FBB44->unk4)->unk1C = heapAlloc(0x100);
    *((G00Sub4 *)D_807FBB44->unk4)->unk1C = 0;
    ((G00Sub4 *)D_807FBB44->unk4)->unk20 = heapAlloc(0x200);
    *((G00Sub4 *)D_807FBB44->unk4)->unk20 = 0xFF;
    ((G00Sub4 *)D_807FBB44->unk4)->unk24 = heapAlloc(0x200);
    *((G00Sub4 *)D_807FBB44->unk4)->unk24 = 0xFF;
    D_807FBB48 = D_807FBB44;
    gActivePlayerState = D_807FBB48->unk174;
    G00_P->unk247 = -1;
    G00_P->unk1A4 = sel;
    G00_P->unk11E = -1;
    G00_P->unk244 = 0;
    G00_P->unk120 = -0x64;
    D_807FD584 = row->unk4;
    G00_P->unk1EE = D_807FBB44->unk58;
    func_806E2C74(D_807FBB48);
    actorSpawn(0xBC, 0);
    G00_P->unk104 = D_807FBB44;
    if (sel == 0) {
        gCamActor = D_807FBB44;
    }
    D_807FBB44->unk60 |= 0x100000;
    func_806C8D20(D_807FBB48);
    flt = D_8075C4B0;
    if (D_8075C410) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
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
    G00_P->unk264 = -1;
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
    gPlayerPadState[sel].unk14 = gPlayerPadState[sel].unk4;
    gPlayerPadState[sel].unk18 = gPlayerPadState[sel].unk4;
    gPlayerPadState[sel].unk1C = gPlayerPadState[sel].unk4;
    gPlayerPadState[sel].unk22 = gPlayerPadState[sel].unk28;
    gPlayerPadState[sel].unk24 = gPlayerPadState[sel].unk28;
    gPlayerPadState[sel].unk26 = gPlayerPadState[sel].unk28;
    gPlayerPadState[sel].unk20 = gPlayerPadState[sel].unk28;
    gPlayerPadState[sel].unk10 = gPlayerPadState[sel].unk4;
    if (D_80753578) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
    playerResumeLocomotion(D_807FBB48);
    func_806C90C4(arg0);
    func_806C8984();
}
