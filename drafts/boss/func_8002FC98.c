// func_8002FC98 (src/boss/B100.c): from .scratch/Boss3D/func_8002FC98_best.c
void func_80614D00(void *, f32, f32);
void func_80614EBC(void *, s32);

void func_8002FC98(arg0, arg1, arg2, arg3)
BossE_B100_Actor *arg0;
u8 arg1;
s32 arg2;
u8 arg3;
{
    BossE_B100_Actor **actor_list;
    BossE_B100_Actor *actor;
    s16 i;

    actor_list = arg0->unk17C;
    i = 0;
    do {
        if (arg1 & (1 << i)) {
            actor = arg0;
            if (i != 0) {
                actor = actor_list[i - 1];
            }
            switch (arg2) {
            case 1:
            case 2:
                actor->unk132 = arg2;
                break;
            case -1:
            case 0:
                actor->unk138 = arg2;
                break;
            default:
                func_80614EBC(actor, arg2);
                if (arg3 != 0) {
                    func_80614D00(actor, (f64)arg3 * 0.01, 0.0f);
                }
                break;
            }
        }
        i++;
    } while (i < 4);
}
