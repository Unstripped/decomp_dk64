// func_806A7600 (src/global/AA960.c): stage 6, 10 diff lines left (393 insns, size/frame/blocks identical): (1) cfg-read block: expected v0=&D_807FBB40 and v1=temp_v1 reload, mine reversed; (2) final sfxPlayAtPositionPooled 0.0f arg: expected mtc1 zero,$f0, mine $f8. Found: switch(unk58) for the sfx-id chain; separate 'flag = (temp == -1 || flagGet(temp,0) != 0) ? 1 : 0' (plain 'x = a||b' gives sltiu/sltu); dead 'if (temp_v1 && temp_v1) {}' after pathPlaybackStart (any temp_v1 use there; blocks s8 store->load forwarding + hoists reload). Tried: callee void->s32 toggles, 0 vs 0.0f, local decl order/types, cfg-read statement joins, 540s permuter, deadsweep rounds (no more).
extern Actor *D_807FBB40;
extern Actor *D_807FBB4C;
void actorAppendModelNode(Actor *, f32, f32, f32, f32, s32);
void actorAppendModelSubNode(Actor *, f32, f32, f32, s32);
void actorSetCollisionRadius(Actor *, f32);
void sfxPlayAtPositionPooled(f32, f32, f32, s32, s32, s32, s32, s32, f32, s32);
void func_807149C8(s32, s32, s32, u8);
void func_80714998(s32);
void func_807149B8(s32);
s32 func_80714C08(void *, f32, void *, s32, s32);

typedef struct EffectState {
    u8 unk0;
    u8 unk1;
    s8 unk2;
    u8 pad3[1];
    u16 unk4;
    s16 unk6;
    u16 unk8;
    s16 unkA;
} EffectState;

typedef struct AA960ConfigInt {
    s32 unk0;
    s32 unk4;
} AA960ConfigInt;

extern u8 D_807FBD70;
extern u32 D_8076A068;
s32 actorListFindIdByActor(Actor *);
s32 actorListLookupEntry(s32);
s32 flagGet(s32, s32);
void flagSet(s32, s32, s32);
s32 pathPlaybackStart(void *, s32, s32, f32, f32, f32, s32);
void func_807232B8(s32, s32);
void func_80723284(s32, s32);
void func_80723320(s32, s32);
void func_8072334C(s32, s32);
void func_80723484(s32);
void pathPlaybackGetPosition(s32, f32 *, f32 *, f32 *);
void func_80724994(s32, s32, s32, s32, s32);
f32 func_80612794(s16);
void func_80714A28(s32);

void func_806A7600(void *arg0) {
    EffectState *temp_v1;
    s32 temp;
    s32 cond;
    s32 flag;

    temp_v1 = D_807FBB40->unk174;
    if (!(D_807FBB40->unk60 & 0x10)) {
        if (D_807FBB40->unk58 == 0x93) {
            temp_v1->unk6 = -1;
        } else {
            temp_v1->unk6 = actorListLookupEntry(actorListFindIdByActor(D_807FBB40) & 0xFFFF);
        }
        if (temp_v1->unk6 != -1 && flagGet(temp_v1->unk6, 0) != 0) {
            actorDespawn(D_807FBB40);
            return;
        }
        actorAppendModelSubNode(D_807FBB40, 0.0f, 0.0f, 0.0f, -1);
        actorSetCollisionRadius(D_807FBB40, 175.0f);
        actorAppendModelNode(D_807FBB40, 0.0f, 12.0f, 0.0f, 80.0f, -1);
        temp_v1->unk0 = ((AA960ConfigInt *)D_807FBB40->unk124)->unk0;
        temp_v1->unk1 = ((AA960ConfigInt *)D_807FBB40->unk124)->unk4;
        temp_v1->unk2 = pathPlaybackStart(D_807FBB40, temp_v1->unk0, 0, 0.0f, 0.0f, 0.0f, 0);
        if (temp_v1 && temp_v1) {}  // FAKE: deadsweep: extra temp_v1 use blocks the s8 unk2 store->load forwarding and hoists the else-branch temp_v1 reload
        if (temp_v1->unk2 != -1) {
            func_807232B8(temp_v1->unk2, 1);
            func_80723284(temp_v1->unk2, temp_v1->unk1);
            func_80723320(temp_v1->unk2, -1);
            func_8072334C(temp_v1->unk2, 1);
        }
        temp_v1->unk4 = 0;
    } else {
        if (temp_v1->unk2 != -1) {
            func_80723484(temp_v1->unk2);
            pathPlaybackGetPosition(temp_v1->unk2, &D_807FBB40->unk7C, &D_807FBB40->unk80, &D_807FBB40->unk84);
        }
        D_807FBB40->unk80 += 5.0 * func_80612794(temp_v1->unk4);
        temp_v1->unk4 = (temp_v1->unk4 + 0x50) & 0xFFF;
        if (D_8076A068 % 0x18 == 0) {
            switch (D_807FBB40->unk58) {
            case 0x5B:
                temp = 6;
                break;
            case 0x6F:
                temp = 0x75;
                break;
            case 0x70:
                temp = 0x42;
                break;
            case 0x71:
                temp = 0x46;
                break;
            default:
                temp = -1;
                break;
            }
            flag = (temp == -1 || flagGet(temp, 0) != 0) ? 1 : 0;
            if (flag != 0) {
                func_807149B8(1);
                cond = 1;
                if (D_807FBB40->unk58 == 0x93) {
                    cond = 0;
                } else if (D_807FBB4C->unk58 == 3 && D_807FBB40->unk58 == 0x5B) {
                    cond = 0;
                } else if (D_807FBB4C->unk58 == 6 && D_807FBB40->unk58 == 0x6F) {
                    cond = 0;
                } else if (D_807FBB4C->unk58 == 5 && D_807FBB40->unk58 == 0x70) {
                    cond = 0;
                } else if (D_807FBB4C->unk58 == 4 && D_807FBB40->unk58 == 0x71) {
                    cond = 0;
                } else if (D_807FBB4C->unk58 == 2 && D_807FBB40->unk58 == 0x72) {
                    cond = 0;
                }
                if (cond != 0) {
                    func_807149C8(0xFF, 0xFF, 0xFF, 0x96);
                } else {
                    func_8071498C(&effectProximityFadeUpdate);
                    func_80714950(0x226);
                }
                func_80714A28(4);
                func_80714998(3);
                func_80714C08(arg0, 0.8f, D_807FBB40, 1, 2);
                D_807FBB40->unk144 = 2;
            } else {
                D_807FBB40->unk144 = 1;
            }
        }
    }
    if (D_807FBD70 == 4) {
        func_80686CF8(D_807FBB40);
        sfxPlayAtPositionPooled(D_807FBB40->unk7C, D_807FBB40->unk80, D_807FBB40->unk84, 0x2BF, 0xFF, 0x7F, 0x1E, 0, 0.0f, 0);
        actorDespawn(D_807FBB40);
        if (D_807FBB40->unk58 == 0x93) {
            func_80724994(3, 1, 0x27, 0, 0);
        } else {
            if (temp_v1->unk6 != -1) {
                flagSet(temp_v1->unk6, 1, 0);
            }
            slotQueueUpdate(0, 0, 0);
            slotQueueAddValue(0, 0, 0xA);
        }
    }
}
