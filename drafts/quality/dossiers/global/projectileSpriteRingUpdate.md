# projectileSpriteRingUpdate

## Sites
- global:80697988:other:d61aae

## Attempts
- 2026-11-14 HackSentinelSwitchChains opus:high: sentinel switch: switch (ringType) with case 1 then case 0 (old else arm) = 4 diff lines (v0 vs a0 only); case 0 first = 178; with a default = 4; switch (kind) with kind kept as the selector (u8/s32/u32/s16/u16, declared first) = 4-13; (s32)/(u8) selector casts = 4; if/else-if chains on ringType or kind = 65-223; if (ringType == 0) ... else switch = 180

## Untried ideas
- none from the switch lever: the target's compares rule it out (see Evidence)

## Evidence
- the target tests one lbu of ringType (lbu a0,17(v1) at 0x77c/0x844) with beqzl a0 at 0x84c (to the ringType == 0 block at 0x938) then bne a0,1 at 0x854; a two-case switch reproduces that block shape exactly but loads the byte into v0 (lbu v0 / beqzl v0 / bne v0), the same register miss as dropping the copy
