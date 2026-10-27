// func_80026E0C (src/critter/0.c): stage 5 (score 60): everything matches incl. frame 0x50 and slots except one pair order: target 'addiu s5,%lo(D_807F6C28); move s7,zero; blez' vs ours 'move s7,zero; addiu s5; blez'. Key tricks: locals decl order g,grp,ent,j,src (frame 0x50, grp/ent homes 0x48/0x44, uninit loads), no cnt local, inner if(j==0){..}else{ent+=0x2C;}. Tried g=0 placements, comma, for-init.
extern void *D_80029BA0;
extern s32 D_807F6C28;
void *memcpy(void *, const void *, unsigned int);
void *func_80610FE8(s32);
void heapClearBlock(void *);
s16 func_806531B8(f32, f32, f32, s32);
void func_80027118();

void func_80026E0C(u8 *arg0) {
    s32 g;
    u8 *grp;
    u8 *ent;
    s32 j;
    u8 *src;

    if (arg0 != NULL) {
        memcpy(D_80029BA0, arg0, 1);
        src = arg0 + 1;
        g = 0;
        if (*(u8 *)D_80029BA0 > 0) {
            do {
                j = 0;
                if (g == 0) {
                    *(void **)((u8 *)D_80029BA0 + 4) = func_80610FE8(*(u8 *)D_80029BA0 * 0xC);
                    heapClearBlock(*(void **)((u8 *)D_80029BA0 + 4));
                    grp = *(u8 **)((u8 *)D_80029BA0 + 4);
                } else {
                    grp += 0xC;
                }
                memcpy(grp, src, 3);
                src += 3;
                if (grp[1] > 0) {
                    do {
                        if (j == 0) {
                            *(void **)(grp + 4) = func_80610FE8(grp[1] * 0x2C);
                            heapClearBlock(*(void **)(grp + 4));
                            ent = *(u8 **)(grp + 4);
                        } else {
                            ent += 0x2C;
                        }
                        memcpy(ent, src, 0x20);
                        if (D_807F6C28 != 0) {
                            *(s16 *)(ent + 0x28) = func_806531B8((f32) * (s16 *)(ent + 0), (f32) * (s16 *)(ent + 2), (f32) * (s16 *)(ent + 4), 0);
                            ent[0x24] = 0xFF;
                        }
                        j++;
                        src += 0x20;
                    } while (j < grp[1]);
                }
                func_80027118(grp);
                g++;
            } while (g < *(u8 *)D_80029BA0);
        }
    }
}
