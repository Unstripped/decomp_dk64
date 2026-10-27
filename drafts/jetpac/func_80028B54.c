// func_80028B54 (src/jetpac/3480.c): text-identical, reloc only: IDO emits D_8002D1A0+0x18 where target relocs D_8002D1B8 (stage 6 done); permuter found body D_8002D190[x%4] inline in loop with x=*arg0/4
typedef struct {
    void *frame;
    s32 unk4;
    s32 unk8;
    s32 unkC;
    s32 unk10;
    s32 unk14;
} JetpacSprite;

extern JetpacSprite D_8002D1A0[];
extern void *D_8002D190[];

void func_80028B54(s32 *arg0) {
    s32 x = *arg0 / 4;
    s32 i;

    for (i = 0; i < 6; i++) {
        D_8002D1A0[i].frame = D_8002D190[x % 4];
    }
}
