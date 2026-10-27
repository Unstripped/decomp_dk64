// func_80029E54 (src/bonus/2690.c): from .scratch/BonusC/func_80029E54_best.c
typedef struct {
    void *unk0;
    u8 unk4;
} BonusC_9E54_S;

void func_80029E54(void *arg0) {
    s32 i;
    s16 *X = &D_8002D8CA - 1;
    s8 *base = ((Actor_BB44 *)arg0)->unk178;

    for (i = 1; i != 7; i++) {
        if (actorSpawn(0x147, X[i - 1]) != 0) {
            BonusC_9E54_S *temp_v1 = (BonusC_9E54_S *)D_807FBB44->unk174;
            s16 *temp_a1 = D_807FBB44->unk17C;
            Point3f *pt;
            f32 scale;

            *temp_a1 = X[i - 1];
            temp_v1->unk0 = arg0;
            temp_v1->unk4 = i - 1;
            pt = (Point3f *)((u8 *)*D_807F5FD4 + (base[(u8)(i - 1) + 8] & 0x7F) * 12);
            pt++;
            D_807FBB44->unk7C = pt->x;
            D_807FBB44->unk80 = pt->y;
            D_807FBB44->unk84 = pt->z;
            D_807FBB44->unk154 = 0;
            D_807FBB44->unk60 |= 0x1000;
            D_807FBB44->unkE6 = 0x800;
            if (i != 6) {
                func_806F0C18(D_807FBB44, temp_a1);
                actorScriptStart(D_807FBB44, D_8002D8D4[i - 1]);
            }
            if (i != 6) {
                scale = 0.25f;
            } else {
                scale = 0.04f;
            }
            D_807FBB44->unk4->unk34 = scale;
            D_807FBB44->unk4->unk38 = scale;
            D_807FBB44->unk4->unk3C = scale;
        }
    }
}
