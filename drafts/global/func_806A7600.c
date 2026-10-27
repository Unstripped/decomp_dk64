// func_806A7600 (src/global/AA960.c): stage 5: size (322 vs 323 instr), frame 0x38, blocks and callees match. Remaining: temp_v1 reload scheduled in the bnezl delay slot instead of above it (expected lw t4,52(sp);bnezl;lb a0,2(t4)), v0/v1 swap between &D_807FBB40 and temp_v1 around the config reads, and 'move a0,v0'+sb in the branch delay slot instead of expected sb v1 = 0x2;lb a0,2(v1). Also the sfx-id if/else chain and the temp==-1 || func() condition compile with bnel/sltu forms instead of the expected beq chain.
typedef struct AA960Config124 {
    f32 unk0;
    f32 unk4;
    f32 unk8;
} AA960Config124;

typedef struct AA960State174 {
    u8 unk0;
    u8 unk1;
    s8 unk2;
    u8 pad3[1];
    u16 unk4;
    s16 unk6;
    u16 unk8;
    s16 unkA;
} AA960State174;

extern ActorGlobalState D_807FBB70;
extern s16 D_80750384;
extern s16 D_8075038C;
extern f32 D_80750388;
void func_806C9974(s32, s32);
void func_8067ACB4(Actor *);
s32 func_806725A0(Actor *, s16);
s16 func_80672A70(s16, s16);
void actorApplyVelocity(Actor *);
void func_80665564(Actor *, f32);
void func_806086CC(f32, f32, f32, s32, s32, s32, s32, s32, f32, s32);
void actorAppendModelNode(Actor *, f32, f32, f32, f32, s32);
void actorAppendModelSubNode(Actor *, f32, f32, f32, s32);
void func_8066EB40(Actor *, f32);
void actorUpdateModelMatrix(Actor *, s32);

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
s32 func_80723020(void *, s32, s32, f32, f32, f32, s32);
void func_807232B8(s32, s32);
void func_80723284(s32, s32);
void func_80723320(s32, s32);
void func_8072334C(s32, s32);
void func_80723484(s32);
void func_807238D4(s32, f32 *, f32 *, f32 *);
void func_80724994(s32, s32, s32, s32, s32);
f32 func_80612794(s16);
void func_80714A28(s32);

void func_806A7600(void *arg0) {
    AA960State174 *temp_v1;
    s32 temp;
    s32 cond;

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
        func_8066EB40(D_807FBB40, 175.0f);
        actorAppendModelNode(D_807FBB40, 0.0f, 12.0f, 0.0f, 80.0f, -1);
        temp_v1->unk0 = ((AA960ConfigInt *)D_807FBB40->unk124)->unk0;
        temp_v1->unk1 = ((AA960ConfigInt *)D_807FBB40->unk124)->unk4;
        temp_v1->unk2 = func_80723020(D_807FBB40, temp_v1->unk0, 0, 0.0f, 0.0f, 0.0f, 0);
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
            func_807238D4(temp_v1->unk2, &D_807FBB40->unk7C, &D_807FBB40->unk80, &D_807FBB40->unk84);
        }
        D_807FBB40->unk80 += 5.0 * func_80612794(temp_v1->unk4);
        temp_v1->unk4 = (temp_v1->unk4 + 0x50) & 0xFFF;
        if (D_8076A068 % 0x18 == 0) {
            if (D_807FBB40->unk58 == 0x5B) {
                temp = 6;
            } else if (D_807FBB40->unk58 == 0x6F) {
                temp = 0x75;
            } else if (D_807FBB40->unk58 == 0x70) {
                temp = 0x42;
            } else if (D_807FBB40->unk58 == 0x71) {
                temp = 0x46;
            } else {
                temp = -1;
            }
            cond = temp == -1 || flagGet(temp, 0) != 0;
            if (cond != 0) {
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
                    func_8071498C(&func_8071EB70);
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
        func_806086CC(D_807FBB40->unk7C, D_807FBB40->unk80, D_807FBB40->unk84, 0x2BF, 0xFF, 0x7F, 0x1E, 0, 0.0f, 0);
        actorDespawn(D_807FBB40);
        if (D_807FBB40->unk58 == 0x93) {
            func_80724994(3, 1, 0x27, 0, 0);
        } else {
            if (temp_v1->unk6 != -1) {
                flagSet(temp_v1->unk6, 1, 0);
            }
            func_806F8BC4(0, 0, 0);
            func_806F91B4(0, 0, 0xA);
        }
    }
}
