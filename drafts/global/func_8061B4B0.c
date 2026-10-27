// func_8061B4B0 (src/global/201B0.c): bss-blocked: text-exact (TEXT OK) with 'u64 D_807F5CE0;' DEFINED in this TU (extern gives a second lui in B4E4's u64 zero store). Needs .bss split at 0x807F5CE0.
// NOTE: D_807F5CE0 must be DEFINED in this TU (needs .bss split in yaml from 0x807F5CE0); extern gives 2 luis on the store in func_8061B4E4.
u64 D_807F5CE0;

u8 func_8061B4B0(void) {
    return D_807F5CE0 != 0;
}
