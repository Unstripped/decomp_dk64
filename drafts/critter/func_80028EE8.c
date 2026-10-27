// func_80028EE8 (src/critter/4840.c): stage 4->5: the sp24 slot (0x24 vs 0x20) is fixed by dropping the sp24 local: write (arg3 << 5) inline at the 3 uses (the CSE temp then takes slot 0x24); remaining diffs: (1) first call 'addu a1,t8,v0' operand order (target D_8002A1C0 first); (2) entry load of D_8002A1C4 not address-CSE'd in ours (lui v1/lw %lo(v1) vs lui;addiu;lw a1,0(v1)) and else branch then puts &D_807FBB44 in v1 not a0; target value lives in a1 (arg1 register). Fake 'D_8002A1C4 = D_8002A1C4;' before the if reproduces the address CSE (score 440->365) but adds a sw; &-pointer alias (Actor_4840 **p) 1111; cur local/arg1 cast no effect; extra uses (&& , repeated reads) no effect. Param decl order and s16 placeholders no effect.
typedef struct TextData {
    char pad0[2];
    s16 unk2;
    s16 *unk4;
    s16 *unk8;
} TextData;
s16 func_800288A8(TextData *arg0, char *arg1, s16 arg2);
char *_strcpy(char *, const char *);
typedef struct Actor_4840 {
    char pad0[0x7C];
    f32 unk7C;
    char pad80[0xEC - 0x80];
    s16 unkEC;
    s16 unkEE;
    char padF0[0x168 - 0xF0];
    s16 unk168;
    char pad16A[0x174 - 0x16A];
    u8 *unk174;
} Actor_4840;
s32 func_806FBD5C(s16, s32);
void heapFree(void *);
void actorSpawn(s32, s32);
extern s16 D_80744490;
extern Actor_4840 *D_807FBB44;
extern s32 D_8002A1C0;
extern Actor_4840 *D_8002A1C4;
void func_80028EE8(u8 arg0, s32 arg1, s16 arg2, u8 arg3, s16 arg4, u16 arg5) {
    u8 *s0;
    s16 sp2A;

    sp2A = (D_80744490 - func_806FBD5C(arg0, D_8002A1C0 + (arg3 << 5))) * 2;
    if (D_8002A1C4 != NULL) {
        s0 = D_8002A1C4->unk174;
        heapFree(*(void **)(s0 + 8));
        heapFree(*(void **)(s0 + 4));
    } else {
        actorSpawn(0x10A, 0);
        s0 = D_807FBB44->unk174;
        *(s16 *)s0 = arg2 * 4;
        D_8002A1C4 = D_807FBB44;
        D_807FBB44->unkEC = 0;
    }
    D_8002A1C4->unk7C = (f32)func_800288A8((TextData *)s0, (char *)(D_8002A1C0 + (arg3 << 5)), sp2A);
    D_8002A1C4->unkEE = 0;
    D_8002A1C4->unk168 = arg5 + 0xE;
    _strcpy((char *)s0 + 0x820, (char *)(D_8002A1C0 + (arg3 << 5)));
    arg4 = 1;
    do {
        s0[0x810 + arg4] = 0;
        arg4++;
    } while (arg4 < 0x10);
    s0[0x810] = 0xC;
}
