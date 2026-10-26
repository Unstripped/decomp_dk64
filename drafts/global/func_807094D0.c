// func_807094D0 (src/global/10E1D0.c): stage 6: 900-second permuter best score 4415; readable hint hoists final 1.0f into local volume. Remaining control-flow/global register coloring mismatch.
extern u8 D_807444EC;
extern u8 D_807444F4;
extern s32 D_8076D1F8;
extern s32 D_807FBB64;
extern s8 D_807FD9BC;
extern s8 D_807FD9BD;
extern f32 D_807FD9C4;
extern s32 D_807FD9C8;
void timerQueueCancel(void *);
void n_alSndpPlay(s32, s16, s32, s32, f32, s32, s32 *);

void func_807094D0(arg0)
u8 arg0;
{
    f32 volume;
    s32 temp_t6;

    temp_t6 = arg0;
    D_807444F4 = D_807444EC;
    switch (temp_t6) {
    case 2:
        D_807FD9C4 = 1.0f;
        D_807FD9BC = 0;
        D_807444F8 = 1;
        D_807444EC = 6;
        break;
    case 3:
        D_807FD9C4 = 0.5f;
        D_807FD9BC = 0;
        D_807444F8 = 2;
        D_807444EC = 6;
        D_807FD9BD = 2;
        if ((D_807444F4 == 1) && (D_807FBB64 & 1)) {
            timerQueueCancel(0);
        }
        break;
    }
    volume = 1.0f;
    n_alSndpPlay(D_8076D1F8, 0x1BC, 0x7FFF, 0x3F, volume, 0, &D_807FD9C8);
}
