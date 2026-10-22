// func_80685B44 (src/global/89250.c): from .scratch/Beh8923B/func_80685B44_best.c
void func_807180F4(void);

void func_80685B44(void *arg0, u8 arg1, f32 arg2, u8 arg3, u8 arg4, s16 arg5, s16 arg6, s16 arg7, s16 arg8) {
    s16 var_s1;
    s8 dx;
    s8 dz;

    var_s1 = 0;
    if (arg3 > 0) {
        do {
            dx = ((func_80611A44() >> 15) % 32767 % (arg4 * 2)) + (-arg4);
            dz = ((func_80611A44() >> 15) % 32767 % (arg4 * 2)) + (-arg4);
            func_80714950(-arg5 - ((func_80611A44() >> 15) % 80));
            func_8071498C(func_807180F4);
            func_807149B8(1);
            func_80714998(2);
            if (arg1 != 0) {
                func_8071496C((s16)arg1);
            }
            func_80714CC0(arg0, arg2, (f32)(arg6 + dx), (f32)arg7, (f32)(arg8 + dz));
            var_s1 = (s16)(var_s1 + 1);
        } while (var_s1 < arg3);
    }
}
