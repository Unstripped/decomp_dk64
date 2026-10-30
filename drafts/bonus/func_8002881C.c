// func_8002881C (src/bonus/2690.c): stage 5: frame 0x58 and every insn match; ONLY diff: first vertex loop (i 4..6) block after the (u32)fy conv: target 'ctc1 t0,$31; slti at,v1,7; sh t1,6(v0); c.lt.s', ours 'ctc1; sh; slti'. slti is the as1-expanded 'blt $3,7' hoisted across the fx/fy diamonds into the conv join block as a NOP filler (mini repro on a 20-line TU: slti always lands after the last store when diamonds follow; lands before it only when no diamond/branch sits between store and loop end). Key: local vb[2] array (idx@0x40,base@0x3c) + chk temp, decl order link,sp50,sp4C,sub,chk,vb,sp38,p,fx,fy,sp28,i; heapAlloc(0x38) takes 1 arg. Tried (all leave 2 diff lines): all 360 store/i++ orders, dead 'if (!p && !p) {}'/ 'if (p==0) {}' etc. at every body position, & 0xFFFF / (u16)/(s16) casts on unk2/unk6, p->unk1 = i++, do{}while(++i<7) (+p++ in cond/comma) x all store orders (diff 8: moves sb a0,0 / cvt.w.s in B1), for/while/goto/break loop forms, q=p+(i-4)/&p[i-4]/p[i-4] indexing, register kw, 30k random topological reorders+dead stmts of the vertex section, 20 min permuter (-j2), 160k random mutants on a mini TU. Nothing flips sh/slti.
typedef struct {
    s8 unk0;
    u8 unk1;
    u16 unk2;
    s16 unk4;
    s16 unk6;
} BonusD2Ent;

typedef struct {
    char pad0[0x1C];
    BonusD2Ent *unk1C;
} BonusD2Model;

typedef struct {
    char pad0[0x20];
    f32 unk20;
} BonusD2Info;

typedef struct {
    char pad0[4];
    u8 unk4;
    u8 unk5;
} BonusD2Sub;

typedef struct BonusD2Actor BonusD2Actor;
struct BonusD2Actor {
    char pad0[4];
    BonusD2Model *unk4;
    char pad8[0x58];
    s32 unk60;
    char pad64[0x82];
    s16 unkE6;
    char padE8[0x5C];
    u8 unk144;
    char pad145[0xF];
    u8 unk154;
    u8 unk155;
    char pad156[0x1E];
    void *unk174;
    BonusD2Info *unk178;
};

typedef struct {
    BonusD2Actor *unk0;
    BonusD2Actor *unk4;
    f32 unk8;
    f32 unkC;
    s8 unk10;
    u8 unk11;
    char pad12[2];
    f32 unk14;
    f32 unk18;
    u8 unk1C;
} BonusD2Link;
#define BD2 ((BonusD2Actor *)D_807FBB40)

extern u8 D_807FBD70;
void *heapAlloc(s32);
void heapClearBlock(void *);

void func_8002881C(void) {
    BonusD2Link *link = BD2->unk174;
    s16 *sp50 = link->unk0->unk174;
    BonusD2Info *sp4C = link->unk0->unk178;
    BonusD2Sub *sub;
    BonusD2Ent *chk;
    s32 vb[2];
    f32 sp38;
    BonusD2Ent *p;
    f32 fx;
    f32 fy;
    f32 sp28;
    s32 i;

    if (!(BD2->unk60 & 0x10)) {
        BD2->unk144 = 0x24;
        link->unkC = 275.0f;
        link->unk8 = 275.0f;
        link->unk10 = link->unk11;
        BD2->unk4->unk1C = heapAlloc(0x38);
        heapClearBlock(BD2->unk4->unk1C);
    }
    sub = link->unk4->unk174;
    if (D_807FBD70 == 4 && sub->unk4 == 0 && link->unk10 == -1) {
        link->unk8 = 275.0f;
        link->unk10 = link->unk11;
        sub->unk5 = 0;
    }
    if (*sp50 > 0 && link->unk0->unk154 == 0) {
        if (sub->unk4 == 0) {
            if (link->unk10 >= 0) {
                link->unk10--;
            }
            if (link->unk10 < 0) {
                link->unk8 -= sp4C->unk20;
            }
        } else {
            link->unk8 += 40.0f;
            link->unk0->unk154 = 2;
        }
    }
    link->unkC = link->unkC + (link->unk8 - link->unkC) * 0.3;
    if (sub->unk4 != 0) {
        if (link->unk14 < 1.0f) {
            link->unk14 += 0.1f;
        } else if (link->unk14 > 1.0f) {
            link->unk14 = 1.0f;
        }
    } else if (link->unk1C != 0) {
        link->unk1C--;
        if (link->unk1C == 0) {
            actorScriptStart(D_807FBB40, 0x1F6);
        }
    }
    chk = BD2->unk4->unk1C;
    if (chk != 0) {
        vb[1] = 0;
        vb[0] = (s32)chk;
        sp38 = 1.0f - ((link->unkC - 40.0f) / 235.0f);
        fx = func_80612794(link->unk4->unkE6) * (5000.0f * sp38 + 150.0f);
        fy = func_80612790(link->unk4->unkE6) * (5000.0f * sp38 + 150.0f);
        sp28 = link->unk14 * 128.0f + -128.0f;
        i = 4;
        if (fx < 0.0f) {
            fx = 65535.0f + fx;
        }
        if (fy < 0.0f) {
            fy = 65535.0f + fy;
        }
        p = (BonusD2Ent *)(vb[1] * 8 + vb[0]);
        do {
            p->unk1 = i;
            i++;
            p->unk0 = (s32)sp28;
            p->unk2 = (u32)fx;
            p->unk4 = 0;
            p->unk6 = (u32)fy;
            if (fx > 32767.0f) {
                fx = fx + (65535.0f - fx) * 0.5;
            } else {
                fx = fx * 0.5;
            }
            if (fy > 32767.0f) {
                fy = fy + (65535.0f - fy) * 0.5;
            } else {
                fy = fy * 0.5;
            }
            p++;
        } while (i < 7);
        switch (BD2->unk155) {
        case 0:
            link->unk18 = link->unk18 + (sp38 - link->unk18) * 0.1;
            break;
        case 1:
        case 2:
            link->unk18 = link->unk18 + (0.0 - link->unk18) * 0.1;
            break;
        }
        p->unk0 = (s32)(link->unk18 * -128.0f);
        p->unk1 = 0xE;
        p->unk2 = 0x61A8;
        p->unk4 = 0;
        p->unk6 = 0;
        p++;
        i = 0xC;
        do {
            p->unk0 = (s32)(link->unk18 * -128.0f);
            p->unk1 = i;
            i++;
            p += 2;
            p[-2].unk2 = 0xD8F0;
            p[-2].unk4 = 0;
            p[-2].unk6 = 0;
        } while (i < 0xD);
        p->unk0 = 0;
    }
    actorUpdateModelMatrix(D_807FBB40, 0);
}
