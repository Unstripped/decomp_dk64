// func_80025404 (src/multiplayer/0.c): stage 5 (frame 0x68 + 9 saves + var_s6 sp50 slot match; 56 diff lines of 153, harness-measured). Only diffs: lui/addiu s5=&D_8071F3C0 sits in the loop preheader (after blez) instead of at the head of the unk260==0 block, and p shares s5 with the reloaded D_807FC924 (lw s5,0(s7) vs lw t5,0(s7)). Key tricks: void *p holds &D_8071F3C0 and is re-assigned p=D_807FC924 before the func_80714C08 call (permuter find: makes uopt colour the address candidate so 774 is not hoisted as multu const; without it li s8,774 + multu replaces the shift chain); s32 temp_s3 (not s8); locals declared i,ret,temp_s3,sc,ac,var_s6 (var_s6 last: gives sp50 slot, frame 0x68).
extern u8 D_8074E77C;
extern u8 D_8071F3C0;
extern u8 D_807207BC;
void effectFreeAndUnlink(s32);
void func_807149B8(s32);
void func_807149FC(s32);
void func_80714998(s32);
void func_807149C8(s32, s32, s32, s32);
void func_8071498C(void *);
s32 func_80714C08(void *, f32, void *, s32, s32);

typedef struct MpA_Plr { s32 unk0; void *unk4; char pad[0x2E8]; } MpA_Plr;
typedef struct MpA_Act { char pad[0x174]; char pad2[0xEC]; s32 unk260; } MpA_Act;
typedef struct MpA_Sc { char pad[0x2FA]; s8 unk2FA; s8 unk2FB; s8 unk2FC; s8 unk2FD; char pad2[8]; } MpA_Sc;
typedef struct MpA_Act2 { char pad[0x174]; MpA_Act *unk174; } MpA_Act2;
s32 func_80025404(void) {
    s32 i; s32 ret; s32 temp_s3; MpA_Sc *sc; MpA_Act *ac; s32 var_s6;
    void *p;
    ret = -1; i = 0;
    if ((s32) D_807FC928 > 0) {
      p = &D_8071F3C0;
      do {
        ac = ((MpA_Act2 *)((MpA_Plr *)D_807FC924)[i].unk4)->unk174;
        sc = &((MpA_Sc *)D_807FC950)[i];
        if (func_806F8AD4(1, i) != 0) {
            temp_s3 = sc->unk2FD + sc->unk2FB;
            if (ac->unk260 == 0) {
                switch (*(&D_8074E77C + i)) { case 0: case 3: var_s6 = 0xF; break; case 1: case 2: case 4: case 5: var_s6 = 0xD; break; }
                func_807149B8(1); func_807149FC(-1); func_80714998(2); func_807149C8(0xFF, 0xFF, 0xFF, 0x7F);
                func_8071498C(p);
                p = D_807FC924; ac->unk260 = func_80714C08(&D_807207BC, 0.5f, ((MpA_Plr *)p)[i].unk4, var_s6, 2);
                sc->unk2FA = temp_s3;
            }
            if (sc->unk2FA < temp_s3) { sc->unk2FA = temp_s3; }
            ret = i;
        } else {
            if (ac->unk260 != 0) {
                effectFreeAndUnlink(ac->unk260);
                ac->unk260 = 0;
                sc = &((MpA_Sc *)D_807FC950)[i]; sc->unk2FA = 0;
            }
        }
        i++;
      } while (i < (s32) D_807FC928);
    }
    return ret;
}
