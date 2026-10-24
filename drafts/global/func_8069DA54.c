// func_8069DA54 (src/global/9DD70.c): stage 6: same blocks/length; mine keeps the actor in v0 with an extra 'move v0,a1' and inverts the unk154 if/else test (target uses beqzl/beql)
extern Actor *D_807FBB40;
void renderCallbacksRegister(void *, void *, s32);
void heapFree(void *);
void actorDespawn(Actor *);
void func_8069D424(Actor *);
Gfx *func_8069D930(Gfx *, Actor *);

void func_8069DA54(void) {
    Actor *actor;
    u8 *model;

    actor = D_807FBB40;
    model = (u8 *)actor->unk174;
    if (*(s16 *)(actor->unkE8 + 6) != 0) {
        renderCallbacksRegister(func_8069D930, D_807FBB40, 3);
        return;
    }
    if (!(actor->unk60 & 0x10)) {
        actor->unk168 = *(u16 *)(model + 4);
        actor = D_807FBB40;
    }
    if (actor->unk154 == 0) {
        if (actor->unk168 != 0) {
            actor->unk168--;
        } else {
            actor->unk154 = 1;
        }
    } else if (actor->unk154 == 1) {
        if (actor->unk155[0] != 3) {
            renderCallbacksRegister(func_8069D424, D_807FBB40, 3);
        }
        switch (actor->unk155[0]) {
        case 0:
            if ((0xFF - model[8]) < actor->unk15F) {
                actor->unk15F = 0xFF;
                D_807FBB40->unk155[0]++;
                D_807FBB40->unk168 = *(u16 *)(model + 6);
            } else {
                actor->unk15F += model[8];
            }
            break;
        case 1:
            if (actor->unk168 != 0) {
                actor->unk168--;
            } else {
                actor->unk155[0]++;
            }
            break;
        case 2:
            if (actor->unk15F < model[9]) {
                actor->unk155[0]++;
                D_807FBB40->unk15F = 0;
            } else {
                actor->unk15F -= model[9];
            }
            break;
        case 3:
            heapFree(*(void **)model);
            actorDespawn(D_807FBB40);
            break;
        }
    }
}
