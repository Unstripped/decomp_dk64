// func_806419F8 (src/global/42630.c): stage 5: regalloc only (same frame/branches/insn count 37). Mine: a(BB4C ptr)=v0, cam=a1, bc=v0; expected a=t7, cam=v0, bc=a1 (t=a0, pl=t6, p=v1 already match). Tried locals order/types (u8/s32 t), named bc/cam/pl, single || chain (needed: lh v0,0x29C after nop), deadsweep, permuter 200s.
typedef struct CsA2Player {
    /* 0x000 */ u8 pad0[4];
    /* 0x004 */ Actor *unk4;
    /* 0x008 */ u8 pad8[0x29C - 8];
    /* 0x29C */ s16 unk29C;
} CsA2Player;
typedef struct CsA2Cam {
    /* 0x00 */ u8 pad0[0xBC];
    /* 0xBC */ s16 unkBC;
} CsA2Cam;

s32 func_806419F8(void) {
    Actor *a = D_807FBB4C;
    CsA2Player *p = (CsA2Player *)D_807FC924;
    s32 t = a->unk154;
    void *cam = p->unk4->unk174;

    if ((t == 0x42 && (((CsA2Cam *)cam)->unkBC == 0x62 || ((CsA2Cam *)cam)->unkBC == 0x88 || ((CsA2Cam *)cam)->unkBC == 0x17)) || t == 0x52 || t == 0x67 ||
        p->unk29C == 0x1C || p->unk29C == 0x53) {
        return 0;
    }
    return 1;
}
