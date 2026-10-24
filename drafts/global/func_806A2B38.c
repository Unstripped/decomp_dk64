// func_806A2B38 (src/global/A7710.c): stage 6: u64 store half order + 1 extra lui vs target (target: one lui %hi(D_807FC7D4), low word stored first, high word in jr delay slot)
// except the order of the two 4-byte halves of the u64 store and one extra address
// computation: target does `lui at,%hi(D_807FC7D4); subu t1,v1,t9; sw t1,%lo(D_807FC7D4)(at);
// jr ra; sw t0,%lo(D_807FC7D0)(at)` (one lui, low word stored first, high word in the jr
// delay slot); this source emits hi-then-lo with a separate lui per half. Tried: plain
// u64 global store, *(u64*)&global, u64 local, volatile u64 via cast, volatile global
// (materialises the address in t2), two u32 globals with t>>32 (calls __ull_rshift).
extern u64 D_807FC7D0;

void func_806A2B38(Actor *actor) {
    D_807FC7D0 = osGetTime() - *(u64 *)actor->unk174;
}
