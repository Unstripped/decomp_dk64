// func_80678050 (src/global/7CA80.c): W4C stage 5, ~36 text diff lines (deadsweep scorer 48->42): dropped the 'u16 aligned' local and spelled (u16)((headerSize + 7) & 0xFFF8) inline twice (CSE'd value spilled at 36(sp), t0 at 40(sp): spill slots + frame now match = fewer named-local homes). Left: const-1 web A (sh unk6C/unk6A) is pre-coloured v1 (adjsave 1.0) before the arg0 reload piece (adjsave 0.5) so arg0 gets a1 not v1 and ring temps shift (li t5/v1 vs t6/t7, li 1024/15 hoisted early). Tried: const types/spellings 1921 combos incl return, chain assign (adds lh readback), dead-if sweep 1700, store moves.
extern u16 *D_8074E218[];
extern u16 D_8074DA58[];
extern u32 D_807FBB64;
extern u16 D_80748D4A;
extern u16 D_807FBB3E;
void heapClearBlock(void *);
void actorTableInsert(Actor *);
void actorInitHealth(Actor *);

typedef struct ActorAllocBlock {
    u8 pad0[0x54];
    /* 0x54 */ s32 unk54;
    /* 0x58 */ s32 unk58;
    /* 0x5C */ s16 unk5C;
    u8 pad5E[2];
    /* 0x60 */ u32 unk60;
    /* 0x64 */ u32 unk64;
    /* 0x68 */ s16 unk68;
    /* 0x6A */ s16 unk6A;
    /* 0x6C */ s16 unk6C;
    /* 0x6E */ s16 unk6E;
    /* 0x70 */ s16 unk70;
    u8 pad72[6];
    /* 0x78 */ u8 unk78;
    u8 pad79[0x37];
    /* 0xB0 */ s8 unkB0;
    u8 padB1[0x1B];
    /* 0xCC */ u8 unkCC;
    /* 0xCD */ u8 unkCD;
    /* 0xCE */ s16 unkCE;
    u8 padD0[4];
    /* 0xD4 */ void *unkD4;
    u8 padD8[2];
    /* 0xDA */ s16 unkDA;
    u8 padDC[0x1C];
    /* 0xF8 */ s16 unkF8;
    u8 padFA[0x16];
    /* 0x110 */ u8 unk110;
    u8 pad111[3];
    /* 0x114 */ void *unk114;
    /* 0x118 */ void *unk118;
    /* 0x11C */ s32 unk11C;
    /* 0x120 */ u8 pad120[4];
    /* 0x124 */ s32 unk124;
    /* 0x128 */ s16 unk128;
    /* 0x12A */ s16 unk12A;
    /* 0x12C */ s16 unk12C;
    u8 pad12E[2];
    /* 0x130 */ u8 unk130;
    /* 0x131 */ u8 unk131;
    /* 0x132 */ u16 unk132;
    u8 pad134[4];
    /* 0x138 */ s32 unk138;
    /* 0x13C */ void *unk13C;
    u8 pad140[4];
    /* 0x144 */ u8 unk144;
    u8 pad145[1];
    /* 0x146 */ s16 unk146;
    /* 0x148 */ void *unk148;
    /* 0x14C */ void *unk14C;
    /* 0x150 */ s32 unk150;
    u8 pad154[2];
    /* 0x156 */ u8 unk156;
    u8 pad157[0x16];
    /* 0x16D */ u8 unk16D;
    u8 pad16E[6];
    /* 0x174 */ void *unk174;
} ActorAllocBlock;

s32 func_80678050(arg0)
u16 arg0;
{
    ActorAllocBlock *actor;
    u16 *types;
    void **ptrArray;
    u8 *dataPtr;
    u16 headerSize;
    u16 totalDataSize;

    types = D_8074E218[arg0];
    headerSize = 0x174;
    totalDataSize = 0;
    if (*types != 0) {
        do {
            if (headerSize) {}  // FAKE: raises headerSize priority so it gets a1 (tds a2)
            totalDataSize += D_8074DA58[*types];
            headerSize += 4;
            types++;
        } while (*types != 0);
    }
    totalDataSize += (u16)((headerSize + 7) & 0xFFF8);
    actor = (ActorAllocBlock *)heapAlloc(totalDataSize);
    if (actor != NULL) {
        heapClearBlock(actor);
        types = D_8074E218[arg0];
        ptrArray = (void **)&actor->unk174;
        dataPtr = (u8 *)actor + ((u16)((headerSize + 7) & 0xFFF8));
        if (*types != 0) {
            do {
                *ptrArray++ = dataPtr;
                dataPtr += D_8074DA58[*types++];
            } while (*types != 0);
        }
        actor->unk13C = NULL;
        actor->unk138 = -1;
        actor->unk144 = 2;
        actor->unk110 = 0;
        actor->unkF8 = 0x50;
        actor->unk60 = 0x58144;
        actor->unk64 = 0;
        actor->unk128 = 0xFF;
        actor->unk58 = arg0;
        if (D_807FBB64 & 0x100) {
            actor->unk12A = 0x7D0;
        } else {
            actor->unk12A = 0x1F4;
        }
        actor->unk68 = 0;
        actor->unk156 = 0;
        actor->unk78 = 0;
        actor->unk6C = 1;
        actor->unk6A = 1;
        actor->unk132 = 1;
        actor->unk114 = NULL;
        actor->unk118 = NULL;
        actor->unk11C = 0;
        actor->unk6E = -1;
        actor->unk70 = -1;
        actor->unk150 = 0;
        actor->unk12C = -1;
        actor->unk124 = 0;
        actor->unk148 = NULL;
        actor->unk14C = NULL;
        actor->unkD4 = &D_80748D4A;
        actor->unk146 = -1;
        actor->unkDA = 0x400;
        actor->unkCC = 0;
        actor->unkCD = 0;
        actor->unk130 = 0;
        actor->unk131 = 0;
        actor->unk16D = 0xF;
        actor->unkCE = 0;
        actor->unkB0 = -1;
        actor->unk5C = D_8074D624[arg0];
        actor->unk54 = D_807FBB38;
        D_807FBB38++;
        actorTableInsert((Actor *)actor);
        actorInitHealth((Actor *)actor);
        gActiveActors[gActiveActorCount].actor = (Actor *)actor;
        gActiveActors[gActiveActorCount].unk4 = 0;
        D_807FBB3E = gActiveActorCount;
        gActiveActorCount++;
        D_807FBB44 = (Actor *)actor;
        return 1;
    }
    return 0;
}
