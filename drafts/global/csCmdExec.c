// func_8063FA48 (src/global/42630.c): CsFA48c stage 5-6: deadsweep full 22 (text 22, shape 12). Fixed: spill split sp+56/60 and found a3 via case-0x7E-local 'u8 pan7' + dead 'if (found) {}' before 'found = 0;' (uninitialised read: NOT kept in the src park, which therefore scores worse; find an equivalent form) and after 'if (D_80748094 > 0) {'. Left: 0x7E ucvt(pan) web wins s0 over vol (higher adjsave), 0x68 &D_807F61F0 a3 vs v0, 0xE/0x7D andi a3,v1,0xff vs move a3,v1. Tried: &x==0 forms, 208 one-line joins, sfxPlayAtPositionPooled narrow-arg prototypes (256 combos), deadsweep 34528 variants, permuter.
void func_8063FA48(CsCmd *cmd, CsState *cs, s16 csId) {
    void *dm = &csId; // unused: address-taken csId, keeps found at sp+0xC3
    u8 found;
    s32 i;
    s32 slot;
    s32 h;
    u8 sel;
    f32 x;
    f32 y;
    f32 z;
    f32 px;
    f32 py;
    f32 pz;
    f32 cr;
    f32 cg;
    f32 cb;
    s16 idx;
    CsCamState *cam;
    Actor *actor;
    s32 map;
    s32 b;
    s32 c;
    s32 exit;
    s16 flag;
    s32 pad68; // unused: keep sx..sz at sp+0x60..0x58
    s32 pad64;
    f32 sx;
    f32 sy;
    f32 sz;
    u8 pan;
    u8 vol;
    volatile u8 pitch;
    f32 cx;
    f32 cy;
    f32 cz;
    u8 pan7;

if (found) {}
    found = 0; 
    switch (cmd->op) {
    case 0x95:
        D_807F693C = 0x80;
        break;
    case 0x92:
        ((CsCamState *)D_807FC924->unk4->unk174)->unk1F0 |= 0x40000800;
        break;
    case 0x91:
        D_807FBB4C->unkB8 = cmd->a;
        break;
    case 0x93:
        camSetZoneWeight(CMDB(cmd)->a, CMDB(cmd)->b);
        break;
    case 0x94:
        func_80724994(2, cmd->a, 0, 0, 0);
        break;
    case 0x90:
        D_807F6902 = cmd->a;
        break;
    case 0x96:
        D_807F6903 = cmd->a;
        break;
    case 0x8E:
        dynamicBufferFree(&D_807F6000[hashTableLookup(csId)].unk28);
        break;
    case 0x8F:
        modelSlotTriBufferRelease(&D_807F6000[hashTableLookup(csId)].unk48);
        break;
    case 0x85:
        func_8062D1A8();
        break;
    case 0x83:
        slotQueueSetDisplayMode(CMDB(cmd)->a, CMDB(cmd)->b, CMDB(cmd)->c);
        break;
    case 0x80:
        eepromSavePlayerData();
        break;
    case 0x81:
        D_807F693E |= 1 << cmd->a;
        break;
    case 0x82:
        D_807F693E &= ~(1 << cmd->a);
        break;
    case 0x7F:
        switch (cmd->b) {
        case 0:
            sel = 0;
            break;
        case 1:
            sel = 1;
            break;
        case 2:
            sel = 2;
            break;
        case 3:
            sel = 3;
            break;
        }
        func_8072EE0C(csId, CMDB(cmd)->a, sel);
        break;
    case 0x7C:
        D_80748094 = cmd->a;
        break;
    case 0x7B:
        modelSlotGetNodePos(csId, 1, cmd->b, &x, &y, &z);
        volumeTriggerSetPosition(cmd->a, x, y, z);
        break;
    case 0x7A:
        effectNodeSetSubVal(cmd->a, CMDB(cmd)->b);
        break;
    case 0x76:
        i = 0;
        for (; i < gActiveActorCount; i++) {
            actor = gActiveActors[i].actor;
            if (!(actor->unk60 & 0x2000) && actor->unk110 == 1 && csId == actor->unk10C) {
                actorAppendCallback(actor, 0, 8, 0, 0, 0);
            }
        }
        break;
    case 0x75:
        volumeTriggerSetEnabled(cmd->a, CMDB(cmd)->b);
        break;
    case 0x78:
        modelSlotGetNodePos(csId, 1, cmd->a, &px, &py, &pz);
        cam = D_807FC924->unk4->unk174;
        cam->unk22C = px;
        cam->unk230 = py;
        cam->unk234 = pz;
        break;
    case 0x74:
        cs->unk9B |= cmd->a;
        break;
    case 0x73:
        playerStateSetCallbackParameters(0, cmd->a, cmd->b, cmd->c);
        break;
    case 0x72:
        actorListGetOrSetState(cmd->a, CMDB(cmd)->b, 1);
        break;
    case 0x6E:
        D_807F693F = cmd->a;
        break;
    case 0x6D:
        func_8063A8C4(csId, 1, cmd->a / 100.0);
        break;
    case 0x6C:
        modelSkipListAdd(cmd->a);
        break;
    case 0x6B:
        flagSet(cmd->a, CMDB(cmd)->b, 0);
        break;
    case 0x79:
        flagSet(cmd->a, CMDB(cmd)->b, 2);
        break;
    case 0x84:
        flagSet(cmd->a, CMDB(cmd)->b, 1);
        break;
    case 0x66:
        if (D_807F61F0.unk8 == 0) {
            actorSpawn(0xB1, 0);
            actor = D_807FBB40;
            D_807F61F0.unk4 = D_807FBB44;
            D_807FBB40 = D_807FBB44;
            hudSpawnCountdownTimer(0xDC, 0x2A, CMDB(cmd)->a, &D_807F61F0);
            D_807F61F0.unk0 = D_807FBB44;
            D_807F61F0.unk8 = 1;
            D_807FBB40 = actor;
        }
        break;
    case 0x67:
        if (D_807F61F0.unk8 != 0) {
            actorSetStateTwo(D_807F61F0.unk0);
        }
        break;
    case 0x68:
        if (D_807F61F0.unk8 != 0) {
            actorDespawn(D_807F61F0.unk0);
            actorDespawn(D_807F61F4);
            D_807F61F0.unk8 = 0;
        }
        break;
    case 0x62:
        D_807F693A = cmd->a;
        break;
    case 0x60:
        actorSetTargetSlotByte(csId, CMDB(cmd)->a);
        break;
    case 0x5F:
        ((CsCamState *)D_807FC924->unk4->unk174)->unk1F0 |= (cmd->a << 16) + cmd->b;
        break;
    case 0x3B:
        ((CsCamState *)D_807FC924->unk4->unk174)->unk1F0 &= ~((cmd->a << 16) + cmd->b);
        break;
    case 0x8C:
        ((CsCamState *)D_807FC924->unk4->unk174)->unk1F4 |= (cmd->a << 16) + cmd->b;
        break;
    case 0x8B:
        ((CsCamState *)D_807FC924->unk4->unk174)->unk1F4 &= ~((cmd->a << 16) + cmd->b);
        break;
    case 0x5D:
        func_805FF158(CMDB(cmd)->a);
        break;
    case 0x5C:
        zoneEntrySetDisabled(CMDB(cmd)->a, CMDB(cmd)->b, CMDB(cmd)->c);
        break;
    case 0x5B:
        func_806C92C4(cmd->a);
        break;
    case 0x5A:
        cs->unk68 = cmd->a;
        cs->unk6A = cmd->b;
        cs->unk6C = cmd->c;
        break;
    case 0x57:
        lightGetColor(&cr, &cg, &cb, D_807F693A);
        lightSetColor(cmd->a / 1000.0 + cr, cmd->b / 1000.0 + cg, cmd->c / 1000.0 + cb, D_807F693A);
        break;
    case 0x4F:
        if (D_807F6938 != 16) {
            if (cmd->a != -2) {
                D_807F6918[D_807F6938] = cmd->a;
                D_807F6938++;
            } else {
                D_807F6918[D_807F6938] = D_807F6000[hashTableLookup(csId)].unk8A;
                D_807F6938++;
            }
        }
        break;
    case 0x50:
        if (D_807F6240[cmd->a] != -1) {
            modelSlotGetNodePos(D_807F6240[cmd->a], 1, cmd->b, &D_807F690C, &D_807F6910, &D_807F6914);
        }
        break;
    case 0x4E:
        slot = func_807146A4(cmd->a);
        func_807149B8(1);
        func_80714B84(slot, cmd->b / 100.0, csId, cmd->c, 0);
        break;
    case 0x4C:
        h = (s16)(modelAnimEntryGetUnkC(csId, cmd->a) + cmd->b);
        if (h < 0) {
            h = 0;
        }
        modelAnimEntrySetUnkC(csId, cmd->a, h);
        break;
    case 0x4B:
        proxPathSetEnabled(csId, CMDB(cmd)->a, CMDB(cmd)->b);
        break;
    case 0x46:
        cs->unk70 = cmd->a;
        break;
    case 0x47:
        cs->unk71 = cmd->a;
        break;
    case 0x4A:
        modelSlotUpdateTailKey(csId, 1, CMDB(cmd)->a, CMDB(cmd)->b);
        break;
    case 0x45:
        cs->unk60 = cmd->a;
        cs->unk62 = cmd->b;
        cs->unk66 = cmd->c;
        break;
    case 0x40:
        D_807FBB60 |= ((u16)cmd->a << 16) + (u16)cmd->b;
        break;
    case 0x88:
        D_807FBB68 |= ((u16)cmd->a << 16) + (u16)cmd->b;
        break;
    case 0x89:
        D_807FBB68 &= ~(((u16)cmd->a << 16) + (u16)cmd->b);
        break;
    case 0x3F:
        cs->unk6E = cmd->a;
        break;
    case 0x3E:
        cs->unk6F = cmd->a;
        break;
    case 0x3D:
        cs->unk67 = cmd->a;
        break;
    case 0x39:
        cs->unk4F = cmd->a;
        break;
    case 0x36:
        func_80641BCC(cmd->a, cmd->b, csId);
        break;
    case 0x35:
        func_80641C98(cmd->a, cmd->b, csId);
        break;
    case 0x33:
        mapOffsetSlotSetTarget(cmd->a, cmd->b, cmd->c / 100.0f);
        break;
    case 0x55:
        mapOffsetSlotSetEnabled(cmd->a, CMDB(cmd)->b);
        break;
    case 0x34:
        mapOffsetSlotAddTarget(cmd->a, cmd->b, cmd->c / 100.0f);
        break;
    case 0x6A:
        effectNodeAddTargetAndStep(cmd->a, cmd->b, cmd->c / 100.0f);
        break;
    case 0x69:
        effectNodeSetTargetAndStep(cmd->a, cmd->b, cmd->c / 100.0f);
        break;
    case 0x26:
        func_8064199C(cs, cmd->a, cmd->b);
        break;
    case 0x54:
        slot = hashTableLookup(D_807F6240[cmd->a]);
        if (slot != -1) {
            func_8064199C(D_807F6000[slot].unk7C, cmd->b, cmd->c);
        }
        break;
    case 0x25:
        func_80641DA0(cs, cmd->a, cmd->b, cmd->c);
        break;
    case 0x3C:
        if (cs->unk94 != NULL) {
            actorDespawn(cs->unk94);
            cs->unk94 = NULL;
        }
        break;
    case 0x30:
        func_805FF378(cmd->a, 0);
        break;
    case 0x86:
        func_806CF398(D_807FBB48);
        func_805FF9AC(0x2A, 0, cmd->a, 2);
        break;
    case 0x87:
        func_805FF898();
        break;
    case 0x8D:
        D_80744824 = 2;
        func_806CF398(D_807FBB48);
        slot = func_805FF030(D_8076A0A8, 0);
        if (func_805FEF74(D_8076A0A8) != 0) {
            map = D_8074809C[slot];
            exit = D_807480AC[slot];
            if (map && map) {}
            if (flagGet(D_807480BC[slot], 0, exit) == 0) {
                if (map == 0x57) {
                    exit = 0x15;
                } else {
                    exit = 0;
                }
            }
            if (cutsceneTriggerCheck(map) == 0) {
                func_805FF378(map, exit);
            }
        } else {
            func_80600044(slot);
        }
        break;
    case 0x31:
        if (cmd->c & 0x100) {
            func_8070B308(2);
            func_805FF158(0);
        }
        switch (cmd->c & 0xFF) {
        case 0:
            flag = 0;
            break;
        case 1:
            flag = 1;
            break;
        case 2:
            flag = 3;
            break;
        }
        func_805FF9AC(cmd->a, cmd->b, 0, flag);
        break;
    case 0x32:
        func_805FF628(cmd->a, cmd->b);
        break;
    case 0x2F:
        func_8060B49C(D_807FBB48, cmd->a);
        break;
    case 0x11:
        modelAnimEntryStart(csId, cmd->a, cmd->b);
        break;
    case 0x12:
        modelAnimEntryStop(csId, cmd->a);
        break;
    case 0x13:
        modelAnimEntryClearTime(csId, cmd->a);
        break;
    case 0x14:
        modelAnimEntrySetUnkC(csId, cmd->a, cmd->b);
        break;
    case 0x15:
        modelAnimEntrySetUnkF(csId, cmd->a, cmd->b);
        break;
    case 0x16:
        modelAnimEntrySetUnk10(csId, cmd->a, cmd->b);
        break;
    case 0x17:
        modelAnimEntryResetFrame(csId, cmd->a, cmd->b);
        break;
    case 0x18:
        modelAnimEntrySetUnk12(csId, cmd->a, cmd->b);
        break;
    case 0x1A:
        modelAnimEntrySetTime(csId, cmd->a, cmd->b, cmd->c / 100.0);
        break;
    case 0xE:
        pan = (cmd->b / 128) & 0xFF;
        vol = (cmd->c / 128) & 0xFF;
        c = cmd->c;
        c &= 0xFF;
        c &= 0x7F;
        if (pan == 0) {
            pan = 0x7F;
        }
        if (vol == 0) {
            vol = 0xFF;
        }
        i = cmd->b & 1;
        b = cmd->b;
        b &= 0xFF;
        if (cs->unk10[i] < 0) {
            b &= 2;
            cs->unk10[i] = sfxSlotAllocateSource(csId, cmd->a, c, b, vol, (u32)pan / 127.0, 0);
        }
        break;
    case 0x7D:
        pan = (cmd->b / 128) & 0xFF;
        vol = (cmd->c / 128) & 0xFF;
        c = cmd->c;
        c &= 0xFF;
        c &= 0x7F;
        if (pan == 0) {
            pan = 0x7F;
        }
        if (vol == 0) {
            vol = 0xFF;
        }
        i = cmd->b & 1;
        b = cmd->b;
        b &= 0xFF;
        if (cs->unk10[i] < 0) {
            b &= 2;
            cs->unk10[i] = sfxSlotAllocateSource(csId, cmd->a, c, b, vol, (u32)pan / 127.0, D_80748094);
        }
        break;
    case 0xF:
        pan = (cmd->b / 128) & 0xFF;
        vol = (cmd->c / 128) & 0xFF;
        c = cmd->c;
        c &= 0xFF;
        c &= 0x7F;
        if (pan == 0) {
            pan = 0x7F;
        }
        if (vol == 0) {
            vol = 0xFF;
        }
        i = cmd->b & 0x7F;
        sfxPlayFromTargetSlot(csId, cmd->a, vol, pan, i, c, 0.3f);
        break;
    case 0x7E:
        pan7 = (cmd->b / 128) & 0xFF;
        vol = (cmd->c / 128) & 0xFF;
        c = cmd->c;
        c &= 0xFF;
        c &= 0x7F;
        if (pan7 == 0) {
            pan7 = 0x7F;
        }
        if (!vol) {
            vol = 0xFF;
        }
        i = cmd->b & 0x7F;
        if (D_80748094 > 0) {
            if (found) {}
            pitch = c;
            modelSlotGetNodePos(csId, 1, D_80748094, &sx, &sy, &sz);
            sfxPlayAtPositionPooled(sx, sy, sz, cmd->a, vol, pan7, i, pitch, 0.3f, 0);
        } else {
            sfxPlayOnFreeSlot(cmd->a, 0x7FFF, 0x427C0000, (u32)pan7 / 127.0, 0, 0);
        }
        break;
    case 0x10:
        if (cs->unk10[cmd->b] >= 0) {
            sfxSlotFreeSource(cs->unk10[cmd->b]);
            cs->unk10[cmd->b] = -1;
        }
        break;
    case 0x48:
        sfxSetVolumeAndPan(cs->unk10[cmd->a], cmd->b * 0.0001220703125, cmd->c);
        break;
    case 0xA:
        cs->unk50 = cmd->a;
        cs->unk78 = cmd->b / 100.0f;
        cs->unk7C = cmd->c / 100.0f;
        break;
    case 0xB:
        cs->unk80 = (f32)cmd->a;
        cs->unk82 = (f32)cmd->b;
        break;
    case 0xC:
        cs->unk84 = (f32)cmd->a;
        cs->unk86 = (f32)cmd->b;
        break;
    case 0xD:
        cs->unk88 = (f32)cmd->a;
        cs->unk8A = (f32)cmd->b;
        break;
    case 0x9:
        if (D_807F61FC != D_807F621C || D_807F6204 != D_807F6224) {
            func_80642480(cmd->a, csId);
        }
        break;
    case 0x41:
        D_807F6904 = 1;
        break;
    case 0x6:
        cs->unk14[cmd->a] = cmd->b / 10.0f;
        break;
    case 0x0:
        func_80642748(cmd->a, cmd->b, cs, csId, 1);
        break;
    case 0x8:
        func_80642844(cmd->a, cmd->b, cs, csId, 1);
        break;
    case 0x1E:
        func_80642748(cmd->a, cmd->b, cs, csId, 0);
        break;
    case 0x1D:
        func_80642844(cmd->a, cmd->b, cs, csId, 0);
        break;
    case 0x3:
        if (cmd->a == 0) {
            cs->unk44[cmd->c] = cmd->b;
        } else {
            cs->unk44[cmd->c] = cs->unk14[cmd->b];
        }
        break;
    case 0x65:
        cs->unk4B[cmd->b] += cmd->a;
        break;
    case 0x1:
        cs->unk4B[cmd->b] = cmd->a;
        break;
    case 0x5:
        if (func_806418E8(cmd->a, cmd->b, cmd->c) == 0) {
            return;
        }
        break;
    case 0x2D:
        i = 0;
        for (; i < gActiveActorCount; i++) {
            actor = gActiveActors[i].actor;
            if (!(actor->unk60 & 0x2000) && actor->unk110 == 1 && csId == actor->unk10C) {
                if (cmd->a != 0) {
                    actor->unk68 |= 4;
                } else {
                    actor->unk68 &= ~4;
                }
            }
        }
        break;
    case 0x7:
        D_80747E70[cmd->a](cs, csId, cmd->b, cmd->c);
        break;
    case 0x37:
        actorAppendCallback(D_807FC924->unk4, 0, 0x400000, CMDB(cmd)->a, 0, 0);
        break;
    case 0x19:
        playerStateQueueCallback(cmd->a, 0, 0);
        break;
    case 0x2C:
        modelSlotGetNodePos(csId, 1, cmd->a, &cx, &cy, &cz);
        func_8067A9F0(0, D_807FC924->unk4, cx, cy, cz);
        break;
    case 0x2B:
        func_80636014(csId, 1, CMDB(cmd)->a);
        break;
    case 0x1B:
        if (D_807F6240[cmd->a] != -1) {
            modelSlotGetNodePos(D_807F6240[cmd->a], 1, cmd->b, &D_807F621C, &D_807F6220, &D_807F6224);
        }
        break;
    case 0x1C:
        if (D_807F6240[cmd->a] != -1) {
            idx = hashTableLookup(D_807F6240[cmd->a]);
            if (idx != -1) {
                if (D_807F6000[idx].unk7C != NULL) {
                    found = 1;
                    D_807F6000[idx].unk7C[cmd->b + 0x48] += cmd->c;
                }
            }
        }
        if (found == 0) {
            return;
        }
        break;
    case 0x2:
        func_80723284(cs->unk38, CMDB(cmd)->a);
        break;
    case 0x1F:
        func_807232EC(cs->unk38, CMDB(cmd)->a);
        break;
    case 0x20:
        func_80723380(cs->unk38, CMDB(cmd)->a);
        break;
    case 0x21:
        func_80723320(cs->unk38, cmd->a);
        break;
    case 0x24:
        func_8072334C(cs->unk38, CMDB(cmd)->a);
        break;
    case 0x22:
        cs->unk38 = func_80723020(0, cmd->a, CMDB(cmd)->b, D_807F621C, D_807F6220, D_807F6224, cmd->c);
        break;
    case 0x23:
        func_80723428(cs->unk38);
        cs->unk38 = -1;
        break;
    case 0x4:
        func_80723484(cs->unk38);
        func_807238D4(cs->unk38, &D_807F621C, &D_807F6220, &D_807F6224);
        break;
    case 0x27:
        modelSlotSetNodeAnimMode(csId, cmd->a, CMDB(cmd)->b);
        break;
    case 0x28:
        modelSlotSetNodeFrame(csId, cmd->a, cmd->b, cmd->c);
        break;
    case 0x42:
        modelSlotSetNodeScrollSpeed(csId, cmd->a, cmd->b, cmd->c);
        break;
    case 0x29:
        cam = D_807FC924->unk4->unk174;
        camStartShakeFromPoint(cam->unk104, CMDB(cmd)->a, cmd->b, D_807F621C, D_807F6220, D_807F6224, D_807F6906, D_807F6908);
        break;
    case 0x44:
        D_807F6906 = cmd->a;
        D_807F6908 = cmd->b;
        break;
    case 0x2A:
        ((CsModelSlot2 *)D_807F6000)[hashTableLookup(csId)].unk3C = cmd->a;
        break;
    case 0x2E:
        mapByteArraySet(cmd->a, CMDB(cmd)->b);
        break;
    case 0x38:
        mapObjectSetByte(cmd->a, CMDB(cmd)->b, CMDB(cmd)->c);
        break;
    case 0x61:
        if (cmd->c != 0) {
            sfxAllocateChannel(cmd->a, cmd->c / 255.0);
        } else {
            sfxAllocateChannel(cmd->a, 1.0f);
        }
        break;
    case 0x6F:
        sfxStopChannel(cmd->a, CMDB(cmd)->b);
        break;
    case 0x70:
        seqRouteChannelVolume(cmd->a, cmd->b / 255.0);
        break;
    case 0x71:
        sfxSetChannelTempo(cmd->a, cmd->b * 0.0001220703125);
        break;
    case 0x43:
        if (cmd->a == 1) {
            cs->unk8 = cs->unk14[cmd->b];
            cs->unkC = cs->unk14[cmd->c];
        } else {
            cs->unk8 = cmd->b / 10.0f;
            cs->unkC = cmd->c / 10.0f;
        }
        break;
    case 0x49:
        func_8067ABC0(0, D_807FC924->unk4, CMDB(cmd)->a, cmd->b, cmd->c, D_807F621C, D_807F6220, D_807F6224);
        break;
    case 0x4D:
        idx = modelSlotAppend(cmd->a, D_807F690C, D_807F6910, D_807F6914, D_807F6910 - D_807F6218, 0);
        if (cmd->b == 0) {
            func_80641B00(idx, csId, cmd->c);
        }
        break;
    case 0x51:
        gridMoveNode(csId, D_807F621C, D_807F6220, D_807F6224);
        break;
    case 0x5E:
        func_80641874(cmd->a, cmd->b);
        break;
    case 0x8A:
        func_806417BC(cmd->a, cmd->b);
        break;
    case 0x63:
        func_8068B830(cmd->a, cmd->b, cmd->c);
        break;
    case 0x64:
        func_8068B8FC();
        break;
    case 0x56:
        func_80724994(1, cmd->a, 0, 0, 0);
        break;
    case 0x59:
        func_80724994(3, cmd->a, cmd->b, 0, 0);
        break;
    case 0x58:
        if (func_805FFE50(cmd->a, cmd->b, cmd->c) == 0) {
            func_8063DB3C(cmd->a, cmd->b, cmd->c);
        }
        break;
    case 0x77:
        modelAnimEntrySetUnk13(csId, cmd->a, CMDB(cmd)->b, cmd->c / 1000.0);
        break;
    }
}
