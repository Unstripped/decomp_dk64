# bossRoundFrame (boss, src/boss/3840.c)

## Sites
- 40c40a: the file-scope `void func_80724A20(void);`. RE-TAGGED `// ORIG:`.
  - The caller-side v0 use after the call proves a void declaration was in the original TU.

## Evidence
- Target: 0x1254 `jal func_80724A20`, 0x1268 `lbu v0,0x154(a2)`, 0x127c `beql v0,at`.
- With the s32 header prototype: 0x1268 `lbu v1`, 0x127c `beq v1`, later branches -4.
