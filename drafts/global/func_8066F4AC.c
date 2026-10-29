// func_8066F4AC (src/global/70FD0.c): stage 6 (frame 0x78 + callee-saved set equal; parked NON_MATCHING in 70FD0.c, 5 diff lines): target schedules move a1,s7 in the delay slot of the beqz after sp77 |= ret and uses s1 alone for flag/ret; mine emits move s0,s1 copy there then move a1,s7 later (beqzl s0 vs s1). Needed SLOT0 comma-operand macro for addu order, buf=&slot->unk28 before the 0x3D test
typedef struct Col7C_Node {
    /* 0x00 */ u8 pad0[0x10];
    /* 0x10 */ s32 unk10;
    /* 0x14 */ s32 unk14;
    /* 0x18 */ s32 unk18;
    /* 0x1C */ s32 unk1C;
    /* 0x20 */ u8 pad20[6];
    /* 0x26 */ u8 unk26;
    /* 0x27 */ u8 unk27;
    /* 0x28 */ struct Col7C_Node *next;
} Col7C_Node;

struct ActorTargetWork;
void actorUpdateSubActorOffsets(struct ActorTargetWork *, u8);
void func_80671880();
void func_8066F84C();
s32 func_80674ADC(s32, s32, s32, s32, s32, s32, s32, s32);
s32 func_80673708(s32, s32, s32, s32, s32, s32, s16 *, s16 *);
s32 func_806D0964(s32, u8);
extern u8 D_807FB548;
extern u8 D_807FB5FD;
extern u8 D_807FB5FF;
extern u8 D_807FB600;
extern u8 D_807FB601;
extern u8 D_807FB61C;

#define SLOT0 ((Col7A_Slot *)((0, i * sizeof(Col7A_Slot)) + (s32)D_807F6000)) // FAKE: comma operand steers addu operand order
#define SLOT ((Col7A_Slot *)((u8 *)D_807F6000 + i * sizeof(Col7A_Slot)))
u8 func_8066F4AC(CollisionActor *arg0, s16 *arg1, s16 *arg2) {
    u8 sp77;
    Col7C_Node *node;
    DynamicBuffer *buf;
    u8 *hit;
    s32 i;
    ActorSub140 *sub;
    u8 sp5F;
    u8 ret;
    u8 flag;

    sp77 = 0;
    sub = (ActorSub140 *)arg0->unk140;
    sub->unk6C = 0;
    D_807FB548 = 0;
    for (i = 0; i < D_80747D70; i++) {
        buf = &SLOT0->unk28;
        if (buf->unk15 & 2) {
            if (func_80674ADC(sub->unk0, sub->unk4, sub->unk8, sub->unkC, ((s32 *)buf)[0], ((s32 *)buf)[1], ((s32 *)buf)[2], ((s32 *)buf)[3]) != 0) {
                if (!(buf->unk15 & 1)) {
                    collisionTransformNode(i, (s32)(*SLOT).unk24, ((f32 *)&(*SLOT))[0], ((f32 *)&(*SLOT))[1], ((f32 *)&(*SLOT))[2], ((f32 *)&(*SLOT))[4], ((f32 *)&(*SLOT))[5], ((f32 *)&(*SLOT))[6], ((f32 *)&(*SLOT))[3]);
                } else {
                    buf->unk10 = D_8076A064;
                }
                if (!(arg0->unk5C & 1) || func_806D0964(*(s32 *)(*SLOT).unk24, arg0->unk174->unk1A4) == 0) {
                    func_80671880(arg0, 0);
                    flag = 1;
                    node = (Col7C_Node *)sub->unk8C;
                    D_807FB5FD = 0;
                    sp5F = D_807FB602;
                    hit = (u8 *)(*SLOT).unk7C;
                    if (hit != NULL) {
                        if (hit[0x6F] != 0) {
                            D_807FB5FD = 1;
                            D_807FB600 = 0;
                        }
                        flag = ((u8 *)(*SLOT).unk7C)[0x70];
                    }
                    if ((D_807FB5FD == 0 || (arg0->unk144 & 0x10)) && flag != 0) {
                        D_807FB5FF = 0;
                        ret = 0;
                        while (node != NULL && D_807FB5FF == 0) {
                            if (node->unk26 != 0 && node->unk1C != 0 && !(node->unk27 & 6)) {
                                ret |= func_80673708(node->unk10, node->unk14, node->unk18, node->unk1C, ((s32 *)buf)[6], ((s32 *)buf)[7], arg1, arg2);
                            }
                            node = node->next;
                        }
                        sp77 |= ret;
                        if (D_807FB601 != 0) {
                            if ((*SLOT).unk7C != NULL) {
                                ((u8 *)(*SLOT).unk7C)[0x5C] = D_807FB601;
                                *(s16 *)(&((u8 *)(*SLOT).unk7C)[0x5E]) = arg0->unk58;
                            }
                        }
                        if (D_807FB5FF != 0) {
                            func_8066F84C(i, arg0, ((s32 *)buf)[6]);
                        }
                        if ((*SLOT).unk7C != NULL && ((u8 *)(*SLOT).unk7C)[0x6E] == 0) {
                            D_807FB602 = sp5F;
                        }
                        if (ret != 0 && D_807FB5FD == 0 && D_807FB61C != 0) {
                            actorUpdateSubActorOffsets((struct ActorTargetWork *)arg0, 0);
                        }
                    }
                }
            }
        }
    }
    return sp77;
}
#undef SLOT0
#undef SLOT
