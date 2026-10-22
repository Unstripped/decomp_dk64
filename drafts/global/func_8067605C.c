// func_8067605C (src/global/7A510.c): from .scratch/Beh7984B/func_8067605C_best.c
typedef struct Beh7984B_80748F58 {
    u16 unk0;
    u8 unk2;
    u8 pad3;
    u16 unk4;
} Beh7984B_80748F58;

extern s8 D_80748E50[][9];
extern Beh7984B_80748F58 D_80748F58[];

void func_8067618C(Actor *, s8 *);
void func_8066EABC(Actor *);
void func_8066EA64(Actor *, s8);
void func_8066E5CC(Actor *, s8, u16);

void func_8067605C(Actor *arg0, u8 arg1) {
    s32 match;
    s16 i;
    s8 *ptr;

    func_8067618C(arg0, (s8 *)&arg1);
    func_8066EABC(arg0);
    ptr = D_80748E50[arg1];
    if (*ptr != -1) {
        do {
            match = 0;
            func_8066EA64(arg0, *ptr);
            i = 0;
            do {
                if ((arg0->unk58 == D_80748F58[i].unk0) && (*ptr == D_80748F58[i].unk2)) {
                    func_8066E5CC(arg0, *ptr, D_80748F58[i].unk4);
                    match = 1;
                } else {
                    func_8066E5CC(arg0, *ptr, 0);
                    i++;
                }
            } while ((i < 24) && (!match));
            ptr++;
        } while (*ptr != -1);
    }
}
