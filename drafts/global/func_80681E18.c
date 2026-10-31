// func_80681E18 (src/global/80150.c): Stage 5 (LgFB6b): frame 0x58, s0/ra match; 18 text diff lines with the 3 deadsweep FAKEs (score 150), another deadsweep round (var_v1 D_807FBB40 D_807FBB70 D_807FBB68, 4200 variants) found nothing. Remaining: (a) (D_807FBB68&2)?0:1 arg temp v1 vs target v0 (named u8/s32 temp, !(..), ==0 forms, void/s32/u8 toggles of slotQueueUpdate and sfxPlay.. all worse or equal); (b) case 3 target reloads s0 only after the unk144 store (nofake variant fixes case 3 to 1 insn but shifts the D_807FBB70 base a2->a3 and ring: score 195); (c) case 20 loop: target orders lbu v1,0x254(a2) before the bottom lw s0,0(t0). Dead 'if (var_v1) {}' after slotQueueUpdate wrecks the frame (3784).
void func_80681E18(void) {
    TagBarrelGroundHit *var_v1;
    s32 pad[3];

    var_v1 = (TagBarrelGroundHit *)D_807FBB40->unk174;
    if (!(D_807FBB40->unk60 & 0x10)) {
        D_807FBB40->unkA4 = 99999.0f;
        collisionCheckGroundAtPoint(D_807FBB40->unk7C, D_807FBB40->unk84, &D_807FBB40->unkA4);
        if (1 == *(s32 *)D_807FBB40->unk124) {
            if (func_8067B450(D_807FBB40) == 0) {
                D_807FBB40->unk154 = 0x14;
                D_807FBB40->unk144 = 1;
                D_807FBB40->unk60 &= ~0x8000;
                D_807FBB40->unk128 = 0;
            }
        }
    }
    if ((D_807FBB40->unk154 == 0) && (D_807FBB70.unk200 == 4)) {
        var_v1->unk0 = 0xA;
        D_807FBB40->unk154 = 1;
        D_807FBB40->unk144 = 1;
        var_v1->unk4 = (Actor *)D_807FBB70.unk1FC;
        D_807FBB40->unk60 |= 0x200000;
        if ((D_8076A0A8 == 0x11) || (D_8076A0A8 == 0xC9) || (D_8076A0A8 == 0xCC)) {
        } else {
            sfxAllocateChannel(0x48, 1.0f);
        }
    }
    switch (D_807FBB40->unk154) {
    case 0: {
        s32 sp44;
        if (D_8074E77C < 5) {
            sp44 = D_807FC950[D_8074E77C][0];
        }
        if (((Actor *)D_807FBB4C)->unk58 == 3 && sp44 >= 2) {
            D_807FBB40->unk60 |= 0x8000;
            D_807FBB40->unk132 = 1;
        } else {
            D_807FBB40->unk60 &= ~0x8000;
            D_807FBB40->unk128 = 0x78;
            D_807FBB40->unk132 = 2;
        }
        func_8065D254(D_807FBB40, 0x3C8, 0x40, 0x40, 0xC, 0xC, 1, 0x64, 0x78, 0, 1.0f);
        break;
    }
    case 1:
        var_v1->unk0--;
        if (var_v1->unk0 == 0) {
            sfxPlayFromActorWithAltitudeCheck(D_807FBB40, 0x1C6, 0xFF, 0x7F, 0);
            D_807FBB40->unk154 = 2;
            slotQueueUpdate(5, (D_807FBB68 & 2) ? 0 : 1, 0);
        }
        break;
    case 2:
        tagBarrelDespawnEffects();
        D_807FBB40->unk60 &= ~0x8000;
        D_807FBB40->unk128 = 0;
        actorAppendCallback(var_v1->unk4, (s32)D_807FBB40, 0x40, 1, 0, 0);
        func_8067AAB8((s32)D_807FBB40, var_v1->unk4, var_v1->unk4->unkE6, (f32) D_80750390, 0);
        func_806C7BAC((s32)var_v1->unk4, D_807FBB40);
        ((TagBarrelActorD580 *)D_807FD580)->unk1A3 = 1;
        D_807FBB40->unk154 = 3;
        break;
    case 3:
        if (D_807FBB70.unk0 != 0) {
            D_807FBB40->unk60 |= 0x8000;
            if (D_807FBB40 && D_807FBB40) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
            D_807FBB40->unk144 = 2;
            D_807FBB40->unk60 &= ~0x200000;
            D_807FBB40->unk154 = 0;
        }
        break;
    case 4:
    case 5:
    case 6:
    case 7:
    case 8:
    case 9:
    case 10:
    case 11:
    case 12:
    case 13:
    case 14:
    case 15:
    case 16:
    case 17:
    case 18:
    case 19:
        break;
    case 20: {
        s16 i;
        if (D_807FBB70.unk254 > 0) {
            i = 0;
            do {
                if (D_807FBB70.unk258[i++] == 1) {
                    D_807FBB40->unk144 = 2;
                    D_807FBB40->unk154 = 0x15;
                    if (D_807FBB40 && D_807FBB40) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
                }
                if (D_807FBB40 == 0) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
            } while (i < D_807FBB70.unk254);
        }
        break;
    }
    case 21:
        D_807FBB40->unk128 += 10;
        if (D_807FBB40->unk128 >= 0xF1) {
            D_807FBB40->unk60 |= 0x8000;
            D_807FBB40->unk154 = 0;
        }
        break;
    }
    actorUpdateModelMatrix(D_807FBB40, 0);
}
