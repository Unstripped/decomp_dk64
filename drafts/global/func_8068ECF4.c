// func_8068ECF4 (src/global/936B0.c): stage 5: frame 0x58/blocks/insn count equal (parked NON_MATCHING); only regalloc: target li t9,0x1000 hoisted above lh t7 so mfc1/andi t1/t2 vs mine t9/t0 (ring shift 2) and mul.s f0,f2,f18 operand order for 3.3f*unk38; tried s32/u32 casts, lim locals, split tgt, deadsweep 396 variants (no gain)
typedef struct Prj9A_CamView {
    u8 pad0[0x210];
    f32 unk210;
    u8 pad214[4];
    f32 unk218;
} Prj9A_CamView;
f32 func_80611BB4(f32, f32);
void func_807149C8(s32, s32, s32, s32);
s32 func_80714C08(void *, f32, Actor *, s32, s32);
struct PlayerTrackEntry;
extern struct PlayerTrackEntry *D_807FC924;
extern Actor *D_807FBB40;
extern u8 D_80720054;

void func_8068ECF4(s32 arg0, u8 arg1) {
    f32 tgt;
    f32 cur;
    s16 diff;
    f32 sp48;
    f32 sp44;
    f32 sp40;

    actorGetNodePos(D_807FBB40, arg0, &sp48, &sp44, &sp40);
    tgt = (s32)(func_80611BB4(((Prj9A_CamView *)D_807FC924)->unk218 - sp40, sp48 - ((Prj9A_CamView *)D_807FC924)->unk210) * 651.8986f + 1024.0f) & 0xFFF;
    cur = D_807FBB40->unkE6;
    if (cur < tgt) {
        diff = tgt - cur;
    } else {
        diff = cur - tgt;
    }
    if (diff > 0x800) {
        diff = 0x1000 - diff;
    }
    if (diff < 0x384) {
        f32 fv0;
        f32 scale;
        s32 alpha;
        f32 vol;
        f32 af;

        fv0 = (1024.0f - diff) * 0.0014285714f;
        if (fv0 < 1.0f) {
            scale = fv0;
        } else {
            scale = 1.0f;
        }
        af = (u32)arg1;
        alpha = (u32)(scale * af) & 0xFF;
        if (alpha != 0) {
            vol = 3.3f;
            if (D_807FBB40->unk4 != NULL) {
                vol = 3.3f * D_807FBB40->unk4->unk38;
            }
            func_807149C8(0xFF, 0xFF, 0xFF, alpha);
            func_80714C08(&D_80720054, vol, D_807FBB40, arg0, 2);
        }
    }
}
