// func_8063EA14 (src/global/42630.c): CsEA14 stage 5-6, parked NON_MATCHING in the private copy: frame 0x78, s0/s1, block layout, operand order, jump table all match; text size equal (21184 B). Remaining diff = ugen $t numbering only (~108 reg-only lines, 22 hunks: t6/t8 swaps in early arms, case 0x1 arg ring starts t3 not t8, actor loops use a2/v1 where target uses v0). Tricks: needs 's32 flagGet();' unprototyped (file decl is (s16,s32,s32)); 'cmd->b - X == 0' and 'k = field - cmd->a; if (k == 0)' change operand-eval order; (k = unk44[..]) == cmd->a in case 4; 'u32 mask = ...; D_807FBB60 & mask'; 'h = f()*0x5E; q = &D_807FC950[A*0x306 + h]'; u8 found; scalar-field view CsEAAct; pads after height fix frame.
typedef struct CsEAState {
    /* 0x00 */ u8 pad0[0x14];
    /* 0x14 */ f32 unk14[9];
    /* 0x38 */ s32 unk38;
    /* 0x3C */ u8 pad3C[8];
    /* 0x44 */ s16 unk44[2];
    /* 0x48 */ u8 unk48[9];
    /* 0x51 */ u8 unk51;
    /* 0x52 */ u8 unk52;
    /* 0x53 */ u8 pad53[9];
    /* 0x5C */ u8 unk5C;
    /* 0x5D */ u8 pad5D;
    /* 0x5E */ u16 unk5E;
    /* 0x60 */ u8 pad60[0x3A];
    /* 0x9A */ u8 unk9A;
} CsEAState;

typedef struct CsEAAct {
    /* 0x000 */ u8 pad0[0x58];
    /* 0x058 */ s32 unk58;
    /* 0x05C */ u8 pad5C[4];
    /* 0x060 */ u32 unk60;
    /* 0x064 */ u8 pad64[0x10C - 0x64];
    /* 0x10C */ s16 unk10C;
    /* 0x10E */ u8 unk10E;
    /* 0x10F */ u8 pad10F;
    /* 0x110 */ u8 unk110;
    /* 0x111 */ u8 pad111[0x12F - 0x111];
    /* 0x12F */ u8 unk12F;
    /* 0x130 */ u8 pad130[0x154 - 0x130];
    /* 0x154 */ u8 unk154;
    /* 0x155 */ u8 unk155;
} CsEAAct;

typedef struct CsEAPlayer {
    /* 0x000 */ u8 unk0;
    /* 0x001 */ u8 pad1[3];
    /* 0x004 */ CsEAAct *unk4;
    /* 0x008 */ u8 pad8[0x288];
    /* 0x290 */ s16 unk290;
    /* 0x292 */ u8 pad292[0x2C0 - 0x292];
    /* 0x2C0 */ u8 unk2C0;
    /* 0x2C1 */ u8 unk2C1;
    /* 0x2C2 */ u8 pad2C2[0x2F0 - 0x2C2];
} CsEAPlayer; /* 0x2F0 */

typedef struct CsEACam {
    /* 0x000 */ u8 pad0[0x1F0];
    /* 0x1F0 */ s32 unk1F0;
    /* 0x1F4 */ s32 unk1F4;
    /* 0x1F8 */ s32 unk1F8;
} CsEACam;

typedef struct CsEAObj {
    /* 0x00 */ u8 pad0[0x48];
    /* 0x48 */ u8 unk48[1];
} CsEAObj;

typedef struct CsEASlot {
    /* 0x00 */ u8 pad0[0x7C];
    /* 0x7C */ u8 *unk7C;
    /* 0x80 */ u8 pad80[4];
    /* 0x84 */ s16 unk84;
    /* 0x86 */ u8 pad86[0xA];
} CsEASlot; /* 0x90 */

typedef struct CsEAActorD {
    /* 0x00 */ u8 pad0[0xD0];
    /* 0xD0 */ u8 unkD0;
    /* 0xD1 */ u8 unkD1;
} CsEAActorD;

typedef struct CsEASpawn {
    /* 0x0 */ Actor *unk0;
    /* 0x4 */ Actor *unk4;
    /* 0x8 */ u8 unk8;
} CsEASpawn;

typedef struct CsEARow {
    /* 0x000 */ u8 e[8][0x5E];
    /* 0x2F0 */ u8 pad2F0[0x16];
} CsEARow; /* 0x306 */

extern ActorEntry gActiveActors[];
extern u16 gActiveActorCount;
extern CsPlayer *D_807FC924;
extern u8 *D_807FD568;
extern u8 D_807FC928;
extern u8 D_807FC929;
extern u8 D_807FC950[];
extern u8 D_807444EC;
extern u8 D_8074E77C;
extern s16 D_8076AEF2;
extern s32 (*D_80748048[])(CsState *, s16, s16, s16);

void modelAnimEntryGetState(s16, s16, s16 *, f32 *, u8 *);
s32 modelAnimEntryIsActive(s16, s16);
s32 actorListGetOrSetState(s16, u8, u8);
s32 flagGet();
s32 func_80689BAC(s16);
u16 func_8067ACC0(u16);
s32 func_806419F8(void);
void func_80641724(s16);
s16 func_80650A70(s16, s16);
Actor *spawnNodeActivate(s16, u16);
u8 spawnNodeHasActor(u8);
s32 spawnNodeIsInCooldown(u8);
s32 listContainsS16(s16);
f32 func_80614A54(void *);
s32 func_806C8D2C(s16);
s32 func_80723C98(s32);
u8 func_80641F70(s16);
s32 func_80642204(s16);
s32 func_806422D8(s16);
s32 func_806423A8(s16, s16, s16);
s32 func_80642500(f32 *, s16, s16);
s32 func_806425FC(s16, s16);

#define CsEAS ((CsEAState *)cs)
#define CsEAP ((CsEAPlayer *)D_807FC924)

s32 func_8063EA14(CsCmd *cmd, CsState *cs, s16 csId) {
    u8 neg;
    u8 ret;
    s16 type;
    CsEAAct *a;
    CsEAPlayer *p;
    u8 found;
    s32 count;
    s32 k;
    s32 h;
    s16 sAnim;
    f32 fAnim;
    u8 uAnim;
    u8 i;
    f32 height;
    u8 *q;
    CsEACam *cam;
    u32 mask;
    s32 pad4;

    if (*(s16 *)cmd & 0x8000) {
        neg = 1;
    } else {
        neg = 0;
    }
    type = *(s16 *)cmd & 0x7FFF;
    switch (type) {
    case 0x0:
        ret = 1;
        break;
    case 0x3D:
        ret = *(u8 *)&D_807F6903;
        break;
    case 0x3C:
        ret = cmd->a == CsEAP->unk290;
        break;
    case 0x3A:
        if ((1 << cmd->a) & D_807F693E) {
            ret = 1;
        } else {
            ret = 0;
        }
        break;
    case 0x39:
        if (cmd->a & D_807FBB4C->unk132) {
            ret = 1;
        } else {
            ret = 0;
        }
        break;
    case 0x38:
        ret = D_8074E77C < 5;
        break;
    case 0x37:
        modelAnimEntryGetState(csId, cmd->a, &sAnim, &fAnim, &uAnim);
        if (sAnim == cmd->b) {
            ret = 1;
        } else {
            ret = 0;
        }
        break;
    case 0x32:
        ret = cmd->a == D_8076AEF2;
        break;
    case 0x30:
        if (((CsEAActorD *)D_807FBB4C)->unkD1 == cmd->a) {
            ret = 1;
        } else {
            ret = 0;
        }
        break;
    case 0x35:
        if (cmd->a == ((CsEAActorD *)D_807FBB4C)->unkD0) {
            ret = 1;
        } else {
            ret = 0;
        }
        break;
    case 0x2E:
        if (actorListGetOrSetState(cmd->a, 0, 0) == cmd->b) {
            ret = 1;
        } else {
            ret = 0;
        }
        break;
    case 0x2D:
        ret = flagGet(cmd->a, 0);
        break;
    case 0x36:
        ret = flagGet(cmd->a, 2);
        break;
    case 0x3B:
        ret = flagGet(cmd->a, 1);
        break;
    case 0x2C:
        if (func_80689BAC(cmd->a) != 0) {
            ret = 1;
        } else {
            ret = 0;
        }
        break;
    case 0x28:
        if (CsEAS->unk9A & 1) {
            ret = 0;
        } else {
            ret = 1;
        }
        break;
    case 0x26:
        cam = D_807FC924->unk4->unk174;
        if ((cmd->b + (cmd->a << 16)) & cam->unk1F0) {
            ret = 1;
        } else {
            ret = 0;
        }
        break;
    case 0x27:
        cam = D_807FC924->unk4->unk174;
        if ((cmd->b + (cmd->a << 16)) & cam->unk1F8) {
            ret = 1;
        } else {
            ret = 0;
        }
        break;
    case 0x25:
        if (D_807FD568[1] >= cmd->a) {
            ret = 1;
        } else {
            ret = 0;
        }
        break;
    case 0x34:
        h = func_806C8D2C(cmd->a) * 0x5E;
        q = &D_807FC950[D_807FC929 * 0x306 + h];
        if (*q >= cmd->b) {
            ret = 1;
        } else {
            ret = 0;
        }
        break;
    case 0x24:
        a = (CsEAAct *)spawnNodeActivate(cmd->a, 0);
        if (cmd->b == a->unk154) {
            ret = 1;
        } else {
            ret = 0;
        }
        break;
    case 0x23:
        if (D_807444EC == 1) {
            ret = 1;
        } else {
            ret = 0;
        }
        break;
    case 0x1D:
        if ((cmd->a == 0 && CsEAS->unk48[cmd->c] < cmd->b) || (cmd->a == 1 && cmd->b < CsEAS->unk48[cmd->c])) {
            ret = 1;
        } else {
            ret = 0;
        }
        break;
    case 0x1C:
        h = func_80650A70(csId, cmd->a);
        if ((cmd->b == 0 && h < cmd->c) || (cmd->b == 1 && cmd->c < h)) {
            ret = 1;
        } else {
            ret = 0;
        }
        break;
    case 0x16:
        mask = cmd->b + (cmd->a << 16);
        if (D_807FBB60 & mask) {
            ret = 1;
        } else {
            ret = 0;
        }
        break;
    case 0x15:
        ret = modelAnimEntryIsActive(csId, cmd->a);
        break;
    case 0xC:
        if (D_807F61FC != D_807F621C || D_807F6200 != D_807F6220 || D_807F6204 != D_807F6224 ||
            D_807F6208 != D_807F6228 || D_807F620C != D_807F622C || D_807F6210 != D_807F6230 ||
            D_807F6214 != D_807F6234) {
            ret = 1;
        } else {
            ret = 0;
        }
        break;
    case 0x8:
        ret = CsEAS->unk51;
        break;
    case 0x9:
        if (CsEAS->unk52 != 0) {
            ret = 1;
        } else {
            ret = 0;
        }
        break;
    case 0x7:
        ret = func_80642500(CsEAS->unk14, cmd->a, cmd->b);
        break;
    case 0x31:
        if (cmd->b - ((CsEASlot *)D_807F6000)[hashTableLookup(D_807F6240[cmd->a])].unk7C[cmd->c + 0x48] == 0) {
            ret = 1;
        } else {
            ret = 0;
        }
        break;
    case 0x1:
        k = CsEAS->unk48[cmd->b] - cmd->a;
        if (k == 0) {
            ret = 1;
        } else {
            ret = 0;
        }
        break;
    case 0x5:
        ret = func_806425FC(cmd->a, cmd->b);
        break;
    case 0x4:
        if ((k = CsEAS->unk44[cmd->b]) == cmd->a) {
            ret = 1;
        } else {
            ret = 0;
        }
        break;
    case 0x2:
        ret = 0;
        for (i = 0; i < D_807FC928; i++) {
            p = &CsEAP[i];
            if (p->unk0 != 0) {
                a = p->unk4;
                if (a->unk110 == 1 && csId == a->unk10C) {
                    ret = 1;
                }
            }
        }
        break;
    case 0xD:
        ret = 0;
        for (i = 0; i < D_807FC928; i++) {
            p = &CsEAP[i];
            if (p->unk0 != 0) {
                a = p->unk4;
                if (a->unk110 == 1 && csId == a->unk10C && cmd->a == a->unk10E) {
                    ret = 1;
                }
            }
        }
        break;
    case 0x11:
        found = 0;
        for (k = 0; k < gActiveActorCount && !found; k++) {
            a = (CsEAAct *)gActiveActors[k].actor;
            if (!(a->unk60 & 0x2000) && cmd->a == a->unk58 && a->unk110 == 1 && csId == a->unk10C) {
                found = 1;
            }
        }
        if (found) {
            ret = 1;
        } else {
            ret = 0;
        }
        break;
    case 0x12:
        found = 0;
        for (k = 0; k < gActiveActorCount && !found; k++) {
            a = (CsEAAct *)gActiveActors[k].actor;
            if (!(a->unk60 & 0x2000) && cmd->a == a->unk58 && a->unk110 == 1 && csId == a->unk10C &&
                cmd->b == a->unk10E) {
                found = 1;
            }
        }
        if (found) {
            ret = 1;
        } else {
            ret = 0;
        }
        break;
    case 0x14:
        count = 0;
        for (k = 0; k < gActiveActorCount; k++) {
            a = (CsEAAct *)gActiveActors[k].actor;
            if (!(a->unk60 & 0x2000) && cmd->a == a->unk58 && csId == a->unk10C && cmd->b == a->unk10E) {
                count++;
            }
        }
        if (count == cmd->c) {
            ret = 1;
        } else {
            ret = 0;
        }
        break;
    case 0xB:
        ret = 0;
        for (i = 0; i < D_807FC928; i++) {
            p = &CsEAP[i];
            if (p->unk0 != 0) {
                a = p->unk4;
                if (a->unk110 == 3 && cmd->a == a->unk12F && csId == a->unk10C) {
                    ret = 1;
                }
            }
        }
        break;
    case 0xA:
        ret = 0;
        for (i = 0; i < D_807FC928; i++) {
            p = &CsEAP[i];
            if (p->unk0 != 0) {
                a = p->unk4;
                if (a->unk110 == 2 && csId == a->unk10C) {
                    ret = 1;
                } else {
                    ret = 0;
                }
            }
        }
        break;
    case 0xE:
        ret = func_80641F70(cmd->a);
        break;
    case 0x13:
        ret = func_80642204(cmd->a);
        break;
    case 0x20:
        ret = func_806422D8(cmd->a);
        break;
    case 0x29:
        ret = func_806423A8(cmd->a, cmd->b, cmd->c);
        break;
    case 0x6:
        ret = D_80748048[cmd->a](cs, csId, cmd->b, cmd->c);
        break;
    case 0xF:
        ret = func_80723C98(CsEAS->unk38);
        break;
    case 0x10:
        if (CsEAS->unk5C != 0 && (cmd->b == -1 || CsEAS->unk5C == cmd->b) &&
            (func_8067ACC0(CsEAS->unk5E) & cmd->a) && func_806419F8() != 0) {
            func_80641724(((CsEASlot *)D_807F6000)[hashTableLookup(csId)].unk84);
            ret = 1;
        } else {
            ret = 0;
        }
        break;
    case 0x18:
        if (CsEAS->unk5C != 0 && (cmd->b == -1 || CsEAS->unk5C == cmd->b) && cmd->a == CsEAS->unk5E &&
            func_806419F8() != 0) {
            func_80641724(((CsEASlot *)D_807F6000)[hashTableLookup(csId)].unk84);
            ret = 1;
        } else {
            ret = 0;
        }
        break;
    case 0x17:
        ret = 0;
        for (i = 0; i < D_807FC928; i++) {
            p = &CsEAP[i];
            if (p->unk0 != 0) {
                a = p->unk4;
                if (cmd->a == a->unk154) {
                    if (cmd->b != 0) {
                        if (a->unk155 == cmd->b) {
                            ret = 1;
                        }
                    } else {
                        ret = 1;
                    }
                }
            }
        }
        break;
    case 0x21:
        ret = 0;
        for (i = 0; i < D_807FC928; i++) {
            p = &CsEAP[i];
            if (p->unk0 != 0 && p->unk4->unk155 == cmd->a) {
                ret = 1;
            }
        }
        break;
    case 0x19:
        if (cmd->a == D_807FBB4C->unk58) {
            ret = 1;
        } else {
            ret = 0;
        }
        break;
    case 0x1A:
        ret = CsEAP->unk2C0 == cmd->a;
        break;
    case 0x1B:
        ret = CsEAP->unk2C1;
        break;
    case 0x1E:
        ret = spawnNodeHasActor(CMDB(cmd)->a);
        break;
    case 0x2F:
        ret = spawnNodeIsInCooldown(CMDB(cmd)->a);
        break;
    case 0x1F:
        ret = 0;
        break;
    case 0x22:
        ret = listContainsS16(cmd->a);
        break;
    case 0x2A:
        if (((CsEASpawn *)&D_807F61F0)->unk8 != 0) {
            if (((CsEASpawn *)&D_807F61F0)->unk0->unk154 == 5) {
                ret = 1;
            } else {
                ret = 0;
            }
        } else {
            ret = 1;
        }
        break;
    case 0x2B:
        ret = ((CsEASpawn *)&D_807F61F0)->unk8;
        break;
    case 0x33:
        height = func_80614A54(D_807FBB4C);
        ret = 0;
        if (cmd->a == 0 && cmd->b < (s16)height) {
            ret = 1;
        }
        if (cmd->a == 1 && (s16)height < cmd->b) {
            ret = 1;
        }
        break;
    default:
        ret = 0;
        break;
    }
    if (neg) {
        ret = 1 - ret;
    }
    return ret;
}
