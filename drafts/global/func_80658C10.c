// func_80658C10 (src/global/55B20.c): stage 6: loop identical; tail a0 vs v0 for found entry, two loads scheduled before the sh stores
extern s32 D_8076A064;

void func_80658C10();

void func_80658C10(arg0, arg1, arg2, arg3)
s32 arg0;
s16 arg1;
s16 arg2;
s16 arg3;
{
    s32 i;
    s32 found;
    M55P6Entry *p;

    found = 0;
    i = 0;
    while ((i < 10) && !found) {
        if (((M55P6Entry *)&D_807F7290)[i].unk10 != 0) {
            i++;
        } else {
            found = 1;
        }
    }
    if (found) {
        p = (M55P6Entry *)&D_807F7290 + i;
        p->unk10 = 1;
        p->unk4 = arg1;
        p->unk6 = arg2;
        p->unk8 = arg3;
        p->unkC = D_8076A064;
        p->unk0 = arg0;
    }
}
