// bonusLightFlashGameUpdate (src/bonus/2690.c): OvlB 2026-11-03 (revisit 8): unchanged park, stage 5, deadsweep full 14 (text 10, reloc 4 = D_8002D8F4+off neighbour spelling vs splat names, harmless). Remaining text diff is ONE thing: target li v0,-100 / li v1,1 (else-arm D_8002D8FC=-0x64 and join D_8002D8F8=1, hoisted before bc1f) are uopt-coloured const webs (ugen ring is round-robin t2..t9 and never yields v0/v1), ours are ring temps t2/t3 so the following lh/lui/lb take t4/t5 instead of t2/t3. Findings: a dead compare on a real field in the else arm (if (t0->unk14 == -0x64) {} or D_807FBB40->unk154 == -0x64) DOES give li v0,-100 coloured (1048 grid variants) but emits it BEFORE c.lt.s (target: after lui at/c.lt.s) and no dead compare/typed local/dup store/copy through c,d,i,j,r of any type made the constant 1 a coloured web (constant 1 is one function-wide weak candidate): 0 of ~5000 variants gave li v1,1. Tried also: ternary (text 12), s16 local d/j carriers (forwarded away), sfxPlayOnFreeSlot prototype toggles (no change), function-local statics for D_8002D8F4/F8/FC (whole function shifts, text 101), 15k-eval dead-statement hill-climb over 15 symbols x 6 consts (no gain).
typedef struct {
    s16 unk0;
    char pad2[2];
    f32 unk4;
    s8 unk8[6];
    s16 unkE;
    char pad10;
    u8 unk11;
    u8 unk12;
    char pad13;
    s16 unk14;
    s16 unk16;
} BonusLightFlashState;

extern s8 D_8002D8F4;
extern s16 D_8002D8F8;
extern s16 D_8002D8FC;
extern s16 D_8002D8EC[];
void lightSetColor(f32, f32, f32, s32);
void func_80029E54(void *);
Gfx *func_80029B9C(Gfx *, Actor *);

void bonusLightFlashGameUpdate(void) {
    Struct_7548 *t1 = D_807FBB40->unk174;
    BonusLightFlashState *t0 = ((BonusActorExt *)D_807FBB40)->unk178;
    Point3f *p;
    f32 y;
    f32 z;
    s32 pad;
    s32 i;
    s32 j;
    s32 r;
    u8 c;
    s16 d;

    if (!(D_807FBB40->unk60 & 0x10)) {
        t1->unk23 = 5;
        t1->unk0 = -2;
        switch (gCurrentMap) {
        case 0x65:
            t0->unk16 = 0xA;
            D_8002D8F4 = 0x30;
            break;
        case 0x8D:
            t0->unk16 = 0xF;
            D_8002D8F4 = 0x30;
            break;
        case 0x8E:
            t0->unk16 = 5;
            D_8002D8F4 = 0x1E;
            break;
        case 0x8F:
            t0->unk16 = 0xA;
            D_8002D8F4 = 0x1E;
            break;
        }
        t0->unk14 = t0->unk16;
        t0->unkE = 0x3C;
        t0->unk12 = 0;
        c = gfxResourceCreate(1, textTableGetString(0x1A, 2, 1), 8, 0.0f, 0.0f, 0.0f);
        t0->unk11 = c;
        func_806FDAB8(c, 0.0f);
        t0->unk0 = 0x3C;
        t0->unk4 = 1.0f;
        playerStateQueueCallback(0x48, 0, 0);
        camSetTarget(BCAM->unk104, D_807FBB40, 4, 0x800, 0x1A, 0, 0x1F, 0x15, 0x10, 0, 0.05f);
        camStartPath(0, 0, 1);
        D_807FBB40->unkE8 = 0x9A;
        D_807FBB40->unk60 |= 0x800000;
        D_807FBB40->unk16A = 0xFF;
        D_807FBB40->unk16B = 0xFF;
        D_807FBB40->unk16C = 0xFF;
        i = 0;
        do {
            t0->unk8[i] = i | 0x80;
        } while (++i < 6);
        func_80029E54(D_807FBB40);
    }
    if (t1->unk0 > 0) {
        if (D_807FBB40->unk154 == 0) {
            t0->unk0 -= 1;
        } else {
            t0->unk0 = 0x3C;
        }
        if (t0->unk0 > 0) {
            t0->unk4 = t0->unk4 + 0.2f;
        } else {
            t0->unk4 = t0->unk4 - 0.2f;
        }
        if (t0->unk4 > 1.0) {
            t0->unk4 = 1.0f;
        }
        if (t0->unk4 < 0.0) {
            t0->unk4 = 0.0f;
        }
        lightSetColor(t0->unk4, t0->unk4, t0->unk4, 0);
        if (t0->unk4 == 0.0f) {
            j = (s16)(D_8002D8F8 - 1);
            ((s16 *)&D_8002D8F4)[2] = j;
            if (j <= 0) {
                sfxPlayOnFreeSlot(0x1A1, 0x7FFF, 63.0f, 1.0f, 0x50, 0);
                j = randomLcgNext() & 3; if (D_807FBB40->unk154 && D_807FBB40->unk154) {} if (j == 9) {} D_8002D8F8 = j + 2; // FAKE/LAYOUT: dead tests make j a coloured candidate (andi v1) and burn one ring temp (addiu t4); one line keeps the lw t0 reload below the sh
            }
            d = D_8002D8FC + 1;
            ((s16 *)&D_8002D8F4)[4] = d;
            if (d == 0xE) {
                sfxPlayOnFreeSlot(D_8002D8EC[randomLcgNext() & 3], 0x7FFF, 63.0f, 1.0f, 0x14, 0);
            }
        } else {
            if (randomFloat() < 0.5f) {
                D_8002D8FC = 0;
            } else {
                D_8002D8FC = -0x64;
            }
            D_8002D8F8 = 1;
        }
        if (t0->unk0 < -0x1E) {
            t0->unk0 = D_8002D8F4;
            i = 0;
            do {
                t0->unk8[i] = -1;
                i++;
            } while (i < 6);
            for (i = 0; i != 6; i++) {
                j = i;
                r = ((((((randomLcgNext() & 0xFFu) & 0xFFu) & 0xFFu) & 0xFFu) & 0xFFu) & 0xFFu) & 7;
                while (r >= 0) {
                    if (t0->unk8[j] == -1) {
                        r -= 1;
                        if (r >= 0) {
                            j += 1;
                        }
                    } else {
                        j += 1;
                    }
                    if (j >= 6) {
                        j = 0;
                    }
                }
                t0->unk8[j] = i | 0x80;
            }
        }
        t1->unk22 = 0;
        if (D_807FBB40->unk154 == 0 && (gPlayerPadState.unk30 >= 0x1F || gPlayerPadState.unk31 >= 0x1F)) {
            if (gPlayerPadState.unk2F > 0) {
                if (gPlayerPadState.unk2E < -0x28) {
                    t1->unk22 = 1;
                } else if (gPlayerPadState.unk2E >= 0x29) {
                    t1->unk22 = 3;
                } else {
                    t1->unk22 = 2;
                }
            } else if (gPlayerPadState.unk2E < -0x28) {
                t1->unk22 = 4;
            } else if (gPlayerPadState.unk2E >= 0x29) {
                t1->unk22 = 5;
            } else {
                t1->unk22 = 6;
            }
        }
        p = *D_807F5FD4 + t1->unk22;
        y = p->y;
        z = p->z;
        if (t1->unk22 != 0) {
            y += 27.0f;
            z -= 8.0f;
        }
        switch (bonusAimAndFire(p->x, y, z)) {
        case 1:
            break;
        case 2:
            t1->unk25 = 0xFF;
            sfxPlayOnFreeSlot(0x3BC, 0x7FFF, 63.0f, 1.0f, 0, 0);
            break;
        }
        switch (D_807FBB40->unk154) {
        case 0:
            if (t0->unk14 == 0) {
                D_807FBB40->unk154 = 2;
            }
            if (((Actor *)D_807FBB40->unk11C)->unk154 == 5) {
                D_807FBB40->unk154 = 1;
            }
            break;
        case 1:
            bonusEndLose(0, 1);
            camStartPath(0, 1, 0x11);
            D_807FBB40->unk154 = 3;
            break;
        case 2:
            bonusEndWin(0, 0);
            camStartPath(0, 1, 0x11);
            D_807FBB40->unk154 = 3;
            break;
        }
    } else {
        switch (t1->unk0) {
        case -2:
            if (D_807444EC != 1) {
                t1->unk0++;
                hudSpawnCountdownTimer(0xDC, 0x2A, ((u8 *)t0)[0xF]);
                func_8070D8C0(D_807FBB40, 0, 9);
            }
            break;
        case -1:
            if (!(D_807FBB40->unk60 & 0x2000000)) {
                t1->unk0 = 1;
                actorSetStateTwo((void *)D_807FBB40->unk11C);
                bonusResetAmmo(t1);
                sfxAllocateChannel(8, 1.0f);
            }
            break;
        }
    }
    renderCallbacksRegister(func_80029B9C, D_807FBB40, 3);
    actorUpdateModelMatrix(D_807FBB40, 0);
}
