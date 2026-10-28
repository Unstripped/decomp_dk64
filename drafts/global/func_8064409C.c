// func_8064409C (src/global/478F0.c): stage 4-5: only diff: target loads p=cs->unk0 in a2 then 'move v1,a2' copy (all case accesses via v1, switch value lw t7,0(a2)); mine p and q coalesce into v1, and case 4 li a2,9 comes out li t2,9. frame var variant (case ends frame=q->unk4, case4 frame=9) fixed the PRE/delay-slot layout. Tried decl-order grid, multi-purpose var (copy survives but copy-prop replaces q by x in straight-line uses), permuter, deadsweep.
void *func_80610FE8(s32);
typedef struct {
    u32 unk0;
    s32 unk4;
    s32 unk8;
} CsB1SfxState;

typedef struct {
    CsB1SfxState *unk0;
    u8 pad4[0xC];
    s16 unk10;
} CsB1SfxView;

void func_80605380(s16);
void modelSlotSetNodeFrame(s32, s16, s32, s32);
void sfxPlayFromTargetSlot(s16, s32, s32, s32, s32, s32, f32);
s16 sfxSlotAllocateSource(s16, s32, s32, s32, s32, f32, s32);

void func_8064409C(CsState *cs, s16 csId, s16 b, s16 c) {
    CsB1SfxState *p;
    CsB1SfxState *q;
    CsB1SfxState *t;
    s32 frame;

    p = ((CsB1SfxView *)cs)->unk0;
    if (p == NULL) {
        t = func_80610FE8(0xC);
        ((CsB1SfxView *)cs)->unk0 = t;
        t->unk0 = 0;
        t->unk4 = 0;
        p = ((CsB1SfxView *)cs)->unk0;
    }
    q = p;
    switch (p->unk0) {
        case 0:
            q->unk4++;
            if (q->unk4 == 4) {
                q->unk8 = 0;
                q->unk0++;
                if (((CsB1SfxView *)cs)->unk10 < 0) {
                    ((CsB1SfxView *)cs)->unk10 = sfxSlotAllocateSource(csId, 0x12C, 0x3C, 1, 0x64, 1.0f, 0);
                }
            }
            frame = q->unk4;
            break;
        case 1:
            q->unk4++;
            if (q->unk4 == 7) {
                q->unk4 = 4;
                q->unk8++;
                if (q->unk8 == 0x1E) {
                    q->unk8 = 0;
                    q->unk0++;
                    if (((CsB1SfxView *)cs)->unk10 >= 0) {
                        func_80605380(((CsB1SfxView *)cs)->unk10);
                        ((CsB1SfxView *)cs)->unk10 = -1;
                    }
                    sfxPlayFromTargetSlot(csId, 0x74, 0xFF, 0x7F, 0, 0x50, 0.3f);
                }
            }
            frame = q->unk4;
            break;
        case 2:
            q->unk4 = 7;
            q->unk8++;
            if (q->unk8 == 0x28) {
                q->unk8 = 0;
                q->unk0++;
                sfxPlayFromTargetSlot(csId, 0x74, 0xFF, 0x7F, 0, 0x50, 0.3f);
            }
            frame = q->unk4;
            break;
        case 3:
            q->unk4 = 8;
            q->unk8++;
            if (q->unk8 == 0x28) {
                q->unk8 = 0;
                q->unk0++;
                sfxPlayFromTargetSlot(csId, 0x75, 0xFF, 0x7F, 0, 0x50, 0.3f);
            }
            frame = q->unk4;
            break;
        case 4:
            frame = 9;
            q->unk4 = frame;
            break;
        default:
            frame = q->unk4;
            break;
    }
    modelSlotSetNodeFrame(csId, 1, frame, 0);
}
