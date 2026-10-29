// func_80690F30 (src/global/936B0.c): stage 4 (frame 0xE8, same s0-s7/fp + f20-f30 saves, every block/register/scheduling matches the target through the phase-3 slot loop; 12 diff lines). Remaining: (1) target computes the loop limit (D_80747D70*9*16 into v0) in BOTH switch exits (case arm after the v1 reload + default arm) and branches to the shared addiu/slt; ours computes it once at the merge in t-regs (4 insns short, size 0x...); (2) 'move s0,zero' sits in the blez delay slot in the target, ours places it before blez. K&R def (u16 arg0; u8 arg3-5; f32* arg6-8), unprototyped decl. Tried: for-loop offset forms (guard becomes product-based), do-while + guard, named lim/cnt locals (regalloc flips), default arm, C1/C3/C5/C6/C7 tails, deadsweep sweep round 1 (no gain), permuter (non-semantic output).
/* needs (936B0.c top): ProjectileActorSub174, ActorEntry, Actor, D_807FC924 (PlayerTrackEntry *); callers should declare s32 func_80690F30(); (K&R) */
typedef struct L690F30_Slot {
    f32 unk0;
    f32 unk4;
    f32 unk8;
    u8 padC[0x84 - 0xC];
    s16 unk84;
    u8 pad86[0x90 - 0x86];
} L690F30_Slot;

typedef struct L690F30_Player {
    u8 pad0[0x210];
    f32 unk210;
    f32 unk214;
    f32 unk218;
    u8 pad21C[0x228 - 0x21C];
    f32 unk228;
    f32 unk22C;
    f32 unk230;
    u8 pad234[0x2F0 - 0x234];
} L690F30_Player;

extern L690F30_Slot *D_807F6000;
extern s32 D_80747D70;
extern ActorEntry gActiveActors[];
extern u16 gActiveActorCount;
f32 func_80612790(s16);
f32 func_80612794(s16);

s32 func_80690F30(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8)
u16 arg0;
void **arg1;
Actor *arg2;
u8 arg3;
u8 arg4;
u8 arg5;
f32 *arg6;
f32 *arg7;
f32 *arg8;
{
    s32 padTop[2]; // FAKE: pads the top of the frame (home slots of the original's register-only locals)
    s32 ret;
    s32 i;
    Actor *a;
    u8 v1;
    s32 j;
    L690F30_Player *pl;
    u8 idx;
    ProjectileActorSub174 *sub;
    f32 d[3];
    f32 n[3];
    f32 padA4[1]; // FAKE: frame hole between the direction vector and n[]
    f32 dirX;
    f32 dirY;
    f32 dirZ;
    f32 pad94[1]; // FAKE: frame hole between best and the direction vector
    f32 best;
    f32 pad8C[1]; // FAKE: frame hole between ox and best
    f32 ox;
    f32 oy;
    f32 oz;
    f32 px;
    f32 py;
    f32 pz;
    f32 x1;
    f32 y1;
    f32 z1;
    f32 scale;
    f32 len;
    f32 dot;
    f32 t;
    f32 dx;
    f32 dy;
    f32 dz;
    f32 d2x;
    f32 d2z;
    f32 tmp;

    ret = 0;
    best = 0.7f;
    if (arg3) {
        best = 0.92f;
    }
    *arg1 = NULL;
    if (arg3) {
        idx = ((ProjectileActorSub174 *)arg2->unk174)->unk1A4;
        pl = &((L690F30_Player *)D_807FC924)[idx];
        x1 = pl->unk228;
        y1 = pl->unk22C;
        z1 = pl->unk230;
        ox = pl->unk210;
        oy = pl->unk214;
        oz = pl->unk218;
    } else {
        scale = arg2->unkB8 * 0.025f;
        x1 = func_80612794(arg2->unkEE) * scale + arg2->unk7C;
        z1 = func_80612790(arg2->unkEE) * scale + arg2->unk84;
        y1 = arg2->unk80 + arg2->unkC0 * 0.025f;
        ox = arg2->unk7C;
        oy = arg2->unk80;
        oz = arg2->unk84;
    }
    d[0] = x1 - ox;
    d[1] = y1 - oy;
    d[2] = z1 - oz;
    len = sqrtf((d[0] * d[0] + d[1] * d[1]) + d[2] * d[2]);
    if (len == 0.0) {
        len = 0.1f;
    }
    dirX = d[0] / len;
    dirY = d[1] / len;
    dirZ = d[2] / len;
    for (i = 0; i < gActiveActorCount; i++) {
        a = gActiveActors[i].actor;
        if (arg2 != a && (!(a->unk5C & 2) || a->unk154 != 0x37) && (a->unk5C & arg0)) {
            if (arg4 == 0 || ((oy < a->unk80) ? (a->unk80 - oy) : -(a->unk80 - oy)) < 30.0f) {
                v1 = 1;
                if (a->unk5C & 1) {
                    sub = a->unk174;
                    v1 = *(u8 *)&((L690F30_Player *)D_807FC924)[sub->unk1A4];
                }
                if (v1 != 0) {
                    tmp = (f32)((f64)a->unk80 + (f64)a->unk15E * 0.5);
                    d[0] = a->unk7C - ox;
                    t = tmp - oy;
                    d[1] = t;
                    d[2] = a->unk84 - oz;
                    len = sqrtf((d[0] * d[0] + d[1] * d[1]) + d[2] * d[2]);
                    if (len == 0.0) {
                        len = 0.1f;
                    }
                    n[0] = d[0] / len;
                    n[1] = d[1] / len;
                    n[2] = d[2] / len;
                    dot = (n[0] * dirX + n[1] * dirY) + n[2] * dirZ;
                    if (dot < 0.0) {
                        dot = 0.0f;
                    }
                    if (best < dot) {
                        d2x = a->unk7C - ox;
                        d2z = a->unk84 - oz;
                        if (sqrtf(d2x * d2x + t * t + d2z * d2z) < 1000.0f) {
                            best = dot;
                            *arg1 = a;
                            ret = 1;
                            *arg6 = a->unk7C;
                            *arg7 = a->unk80;
                            *arg8 = a->unk84;
                        }
                    }
                }
            }
        }
    }
    if (arg5 != 0) {
        if (D_80747D70 > 0) {
            j = 0;
            do {
                switch (((L690F30_Slot *)((u8 *)D_807F6000 + j))->unk84) {
                    case 0x125:
                    case 0x126:
                    case 0x127:
                    case 0x128:
                    case 0x129:
                        px = ((L690F30_Slot *)((u8 *)D_807F6000 + j))->unk0;
                        py = ((L690F30_Slot *)((u8 *)D_807F6000 + j))->unk4 + 10.0;
                        pz = ((L690F30_Slot *)((u8 *)D_807F6000 + j))->unk8;
                        dx = px - ox;
                        dy = py - oy;
                        dz = pz - oz;
                        d[0] = dx;
                        d[1] = dy;
                        d[2] = dz;
                        len = sqrtf((d[0] * d[0] + d[1] * d[1]) + d[2] * d[2]);
                        if (len == 0.0) {
                            len = 0.1f;
                        }
                        n[0] = d[0] / len;
                        n[1] = d[1] / len;
                        n[2] = d[2] / len;
                        dot = (n[0] * dirX + n[1] * dirY) + n[2] * dirZ;
                        if (dot < 0.0) {
                            dot = 0.0f;
                        }
                        if (best < dot && sqrtf(dx * dx + dy * dy + dz * dz) < 800.0f) {
                            best = dot;
                            *arg1 = NULL;
                            *arg6 = px;
                            *arg7 = py;
                            ret = 1;
                            *arg8 = pz;
                        }
                        break;
                }
                j += 0x90;
            } while (j < (D_80747D70 * 8 + D_80747D70) * 16); // FAKE: x * 9 * 16 spelled as shifts; plain * 0x90 hoists 144 into a register and emits multu
        }
    }
    return ret;
}
