// func_806A2B38 (src/global/A7710.c): stage 6: text-identical instruction shape except IDO emits the lo/hi half stores with one lui in target vs two lui + addend-4 store here (64-bit global store to D_807FC7D0)
extern u64 D_807FC7D0;

void func_806A2B38(Actor *actor) {
    D_807FC7D0 = osGetTime() - *(u64 *)actor->unk174;
}
