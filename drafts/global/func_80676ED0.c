// func_80676ED0 (src/global/7BBD0.c): 2-insn scheduling swap
u8 func_80676ED0(Beh7BB_Actor *arg0, s32 arg1, s32 arg2) {
    Beh7BB_ActorSub140 *sub140;
    s32 pad78;
    s32 sp74;
    s32 sp70;
    s32 sp6C;
    s32 sp68;
    s32 i;
    s32 pad60;
    s16 pad5E;
    s16 pad5C;
    u8 pad5B;
    u8 ret;
    ActorEntry *entry;
    u8 var_s3;
    Beh7BB_Node *node;
    Beh7BB_Actor *other;
    Beh7BB_ActorSub140 *other_sub140;

    ret = 0;
    var_s3 = 0;
    if (!(arg0->unk60 & 0x10)) {
        return 0;
    }
    sub140 = arg0->unk140;
    sp74 = sub140->unk0;
    sp70 = sub140->unk4;
    sp6C = sub140->unk8;
    sp68 = sub140->unkC;
    D_807FB600 = 0;
    i = 0;
    if (D_807FBB34 > 0) {
        entry = D_807FB930;
        do {
            other = (Beh7BB_Actor *)entry->actor;
            other_sub140 = other->unk140;
            if (!(other->unk60 & 0x2000) && (sub140 != other_sub140) && (other->unk144 != 1) && (other->unk60 & 0x10)) {
                if (func_80674ADC(sp74, sp70, sp6C, sp68, other_sub140->unk0, other_sub140->unk4, other_sub140->unk8, other_sub140->unkC)) {
                    node = sub140->unk8C;
                    D_807FB5FF = 0;
                    if (other->unk64 & 0x20) {
                        D_807FB5FD = 0;
                    } else {
                        D_807FB5FD = 1;
                    }
                    while (node != NULL && D_807FB5FF == 0) {
                        if (node->unk26 != 0 && !(node->unk27 & 2)) {
                            var_s3 |= func_80673708(node->unk10, node->unk14, node->unk18, node->unk1C, other_sub140->unkA4, other_sub140->unkA8, arg1, arg2);
                        }
                        node = node->unk28;
                    }
                    if (other->unk64 & 0x20) {
                        arg0->unkFC |= var_s3;
                    }
                    if (D_807FB5FF != 0) {
                        ret |= func_80677148((Actor *)arg0, (Actor *)other);
                    }
                }
            }
            i++;
            entry++;
        } while (i < D_807FBB34);
    }
    return ret;
}
