# gfxDrawTexturedTileGrid

## Sites
- global:807024E0:other:89672b
- global:807024E0:other:732a72

## Attempts
- 2026-11-14 HackSentinelSwitchChains opus:high: switch (bitSize) in source order 8/0x10/0x20/4 or sorted 4/8/0x10/0x20, with both copies, without rowT, without colS, without both: 408-716 diff lines (the copies alone stay at 754/3200 as recorded)
- 2026-11-14 HackSentinelSwitchChains opus:high: switch (bitSize) with colS removed: 601 (source order) / 593 (sorted)

## Untried ideas
- none from the switch lever: the target's compares rule it out (see Evidence)

## Evidence
- the bitSize ladder is a real else-if chain: the target reloads the byte for every compare (bne t9,8 at 0x3cb8, bne t8,0x10 at 0x3dfc, bne t7,0x20 at 0x3f44, bne t8,4 at 0x408c, in source order), which a switch (one load, one selector register) cannot give
- same ladder measurement as 89672b: the else-if chain is the target's (per-compare byte reloads at 0x3cb4-0x408c), so a switch cannot carry the colS copy's removal
