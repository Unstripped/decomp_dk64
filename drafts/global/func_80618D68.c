// func_80618D68 (src/global/19A00.c): stage 4; closest diff 482 (permuter): local stack offsets and callback/floating-point scheduling remain. Attempts: stored u8 postincrement; s32 loop counter; explicit u8 cast increment (1211); direct table-pointer form; 600-second permuter search.
typedef int s32;
typedef unsigned char u8;
typedef float f32;
typedef struct Actor Actor;
extern void *D_80746B80[];
void func_80614F28(u8 *);
void func_80714950(s32);
void func_8071496C(s32);
void func_8071498C(void *);
void func_807149B8(s32);
void func_807149FC(s32);
void func_80714A28(s32);
void func_80714C08(void *, f32, Actor *, u8, s32);
extern void func_8071D28C(void);

void func_80618D68(Actor *arg0) {
    u8 sp43;
    u8 sp42;
    void **var_s0;
    s32 var_s1;

    func_80614F28(&sp43);
    func_80614F28(&sp42);
    var_s1 = sp43;
    if (((s32)(sp43 ^ (1 * 0))) < (s32)sp42) {
        if (func_8071D28C) {
        }
        var_s0 = &D_80746B80[sp43];
        do {
            func_8071498C(func_8071D28C);
            func_807149FC(-1);
            func_807149B8(1);
            func_8071496C(1);
            func_80714950(1);
            func_80714A28(0x20);
            func_80714C08(*var_s0, 0.2f, arg0, 7, 0);
            var_s1++;
            var_s0++;
        } while ((s32)var_s1 < (s32)sp42);
    }
}
