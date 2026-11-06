---
title: "IDO 5.3 argument home-slot spills and frame layout"
description: "Rules for when IDO 5.3 -O2 -mips2 spills incoming register arguments to caller home slots, verified with micro-tests while matching RDP display-list builders in src/global/0.c."
origin: "ok-fine dk64/notes/ido-argument-home-slot-spills"
---
# IDO 5.3 argument home-slot spills and frame layout

Facts established with micro-tests (`/opt/ido5.3/cc -c -non_shared -G 0 -Xcpluscomm -signed -O2 -mips2` inside the `dk64-decomp` container) while matching RDP display-list builders in `src/global/0.c`.[^microtest]

- **Calls force home-slot spills of modified params.** Assigning to a parameter (`a1 = a1 & 0xFF;`) plus any call in the function makes IDO emit `move a1,t6` AND store the masked value to the caller home slot `0x4($sp)` before the call. Without any call, no spill occurs (verified with a no-call probe).
- **Unused stack-passed args cost nothing.** A function defined with 13 params (4 of them home-slot params) whose stack args 5-13 are never read has the same frame as a 5-arg version: no extra `sw` in the prologue and no extra frame. The home-slot spill `sw a1,4(sp)` appears because the caller wrote the home slot in its own prologue, not because the callee reads it. The callee-side home-slot spill for `a1` (the 5th arg in the caller) only appears when that arg is actually used in a call (verified: 9-arg definition with unused stack args = 32-byte frame, identical to 5-arg version).
- **Frame sizing:** `sp = 0x20` frame with `a0,a1` at `32,36(sp)` plus `ra` at `28(sp)`, and the arg-spill block of a 13-arg call at `16..48(sp)`, all within the same 32-byte frame plus the incoming `a4`-style caller home slots at `+0x20` offset — the frame grows by 16 bytes per extra stack-arg-past-5 in the call, not by the arg count of the enclosing function.
- **Reg allocation from arg liveness:** a pointer (`arg0`) live across many calls stays in `s0`, and a masked int (`a1 & 0xFF`) live across many calls stays in `s1`; both are pushed into callee-saved registers only after enough pressure (several calls), not after a single call. Reproduced by storing through `a0` and calling `h(a0, masked_a1, ...)` repeatedly between RDP word stores in the right interleaving (stores of constants 0xE7000000/0, 0xE200001C/0, 0xE3000A01/0x300000, then call, then stores of 5, 6, call, 7, 8, 9, call, ...).
- **Statement-order effect:** the IDO scheduler hoists `lui/ori` constant loads into the prologue block before the first `sw` only when the enclosing function has more call pressure (i.e. more total stores+calls), not when it has fewer. Ordering of `andi s1,a1,0xff; move s0,a0; move a1,s1; sw zero,16(sp); move a3,zero; jal; move a2,zero` at the first call in a 6-call probe reproduces this exact pattern when the function contains enough stores after the last call (verified tail of 22+ stores).

Use these rules when the expected asm shows `move v0,a0` + home-slot spill at function entry (a modified param reg moved to a copy reg and stored to its home slot) or callee-saved `s0`/`s1` appearing in a function whose C body has no obvious reason for them. Link: IDO matching quirks.

## Sources

[^microtest]: urn:ok-fine:pasted:ido-arg-spill-microtests
