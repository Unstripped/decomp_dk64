// func_806F1EB0 (src/global/F56F0.c): Stage 5 (parked NON_MATCHING): same saved regs, frame 0xF0, all FP code exact. Remaining ~11 diff lines: arg1 in s4 instead of s2 (the deadsweep-found 'if (i == 0) {}' after loop 1 is what makes index land in s7 but also makes i interfere with arg1), loop-1 preheader order (move v1,s0 before addiu v0,sp,0xa4) and the resulting sll/addu s1 placement. Tricks: ret = 0 (int) keeps its zero apart from the loop-hoisted 0.0f; (0 < ret) not 0.0f < ret; slot = arg1; slot += index gives addu base,off; one-line 'k++; cur++;' fixes the tail store order. Uses F56AState (0x13C stride) from src/global/F56F0.c.
extern s8 D_80752CBF[];

void func_806F1EB0(Actor *arg0, F5BSlot *arg1, s32 *arg2) {
    F56AState *state = ((F56AActor *) arg0)->unk178;
    F56APair *pair;
    F5BSlot *slot;
    f32 spE0;
    s32 index;
    s32 kind;
    s32 value;
    s32 i;
    s32 k;
    f32 spC8;
    f32 spC4;
    f32 ret;
    f32 angle;
    f32 pos[2][3];
    f32 y;
    f32 newvel;
    f32 delta;
    F56AState *cur;
    s32 active;
    f32 boost;
    f32 accel0;
    f32 accel1;

    index = *arg2;
    ret = 0;
    kind = 0x16;
    cur = state;
    active = func_806F1B58((F5BActor *) arg0, (F5N1Predicate *) state, 5);
    value = -0x80;
    actorGetNodePos(arg0, 0xD, &pos[0][0], &pos[0][1], &pos[0][2]);
    actorGetNodePos(arg0, 0xE, &pos[1][0], &pos[1][1], &pos[1][2]);
    angle = func_80611BB4(pos[0][2] - pos[1][2], pos[0][0] - pos[1][0]);
    if (active == 0) {
        for (i = 0; i != 2; i++) {
            state[i].unk0 = angle;
            state[i].unk4 = pos[i][1];
        }
        if (i == 0) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
        if ((state->unk14 != 0) && (((F56AActor *) arg0)->unk60 & 0x100) && (state->unk18 == 5)) {
            state->unk14 -= 1;
        }
    } else {
        s16 idx = ((F56AIdxSub *) arg0->unk4)->unk0->unk10;

        if (idx >= 0) {
            newvel = D_80752CBF[idx];
        } else {
            newvel = -128.0f;
        }
        state->unk10 = state->unk10 + ((newvel - state->unk10) * 0.3);
        value = (s8) (s32) state->unk10;
        ret = func_806F1B90(&state->unk0, angle);
        spE0 = func_806F1AE0((F5BActor *) arg0, (F5BAccel *) state, 0.02f);
    }
    slot = arg1; slot += index; k = 0; // FAKE: one source line lets as1 schedule the loop preheader
    do {
        accel1 = 0.0f;
        accel0 = 0.0f;
        spC8 = 0.0f;
        spC4 = 0.0f;
        pair = cur->unk1C;
        if (active != 0) {
            y = pos[k][1];
            newvel = y - cur->unk4;
            delta = newvel - cur->unk8;
            cur->unk4 = y;
            cur->unk8 = newvel;
            boost = 0.4f * ret;
            y = (0 < ret) ? ret : -ret;
            if (k != 0) {
                accel0 = -spE0;
                accel1 = -((y * 0.3f) + (-0.015f * delta - 0.0008f * newvel));
            } else {
                accel0 = spE0;
                accel1 = (y * 0.3f) + (-0.015f * delta - 0.0008f * newvel);
            }
            accel0 += boost;
        }
        i = 0;
        do {
            if (active != 0) {
                func_806F1A18(accel1, 0.06f, &pair->unk0, &spC8);
                func_806F1A18(accel0, 0.06f, &pair->unkC, &spC4);
            }
            slot->unk0 = value;
            slot->unk1 = kind;
            slot->unk2 = 0;
            slot->unk4 = (s32) ((pair->unkC.unk4 + pair->unkC.unk0) * 10430.218905280077);
            slot->unk6 = (s32) ((pair->unk0.unk4 + pair->unk0.unk0) * 10430.218905280077);
            i++;
            pair++;
            index++;
            slot++;
            kind++;
        } while (i != 8);
        k++; cur++; // FAKE: one source line orders the k/cur reload-increment-store tail
    } while (k != 2);
    *arg2 = index;
}
