// func_80618D68 (src/global/19A00.c): stage 4: uopt trace confirms target save-set/roles; u8 candidate has target frame but target omits its post-increment truncation, while s32 variants enlarge frame
typedef int s32;
typedef unsigned char u8;
typedef float f32;
typedef struct Actor Actor;

void func_80614F28(u8 *);
void func_80714950(s32);
void func_8071496C(s32);
void func_8071498C(void *);
void func_807149B8(s32);
void func_807149FC(s32);
void func_80714A28(s32);
void func_80714C08(void *, f32, Actor *, u8, s32);
extern void *D_80746B80[];
extern void func_8071D28C(void);

void func_80618D68(Actor *arg0) {
    u8 sp43;
    u8 sp42;
    void **var_s0;
    u8 var_s1;

    func_80614F28(&sp43);
    func_80614F28(&sp42);
    var_s1 = sp43;
    if ((s32)sp43 < (s32)sp42) {
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
