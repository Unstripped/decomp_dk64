// func_80675E3C (src/global/7A510.c): from .scratch/Beh7984B/func_80675E3C_best.c
typedef struct Beh7984B_Entry {
    s16 unk0;
    s32 unk4;
} Beh7984B_Entry;

s32 func_80675E3C(Beh7984B_Entry *arg0, s16 arg1, s16 arg2) {
    s16 s1;
    s32 s2;
    s32 match;

    do {
        s1 = arg0->unk0;
        s2 = arg0->unk4;
        match = func_80675C70(arg1, arg2, s1);
        arg0++;
        if (match) {
            break;
        }
    } while (s1 != 0);
    return s2;
}
