// func_80670548 (src/global/70FD0.c): stage 5: every insn identical except frame size (384 vs 376, stack offsets); only local home-slot layout remains. Uses K&R def (caller declares s32 func_80670548(); in 70FD0.c) + u8 ret/res temp (res = call; ret = ret | res).
typedef struct L670548_Node {
    /* 0x00 */ u8 pad0[0x10];
    /* 0x10 */ s32 unk10;
    /* 0x14 */ s32 unk14;
    /* 0x18 */ s32 unk18;
    /* 0x1C */ s32 unk1C;
    /* 0x20 */ u8 pad20[6];
    /* 0x26 */ u8 unk26;
    /* 0x27 */ u8 pad27;
    /* 0x28 */ struct L670548_Node *unk28;
} L670548_Node;

typedef struct L670548_Sub {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ s32 unk8;
    /* 0x0C */ u8 padC[0x26 - 0xC];
    /* 0x26 */ s16 unk26;
    /* 0x28 */ f32 unk28[3];
    /* 0x34 */ f32 unk34[3];
    /* 0x40 */ f32 unk40[3];
    /* 0x4C */ f32 unk4C;
    /* 0x50 */ f32 unk50;
    /* 0x54 */ f32 unk54;
    /* 0x58 */ s16 unk58;
    /* 0x5A */ s8 unk5A;
    /* 0x5B */ u8 pad5B;
    /* 0x5C */ s32 unk5C;
    /* 0x60 */ s32 unk60;
    /* 0x64 */ s16 unk64;
    /* 0x66 */ u8 pad66[0x8C - 0x66];
    /* 0x8C */ L670548_Node *unk8C;
} L670548_Sub;

typedef struct L670548_Hit {
    /* 0x00 */ u8 pad0[0x53];
    /* 0x53 */ u8 unk53;
    /* 0x54 */ u8 pad54[8];
    /* 0x5C */ u8 unk5C;
    /* 0x5D */ u8 pad5D;
    /* 0x5E */ s16 unk5E;
    /* 0x60 */ u8 pad60[0xE];
    /* 0x6E */ u8 unk6E;
    /* 0x6F */ u8 pad6F[0x2C];
    /* 0x9B */ u8 unk9B;
} L670548_Hit;

typedef struct L670548_Rec {
    /* 0x00 */ f32 unk0;
    /* 0x04 */ u8 pad4[0x30];
} L670548_Rec; // size = 0x34

extern u8 D_807FB5FD;
extern u8 D_807FB600;
extern u8 D_807FB601;
extern u8 D_807FB603;
extern L670548_Rec D_807FD614[];
s32 hashTableLookup();
s32 func_80673708(s32, s32, s32, s32, s32, s32, s16 *, s16 *);
s32 func_806738D0(s32, s32, s32, s32, s32, s32);
s32 func_8067B1E0(Actor *);
void actorSetTargetAngleBounds();
struct Col7DWork;
struct Col7DPlane;
void func_80670C5C(struct Col7DWork *, s16, struct Col7DPlane *);
struct ActorMotionWork;
s32 func_80672328(struct ActorMotionWork *, f32, f32);

s32 func_80670548(arg0)
Actor *arg0;
{
    L670548_Sub *sub;
    u8 ret;
    s16 slot;
    DynamicBuffer *buf;
    f32 px[3];
    f32 py[3];
    f32 pz[3];
    f32 x;
    f32 y;
    f32 z;
    f32 pad1[8];
    f32 mtx[4][4];
    f32 pad2[16];
    f32 e1[3];
    f32 e2[3];
    f32 n[3];
    f32 out[3];
    s32 i;
    f32 scale;
    f32 inv;
    u8 bits;
    s32 res;
    u8 kind;
    L670548_Hit *hit;
    L670548_Node *node;

    kind = 0;
    sub = (L670548_Sub *)arg0->unk140;
    ret = 0;
    slot = hashTableLookup(sub->unk26);
    if (slot != -1) {
        buf = &D_807F6000[slot].unk28;
        if (!(buf->unk15 & 1)) {
            return 0;
        }
        D_807FB603 = buf->unk14;
        D_807FB5FD = 1;
        D_807FB600 = 1;
        D_807FB602 = 0;
        func_80672E90(sub->unk0, sub->unk4, sub->unk8);
        actorSetCameraBoundaryMode(arg0->unk58);
        hit = (L670548_Hit *)D_807F6000[slot].unk7C;
        if (hit != NULL) {
            if (hit->unk9B & 4) {
                kind = 1;
            }
            if (hit->unk9B & 8) {
                kind = 2;
            }
            if (hit->unk9B & 0x10) {
                kind = 3;
            }
            if (hit->unk9B & 0x20) {
                kind = 4;
            }
        }
        if (hit != NULL && hit->unk53 != 0) {
            ret = func_80673708(sub->unk0, sub->unk4, sub->unk8, sub->unk5C, ((s32 *)buf)[6], ((s32 *)buf)[7], &arg0->unkF4, &arg0->unkF6);
        } else {
            actorSetTargetAngleBounds(((s32 *)buf)[6] + sub->unk58 * 0x58);
            switch (kind) {
            case 0:
                ret = func_806738D0(sub->unk0, sub->unk4, sub->unk8, sub->unk5C, ((s32 *)buf)[6], ((s32 *)buf)[7]);
                func_80673708(sub->unk0, sub->unk4, sub->unk8, sub->unk5C, ((s32 *)buf)[6], ((s32 *)buf)[7], &arg0->unkF4, &arg0->unkF6);
                break;
            case 1:
            case 2:
                ret = func_80673708(sub->unk0, sub->unk4, sub->unk8, sub->unk5C, ((s32 *)buf)[6], ((s32 *)buf)[7], &arg0->unkF4, &arg0->unkF6);
                break;
            case 3:
            case 4:
                ret = func_80673708(sub->unk0, sub->unk4, sub->unk8, 0x64, ((s32 *)buf)[6], ((s32 *)buf)[7], &arg0->unkF4, &arg0->unkF6);
                break;
            }
        }
        if (D_807FB601 != 0 && hit != NULL) {
            ((L670548_Hit *)D_807F6000[slot].unk7C)->unk5C = D_807FB601;
            ((L670548_Hit *)D_807F6000[slot].unk7C)->unk5E = arg0->unk58;
        }
        if (D_807F6000[slot].unk7C != NULL && ((L670548_Hit *)D_807F6000[slot].unk7C)->unk6E != 0) {
            actorQueueCollisionCallbacks((CollisionActor *)arg0);
        }
        if (hit != NULL && hit->unk53 != 0 && D_807FD614[func_8067B1E0(arg0)].unk0 > 30.0) {
            ret = 1;
        }
        if (arg0->unk5C & 1) {
            func_80670C5C((struct Col7DWork *)arg0, slot, (struct Col7DPlane *)sub);
        }
        if (ret != 0) {
            func_8066C610(slot, sub->unk5A, mtx);
            guMtxXFMF(mtx, sub->unk4C, sub->unk50, sub->unk54, &x, &y, &z);
            if (kind == 1 || kind == 4) {
                arg0->unk7C = x;
                arg0->unk84 = z;
            } else {
                for (i = 0; i < 3; i++) {
                    guMtxXFMF(mtx, sub->unk28[i], sub->unk34[i], sub->unk40[i], &px[i], &py[i], &pz[i]);
                }
                e1[0] = px[2] - px[0];
                e1[1] = py[2] - py[0];
                e1[2] = pz[2] - pz[0];
                e2[0] = px[1] - px[0];
                e2[1] = py[1] - py[0];
                e2[2] = pz[1] - pz[0];
                n[0] = (e1[1] * e2[2]) - (e1[2] * e2[1]);
                n[1] = (e1[2] * e2[0]) - (e1[0] * e2[2]);
                n[2] = (e1[0] * e2[1]) - (e1[1] * e2[0]);
                inv = 1.0f / sqrtf(((n[0] * n[0]) + (n[1] * n[1])) + (n[2] * n[2]));
                out[0] = n[0] * inv;
                out[1] = n[1] * inv;
                out[2] = n[2] * inv;
                if (sub->unk60 != 0) {
                    D_807FB5D0 = sub->unk60 + 5;
                    if (sub->unk64 < D_807FB5D0) {
                        D_807FB5D0 = sub->unk64;
                    }
                } else {
                    D_807FB5D0 = sub->unk5C;
                    if (D_807FB5D0 < 0xF) {
                        D_807FB5D0 = 0xF;
                    }
                    if (sub->unk64 < D_807FB5D0) {
                        D_807FB5D0 = sub->unk64;
                    }
                }
                if (kind == 3) {
                    D_807FB5D0 = 0x46;
                }
                sub->unk60 = D_807FB5D0;
                scale = (f32)D_807FB5D0 / 8;
                out[0] = out[0] * scale;
                out[1] = out[1] * scale;
                out[2] = out[2] * scale;
                if (kind == 3 || func_80672328((struct ActorMotionWork *)arg0, x - out[0], z - out[2]) != 0) {
                    arg0->unk7C = x - out[0];
                    arg0->unk84 = z - out[2];
                }
            }
        } else {
            node = sub->unk8C;
            while (node != NULL) {
                if (node->unk26 != 0) {
                    res = func_80673708(node->unk10, node->unk14, node->unk18, node->unk1C, ((s32 *)buf)[6], ((s32 *)buf)[7], &arg0->unkF4, &arg0->unkF6);
                    ret = ret | res;
                }
                node = node->unk28;
            }
        }
    }
    return ret;
}
