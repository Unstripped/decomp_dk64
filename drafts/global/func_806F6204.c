// func_806F6204 (src/global/F9450.c): Stage 4: faithful traversal, activation, queue, and dispatch behavior; frame/register allocation diverges (0x78 vs target 0x48 with locally reconstructed views).
void func_806F6204(F9F1_Node *arg0, u8 arg1, F9F1_Rect *arg2) {
    s16 temp_s1;
    s16 temp_s1_2;
    s16 temp_v0_2;
    s32 temp_s3;
    s32 temp_v0;
    u8 var_v0_2;
    F9F2_PlayerActor *temp_s5;
    F9A_DestinationNode *temp_v0_3;
    F9A_DestinationNode *var_v0;
    F9F1_Node *var_s0;

    temp_s3 = arg1 & 0xFF;
    var_s0 = arg0;
    temp_s5 = F9F2_PLAYER[temp_s3].unk4;
    if (arg0 != NULL) {
        do {
            temp_v0 = func_80626BC8(var_s0->unk8, F9F2_TABLE[var_s0->unk14].unk10 + var_s0->unkA, var_s0->unkC, (s32)arg2->unk0, (s32)*(f32 *)arg2->pad4, (s32)arg2->unk8);
            if ((var_s0->unkE == 0) && ((f32)temp_v0 < ((f32)F9F2_TABLE[var_s0->unk14].unk12 + arg2->unkC)) && ((temp_v0_2 = var_s0->unk4, (temp_v0_2 == 0)) || (temp_v0_2 == temp_s5->unk58)) && (func_8063C2A8(var_s0->unk0) != 0) && (func_806F6644(var_s0->unk0, temp_s3 & 0xFF, var_s0->unk2) != 0)) {
                var_s0->unkE = 1;
                func_806362C4(var_s0->unk0, 1);
                if (var_s0->unk6 != -1) {
                    func_8060E430((u16)var_s0->unk6, 1, func_805FF030(D_8076A0AB, 1) & 0xFF);
                }
                if (D_807FC928 == 1) {
                    if (D_807FD734 == NULL) {
                        var_v0 = (F9A_DestinationNode *)D_807FD730;
                        D_807FD734 = var_v0;
                        if (var_v0 != NULL) {
                            do {
                                D_807FD734 = var_v0;
                                var_v0 = var_v0->next;
                            } while (var_v0 != NULL);
                        }
                    }
                    temp_v0_3 = func_806F53EC((F9A_SourceNode *)var_s0);
                    temp_v0_3->next = NULL;
                    if (D_807FD730 != NULL) {
                        D_807FD734->next = temp_v0_3;
                    } else {
                        D_807FD730 = (F9A_LinkedNode *)temp_v0_3;
                    }
                    D_807FD734 = temp_v0_3;
                }
                temp_s1 = var_s0->unk2;
                switch (temp_s1) {
                case 0x2B:
                case 0x205:
                case 0x206:
                case 0x207:
                case 0x208:
                    func_806F58A0(temp_s3 & 0xFF, var_s0->unk0, temp_s5);
                    var_v0_2 = D_807FC928;
                    break;
                case 0x11:
                case 0x8F:
                    func_806F5A48(temp_s3 & 0xFF, var_s0->unk0, temp_s5, temp_s1 & 0xFFFF);
                    var_v0_2 = D_807FC928;
                    break;
                default:
                    var_v0_2 = D_807FC928;
                    if ((s32)var_v0_2 >= 2) {
                        func_806F54E0(temp_s3 & 0xFF, temp_s1, var_s0->unk13);
                        var_v0_2 = D_807FC928;
                    }
                    break;
                }
                if ((s32)var_v0_2 >= 2) {
                    playerStateHandleSoundEffects(var_s0->unk2, temp_s3 & 0xFF);
                    func_806355DC(var_s0->unk0, 1);
                }
                if (D_807FBB64 & 0x10000) {
                    temp_s1_2 = var_s0->unk2;
                    if (temp_s1_2 != 0x1D2) {
                        func_806F5FE8(temp_s1_2, var_s0->unk8, var_s0->unkA, var_s0->unkC, 0x258);
                    }
                }
            }
            var_s0 = var_s0->next;
        } while (var_s0 != NULL);
    }
}
