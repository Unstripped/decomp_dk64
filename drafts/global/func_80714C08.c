// func_80714C08 (src/global/119370.c): Stage 6: exact frame/control flow/instructions; only v0/v1 allocation for the restored actor pointer differs.
void actorGetNodePos(void *, s32, s32 *, s32 *, f32 *);

void func_80714C08(s32 arg0, s32 arg1, void *arg2, s32 arg3, u8 arg4) {
    s32 sp3C;
    s32 sp38;
    f32 sp34;

    actorGetNodePos(arg2, arg3, &sp3C, &sp38, &sp34);
    if (!(((Actor *) arg2)->unk60 & 0x200) && (((Actor *) arg2)->unk4 != NULL) && (D_807FDB36 & 0x80)) {
        func_80714A38(0x40);
    }
    func_80714D08(arg0, arg1, sp3C, sp38, sp34, arg2, 0, arg3, (s32) arg4);
}
