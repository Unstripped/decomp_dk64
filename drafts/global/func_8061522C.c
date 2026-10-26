// func_8061522C (src/global/19A00.c): stage 4; closest diff 212 (permuter): byte-local placement and expression/register scheduling remain. Attempts: stored m2c local layout; simple min/max/value layout; typed temporary pointer layout; narrowed value assignment; 600-second permuter search.
typedef int s32;
typedef unsigned char u8;
typedef struct Actor { void *unk4; } Actor;
typedef struct P19aState { u8 pad0[0x78]; s32 flags; s32 unk7C; } P19aState;
extern u8 *D_807F5AF0;
extern s32 func_80611A44(void);
void func_80614F28(u8 *);

s32 func_8061522C(Actor *arg0) {
    u8 min;
    u8 max;
    s32 value;

    D_807F5AF0++;
    func_80614F28(&min);
    func_80614F28(&max);
    value = ((func_80611A44() >> 15) % 32767) % ((max - min) + 1) + min;
    if (value & 0xFF) {
        ((P19aState *)arg0->unk4)->unk7C = (value & 0xFF) - 1;
        ((P19aState *)arg0->unk4)->flags |= 2;
        return 0;
    }
    return 1;
}
