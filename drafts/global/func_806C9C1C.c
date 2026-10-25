// func_806C9C1C (src/global/CC800.c): G01 stage 6 near-miss: addiu s0/s2 order only
extern s32 D_80750B34[];
extern s32 D_80750B48;
void func_806F91B4(s32, u8, s32);
void func_806F833C(s32);

/* stage 6: instruction-identical except `addiu s0,&B34` is emitted before `addiu s2,&B48` (target: s2 first, then s0, then andi s1).
 * Tried for-loop (adds guard), end-pointer local, *p++ in arg, p++ in body. */
void func_806C9C1C(s32 arg0) {
    s32 *p = D_80750B34;

    do {
        func_806F91B4(*p, arg0, 0x270F);
    } while (++p != &D_80750B48);
    func_806F833C(0);
}
