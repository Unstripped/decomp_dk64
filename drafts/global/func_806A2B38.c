// func_806A2B38 (src/global/A7710.c): stage 6: target = one lui %hi(D_807FC7D4) + hi store first + lo store in jr delay slot; symbol u64 store always emits lo-first with 2 lui; pointer/constant-address stores are hi-first with one base but use a real register
/* func_806A2B38 (src/global/A7710.c) - stage 6, 4 instructions too long.
 * Target (16 insns): one `lui at,%hi(D_807FC7D4)` then `sw t1,%lo(D_807FC7D4)(at)`
 * (t1 = high word) and `sw t0,%lo(D_807FC7D0)(at)` (low word) in the jr delay slot.
 * Any symbol-form 64-bit store emits lo-first with TWO address materialisations:
 *   lui at,%hi(D_807FC7D0); sw t0,%lo(D_807FC7D0)(at);
 *   lui at,%hi(D_807FC7D0); ... sw t1,%lo(D_807FC7D0+4)(at)
 * Probes that all give the same 20-insn symbol form: u64/s64/OSTime global, array
 * element `A[0]`, struct member `s.t`, `*(u64 *)&D`, `((u64 *)&D)[0]`,
 * `*(u64 *)((u8 *)&D - 4)`, `p = &D; *p = ...`, volatile global/u64 cast, u64 local,
 * register u64 local. Store through a register pointer (`u64 *p` param or `*P` global)
 * or through a raw constant address `*(u64 *)0x807FC7D0` is hi-first with ONE base
 * (constant form: `lui t2,0x8080; sw t1,-0x382C(t2); sw t0,-0x3830(t2)`), i.e. the
 * target's ordering only appears on the pointer/constant store path but the target
 * keeps $at addressing, so it must be a symbol-based lvalue that IDO treats as one
 * 8-byte object with the base taken at the high half. Not found yet.
 */
extern u64 D_807FC7D0;

void func_806A2B38(Actor *actor) {
    D_807FC7D0 = osGetTime() - *(u64 *)actor->unk174;
}
