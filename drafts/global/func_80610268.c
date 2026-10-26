// func_80610268 (src/global/14CF0.c): from .scratch/SmallC/func_80610268_best.c
extern s8 D_80746834;
extern OSMesgQueue D_807659E8;
extern u8 D_807F059C[];
void func_80610268(s32 arg0) {
    void *sp34;
    s32 temp_t8;
    do {
        D_80746834 = 8;
        osRecvMesg(&D_807659E8, &sp34, 1);
        D_80746834 = 0;
        D_807F059C[(u32)sp34 >> 0x10] = 0;
        temp_t8 = (s32)sp34 & 0xFFFF;
        sp34 = (void *)temp_t8;
    } while (temp_t8 != arg0);
}
