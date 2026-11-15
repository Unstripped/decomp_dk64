# tagBarrelCheckKongFlag (global, src/global/80150.c)
## Sites
global:806832F4:other:871b3e other: `ret = p->found != 0;` with no final return: ret coloured v0 (move v0,t3 at 0x7f6c) only when found is an ilod read through p.
## Attempts
2026-11-15 HackthrowableBarrelUpdate HackthrowableBarrelUpdate anthropic/claude-opus-5-5:high: scalar s32 found/isSet/value (homes 0x28/0x24/0x20 reproduce the struct frame) with tails: return found && isSet == 0 -> 23; ret + if + return ret -> 8; ret = isSet == 0 then return ret -> 20; fall-off -> 23; `if ((ret = found != 0) != 0)` fall-off -> 23; if (found) return isSet == 0; return 0 -> 17; ternary (ret = found != 0) ? isSet == 0 : ret -> 6
2026-11-15 HackthrowableBarrelUpdate HackthrowableBarrelUpdate anthropic/claude-opus-5-5:high: struct: info.* fall-off without p -> 7 (found in t3, beqzl lw ra); ret = p->isSet == 0 + return ret -> 8; ternary via p -> 19; info.* + return ret -> 19; every access through p -> 11; p only after the call -> 11
## Untried ideas
none concrete; the scalar-local frame result could retire the KongFlagInfo view once the tail is solved.
## Evidence
0x7ef8 sw v0,0x28(sp) (found), 0x7f0c sw v0,0x24(sp) (isSet), 0x7ec8 sw zero,0x24(sp) before dispatch; 0x7f60-0x7f78 lw v0,0x28(sp); sltu t3,zero,v0; beqz t3 0x7f7c; move v0,t3; lw v0,0x24(sp); sltiu t4,v0,1; move v0,t4 (Q0457 fall-off shape).
