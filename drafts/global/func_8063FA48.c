// func_8063FA48 (src/global/42630.c): stage 5-6, 1836/1847 insns, frame 0xC8 + s0/s1 + block order match; parked NON_MATCHING in src/global/42630.c. Left: sfx cases 0xE/0x7D/0xF/0x7E (original copies cmd->c into a 2nd reg then masks in place; pan/vol u8, pitch u8 at sp+0x55, pan spill to temp 0x3C), 0x8D (map must take s1 before exit: exit uncolored with pieces in a2 at sp+0x70), loops 0x76/0x2D (cursor v0, count v1, i t0: a declared 'ActorEntry *e' pointer loop gives those regs but costs 8 frame bytes; csId not hoisted in 0x2D), ugen scratch cascade. Fixed so far: found test 'if (found == 0) return;', D_807F61F4 as its own symbol in 0x68, s32 h = (s16)(...) with K&R modelAnimEntrySetUnkC in 0x4C, 0x66 store order unk0 then unk8.
// Cutscene script command: 16-bit opcode followed by three s16 parameters.
typedef struct CsCmd {
    /* 0x0 */ u16 op;
    /* 0x2 */ s16 a;
    /* 0x4 */ s16 b;
    /* 0x6 */ s16 c;
} CsCmd;

// Byte view of the same command (low bytes of a, b, c).
typedef struct CsCmdBytes {
    /* 0x0 */ u16 op;
    /* 0x2 */ u8 aHi;
    /* 0x3 */ u8 a;
    /* 0x4 */ u8 bHi;
    /* 0x5 */ u8 b;
    /* 0x6 */ u8 cHi;
    /* 0x7 */ u8 c;
} CsCmdBytes;

#define CMDB(cmd) ((CsCmdBytes *)(cmd))

// Per-cutscene playback state.
typedef struct CsState {
    /* 0x00 */ u8 pad0[8];
    /* 0x08 */ f32 unk8;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ s16 unk10[2];
    /* 0x14 */ f32 unk14[9];
    /* 0x38 */ s32 unk38;
    /* 0x3C */ u8 pad3C[8];
    /* 0x44 */ s16 unk44[3];
    /* 0x4A */ u8 pad4A;
    /* 0x4B */ u8 unk4B[4];
    /* 0x4F */ s8 unk4F;
    /* 0x50 */ s8 unk50;
    /* 0x51 */ u8 pad51[0xF];
    /* 0x60 */ s8 unk60;
    /* 0x61 */ u8 pad61;
    /* 0x62 */ s16 unk62;
    /* 0x64 */ u8 pad64[2];
    /* 0x66 */ s8 unk66;
    /* 0x67 */ s8 unk67;
    /* 0x68 */ s16 unk68;
    /* 0x6A */ s16 unk6A;
    /* 0x6C */ s16 unk6C;
    /* 0x6E */ s8 unk6E;
    /* 0x6F */ s8 unk6F;
    /* 0x70 */ s8 unk70;
    /* 0x71 */ s8 unk71;
    /* 0x72 */ u8 pad72[6];
    /* 0x78 */ f32 unk78;
    /* 0x7C */ f32 unk7C;
    /* 0x80 */ s16 unk80;
    /* 0x82 */ s16 unk82;
    /* 0x84 */ s16 unk84;
    /* 0x86 */ s16 unk86;
    /* 0x88 */ s16 unk88;
    /* 0x8A */ s16 unk8A;
    /* 0x8C */ u8 pad8C[8];
    /* 0x94 */ Actor *unk94;
    /* 0x98 */ u8 pad98[3];
    /* 0x9B */ u8 unk9B;
} CsState;

typedef struct CsPlayer {
    /* 0x0 */ u8 pad0[4];
    /* 0x4 */ Actor *unk4;
} CsPlayer;

// Object hanging off the player actor's unk174.
typedef struct CsCamState {
    /* 0x000 */ u8 pad0[0x104];
    /* 0x104 */ s32 unk104;
    /* 0x108 */ u8 pad108[0x1F0 - 0x108];
    /* 0x1F0 */ s32 unk1F0;
    /* 0x1F4 */ s32 unk1F4;
    /* 0x1F8 */ u8 pad1F8[0x22C - 0x1F8];
    /* 0x22C */ f32 unk22C;
    /* 0x230 */ f32 unk230;
    /* 0x234 */ f32 unk234;
} CsCamState;

typedef struct CsModelSlot {
    /* 0x00 */ u8 pad0[0x28];
    /* 0x28 */ u8 unk28[0x20];
    /* 0x48 */ u8 unk48[0x34];
    /* 0x7C */ u8 *unk7C;
    /* 0x80 */ u8 pad80[0xA];
    /* 0x8A */ s16 unk8A;
    /* 0x8C */ u8 pad8C[4];
} CsModelSlot; /* 0x90 */

typedef struct CsModelSlot2 {
    /* 0x00 */ u8 pad0[0x3C];
    /* 0x3C */ s8 unk3C;
    /* 0x3D */ u8 pad3D[0x90 - 0x3D];
} CsModelSlot2;

typedef struct CsSpawnReq {
    /* 0x0 */ Actor *unk0;
    /* 0x4 */ Actor *unk4;
    /* 0x8 */ u8 unk8;
} CsSpawnReq;

typedef void (*CsCmdFunc)(CsState *, s16, s16, s16);

extern CsCmdFunc D_80747E70[];
extern u8 D_80744824;
extern s8 D_80748094;
extern s16 D_8074809C[];
extern s16 D_807480AC[];
extern s16 D_807480BC[];
extern s32 D_8076A0A8;
extern CsModelSlot *D_807F6000;
extern CsSpawnReq D_807F61F0;
extern Actor *D_807F61F4;
extern f32 D_807F61FC;
extern f32 D_807F6204;
extern f32 D_807F6218;
extern f32 D_807F621C;
extern f32 D_807F6220;
extern f32 D_807F6224;
extern s16 D_807F6240[];
extern s8 D_807F6902;
extern s8 D_807F6903;
extern s16 D_807F6904;
extern s16 D_807F6906;
extern s16 D_807F6908;
extern f32 D_807F690C;
extern f32 D_807F6910;
extern f32 D_807F6914;
extern s16 D_807F6918[16];
extern u8 D_807F6938;
extern s16 D_807F693A;
extern s16 D_807F693C;
extern u8 D_807F693E;
extern s8 D_807F693F;
extern Actor *D_807FBB44;
extern Actor *D_807FBB48;
extern u32 D_807FBB60;
extern u32 D_807FBB68;
extern CsPlayer *D_807FC924;
extern ActorEntry gActiveActors[];
extern u16 gActiveActorCount;

void actorAppendCallback(Actor *, s32, s32, u8, s32, void *);
void actorDespawn(Actor *);
s32 actorListGetOrSetState(s16, u8, u8);
void actorSetStateTwo(Actor *);
void actorSetTargetSlotByte(s32, u8);
s32 actorSpawn(s32, s32);
void dynamicBufferFree(void *);
void effectNodeAddTargetAndStep(s32, f32, f32);
void effectNodeSetSubVal(s32, u8);
void effectNodeSetTargetAndStep(s32, f32, f32);
s32 func_805FEF74(s32);
u8 func_805FF030(u8, u8);
void func_805FF158(u8);
void func_805FF378(s32, s32);
void func_805FF628(s16, s16);
void func_805FF898(void);
void func_805FF9AC(s16, s16, s16, s16);
s32 func_805FFE50(s16, s16, s16);
void func_80600044(s32);
void func_80605380(s16);
void func_806086CC(f32, f32, f32, s16, s32, s32, s32, s32, f32, s32);
s16 func_80609140(s16, s32, s32, f32, s32, s32);
void func_8060B49C(Actor *, s16);
void func_8060DEC8(void);
void func_8061EF4C(s32, u8, u16, f32, f32, f32, f32, f32);
void func_8061F510(u8, u8);
void func_8062B630(s16, u8);
void func_8062B86C(s16, f32, f32);
void func_8062B8A4(s16, f32, f32);
void func_8062D1A8(void);
void func_80631B8C(s16);
s16 func_80632630(s16, f32, f32, f32, f32, s32);
void func_806335B0(s16, s32, s32, f32 *, f32 *, f32 *);
void func_8063393C(s16, s32, u8, u8);
void func_806348B4(void *);
void func_80634CC8(s16, s16, s16, s16);
void func_80634EA4(s16, s16, u8);
void func_80635018(s16, s16, s16, s16);
void func_80636014(s16, s32, u8);
void func_8063A8C4(s16, s32, f32);
void func_8063DB3C(s16, s16, s16);
void func_806417BC(s16, s16);
void func_80641874(s16, s16);
s32 func_806418E8(s16, s16, s16);
void func_8064199C(void *, s16, s16);
void func_80641B00(s16, s16, s16);
void func_80641BCC(s16, s16, s16);
void func_80641C98(s16, s16, s16);
void func_80641DA0(void *, s16, s16, s16);
void func_80642480(s16, s16);
void func_80642748(s16, s16, void *, s16, s32);
void func_80642844(s16, s16, void *, s16, s32);
void func_80650794(s16, s16, u8, f32);
s16 func_80650A70(s16, s16);
void func_8067A9F0(s32, Actor *, f32, f32, f32);
void func_8067ABC0(s32, Actor *, u8, s16, s32, f32, f32, f32);
s32 func_8068ABE0(s16);
void func_8068B830(s16, s16, s16);
void func_8068B8FC(void);
void func_806A2A10(s32, s32, u8, void *);
void func_806C92C4(s16);
void func_806CF398(Actor *);
void playerStateQueueCallback(s16, s32, s32);
void playerStateSetCallbackParameters(s32, s16, s16, s16);
void func_806F4F50(s16, f32, f32, f32);
void func_806FB370(u8, u8, u8);
void func_8070B308(s32);
s32 func_807146A4(s16);
void func_807149B8(s32);
void func_80714B84(s32, f32, s16, s16, s32);
s32 func_80723020(s32, s16, u8, f32, f32, f32, s32);
void func_80723284(s32, u8);
void func_807232EC(s32, u8);
void func_80723320(s32, s16);
void func_8072334C(s32, u8);
void func_80723380(s32, u8);
void func_80723428(s32);
void func_80723484(s32);
void func_807238D4(s32, f32 *, f32 *, f32 *);
void func_80724994(s32, s16, s16, s32, s32);
void func_80724A9C(u8, u8, u8);
void func_8072EC94(s16, u8);
void func_8072ECFC(s16, s16, s16, s16);
void func_8072ED9C(s16, u8, u8);
void func_8072EE0C(s16, u8, u8);
s32 func_8073110C(s16, s32, s32);
void func_8073129C(s16, u8, s32);
s32 hashTableLookup();
void lightGetColor(f32 *, f32 *, f32 *, s16);
void lightSetColor(f32, f32, f32, s16);
void mapByteArraySet(s16, u8);
void mapObjectSetByte(s16, u8, u8);
void modelAnimEntryClearTime(s16, s16);
void modelAnimEntryResetFrame(s16, s16, s16);
void modelAnimEntrySetTime(s16, s16, s16, f32);
void modelAnimEntrySetUnk10(s16, s16, s16);
void modelAnimEntrySetUnk12(s16, s16, s16);
void modelAnimEntrySetUnkC();
void modelAnimEntrySetUnkF(s16, s16, s16);
void modelAnimEntryStart(s16, s16, s16);
void modelAnimEntryStop(s16, s16);
void seqRouteChannelVolume(s32, f32);
void sfxAllocateChannel(s32, f32);
void sfxPlayFromTargetSlot(s16, s16, u8, u8, s32, s32, f32);
void sfxSetChannelTempo(s32, f32);
void sfxSetVolumeAndPan(u8, f32, f32);
u8 sfxSlotAllocateSource(s16, s16, s32, s32, u8, f32, s8);
void sfxStopChannel(s32, s32);

void func_8063FA48(CsCmd *cmd, CsState *cs, s16 csId) {
    s32 padC4;
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
    s32 pad68;
    s32 pad64;
    f32 sx;
    f32 sy;
    f32 sz;
    u8 pan;
    u8 vol;
    u8 pitch;
    f32 cx;
    f32 cy;
    f32 cz;

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
        func_8061F510(CMDB(cmd)->a, CMDB(cmd)->b);
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
        func_806348B4(&D_807F6000[hashTableLookup(csId)].unk48);
        break;
    case 0x85:
        func_8062D1A8();
        break;
    case 0x83:
        func_806FB370(CMDB(cmd)->a, CMDB(cmd)->b, CMDB(cmd)->c);
        break;
    case 0x80:
        func_8060DEC8();
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
        func_806335B0(csId, 1, cmd->b, &x, &y, &z);
        func_8072ECFC(cmd->a, x, y, z);
        break;
    case 0x7A:
        effectNodeSetSubVal(cmd->a, CMDB(cmd)->b);
        break;
    case 0x76:
        for (i = 0; i < gActiveActorCount; i++) {
            actor = gActiveActors[i].actor;
            if (!(actor->unk60 & 0x2000) && actor->unk110 == 1 && csId == actor->unk10C) {
                actorAppendCallback(actor, 0, 8, 0, 0, 0);
            }
        }
        break;
    case 0x75:
        func_8072EC94(cmd->a, CMDB(cmd)->b);
        break;
    case 0x78:
        func_806335B0(csId, 1, cmd->a, &px, &py, &pz);
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
        func_80631B8C(cmd->a);
        break;
    case 0x6B:
        func_8073129C(cmd->a, CMDB(cmd)->b, 0);
        break;
    case 0x79:
        func_8073129C(cmd->a, CMDB(cmd)->b, 2);
        break;
    case 0x84:
        func_8073129C(cmd->a, CMDB(cmd)->b, 1);
        break;
    case 0x66:
        if (D_807F61F0.unk8 == 0) {
            actorSpawn(0xB1, 0);
            actor = D_807FBB40;
            D_807F61F0.unk4 = D_807FBB44;
            D_807FBB40 = D_807FBB44;
            func_806A2A10(0xDC, 0x2A, CMDB(cmd)->a, &D_807F61F0);
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
        func_80724A9C(CMDB(cmd)->a, CMDB(cmd)->b, CMDB(cmd)->c);
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
            func_806335B0(D_807F6240[cmd->a], 1, cmd->b, &D_807F690C, &D_807F6910, &D_807F6914);
        }
        break;
    case 0x4E:
        slot = func_807146A4(cmd->a);
        func_807149B8(1);
        func_80714B84(slot, cmd->b / 100.0, csId, cmd->c, 0);
        break;
    case 0x4C:
        h = (s16)(func_80650A70(csId, cmd->a) + cmd->b);
        if (h < 0) {
            h = 0;
        }
        modelAnimEntrySetUnkC(csId, cmd->a, h);
        break;
    case 0x4B:
        func_8072ED9C(csId, CMDB(cmd)->a, CMDB(cmd)->b);
        break;
    case 0x46:
        cs->unk70 = cmd->a;
        break;
    case 0x47:
        cs->unk71 = cmd->a;
        break;
    case 0x4A:
        func_8063393C(csId, 1, CMDB(cmd)->a, CMDB(cmd)->b);
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
        func_8062B86C(cmd->a, cmd->b, cmd->c / 100.0f);
        break;
    case 0x55:
        func_8062B630(cmd->a, CMDB(cmd)->b);
        break;
    case 0x34:
        func_8062B8A4(cmd->a, cmd->b, cmd->c / 100.0f);
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
            exit = D_807480AC[slot];
            map = D_8074809C[slot];
            if (func_8073110C(D_807480BC[slot], 0, exit) == 0) {
                exit = 0;
                if (map == 0x57) {
                    exit = 0x15;
                }
            }
            if (func_8068ABE0(map) == 0) {
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
        pan = cmd->b / 128;
        vol = cmd->c / 128;
        c = cmd->c;
        c &= 0x7F;
        if (pan == 0) {
            pan = 0x7F;
        }
        if (vol == 0) {
            vol = 0xFF;
        }
        b = cmd->b;
        b &= 2;
        if (cs->unk10[cmd->b & 1] < 0) {
            cs->unk10[cmd->b & 1] = sfxSlotAllocateSource(csId, cmd->a, c, b, vol, (u32)pan / 127.0, 0);
        }
        break;
    case 0x7D:
        pan = cmd->b / 128;
        vol = cmd->c / 128;
        c = cmd->c;
        c &= 0x7F;
        if (pan == 0) {
            pan = 0x7F;
        }
        if (vol == 0) {
            vol = 0xFF;
        }
        b = cmd->b;
        b &= 2;
        if (cs->unk10[cmd->b & 1] < 0) {
            cs->unk10[cmd->b & 1] = sfxSlotAllocateSource(csId, cmd->a, c, b, vol, (u32)pan / 127.0, D_80748094);
        }
        break;
    case 0xF:
        pan = cmd->b / 128;
        vol = cmd->c / 128;
        c = cmd->c;
        c &= 0x7F;
        if (pan == 0) {
            pan = 0x7F;
        }
        if (vol == 0) {
            vol = 0xFF;
        }
        sfxPlayFromTargetSlot(csId, cmd->a, vol, pan, cmd->b & 0x7F, c, 0.3f);
        break;
    case 0x7E:
        pan = cmd->b / 128;
        vol = cmd->c / 128;
        c = cmd->c;
        c &= 0x7F;
        if (pan == 0) {
            pan = 0x7F;
        }
        if (vol == 0) {
            vol = 0xFF;
        }
        i = cmd->b & 0x7F;
        if (D_80748094 > 0) {
            pitch = c;
            func_806335B0(csId, 1, D_80748094, &sx, &sy, &sz);
            func_806086CC(sx, sy, sz, cmd->a, vol, pan, i, pitch, 0.3f, 0);
        } else {
            func_80609140(cmd->a, 0x7FFF, 0x427C0000, (u32)pan / 127.0, 0, 0);
        }
        break;
    case 0x10:
        if (cs->unk10[cmd->b] >= 0) {
            func_80605380(cs->unk10[cmd->b]);
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
        if (D_807F621C != D_807F61FC || D_807F6224 != D_807F6204) {
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
        func_806418E8(cmd->a, cmd->b, cmd->c);
        break;
    case 0x2D:
        for (i = 0; i < gActiveActorCount; i++) {
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
        func_806335B0(csId, 1, cmd->a, &cx, &cy, &cz);
        func_8067A9F0(0, D_807FC924->unk4, cx, cy, cz);
        break;
    case 0x2B:
        func_80636014(csId, 1, CMDB(cmd)->a);
        break;
    case 0x1B:
        if (D_807F6240[cmd->a] != -1) {
            func_806335B0(D_807F6240[cmd->a], 1, cmd->b, &D_807F621C, &D_807F6220, &D_807F6224);
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
        func_80634EA4(csId, cmd->a, CMDB(cmd)->b);
        break;
    case 0x28:
        func_80635018(csId, cmd->a, cmd->b, cmd->c);
        break;
    case 0x42:
        func_80634CC8(csId, cmd->a, cmd->b, cmd->c);
        break;
    case 0x29:
        func_8061EF4C(((CsCamState *)D_807FC924->unk4->unk174)->unk104, CMDB(cmd)->a, cmd->b, D_807F621C, D_807F6220, D_807F6224, D_807F6906, D_807F6908);
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
        idx = func_80632630(cmd->a, D_807F690C, D_807F6910, D_807F6914, D_807F6910 - D_807F6218, 0);
        if (cmd->b == 0) {
            func_80641B00(idx, csId, cmd->c);
        }
        break;
    case 0x51:
        func_806F4F50(csId, D_807F621C, D_807F6220, D_807F6224);
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
        func_80650794(csId, cmd->a, CMDB(cmd)->b, cmd->c / 1000.0);
        break;
    }
}
